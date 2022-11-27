#include <stdio.h>
#include <stdlib.h>
#include "../headers/polarCodes.h"

int INPUT_INTERLEAVE_PATTERN[] = {0, 2, 4, 7, 9, 14, 19, 20, 24, 25, 26, 28, 31, 34, 42, 45, 49, 50, 51, 53, 54, 56, 58, 59, 61, 62, 65, 66, 67, 69, 70, 71, 72, 76, 77, 81, 82, 83, 87, 88, 89, 91, 93, 95, 98, 101, 104, 106, 108, 110, 111, 113, 115, 118, 119, 120, 122, 123, 126, 127, 129, 132, 134, 138, 139, 140, 1, 3, 5, 8, 10, 15, 21, 27, 29, 32, 35, 43, 46, 52, 55, 57, 60, 63, 68, 73, 78, 84, 90, 92, 94, 96, 99, 102, 105, 107, 109, 112, 114, 116, 121, 124, 128, 130, 133, 135, 141, 6, 11, 16, 22, 30, 33, 36, 44, 47, 64, 74, 79, 85, 97, 100, 103, 117, 125, 131, 136, 142, 12, 17, 23, 37, 48, 75, 80, 86, 137, 143, 13, 18, 38, 144, 39, 145, 40, 146, 41, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163};

int * NR_PC_CODED_BITS_INTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig) {
    int * intrlvData = (int *)calloc(pcConfig->E, sizeof(int));
    int cnt, E = pcConfig->E;
    int T = QUAD_EQN_SOL(1, 1, -2 * pcConfig->E);

    int ** intrlvMat = (int **)calloc(T, sizeof(int *));

    for (int iter_rows = 0; iter_rows < T; iter_rows++) {
        *(intrlvMat + iter_rows) = (int *)calloc(T, sizeof(int));

        for (int iter_cols = 0; iter_cols < T; iter_cols++) {
            *(*(intrlvMat + iter_rows) + iter_cols) = -1;
        }
    }

    if (pcConfig->iBIL == 1) {
        if (_DEBUG_ == 1) {
            printf("\tPeforming coded bit interleaving...\n");
        }

        cnt = 0;

        for (int iter_rows = 0; iter_rows < T; iter_rows++) {
            for (int iter_cols = 0; iter_cols < T-iter_rows; iter_cols++) {
                if (cnt < E) {
                    *(*(intrlvMat + iter_cols) + iter_rows) = *(dataBits + cnt);
                }
                cnt++;
            }
        }

        cnt = 0;

        for (int iter_cols = 0; iter_cols < T; iter_cols++) {
            for (int iter_rows = 0; iter_rows < T-iter_cols; iter_rows++) {
                if (*(*(intrlvMat + iter_cols) + iter_rows) >= 0) {
                    *(intrlvData + cnt) = *(*(intrlvMat + iter_cols) + iter_rows);
                    cnt++;
                }
            }
        }

    } else {
        for (int iter_bits = 0; iter_bits < pcConfig->E; iter_bits++) {
            *(intrlvData + iter_bits) = *(dataBits + iter_bits);
        }
    }

    for (int iter_rows = 0; iter_rows < T; iter_rows++) {
        free(*(intrlvMat + iter_rows));
    }

    free(intrlvMat);

    return intrlvData;
}

double * NR_PC_CODED_BITS_DEINTERLEAVING(double * dataBits, struct PC_CONFIG * pcConfig) {
    double * deintrlvData = (double *)calloc(pcConfig->E, sizeof(double));
    int cnt, E = pcConfig->E;
    int T = QUAD_EQN_SOL(1, 1, -2 * pcConfig->E);

    double ** deintrlvMat = (double **)calloc(T, sizeof(double *));

    for (int iter_rows = 0; iter_rows < T; iter_rows++) {
        *(deintrlvMat + iter_rows) = (double *)calloc(T, sizeof(double));
        
        for (int iter_cols = 0; iter_cols < T; iter_cols++) {
            *(*(deintrlvMat + iter_rows) + iter_cols) = -1;
        }
    }

    cnt = 0;

    for (int iter_rows = 0; iter_rows < T; iter_rows++) {
        for (int iter_cols = 0; iter_cols < T-iter_rows; iter_cols++) {
            if (cnt < E) {
                *(*(deintrlvMat + iter_cols) + iter_rows) = -2;
            }
            cnt++;
        }
    }

    if (pcConfig->iBIL == 1) {
        if (_DEBUG_ == 1) {
            printf("\tPeforming coded bit deinterleaving...\n");
        }
        cnt = 0;

        for (int iter_rows = 0; iter_rows < T; iter_rows++) {
            for (int iter_cols = 0; iter_cols < T-iter_rows; iter_cols++) {
                if (cnt < E && (*(*(deintrlvMat + iter_rows) + iter_cols) == -2)) {
                    *(*(deintrlvMat + iter_rows) + iter_cols) = *(dataBits + cnt);
                    cnt++;
                }
            }
        }

        cnt = 0;

        for (int iter_cols = 0; iter_cols < T; iter_cols++) {
            for (int iter_rows = 0; iter_rows < T-iter_cols; iter_rows++) {
                if (*(*(deintrlvMat + iter_rows) + iter_cols) != -1) {
                    *(deintrlvData + cnt) = *(*(deintrlvMat + iter_rows) + iter_cols);
                    cnt++;
                }
            }
        }

    } else {
        for (int iter_bits = 0; iter_bits < pcConfig->E; iter_bits++) {
            *(deintrlvData + iter_bits) = *(dataBits + iter_bits);
        }
    }

    for (int iter_rows = 0; iter_rows < T; iter_rows++) {
        free(*(deintrlvMat + iter_rows));
    }

    free(deintrlvMat);

    return deintrlvData;
}

int * NR_PC_INPUT_BITS_INTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig, int FWD_BWD) {
    int * dataOut = (int *)calloc(pcConfig->K, sizeof(int));
    int cnt = 0;
    
    if (pcConfig->iIL == 1) {
        if (_DEBUG_ == 1 && FWD_BWD == 0) {
            printf("Peforming Input bit interleaving...\n");
        }

        if (_DEBUG_ == 1 && FWD_BWD == 1) {
            printf("Peforming Input bit deinterleaving...\n");
        }
        
        for (int iter_bits = 0; iter_bits < pcConfig->K_IL_MAX; iter_bits++) {
            if (*(INPUT_INTERLEAVE_PATTERN + iter_bits) >= pcConfig->K_IL_MAX - pcConfig->K) {
                if (FWD_BWD == 0) {
                    *(dataOut + cnt) = *(dataBits + *(INPUT_INTERLEAVE_PATTERN + iter_bits) - (pcConfig->K_IL_MAX - pcConfig->K));
                } else {
                    *(dataOut + *(INPUT_INTERLEAVE_PATTERN + iter_bits) - (pcConfig->K_IL_MAX - pcConfig->K)) = *(dataBits + cnt);
                }

                cnt++;
            }
        }
    } else {
        for (int iter_bits = 0; iter_bits < pcConfig->K; iter_bits++) {
            *(dataOut + iter_bits) = *(dataBits + iter_bits);
        }
    }

    free(dataBits);
    
    return dataOut;
}
