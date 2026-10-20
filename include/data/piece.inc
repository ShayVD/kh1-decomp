/* PIECE name, size, align: one data name as its own section (.data.<name>), the
 * original bytes cut from the user's ELF at build time (tools/shift/cut_pieces.py
 * writes out/data/pieces/<name>.bin; never committed). kh1tool link-script places it
 * at the address in its name; the shift build can float it (phase 4, step 4). */
	.macro PIECE name, size, align
	.section .data.\name, "aw", @progbits
	.balign \align
	.globl \name
	.type \name, @object
	.size \name, \size
\name:
	.incbin "out/data/pieces/\name\().bin"
	.if . - \name - (\size)
	.error "piece \name: out/data/pieces/\name\().bin is not \size bytes"
	.endif
	.endm
