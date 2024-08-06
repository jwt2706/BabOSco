section .multiboot2
align 8
    dd 0xe85250d6                                       ; magic number to make the kernel multiboot compliant
    dd 1                                                ; architecture type (0 = 32bit, 1 = 64bit)
    dd header_end - header_start                        ; header length
    dd -(0xe85250d6 + 1 + (header_end - header_start))  ; checksum to verify the integrity
header_start:
    ;
header_end: