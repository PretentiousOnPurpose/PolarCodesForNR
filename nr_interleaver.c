#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int INPUT_INTERLEAVE_PATTERN[] = {};

int * NR_PC_CODED_BITS_INTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig) {
    int * dataOut = (int *)calloc(pcConfig->K, sizeof(int));
    int iter_bits1 = 0, iter_bits2, iter_bits3;
    
    int T = QUAD_EQN_SOL(1, 1, -2 * pcConfig->E);

    int ** intrlvMat = (int **)calloc(T, sizeof(int));

    for (iter_bits2 = 0; iter_bits2 < t; iter_bits2++) {
        *(intrlvMat + iter_bits) = (int *)calloc(T, sizeof(int));
    }

    if (pcConfig->iBIL) {
        for (iter_bits2 = 0; iter_bits2 < T; iter_bits2++) {
            for (iter_bits3 = 0; iter_bits3 < T - iter_bits2; iter_bits3++) {
                if (iter_bits1 < pcConfig->E) {
                    intrlvMat(iter_bits2 * T + iter_bits3) = *(dataBits + iter_bits1);
                } else {
                    intrlvMat(iter_bits2 * T + iter_bits3) = -1;
                }

                iter_bits1++;
            }
        }

        iter_bits1 = 0;

        for (iter_bits3 = 0; iter_bits3 < T; iter_bits3++) {
            for (iter_bits2 = 0; iter_bits2 < T - iter_bits3; iter_bits2++) {
                if (intrlvMat(iter_bits2 * T + iter_bits3) != -1) {
                    *(dataOut + iter_bits1) = intrlvMat(iter_bits2 * T + iter_bits3);
                    iter_bits1++;
                }
            }
        }

    } else {
        for (iter_bits1 = 0; iter_bits1 < pcConfig->E; iter_bits1++) {
            *(dataOut + iter_bits1) = *(dataBits + iter_bits1);
        }
    }

    free(dataBits);

    return dataOut;
}

// int * NR_PC_CODED_BITS_DEINTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig) {
//     int * dataOut = (int *)calloc(pcConfig->K, sizeof(int));
//     int iter_bits1 = 0, iter_bits2, iter_bits3;
    
//     int T = QUAD_EQN_SOL(1, 1, -2 * pcConfig->E);

//     int ** intrlvMat = (int **)calloc(T, sizeof(int));

//     for (iter_bits2 = 0; iter_bits2 < t; iter_bits2++) {
//         *(intrlvMat + iter_bits) = (int *)calloc(T, sizeof(int));
//     }

//     if (pcConfig->iBIL) {
//         for (iter_bits3 = 0; iter_bits3 < T; iter_bits3++) {
//             for (iter_bits2 = 0; iter_bits2 < T - iter_bits3; iter_bits2++) {
//                 if (intrlvMat(iter_bits2 * T + iter_bits3) != -1) {
//                     *(dataOut + iter_bits1) = intrlvMat(iter_bits2 * T + iter_bits3);
//                     iter_bits1++;
//                 }
//             }
//         }

//         iter_bits1 = 0;

//         for (iter_bits2 = 0; iter_bits2 < T; iter_bits2++) {
//             for (iter_bits3 = 0; iter_bits3 < T - iter_bits2; iter_bits3++) {
//                 if (iter_bits1 < pcConfig->E) {
//                     intrlvMat(iter_bits2 * T + iter_bits3) = *(dataBits + iter_bits1);
//                 } else {
//                     intrlvMat(iter_bits2 * T + iter_bits3) = -1;
//                 }

//                 iter_bits1++;
//             }
//         }
//     } else {
//         for (iter_bits1 = 0; iter_bits1 < pcConfig->E; iter_bits1++) {
//             *(dataOut + iter_bits1) = *(dataBits + iter_bits1);
//         }
//     }

//     free(dataBits);

//     return dataOut;
// }


int * NR_PC_INPUT_BITS_INTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig, int FWD_BWD) {
    int * dataOut = (int *)calloc(pcConfig->K, sizeof(int));
    int iter_bits1 = 0, iter_bits2;
    
    if (pcConfig->iIL) {
        for (iter_bits2 = 0; iter_bits2 < pcConfig->K_IL_MAX; iter_bits2++) {
            if (*(INPUT_INTERLEAVE_PATTERN + iter_bits2) >= pcConfig->K_IL_MAX - pcConfig->K) {
                if (FWD_BWD == 0) {
                    *(dataOut + iter_bits1) = *(dataBits + *(INPUT_INTERLEAVE_PATTERN + iter_bits2) - (pcConfig->K_IL_MAX - pcConfig->K));
                } else {
                    *(dataBits + *(INPUT_INTERLEAVE_PATTERN + iter_bits2) - (pcConfig->K_IL_MAX - pcConfig->K)) = *(dataOut + iter_bits1);
                }

                iter_bits1++;
            }
        }
    } else {
        for (iter_bits1 = 0; iter_bits1 < pcConfig->K; iter_bits1++) {
            if (FWD_BWD == 0) {
                *(dataOut + iter_bits1) = *(dataBits + iter_bits1);
            } else {
                *(dataBits + iter_bits1) = *(dataOut + iter_bits1);
            }
        }
    }

    free(dataBits);

    return dataOut;
}
