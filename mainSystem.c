#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int main() {

    srand(108);
    
    // Polar Code Config
    pcConfig.E = 192;
    pcConfig.K = 14;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 1;
    pcConfig.iIL = 0;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 5;
    pcConfig.crcPolyID = 2; 

    int p1[] = {1, 1, 0, 0, 1, 1, 0, 0, 1};
    int p2[] = {1, 0, 1, 0, 1, 1};

    printf("DE: %d\n", degree_poly(p1, 9));
    printf("DE: %d\n", degree_poly(p2, 6));

    int * rem = poly_long_div(p1, p2, 9, 6);
    PRINT_ARRAY_INT(rem, 9);

    return 0;
}