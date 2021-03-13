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
    pcConfig.K_IL_MAX = 164;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 24;
    pcConfig.crcPolyID = 1; 
    pcConfig.decodingMethod = 1;
    pcConfig.iter_BP = 10;
    pcConfig.LR_PROB_1 = 0;

    int remLen = 0;
    int err = 1;

    int * dataBits = DATA_GEN(pcConfig.K); // - pcConfig.crcLen);
    int * cp = (int * )calloc(pcConfig.K, sizeof(int));
    ARRAY_INT_COPY(cp, dataBits, pcConfig.K);
    int * encData = NR_PC_ENCODER(dataBits, &pcConfig);
    PRINT_ARRAY_INT(encData, pcConfig.N);
    double * modData = BPSK_MOD(encData, pcConfig.N);
    PRINT_ARRAY_DOUBLE(modData, 5);
    printf("MODATA_____END____\n");
    double * demodData = BPSK_DEMOD(modData, pcConfig.N, pcConfig.LR_PROB_1);
    PRINT_ARRAY_DOUBLE(demodData, 5);
    int * dataHat = NR_PC_DECODER(demodData, &pcConfig);

    err = isEqual_INT(cp, dataHat, pcConfig.K); // - pcConfig.crcLen);
    PRINT_ARRAY_INT(cp, pcConfig.K);
    PRINT_ARRAY_INT(dataHat, pcConfig.K);

    if (err == 0) {
        printf("Successful Transmission\n");
    } else {
        printf("Corrupted Reception\n");
    }

    return 0;
}