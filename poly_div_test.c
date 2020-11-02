#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"
#include <time.h>
#include <math.h>

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
    pcConfig.decodingMethod = 1;

    int err = 0;

    int * dataBits = DATA_GEN(61);
    int CRC11[] = {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    int * encData = NR_CRC_ENCODER(dataBits, &pcConfig);

    int * rem =

    PRINT_ARRAY_INT(dataBits, 61);
    PRINT_ARRAY_INT(encData, 72);

    return 0;
}