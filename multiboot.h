#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#define MULTIBOOT2_HEADER_MAGIC 0xe85250d6
#define MULTIBOOT2_ARCHITECTURE 0
#define MULTIBOOT2_HEADER_LENGTH 24

struct multiboot_header {
    uint32_t magic;
    uint32_t architecture;
    uint32_t header_length;
    uint32_t checksum;
} __attribute__((packed));

static struct multiboot_header mb_header __attribute__((section(".multiboot2"))) = {
    .magic = MULTIBOOT2_HEADER_MAGIC,
    .architecture = 1, // 1 for 64-bit
    .header_length = MULTIBOOT2_HEADER_LENGTH,
    .checksum = -(MULTIBOOT2_HEADER_MAGIC + 1 + MULTIBOOT2_HEADER_LENGTH)
};

#endif