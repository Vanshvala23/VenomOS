void kernel_main() {
    char *video_memory = (char *)0xb8000;
    const char *message = "Hello from Simple OS!";
    int i = 0;
    
    while (message[i] != '\0') {
        video_memory[i * 2] = message[i];
        video_memory[i * 2 + 1] = 0x07; // White text on black
        i++;
    }

    while (1) {
        __asm__("hlt");
    }
}
