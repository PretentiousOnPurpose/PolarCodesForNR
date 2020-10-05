#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int main() {

    srand(108);
    
    // Polar Code Config
    pcConfig.E = 144;
    pcConfig.K = 72;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 1;
    pcConfig.iIL = 0;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 11;
    pcConfig.crcPolyID = 5; 

    int remLen = 0;

    int * dataBits = DATA_GEN(pcConfig.K - pcConfig.crcLen);



    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
    PRINT_ARRAY_INT(dataBits, pcConfig.K - pcConfig.crcLen);

    PRINT_ARRAY_INT(crcData, pcConfig.K);
    return 0;
}