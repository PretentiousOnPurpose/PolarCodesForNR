#include <stdio.h>

// Polar Codes
struct PC_CONFIG {
    int E; // Rate-Matched Output
    int K; // Input Data Block size (in bits)
    int N; // Polar Encoding Output Size
    int n; // log2(N)
    int nMax; 
    int UL_DL; // Uplink/Downlink
    int iIL;
    int iBIL; 
    int L; // List length for SCL
    int crcLen; // CRC Length
    int crcPolyID; // 1 - 24A, 2 - 24B, 3 - 24C, 4 - 16, 5 - 11
    int decodingMethod; // 1 - SC, 2 - SCL, 3 - BPL
} pcConfig;

void NR_PC_GET_N(struct PC_CONFIG * pcConfig);
int * NR_PC_ENCODER(int * dataBits, struct PC_CONFIG * pcConfig);
int * NR_PC_DECODER(double * rxLLR, struct PC_CONFIG * pcConfig);

int * POLAR_TRANSFORM(int * dataBits, int ind1, int ind2);
int * PC_SET_DATABITS(int * dataBits, struct PC_CONFIG * pcConfig);

int * NR_CRC_ENCODER(int * bits, struct PC_CONFIG * pcConfig);
int * NR_CRC_DECODER(int * bits, struct PC_CONFIG * pcConfig, int * err);

int * NR_PC_RATE_MATCH(int * bits, struct PC_CONFIG * pcConfig);
int * NR_PC_RATE_REMOVE(int * bits, struct PC_CONFIG * pcConfig);

int * SC_DECODER(double * rxLLR, struct PC_CONFIG * pcConfig);
int * SCL_DECODER(double * rxLLR, struct PC_CONFIG * pcConfig);
int * BP_DECODER(double * rxLLR, struct PC_CONFIG * pcConfig);

// BPSK Modulation
double * BPSK_MOD(int * bits);
double * BPSK_DEMOD(double * rxSyms, int BITS_LLR);

// AWGN Channels
double * AWGN(double * txSyms, double SNRdB);

// Utilities and Misc.

int * DATA_GEN(int numBits);
void PRINT_ARRAY_INT(int * dataBits, int numBits);
void PRINT_ARRAY_DOUBLE(double * mat);
int * poly_long_div(int * P1, int * P2, int L1, int L2, int * remLen);
int degree_poly(int * poly, int numBits);
int * incr_degree_poly(int * poly, int numBits, int incr_deg);
int * CRCGenerator(int * msg, int * crcPoly, int msgLen, int crcPolyLen);
int * ones(int len);
void bitxor(int * x1, int * x2, int len);
int * merge(int * s1, int * s2, int L1, int L2);
int * mergeSort(int * s, int L);
