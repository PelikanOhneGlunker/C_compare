#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define REQ_LEN 64

char *err = "only pass sha256sum strings";

int validate_input(const char *str) {
    if (!str) return 0;
    if ((int)strlen(str) != REQ_LEN) return 0;
    for (int i = 0; i < REQ_LEN; ++i) {
        char c = str[i];
        if (!( (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') )) return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <64-char-lowercase-or-digit-string> <64-char-lowercase-or-digit-string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *s1 = argv[1];
    const char *s2 = argv[2];
    printf(s1);
    printf("\n");
    printf(s2);
    printf("\n");
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

