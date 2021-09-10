#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "polarCodes.h"

int main() {

    srand(108);
    
    struct PC_CONFIG pcConfig;

    // Polar Code Config
    pcConfig.E = 94;
    pcConfig.K = 28;
    pcConfig.nMax = 9;
    pcConfig.iBIL = 0;
    pcConfig.iIL = 0;
    pcConfig.K_IL_MAX = 164;
    pcConfig.UL_DL = 0;
    pcConfig.L = 8;
    pcConfig.crcLen = 24;
    pcConfig.crcPolyID = 1; 
    pcConfig.decodingMethod = 1;
    pcConfig.iter_BP = 10;
    pcConfig.LR_PROB_1 = 1;

    int remLen = 0;
    int err = 1;

    printf("Polar Codes for 5G NR\n---------------------\n");
    if (_DEBUG_ == 1) {
        printf("K/E: %d/%d\n", pcConfig.K, pcConfig.E);
        printf("Direction: %s\n---------------------\n", (pcConfig.UL_DL == 0) ? "Uplink" : "Downlink");
        printf("Transmitter Side\n---------------------\n");
    }


    int * dataBits = DATA_GEN(pcConfig.K - pcConfig.crcLen);
    PRINT_ARRAY_INT(dataBits, pcConfig.K - pcConfig.crcLen);
    int * crcData = NR_CRC_ENCODER(dataBits, &pcConfig);
    PRINT_ARRAY_INT(crcData, pcConfig.K);
    int * encData = NR_PC_ENCODER(crcData, &pcConfig);
    PRINT_ARRAY_INT(encData, pcConfig.N);
    // printf("\n\n\n");
    // PRINT_ARRAY_INT(subBlockInterleavePattern(128), pcConfig.N);
    int * rateMatcData = NR_PC_RATE_MATCH(encData, &pcConfig);
    PRINT_ARRAY_INT(rateMatcData, pcConfig.E);

    // double * modData = BPSK_MOD(rateMatcData, pcConfig.E);
    // if (_DEBUG_ == 1) {
    //     printf("----------------------\nReceiver Side\n----------------------\n");
    // }
    // double * rxData = AWGN(modData, pcConfig.E, 0);
    // double * rxLR = BPSK_DEMOD(rxData, pcConfig.E, pcConfig.LR_PROB_1);
    // double * rateRecoverData = NR_PC_RATE_RECOVER(rxLR, &pcConfig);
    // int * decData = NR_PC_DECODER(rateRecoverData, &pcConfig);
    // int * dataHat = NR_CRC_DECODER(decData, &pcConfig, &err);

    // printf("Result: ");

    // if (err == 0) {
    //     printf("Successful Transmission with %d out of %d bits in error\n", bitXORSum(dataHat, dataBits, pcConfig.K - pcConfig.crcLen), pcConfig.K - pcConfig.crcLen);
    // } else {
    //     printf("Corrupted Reception with %d out of %d bits in error\n", bitXORSum(dataHat, dataBits, pcConfig.K - pcConfig.crcLen), pcConfig.K - pcConfig.crcLen);
    // }

    return 0;
}
