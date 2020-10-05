#include <stdio.h>
#include <stdlib.h>
#include "polarCodes.h"

int main() {
    int p1[] = {1, 0, 1, 1, 1, 0, 1, 0};
    int p2[] = {1, 0, 0, 1, 0, 0, 1, 1};

    int remLen = 8;

    bitxor(p1, p2, 8);

    PRINT_ARRAY_INT(p1, remLen);

    return 0;
}