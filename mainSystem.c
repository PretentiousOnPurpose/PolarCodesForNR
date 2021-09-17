#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "polarCodes.h"

int main() {

    // srand(time(NULL));
    srand(108);
    
    struct PC_CONFIG pcConfig;

    // Polar Code Config
    pcConfig.E = 4096;
    pcConfig.K = 256;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 1;
    pcConfig.iIL = 0;
    pcConfig.K_IL_MAX = 164;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 24;
    pcConfig.crcPolyID = 1; 
    pcConfig.decodingMethod = 1;
    pcConfig.iter_BP = 1;
    pcConfig.LR_PROB_1 = pcConfig.decodingMethod == 1 ? 0:1; // if 0 - output is Likelihood Ratio else Probability of bit being 1

    int remLen = 0;
    int err = 1;
    double SNR_dB = -2;
    double SNR = pow(10, SNR_dB / 10);

    int * dataBits = DATA_GEN(pcConfig.K - pcConfig.crcLen);
    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
    int * encData = NR_PC_ENCODER(crcData, &pcConfig);
    int * rateMatcData = NR_PC_RATE_MATCH(encData, &pcConfig);
    double * modData = BPSK_MOD(rateMatcData, pcConfig.E);
    double * rxData = AWGN(modData, pcConfig.E, SNR);
    double * rxLR = BPSK_DEMOD(rxData, pcConfig.E, pcConfig.LR_PROB_1);
    double * rateRecoverData = NR_PC_RATE_RECOVER(rxLR, &pcConfig);
    int * decData = NR_PC_DECODER(rateRecoverData, &pcConfig);
    int * dataHat = NR_CRC_DECODER(decData, &pcConfig, &err);

    printf("Result: ");

    if (err == 0) {
        printf("Successful Transmission with %d out of %d bits in error\n", bitXORSum(dataHat, dataBits, pcConfig.K - pcConfig.crcLen), pcConfig.K - pcConfig.crcLen);
    } else {
        printf("Corrupted Reception with %d out of %d bits in error\n", bitXORSum(dataHat, dataBits, pcConfig.K - pcConfig.crcLen), pcConfig.K - pcConfig.crcLen);
    }

    return 0;
}
