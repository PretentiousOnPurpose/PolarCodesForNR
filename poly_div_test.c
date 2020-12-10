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
    pcConfig.iIL = 1;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 11;
    pcConfig.crcPolyID = 5; 
    pcConfig.decodingMethod = 1;
    pcConfig.K_IL_MAX = 164;

    int err = 0;

    int * dataBits = DATA_GEN(144);
    PRINT_ARRAY_INT(dataBits, 144);
    printf("\nDATA\n\n");

    int * iD = NR_PC_INPUT_BITS_INTERLEAVING(dataBits, &pcConfig, 0);
    PRINT_ARRAY_INT(iD, 144);
    printf("\nINTR_DATA\n\n");
    int * jD = NR_PC_INPUT_BITS_INTERLEAVING(iD, &pcConfig, 1);

    PRINT_ARRAY_INT(jD, 144);
    printf("\nINTR_DE\n\n");
    

    return 0;
}