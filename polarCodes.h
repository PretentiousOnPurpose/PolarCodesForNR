#include <stdio.h>

CRC_CONFIG GEN_CRC_CONFIG(int crcLen, int crcPoly);
PC_CONFIG GEN_PC_CONFIG(int E, int K, int nMax, int UL_DL, int iBL, int iDL, CRC_CONFIG crcConfig);

