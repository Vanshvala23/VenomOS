#include <stdint.h>

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

char *video_memory = (char *)VIDEO_MEMORY;
int cursor_pos = 0;

// Print a character to the screen
void print_char(char c, uint8_t color) {
    if (c == '\n') {
        cursor_pos += SCREEN_WIDTH - (cursor_pos % SCREEN_WIDTH);
    } else {
        video_memory[cursor_pos * 2] = c;
        video_memory[cursor_pos * 2 + 1] = color;
        cursor_pos++;
    }
}

// Print a string to the screen
void print(const char *str, uint8_t color) {
    while (*str) {
        print_char(*str++, color);
    }
}

// Clear the screen
void clear_screen() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07; // Light gray on black
    }
    cursor_pos = 0;
}

// Kernel Entry Point
extern "C" void kernel_main() {
    clear_screen();
    print("SimpleOS: Welcome to your terminal!\n", 0x07);

    while (1) {}
}
