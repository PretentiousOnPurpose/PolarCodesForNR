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
    pcConfig.iter_BP = 10;
    pcConfig.LR_PROB_1 = 1;

    int remLen = 0;
    int err = 1;

    int * dataBits = DATA_GEN(pcConfig.K - pcConfig.crcLen);
    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
    int * encData = NR_PC_ENCODER(crcData, &pcConfig);
    double * modData = BPSK_MOD(encData, pcConfig.N);
    double * rxData = AWGN(modData, pcConfig.N, 0.12);
    double * rxLR = BPSK_DEMOD(rxData, pcConfig.N, pcConfig.LR_PROB_1);
    int * decData = NR_PC_DECODER(rxLR, &pcConfig);
    int * dataHat = NR_CRC_DECODER(decData, &pcConfig, &err);

    if (err == 0) {
        printf("Successful Transmission\n");
    } else {
        printf("Corrupted Reception\n");
    }

    return 0;
}