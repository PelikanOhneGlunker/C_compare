#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main() {
void *mem = malloc((8 * sizeof(uint64_t)) + (8 * sizeof(char*)));
uint64_t *nums = (uint64_t*)mem;
char **strs = (char**)(nums + 8); // zeigt direkt hinter die 8 uint64_t
printf("nums: %p\n", (void*)nums);
printf("strs: %p\n", (void*)strs);

nums++; // verschiebt sich um 8 Bytes

printf("nums nach ++: %p\n", (void*)nums);
printf("strs bleibt: %p\n", (void*)strs);	

printf("%s", "-------------------------------");

return 0;
}


