#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define N 88888888  // Anzahl der Paare

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
    printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
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
    printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
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
    printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    free(mem);

    // --- Variante 4: List of strings and numbers
    void *mem = malloc((N * sizeof(uint64_t)) + (N * sizeof(char*)));
    if (!mem) {
        perror("malloc failed");
        return 1;
    }
    uint64_t *nums = (uint64_t*)mem;
    char **strs = (char**)(nums + N);
    for (int i = 0; i < N; i++) {
        nums[i] = (uint64_t)(rand() & 0xFFFFFFFF);
        char buf[32];
        snprintf(buf, sizeof(buf), "val_%u", rand() & 0xFFFF);
        strs[i] = strdup(buf);
    }
    clock_t start = clock();
    uint64_t sum = 0;
    for (int i = 0; i < N; i++) {
        sum += nums[i] + strlen(strs[i]);
    }
    clock_t end = clock();
    printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < N; i++) {
        free(strs[i]);
    }
    free(mem);

    //  --- Variante 5: List of strings and pointers
    void *mem = malloc((N * sizeof(uint64_t)) + (N * sizeof(uint32_t*)));
    if (!mem) {
        perror("malloc failed");
        return 1;
    }
    uint64_t *nums = (uint64_t*)mem;
    uint32_t **strs = (uint32_t**)(nums + N);
    for (int i = 0; i < N; i++) {
        nums[i] = (uint64_t)(rand() & 0xFFFFFFFF);
        strs[i] = malloc(sizeof(uint32_t));
        *strs[i] = (uint32_t)(rand() & 0xFFFFFFFF);
    }
    clock_t start = clock();
    uint64_t sum = 0;
    for (int i = 0; i < N; i++) {
        sum += nums[i] + *strs[i];
    }
    clock_t end = clock();
    printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < N; i++) {
        free(strs[i]);
    }
    free(mem);
    return 0;
}

