#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    pcConfig.crcPolyID = 2; 
    pcConfig.decodingMethod = 1;

    int remLen = 0;
    int err = 0;
//
    int * dataBits = DATA_GEN(pcConfig.K);
//    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
   int * encData = NR_PC_ENCODER(dataBits, &pcConfig);
   double * modData = BPSK_MOD(encData, pcConfig.N);
   double * rxData = AWGN(modData, pcConfig.N, 0.1);
   double * rxLR = BPSK_DEMOD(modData, pcConfig.N);
   int * dataHat = NR_PC_DECODER(rxLR, &pcConfig);
//    int * dataHat = NR_CRC_DECODER(decData, &pcConfig, &err);


    // PRINT_ARRAY_INT(dataHat, pcConfig.K);
    // // PRINT_ARRAY_DOUBLE(modData, pcConfig.N);

    PRINT_ARRAY_INT(dataHat, pcConfig.K);
    PRINT_ARRAY_INT(dataBits, pcConfig.K);

    return 0;
}