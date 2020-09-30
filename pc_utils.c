#include <stdio.h>
#include "polarCodes.h"

int * DATA_GEN(int nRows, int nCols) {
    int iter_rows, iter_cols;

    int * dataMat = (int *)malloc(sizeof(int) * nRows * nCols);

    for (iter_rows = 0; iter_rows < nCols; iter_rows++) {
        for (iter_cols = 0; iter_cols < nRows; iter_cols++) {
            *(dataMat + iter_rows + iter_cols) = rand() % 2;
        }
    }

    return dataMat;
}

void PRINT_MAT_INT(int * dataMat, int nRows, int nCols) {
    int iter_rows, iter_cols;
    
    for (iter_rows = 0; iter_rows < nRows; iter_rows++) {
        for (iter_cols = 0; iter_cols < nCols; iter_cols++) {
            printf("%d ", *(dataMat + iter_rows + iter_cols));
        }
        printf("\n");
    }
}