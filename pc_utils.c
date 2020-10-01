#include <stdio.h>
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
        printf("%d ", *(dataBits + iter_bits));
    }
    printf("\n");
  
}

// Performs Long Division between Two Polynomials
int * poly_long_div(int * dataBits, int * crcPoly, struct PC_CONFIG * pcConfig) {
    int iter_bits, tmp, numBits = pcConfig->K - pcConfig->crcLen;
    int * tmp_poly;
    int * rem = (int *)malloc(sizeof(int) * numBits);

    for (iter_bits = 0; iter_bits < (pcConfig->K - pcConfig->crcLen); iter_bits++) {
        *(rem + iter_bits) = *(dataBits + iter_bits);
    }

    while((degree_poly(rem, numBits) - degree_poly(crcPoly, numBits)) >= 0) {
        tmp = degree_poly(rem, numBits) - degree_poly(crcPoly, numBits);
        tmp_poly = incr_degree_poly(crcPoly, pcConfig->crcLen + 1, tmp);

        for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
            *(rem + iter_bits) = (*(rem + iter_bits) - *(tmp_poly + iter_bits)) % 2; 
        }

        
    }

    return rem;
}

// Returns Degree of a Polynomial
int degree_poly(int * poly, int numBits) {
    // For iter var and return var
    int iter_bits, deg;

    // Iterating over the polynomial and finding the degree
    for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
        if (*(poly + iter_bits)) {
            deg = numBits - iter_bits;
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