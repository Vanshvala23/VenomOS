ENTRY(start32)

SECTIONS {
    . = 1M;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss) }
}
