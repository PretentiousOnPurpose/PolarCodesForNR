#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../src/polarCodes.h"

int main() {

    // srand(time(NULL));
    srand(192);
    
    int seqLen = 1000, iter_for, tmpVar;
    double rho[5] = {0.1, 0.2, 0.3, 0.4, 0.5};
    int * dataBits;
    int * rxData;


    for (iter_for = 0; iter_for < 5; iter_for++) {
        dataBits = ones(seqLen);
        rxData = BSC_Channel(modData, pcConfig.E, );      

        tmpVar = SUM_ARRAY_INT(rxData, seqLen);

        if (abs((double)tmpVar - rho * seqLen) < 0.05 * seqLen) {
            printf("Case %d: Success", iter_for);
        } else {
            printf("Case %d: Failed", iter_for);
        }
    }


    return 0;
}
