#include <stdint.h>
#include "multiboot2.h"

void kernel(void) {

    char *video_memory = (char *) 0xb8000; // pointer to the starting address for the video memory in x86 archetecture

    // clear the screen (by putting spaces everywhere)
    for (int i=0; i<80*25*2; i+=2) { // 80 columns, 25 rows, 2 bytes per character
        video_memory[i] = ' '; // first byte is the ascii character
        video_memory[i+1] = 0x0f; // second byte is the color [0 = black (background), f = white (foreground)]
    }

    // write the message
    const char *message = "BabOSco booted successfully!";
    for (int i=0; message[i]!='\0'; i++) {
        video_memory[i*2] = message[i];
    }

    while (1); // infinite loop, just to keep the kernel alive
}