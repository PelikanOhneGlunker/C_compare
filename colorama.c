#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void pri(uint64_t col, char *text);
void styled_printf(uint64_t col, char *ptext);
void drawLine(uint8_t lengthLine);
void ruecken(uint8_t nrOfSpaces);
void toStr(uint64_t value, char **hex_string);

void styled_printf(uint64_t col, char *ptext) {
    uint8_t line = (col >> 54) & 0xFF;// 8Bit linie zeichen
    uint8_t einr = (col >> 46) & 0x0F;// 8bit für einrückung
    uint8_t br_h = (col >> 42) & 0x01;// <br> hinterher
    uint8_t br_v = (col >> 41) & 0x01;// <br> davor
    uint8_t fg_r = (col >> 40) & 0xFF;// vordergrundfarben
    uint8_t fg_g = (col >> 32) & 0xFF;
    uint8_t fg_b = (col >> 24) & 0xFF;
    uint8_t bg_r = (col >> 16) & 0xFF;// hintergrundfarben
    uint8_t bg_g = (col >> 8)  & 0xFF;
    uint8_t bg_b = col         & 0xFF;
    printf("\033[38;2;%d;%d;%dm", fg_r, fg_g, fg_b);/*vordergrund*/
    printf("\033[48;2;%d;%d;%dm", bg_r, bg_g, bg_b);/*hintergrund*/
    if (einr > 0) {
         ruecken(einr);
    }
    if (line > 0) {
        drawLine(line);
    }
    if (br_v > 1) {
        printf("\n");
    }
    printf("| %s", ptext);
    if (br_h == 1) {
    	printf("\n");
    }
    printf("\033[0m");/*reset color*/
}

void pri(uint64_t col, char *text) {
    styled_printf(col, text);
}

void drawLine(uint8_t lengthLine) {
    size_t lengthInByte = (lengthLine + 1) * sizeof(char);
    uintptr_t *arr = (uintptr_t*)malloc(lengthInByte);
    if (!arr) return;
    for (size_t i = 0; i < lengthInByte; ++i) {
        *arr = '-';
	++arr;
    }
    arr[lengthLine] = '\0';
    printf("%s", arr);
    free(arr);
}

void toStr(uint64_t value, char **hex_string) {
    *hex_string = malloc(17);
    if (!*hex_string) return;
    sprintf(*hex_string, "%016llx", value);
}

            // 48-56 bit %128 says
int main() {// 0x[veborX<br>orAfter][color_red, color_green, color_blue][bg_color_red, bg_color_green, bg_color_blue]
    uint64_t custom_color = 0xFFFFF00FF0000003;
    uint64_t green_shell  = 0xFFFFFF0FF0000223;
    uint64_t light_green  = 0xFFFFFF6FF6600333;
    uint64_t neon_green   = 0xFFF0000FF3300003;
    char *list[8];
    list[0] = "This is a classic green shell style text!\0";
    list[1] = "This is a light green shell style text!\0";
    list[2] = "This is a neon green shell style text!\0";
    list[3] = "This is a custom color text!\0";
    list[4] = "This is a lightrue color, the colors may not display correctly. ons  in the format 0xRRGGBBRRGGBB (text c).\0";
    list[5] = "String changes with bitshifting. \n\0";
    list[6] = "This is a lightrue color, the colors may not dispn the format `0xRRGGBBRRGGBB` (text c) \n\0";
    list[7] = "Programm skippt int part and finished\n\0";



    pri(green_shell, list[0]);
    pri(light_green, list[1]);
    pri(neon_green, list[2]);
    custom_color = 0x00CC99001122;
    pri(custom_color, list[3]);
    pri(0b10101011111100000000000000000, "ewrthzuewrhg###########");
    green_shell = 0x000FF00002203;
    light_green = 0x066FF66003303;
    neon_green  = 0x00FF330000003;
    pri(green_shell, "This is a classic green shell style text!\0");
    pri(light_green, "This is a light green shell style text!\0");
    pri(neon_green, "This is a neon green shell style text!\n");
    custom_color = 0x0FF;
    pri(custom_color, "This is a custom color text!\n");
    green_shell = 0xFFF000FF00002203;
    light_green = 0xFFF066FF66003303;
    neon_green  = 0xFFF00FF330000003;
    pri(green_shell, "This is a classic green shell style text!\n");
    pri(light_green, "This is a light green shell style text!\n");
    pri(neon_green, "This is a neon green shell style text!\n");
    uint64_t zahl = 0b10101010101010101010101010101010;
    pri(light_green, "This is a lightrue color, the colors may not display correctly. ons  in the format 0xRRGGBBRRGGBB (text c).\n");
    pri(0x0 | (0xFF << 4), "String changes with bitshifting. \n");
    styled_printf(zahl, "This is a lightrue color, the colors may not dispn the format `0xRRGGBBRRGGBB` (text c) \n");
    int i;
#ifdef INT_TEST
    for (i = 1; i < 64; i = i + 2) {
	if (((uint64_t)(0x1 >> i) | 0x0000000000000000) > 0xFFFFFFFFFFFFFFFF || (uint64_t)((0x0 >> i) & 0xFFFFFFFFFFFFFFFF) > 0xFFFFFFFFFFFFFFFF) {
	     continue;
	}
	uint64_t zz = (uint64_t)(0x1 >> i) | 0x0000000000000000;
	uint64_t dd = (uint64_t)(0x0 >> i) &  0xFFFFFFFFFFFFFFFF;
	char *ptr_zz;
	char *ptr_dd;
	toStr(zz, &ptr_zz);
	toStr(dd, &ptr_dd);
    	styled_printf(0xFFFF00000000FF00, ptr_zz);
	styled_printf(0x0008000000000000, ptr_dd);
    }
#else
    pri(0x000000AA2200, "Programm skippt int part and finished\n");
#endif
    return 0;
}

void ruecken(uint8_t nrOfSpaces) {
    char *arr = malloc((nrOfSpaces + 1) * sizeof(char));
    if (!arr) return;
        for (int i = 0; i < nrOfSpaces; ++i) {
        arr[i] = ' ';
    }
    printf("%s", arr);
    free(arr);
}

/*
  malloc()  → reserve only
  calloc()  → reserve + zero
  realloc() → resize, preserving old data, possibly moving it
**/
