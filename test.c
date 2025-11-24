#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *arr = malloc(4 * sizeof(int));
    arr[0] = 22;
    arr[1] = 23;
    arr[2] = 99;
    arr[3] = 101;
    int i;
    for (i = 0; i < 4; ++i, ++arr) {
	 if (*arr > 100) {
		break;
	} else {
		printf(" :: %d \n", *arr);
	}
    }
    printf("\n\nLAst %d\n", *arr);
    uint64_t col = 0xAABBCCDD11223344;
    uint64_t line = 0x0;
    printf("%llx\n", col);
    line = (col >> 56) & 0xFF;
    printf("%llx\n", line);
    line = (col >> 48) & 0xFF;
    printf("%llx\n", line);
    line = (col >> 40) & 0xFF;
    printf("%llx\n", line);
    line = (col >> 32) & 0xFF;
    printf("%llx\n", line);
    line = (col >> 24) & 0xFF;
    printf("%llx\n", line);
    line = (col >> 16) & 0xFF;
    printf("%llx\n", line);
    line = (col >> 8) & 0xFF;
    printf("%llx\n", line);
    line = (col >> 0) & 0xFF;
    printf("%llx\n", line);


    uint8_t *ptr = malloc(5 * sizeof(char));
    strcpy(ptr, "hihi");
    printf("ptr:%p\n", *ptr);
    printf("ptr:%s\n", ptr);
    printf("ptr:%p\n", &ptr);
    return 0;
}

