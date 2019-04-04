# From Python:
import time
import os

# From Pytorch:
import torch
import torch.nn as nn
import torch.nn.functional as functional
from torch.utils.data import Dataset

# General libraries
import numpy as np
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

        self.target = [[int(file.split("_")[9].split("head")[1]),
                        int(file.split("_")[10].split("tail")[1].split(".csv")[0])]
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
        # input sequence is of shape (seq_len, batch, input_size)
        input_tensor = torch.FloatTensor(self.data[first_idx:last_idx]).permute(1, 0, 2)
        output_tensor = torch.FloatTensor(self.target[first_idx:last_idx])
        # output_tensor = torch.LongTensor(self.target[first_idx:last_idx])
        return input_tensor, output_tensor


################
# Define models:
################

class LSTMAddressOracle(nn.Module):
    def __init__(self, vector_dim, lstm_hidden_dim, lstm_layers, output_dim, kernel_size, batch_size):
        super(LSTMAddressOracle, self).__init__()

        self.batch_size = batch_size
        # self.kernel_size = kernel_size
        # LSTM layers:
        self.lstm = nn.LSTM(input_size=vector_dim,
                            hidden_size=lstm_hidden_dim,
                            num_layers=lstm_layers,
                            dropout=0.2)
        # Convolutional layers: input shape is [batch_size, in_channels, len]

        self.conv0 = torch.nn.Conv1d(in_channels=1,
                                     out_channels=2,
                                     kernel_size=kernel_size)

        self.conv1 = torch.nn.Conv1d(in_channels=2,
                                     out_channels=4,
                                     kernel_size=kernel_size)

        self.conv2 = torch.nn.Conv1d(in_channels=4,
                                     out_channels=8,
                                     kernel_size=kernel_size)

        self.conv3 = torch.nn.Conv1d(in_channels=8,
                                     out_channels=16,
                                     kernel_size=kernel_size)

        self.conv4 = torch.nn.Conv1d(in_channels=16,
                                     out_channels=32,
                                     kernel_size=kernel_size)

        self.pool = nn.MaxPool1d(kernel_size=kernel_size,
                                 stride=2)

        # Linear layers:
        # features = 224
        features = 1012
        self.fc_layer_0 = nn.Linear(in_features=lstm_hidden_dim,
                                    out_features=output_dim)
        self.fc_layer_1 = nn.Linear(in_features=features,
                                    out_features=features)
        self.fc_layer_2 = nn.Linear(in_features=features,
                                    out_features=output_dim)

    def forward(self, input_sequence, hidden=None):
        # print(input_sequence.shape)

        output = self.conv0(input_sequence.permute(1, 2, 0))
        # output = self.pool(functional.relu(output))
        #
        # output = self.conv1(output)
        # output = self.pool(functional.relu(output))
        #
        # output = self.conv2(output)
        # output = self.pool(functional.relu(output))
        #
        # output = self.conv3(output)
        # output = self.pool(functional.relu(output))
        #
        # output = self.conv4(output)
        # output = self.pool(functional.relu(output))

        # print(output.shape)
        # print(output.view(self.batch_size, -1).shape)

        output = functional.relu(self.fc_layer_1(output.view(self.batch_size, -1)))
        output = self.fc_layer_2(output)

        # output, hidden = self.lstm(input_sequence, hidden)
        # print(output.shape)

        # print(output.view(-1, output.size(1)).shape)
        # print(output[-1].view(self.batch_size, -1).shape)

        # output = self.fc_layer_0(output[-1].view(self.batch_size, -1))

        # print(output[:, :, -1].permute(1, 0).shape)
        # output = functional.relu(self.fc_layer_0(output[510, :, :]))

        # output = functional.relu(self.fc_layer_1(output[:, :, -1].permute(1, 0)))
        # output = functional.relu(self.fc_layer_2(output))

        # output = self.fc_layer_2(output.view(-1, output.size(1)).permute(1, 0))
        # print(output.shape)
        # output = functional.relu(output)
        #
        # output = functional.relu(self.fc_layer_1(input_sequence.squeeze(2).permute(1, 0)))
        # output = functional.relu(self.fc_layer_1(output))
        # output = functional.relu(self.fc_layer_1(output))
        # output = functional.relu(self.fc_layer_2(output))
        return output


##############
# Train model:
##############
data = CPUTracesDatasetFromCSV("./dataset/")


def train_model(model, learning_rate, num_epochs, mini_batch_size):
    print("Training started... Please Wait")
    # criterion = nn.NLLLoss()
    # criterion = nn.CrossEntropyLoss()
    # criterion = nn.MSELoss()
    # criterion = nn.BCELoss()
    criterion = nn.SmoothL1Loss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    loss_history = []
    val_history = []
    min_val = 10000
    val_loss_hist = []
    for i in range(num_epochs):
        start = time.time()
        loss_history.append(0)
        val_history.append(0)
        val_loss_hist.append(0)
        # use 80% of dataset as training:
        for j in range(int(0.8*data.__len__()/mini_batch_size)):
            x_t, y_t = data.get_batch(j*mini_batch_size, (j+1)*mini_batch_size)
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
            for j in range(int(0.8 * data.__len__()/mini_batch_size), int(0.95 * data.__len__()/mini_batch_size)):
                x_t, y_t = data.get_batch(j * mini_batch_size, (j + 1) * mini_batch_size)
            # x_t, y_t = data.get_batch(int(0.8 * data.__len__()),
            #                           int(0.95 * data.__len__()))
                y_hat = model(x_t)
                val_loss = criterion(y_hat, y_t)
                val_loss_hist[i] += val_loss
                # print(y_t)
                # print(y_hat)

        if val_loss_hist[i] < min_val:
            min_val = val_loss_hist[i]
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
        # x_t, y_t = data.get_batch(int(0.95 * data.__len__()), data.__len__())

        checkpoint = torch.load('best_model.pt')
        model.load_state_dict(checkpoint)
        accuracy = []
        for j in range(int(0.95 * data.__len__() / mini_batch_size), int(data.__len__()/mini_batch_size)):
            x_t, y_t = data.get_batch(j * mini_batch_size, (j + 1) * mini_batch_size)
            y_hat = model(x_t).squeeze(0)
            y_hat = torch.round(y_hat)
            correct = int(torch.sum(y_hat == y_t))
            accuracy.append(100*correct/(y_t.shape[0]*y_t.shape[1]))
            print(y_t)
            print(y_hat)

        accuracy = np.mean(accuracy)
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


batch_size = 5

loop_oracle_model = LSTMAddressOracle(vector_dim=1,
                                      lstm_hidden_dim=8,
                                      lstm_layers=2,
                                      output_dim=2,
                                      kernel_size=6,
                                      batch_size=batch_size)


train_model(model=loop_oracle_model,
            learning_rate=0.0005,
            num_epochs=200,
            mini_batch_size=batch_size)

# checkpoint = torch.load('best_model.pt')
#
# loop_oracle_model.load_state_dict(checkpoint)
#
# model = loop_oracle_model
