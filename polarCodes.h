#define _DEBUG_ 0

// Polar Codes
struct PC_CONFIG {
    int E; // Rate-Matched Output
    int K; // Input Data Block size (in bits)
    int N; // Polar Encoding Output Size
    int n;
    int nMax; // 9 - Downlink | 10 - Uplink
    int UL_DL; // Uplink/Downlink
    int iIL; // Input bit interleaving
    int iBIL; // Code bit interleaving
    int K_IL_MAX;
    int L; // List length for SCL
    int crcLen; // CRC Length
    int crcPolyID; // 1 - 24A, 2 - 24B, 3 - 24C, 4 - 16, 5 - 11
    int decodingMethod; // 1 - SC, 2 - CRC-SCL, 3 - BP, 4 - CRC-BPL
    int iter_BP; // Number of iterations for BP Decoder
    int LR_PROB_1; // Demod output type - Likelihood Ratio or Probability of Bit being 1
};

// Input and Coded Bits Interleaving
int * NR_PC_INPUT_BITS_INTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig, int FWD_BWD);
int * NR_PC_CODED_BITS_INTERLEAVING(int * dataBits, struct PC_CONFIG * pcConfig);
double * NR_PC_CODED_BITS_DEINTERLEAVING(double * dataBits, struct PC_CONFIG * pcConfig);

// Polar Encoding
void NR_PC_GET_N(struct PC_CONFIG * pcConfig);
int * NR_PC_GET_REL_SEQ(struct PC_CONFIG * pcConfig);
int * NR_PC_GET_FROZEN_POS(struct PC_CONFIG * pcConfig);
int * NR_PC_ENCODER(int * dataBits, struct PC_CONFIG * pcConfig);
int * NR_PC_DECODER(double * rxLR, struct PC_CONFIG * pcConfig);
int * POLAR_TRANSFORM(int * dataBits, int ind1, int ind2);
int * PC_SET_DATABITS(int * dataBits, struct PC_CONFIG * pcConfig);

// Cyclic Redudancy Check (CRC)
int * NR_CRC_ENCODER(int * dataBits, struct PC_CONFIG * pcConfig);
int * NR_CRC_DECODER(int * dataBits, struct PC_CONFIG * pcConfig, int * err);

// Rate Matching and Recovery
int * subBlockInterleaving(int * dataBits, struct PC_CONFIG * pcConfig);
double * subBlockDeinterleaving(double * dataBits, struct PC_CONFIG * pcConfig);
int * bitSelection(int * dataBits, struct PC_CONFIG * pcConfig);
double * bitDeselection(double * dataBits, struct PC_CONFIG * pcConfig);
int * NR_PC_RATE_MATCH(int * dataBits, struct PC_CONFIG * pcConfig);
double * NR_PC_RATE_RECOVER(double * dataBits, struct PC_CONFIG * pcConfig);
int * subBlockInterleavePattern(int N);

// Likelihood Calculation
double PC_LikelihoodRatio_L(double x1, double x2);
double PC_LikelihoodRatio_R(double x1, double x2, int bit);
double PC_LLR_TO_BIT(double rxLR);
double * LR_TO_PROB(double * rxLR, int L);

// Successive Cancellation (SC) and SC List Decoder 
void SC_DECODER(double * rxLR, int L, double ** rxBitsMat, int * rxLen, int * frozen_pos, struct PC_CONFIG * pcConfig);
int * SCL_DECODER(double * rxLR, struct PC_CONFIG * pcConfig);


// BPSK Modulation and LLR based Demodulation
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
int QUAD_EQN_SOL(int a, int b, int c);
int isEqual_INT(int * x1, int * x2, int L);
int isEqual_DOUBLE(double * x1, double * x2, int L);
void ARRAY_INT_COPY(int * dst, int * src, int L);
int bitXORSum(int * x1, int * x2, int L);
double norm(double * x, int L);
int * linspace(int start, int stop, int step);
int * seqUnion(int * seq1, int * seq2, int L1, int L2, int * L);
int isElementInArray(int * seq, int len, int el);
int * unionElToArray(int * seq, int L, int el, int * seq_len);