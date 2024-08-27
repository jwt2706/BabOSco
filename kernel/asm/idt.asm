; This is just the assembly refrence for the load_idt function. It's actually done with inline assembly in "../src/drivers/idt.c"

section .text
global load_idt

load_idt:
    lidt [rdi]
    ret