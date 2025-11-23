#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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
}

