/* The gauges, 0x0023cfe8-0x00243168 (ttlib/ui_gauge.c: its assert names the
 * file and tt_gaugeWorldmap; docs/modules.md "Session 47"): src/hud/gauge.c
 * and its flag-mode siblings.  Five gauge slots in D_00651E50 (0 the
 * player's, 1 and 2 the party's, 3 one fed with f32 pointers, 4 the world
 * map's, read from tt_gaugeWorldmap D_00454A20); each slot is a 0xD00-byte
 * Gauge.  Field meanings are read from the code; none is proved by a boot. */
#ifndef KH1_HUD_GAUGE_H
#define KH1_HUD_GAUGE_H

#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h" /* QW */
#include "data/types/nostrict_text_00230000_b16.h"    /* GW: tt_gaugeWorldmap */
#include "data/pieces/D_004268B0.h"                   /* Tex_4268b0 */

/* A ui.c sprite object (0xC0 bytes: func_0024aa48 draws one, func_0024ae00
 * starts it, func_0024af00 steps it, +0x9C its flags). */
typedef struct { s32 v[48]; } __attribute__((aligned(8))) GSpr;

/* Three sprites played in turn by func_002409e0 (state unk250). */
typedef struct {
    GSpr *unk0;
    u8 pad4[0xC];
    GSpr unk10;
    GSpr unkD0;
    GSpr unk190;
    u32 unk250;
    s32 unk254;
    u8 pad258[0x260 - 0x258];
} GFade;

/* The actor's numbers the gauges read (+0x6C of the actor). */
typedef struct {
    u8 pad0[0x3C];
    s32 unk3C; /* the value of the round gauge (HP most likely) */
    s32 unk40; /* its maximum */
    s32 unk44; /* the value of the second gauge (MP most likely) */
    s32 unk48; /* its maximum */
    u8 pad4C[0xBE - 0x4C];
    u16 unkBE;
} GStat;
typedef struct { u8 pad[0x4C]; u16 unk4C; } GActor130;
/* A TIM2 picture (func_00242c08 / func_00242ef8: width, height, the CLUT,
 * the image). */
typedef struct { s32 w, h; u8 pad8[8]; u8 clut[0x400]; u8 img[1]; } GImg;
typedef struct {
    u8 pad0[0x6C];
    GStat *unk6C;
    u8 pad70[0x130 - 0x70];
    GActor130 *unk130;
    u8 pad134[0x140 - 0x134];
    GImg *unk140;
} GActor;

typedef struct {
    s32 unk0;           /* the kind: 0 the player, 1 / 2 the party, 3, 4 the world map */
    union {
        GActor *unk4;
        s32 unk4i;      /* func_00241b60 stores it as an s32 */
    };
    GSpr *unk8[7];      /* +0x08 the frame's sprites */
    s32 unk24;
    GSpr *unk28[4];     /* +0x28 */
    s32 unk38;
    GSpr *unk3C[2];     /* +0x3C */
    s32 unk44;
    GSpr *unk48[8];     /* +0x48 the bars' pieces */
    s32 unk68;
    Tex_4268b0 *unk6C;  /* +0x6C the textures */
    Tex_4268b0 *unk70;
    u8 pad74[0x80 - 0x74];
    s32 unk80[4];       /* +0x80 the centre (GS units) */
    s32 (*unk90)[4];    /* the bars' sizes (x, y, the width) */
    s32 unk94;
    s32 unk98;
    GSpr *unk9C;        /* the sprite playing (func_002407b0) */
    GSpr unkA0[6];
    GFade unk520;
    GFade unk780;
    s32 unk9E0;
    f32 unk9E4;
    f32 unk9E8;
    f32 unk9EC[4];      /* a fade (func_002492d0) */
    s32 unk9FC;
    f32 unkA00;
    f32 unkA04;
    f32 unkA08[4];      /* a fade (func_002492d0) */
    s32 unkA18;
    f32 unkA1C;         /* the alpha */
    f32 unkA20;         /* its step */
    s32 unkA24;
    s32 unkA28;
    s32 unkA2C;
    s32 unkA30;
    struct GaugeWm { GSpr *a[5]; GSpr *b; GSpr *c[4]; GSpr *d[5]; } unkA34; /* the world map's parts */
    u8 padA70[0xA84 - 0xA70];
    GSpr *unkA84;
    f32 *unkA88;        /* kind 3: the values it shows */
    f32 *unkA8C;
    f32 *unkA90;
    f32 *unkA94;
    u8 padA98[0xAA0 - 0xA98];
    GFade unkAA0;
} Gauge;

typedef struct {
    s32 used[8];
    Gauge ent[5];
    s32 unk4120;
    s32 unk4124;
    u8 pad4128[0x4130 - 0x4128];
} GaugeTbl;

#endif /* KH1_HUD_GAUGE_H */
