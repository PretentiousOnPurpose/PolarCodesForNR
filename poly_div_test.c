#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int main() {
    int remLen = 0;

    int p1[] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1};
    int p2[] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1};
    int L1 = 72, L2 = 25;
    PRINT_ARRAY_INT(p1, L1);
    PRINT_ARRAY_INT(p2, L2);

    int * rem = poly_long_div(p1, p2, L1, L2, &remLen);

    PRINT_ARRAY_INT(rem, remLen);

    return 0;
}