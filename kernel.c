void clear_screen() {
    char *video_memory = (char*) 0xB8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';    // Clear character
        video_memory[i + 1] = 0x07; // White color
    }
}

void print_string(char *message) {
    char *video_memory = (char*) 0xB8000;
    int i = 0;
    while (message[i]) {
        video_memory[i * 2] = message[i];  // Character
        video_memory[i * 2 + 1] = 0x07;    // Color attribute (white)
        i++;
    }
}

void kernel_main() {
    clear_screen();
    print_string("Welcome to MyOS!");
    while (1); // Infinite loop to keep the OS running
}
