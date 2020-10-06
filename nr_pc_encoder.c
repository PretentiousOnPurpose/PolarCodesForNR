// Performs 5G Polar Codes - Encoding
#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int REL_SEQ[] = {}; // 3GPP Release 15 TS 138 212 5G NR

int * NR_PC_ENCODER(int * dataBits, struct PC_CONFIG * pcConfig) {
    // For Iter Vars
    int iter_step, iter_bits, iter_group;

    // Set Frozen Bits and Placing Data bits in appropriate locations
    int * encData = PC_SET_DATABITS(encData, pcConfig);

    // Polar Transform - Encoding
    for (iter_step = 1; iter_step < pcConfig->nMax; iter_step++) {
        for (iter_group = 0; iter_group < (1 << (pcConfig->nMax - iter_step)); iter_group++) {
            for (iter_bits = 0; iter_bits < (1 << (iter_step - 1)); iter_bits++) {
                encData = POLAR_TRANSFORM(encData, iter_bits + iter_group * (1 << iter_step), iter_bits + iter_group * (1 << iter_step) + (1 << (iter_step - 1)));
            }
        }
    }

    return encData;
}

int * POLAR_TRANSFORM(int * dataBits, int ind1, int ind2) {
    *(dataBits + ind1) = *(dataBits + ind1) ^ *(dataBits + ind2);
    *(dataBits + ind2) = *(dataBits + ind2); // Redundant Step

    return dataBits;
}

int * PC_SET_DATABITS(int * dataBits, struct PC_CONFIG * pcConfig) {
    int iter_bits;
    int * encData = (int *)calloc(1 << pcConfig->nMax, sizeof(int));

    for (iter_bits = 0; iter_bits < pcConfig->K; iter_bits++) {
        *(encData + REL_SEQ[iter_bits]) = *(dataBits + iter_bits);
    }  

    return encData;
}