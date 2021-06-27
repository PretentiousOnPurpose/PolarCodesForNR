#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "polarCodes.h"

int main() {

    srand(108);
    
    struct PC_CONFIG pcConfig;

    // Polar Code Config
    pcConfig.E = 144;
    pcConfig.K = 72;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 0;
    pcConfig.iIL = 1;
    pcConfig.K_IL_MAX = 164;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 24;
    pcConfig.crcPolyID = 1; 
    pcConfig.decodingMethod = 1;
    pcConfig.iter_BP = 10;
    pcConfig.LR_PROB_1 = 1;

    int remLen = 0;
    int err = 1;

    int * dataBits = DATA_GEN(pcConfig.K - pcConfig.crcLen);
    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
    int * encData = NR_PC_ENCODER(crcData, &pcConfig);
    double * modData = BPSK_MOD(encData, pcConfig.N);
    double * rxData = AWGN(modData, pcConfig.N, 0);
    double * rxLR = BPSK_DEMOD(rxData, pcConfig.N, pcConfig.LR_PROB_1);
    int * decData = NR_PC_DECODER(rxLR, &pcConfig);
    int * dataHat = NR_CRC_DECODER(decData, &pcConfig, &err);

    if (err == 0) {
        printf("Successful Transmission | %d out of %d bits in error\n", bitXORSum(dataHat, dataBits, pcConfig.K - pcConfig.crcLen), pcConfig.K - pcConfig.crcLen);
    } else {
        printf("Corrupted Reception | %d out of %d bits in error\n", bitXORSum(dataHat, dataBits, pcConfig.K - pcConfig.crcLen), pcConfig.K - pcConfig.crcLen);
    }

    return 0;
}
