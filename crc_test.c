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
    int * cp = (int * )calloc(pcConfig.K - pcConfig.crcLen, sizeof(int));
    ARRAY_INT_COPY(cp, dataBits, pcConfig.K - pcConfig.crcLen);
    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
    int * dataHat = NR_CRC_DECODER(crcData, &pcConfig, &err);

    err = isEqual_INT(cp, dataHat, pcConfig.K - pcConfig.crcLen);

    if (err == 0) {
        printf("Successful Transmission\n");
    } else {
        printf("Corrupted Reception\n");
    }

    return 0;
}