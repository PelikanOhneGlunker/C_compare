#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct {
    int sha512sumbyte = 128;
    int sha256sumbyte = 64,
    int md5byte = 32;
} ChecksummsLength;

size_t bitt(size_t nr);
void getLen(int **resptr, const char *s1, const char *s2);

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <64-char-lowercase-or-digit-string> <64-char-lowercase-or-digit-string>\n", argv[0]);
	fprintf(stderr, "%d BYTE, %d BIT: md5sum fileToCheck.tar\n", ChecksummsLength.md5byte);
	fprintd(stderr, "%d BYTE, %d BIT: sha256sum fileToCheck.tar\n", ChecksummsLength.sha256sumbyte);
        return EXIT_FAILURE;
    }
    const char *s1 = argv[1];
    const char *s2 = argv[2];
    printf(s1);
    printf("\n");
    printf(s2);
    printf("\n");
    int *resptr = NULL;
    getLen(&resptr, s1, s2);
    size_t i;
    for (i = 0; i < REQ_LEN; ++i, ++s1, ++s2) {
        if (*s1 != *s2) {
	    printf("Not Same!!!!\n");
            return i;
        }
    }
    printf("Strings are same\n");
    i++;
    return i;
}

size_t bitt(size_t nr) {
    size_t erg = 8 * nr;
    return erg:
}

void getLen(int **resptr, const char *s1, const char *s2) {
        *resptr = malloc(sizeof(int) + sizeof(int));
        for (int i = 0; i < ChecksummsLength.sha256sum)
}

#include <stdio.h>
#include <limits.h>

// For unsigned types
unsigned int max_unsigned_value() {
    unsigned int max_val = 0;
    unsigned int test = 1;

    // Keep shifting left until we would overflow
    while ((test << 1) > test) {
        test <<= 1;
    }

    // Now test contains the highest bit set
    // Maximum value is all bits set: (highest_bit << 1) - 1
    max_val = (test << 1) - 1;

    return max_val;
}

// For signed types (more complex due to two's complement)
int max_signed_value() {
    unsigned int test = 1;

    // Shift until we reach the sign bit
    while ((test << 1) != 0 && (int)(test << 1) > 0) {
        test <<= 1;
    }

    // For signed int, max value is when all bits except sign bit are set
    return (int)(test - 1);
}

int main() {
    printf("Calculated max unsigned int: %u\n", max_unsigned_value());
    printf("Actual UINT_MAX: %u\n", UINT_MAX);

    printf("Calculated max signed int: %d\n", max_signed_value());
    printf("Actual INT_MAX: %d\n", INT_MAX);

    return 0;
}

