#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#define SMALL_VALUES

#ifdef SMALL_VALUES
#define N 8888
#else
#define N 88888888  // Anzahl der Paare
#endif

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
    printf("%f strukt\n", (double)(end - start) / CLOCKS_PER_SEC);
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
    printf("%f arrayy von structs\n", (double)(end - start) / CLOCKS_PER_SEC);
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
    printf("%f Manuelle Speicherverwaltung gleichgroße Blöcke\n", (double)(end - start) / CLOCKS_PER_SEC);
    free(mem);

    // --- Variante 4: List of strings and numbers
    void *memm = malloc((N * sizeof(uint64_t)) + (N * sizeof(char*)));
    if (!memm) {
        perror("malloc failed");
        return 1;
    }
    uint64_t *nums2 = (uint64_t*)memm;
    char **strs = (char**)(nums2 + N);
    for (int i = 0; i < N; i++) {
        nums2[i] = (uint64_t)(rand() & 0xFFFFFFFF);
        char buf[32];
        snprintf(buf, sizeof(buf), "val_%u", rand() & 0xFFFF);
        strs[i] = strdup(buf);
    }
    start = clock();
    uint64_t sum4 = 0;
    for (int i = 0; i < N; i++) {
        sum4 += nums2[i] + strlen(strs[i]);
    }
    end = clock();
    printf("%f array of *ptr of strings\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < N; i++) {
        free(strs[i]);
    }
    free(memm);

    //  --- Variante 5: List of strings and pointers
    void *memmo = malloc((N * sizeof(uint64_t)) + (N * sizeof(uint32_t*)));
    if (!memmo) {
        perror("malloc failed");
        return 1;
    }
    uint64_t *nums3 = (uint64_t*)memmo;
    uint32_t **strs3 = (uint32_t**)(nums3 + N);
    for (int i = 0; i < N; i++) {
        nums3[i] = (uint64_t)(rand() & 0xFFFFFFFF);
        strs3[i] = malloc(sizeof(uint32_t));
        *strs3[i] = (uint32_t)(rand() & 0xFFFFFFFF);
    }
    start = clock();
    uint64_t sum5 = 0;
    for (int i = 0; i < N; i++) {
        sum5 += nums3[i] + *strs3[i];
    }
    end = clock();
    printf("%f array of 64bit and *ptr to 64bit\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < N; i++) {
        free(strs3[i]);
    }
    free(memmo);
    return 0;
}

