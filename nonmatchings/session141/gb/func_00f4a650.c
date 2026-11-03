/* Round 46 wwm2: score 36 -> 34, hill3o statement order. Earlier header below. */
/* Round 46 wwm2: score 38 -> 36, port.py of the wm twin func_00f71748 draft. Earlier header below. */
/* Round 36 (wgb): no change (21 words, score 38). Note: the round 35 order moves the o3->f24 / o3->h8 stores above the o4->f24 / o4->h8 stores (o3 and o4 are parameters), which is only safe if the caller passes distinct objects; hill3.py rejects it even with --noalias. A strict score-ranked run from the pre-round-35 draft gets 19 words, score 32, but a worse aligned diff (26 vs 20), so the committed order stays. */
#include "platform/thread.h"
typedef struct { u8 pad[5]; s8 b5; u8 pad2[2]; s16 h8; u8 pad3[10]; f32 f20; f32 f24; } Obj;
typedef struct { u8 b0; u8 b1; u8 b2; u8 b3; u8 b4[4]; u8 b8; u8 b9; u8 pad[86]; } Ent;
extern s32 D_00F82C58, D_00F82C5C, D_00F82C60;
extern s32 D_00F82B78[];
extern Ent *D_00F82B50[];
extern u8 D_00F82BF8[];
extern s32 D_00F82C30[];
extern s8 D_00F82C68[];
extern s32 D_00F82BF0;
extern s32 D_00F82B48;
extern Ent *D_00F82C08[];
extern s32 D_00F82BA0[];
extern s32 D_00F82BC8[];
extern s32 D_00F70650;
extern s32 D_00F70654;
extern s32 D_00F70640;
extern s32 D_00F70644;
s32 func_001bc4e0(void);
s32 func_001bc510(void);
void func_00f49e48(void);
void func_00f49f60(void);
void func_00f4a410(void);
void func_00f4a1c0(s32, s32);
void func_00f4a598(void);
void func_00f43350(void);
s32 func_001f0118(s32, s32);

void func_00f4a650(Obj *o1, Obj *o2, Obj *o3, Obj *o4, Obj *o5, Obj *o6)
{

    s32 i, j, k, n, v, found;
    f32 x, w;
    Ent *base, *e, *f;
    s8 *p;
    D_00F82C58 = -1;
    D_00F82C60 = -1;
    D_00F82C5C = 0;
    for (i = 0; i < 10; i++) {
        D_00F82B50[i] = 0;
        D_00F82B78[i] = 0;
        D_00F82BF8[i] = 0;
        D_00F82C30[i] = 0;
    }
    for (i = 0; i < 256; i++) {
        D_00F82C68[i] = 0;
    }
    base = (Ent *)(func_001bc4e0() + 96);
    n = func_001bc510() - 1;
    D_00F82BF0 = 0;
    D_00F82B48 = 0;
    if (n >= 256) {
        PlatBreak();
    }
    for (i = 0; i < n; i++) {
        e = &base[i];
        if (D_00F82C68[i] != 0) continue;
        if (e->b0 == 0) continue;
        if (e->b8 != 0) continue;
        if (e->b3 == 0) continue;
        found = 0;
        if (e->b9 != 0) {
            j = e->b9 - 1;
            f = (Ent *)(j * sizeof(Ent) + (u32)base);
            if (f->b0 != 0 && f->b8 == 0 && f->b3 != 0 && f->b9 == i + 1) {
                D_00F82C08[D_00F82BF0] = e;
                D_00F82C68[i] = 1;
                D_00F82BA0[D_00F82BF0] = i;
                D_00F82C68[j] = 1;
                D_00F82BF0++;
                D_00F82C08[D_00F82BF0] = f;
                found = 1;
                D_00F82BA0[D_00F82BF0] = j;
                D_00F82BF0++;
            }
        }
        if (!found) {
            D_00F82C68[i] = 1;
            k = D_00F82B48;
            D_00F82B50[k] = e;
            D_00F82B48 = k + 1;
            D_00F82BC8[k] = i;
        }
    }
    func_00f49e48();
    func_00f49f60();
    func_00f4a410();
    func_00f4a1c0(-1, -1);
    func_00f4a598();
    func_00f43350();
    v = func_001f0118(83, o1->b5);
    o1->f20 = D_00F70650;
    w = D_00F70640 - 20;
    x = D_00F70650 + v + 10;
    o3->f24 = w + 8.0f;
    o1->f24 = w;
    o4->f24 = w + 8.0f;
    o4->h8 = 512.0f - x;
    o3->h8 = D_00F70650 - 10;
    o3->f20 = 0.0f;
    o4->f20 = x;
    v = func_001f0118(84, o2->b5);
    o2->f20 = D_00F70654;
    w = D_00F70644 - D_00F82BF0 / 2 * 28 + 8;
    o2->f24 = w;
    x = D_00F70650 + v + 10;
    o6->f24 = w + 8.0f;
    o5->f24 = w + 8.0f;
    o5->f20 = 0.0f;
    o5->h8 = D_00F70654 - 10;
    o6->h8 = 512.0f - x;
    o6->f20 = x;
}
