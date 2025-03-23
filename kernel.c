#include <stdint.h>

// Video memory and screen size
#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

char *video_memory = (char *)VIDEO_MEMORY;
int cursor_pos = 0;

// Function to print a character
void print_char(char c, uint8_t color) {
    if (c == '\n') {
        cursor_pos += SCREEN_WIDTH - (cursor_pos % SCREEN_WIDTH);
    } else {
        video_memory[cursor_pos * 2] = c;
        video_memory[cursor_pos * 2 + 1] = color;
        cursor_pos++;
    }
}

// Function to print a string
void print(const char *str, uint8_t color) {
    while (*str) {
        print_char(*str++, color);
    }
}

// Function to clear the screen
void clear_screen() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07; // Light gray on black
    }
    cursor_pos = 0;
}

// External function from terminal.c
void shell();

// Kernel Entry Point
void kernel_main() {
    clear_screen();
    print("Welcome to SimpleOS!\nType 'help' for commands.\n\n", 0x07);
    shell();
}
