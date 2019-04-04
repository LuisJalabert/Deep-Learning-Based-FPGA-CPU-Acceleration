//
// Created by luis on 12.03.19.
//

#ifndef CNN_DATA_LOADER_H

#define CNN_DATA_LOADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

template <size_t x_in_dim, size_t y_in_dim>
void data_loader(float (&data_in)[x_in_dim][y_in_dim], std::string file_name)
{
    std::ifstream file(file_name);

    std::string line;
    std::getline(file, line);

    for(int row = 0; row < x_in_dim; ++row)
    {
        std::getline(file, line);

        if ( !file.good() )
            break;

        std::stringstream iss(line);

        for (int col = 0; col < y_in_dim; ++col)
        {
            std::string val;
            std::getline(iss, val, ',');
            if ( !iss.good() )
                break;

            std::stringstream converter(val);
            converter >> data_in[row][col];
        }
    }
}

template <size_t x_in_dim, size_t y_in_dim>
void Transpose2d(float (&dataIn)[x_in_dim][y_in_dim], float (&dataOut)[y_in_dim][x_in_dim])
{
    for (int i = 0; i < x_in_dim; i++){
        for (int j = 0; j < y_in_dim; j++) {
            dataOut[j][i] = dataIn[i][j];
        }
    }
}


template <size_t x_in_dim, size_t y_in_dim>
void unsqueeze(float (&dataIn)[x_in_dim][y_in_dim], float (&dataOut)[1][x_in_dim][y_in_dim])
{
    for (int i = 0; i < x_in_dim; i++){
        for (int j = 0; j < y_in_dim; j++) {
            dataOut[0][i][j] = dataIn[i][j];
        }
    }
}



#endif //CNN_DATA_LOADER_H
