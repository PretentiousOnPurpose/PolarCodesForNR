#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int * charToINTArray(char data) {
    int * dataBits = (int *)malloc(8 * sizeof(int));

    for (int iterBits = 0; iterBits < 8; iterBits++) {
        *(dataBits + iterBits) = ((data & (1 << (8 - iterBits - 1))) > 0);
    }

    return dataBits;
}


char INTArrayToChar(int * dataBits) {
    char data = 0x00000000;

    for (int iterBits = 0; iterBits < 8; iterBits++) {
        data = data | (1 << iterBits) * dataBits[7-iterBits];
    }

    return data;
}

// int * loadImg(int * imgLen) {
//     FILE * fp;
//     int numBytes;
//     char dataByte;
//     int * dataBits;
//     int * tmpBits;
    
//     fp = fopen("./images/test_image.jpg", "rb");
//     fseek(fp, 0, SEEK_END);
//     numBytes = ftell(fp);
//     *imgLen = numBytes * 8;
//     dataBits = (int *)malloc(numBytes * 8 * sizeof(int));
//     rewind(fp);

//     for (int iterBytes = 0; iterBytes < numBytes; iterBytes++) {
//         fread(&dataByte, 1, 1, fp);
//         tmpBits = charToINTArray(dataByte);
//         for (int iterBits = 0; iterBits < 8; iterBits++) {
//             dataBits[iterBytes * 8 + iterBits] = tmpBits[iterBits];
//         }
//     }

//     fclose(fp);

//     return dataBits;
// } 

// int saveImg(int * imgData, int imgLen) {
//     FILE * fp = fopen("./images/test_image_rec.jpg", "wb");
//     char data = 0x00000000;


//     for (int iterBytes = 0; iterBytes < imgLen / 8; iterBytes++) {
//         data = INTArrayToChar(&imgData[iterBytes * 8]);
//         fwrite(&data, 1, 1, fp);
//     }

//     fclose(fp);
//     return 0;
// } 


void main() {
    // int imgLen = 0;
    // int * imgData = loadImg(&imgLen);
    // imgData = appendZerosINT(imgData, imgLen, 123);
    // imgData = clipLastZerosINT(imgData, imgLen + 123, 123);

    // saveImg(imgData, imgLen);

    printf("%lf\n", (double)sqrt(1/(10)));

}