ENTRY(kernel_main)

SECTIONS {
    . = 1M; /* Load kernel at 1MB */
    .text : { *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}
