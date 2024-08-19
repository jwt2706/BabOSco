#include "../include/text.h"
#include "../include/font.h"

void draw_char(struct limine_framebuffer *framebuffer, char c, int x, int y, uint32_t color, int scale) {
    if (c < 32 || c > 127) return; // only handle ASCII characters

    const uint8_t *glyph = font[c - 32]; // find the glyph for the character that we need to draw
    
    for (int i = 0; i < 8; i++) { // loop through each row and column of the glyph (8x8)       
        for (int j = 0; j < 8; j++) {
            
            // glyph[i] is a byte representing a row of the glyph
            // (1 << j) creates a mask to check the j-th bit of the byte
            // if the bit is set, the pixel should be drawn
            if (glyph[i] & (1 << j)) {
                
                // next, we need to scale each pixel according to the scale factor (if we want bigger text, for example)
                for (int dy = 0; dy < scale; dy++) { // vertical scale
                    for (int dx = 0; dx < scale; dx++) { // horizontal scale

                        // now that we know what we need to draw, we just calculate the position in the framebuffer
                        uint32_t *framebuffer_address = (uint32_t *)framebuffer->address;
                        int vertical_position = y + i * scale + dy;
                        int horizontal_position = x + j * scale + dx;
                        int pixels_per_row = framebuffer->pitch / 4; // convert pitch from bytes to number of 32-bit pixels per row

                        // and set the pixel color
                        framebuffer_address[vertical_position * pixels_per_row + horizontal_position] = color;
                    }
                }
            }
        }
    }
}

void draw_string(struct limine_framebuffer *framebuffer, const char *str, int x, int y, uint32_t color, int scale) {
    int startX = x;
    while (*str) {
        if (*str == '\n') { // if the character is a newline..
            y += 8 * scale; // ..offset y
            x = startX; // ..and reset x
        } else {
            draw_char(framebuffer, *str, x, y, color, scale);
            x += 8 * scale; // offset x for each new character so they don't just print on top of each other
        }
        str++;
    }
}