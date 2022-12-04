#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../headers/polarCodes.h"

int main() {

    srand(time(NULL));
    
    int seqLen = 1000, iter_for, tmpVar;
    double snr[7] = {-10, -5, 0, 5, 10};
    double * dataBits, * rxData, *noiseData;

    float tolerance = 0.5;
    double noiseVar, SNRdB;

    printf("CRC-aided Polar Codes for 5G NR\n\n");
    printf("Testing the AWGN Channel...\n\n");
    printf("The empirical SNR from the AWGN Channel is expected to be: SNR ± %0.2lf dB\n", tolerance);
    printf("Sequence length set to: %d bits\n\n", seqLen);

    for (iter_for = 0; iter_for < 5; iter_for++) {
        dataBits = ones_d(seqLen);
        rxData = AWGN(dataBits, seqLen, snr[iter_for]);      

        noiseData = subVectors_d(rxData, dataBits, seqLen);

        noiseVar = variance_d(noiseData, seqLen);

        SNRdB = 10 * log10(1 / (noiseVar));

        printf("Case %d: SNR: %0.2lf dB | empirical SNR (from simulated AWGN Channel): %0.2lf dB\n", iter_for, snr[iter_for], SNRdB);

        if (abs(SNRdB - snr[iter_for]) >= tolerance) {
            printf("Result: Case %d FAILED\n", iter_for);
        } else {
            printf("Result: Case %d PASSED\n", iter_for);
        }
    }

    return 0;
}
