#include <stdio.h>
#include <stdint.h>

void styled_printf(uint64_t col, const char *text) {
    uint8_t br_h = (col >> 42) & 0x1;
    uint8_t br_v = (col >> 41) & 0x1;
    if (br_v == 1) {
       printf("Bit was set: %d", br_v);
    } else {
       printf("Bit was not set: %d", br_v);
    }
    uint8_t fg_r = (col >> 40) & 0xFF;
    uint8_t fg_g = (col >> 32) & 0xFF;
    uint8_t fg_b = (col >> 24) & 0xFF;
    uint8_t bg_r = (col >> 16) & 0xFF;
    uint8_t bg_g = (col >> 8) & 0xFF;
    uint8_t bg_b = col & 0xFF;
    printf("\033[38;2;%d;%d;%dm", fg_r, fg_g, fg_b);/*vordergrund*/
    printf("\033[48;2;%d;%d;%dm", bg_r, bg_g, bg_b);/*hintergrund*/
    printf("%s", text);
    printf("\033[0m");/*reset color*/
}

int main() {
    // Example colors inspired by a green-themed shell editor
    // Format: 0x[Foreground RGB][Background RGB]
    uint64_t custom_color = NULL;
    // Green text on a dark background (classic shell-like)
    uint64_t green_shell = 0x1100FF00002222
    // Foreground: 0x00FF00 (Bright Green)
    // Background: 0x002222 (Dark Teal/Grayish)

    // Light green text on a darker background
    uint64_t light_green = 0x1166FF66003333
    // Foreground: 0x66FF66 (Light Green)
    // Background: 0x003333 (Very Dark Cyan)

    // Neon green text on black background
    uint64_t neon_green = 0x1100FF330000000
    // Foreground: 0x00FF33 (Neon Green)
    // Background: 0x000000 (Black)

    // Test the colors with styled_printf
    styled_printf(green_shell, "This is a classic green shell style text!\n");
    styled_printf(light_green, "This is a light green shell style text!\n");
    styled_printf(neon_green, "This is a neon green shell style text!\n");

    // Example of using a custom color
    custom_color = 0x00CC99001122;
    styled_printf(custom_color, "This is a custom color text!\n");
}

