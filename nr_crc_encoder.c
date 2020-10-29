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

int * NR_CRC_ENCODER(int * dataBits, struct PC_CONFIG * pcConfig) {
    // For iter variable
    int iter_bits;
    // Allocating buffer for CRC Encoded Output
    int * crcEncOut = (int *)malloc(sizeof(int) * pcConfig->K);
    int * crcPoly = (int *)malloc(sizeof(int) * (pcConfig->crcLen + 1));
    int remLen = 0;

    // Selecting a CRC Polynomial as per Config    
    if (pcConfig->crcPolyID == 1) {
        crcPoly = CRC24A;
    } else if (pcConfig->crcPolyID == 2) {
        crcPoly = CRC24B;
    } else if (pcConfig->crcPolyID == 3) {
        crcPoly = CRC24C;
    } else if (pcConfig->crcPolyID == 4) {
        crcPoly = CRC16;
    } else if (pcConfig->crcPolyID == 5) {
        crcPoly = CRC11;
    } else if (pcConfig->crcPolyID == 6) {
        crcPoly = CRC6;
    }

    // Calculating Remainder to be appended to the message using Long Division
    int * rem = CRCGenerator(dataBits, crcPoly, pcConfig->K - pcConfig->crcLen, pcConfig->crcLen + 1);

    // Appending Remainder to the Message Bits
    for (iter_bits = 0; iter_bits < (pcConfig->K - pcConfig->crcLen); iter_bits++) {
        *(crcEncOut + iter_bits) = *(dataBits + iter_bits);

        if (iter_bits < pcConfig->crcLen) {
            *(crcEncOut + iter_bits + pcConfig->K - pcConfig->crcLen) = *(rem + iter_bits);    
        }
    }

    return crcEncOut;
}


int * CRCGenerator(int * msg, int * crcPoly, int msgLen, int crcPolyLen) {
    int iter_bits, remLen = 0;
    int * crcBits = (int *)malloc(sizeof(int) * (crcPolyLen - 1));


    int * msg_tmp = incr_degree_poly(msg, msgLen, crcPolyLen - 1);
    msgLen = msgLen + crcPolyLen - 1;

    int * rem = poly_long_div(msg_tmp, crcPoly, msgLen, crcPolyLen, &remLen);

    for (iter_bits = crcPolyLen - 1 - remLen; iter_bits < crcPolyLen - 1; iter_bits++) {
        *(crcBits + iter_bits) = *(rem + iter_bits - (crcPolyLen - 1 - remLen));
    }

    free(msg_tmp);

    return crcBits;
}