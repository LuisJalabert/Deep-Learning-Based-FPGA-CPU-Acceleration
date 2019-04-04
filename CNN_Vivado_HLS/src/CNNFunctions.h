#ifndef CNN_CNNFUNCTIONS_H
#define CNN_CNNFUNCTIONS_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "ap_fixed.h"

#define data_in_x  	256
#define data_in_y 	76
#define dtr_in_x  	76
#define dtr_in_y  	256
#define data_in_CH 	1
#define kernel_size 2

#define C1_out_CH 	2
#define C1_out_x 	dtr_in_x-kernel_size+1
#define C1_out_y 	dtr_in_y-kernel_size+1
#define R1_out_x 	((dtr_in_x-kernel_size+1)/stride_x)
#define R1_out_y 	((dtr_in_y-kernel_size+1)/stride_y)

#define C2_out_x 	R1_out_x-kernel_size+1
#define C2_out_y 	R1_out_y-kernel_size+1
#define R2_out_x 	((R1_out_x-kernel_size+1)/stride_x)
#define R2_out_y 	((R1_out_y-kernel_size+1)/stride_y)
#define C2_out_CH  	4

#define C3_out_x 	R2_out_x-kernel_size+1
#define C3_out_y 	R2_out_y-kernel_size+1
#define R3_out_x 	((R2_out_x-kernel_size+1)/stride_x)
#define R3_out_y 	((R2_out_y-kernel_size+1)/stride_y)
#define C3_out_CH  	8

#define FC_in 		192
#define FC_out 		2

typedef ap_ufixed<1, 1, AP_RND, AP_SAT> fixed1;
typedef ap_fixed<6, 2, AP_RND, AP_SAT> fixed6;
//typedef float cnn_t;

void LoopOracle(float (&DataInTr)[1][dtr_in_x][dtr_in_y], int (&CnnOut)[FC_out]);

/*
template <size_t x_in_dim>
void print1dArray(int (&dataIn)[x_in_dim])
{
    for (int i = 0; i < x_in_dim; i++) {
        printf("%d, ", dataIn[i]);
        if ((i+1)%9 == 0){
            printf("\n");
        }
    }
    printf("\n\n");
}

template <size_t x_in_dim, size_t y_in_dim>
void print2dArray(float (&dataIn)[x_in_dim][y_in_dim])
{
    int i, j;
    for (i = 0; i < x_in_dim; i++) {
        for (j = 0; j < y_in_dim; j++) {
            printf("%.0f ", dataIn[i][j]);
            if ( j == y_in_dim-1){
                printf("\n");
            }
        }
    }
}


template <size_t x_in_dim, size_t y_in_dim, size_t z_in_dim>
void print3dArray(float (&dataIn)[x_in_dim][y_in_dim][z_in_dim])
{
    int i, j, k;
    for (i = 0; i < x_in_dim; i++) {
        for (j = 0; j < y_in_dim; j++) {
            for (k = 0; k < z_in_dim; k++){
                printf("%.4f ", dataIn[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

template <size_t x_in_dim, size_t y_in_dim, size_t z_in_dim, size_t t_in_dim>
void print4dArray(float (&dataIn)[x_in_dim][y_in_dim][z_in_dim][t_in_dim])
{
    int i, j, k, l;
    for (i = 0; i < x_in_dim; i++) {
        for (j = 0; j < y_in_dim; j++) {
            for (k = 0; k < z_in_dim; k++){
                for (l = 0; l < t_in_dim; l++){
                    printf("%f ", dataIn[i][j][k][l]);
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("\n");
    }
}
*/

#endif //CNN_CNNFUNCTIONS_H
