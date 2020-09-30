#include <stdio.h>
#include "polarCodes.h"

int * DATA_GEN(int numBits) {
    int iter_bits;

    int * dataBits = (int *)malloc(sizeof(int) * numBits);

    for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
        *(dataBits + iter_bits) = rand() % 2;
    }

    return dataBits;
}

void PRINT_MAT_INT(int * dataBits, int numBits) {
    int iter_bits;
    
    for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
            printf("%d ", *(dataBits + iter_bits));
    }
    printf("\n");
  
}