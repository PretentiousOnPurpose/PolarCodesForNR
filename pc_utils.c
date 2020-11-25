#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "polarCodes.h"

int * DATA_GEN(int numBits) {
    int iter_bits;

    int * dataBits = (int *)calloc(numBits, sizeof(int));

    for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
        *(dataBits + iter_bits) = rand() % 2;
    }

    return dataBits;
}

void PRINT_ARRAY_INT(int * dataBits, int numBits) {
    int iter_bits;
    
    for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
        printf("%d,", *(dataBits + iter_bits));
    }
    printf("\n");
  
}

void PRINT_ARRAY_DOUBLE(double * dataBits, int numBits) {
    int iter_bits;
    
    for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
        printf("%f,", *(dataBits + iter_bits));
    }
    printf("\n");
  
}

void PRINT_MAT_INT(int ** dataMat, int rows, int cols) {
    int iter_rows, iter_cols;

    for (iter_rows = 0; iter_rows < rows; iter_rows++) {
        for (iter_cols = 0; iter_cols < cols; iter_cols++) {
            printf("%d ", *(*(dataMat + iter_cols) + iter_rows));
        }
        printf("\n");
    }

}


void PRINT_MAT_DOUBLE(double ** dataMat, int rows, int cols) {
    int iter_rows, iter_cols;

    for (iter_rows = 0; iter_rows < rows; iter_rows++) {
        for (iter_cols = 0; iter_cols < cols; iter_cols++) {
            printf("%f ", *(*(dataMat + iter_cols) + iter_rows));
        }
        printf("\n");
    }

}

// Performs Long Division between Two Polynomials
int * poly_long_div(int * P1, int * P2, int L1, int L2, int * remLen) {
    int iter_bits, tmp, deg1, deg2;
    int * tmp_poly;

    int * rem = (int *)calloc(L1, sizeof(int));

    for (iter_bits = 0; iter_bits < L1; iter_bits++) {
        *(rem + iter_bits) = *(P1 + iter_bits);
    }

    while((degree_poly(rem, L1) - degree_poly(P2, L2)) >= 0) {
        tmp = degree_poly(rem, L1) - degree_poly(P2, L2);
        tmp_poly = incr_degree_poly(P2, L2, tmp);

        for (iter_bits = 0; iter_bits < L1; iter_bits++) {
            if ((*(rem + iter_bits) - *(tmp_poly + iter_bits)) != 0) {
                *(rem + iter_bits) = 1;
            } else {
                *(rem + iter_bits) = 0;
            }
        }

        if (SUM_ARRAY_INT(rem, L1) == 0) {
            break;
        }

        deg1 = degree_poly(rem, L1);
        rem = rem + L1 - deg1 - 1;
        L1 = deg1 + 1;

        free(tmp_poly);
    }

    *remLen = L1;

    return rem;
}

int SUM_ARRAY_INT(int * dataBits, int L) {
    int iter_bits, sum = 0;

    for (iter_bits = 0; iter_bits < L; iter_bits++) {
        sum += *(dataBits + iter_bits);
    }

    return sum;
}

// Returns Degree of a Polynomial
int degree_poly(int * poly, int numBits) {
    // For iter var and return var
    int iter_bits, deg;

    // Iterating over the polynomial and finding the degree
    for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
        if (*(poly + iter_bits)) {
            deg = numBits - iter_bits - 1;
            break;
        }
    }

    return deg;
}

// Increase the Degree of the Polynomial
int * incr_degree_poly(int * poly, int numBits, int incr_deg) {
    int iter_bits;
    int * newPoly = (int * )calloc(numBits + incr_deg, sizeof(int));

    for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
        *(newPoly + iter_bits) = *(poly + iter_bits);

        if (iter_bits < incr_deg) {
            *(newPoly + iter_bits + numBits) = 0;
        }
    }

    return newPoly;
}

int * ones(int len) {
    int iter_bits;
    int * dataBits = (int *)calloc(len, sizeof(int));

    for (iter_bits = 0; iter_bits < len; iter_bits++) {
        *(dataBits + iter_bits) = 1;
    }

    return dataBits;
}

void bitxor(int * x1, int * x2, int len) {
    int iter_bits;
    // int * y = (int *)malloc(sizeof(int) * len);

    for (iter_bits = 0; iter_bits < len; iter_bits++) {
        *(x1 + iter_bits) = *(x1 + iter_bits) ^ *(x2 + iter_bits);
    }

}

int * merge(int * s1, int * s2, int L1, int L2) {
    int i = 0, j = 0, k = 0;

    int * s_tmp = (int *)calloc(sizeof(int), (L1 + L2));

    while (i < L1 && j < L2) {
        if (*(s1 + i) < *(s2 + j)) {
            *(s_tmp + k) = *(s1 + i);
            i++;
            k++;
        } else {
            *(s_tmp + k) = *(s2 + j);
            j++;
            k++;
        }
    }

    while (i < L1) {
        *(s_tmp + k) = *(s1 + i);
        i++;
        k++;
    }

    while (j < L2) {
        *(s_tmp + k) = *(s2 + j);
        j++;
        k++;
    }

    return s_tmp;
}

int * mergeSort(int * s, int L) {
    int i;

    if (L == 1) {
        return s;
    }

    int * s1 = (int *)calloc(sizeof(int), (int)floor(L/2));
    int * s2 = (int *)calloc(sizeof(int), (int)(L - floor(L/2)));
    
    for (i = 0; i < (int)floor(L/2); i++) {
        *(s1 + i) = *(s + i);
    }

    for (i = (int)floor(L/2); i < L; i++) {
        *(s2 + i - (int)floor(L/2)) = *(s + i);        
    }

    s1 = mergeSort(s1, (int)floor(L/2));
    s2 = mergeSort(s2, (int)(L - floor(L/2)));

    s = merge(s1, s2, (int)floor(L/2), (int)(L - floor(L/2)));

    free(s1);
    free(s2);

    return s;
}

double * BPSK_MOD(int * dataBits, int L) {
    int iter_bits;

    double * modData = (double *)calloc(L, sizeof(double));

    for (iter_bits = 0; iter_bits < L; iter_bits++) {
        *(modData + iter_bits) = -1 * (*(dataBits + iter_bits) == 0) + 1 * (*(dataBits + iter_bits) == 1);
    }

    return modData;
}

double * AWGN(double * modData, int L, double noiseVar) {
    int iter_syms;
    double * rxData = (double *)calloc(L, sizeof(double));

    for (iter_syms = 0; iter_syms < L; iter_syms++) {
        *(rxData + iter_syms) = *(modData + iter_syms) + sqrt(noiseVar) * randn();
    }
    
    return rxData;
}

double * BPSK_DEMOD(double * rxSyms, int L, int LR_PROB_1) {
    int iter_syms;

    double * rxLR = (double *)calloc(L, sizeof(double));

    for (iter_syms = 0; iter_syms < L; iter_syms++) {
        if (LR_PROB_1) {
            *(rxLR + iter_syms) = (exp(-(pow((*(rxSyms + iter_syms) - 1), 2))));
        } else {
            *(rxLR + iter_syms) = (exp(-(pow((*(rxSyms + iter_syms) + 1), 2)) + (pow((*(rxSyms + iter_syms) - 1), 2))));
            
            if (*(rxLR + iter_syms) <= 0.025) {
                *(rxLR + iter_syms) = 0.001;
            }

            if (*(rxLR + iter_syms) > 10) {
                *(rxLR + iter_syms) = 10;
            }
        }
    }

    return rxLR;
}

double randn() {
    // Implemented using Box Muller Transform
    double x1 = (double)rand() / RAND_MAX;
    double x2 = (double)rand() / RAND_MAX;

    return sqrt(-2 * log(x1)) * cos(2 * 3.14159 * x2);
}

int * QUAD_EQN_SOL(int a, int b, int c) {
    double delta = (b * b) - 4 * a * c;
    double root1, root2;

    if (delta > 0) {
        root1 = (-b + sqrt(delta)) / (2 * a);
        root2 = (-b - sqrt(delta)) / (2 * a);
    } else if (delta == 0) {
        root1 = root2 = -b / (2 * a);
    } else {
        root1 = root2 = 0;
    }

    if (root1 < root2) {
        return (int)ceil(root1);
    }

    return (int)ceil(root2);
}