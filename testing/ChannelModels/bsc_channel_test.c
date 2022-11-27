#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../headers/polarCodes.h"

int main() {

    srand(time(NULL));
    
    int seqLen = 10000, iter_for, tmpVar;
    double rho[5] = {0.1, 0.3, 0.5};
    int * dataBits;
    int * rxData;

    float tolerance = 0.05;
    double diff;

    printf("Tolerance setting for the BSC Channel: %f\n", tolerance * seqLen);
    printf("Sequence length set to: %d bits\n", seqLen);

    for (iter_for = 0; iter_for < 3; iter_for++) {
        dataBits = ones(seqLen);
        rxData = BSC_Channel(dataBits, seqLen, rho[iter_for]);      

        tmpVar = SUM_ARRAY_INT(rxData, seqLen);


        diff = abs((double)tmpVar - (1 - rho[iter_for]) * seqLen);

        printf("Case %d: rho: %0.2lf | Number of unflipped bits: %d | abs. diff: %0.1lf\n", iter_for, rho[iter_for], tmpVar, diff);
        if (diff >= tolerance * seqLen) {
            printf("Result: Case %d FAILED\n", iter_for);
        } else {
            printf("Result: Case %d PASSED\n", iter_for);
        }
    }


    return 0;
}
