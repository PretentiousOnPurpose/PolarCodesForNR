#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int main() {

    srand(110);
    
    // Polar Code Config
    pcConfig.E = 96;
    pcConfig.K = 9;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 1;
    pcConfig.iIL = 0;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 3;
    pcConfig.crcPolyID = 2; 

    int remLen = 0;

    // int dataBits[] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1};
    int dataBits[] = {1, 0, 0, 1, 0, 0};
    // int p2[] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1};
    // int p2[] = {1, 0, 0, 0, 1, 1, 1, 0, 1};

    int p2[] = {1, 1, 0, 1};

    int * crcEncOut = CRCGenerator(dataBits, p2, 6, 4);
    // int * crcEncOut = NR_CRC_ENCODER(dataBits, &pcConfig);

    PRINT_ARRAY_INT(crcEncOut, 3);


    return 0;
}