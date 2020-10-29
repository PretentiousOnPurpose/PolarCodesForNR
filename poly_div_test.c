#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int main() {
    int remLen = 0;

    // int p1[] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1};
    // int p2[] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1};
    // int L1 = 72, L2 = 25;
    // PRINT_ARRAY_INT(p1, L1);
    // PRINT_ARRAY_INT(p2, L2);

    // int * rem = poly_long_div(p1, p2, L1, L2, &remLen);

    int * rem = (int * )calloc(5, sizeof(int));
    *(rem) = 100;
    *(rem + 1) = -100;
    *(rem + 2) = 3;
    *(rem + 3) = -5;
    *(rem + 4) = 0;

    PRINT_ARRAY_INT(rem, remLen);
    remLen = 5;

    rem = mergeSort(rem, remLen);


    return 0;
}