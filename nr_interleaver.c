#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int INPUT_INTERLEAVE_PATTERN[] = {0, 2, 4, 7, 9, 14, 19, 20, 24, 25, 26, 28, 31, 34, 42, 45, 49, 50, 51, 53, 54, 56, 58, 59, 61, 62, 65, 66, 67, 69, 70, 71, 72, 76, 77, 81, 82, 83, 87, 88, 89, 91, 93, 95, 98, 101, 104, 106, 108, 110, 111, 113, 115, 118, 119, 120, 122, 123, 126, 127, 129, 132, 134, 138, 139, 140, 1, 3, 5, 8, 10, 15, 21, 27, 29, 32, 35, 43, 46, 52, 55, 57, 60, 63, 68, 73, 78, 84, 90, 92, 94, 96, 99, 102, 105, 107, 109, 112, 114, 116, 121, 124, 128, 130, 133, 135, 141, 6, 11, 16, 22, 30, 33, 36, 44, 47, 64, 74, 79, 85, 97, 100, 103, 117, 125, 131, 136, 142, 12, 17, 23, 37, 48, 75, 80, 86, 137, 143, 13, 18, 38, 144, 39, 145, 40, 146, 41, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163};

int * NR_PC_CODED_BITS_INTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig) {
    int * intrlvData = (int *)calloc(pcConfig->E, sizeof(int));
    int cnt, E = pcConfig->E;
    int T = QUAD_EQN_SOL(1, 1, -2 * pcConfig->E);

    int ** intrlvMat = (int **)calloc(T, sizeof(int));

    for (int iter_bits = 0; iter_bits < T; iter_bits++) {
        *(intrlvMat + iter_bits) = (int *)calloc(T, sizeof(int));
    }

    if (pcConfig->iBIL) {
        cnt = 0;

        for (int iter_row = 0; iter_row < T; iter_row++) {
            for (int iter_col = 0; iter_col < T-iter_row; iter_col++) {
                if (cnt < E) {
                    *(*(intrlvMat + iter_row) + iter_col) = *(dataBits + cnt);
                } else {
                    *(*(intrlvMat + iter_row) + iter_col) = -1;
                }
                cnt++;
            }
        }

        cnt = 0;

        for (int iter_col = 0; iter_col < T; iter_col++) {
            for (int iter_row = 0; iter_row < T-iter_col; iter_row++) {
                if (*(*(intrlvMat + iter_row) + iter_col) > 0) {
                    *(intrlvData + cnt) = *(*(intrlvMat + iter_row) + iter_col);
                    cnt++;
                }
            }
        }

    } else {
        for (int iter_bits = 0; iter_bits < pcConfig->E; iter_bits++) {
            *(intrlvData + iter_bits) = *(dataBits + iter_bits);
        }
    }

    for (int iter_bits = 0; iter_bits < T; iter_bits++) {
        free(*(intrlvMat + iter_bits));
    }

    free(intrlvMat);

    return intrlvData;
}

int * NR_PC_CODED_BITS_DEINTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig) {
    int * dataOut = (int *)calloc(pcConfig->E, sizeof(int));
    int iter_bits1, iter_bits2, iter_bits3;
    
    int T = QUAD_EQN_SOL(1, 1, -2 * pcConfig->E);

    int ** intrlvMat = (int **)calloc(T, sizeof(int));

    for (iter_bits2 = 0; iter_bits2 < T; iter_bits2++) {
        *(intrlvMat + iter_bits2) = (int *)calloc(T, sizeof(int));
    }

    iter_bits1 = 0;

    if (pcConfig->iBIL) {
        for (iter_bits2 = 0; iter_bits2 < T; iter_bits2++) {
            for (iter_bits3 = 0; iter_bits3 < T - iter_bits2; iter_bits3++) {
                if (iter_bits1 < pcConfig->E) {
                    *(*(intrlvMat + iter_bits2) + iter_bits3) = 1;
                    iter_bits1++;
                } else {
                    *(*(intrlvMat + iter_bits2) + iter_bits3) = -1;
                }
            }
        }

        iter_bits1 = 0;

        for (iter_bits3 = 0; iter_bits3 < T; iter_bits3++) {
            for (iter_bits2 = 0; iter_bits2 < T - iter_bits3; iter_bits2++) {                
                if (*(*(intrlvMat + iter_bits2) + iter_bits3) != -1) {
                    *(*(intrlvMat + iter_bits2) + iter_bits3) = *(dataBits + iter_bits1);
                    iter_bits1++;
                }
            }
        }

        iter_bits1 = 0;

        for (iter_bits2 = 0; iter_bits2 < T; iter_bits2++) {
            for (iter_bits3 = 0; iter_bits3 < T - iter_bits2; iter_bits3++) {
                if (*(*(intrlvMat + iter_bits2) + iter_bits3) != -1) {
                    *(dataOut + iter_bits1) = *(*(intrlvMat + iter_bits2) + iter_bits3);
                    iter_bits1++;
                }
            }
        }

    } else {
        for (iter_bits1 = 0; iter_bits1 < pcConfig->E; iter_bits1++) {
            *(dataOut + iter_bits1) = *(dataBits + iter_bits1);
        }
    }

    for (iter_bits2 = 0; iter_bits2 < T; iter_bits2++) {
        free(*(intrlvMat + iter_bits2));
    }

    free(intrlvMat);

    return dataOut;
}

int * NR_PC_INPUT_BITS_INTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig, int FWD_BWD) {
    int * dataOut = (int *)calloc(pcConfig->K, sizeof(int));
    int iter_bits1 = 0, iter_bits2;
    
    if (pcConfig->iIL) {
        for (iter_bits2 = 0; iter_bits2 < pcConfig->K_IL_MAX; iter_bits2++) {
            if (*(INPUT_INTERLEAVE_PATTERN + iter_bits2) >= pcConfig->K_IL_MAX - pcConfig->K) {
                if (FWD_BWD == 0) {
                    *(dataOut + iter_bits1) = *(dataBits + *(INPUT_INTERLEAVE_PATTERN + iter_bits2) - (pcConfig->K_IL_MAX - pcConfig->K));
                } else {
                    *(dataOut + *(INPUT_INTERLEAVE_PATTERN + iter_bits2) - (pcConfig->K_IL_MAX - pcConfig->K)) = *(dataBits + iter_bits1);
                }

                iter_bits1++;
            }
        }
    } else {
        for (iter_bits1 = 0; iter_bits1 < pcConfig->K; iter_bits1++) {
            *(dataOut + iter_bits1) = *(dataBits + iter_bits1);
        }
    }

    free(dataBits);
    // exit(0);
    return dataOut;
}
