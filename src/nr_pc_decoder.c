#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/polarCodes.h"

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

double PC_LLR_TO_BIT(double rxLR) {
    return 1.0 * (rxLR <= 1.0) + 0.0 * (rxLR > 1.0);
}

void SC_DECODER(double * rxLR, int L, double ** rxBitsMat, int * rxLen, int * frozen_pos, struct PC_CONFIG * pcConfig) {
    int * rxBits = (int *)calloc(L, sizeof(int));
    double * rxLR_L = (double *)calloc(L/2, sizeof(double));
    double * rxLR_R = (double *)calloc(L/2, sizeof(double));

 
    for (int iter_lr = 0; iter_lr < L/2; iter_lr++) {
        *(rxLR_L + iter_lr) = PC_LikelihoodRatio_L(*(rxLR + iter_lr), *(rxLR + iter_lr + L/2));
        *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + iter_lr) = (*(rxLR_L + iter_lr));
    }

    if (L > 2) {
        SC_DECODER(rxLR_L, L/2, rxBitsMat, rxLen, frozen_pos, pcConfig);
    } else if (L == 2) {        
        if ((*(frozen_pos + *(rxLen + (int)log2(L/2))) == 1)) { 
            *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2))) = 0;
        } else {
            *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2))) = PC_LLR_TO_BIT(*(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2))));
        }
    }

    for (int iter_lr = 0; iter_lr < L/2; iter_lr++) {
        *(rxLR_R + iter_lr) = PC_LikelihoodRatio_R(*(rxLR + iter_lr), *(rxLR + iter_lr + L/2), *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + iter_lr));
        *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) + L/2 + iter_lr) = (*(rxLR_R + iter_lr));
    }
    
    *(rxLen + (int)log2(L/2)) = *(rxLen + (int)log2(L/2)) + L;
    
    if (L > 2) {        
        SC_DECODER(rxLR_R, L/2, rxBitsMat, rxLen, frozen_pos, pcConfig);
    } else {
        if ((*(frozen_pos + *(rxLen + (int)log2(L/2)) - L + 1) == 1)) { 
            *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) - L + 1) = 0;
        } else {
            *(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) - L + 1) = PC_LLR_TO_BIT(*(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) - L + 1));
        }
    }

    if (L < pow(2, pcConfig->n)) {
        for (int iter_lr = 0; iter_lr < L/2; iter_lr++) {
            *(*(rxBitsMat + (int)log2(L)) + *(rxLen + (int)log2(L/2)) - L + iter_lr) = (double)((int)(*(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) - L + iter_lr)) ^ (int)(*(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) - L + iter_lr + L/2)));
            *(*(rxBitsMat + (int)log2(L)) + *(rxLen + (int)log2(L/2)) - L + iter_lr + L/2) = (double)((int)(*(*(rxBitsMat + (int)log2(L/2)) + *(rxLen + (int)log2(L/2)) - L + iter_lr + L/2)));
        }
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

int * NR_PC_DECODER(double * rxLR, struct PC_CONFIG * pcConfig) {
    if (_DEBUG_ == 1) {
        printf("Peforming polar decoding...\n");
    }

    int iter_bits, iter_step;

    int * intrlvData = (int *)calloc(pcConfig->K, sizeof(int));
    int * dataBits = NULL;

    int * rel_seq = NR_PC_GET_REL_SEQ(pcConfig);
    int * frozen_pos = NR_PC_GET_FROZEN_POS(pcConfig);

    if (pcConfig->decodingMethod == 1) {
        double ** rxBitsMat = (double **)calloc(pcConfig->n, sizeof(double *));

        for (iter_step = 0; iter_step < pcConfig->n; iter_step++) {
            *(rxBitsMat + iter_step) = (double *)calloc(pcConfig->N, sizeof(double));
        }

        int * rxLen = (int *)calloc(pcConfig->n, sizeof(int));

        // Perform Successive Cancellation (SC) Decoding
        SC_DECODER(rxLR, pcConfig->N, rxBitsMat, rxLen, frozen_pos, pcConfig);

        // PRINT_MAT_DOUBLE(rxBitsMat, pcConfig->N, pcConfig->n);
        // exit(0);
        // Extracting Data from Informatiom Bit Positions
        for (iter_bits = 0; iter_bits < pcConfig->K; iter_bits++) {
            *(intrlvData + iter_bits) = (int)(*(*(rxBitsMat) + *(rel_seq + iter_bits)));
        }
        
        for (iter_step = 0; iter_step < pcConfig->n; iter_step++) {
            free(*(rxBitsMat + iter_step));
        }

        free(rxBitsMat);
        free(rxLen);

    } else if (pcConfig->decodingMethod == 2) {
        // CRC-aided Belief Propagation List Decoder
    } else if (pcConfig->decodingMethod == 3) {
        // CRC-aided Successive Cancellation List Decoder
    }

    dataBits = NR_PC_INPUT_BITS_INTERLEAVING(intrlvData, pcConfig, 1);

    return dataBits;
}
