#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "polarCodes.h"

int main() {
    pcConfig.E = 144;
    pcConfig.K = 100;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 0;
    pcConfig.iIL = 0;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 11;
    pcConfig.crcPolyID = 5; 
    pcConfig.decodingMethod = 1;
    pcConfig.K_IL_MAX = 164;

    int err = 0;

    int * cp = (int *)calloc(100, sizeof(int));

    int * dataBits = DATA_GEN(100);
    // PRINT_ARRAY_INT(dataBits, 100);
    // printf("\nDATA\n\n");

    ARRAY_INT_COPY(cp, dataBits, 100);

    int * intrlvData = NR_PC_INPUT_BITS_INTERLEAVING(dataBits, &pcConfig, 0);
    // PRINT_ARRAY_INT(intrlvData, 100);
    // printf("\nINTR_DATA\n\n");

    int * deintrlvData = NR_PC_INPUT_BITS_INTERLEAVING(intrlvData, &pcConfig, 1);
    // PRINT_ARRAY_INT(deintrlvData, 100);
    // printf("\nINTR_DE\n\n");
    
    err = isEqual_INT(deintrlvData, cp, 100);

    printf("Result: %d\n", err);

    return 0;
}