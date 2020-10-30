#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int * NR_PC_DECODER(int * rxLLR, struct PC_CONFIG * pcConfig) {
    int iter_bits;

    int * decData = (int *)calloc(pcConfig->N, sizeof(int));
    int * dataBits = (int *)calloc(pcConfig->K, sizeof(int));

    int * rel_seq = NR_PC_GET_REL_SEQ(pcConfig);

    if (pcConfig->decodingMethod == 1) {
        // Perform Successive Cancellation (SC) Decoding



    } else if (pcConfig->decodingMethod == 2) {
        // Perform SC List Decoding
    
    
    
    } else {
        // Perform Belief Propagation (BP) based List Decoding
    
    
    
    }

    // Extracting Data from Informatiom Bit Positions
    for (iter_bits = 0; iter_bits < pcConfig->K; iter_bits++) {
        *(dataBits + iter_bits) = *(decData + *(rel_seq + iter_bits));
    }

    free(decData);

    return dataBits;
}