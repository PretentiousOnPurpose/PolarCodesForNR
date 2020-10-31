#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"
#include <time.h>
#include <math.h>

int main() {
    
    srand(time(NULL));

    int * dataBits = (int *)calloc(8, sizeof(int));
    *(dataBits) = 1;
    *(dataBits + 1) = 1;
    *(dataBits + 2) = 1;
    *(dataBits + 3) = 1;
    *(dataBits + 4) = 0;
    *(dataBits + 5) = 0;
    *(dataBits + 6) = 0;
    *(dataBits + 7) = 0;
    
    double * modData = BPSK_MOD(dataBits, 8);
    double * rxData = AWGN(modData, 8, 0.1);
    double * rxLLR = BPSK_DEMOD(rxData, 8);

    PRINT_ARRAY_DOUBLE(rxLLR, 8);

    return 0;
}