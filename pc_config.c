#include <stdio.h>
#include <polarCodes.h>

extern typedef struct {
    int crcLen;
    int crcPoly;
} CRC_CONFIG;

extern typedef struct {
    int E;
    int K;
    int nMax;
    int UL_DL;
    int iBL;
    int iDL;
    CRC_CONFIG crcConfig;
} PC_CONFIG;

CRC_CONFIG GEN_CRC_CONFIG(int crcLen, int crcPoly) {
    return crcConfig(crcLen, crcPoly);
}

PC_CONFIG GEN_PC_CONFIG(int E, int K, int nMax, int UL_DL, int iBL, int iDL, CRC_CONFIG crcConfig) {
    return PC_CONFIG(int E, int K, int nMax, int UL_DL, int iBL, int iDL, CRC_CONFIG crcConfig);    
}

