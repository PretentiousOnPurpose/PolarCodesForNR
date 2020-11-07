#include <stdio.h>

// Polar Codes
struct PC_CONFIG {
    int E; // Rate-Matched Output
    int K; // Input Data Block size (in bits)
    int N; // Polar Encoding Output Size
    int n; // log2(N)
    int nMax; // 9 - Downlink | 10 - Uplink
    int UL_DL; // Uplink/Downlink
    int iIL;
    int iBIL; 
    int L; // List length for SCL
    int crcLen; // CRC Length
    int crcPolyID; // 1 - 24A, 2 - 24B, 3 - 24C, 4 - 16, 5 - 11
    int decodingMethod; // 1 - SC, 2 - SCL, 3 - BPL
    int iter_BP; // Number of iterations for BP Decoder
    int LR_LLR; // Demod output type - Likelihood or Log-likelihood Ratio 
} pcConfig;

static int cnt = 0;

void NR_PC_GET_N(struct PC_CONFIG * pcConfig);
int * NR_PC_GET_REL_SEQ(struct PC_CONFIG * pcConfig);
int * NR_PC_GET_FROZEN_POS(struct PC_CONFIG * pcConfig);
int * NR_PC_ENCODER(int * dataBits, struct PC_CONFIG * pcConfig);
int * NR_PC_DECODER(double * rxLR, struct PC_CONFIG * pcConfig);

int * POLAR_TRANSFORM(int * dataBits, int ind1, int ind2);
int * PC_SET_DATABITS(int * dataBits, struct PC_CONFIG * pcConfig);

int * NR_CRC_ENCODER(int * dataBits, struct PC_CONFIG * pcConfig);
int * NR_CRC_DECODER(int * dataBits, struct PC_CONFIG * pcConfig, int * err);

int * NR_PC_RATE_MATCH(int * dataBits, struct PC_CONFIG * pcConfig);
int * NR_PC_RATE_REMOVE(int * dataBits, struct PC_CONFIG * pcConfig);

double PC_LikelihoodRatio_L(double x1, double x2);
double PC_LikelihoodRatio_R(double x1, double x2, int bit);
int PC_LLR_TO_BIT(double rxLR);
void SC_DECODER(double * rxLR, int L, int ** rxBitsMat, int * rxLen, int * frozen_pos);
int * SCL_DECODER(double * rxLR, struct PC_CONFIG * pcConfig);

double * LR_TO_PROB(double * rxLR, int L);
double PROB_A_B_EQ(double P1, double P2);
double PROB_A_B_XOR(double P1, double P2);
void BP_ProcessUnit_BACK(double ** rxBeliefsMat, int currStep, int ind1, int ind2, int * frozen_pos);
void BP_ProcessUnit_FWD(double ** rxBeliefsMat, int currStep, int ind1, int ind2, int * frozen_pos);
void BP_DECODER(double ** rxBeliefsMat, int L, int * frozen_pos, int iter_BP);

// BPSK Modulation
double * BPSK_MOD(int * dataBits, int L);
double * BPSK_DEMOD(double * rxSyms, int L, int LR_LLR);

// AWGN Channels
double * AWGN(double * txSyms, int L, double noiseVar);

// Utilities and Misc.

int * DATA_GEN(int numBits);
int SUM_ARRAY_INT(int * dataBits, int L);
void PRINT_ARRAY_INT(int * dataBits, int numBits);
void PRINT_ARRAY_DOUBLE(double * dataBits, int numBits);
void PRINT_MAT_INT(int ** dataMat, int rows, int cols);
void PRINT_MAT_DOUBLE(double ** dataMat, int rows, int cols);
int * poly_long_div(int * P1, int * P2, int L1, int L2, int * remLen);
int degree_poly(int * poly, int numBits);
int * incr_degree_poly(int * poly, int numBits, int incr_deg);
int * CRCGenerator(int * msg, int * crcPoly, int msgLen, int crcPolyLen);
int * ones(int len);
void bitxor(int * x1, int * x2, int len);
int * merge(int * s1, int * s2, int L1, int L2);
int * mergeSort(int * s, int L);
double randn();
