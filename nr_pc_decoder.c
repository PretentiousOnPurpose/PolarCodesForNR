#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polarCodes.h"
double PC_LikelihoodRatio_L(double x1, double x2) {    
    double LR = (1 + x1 * x2) / (x1 + x2);
	
    if (LR == 0) {
        LR = 0.01;
    }

    if (LR > 10) {
        LR = 10;
    }

    return LR;
}

double PC_LikelihoodRatio_R(double x1, double x2, int bit) {
    double LR = ((pow(x1, 1 - 2 * bit)) * x2);

    if (LR == 0) {
        LR = 0.01;
    }

    if (LR > 10) {
        LR = 10;
    }

    return LR;
}

int PC_LLR_TO_BIT(double rxLR) {
    return 1 * (rxLR <= 1.0) + 0 * (rxLR > 1.0);
}

// Need an optimized version using Intel Intrinsics (AVX2/SSE 4.1 or 4.2)
void SC_DECODER(double * rxLR, int L, int ** rxBitsMat, int * rxLen, int * frozen_pos) {
    int iter_lr;
    int * rxBits = (int *)calloc(L, sizeof(int));

    double * rxLR_L = (double *)calloc(L/2, sizeof(double));
    double * rxLR_R = (double *)calloc(L/2, sizeof(double));

    for (iter_lr = 0; iter_lr < L/2; iter_lr++) {
        *(rxLR_L + iter_lr) = PC_LikelihoodRatio_L(*(rxLR + iter_lr), *(rxLR + iter_lr + L/2));
        *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + iter_lr) = PC_LLR_TO_BIT(*(rxLR_L + iter_lr));
        
        if ((L == 2) && (*(frozen_pos + *(rxLen + (int)log2(L/2)) + iter_lr) == 1)) { 
            *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + iter_lr) = 0;
        }

    }

    if (L > 2) {
        SC_DECODER(rxLR_L, L/2, rxBitsMat, rxLen, frozen_pos);
    }

    for (iter_lr = 0; iter_lr < L/2; iter_lr++) {
        *(rxLR_R + iter_lr) = PC_LikelihoodRatio_R(*(rxLR + iter_lr), *(rxLR + iter_lr + L/2), *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + iter_lr));
        *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + L/2 + iter_lr) = PC_LLR_TO_BIT(*(rxLR_R + iter_lr));

        if ((L == 2) && (*(frozen_pos + *(rxLen + (int)log2(L/2)) + L/2 + iter_lr) == 1)) { 
            *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + L/2 + iter_lr) = 0;
        }

    }

    *(rxLen + (int)log2(L/2)) = *(rxLen + (int)log2(L/2)) + L;

    if (L > 2) {
        SC_DECODER(rxLR_R, L/2, rxBitsMat, rxLen, frozen_pos);
    }
    
    free(rxLR_L);
    free(rxLR_R);
}

double * LR_TO_PROB(double * rxLR, int L) {
    int iter_LR;

    double * rxProb = (double *)calloc(L, sizeof(double));

    for (iter_LR = 0; iter_LR < L; iter_LR++) {
        if (*(rxLR + iter_LR) < 0) {
            *(rxProb + iter_LR) = *(rxLR + iter_LR) / (-4);
        } else if (*(rxLR + iter_LR) > 0) {
            *(rxProb + iter_LR) = 1 - *(rxLR + iter_LR) / 4;
        } else {
            *(rxProb + iter_LR) = rand() % 2;
        }
    }

    return rxProb;
}

double PROB_A_B_EQ(double P1, double P2) {
    double P_1 = P1 * P2;
    P_1 = P_1 / (P_1 + ((1 - P1) * (1 - P2)));

    return P_1;
}

double PROB_A_B_XOR(double P1, double P2) {
    double P_1 = ((1 - P1) * P2 + P1 * (1 - P2));
    P_1 = P_1 / (P_1 + (P1 * P2 + (1 - P1) * (1 - P2)));

    return P_1;
}

void BP_ProcessUnit(double ** rxBeliefsMat, int currStep, int ind1, int ind2, int * frozen_pos) {
    *(*(rxBeliefsMat + currStep - 1) + ind1) = PROB_A_B_XOR(*(*(rxBeliefsMat + currStep) + ind1), PROB_A_B_EQ(*(*(rxBeliefsMat + currStep) + ind2), *(*(rxBeliefsMat + currStep - 1) + ind2)));
    *(*(rxBeliefsMat + currStep - 1) + ind2) = (*(*(rxBeliefsMat + currStep) + ind2));

    if (*(frozen_pos + ind1) && currStep == 1) {
        *(*(rxBeliefsMat + currStep - 1) + ind1) = 0;
    }

    if (*(frozen_pos + ind2) && currStep == 1) {
        *(*(rxBeliefsMat + currStep - 1) + ind2) = 0;
    }

}

// Need an optimized version using Intel Intrinsics (AVX2/SSE 4.1 or 4.2)
void BP_DECODER(double ** rxBeliefsMat, int L, int * frozen_pos, int iter_BP) {
    int iter, iter_step, iter_group, iter_LR, n = (int)log2(L);

    for (iter = 0; iter < iter_BP; iter++) {
        // Backward Message Passing
        for (iter_step = n; iter_step >= 1; iter_step--) {
            for (iter_group = 0; iter_group < (1 << (n - iter_step)); iter_group++) {
                for (iter_LR = 0; iter_LR < (1 << (iter_step - 1)); iter_LR++) {
                    BP_ProcessUnit(rxBeliefsMat, iter_step, iter_LR + iter_group * (1 << iter_step), iter_LR + iter_group * (1 << iter_step) + (1 << (iter_step - 1)), frozen_pos);
                }
            }
        }
    }
}


int * NR_PC_DECODER(double * rxLR, struct PC_CONFIG * pcConfig) {
    int iter_bits, iter_step;

    int * intrlvData = (int *)calloc(pcConfig->K, sizeof(int));
    int * dataBits = NULL;

    int * rel_seq = NR_PC_GET_REL_SEQ(pcConfig);
    int * frozen_pos = NR_PC_GET_FROZEN_POS(pcConfig);

    if (pcConfig->decodingMethod == 1) {
        int ** rxBitsMat = (int **)calloc(pcConfig->n, sizeof(int));

        for (iter_step = 0; iter_step < pcConfig->n; iter_step++) {
            *(rxBitsMat + iter_step) = (int *)calloc(pcConfig->N, sizeof(int));
        }

        int * rxLen = (int *)calloc(pcConfig->n, sizeof(int));

        // Perform Successive Cancellation (SC) Decoding
        SC_DECODER(rxLR, pcConfig->N, rxBitsMat, rxLen, frozen_pos);

        for (iter_step = 0; iter_step < pcConfig->n; iter_step++) {
            free(*(rxBitsMat + iter_step));
        }

        // Extracting Data from Informatiom Bit Positions
        for (iter_bits = 0; iter_bits < pcConfig->K; iter_bits++) {
            *(intrlvData + iter_bits) = *(*(rxBitsMat) + *(rel_seq + iter_bits));
        }

        free(rxBitsMat);
        free(rxLen);

    } else if (pcConfig->decodingMethod == 2) {
        // Perform SC List Decoding
        // decData = SCL_DECODER(rxLR, pcConfig);
    } else {
        double ** rxBeliefsMat = (double **)calloc(pcConfig->n + 1, sizeof(double));

        for (iter_step = 0; iter_step < pcConfig->n; iter_step++) {
            *(rxBeliefsMat + iter_step) = (double *)calloc(pcConfig->N, sizeof(double));

            for (iter_bits = 0; iter_bits < pcConfig->N; iter_bits++) {
                *(*(rxBeliefsMat + iter_step) + iter_bits) = 1.0;
            }
        }

        *(rxBeliefsMat + pcConfig->n) = rxLR;

        // Perform Belief Propagation (BP) based List Decoding
        BP_DECODER(rxBeliefsMat, pcConfig->N, frozen_pos, pcConfig->iter_BP);

        // Extracting Data from Informatiom Bit Positions
        for (iter_bits = 0; iter_bits < pcConfig->K; iter_bits++) {
            if (*(*(rxBeliefsMat) + *(rel_seq + iter_bits)) >= 0.5) {
                *(intrlvData + iter_bits) = 1;
            }
        }
        
        for (iter_step = 0; iter_step < pcConfig->n + 1; iter_step++) {
            free(*(rxBeliefsMat + iter_step));
        }

        free(rxBeliefsMat);
    }

    dataBits = NR_PC_INPUT_BITS_INTERLEAVING(intrlvData, pcConfig, 1);

    return dataBits;
}
