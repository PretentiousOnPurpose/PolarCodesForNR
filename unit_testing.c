#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "polarCodes.h"

int main() {
    pcConfig.E = 144;
    pcConfig.K = 72;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 0;
    pcConfig.iIL = 0;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 11;
    pcConfig.crcPolyID = 5; 
    pcConfig.decodingMethod = 0;
    pcConfig.K_IL_MAX = 164;
    pcConfig.LR_PROB_1 = 1;

    int err = 0;

    int * cp = (int *)calloc(72, sizeof(int));

    int * dataBits = DATA_GEN(pcConfig.K);
    PRINT_ARRAY_INT(dataBits, pcConfig.K);
    printf("\nDATA\n\n");

    ARRAY_INT_COPY(cp, dataBits, pcConfig.K);

    int * encData = NR_PC_ENCODER(dataBits, &pcConfig);
    PRINT_ARRAY_INT(encData, pcConfig.N);
    printf("\nENC_DATA\n\n");

    double * modData = BPSK_MOD(dataBits, pcConfig.N);
    double * demodData = BPSK_DEMOD(modData, pcConfig.N, 0);

    int * decData = NR_PC_DECODER(demodData, &pcConfig);
    PRINT_ARRAY_INT(decData, pcConfig.K);
    printf("\nDEC_DATA\n");
    
    err = isEqual_INT(decData, cp, pcConfig.K);

    printf("Result: %d\n", err);

    return 0;
}