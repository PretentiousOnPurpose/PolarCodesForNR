// NR_CRC_ENCODER - Perform CRC Encoding which is a required step right before
//                  Polar Encoding

#include <stdio.h>
#include "polarCodes.h"

int * NR_CRC_ENCODER(int * dataBits, struct PC_CONFIG pcConfig) {
    // For iter variable
    int iter_bits;
    // Allocating buffer for CRC Encoded Output
    int * crcEncOut = (int *)malloc(sizeof(int) * pcConfig.K);

    // Selecting a CRC Polynomial as per Config    
    if (pcConfig.crcPolyID == 1) {
        int * crcPoly = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1};
    } else if (pcConfig.crcPolyID == 2) {
        int * crcPoly = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1};
    } else if (pcConfig.crcPolyID == 3) {
        int * crcPoly = {1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1};
    } else if (pcConfig.crcPolyID == 4) {
        int * crcPoly = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};   
    } else if (pcConfig.crcPolyID == 5) {
        int * crcPoly = {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    } else if (pcConfig.crcPolyID == 5) {
        int * crcPoly = {1, 1, 0, 0, 0, 0, 1};
    }

    // Calculating Remainder to be appended to the message using Long Division
    int * rem = poly_long_div(dataBits, crcPoly);

    // Appending Remainder to the Message Bits
    for (iter_bits = 0; iter_bits < (pcConfig.K - pcConfig.crcLen); iter_bits++) {
        *(crcEncOut + iter_bits) = *(dataBits + iter_bits);

        if (iter_bits < pcConfig.crcLen) {
            *(crcEncOut + iter_bits + pcConfig.K - pcConfig.crcLen) = *(rem + iter_bits);    
        }
    }

    return crcEncOut;
}