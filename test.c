#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <immintrin.h>

int main() {
    time_t tstart, tend; 
    int a = 102942, b = 32320, c = 0;
    __m256i A = *(__m256i *)&a;
    __m256i B = *(__m256i *)&b;
    __m256i C = *(__m256i *)&C;    
    long long N = 1000000000;
    int i;
    tstart = time(0);
    for (i = 0; i < N; i++) {
        c = a + b;
    }

    tend = time(0); 

    printf("Diff time(normal): %lf\n", difftime(tend, tstart));

    tstart = time(0);

    for (i = 0; i < N; i++) {
        C = _mm256_add_epi32(A, B);
    }

    tend = time(0); 
    printf("Diff time(AVX2): %lf\n", difftime(tend, tstart));


    printf("Results - c: %d | C: %d\n", c, *(int *)&C);


    return 0;

}