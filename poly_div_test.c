#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"
#include <time.h>
#include <math.h>

int main() {
    double * rxLLR = (double *)calloc(8, sizeof(double));

    *(rxLLR) = 10;
    *(rxLLR + 1) = 10;
    *(rxLLR + 2) = 0.01;
    *(rxLLR + 3) = 0.01;
    *(rxLLR + 4) = 0.01;
    *(rxLLR + 5) = 10;
    *(rxLLR + 6) = 10;
    *(rxLLR + 7) = 10;

	int ** rxBitsMat = (int **)calloc(3, sizeof(int));
	int * rxLen = (int *)calloc(3, sizeof(int));

    *(rxBitsMat) = (int *)calloc(8, sizeof(int));
    *(rxBitsMat + 1) = (int *)calloc(8, sizeof(int));
    *(rxBitsMat + 2) = (int *)calloc(8, sizeof(int));

    // PRINT_MAT_INT(rxBitsMat, 8, 3);

    SC_DECODER(rxLLR, 8, rxBitsMat, rxLen);

    // PRINT_ARRAY_INT(*(rxBitsMat), 8);

    return 0;
}