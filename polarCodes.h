#include <stdio.h>

CRC_CONFIG GEN_CRC_CONFIG(int crcLen, int crcPoly);
PC_CONFIG GEN_PC_CONFIG(int E, int K, int nMax, int UL_DL, int iBL, int iDL, CRC_CONFIG crcConfig);

int * NR_CRC_ENCODER(int * bits, CRC_CONFIG crcConfig);
int * NR_CRC_DECODER(int * bits, CRC_CONFIG crcConfig);

int * NR_PC_ENCODER(int * bits, PC_CONFIG pcConfig);
int * NR_PC_DECODER(int * bits, PC_CONFIG pcConfig);

int * NR_PC_RATE_MATCH(int * bits, PC_CONFIG pcConfig);
int * NR_PC_RATE_DEMATCH(int * bits, PC_CONFIG pcConfig);

float * AWGN(int * bits, float SNRdB);
float * EPA1(int * bits, int numRxAnt, float dopplerFreq, float initTime);

int * SC_DECODER(int * bits, PC_CONFIG pcConfig);
int * SCL_DECODER(int * bits, PC_CONFIG pcConfig);
int * BP_DECODER(int * bits, PC_CONFIG pcConfig);
