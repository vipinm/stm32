ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx):ORIGIN =0x08000000,LENGTH =64K
    SRAM(rwx):ORIGIN =0x20000000,LENGTH =20K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector)
        *(.text)
        *(.init)
        *(.fini)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
        _etext = .;
    }> FLASH

    _la_data = LOADADDR(.data);
    .data :
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss :
    {
        __bss_start__ = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        __bss_end__ = .;
        . = ALIGN(4);
	end = .;
    }> SRAM
}
