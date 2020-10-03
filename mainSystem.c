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
    pcConfig.crcLen = 11;
    pcConfig.crcPolyID = 5; 

    int remLen = 0;

    int p1[] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1};
    // int p1[] = {1, 1, 0, 0, 0, 0, 1, 0};
    int p2[] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1};
    // int p2[] = {1, 0, 0, 0, 1, 1, 1, 0, 1};
    int L1 = 8, L2 = 9;
    PRINT_ARRAY_INT(p1, L1);
    PRINT_ARRAY_INT(p2, L2);

    int * rem = poly_long_div(p1, p2, L1, L2, &remLen);

    PRINT_ARRAY_INT(rem, remLen);

    // int * dataBits = DATA_GEN(pcConfig.K - pcConfig.crcLen);

    // PRINT_ARRAY_INT(dataBits, 72);
    // printf("\n\n");

    // int * crcEncOut = NR_CRC_ENCODER(dataBits, &pcConfig);



    return 0;
}