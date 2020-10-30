#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polarCodes.h"

int * DATA_GEN(int numBits) {
    int iter_bits;

    int * dataBits = (int *)malloc(sizeof(int) * numBits);

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

// Performs Long Division between Two Polynomials
int * poly_long_div(int * P1, int * P2, int L1, int L2, int * remLen) {
    int iter_bits, tmp, deg1, deg2;
    int * tmp_poly;

    int * rem = (int *)malloc(sizeof(int) * L1);

    for (iter_bits = 0; iter_bits < L1; iter_bits++) {
        *(rem + iter_bits) = *(P1 + iter_bits);
    }

    while((degree_poly(rem, L1) - degree_poly(P2, L2)) >= 0) {
        tmp = degree_poly(rem, L1) - degree_poly(P2, L2);
        tmp_poly = incr_degree_poly(P2, L2, tmp);

        bitxor(rem, tmp_poly, L1);

        deg1 = degree_poly(rem, L1);
        rem = rem + L1 - deg1 - 1;
        L1 = deg1 + 1;

        free(tmp_poly);
    }

    *remLen = L1;

    return rem;
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
    int * newPoly = (int * )malloc(sizeof(int) * (numBits + incr_deg));

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
    int * dataBits = (int *)malloc(sizeof(int) * len);

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
