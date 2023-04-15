#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "headers/polarCodes.h"

int main() {

    srand(time(NULL));

    int * dataBits = NULL;
    int * crcData = NULL;
    int * encData = NULL;
    int * rateMatchData = NULL;
    double * modData = NULL;
    double * rxData = NULL;
    int * rxData_i = NULL;
    
    double * rxLR = NULL;
    double * rateRecoverData = NULL;
    int * decData = NULL;
    int * dataHat = NULL;    

    struct PC_CONFIG pcConfig;

    // Polar Code Config
    pcConfig.E = 1024;
    pcConfig.K = 512;
    pcConfig.nMax = 10;
    pcConfig.iBIL = 2;
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
    double SNR_dB = 7;


    // saveImg(imgData, imgLen);

    printf("SNR (dB): %f\n", SNR_dB);

    int imgLen = 0;
    int * dataBlock = loadImg(&imgLen);
    int numBlockEnc = ceil((float)imgLen / (pcConfig.K - pcConfig.crcLen));
    int numZeroAppend = (numBlockEnc * (pcConfig.K - pcConfig.crcLen) - imgLen);
    int dataBlockLen = numBlockEnc * (pcConfig.K - pcConfig.crcLen);
    int encBlockLen = numBlockEnc * pcConfig.E;

    dataBlock = appendZerosINT(dataBlock, imgLen, numZeroAppend);

    int * dataBlockHat = (int *)malloc(sizeof(int) * dataBlockLen);
    printf("num block: %d\n", numBlockEnc);
    for (int iter_blk = 0; iter_blk < numBlockEnc; iter_blk++) {
        dataBits = (dataBlock + iter_blk * (pcConfig.K - pcConfig.crcLen));

        crcData = NR_CRC_ENCODER(dataBits, &pcConfig);        
        encData = NR_PC_ENCODER(crcData, &pcConfig);        
        rateMatchData = NR_PC_RATE_MATCH(encData, &pcConfig);        
        modData = BPSK_MOD(rateMatchData, pcConfig.E);        
        
        rxData = AWGN(modData, pcConfig.E, SNR_dB);
        
        // rxData_i = BSC_Channel(rateMatchData, pcConfig.E, 0.000000000);        
        // rxData = intToDoubleArray(rxData_i, pcConfig.E);

        rxLR = BPSK_DEMOD(rxData, pcConfig.E, pcConfig.LR_PROB_1);                
        rateRecoverData = NR_PC_RATE_RECOVER(rxLR, &pcConfig);        
        decData = NR_PC_DECODER(rateRecoverData, &pcConfig);        
        dataHat = NR_CRC_DECODER(decData, &pcConfig, &err);

        for (int iter_bits = 0; iter_bits < (pcConfig.K - pcConfig.crcLen); iter_bits++) {
            *(dataBlockHat + iter_blk * (pcConfig.K - pcConfig.crcLen) + iter_bits) = *(dataHat + iter_bits);
        }        
    }    

    err = bitXORSum(dataBlockHat, dataBlock, numBlockEnc * (pcConfig.K - pcConfig.crcLen)); // Tmp

    dataBlockHat = clipLastZerosINT(dataBlockHat, numBlockEnc * (pcConfig.K - pcConfig.crcLen) + numZeroAppend, numZeroAppend);
    dataBlock = clipLastZerosINT(dataBlock, numBlockEnc * (pcConfig.K - pcConfig.crcLen) + numZeroAppend, numZeroAppend);

    saveImg(dataBlockHat, imgLen);

    printf("Result: ");

    if (err == 0) {
        printf("Successful Transmission with %d out of %d bits in error\n", err, numBlockEnc * (pcConfig.K - pcConfig.crcLen));
    } else {
        printf("Corrupted Reception with %d out of %d bits in error\n", err, numBlockEnc * (pcConfig.K - pcConfig.crcLen));
    }


    return 0;
}
