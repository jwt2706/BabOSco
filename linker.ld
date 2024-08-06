OUTPUT_FORMAT(elf64-x86-64)
ENTRY(kernel)
SECTIONS
{
    . = 0x100000;
        
    .text :
    {
        *(.multiboot2)
        *(.text)
    }
    .rodata :
    {
        *(.rodata)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    }
}