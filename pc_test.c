#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "polarCodes.h"

int main() {

    srand(108);
    
    
    struct PC_CONFIG pcConfig;

    // Polar Code Config
    pcConfig.E = 12;
    pcConfig.K = 6;
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

    int * dataBits = DATA_GEN(pcConfig.E); // - pcConfig.crcLen);
    PRINT_ARRAY_INT(dataBits, pcConfig.E);
    int * intrlvdata = NR_PC_CODED_BITS_INTERLEAVING(dataBits, &pcConfig);
    PRINT_ARRAY_INT(intrlvdata, pcConfig.E);

    double * dd = (double *)calloc(pcConfig.E, sizeof(double));

    for (int i = 0; i < pcConfig.E; i++) {
        *(dd + i) = (double)intrlvdata[i];
    }

    double * deintrlvdata = NR_PC_CODED_BITS_DEINTERLEAVING(dd, &pcConfig);
    PRINT_ARRAY_DOUBLE(deintrlvdata, pcConfig.E);

    return 0;
}