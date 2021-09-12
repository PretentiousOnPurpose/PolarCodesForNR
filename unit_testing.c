// #include <stdio.h>
// #include <stdlib.h>

// void PRINT_ARRAY_INT(int * dataBits, int numBits) {
//     int iter_bits;
    
//     for (iter_bits = 0; iter_bits < numBits; iter_bits++) {
//         printf("%d,", *(dataBits + iter_bits));
//     }
//     printf("\n");
  
// }

// int isElementInArray(int * seq, int len, int el) {
//     for (int iter_seq = 0; iter_seq < len; iter_seq++) {
//         if (*(seq + iter_seq) == el) {
//             return 1;
//         }
//     }

//     return 0;
// }

// int * seqUnion(int * seq1, int * seq2, int L1, int L2, int * L) {
//     int iter_bits;
//     int * master_seq_tmp = (int *)calloc(L1 + L2, sizeof(int));
//     int * master_seq = NULL; //(int *)calloc(L1 + L2, sizeof(int));

//     for (iter_bits = 0; iter_bits < L1; iter_bits++) {
//         *(master_seq_tmp + iter_bits) = *(seq1 + iter_bits);
//     }

//     *L = L1;

//     for (int iter_bits = L1; iter_bits < L1 + L2; iter_bits++) {
//         if (!(isElementInArray(seq1, L1, *(seq2 + iter_bits - L1)))) {
//             *(master_seq_tmp + *L) = *(seq2 + iter_bits - L1);
//             *L = *L + 1;
//         }
//     }

//     master_seq = (int *)calloc(*L, sizeof(int));

//     for (int iter_bits = 0; iter_bits < *L; iter_bits++) {
//         *(master_seq + iter_bits) = *(master_seq_tmp);
//     }

//     free(master_seq_tmp);

//     return master_seq;
// }


// int main(void) {
// 	// your code goes here
	
// 	int * a1 = (int *)calloc(4, sizeof(int));
// 	a1[0] = 1;
// 	a1[1] = 4;
// 	a1[2] = 6;
// 	a1[3] = 10;

// 	int * a2 = (int *)calloc(6, sizeof(int));
// 	a2[0] = 1;
// 	a2[1] = 4;
// 	a2[2] = 6;
// 	a2[3] = 10;
// 	a2[4] = 13;
// 	a2[5] = 18;

//     int a = 0;

//     int * a3 = seqUnion(a1, a2, 4, 6, &a);

//     printf("Element is Present: %d\n", isElementInArray(a1, 4, 0));	
//     printf("Element is Present: %d\n", isElementInArray(a2, 6, 13));	
// 	return 0;
// }

