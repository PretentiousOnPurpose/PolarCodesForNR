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
    pcConfig.crcPolyID = 2; 

    int p1[] = {1, 0, 0, 1, 0, 0, 1, 0, 1, 1};
    int p2[] = {1, 1, 0, 0, 0, 1};
    int L1 = 10, L2 = 6;

    int * rem = poly_long_div(p1, p2, L1, L2);

    PRINT_ARRAY_INT(rem, 5);

    return 0;
}