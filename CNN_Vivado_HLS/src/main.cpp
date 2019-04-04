#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CNNFunctions.h"
#include "data_loader.cpp"
#include <dirent.h>


//#include <math.h>


int main() {

    float DataIn[data_in_x][data_in_y];
    float DataInTrSq[dtr_in_x][dtr_in_y];

    DIR *dir;
    struct dirent *ent;
    const char *dir_string = "/home/luis/Desktop/Thesis/dataset/";

    if ((dir = opendir (dir_string)) != NULL) {
        int correct, count = 0;
        while ((ent = readdir (dir)) != NULL) {
            if (( strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..") )) {
                int target[FC_out];

                target[0] = !(ent->d_name[0] - '0');
                target[1] = (ent->d_name[0] - '0');
                std::string full_file_path(dir_string);
                full_file_path.append(ent->d_name);
                data_loader<data_in_x, data_in_y>(DataIn, full_file_path);

                Transpose2d<data_in_x, data_in_y>(DataIn, DataInTrSq);

                float DataInTr[1][dtr_in_x][dtr_in_y];
                unsqueeze<dtr_in_x, dtr_in_y>(DataInTrSq, DataInTr);

                int CnnOut[FC_out];

                LoopOracle(DataInTr, CnnOut);

                if (target[0] == CnnOut[0]){
                    correct++;
                }
                count++;
            }
        }
        closedir (dir);
        printf("Accuracy(percent): %f ", 100*(double)correct/(double)count);
    } else {
        /* could not open directory */
        perror ("");
    }

    return 0;

}
