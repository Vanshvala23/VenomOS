#include <stdint.h>
#include <stdbool.h>
#define MAX_INPUT_SIZE 100

// Functions from kernel.c
void print(const char *str, uint8_t color);
void clear_screen();
char get_key();

// Simple input buffer
void gets(char *buffer) {
    int i = 0;
    while (true) {
        char key = get_key();
        if (key == '\n') {
            buffer[i] = '\0';
            print("\n", 0x07);
            break;
        } else {
            buffer[i++] = key;
            print_char(key, 0x07);
        }
    }
}

// Display Help Menu
void print_help() {
    print("Available commands:\n", 0x07);
    print("  help    - Show this help message\n", 0x07);
    print("  clear   - Clear the screen\n", 0x07);
    print("  echo    - Print a message\n", 0x07);
    print("  exit    - Exit the system (simulated)\n", 0x07);
}

// Handle Input
void handle_command(char *input) {
    if (input[0] == '\0') return;

    if (strcmp(input, "help") == 0) {
        print_help();
    } else if (strcmp(input, "clear") == 0) {
        clear_screen();
    } else if (strncmp(input, "echo ", 5) == 0) {
        print(input + 5, 0x07);
        print("\n", 0x07);
    } else if (strcmp(input, "exit") == 0) {
        print("Shutting down...\n", 0x07);
        while (1) {}
    } else {
        print("Unknown command. Type 'help' for a list of commands.\n", 0x07);
    }
}

// Shell
void shell() {
    char input[MAX_INPUT_SIZE];
    while (1) {
        print("SimpleOS> ", 0x07);
        gets(input);
        handle_command(input);
    }
}
