/* The notice (docs/modules.md "Session 46"), nostrict part.  func_002436c0
 * draws the notice shown (drawing environment D_00655F80, buffer at
 * D_00351E10): state 1 starts it (sound 31 unless kind 2), 2 holds it for 60
 * frames (20 when another is queued), 3 / 4 fade it out by 1/7 a frame until
 * its sprite set's animation ends (bit 4 of +0x9C), 5 ends it.
 * func_00243508 draws a sprite set (seven sprites of one texture, two of
 * another) and the name of id; func_002432d8 sends one sprite moved by
 * (x, y) through D_006560F0. */
#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h" /* QW */
#include "data/pieces/D_004267F0.h"
#include "data/pieces/D_004267C0.h"

typedef struct { s32 x, y, z, w; } I4;
typedef struct { u8 pad[0x60]; I4 c[4]; I4 p[4]; } Pkt;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
typedef struct { u8 pad[0x9C]; s32 unk9C; } Gm;
typedef struct { s32 mode; s32 unk8; f32 unkC; } Sub;
typedef struct {
    s32 state;
    Sub sub;
    s32 cnt;
} S61D0;

extern Gm *D_00656230;
Gm *D_00656254 ALIGNED(4);
Gm *D_00656278 ALIGNED(8);
Gm *D_0065629C ALIGNED(4);
extern S61D0 D_006561D0;
Q D_00655F80 ALIGNED(64);
QW *D_006560E4 ALIGNED(4);
Pkt D_006560F0 ALIGNED(16);
extern QW *D_006560E0; /* src/data/bss_0065.c: s32 D_006560E0 */
extern QW D_00351E10[];
void func_002370c8(Q *);
void func_00237018(void *, s32, s32);
void func_0011d768(s32);
void func_0024aa48(s32, Pkt *, s32);
s32 func_002388b8(Pkt *, s32, s32);
void func_00243380(s32, u8 *, void *, s32, s32);
u16 *func_00147840(s32);
s32 func_00147808(u16);
void func_0024ac08(u8 *, s32 *);
void func_002433e8(s32, s32, s32, s32, f32);

void func_002432d8(s32 a0, s32 a1, s32 x, s32 y) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_006560F0, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_006560F0.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    D_006560E0 = (QW *)func_002388b8(&D_006560F0, 1, (s32)D_006560E0);
}

void func_00243508(s32 a0, u8 *p, void *c0, void *c1, s32 x, s32 y, s32 id, s32 k, f32 f) {
    s32 i;
    u8 *q = p;
    s32 v;
    s32 d[4];
    for (i = 0; i < 7; i++) {
        func_00243380(a0, p, c0, x, y);
        p += 0xC0;
    }
    for (i = 0; i < 2; i++) {
        func_00243380(a0, p, c1, x, y);
        p += 0xC0;
    }
    if (id != 0) {
        v = func_00147808(*func_00147840(id));
        func_0024ac08(q, d);
        func_002433e8(x + d[0], y + d[1], v, k, f);
    }
}

void func_002436c0(s32 arg) {
    s32 f2 = 0, f3 = 0;
    Sub *g = 0;
    if (D_006561D0.state == 0) return;
    func_002370c8(&D_00655F80);
    D_00655F80.unkE0 = 5;
    D_00655F80.unk60 = 0x30003;
    func_00237018(&D_00655F80, 22, 1);
    D_006560E4 = D_00351E10;
    D_006560E0 = D_00351E10 + 1;
    switch (D_006561D0.state) {
    case 1:
        f2 = 1;
        D_006561D0.state = 2;
        if (D_006561D0.sub.mode != 2) func_0011d768(31);
        break;
    case 2:
        break;
    case 3:
        D_006561D0.state = 4;
        f3 = 1;
        break;
    }
    g = &D_006561D0.sub;
    switch (g->mode) {
    case 0:
        if (D_006561D0.state == 2) func_00243508(f2, (u8 *)D_00656230, D_004267C0, D_004267F0, 160, 344, g->unk8, 0, g->unkC);
        else func_00243508(f3, (u8 *)D_00656278, D_004267C0, D_004267F0, 160, 344, g->unk8, 0, g->unkC);
        break;
    case 1:
        if (D_006561D0.state == 2) func_00243508(f2, (u8 *)D_00656230, D_004267C0, D_004267F0, 160, 344, g->unk8, 0, g->unkC);
        else func_00243508(f3, (u8 *)D_0065629C, D_004267C0, D_004267F0, 160, 344, g->unk8, 0, g->unkC);
        break;
    case 2:
        func_00243508(f2, (u8 *)D_00656254, D_004267C0, D_004267F0, 160, 344, g->unk8, 1, g->unkC);
        break;
    }
    if (D_006561D0.state == 2) {
        D_006561D0.cnt++;
        if (D_006561D0.cnt >= 61 || (arg && D_006561D0.cnt >= 21)) D_006561D0.state = 3;
    }
    func_00237018(D_006560E4, D_006560E0 - D_006560E4, 1);
    if (D_006561D0.state == 4) {
        g->unkC -= 0.1428571381f;
        if (g->unkC < 0.0f) g->unkC = 0.0f;
        switch (D_006561D0.sub.mode) {
        case 0:
            if (D_00656278->unk9C & 4) D_006561D0.state++;
            break;
        case 1:
            if (D_0065629C->unk9C & 4) D_006561D0.state++;
            break;
        case 2:
            D_006561D0.state++;
            break;
        }
    }
    if (D_006561D0.state == 5) D_006561D0.state = 0;
}
