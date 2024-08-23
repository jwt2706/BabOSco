#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <limine.h>

struct terminal {
    struct limine_framebuffer *framebuffer;
    int cursor_x;
    int cursor_y;
    uint32_t color;
    int scale;
};

void terminal_init(struct terminal *term, struct limine_framebuffer *framebuffer, uint32_t color, int scale);
void terminal_edit(struct terminal *term, uint32_t color, int scale);
void terminal_write(struct terminal *term, const char *str);
void terminal_write_char(struct terminal *term, char c);
void terminal_event(struct terminal *term, char c);

#endif