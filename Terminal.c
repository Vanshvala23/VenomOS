#include <stdint.h>

#define MAX_INPUT_SIZE 100

void print(const char *str, uint8_t color);
void clear_screen();

void print_help() {
    print("Available commands:\n", 0x07);
    print("  help    - Display this help message\n", 0x07);
    print("  clear   - Clear the screen\n", 0x07);
    print("  exit    - Exit the terminal (simulation)\n", 0x07);
}

void handle_command(const char *input) {
    if (input[0] == '\0') return;
    if (strcmp(input, "help") == 0) {
        print_help();
    } else if (strcmp(input, "clear") == 0) {
        clear_screen();
    } else if (strcmp(input, "exit") == 0) {
        print("Exiting terminal...\n", 0x07);
        while (1) {} // Hang system (simulate exit)
    } else {
        print("Unknown command. Type 'help' for a list of commands.\n", 0x07);
    }
}

// Shell function
void shell() {
    char input[MAX_INPUT_SIZE];
    while (1) {
        print("SimpleOS> ", 0x07);
        gets(input);  // Implement `gets` to read from keyboard
        handle_command(input);
    }
}
