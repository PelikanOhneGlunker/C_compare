#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

const int MAX_COUNT = 128;
unsigned int *uintlist = NULL;
int *intlist = NULL;

void setUnsignedEnd(unsigned int *pos, unsigned int test, unsigned int *maxx) {
     *maxx = (test << 1) - 1;
     *pos = *maxx; ++pos;
     *pos = 0; ++pos;
     *pos = 0;
}

void setEnd(int *pos, int test, int *maxx) {
     *maxx = (test << 1) - 1;
     *pos = *maxx; ++pos;
     *pos = 0; ++pos;
     *pos = 0;
}

unsigned int max_unsigned_value() {
    unsigned int max_val = 0;
    unsigned int test = 1;
    unsigned int *start = uintlist;
    while ((test << 1) > test) {
        test <<= 1;
	*uintlist = test;
	++uintlist;
    }
    setUnsignedEnd(uintlist, test, &max_val);
    uintlist = start;
    return max_val;
}

int max_signed_value() {
    int max_value = 0;
    int test = 1;
    int *start = intlist;
    while ((test << 1) != 0 && (int)(test << 1) > 0) {
        test <<= 1;
	*intlist = test;
	++intlist;
    }
    setEnd(intlist, test, &max_value);
    intlist = start;
    return max_value;
}

void drawLine(bool breakk) {
    const int lengthLine = 20;
    char *arr = malloc((lengthLine + 1) * sizeof(char));
    if (!arr) return;
    for (int i = 0; i < lengthLine; ++i) {
        arr[i] = '-';
    }
    arr[lengthLine] = '\n';
    if (breakk) {
        printf("\n\033[31m%s\033[0m\n", arr);
    } else {
    	printf("\033[31m%s\033[0m\n", arr);
    }
    free(arr);
}

int main() {
    uintlist = malloc((MAX_COUNT + 1) * sizeof(unsigned int));
    intlist = malloc((MAX_COUNT + 1) * sizeof(int));
    drawLine(true);
    printf("Calculated max unsigned int: %u\n", max_unsigned_value());
    printf("Actual UINT_MAX: %u STORAGE: %d\n", UINT_MAX, sizeof(unsigned int));
    drawLine(false);
    printf("Calculated max signed int: %d\n", max_signed_value());
    printf("Actual INT_MAX: %d STORAGE: %d\n", INT_MAX, sizeof(int));
    drawLine(false);
    while (*uintlist != 0 && *(uintlist + 1) != 0) {
    	printf("%d, ", *uintlist);
	++uintlist;
    }
    drawLine(true);
    while (*intlist != 0 && *(intlist + 1) != 0) {
        printf("%d, ", *intlist);
        ++intlist;
    }
    drawLine(true);
    return 0;
}

