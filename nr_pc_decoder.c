#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polarCodes.h"

double PC_LikelihoodRatio_L(double x1, double x2) {    
    return (1 + x1 * x2) / (x1 + x2);
}

double PC_LikelihoodRatio_R(double x1, double x2, int bit) {
    return ((pow(x1, 1 - 2 * bit)) * x2);
}

int PC_LLR_TO_BIT(double rxLLR) {
    return 1 * (rxLLR <= 1.0) + 0 * (rxLLR > 1.0);
}

void SC_DECODER(double * rxLLR, int L, int ** rxBitsMat, int * rxLen) {
    int iter_llr;
    int * rxBits = (int *)calloc(L, sizeof(int));

        double * rxLLR_L = (double *)calloc(L/2, sizeof(double));
        double * rxLLR_R = (double *)calloc(L/2, sizeof(double));

        for (iter_llr = 0; iter_llr < L/2; iter_llr++) {
            *(rxLLR_L + iter_llr) = PC_LikelihoodRatio_L(*(rxLLR + iter_llr), *(rxLLR + iter_llr + L/2));
            *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + iter_llr) = PC_LLR_TO_BIT(*(rxLLR_L + iter_llr));
		}
		
        PRINT_ARRAY_DOUBLE(rxLLR, L);
		PRINT_ARRAY_DOUBLE(rxLLR_L, L/2);
        PRINT_MAT_INT(rxBitsMat, 8, 3);
        printf("----------------------\n");
        
		if (L > 2) {
			SC_DECODER(rxLLR_L, L/2, rxBitsMat, rxLen);
		}
		
        for (iter_llr = 0; iter_llr < L/2; iter_llr++) {
            *(rxLLR_R + iter_llr) = PC_LikelihoodRatio_R(*(rxLLR + iter_llr), *(rxLLR + iter_llr + L/2), *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + iter_llr));
            *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + L/2 + iter_llr) = PC_LLR_TO_BIT(*(rxLLR_R + iter_llr));
			PRINT_MAT_INT(rxBitsMat, 8, 3);
        }
		
		*(rxLen + (int)log2(L/2)) = *(rxLen + (int)log2(L/2)) + L/2;
		
		PRINT_ARRAY_DOUBLE(rxLLR, L);
		PRINT_ARRAY_DOUBLE(rxLLR_R, L/2);
        PRINT_MAT_INT(rxBitsMat, 8, 3);
        printf("----------------------\n");

		if (L > 2) {
			SC_DECODER(rxLLR_R, L/2, rxBitsMat, rxLen);
		}

        free(rxLLR_L);
        free(rxLLR_R);

}

int * NR_PC_DECODER(double * rxLLR, struct PC_CONFIG * pcConfig) {
    int iter_bits, iter_group1, iter_group2, iter_step;

    int * decData = (int *)calloc(pcConfig->N, sizeof(int));
    int * dataBits = (int *)calloc(pcConfig->K, sizeof(int));

    int * rel_seq = NR_PC_GET_REL_SEQ(pcConfig);

    if (pcConfig->decodingMethod == 1) {
        // Perform Successive Cancellation (SC) Decoding
        // decData = SC_DECODER(rxLLR, pcConfig->N);
    } else if (pcConfig->decodingMethod == 2) {
        // Perform SC List Decoding
        // decData = SCL_DECODER(rxLLR, pcConfig);
    } else {
        // Perform Belief Propagation (BP) based List Decoding
        // decData = BP_DECODER(rxLLR, pcConfig);    
    }

    // Extracting Data from Informatiom Bit Positions
    for (iter_bits = 0; iter_bits < pcConfig->K; iter_bits++) {
        *(dataBits + iter_bits) = *(decData + *(rel_seq + iter_bits));
    }

    free(decData);

    return dataBits;
}