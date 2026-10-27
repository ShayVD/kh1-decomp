#ifndef KH1_LANG_H
#define KH1_LANG_H
/* The community English patch (docs/english-patch.md): the functions it changes say KH1_EN where
 * the patched ELF differs.  The matching build has KH1_EN 0, so they compile as before;
 * KH1_EN_TARGET (make KH1_EN_TARGET=1) makes it 1 to check the English side against the patched
 * ELF; the port sets kh1_lang_en at boot when the disc holds that ELF (host/port/lang.c). */
#if defined(KH1_PS2)
#ifdef KH1_EN_TARGET
#define KH1_EN 1
#else
#define KH1_EN 0
#endif
#else
extern int kh1_lang_en;
#define KH1_EN kh1_lang_en
#endif

/* the font's glyph cell: 18 px, 24 in the English font (and its 16x stride, 0x120 / 0x180) */
#define KH1_GLYPH (KH1_EN ? 24 : 18)

/* an object the patch moved: `off` bytes into the data piece `piece` in English, the original
 * name `ja` otherwise (both in the same src/data/*.s file, so the port keeps their distance) */
#define KH1_EN_AT(piece, off, ja) (KH1_EN ? (void *)((u8 *)&(piece) + (off)) : (void *)&(ja))

#endif
