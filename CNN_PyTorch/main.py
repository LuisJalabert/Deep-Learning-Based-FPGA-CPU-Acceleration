# From Python:
import time
import os

# From Pytorch:
import torch
import torch.nn as nn
import torch.nn.functional as functional
from torch.utils.data import Dataset

# General libraries
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.utils import shuffle


#################
# Dataset import:
#################

class CPUTracesDatasetFromCSV(Dataset):
    def __init__(self, root_dir):
        super(CPUTracesDatasetFromCSV, self).__init__()
        self.root_dir = root_dir
        self.data = [pd.read_csv(os.path.join(root_dir, file)).values.astype(int)
                     for file in os.listdir(root_dir)
                     if file.endswith(".csv")]
        self.target = [[int(not(int(file[0]))), int(file[0])]
                       for file in os.listdir(root_dir)
                       if file.endswith(".csv")]

        self.data, self.target = shuffle(self.data, self.target)

    def __len__(self):
        return self.data.__len__()

    def __getitem__(self, idx):
        input_tensor = torch.FloatTensor(self.data[idx])
        output_tensor = torch.FloatTensor(self.target[idx]).unsqueeze(0)
        return input_tensor, output_tensor

    def get_batch(self, first_idx, last_idx):
        input_tensor = torch.FloatTensor(self.data[first_idx:last_idx]).permute(0, 2, 1).unsqueeze(1)
        output_tensor = torch.FloatTensor(self.target[first_idx:last_idx])
        # output_tensor = torch.LongTensor(self.target[first_idx:last_idx])
        return input_tensor, output_tensor


###############
# Define model:
###############

class ConvolutionalLoopOracle(nn.Module):
    def __init__(self):
        super(ConvolutionalLoopOracle, self).__init__()

        # Convolutional layers:
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=2, kernel_size=2)
        self.conv2 = nn.Conv2d(in_channels=2, out_channels=4, kernel_size=2)
        self.conv3 = nn.Conv2d(in_channels=4, out_channels=8, kernel_size=2)
        self.pool2x4 = nn.MaxPool2d(kernel_size=[2, 4], stride=[2, 4])

        # Output layer:
        self.fc = nn.Linear(8 * 8 * 3, 2)

    def forward(self, x):

        debug = 0
        if debug:
            print(x.shape)

        x = functional.relu(self.conv1(x))
        if debug:
            print(x.shape)

        x = self.pool2x4(x)
        if debug:
            print(x.shape)

        x = functional.relu(self.conv2(x))
        if debug:
            print(x.shape)

        x = self.pool2x4(x)
        if debug:
            print(x.shape)

        x = functional.relu(self.conv3(x))
        if debug:
            print(x.shape)

        x = self.pool2x4(x)
        if debug:
            print(x.shape)

        x = x.view(-1, 8 * 8 * 3)

        if debug:
            print(x.shape)

        x = functional.relu(self.fc(x))

        if debug:
            print(x.shape)

        return x


##############
# Train model:
##############

data = CPUTracesDatasetFromCSV("/home/luis/Desktop/Thesis/dataset/")


def train_model(model, learning_rate, num_epochs):
    print("Training started... Please Wait")
    criterion = nn.SmoothL1Loss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    loss_history = []
    val_history = []
    min_val = 1000
    val_loss_hist = []
    for i in range(num_epochs):
        start = time.time()
        loss_history.append(0)
        val_history.append(0)
        val_loss_hist.append(0)
        # use 80% of dataset as training:
        for j in range(int(0.8*data.__len__()/5)):
            x_t, y_t = data.get_batch(j*5, (j+1)*5)
            optimizer.zero_grad()
            y_hat = model(x_t)
            loss = criterion(y_hat, y_t)
            loss.backward()
            optimizer.step()
            loss_history[i] += loss.item()

        # Validation:
        with torch.no_grad():
            optimizer.zero_grad()
            # use 15% of dataset as validation:
            x_t, y_t = data.get_batch(int(0.8 * data.__len__()),
                                      int(0.95 * data.__len__()))
            y_hat = model(x_t)
            val_loss = criterion(y_hat, y_t)
            val_loss_hist[i] += val_loss

        if val_loss < min_val:
            min_val = val_loss
            torch.save(model.state_dict(), 'best_model.pt')
        end = time.time()
        print("Epoch: %3d/%3d, Training Loss: %2.5f, Validation Loss: %2.5f, Epoch Time: %3.2f seconds" %
              (i+1, num_epochs, loss_history[i], val_loss_hist[i], end - start))

    ###############
    # Show Results:
    ###############

    # Final accuracy test:
    with torch.no_grad():
        # use 5% of dataset as test.
        x_t, y_t = data.get_batch(int(0.95 * data.__len__()), data.__len__())
        y_hat = model(x_t).squeeze(0)
        _, max_ind = torch.max(y_hat, 1)
        y_pred = torch.zeros(y_t.shape)
        for j in range(max_ind .__len__()):
            y_pred[j, max_ind[j]] = 1
        correct = int(torch.sum(y_pred == y_t, dim=0)[0])
        accuracy = 100*correct/y_t.shape[0]
        print("Test accuracy = " + str(accuracy) + "%")

    fig, ax1 = plt.subplots()
    color = 'tab:red'
    ax1.set_xlabel('Epoch number')
    ax1.set_ylabel('Training Loss', color=color)
    ax1.plot(loss_history, color=color)
    ax1.tick_params(axis='y', labelcolor=color)

    ax2 = ax1.twinx()
    color = 'tab:blue'
    ax2.set_ylabel('Validation Loss', color=color)
    ax2.plot(val_loss_hist, color=color)
    ax2.tick_params(axis='y', labelcolor=color)
    fig.tight_layout()
    plt.show()


model = ConvolutionalLoopOracle()

train_model(model=model,
            learning_rate=0.001,
            num_epochs=150)

checkpoint = torch.load('best_model.pt')

model.load_state_dict(checkpoint)
