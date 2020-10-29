// NR_CRC_DECODER - Perform CRC Decoding

#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

// CRC Polynomial

int CRC6_DEC[] = {1, 1, 0, 0, 0, 0, 1};
int CRC11_DEC[] = {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1};
int CRC16_DEC[] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
int CRC24C_DEC[] = {1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1};
int CRC24B_DEC[] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1};
int CRC24A_DEC[] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1};

int * NR_CRC_DECODER(int * crcBits, struct PC_CONFIG * pcConfig, int * err) {
    int iter_bits; // Iter Var
    // Allocating Buffers for Outputs and Other Vars
    int * crcDecOut = (int *)malloc(sizeof(int) * (pcConfig->K - pcConfig->crcLen));
    int * crcPoly = (int *)malloc(sizeof(int) * (pcConfig->crcLen + 1));
    int remLen = 0;

    // Selecting a CRC Polynomial as per Config    
    if (pcConfig->crcPolyID == 1) {
        crcPoly = CRC24A_DEC;
    } else if (pcConfig->crcPolyID == 2) {
        crcPoly = CRC24B_DEC;
    } else if (pcConfig->crcPolyID == 3) {
        crcPoly = CRC24C_DEC;
    } else if (pcConfig->crcPolyID == 4) {
        crcPoly = CRC16_DEC;
    } else if (pcConfig->crcPolyID == 5) {
        crcPoly = CRC11_DEC;
    } else if (pcConfig->crcPolyID == 6) {
        crcPoly = CRC6_DEC;
    }

    // Calculating Remainder of (crcBits / crcPoly)
    int * rem = poly_long_div(crcBits, crcPoly, pcConfig->K, pcConfig->crcLen + 1, &remLen);

    //  Checking if remainder is zeros or not. If rem is zero, then there is NO ERROR
    *err = 0;
    for (iter_bits = 0; iter_bits < remLen; iter_bits++) {
        if (*(rem + iter_bits)) {
            *err = 1;
            break;
        }
    }

    // Extracting DataBits from Systematic CRC ENCODING
    for (iter_bits = 0; iter_bits < (pcConfig->K - pcConfig->crcLen); iter_bits++) {
        *(crcDecOut + iter_bits) = *(crcBits + iter_bits);
    }

    return crcDecOut;

}