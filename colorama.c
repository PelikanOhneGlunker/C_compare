#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void pri(uint64_t col, char *text);
void toStr(uint64_t value, char **hex_string);
void expandString(uint8_t nrOfChars, char c);
void drawEinruekung(uint8_t len);
void drawLine(uint8_t len);
void drawBr(uint8_t len);

void pri(uint64_t col, char *ptext) {
    uint8_t line = (col >> 60) & 0xFF;// 4Bit für linie zeichen
    uint8_t einr = (col >> 56) & 0xFF;// 4bit für einrückung
    uint8_t br_h = (col >> 48) & 0xFF;// 4bit <br> hinterher
    uint8_t br_v = (col >> 44) & 0xFF;// 4bit <br> davor
    uint8_t fg_r = (col >> 40) & 0xFF;// vordergrundfarben
    uint8_t fg_g = (col >> 32) & 0xFF;
    uint8_t fg_b = (col >> 24) & 0xFF;
    uint8_t bg_r = (col >> 16) & 0xFF;// hintergrundfarben
    uint8_t bg_g = (col >> 8)  & 0xFF;
    uint8_t bg_b = col         & 0xFF;
    drawBreaks(br_h);
    drawEinruekung(einr);
    printf("\033[38;2;%d;%d;%dm", fg_r, fg_g, fg_b);/*vordergrund*/
    printf("\033[48;2;%d;%d;%dm", bg_r, bg_g, bg_b);/*hintergrund*/
    drawLine(line);
    printf("%s", ptext);
    printf("\033[0m");                             /*reset color*/
    drawBreaks(br_h);
}

void toStr(uint64_t value, char **hex_string) {
    *hex_string = malloc(17);
    if (!*hex_string) return;
    sprintf(*hex_string, "%016llx", value);
}

void drawEinruekung(uint8_t len) {
    expandString(len, ' ');
}

void drawLine(uint8_t len) {
    expandString(len, '-');
}

void drawBr(uint8_t len) {
    expandString(len, '\n')
}

void expandString(uint8_t nrOfChars, char c) {
    uint8_t blockSize = (nrOfChars + 1) * sizeof(c);
    char *ptr = malloc(blockSize);
    for (uint8_t i = 0; i < nrOfChars; ++i) {
        *ptr = c;
	++ptr;
    }
    printf("%s", ptr);
    free(ptr);
}

int main() {
    uint64_t custom_color = 0xFFFFF00FF0000003;
    uint64_t green_shell  = 0xFFFFFF0FF0000223;
    uint64_t light_green  = 0xFFFFFF6FF6600333;
    uint64_t neon_green   = 0xFFF0000FF3300003;
    uint64_t custom_color = 0x000000CC99001122;
    uint64_t bitshifting  = (0x0000000000000000 >> 40) & 0xFF;
    char *list[8];
    list[0] = "This is a classic green shell style text!\0";
    list[1] = "This is a light green shell style text!\0";
    list[2] = "This is a neon green shell style text!\0";
    list[3] = "This is a custom color text!\0";
    list[4] = "This is a lightrue color, the colors may not display correctly. ons  in the format 0xRRGGBBRRGGBB (text c).\0";
    list[5] = "String changes with bitshifting. \n\0";
    list[6] = "This is a lightrue color, the colors may not dispn the format `0xRRGGBBRRGGBB` (text c) \n\0";
    list[7] = "Programm skippt int part and finished\n\0";

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
#endif
    return 0;
}

