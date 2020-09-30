#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int main() {

    srand(108);

    // Polar Code Config
    pcConfig.E = 192;
    pcConfig.K = 96;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 1;
    pcConfig.iIL = 0;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 24;
    pcConfig.crcPoly = "24B"; 

    int * dataBits = DATA_GEN(10, 1);
    PRINT_MAT_INT(dataBits, 10, 1);

    return 0;
}