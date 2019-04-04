//
// Created by luis on 07.03.19.
//

#ifndef CNN_CNNFUNCTIONS_H
#define CNN_CNNFUNCTIONS_H

#include <stdio.h>
#include <math.h>
#include <string.h>


template <size_t x_in_dim, size_t y_in_dim, size_t ch_in, size_t ch_out, size_t kernel_size>
void Conv2d(float (&dataIn)[ch_in][x_in_dim][y_in_dim],
            float (&dataOut)[ch_out][x_in_dim-kernel_size+1][y_in_dim-kernel_size+1],
            float (&C2dWeights)[ch_out][ch_in][kernel_size][kernel_size], float (&C2dBias)[ch_out])
{
    int i, j, m, n, in, out;
    for (out=0; out < ch_out; out++){
        for (m=0; m < x_in_dim-kernel_size+1; m++){
            for (n=0; n < y_in_dim-kernel_size+1; n++){
                dataOut[out][m][n] = C2dBias[out];
                for (i = 0; i < kernel_size; i++){
                    for (j = 0; j < kernel_size; j++){
                        for (in = 0; in < ch_in; in++){
                            dataOut[out][m][n] = dataOut[out][m][n] + dataIn[in][m+i][n+j]*C2dWeights[out][in][i][j];
                        }
                    }
                }
            }
        }
    }
}


template <size_t x_dim>
void ReLU1d(float (&dataIn)[x_dim], float (&dataOut)[x_dim])
{
    int i;
    for (i = 0; i < x_dim; i++)
        dataOut[i] = (dataIn[i]>0) ? dataIn[i] : 0;
}

template <size_t x_in_dim, size_t y_in_dim>
void ReLU2d(float (&dataIn)[x_in_dim][y_in_dim], float (&dataOut)[x_in_dim][y_in_dim])
{
    int i, j;
    for (i = 0; i < x_in_dim; i++)
        for (j = 0; j < y_in_dim; j++)
            dataOut[i][j]= (dataIn[i][j]>0) ? dataIn[i][j] : 0;
}



template <size_t x_in_dim, size_t y_in_dim, size_t z_in_dim>
void ReLU3d(float (&dataIn)[x_in_dim][y_in_dim][z_in_dim], float (&dataOut)[x_in_dim][y_in_dim][z_in_dim])
{
    int i,j,k;
    for (i = 0; i < x_in_dim; i++)
        for (j = 0; j < y_in_dim; j++)
            for (k = 0; k < z_in_dim; k++)
                dataOut[i][j][k] = (dataIn[i][j][k]>0) ? dataIn[i][j][k] : 0;
}



template <size_t x_in_dim, size_t y_in_dim, size_t stride_x, size_t stride_y>
void MaxPool2d(float (&dataIn)[x_in_dim][y_in_dim], float (&dataOut)[x_in_dim/stride_x][y_in_dim/stride_y])
{
    int i, j, m, n;
    for (i = 0; i < x_in_dim/stride_x; i++){
        for (j = 0; j < y_in_dim/stride_y; j++){
            dataOut[i][j] = -INFINITY;
            for (m = 0; m < stride_x; m++){
                for (n = 0; n < stride_y; n++){
                    dataOut[i][j] = fmaxf(dataOut[i][j], dataIn[i*stride_x + m][j*stride_y + n]);
                }
            }
        }
    }
}

template <size_t ch_in_dim, size_t x_in_dim, size_t y_in_dim, size_t stride_x, size_t stride_y>
void MaxPool3d(float (&dataIn)[ch_in_dim][x_in_dim][y_in_dim],
               float (&dataOut)[ch_in_dim][x_in_dim/stride_x][y_in_dim/stride_y])
{
    int i, j, k, m, n;
    for (k = 0; k < ch_in_dim; k++) {
        for (i = 0; i < x_in_dim / stride_x; i++) {
            for (j = 0; j < y_in_dim / stride_y; j++) {
                dataOut[k][i][j] = -INFINITY;
                for (m = 0; m < stride_x; m++) {
                    for (n = 0; n < stride_y; n++) {
                        dataOut[k][i][j] = fmaxf(dataOut[k][i][j], dataIn[k][i * stride_x + m][j * stride_y + n]);
                    }
                }
            }
        }
    }
}


template <size_t x_in_dim, size_t y_in_dim, size_t z_in_dim>
void view(float (&dataIn)[x_in_dim][y_in_dim][z_in_dim], float (&dataOut)[x_in_dim*y_in_dim*z_in_dim])
{
    int i, j, k, l;
    l=0;
    for (i=0; i<x_in_dim; i++){
        for (j=0; j<y_in_dim; j++){
            for (k=0; k<z_in_dim; k++) {
                dataOut[l] = dataIn[i][j][k];
                l++;
            }
        }
    }
}

template <size_t fc_in, size_t fc_out>
void FullyConnected(float (&dataIn)[fc_in], float dataOut[fc_out],
                    float (&FCWeights)[fc_out][fc_in], float (&FCBias)[fc_out])
{
    int i, j;
    for (i=0; i<fc_out; i++){
        dataOut[i] = FCBias[i];
        for (j=0; j<fc_in; j++){
            dataOut[i] = dataOut[i] + dataIn[j]*FCWeights[i][j];
        }
    }
}


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



//Define CNN weights and bias:

//Data input:
//torch.Size([1, 76, 512])
#define data_in_x  256
#define data_in_y  76
#define dtr_in_x  76
#define dtr_in_y  256
#define data_in_CH 1

#define kernel_size  2
//Convolutional layer 1:
#define C1_out_CH  2


float C1W[C1_out_CH][data_in_CH][kernel_size][kernel_size] = {{{{ 0.2495,  0.6952},
                                                                       {-0.0093, -0.2705}}},

                                                              {{{ 0.7643,  0.6514},
                                                                       {-0.1802,  0.1769}}}};

float C1B[C1_out_CH] = {0.0215, 0.1528};


//Convolutional layer 2:
#define C2_out_CH  4

float C2W[C2_out_CH][C1_out_CH][kernel_size][kernel_size] =   {{{{ 0.2503,  0.5665},
                                                                        { 0.0036,  0.3982}},

                                                                       {{ 0.0933, -0.2098},
                                                                               {-0.3536,  0.0921}}},


                                                               {{{ 0.0741,  0.2164},
                                                                        {-0.1738, -0.3329}},

                                                                       {{ 0.5837,  0.3433},
                                                                               {-0.0689, -0.3666}}},


                                                               {{{-0.2262, -0.2788},
                                                                        {-0.1670, -0.2034}},

                                                                       {{-0.2885, -0.1306},
                                                                               {-0.3069, -0.2642}}},


                                                               {{{-0.3557, -0.1726},
                                                                        {-0.3870,  0.4434}},

                                                                       {{-0.5039,  0.0656},
                                                                               { 0.4532,  0.1524}}}};


float C2B[C2_out_CH] = {-0.3471, -0.1473, -0.0187, -0.3810};

//Convolutional layer 3:
#define C3_out_CH  8

float C3W[C3_out_CH][C2_out_CH][kernel_size][kernel_size] =   {{{{ 0.1002,  0.2036},
                                                                        {-0.1372,  0.1525}},

                                                                       {{-0.2649, -0.0033},
                                                                               {-0.0387, -0.1558}},

                                                                       {{ 0.0402,  0.1817},
                                                                               { 0.2373,  0.1291}},

                                                                       {{-0.1171, -0.0594},
                                                                               {-0.0632,  0.0762}}},

                                                               {{{-0.5694, -0.2572},
                                                                        {-0.0639, -0.1435}},

                                                                       {{ 0.6261, -0.1792},
                                                                               {-0.2571, -0.0931}},

                                                                       {{ 0.1354, -0.0504},
                                                                               { 0.0973, -0.0616}},

                                                                       {{-0.7480, -0.2495},
                                                                               {-0.0772,  0.0182}}},


                                                               {{{ 0.3280,  0.5376},
                                                                        { 0.4417, -0.2036}},

                                                                       {{ 0.1155,  0.1416},
                                                                               {-0.1166, -0.1668}},

                                                                       {{ 0.1868,  0.0679},
                                                                               { 0.1224, -0.1725}},

                                                                       {{ 0.5698, -0.1814},
                                                                               { 0.4714, -0.1392}}},

                                                               {{{ 0.0442,  0.1584},
                                                                        { 0.1004, -0.1083}},

                                                                       {{ 0.0608,  0.2177},
                                                                               { 0.0241,  0.0734}},

                                                                       {{ 0.2350, -0.2179},
                                                                               {-0.1837, -0.1981}},

                                                                       {{ 0.0432,  0.0835},
                                                                               { 0.0649,  0.0137}}},


                                                               {{{-0.9156, -1.1689},
                                                                        { 0.0115, -0.0784}},

                                                                       {{-0.0677, -0.2593},
                                                                               {-0.0359, -0.0581}},

                                                                       {{-0.2292, -0.0496},
                                                                               {-0.2495,  0.2441}},

                                                                       {{ 0.0427,  0.2129},
                                                                               { 0.0456, -0.1024}}},


                                                               {{{ 0.0479, -0.0574},
                                                                        {-0.3265,  0.0530}},

                                                                       {{ 0.0848,  0.0861},
                                                                               {-0.1167,  0.1574}},

                                                                       {{-0.0804, -0.2328},
                                                                               {-0.1577,  0.1607}},

                                                                       {{-0.1328, -0.0078},
                                                                               {-0.0613,  0.0213}}},


                                                               {{{-0.1902, -0.3171},
                                                                        { 0.2290, -0.1157}},

                                                                       {{ 0.0168, -0.4969},
                                                                               {-0.2179,  0.2624}},

                                                                       {{-0.2204,  0.0888},
                                                                               { 0.1242,  0.0146}},

                                                                       {{ 0.5564, -0.0566},
                                                                               { 0.3385, -0.3402}}},


                                                               {{{-0.0899, -0.0268},
                                                                        { 0.4744, -0.5464}},

                                                                       {{ 0.0423,  0.0931},
                                                                               {-0.1810, -0.2237}},

                                                                       {{ 0.0200,  0.0771},
                                                                               {-0.1452, -0.0383}},

                                                                       {{ 0.8099, -0.3167},
                                                                               { 0.4124, -0.5939}}}};


float C3B[C3_out_CH] = {-0.0971,  0.1375, -0.3351, -0.2679,  0.3977,  0.1135, -0.0795,  0.0398};


//Fully connected output layer:
//torch.Size([576])
//torch.Size([2])
//#define FC_in  4;

#define FC_in 192
#define FC_out 2

float FCW[FC_out][FC_in] =    {{ 3.6558e-03, -3.2627e-02,  4.2215e-02, -3.9226e-03, -5.2063e-03,
                                       7.1430e-02, -4.4163e-02,  7.0535e-02,  7.0741e-02, -2.9209e-02,
                                       -2.7480e-03,  2.0483e-02, -4.6853e-02, -4.8983e-03,  1.8983e-02,
                                       6.9033e-02, -4.0232e-02, -6.6660e-02, -1.3226e-02,  6.5270e-02,
                                       3.6137e-02, -4.8851e-02,  3.1263e-04,  7.1858e-02,  1.0191e+00,
                                       -4.3431e-02, -2.9340e-02, -4.7531e-02,  5.9558e-02,  1.0375e-01,
                                       -1.3672e-01, -1.0210e-01, -4.6223e-02, -2.2028e-02,  4.6108e-02,
                                       -5.0628e-02, -5.0690e-02,  3.5503e-02,  2.5284e-02,  1.4359e-02,
                                       -3.3188e-02, -5.1140e-02, -1.4673e-02,  2.0149e-02,  6.5366e-02,
                                       -8.7271e-03, -7.0678e-02,  4.1720e-02, -3.5606e-01, -1.6281e-01,
                                       -6.3010e-02, -1.1839e-01, -1.3046e-01, -1.8279e-01, -2.8003e-02,
                                       -3.0381e-02,  1.5533e-01,  6.1333e-02,  8.4046e-03,  1.6871e-02,
                                       9.0330e-02, -6.9502e-03, -3.1157e-02,  3.5524e-04,  2.9371e-02,
                                       3.1291e-02,  2.3114e-03,  3.1063e-02,  2.0371e-02, -1.0563e-02,
                                       -5.2218e-02,  4.2273e-02, -3.7816e-02,  1.3562e-02, -7.0638e-02,
                                       1.5589e-01,  7.6448e-03, -1.9730e-02, -1.1977e-01, -1.3267e-01,
                                       1.1371e-02,  1.5617e-02, -1.4312e-02, -4.7854e-02,  7.5585e-02,
                                       4.1256e-02, -2.0657e-02,  2.2452e-02,  5.7296e-02,  4.5764e-02,
                                       7.5806e-02, -7.5825e-02, -2.5100e-02,  1.1542e-02, -7.4170e-02,
                                       -5.9403e-02, -7.0712e-01, -1.5551e-01, -1.5392e-01,  4.5490e-01,
                                       3.3910e-01,  3.1892e-01,  2.8741e-01,  8.9714e-02, -2.5250e-02,
                                       -1.5487e-01,  1.5544e-01,  6.0846e-03, -3.4574e-02, -6.9071e-03,
                                       3.4640e-02,  3.2540e-01,  4.1600e-02,  1.4811e-01,  2.3007e-02,
                                       -3.5421e-02,  7.0415e-03,  2.8876e-01,  1.4240e-02,  1.1209e-01,
                                       -4.6937e-02,  6.6729e-03, -3.1954e-03,  7.5046e-02,  1.2890e-01,
                                       1.1466e-01, -5.1618e-02,  2.9369e-02,  1.3195e-01,  1.8173e-02,
                                       6.1785e-02,  6.4946e-03,  5.0202e-03,  6.8431e-02, -5.9397e-02,
                                       3.3012e-02, -6.6238e-03,  5.2508e-02,  2.7428e-02, -1.3633e-02,
                                       -3.6757e-02,  1.0960e-01,  5.2477e-02, -4.0004e-02,  5.2990e-01,
                                       -3.7679e-01, -1.8187e-01, -3.9973e-02, -4.5801e-01, -1.2355e-01,
                                       6.9153e-03, -1.1886e-01,  2.5005e-01,  1.3011e-02,  1.3801e-02,
                                       -1.2104e-02,  8.9357e-02,  8.8639e-02, -1.6785e-01,  1.2259e-02,
                                       6.7592e-03, -1.2007e-01,  6.5805e-02, -9.3085e-02, -1.4911e-01,
                                       1.5164e-02,  2.4661e-02, -1.0603e-01, -7.8609e-01, -2.8488e-01,
                                       -2.9388e-02, -1.1178e-01,  2.5456e-02,  8.4969e-02,  1.3201e-01,
                                       4.1403e-02,  1.7898e-01, -7.0961e-02,  4.3944e-03,  4.2936e-02,
                                       -3.7471e-02,  6.7398e-02, -2.1389e-02, -1.1745e-02,  6.7527e-02,
                                       1.4350e-02, -4.9557e-03,  1.1438e-04,  5.7967e-02, -4.0155e-02,
                                       6.4373e-02,  5.9423e-02},

                               {-3.3660e-02,  5.2401e-02, -3.2279e-02,  1.9713e-02,  6.5904e-02,
                                       2.7068e-02,  2.5472e-02, -6.4461e-04,  6.6081e-02,  5.4560e-02,
                                       -7.8562e-03, -1.3177e-02, -3.4925e-02,  1.8079e-02,  7.5376e-03,
                                       -1.6000e-02, -2.6578e-02, -2.0938e-02, -3.1819e-02, -5.8390e-02,
                                       -3.7515e-03, -1.6131e-02,  1.1469e-02, -1.3605e-02, -1.0462e+00,
                                       -4.4869e-02,  8.2960e-02,  1.3186e-01, -1.3735e-02,  7.6418e-02,
                                       1.3174e-01,  1.1838e-01,  2.1032e-01,  4.7040e-02, -1.4923e-02,
                                       -7.4420e-02,  3.5976e-02,  1.3849e-03,  2.7331e-02, -6.2945e-02,
                                       6.2869e-02, -1.3469e-02,  4.7827e-03,  2.3253e-02, -6.4605e-02,
                                       3.8285e-02,  1.2144e-02,  1.3046e-02,  3.0618e-01,  1.6002e-01,
                                       1.7484e-01, -5.0946e-02,  8.4632e-03,  1.4537e-01,  5.1940e-02,
                                       -9.3886e-02,  1.0542e-01, -4.1265e-02, -3.1216e-02, -3.1954e-02,
                                       -3.1560e-02, -2.4488e-02,  9.8255e-03, -8.4932e-02,  4.0151e-02,
                                       -1.9619e-02, -8.9410e-02, -2.2586e-02,  4.1530e-02,  2.6905e-02,
                                       9.9104e-02, -1.2242e-01,  1.5818e-01,  1.0300e-01,  1.6314e-02,
                                       -2.4030e-01, -8.2216e-02, -2.9780e-02,  2.0565e-01,  7.8464e-02,
                                       3.1167e-02, -8.4922e-02,  1.3136e-02, -2.5306e-02, -1.1245e-01,
                                       -1.2753e-01, -5.6909e-02, -4.7001e-02, -6.3269e-02,  2.9097e-03,
                                       -5.0569e-02,  1.3485e-02, -1.5599e-02,  7.4933e-02,  4.3906e-02,
                                       -2.0674e-02,  5.7147e-01,  2.8324e-01,  1.0678e-01, -4.9484e-01,
                                       -2.3408e-01, -9.3301e-02, -8.8654e-02,  5.8209e-02,  1.6026e-01,
                                       -1.5294e-01, -1.1514e-01,  6.8394e-02,  8.2321e-02,  6.1368e-02,
                                       -4.4569e-02, -2.3609e-01, -1.0962e-01, -1.0047e-01, -4.5938e-03,
                                       -6.0204e-02,  6.7236e-02, -2.7657e-01,  3.6863e-02,  3.6026e-02,
                                       4.9778e-02,  1.1104e-01,  8.4829e-02,  5.5776e-02,  3.7303e-02,
                                       -8.4547e-02,  8.3021e-02,  3.7604e-03, -2.6045e-02,  3.9103e-02,
                                       5.5573e-03,  1.0465e-01,  7.7264e-02, -3.2195e-02, -9.8168e-02,
                                       1.3861e-02,  6.9481e-02,  6.2269e-02,  3.4634e-03, -3.3988e-02,
                                       -1.2236e-02,  2.8032e-02,  3.6470e-03,  2.3071e-02, -5.1772e-01,
                                       3.3202e-01,  2.1072e-01, -7.0746e-02,  4.3279e-01,  6.7992e-02,
                                       1.3616e-01,  3.2281e-03, -3.7164e-01,  8.6226e-03, -1.6348e-01,
                                       -2.2665e-01,  9.5637e-02, -2.9574e-02, -8.8870e-02,  3.5575e-02,
                                       -6.2715e-02, -1.0189e-02,  4.5355e-02, -5.0849e-02,  1.0125e-01,
                                       -1.9251e-01, -1.0790e-01,  4.3701e-04,  7.1528e-01,  1.7032e-01,
                                       7.1783e-02,  1.8129e-01,  3.6587e-02,  1.5882e-02, -2.0241e-01,
                                       -4.1432e-02, -1.9950e-01,  4.5620e-02,  1.6784e-02,  2.7767e-02,
                                       2.9919e-02, -8.8911e-03, -3.8847e-02,  5.2215e-02, -1.4271e-02,
                                       2.1651e-02, -1.7864e-02,  1.0957e-01, -3.7813e-02, -3.0163e-02,
                                       -2.4705e-02, -3.6848e-02}};


float FCB[FC_out] = {0.0259, 0.0841};


template <size_t in_x, size_t in_y, size_t out_x>
void LoopOracle(float (&DataInTr)[1][in_x][in_y], int (&CnnOut)[out_x])
{
#define stride_x 2
#define stride_y 4


//..::First convolutional layer::..
// kernel size = 2x2, 1 input channel, 2 output channel
#define C1_out_x dtr_in_x-kernel_size+1
#define C1_out_y dtr_in_y-kernel_size+1

    float DataOutC1[C1_out_CH][C1_out_x][C1_out_y];

    Conv2d<in_x, in_y, data_in_CH, C1_out_CH, kernel_size>(DataInTr, DataOutC1, C1W, C1B);

    ReLU3d<C1_out_CH, C1_out_x, C1_out_y>(DataOutC1, DataOutC1);

#define R1_out_x ((dtr_in_x-kernel_size+1)/stride_x)
#define R1_out_y ((dtr_in_y-kernel_size+1)/stride_y)

    float DataOutMP1[C1_out_CH][R1_out_x][R1_out_y];

    MaxPool3d<C1_out_CH, C1_out_x, C1_out_y, stride_x, stride_y>(DataOutC1, DataOutMP1);

//..::Second convolutional layer::..
//kernel size = 2x2, 2 input channel, 4 output channel
#define C2_out_x R1_out_x-kernel_size+1
#define C2_out_y R1_out_y-kernel_size+1

    float DataOutC2[C2_out_CH][C2_out_x][C2_out_y];

    Conv2d<R1_out_x, R1_out_y, C1_out_CH, C2_out_CH, kernel_size>(DataOutMP1, DataOutC2, C2W, C2B);

    ReLU3d<C2_out_CH, C2_out_x, C2_out_y>(DataOutC2, DataOutC2);


#define R2_out_x ((R1_out_x-kernel_size+1)/stride_x)
#define R2_out_y ((R1_out_y-kernel_size+1)/stride_y)

    float DataOutMP2[C2_out_CH][R2_out_x][R2_out_y];

    MaxPool3d<C2_out_CH, C2_out_x, C2_out_y, stride_x, stride_y>(DataOutC2, DataOutMP2);

//    print3dArray(DataOutMP2);

//..::Third convolutional layer::..
//kernel size = 2x2, 4 input channel, 8 output channel
#define C3_out_x R2_out_x-kernel_size+1
#define C3_out_y R2_out_y-kernel_size+1

    float DataOutC3[C3_out_CH][C3_out_x][C3_out_y];

    Conv2d<R2_out_x, R2_out_y, C2_out_CH, C3_out_CH, kernel_size>(DataOutMP2, DataOutC3, C3W, C3B);
    ReLU3d<C3_out_CH, C3_out_x, C3_out_y>(DataOutC3, DataOutC3);

#define R3_out_x ((R2_out_x-kernel_size+1)/stride_x)
#define R3_out_y ((R2_out_y-kernel_size+1)/stride_y)

    float DataOutMP3[C3_out_CH][R3_out_x][R3_out_y];

    MaxPool3d<C3_out_CH, C3_out_x, C3_out_y, stride_x, stride_y>(DataOutC3, DataOutMP3);


//..::Fully connected layer::..

    float dataOutView[C3_out_CH*R3_out_x*R3_out_y];
    view<C3_out_CH, R3_out_x, R3_out_y>(DataOutMP3, dataOutView);

    float dataOut[out_x];

    FullyConnected<FC_in, out_x>(dataOutView, dataOut, FCW, FCB);

    ReLU1d<out_x>(dataOut, dataOut);


    if (dataOut[0] < dataOut[1]){
        CnnOut[0] = 0;
        CnnOut[1] = 1;
    } else {
        CnnOut[0] = 1;
        CnnOut[1] = 0;
    }

}




#endif //CNN_CNNFUNCTIONS_H
