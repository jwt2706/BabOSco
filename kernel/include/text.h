#ifndef TEXT_H
#define TEXT_H

#include <stdint.h>
#include <limine.h>

void draw_char(struct limine_framebuffer *framebuffer, char c, int x, int y, uint32_t color, int scale);
void draw_string(struct limine_framebuffer *framebuffer, const char *str, int x, int y, uint32_t color, int scale);

#endif