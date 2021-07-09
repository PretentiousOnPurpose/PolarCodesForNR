#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "polarCodes.h"

int main() {

    srand(108);
    
    struct PC_CONFIG pcConfig;

    // Polar Code Config
    pcConfig.E = 256;
    pcConfig.K = 144;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 1;
    pcConfig.iIL = 1;
    pcConfig.K_IL_MAX = 164;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 11;
    pcConfig.crcPolyID = 5; 
    pcConfig.decodingMethod = 1;
    pcConfig.iter_BP = 10;
    pcConfig.LR_PROB_1 = 1;

    int remLen = 0;
    int err = 1;

    printf("Polar Codes for 5G NR\n\n");

    int * dataBits = DATA_GEN(pcConfig.K - pcConfig.crcLen);
    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
    int * encData = NR_PC_ENCODER(crcData, &pcConfig);
    int * rateMatcData = NR_PC_RATE_MATCH(encData, &pcConfig);
    double * modData = BPSK_MOD(rateMatcData, pcConfig.E);
    double * rxData = AWGN(modData, pcConfig.E, 0);
    double * rxLR = BPSK_DEMOD(rxData, pcConfig.E, pcConfig.LR_PROB_1);
    double * rateRecoverData = NR_PC_RATE_RECOVER(rxLR, &pcConfig);
    int * decData = NR_PC_DECODER(rateRecoverData, &pcConfig);
    int * dataHat = NR_CRC_DECODER(decData, &pcConfig, &err);

    if (err == 0) {
        printf("Successful Transmission | %d out of %d bits in error\n", bitXORSum(dataHat, dataBits, pcConfig.K - pcConfig.crcLen), pcConfig.K - pcConfig.crcLen);
    } else {
        printf("Corrupted Reception | %d out of %d bits in error\n", bitXORSum(dataHat, dataBits, pcConfig.K - pcConfig.crcLen), pcConfig.K - pcConfig.crcLen);
    }

    return 0;
}
