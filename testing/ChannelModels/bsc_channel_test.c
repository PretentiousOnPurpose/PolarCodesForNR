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

    printf("Testing the Binary Symmetric Channel...\n\n");
    printf("The empirical rho from the BSC Channel is expected to be: rho ± %0.2lf\n", tolerance);
    printf("Sequence length set to: %d bits\n\n", seqLen);

    for (iter_for = 0; iter_for < 3; iter_for++) {
        dataBits = ones(seqLen);
        rxData = BSC_Channel(dataBits, seqLen, rho[iter_for]);      

        tmpVar = SUM_ARRAY_INT(rxData, seqLen);


        diff = abs((double)tmpVar - (1 - rho[iter_for]) * seqLen);

        printf("Case %d: rho: %0.2lf | empirical rho (from simulated BSC Channel): %0.2lf\n", iter_for, rho[iter_for], 1 - ((double)tmpVar / seqLen));

        if (diff >= tolerance * seqLen) {
            printf("Result: Case %d FAILED\n", iter_for);
        } else {
            printf("Result: Case %d PASSED\n", iter_for);
        }
    }


    return 0;
}
