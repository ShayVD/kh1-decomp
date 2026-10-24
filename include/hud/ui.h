/* ttlib/ui.c (its asserts name the file; docs/modules.md "Session 47"):
 * src/hud/ui.c and ui.nostrict.c, 0x00249fb0-0x0024b0c8.  The sprite every
 * HUD part draws: a 0xC0-byte element with a rectangle, a texture
 * rectangle, four vertex colours and three keyframe tracks (a: one colour,
 * b: four colours, c: the rectangle), read from a sprite file
 * (func_0024aac8 fixes the tracks' offsets). */
#ifndef KH1_HUD_UI_H
#define KH1_HUD_UI_H

#include "common.h"

/* A key: its length in frames and four values (a colour or a rectangle). */
typedef struct { s32 dur; u8 pad4[0xc]; f32 v[4]; } UiKey;
/* A key of four colours (track b). */
typedef struct { s32 dur; u8 pad4[0xc]; f32 v[4][4]; } UiKey4;
/* A track: the time in its key, the key, the key count, the keys, its flags. */
typedef struct { s32 time; s32 idx; s32 n; UiKey *fr; u32 flags; } UiAnim;
typedef struct { s32 time; s32 idx; s32 n; UiKey4 *fr; u32 flags; } UiAnim4;

/* The flags at +0x60 are read both as a u64 (ld) and as a u32 (lw), hence
 * the union.  Bits: 2 / 8 track a (has / plays), 0x40 / 0x80 track b,
 * 4 / 0x10 track c, 0x20 the four colours (else m[0] for all).  Each
 * track's own flags: 2 playing, 4 at its end. */
typedef union {
    struct { u8 pad[0x60]; u64 flags; } h;
    struct {
        s32 r[4];       /* x, y, w, h */
        s32 t[4];       /* u0, v0, u1, v1 */
        s32 m[4][4];    /* the vertices' colours */
        u32 flags;
        UiAnim a;       /* +0x64 */
        UiAnim4 b;      /* +0x78 */
        UiAnim c;       /* +0x8C */
        u8 pad2[0x20];
    } s;
} UiSpr;

/* The GS packet of one sprite (func_0024a6b8): two tags, then the UVs, the
 * colours and the positions of four vertices. */
typedef struct {
    u64 unk0, unk8, unk10, unk18;
    s32 uv[4][4];
    s32 m[4][4];
    s32 xy[4][4];
} UiPkt;

#endif /* KH1_HUD_UI_H */
