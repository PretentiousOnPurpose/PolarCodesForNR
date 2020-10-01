// NR_CRC_ENCODER - Perform CRC Encoding

#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

// CRC Polynomial

int CRC6[] = {1, 1, 0, 0, 0, 0, 1};
int CRC11[] = {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1};
int CRC16[] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
int CRC24C[] = {1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1};
int CRC24B[] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1};
int CRC24A[] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1};

// int * NR_CRC_ENCODER(int * dataBits, struct PC_CONFIG pcConfig) {
//     // For iter variable
//     int iter_bits;
//     // Allocating buffer for CRC Encoded Output
//     int * crcEncOut = (int *)malloc(sizeof(int) * pcConfig.K);
//     int * crcPoly = (int *)malloc(sizeof(int) * 24);

//     // Selecting a CRC Polynomial as per Config    
//     if (pcConfig.crcPolyID == 1) {
//         crcPoly = CRC24A;
//     } else if (pcConfig.crcPolyID == 2) {
//         crcPoly = CRC24B;
//     } else if (pcConfig.crcPolyID == 3) {
//         crcPoly = CRC24C;
//     } else if (pcConfig.crcPolyID == 4) {
//         crcPoly = CRC16;
//     } else if (pcConfig.crcPolyID == 5) {
//         crcPoly = CRC11;
//     } else if (pcConfig.crcPolyID == 5) {
//         crcPoly = CRC6;
//     }

//     // Calculating Remainder to be appended to the message using Long Division
//     int * rem = poly_long_div(dataBits, crcPoly, pcConfig);

//     // Appending Remainder to the Message Bits
//     for (iter_bits = 0; iter_bits < (pcConfig.K - pcConfig.crcLen); iter_bits++) {
//         *(crcEncOut + iter_bits) = *(dataBits + iter_bits);

//         if (iter_bits < pcConfig.crcLen) {
//             *(crcEncOut + iter_bits + pcConfig.K - pcConfig.crcLen) = *(rem + iter_bits);    
//         }
//     }

//     return crcEncOut;
// }

// // Performs Long Division between Two Polynomials
// int * poly_long_div(int * dataBits, int * crcPoly, struct PC_CONFIG pcConfig) {
//     int iter_bits, tmp, numBits = pcConfig.K - pcConfig.crcLen;
//     int * tmp_poly;
//     int * rem = (int *)malloc(sizeof(int) * numBits);

//     for (iter_bits = 0; iter_bits < (pcConfig.K - pcConfig.crcLen); iter_bits++) {
//         *(rem + iter_bits) = *(dataBits + iter_bits);
//     }

//     while((degree_poly(rem, numBits) - degree_poly(crcPoly, numBits)) >= 0) {
//         tmp = degree_poly(rem, numBits) - degree_poly(crcPoly, numBits);
//         tmp_poly = incr_degree_poly(crcPoly, pcConfig.crcLen + 1, tmp);

//         for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
//             *(rem + iter_bits) = (*(rem + iter_bits) - *(tmp_poly + iter_bits)) % 2; 
//         }

        
//     }

//     return rem;
// }

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