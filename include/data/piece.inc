/* PIECE name, size, align: one data name as its own section (.data.<name>), the
 * original bytes cut from the user's ELF at build time (tools/shift/cut_pieces.py
 * writes out/data/pieces/<name>.bin; never committed). kh1tool link-script places it
 * at the address in its name; the shift build can float it (phase 4, step 4).
 *
 * A piece holding pointers (data_relocs.tsv rows) is written as
 *   PIECE_BEGIN name, size, align
 *   PIECE_BYTES name, off, len      (original bytes)
 *   .word sym+addend                 (a pointer: a relocation, so it follows its target)
 *   PIECE_END name, size
 * The section alignment must divide the size: MIPS gas pads a section to it.
 *
 * A piece that some user declares larger than the next name (a field named on its
 * own, tools/shift/merge_pieces.py) spans the whole object; each inner name is a
 * global label in it, so it moves with the object:
 *   PIECE_LABEL name, inner, off     (inner = name + off)  */
	.macro PIECE_BEGIN name, size, align
	.section .data.\name, "aw", @progbits
	.balign \align
	.align 0  /* no automatic alignment of .word: offsets are the original ones */
	.globl \name
	.type \name, @object
	.size \name, \size
\name:
	.endm

	.macro PIECE_BYTES name, off, len
	.incbin "out/data/pieces/\name\().bin", \off, \len
	.endm

	.macro PIECE_LABEL name, inner, off
	.if . - \name - (\off)
	.error "piece \name: label \inner not at offset \off"
	.endif
	.globl \inner
	.type \inner, @object
\inner:
	.endm

	.macro PIECE_END name, size
	.if . - \name - (\size)
	.error "piece \name: not \size bytes (out/data/pieces/\name\().bin cut wrong?)"
	.endif
	.endm

	.macro PIECE name, size, align
	PIECE_BEGIN \name, \size, \align
	.incbin "out/data/pieces/\name\().bin"
	PIECE_END \name, \size
	.endm
