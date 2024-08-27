#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <limine.h>

struct terminal {
    struct limine_framebuffer *framebuffer;
    int start_x;
    int start_y;
    int cursor_x;
    int cursor_y;
    uint32_t color;
    int scale;
};

extern struct terminal term;

void terminal_init(struct limine_framebuffer *framebuffer, uint32_t color, int scale);
void terminal_edit(uint32_t color, int scale);
void terminal_write(const char *str);
void terminal_write_char(char c);
void terminal_event(char c);

#endif