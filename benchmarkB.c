#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define N 88888888  // Anzahl der Elemente

int main(void) {
    srand((unsigned)time(NULL));

    // Speicherblock: N uint64_t + N char*
    void *mem = malloc((N * sizeof(uint64_t)) + (N * sizeof(char*)));
    if (!mem) {
        perror("malloc failed");
        return 1;
    }

    uint64_t *nums = (uint64_t*)mem;
    char **strs = (char**)(nums + N);

    // Initialisierung: Zufallszahlen und Dummy-Strings
    for (int i = 0; i < N; i++) {
        nums[i] = (uint64_t)(rand() & 0xFFFFFFFF);

        // kleine Strings erzeugen
        char buf[32];
        snprintf(buf, sizeof(buf), "val_%u", rand() & 0xFFFF);
        strs[i] = strdup(buf);  // allokiert neuen String
    }

    // Benchmark: Summation
    clock_t start = clock();
    uint64_t sum = 0;
    for (int i = 0; i < N; i++) {
        sum += nums[i] + strlen(strs[i]);
    }
    clock_t end = clock();

    printf("Sum=%llu, Zeit=%f s\n",
           (unsigned long long)sum,
           (double)(end - start) / CLOCKS_PER_SEC);

    // Speicher freigeben
    for (int i = 0; i < N; i++) {
        free(strs[i]);
    }
    free(mem);

    return 0;
}

