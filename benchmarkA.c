#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define N 88888888  // Anzahl der Paare

/*
 *0.003141
 *0.004787
 *0.002654
 * */

// Variante 1: struct
typedef struct {
    uint64_t nums[N];
    uint64_t other[N];
} DataBlock;

int main(void) {
    srand((unsigned)time(NULL));

    // --- Variante 1: struct ---
    DataBlock *block = malloc(sizeof(DataBlock));
    for (int i = 0; i < N; i++) {
        block->nums[i]  = (uint64_t)(rand() & 0xFFFFFFFF);
        block->other[i] = (uint64_t)(rand() & 0xFFFFFFFF);
    }

    clock_t start = clock();
    uint64_t sum1 = 0;
    for (int i = 0; i < N; i++) {
        sum1 += block->nums[i] + block->other[i];
    }
    clock_t end = clock();
    printf("Struct: Sum=%llu, Zeit=%f s\n",
           (unsigned long long)sum1,
           (double)(end - start) / CLOCKS_PER_SEC);
    free(block);

    // --- Variante 2: Array von structs ---
    typedef struct { uint64_t a, b; } Pair;
    Pair *arr = malloc(N * sizeof(Pair));
    for (int i = 0; i < N; i++) {
        arr[i].a = (uint64_t)(rand() & 0xFFFFFFFF);
        arr[i].b = (uint64_t)(rand() & 0xFFFFFFFF);
    }

    start = clock();
    uint64_t sum2 = 0;
    for (int i = 0; i < N; i++) {
        sum2 += arr[i].a + arr[i].b;
    }
    end = clock();
    printf("Array von Structs: Sum=%llu, Zeit=%f s\n",
           (unsigned long long)sum2,
           (double)(end - start) / CLOCKS_PER_SEC);
    free(arr);

    // --- Variante 3: manuelles Layout ---
    void *mem = malloc(2 * N * sizeof(uint64_t));
    uint64_t *nums = (uint64_t*)mem;
    uint64_t *other = nums + N;

    for (int i = 0; i < N; i++) {
        nums[i]  = (uint64_t)(rand() & 0xFFFFFFFF);
        other[i] = (uint64_t)(rand() & 0xFFFFFFFF);
    }

    start = clock();
    uint64_t sum3 = 0;
    for (int i = 0; i < N; i++) {
        sum3 += nums[i] + other[i];
    }
    end = clock();
    printf("Manuelles Layout: Sum=%llu, Zeit=%f s\n",
           (unsigned long long)sum3,
           (double)(end - start) / CLOCKS_PER_SEC);
    free(mem);
    return 0;
}

