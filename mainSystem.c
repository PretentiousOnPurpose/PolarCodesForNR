#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "polarCodes.h"

int main() {

    srand(108);
    
    // Polar Code Config
    pcConfig.E = 144;
    pcConfig.K = 72;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 0;
    pcConfig.iIL = 0;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 24;
    pcConfig.crcPolyID = 1; 
    pcConfig.decodingMethod = 3;
    pcConfig.iter_BP = 100;
    pcConfig.LR_LLR = 1;

    int remLen = 0;
    int err = 0;

    int * dataBits = DATA_GEN(pcConfig.K - pcConfig.crcLen);
    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
    int * encData = NR_PC_ENCODER(crcData, &pcConfig);
    double * modData = BPSK_MOD(encData, pcConfig.N);
    double * rxData = AWGN(modData, pcConfig.N, 0.15);
    double * rxLR = BPSK_DEMOD(rxData, pcConfig.N, pcConfig.LR_LLR);
    // PRINT_ARRAY_DOUBLE(rxLR, 128);
    int * decData = NR_PC_DECODER(rxLR, &pcConfig);
    int * dataHat = NR_CRC_DECODER(decData, &pcConfig, &err);

    printf("Err: %d\n", err);

    PRINT_ARRAY_INT(dataBits, pcConfig.K - pcConfig.crcLen);
    PRINT_ARRAY_INT(dataHat, pcConfig.K - pcConfig.crcLen);


    // int encBits[] = {0, 0, 1, 1, 1, 0, 0, 0};
    // pcConfig.n = 3;
    // pcConfig.N = 8;
    // pcConfig.K = 8;
    
    // double * modData = BPSK_MOD(encBits, 8);
    // double * rxData = AWGN(modData, 8, 0.1);
    // double * rxLR = BPSK_DEMOD(modData, 8, 1);

    // // PRINT_ARRAY_DOUBLE(rxLR, 8);

    // int * dataHat = NR_PC_DECODER(rxLR, &pcConfig);
    // PRINT_ARRAY_INT(dataHat, 8);

    return 0;
}