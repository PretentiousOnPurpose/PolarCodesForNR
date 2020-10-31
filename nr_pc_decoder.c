#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polarCodes.h"

double PC_LikelihoodRatio_L(double x1, double x2) {
    return (x1 + x2) / (1 + x1 * x2);
}

double PC_LikelihoodRatio_R(double x1, double x2, int bit) {
    return ((pow(x1, 1 - 2 * bit)) * x2);
}

int * SC_DECODER(double * rxLLR, int L, struct PC_CONFIG * pcConfig, int * RX_BITS_L) {
    int iter_llr;
    int * rxBits = (int *)calloc(L, sizeof(int));

    if (L == 1) {
        *rxBits = 1 * (*rxLLR < 1.0) + 0 * (*rxLLR >= 1.0);
    } else {
        double * rxLLR_L = (double *)calloc(L/2, sizeof(double));
        double * rxLLR_R = (double *)calloc(L/2, sizeof(double));
        int * rxBits_L, * rxBits_R;

        for (iter_llr = 0; iter_llr < L/2; iter_llr++) {
            *(rxLLR_L + iter_llr) = PC_LikelihoodRatio_L(*(rxLLR + iter_llr), *(rxLLR + iter_llr + L/2));
        }

        rxBits_L = SC_DECODER(rxLLR_L, L/2, pcConfig, NULL);

        for (iter_llr = 0; iter_llr < L/2; iter_llr++) {
            *(rxLLR_R + iter_llr) = PC_LikelihoodRatio_R(*(rxLLR + iter_llr), *(rxLLR + iter_llr + L/2), *(rxBits_L + iter_llr));
        }

        rxBits_R = SC_DECODER(rxLLR_R, L/2, pcConfig, rxBits_L);

        for (iter_llr = 0; iter_llr < L; iter_llr++) {
            *(rxBits + iter_llr) = (iter_llr < L/2) * (*(rxBits_L + iter_llr)) + (iter_llr >= L/2) * (*(rxBits_R + iter_llr));
        }

        free(rxLLR_L);
        free(rxLLR_R);
    }
    return rxBits;
}

int * NR_PC_DECODER(int * rxLLR, struct PC_CONFIG * pcConfig) {
    int iter_bits, iter_group1, iter_group2, iter_step;

    int * decData = (int *)calloc(pcConfig->N, sizeof(int));
    int * dataBits = (int *)calloc(pcConfig->K, sizeof(int));

    int * rel_seq = NR_PC_GET_REL_SEQ(pcConfig);

    if (pcConfig->decodingMethod == 1) {
        // Perform Successive Cancellation (SC) Decoding
        decData = SC_DECODER(rxLLR, pcConfig->N, pcConfig);
    } else if (pcConfig->decodingMethod == 2) {
        // Perform SC List Decoding
        decData = SCL_DECODER(rxLLR, pcConfig);
    } else {
        // Perform Belief Propagation (BP) based List Decoding
        decData = BP_DECODER(rxLLR, pcConfig);    
    }

    // Extracting Data from Informatiom Bit Positions
    for (iter_bits = 0; iter_bits < pcConfig->K; iter_bits++) {
        *(dataBits + iter_bits) = *(decData + *(rel_seq + iter_bits));
    }

    free(decData);

    return dataBits;
}