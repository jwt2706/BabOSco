#include "../include/terminal.h"
#include "../include/font.h"

void terminal_init(struct terminal *term, struct limine_framebuffer *framebuffer, uint32_t color, int scale) {
    term->framebuffer = framebuffer;
    term->cursor_x = 4;
    term->cursor_y = 4;
    term->color = color;
    term->scale = scale;
}

void terminal_edit(struct terminal *term, uint32_t color, int scale) {
    term->color = color;
    term->scale = scale;
}

/*
    This will basically just invoke terminal_write_char for each character in the string
    but take into account, special things like '\n' for new lines.
*/
void terminal_write(struct terminal *term, const char *str) {
    int start_x = term->cursor_x;
    int max_x = term->framebuffer->width - 8 * term->scale; // maximum x position before wrapping
    while (*str) {
        if (*str == '\n' || term->cursor_x > max_x) { // if the character is a newline or cursor exceeds max_x..
            term->cursor_y += 8 * term->scale; // ..offset y
            term->cursor_x = start_x; // ..and reset x
        }
        if (*str != '\n') {
            terminal_write_char(term, *str);
            term->cursor_x += 8 * term->scale; // offset x for each new character so they don't just print on top of each other
        }
        str++;
    }
    term->cursor_x = start_x;
}

/*
    This just writes one character to the terminal
    It looks up the right glyph to draw from the font array (see ../include/font.h)
*/
void terminal_write_char(struct terminal *term, char c) {
    if (c < 32 || c > 127) return; // only handle ASCII characters

    const uint8_t *glyph = font[c - 32]; // find the glyph for the character that we need to draw
    
    for (int i = 0; i < 8; i++) { // loop through each row and column of the glyph (8x8)       
        for (int j = 0; j < 8; j++) {
            
            // glyph[i] is a byte representing a row of the glyph
            // (1 << j) creates a mask to check the j-th bit of the byte
            // if the bit is set, the pixel should be drawn
            if (glyph[i] & (1 << j)) {
                
                // next, we need to scale each pixel according to the scale factor (if we want bigger text, for example)
                for (int dy = 0; dy < term->scale; dy++) { // vertical scale
                    for (int dx = 0; dx < term->scale; dx++) { // horizontal scale

                        // now that we know what we need to draw, we just calculate the position in the framebuffer
                        uint32_t *framebuffer_address = (uint32_t *)term->framebuffer->address;
                        int vertical_position = term->cursor_y + i * term->scale + dy;
                        int horizontal_position = term->cursor_x + j * term->scale + dx;
                        int pixels_per_row = term->framebuffer->pitch / 4; // convert pitch from bytes to number of 32-bit pixels per row

                        // and set the pixel color
                        framebuffer_address[vertical_position * pixels_per_row + horizontal_position] = term->color;
                    }
                }
            }
        }
    }
}

/*
    This handles special input stuff, like backspace, enter, etc.
*/
void terminal_event(struct terminal *term, char c) {
    if (c == '\b') {
        if (term->cursor_x > 0) {
            term->cursor_x -= 8 * term->scale;
            terminal_write_char(term, ' ');
        }
    } else {
        terminal_write_char(term, c);
    }
}