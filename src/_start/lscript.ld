/* ENTRY POINT */
ENTRY(_start)


/* SEGMENTS */
PHDRS
{
	text PT_LOAD;
  	data PT_LOAD;
}

/* SECTIONS */
SECTIONS
{
	. = 0x00100000;
	/* Start up code and text */
	.text : ALIGN(4096) {
		_text_start = .;
			*(.text);
			*(.text.startup);
		_text_end = .;
	}: text
	
	/* Rodara section: read only data*/
	.rodata : ALIGN(4) {
		_data_start = .;
			*(.rodata)
			*(.rodata.*)
		_data_end = .;
	}: text
	
	/* Data section: read write only data */
	.data : ALIGN(4096) {
		_data_start = .;
			*(.data)
			*(.data.*)
		_data_end = .;
	}:data
	
	/* Uninitialized data section */
	.bss : ALIGN(4) {
		_bss_start = .;
			*(.bss)
			*(.bss.*)
			*(COMMON)
		_bss_end = .;
	}: data
}
