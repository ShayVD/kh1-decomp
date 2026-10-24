/* The party members' AI, default flags (docs/modules.md "Session 51"): the
 * setup functions of the eight party member kinds (func_00172010,
 * func_00172d90, func_00173740 ... func_00174d98: each sets the member's
 * action table D_0035BD50 / D_0035BE50 / D_0035BFC0 ... of 16-byte records
 * {condition, flags, handler, 0}; the table of setups is D_0035BC80 in
 * partyai.nostrict.c) and part of their action handlers; the helpers the
 * handlers share: a 2-bit setting per member (func_00170d60 / 00170dd8),
 * the timed callbacks list D_00575780 (func_00170f50), the motion test
 * (func_00170f90) and change (func_00170fa8), the action flag bits
 * D_00575788 (func_00171a88), a random value in a range (func_00171aa8), the
 * target tests (func_00171ae8, an inline definition func_00171b18 inlines),
 * and stubs.  partyai.nostrict.c has the AI's start for a member
 * (func_00170400), the steering and action selection, and most handlers.
 * The module also covers the 0x0016 code the tables name (func_0016b670 ...),
 * still in src/hand.  Each section names the file its code came from.  Read
 * from the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002BBDF8.h"
#include "m2c.h"
#include "data/bss_0057.h"
#include "data/pieces/D_0035BD40.h"
#include "data/pieces/D_003626C0.h"
#include "data/types/text_00170000_h38.h"
#include "data/types/text_00170000_h38_p.h"

/* func_00170d60 (from hand/text_00150000_h10.c). */
u32 *func_00232cc0(s32);
void func_00170d60(s32 a, s32 b, s32 c) {
    u32 *p = &func_00232cc0(6)[a];
    *p = (*p & ~(3LL << (b * 2))) | (c << (b * 2));
}

/* func_00170dd8 (from auto/text_00170000_10.c). */
#define func_00232cc0 ((s32 (*)(M2C_UNK)) func_00232cc0)
s32 func_00170dd8(s32 arg0, s32 arg1) {
    s32 var_v0;
    u32 *temp_a0;

    temp_a0 = func_00232cc0(6) + (arg0 * 4);
    var_v0 = -1;
    if (arg1 == -1) {
        return var_v0;
    }
    var_v0 = ((u32) *temp_a0 >> (arg1 * 2)) & 3;
    return var_v0;
}
#undef func_00232cc0

/* func_00170e30 (from auto/text_00170000_2.c). */
s32 func_00170e30(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_00574FB4;
    D_00574FB4 = arg0;
    return temp_v0;
}

/* func_00170e48 (from auto/text_00170000_10.c). */
void func_00121eb0(s32);
void func_0016f3d0(s32, s32);
void func_00170e48(s32 arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x144);
    func_0016f3d0(arg0, temp_s0);
    *(M2C_UNK *)((s8 *)(s8 *)&D_0035BD40.i + (*(M2C_UNK *)temp_s0 * 4)) = 0;
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x144));
}

/* func_00170e98 (from auto/text_00170000_8.c). */
M2C_UNK func_00122768(s32);
M2C_UNK func_001386f8(s32);
M2C_UNK func_0016f548();
extern M2C_UNK D_00575010;
extern s32 D_00575310;
void func_00170e98(void) {
    s32 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s0 = &D_00575310;
    var_s1 = 2;
    do {
        temp_a0 = *var_s0;
        var_s1 -= 1;
        if (temp_a0 != 0) {
            func_00122768(temp_a0);
            *var_s0 = 0;
        }
        var_s0 += 2;
    } while (var_s1 >= 0);
    func_0016f548();
    func_001386f8(M2C_FIELD(&D_00575010, s32 *, 0));
    func_001386f8(M2C_FIELD(&D_00575010, s32 *, 4));
}

/* func_00170f08 (from hand/text_00150000_h10.c). */
typedef struct Node70 { s32 id; s32 w4; s32 w8; s32 wC; struct Node70 *next; } Node70;
extern Node70 *D_00575780;
s32 func_00170f08(void *a, s32 *key, s32 v) {
    Node70 *n;
    s32 cnt = 0;
    for (n = D_00575780; n != 0; n = n->next) {
        if (n->id == *key && n->w8 == v) cnt++;
    }
    return cnt;
}

/* func_00170f50 (from auto/text_00170000_4.c). */
extern void *D_00575784;
#ifdef KH1_PS2 /* the lvalue form changes this match */
#define D_00575780 ((void *) D_00575780)
#else
#define D_00575780 (*(void **)&D_00575780)
#endif
void func_00170f50(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_v0;

    temp_v0 = D_00575784;
    D_00575784 = M2C_FIELD(temp_v0, void **, 0x10);
    M2C_FIELD(temp_v0, s32 *, 0) = (s32) *arg1;
    M2C_FIELD(temp_v0, s32 *, 8) = arg2;
    M2C_FIELD(temp_v0, s32 *, 4) = arg3;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg4;
    M2C_FIELD(temp_v0, void **, 0x10) = (void *) D_00575780;
    D_00575780 = temp_v0;
}
#undef D_00575780

/* func_00170f90 (from auto/text_00170000_2.c). */
s32 func_00170f90(void *arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x4C) == M2C_FIELD(arg0, s32 *, 0x164);
}

/* func_00170fa8 (from auto/text_00170000_10.c). */
f32 func_001224c8(s32, s32, s32, f32);
s32 func_001226f0(s32, s32, s32);
#define D_00575310 (*(M2C_UNK (*)) &D_00575310)
void func_00170fa8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    if ((*(M2C_UNK *)((s32) ((*(M2C_UNK *)arg1 * 8)) + (s32) &D_00575310) != 0) || (*(M2C_UNK *)((s32) ((*(M2C_UNK *)arg1 * 8)) + (s32) &D_00575310) = func_001226f0(1, 9, 0xA), (*(M2C_UNK *)((s32) ((*(M2C_UNK *)arg1 * 8)) + (s32) &D_00575310) != 0))) {
        func_001224c8(*(M2C_UNK *)((s32) ((*(M2C_UNK *)arg1 * 8)) + (s32) &D_00575310), arg3, 0, fparg0);
        M2C_FIELD(((s8 *)&D_00575310 + (*(M2C_UNK *)arg1 * 8)), s32 *, 4) = arg2;
    }
}
#undef D_00575310

/* func_00171078 (from hand/text_00170000_s9_w9.c). */
/* func_00171078: the table is read through a hard-coded address, not the
   D_0035BD40 symbol. gcc emits `lw $2,3521856($3)`; gas expands the large
   constant offset itself (lui v0; addu v0,v0,v1; lw v0,lo(v0)) and, since the
   last insn carries no relocation, moves it into the empty `j $31` slot. With
   the symbol the %lo fixup stops gas from filling the slot (nop).
   KH1_SHIFTABLE (the shiftable build, tools/shift/variants.py): use the
   symbol so the table can move; 4 bytes longer (the nop), which still fits
   before func_00171098. */
s32 func_00171078(s32 a, s32 *b) {
#ifdef KH1_SHIFTABLE
    return D_0035BD40.i_2[*b ^ 3];
#else
    return ((s32 *)0x35BD40)[*b ^ 3];
#endif
}

/* func_00171098 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x3C]; s32 w3C, w40, w44, w48; } Stat6C;
typedef struct { u32 flags; u8 pad[0x68]; Stat6C *p6C; } Obj710;
s32 func_00171098(Obj710 *o, u8 pct) {
    if (o->flags & 0x200) return 0;
    if (o->p6C->w40 * pct < o->p6C->w3C * 255) return 0;
    return 1;
}

/* func_001710d8 (from hand/text_00150000_h10.c). */
s32 func_001710d8(Obj710 *o, u8 pct) {
    if (o->flags & 0x200) return 0;
    if (o->p6C->w48 * pct < o->p6C->w44 * 255) return 0;
    return 1;
}

/* func_00171460 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x70]; s32 w70; } Obj714;
void func_0013dfb8(void *, void *);
void func_00171460(Obj714 *o, u8 *b) {
    if (o->w70 != 2) func_0013dfb8(o, b + 0x120);
}

/* func_00171498 (from hand/text_00150000_h10.c). */
s32 func_00133000(void *, s32);
s32 func_00171498(Obj714 *o, s32 b) {
    switch (o->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(o, b)) return 1;
        break;
    }
    return 0;
}

/* func_00171890 (from auto/text_00170000_4.c). */
s32 func_00171890(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 3) || (var_v0 = 1, (arg2 < 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

/* func_001718b8 (from auto/text_00170000_4.c). */
s32 func_001718b8(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0x7C) || (var_v0 = 1, ((arg2 < 0x75) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

/* func_001718e0 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x4C]; s32 w4C; } Obj718;
s32 func_001718e0(void *a, Obj718 *b, s32 v) {
    s32 w = v;
    if (v >= 0 && (v < 3 || (v < 131 && w >= 124))) return 1;
    return v == b->w4C;
}

/* func_00171920 (from auto/text_00170000_4.c). */
s32 func_00171920(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0x31) || (var_v0 = 1, ((arg2 < 0x2D) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

/* func_00171948 (from auto/text_00170000_4.c). */
s32 func_00171948(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0xD) || (var_v0 = 1, ((arg2 < 3) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

/* func_00171a88 (from hand/text_00170000.c). */
extern u8 D_00575788[];
s32 func_00171a88(s32 arg0, s32 arg1, s32 bit) {
    return ((u32) D_00575788[bit >> 3] >> (bit & 7)) & 1;
}

/* func_00171aa8 (from auto/text_00170000.c). */
f32 func_001629e8();
f32 func_00171aa8(f32 fparg0, f32 fparg1) {
    return fparg0 + (func_001629e8() * (fparg1 - fparg0));
}

/* func_00171ae8 (from hand/text_00150000_h10.c). */
typedef struct { u64 flags; } Tgt71B;
typedef struct { u8 pad[0x3C]; Tgt71B **p3C; union { Tgt71B *p; u64 d; } p40; } Obj71A;
inline s32 func_00171ae8(void *a, Obj71A *o) {
    if (o->p3C && o->p40.p) {
        if (*o->p3C == o->p40.p) return 1;
    }
    return 0;
}

/* func_00171b18 (from hand/text_00150000_h10.c). */
void func_00171b18(void *a, Obj71A *o) {
    if (func_00171ae8(a, o)) {
        o->p40.p->flags &= ~0x100;
        o->p40.p->flags &= ~0xC;
    }
    o->p3C = 0;
    o->p40.p = 0;
}

/* func_00171e90 (from auto/text_00170000_4.c). */
void func_00171e90(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) | 0x10);
}

/* func_00171ea8 (from auto/text_00170000_4.c). */
void func_00171ea8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) & ~0x10);
}

/* func_00171ec0 (from auto/text_00170000_4.c). */
void func_00171ec0(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) | 0x20);
}

/* func_00171ed8 (from auto/text_00170000_4.c). */
void func_00171ed8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) & ~0x20);
}

/* func_00171ef0 (from auto/text_00170000_10.c). */
s32 func_00153d78();
s32 func_00171ef0(s32 *arg0) {
    s32 var_v0;

    var_v0 = func_00153d78();
    if (!((var_v0 != 0) || (*arg0 & 0x200))) {
        return var_v0;
    }
    var_v0 = 1;
    return var_v0;
}

/* func_00171f30 (from auto/text_00170000_2.c). */
s32 func_00171f30(void) {
    return 0;
}

/* func_00171f38 (from auto/text_00170000_2.c). */
void func_00171f38(s32 arg0, s32 *arg1) {
    if ((arg1 != NULL) && (*arg1 == arg0)) {
        *arg1 = 0;
    }
}

/* func_00171f58 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x18]; f32 f18; f32 x, y, z; u8 pad28[0x20]; s16 h48; u8 pad4a[2]; u16 h4C; } Sub130;
typedef union { u64 d; } Flg64;
typedef struct { u8 pad[0x34]; f32 f34; Flg64 f38; u8 pad40[0xC]; s32 w4C; u8 pad50[8]; s32 w58; u8 pad5c[4]; s32 w60; } Sub144;
typedef struct { u8 pad[0x130]; Sub130 *p130; u8 pad134[0x10]; Sub144 *p144; u8 pad148[0x1C]; s32 w164; } Obj71F;
void func_00171f58(Obj71F *o) {
    Sub144 *s = o->p144;
    if ((s32)(s->f38.d >> 6) & 1) {
        o->p130->f18 = s->f34;
        s->f38.d &= ~0x40;
    }
    s->w58 = 0;
    s->w60 = 0;
}

/* func_00171fa0 (from hand/text_00150000_h10.c). */
void func_00171fa0(Obj71F *o) {
    if ((u16)(o->p130->h4C - 1) < 2) {
        Sub144 *s = o->p144;
        s32 save = s->w4C;
        s32 r, v, w;
        s->w4C = -1;
        v = o->w164;
        w = v;
        if (w < 3 && v >= 0) r = 1;
        else r = v == s->w4C;
        if (r) s->f38.d |= 0x100;
        s->w4C = save;
    }
}

/* func_00172010 (from auto/text_00170000_4.c). */
extern M2C_UNK D_0035BD50;
void func_00172010(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xF;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BD50;
}

/* func_00172d90 (from auto/text_00170000_7.c). */
extern M2C_UNK D_0035BE50;
void func_0014f828();
void func_00172028();
void func_001732b0();
void func_00173360();
void func_00173478();
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
void func_00172d90(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0x17;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BE50;
    func_0014f830(0x32, 2, &func_00172028, &func_001732b0, &func_00173360, &func_00173478, &func_0014f828, 0, 0);
}

/* func_001732b0 (from auto/text_00170000_4.c). */
s32 func_00130340(s32, s32, f32);
void func_001732b0(s32 arg0) {
    s32 temp_v1;
    s32 temp_v1_2;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x144);
    if (M2C_FIELD(arg0, s32 *, 0x70) == 8) {
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x164);
        if ((temp_v1 == 0xCE) || (temp_v1 == M2C_FIELD(temp_s0, s32 *, 0x4C))) {
            func_00130340(arg0, 0x40000075, 8.0f);
        }
    } else {
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x164);
        if ((temp_v1_2 == 0xCE) || (temp_v1_2 == M2C_FIELD(temp_s0, s32 *, 0x4C))) {
            func_00130340(arg0, M2C_FIELD(temp_s0, s32 *, 0x178), 8.0f);
        }
    }
    M2C_FIELD(temp_s0, s64 *, 0x38) = (s64) ((M2C_FIELD(temp_s0, s64 *, 0x38) & ~0x800) | 0x20000);
}

/* func_00173718 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x164]; s32 w164; } Obj737;
s32 func_00173718(Obj737 *o) {
    s32 v = o->w164;
    if (v == 63 || v == 140) return 1;
    return 0;
}

/* func_00173740 (from auto/text_00170000_4.c). */
extern M2C_UNK D_0035BFC0;
void func_00173740(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xC;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BFC0;
}

/* func_00173ad8 (from auto/text_00170000_4.c). */
extern M2C_UNK D_0035C090;
void func_00173ad8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xA;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C090;
}

/* func_00173ea8 (from auto/text_00170000_4.c). */
extern M2C_UNK D_0035C140;
void func_00173ea8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xA;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C140;
}

/* func_00174398 (from auto/text_00170000_4.c). */
extern M2C_UNK D_0035C1F0;
void func_00174398(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xC;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C1F0;
}

/* func_001743b0 (from hand/text_00170000_h38.c). */
typedef struct Prm {
    s32 x0;         /* 0x00 */
    u8 pad4[0x10];
    f32 x14;        /* 0x14 */
    f32 x18;        /* 0x18 */
    f32 x1c;        /* 0x1C */
    f32 x20;        /* 0x20 */
} Prm;
typedef struct { u8 pad[0xc]; Prm *xc; } P160;
typedef struct { u8 pad[0x50]; f32 x50; } P40;
typedef struct Ob {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x68 - 0x50];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x160 - 0x6c];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob;
typedef struct Wk {
    u8 pad0[0x144];
    Ob *x144;       /* 0x144 */
} Wk;
extern u8 D_0035C2B0[];
void func_00148a40(Wk *, s32);
s32 func_0016b670(Wk *, Ob *, s32, s32);
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
#define func_00170f90 ((void (*)(void)) func_00170f90)
#define func_00170fa8 ((void (*)(Wk *, Ob *, void *, void *, f32)) func_00170fa8)
s32 func_001743b0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 39)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C2B0, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_00170f90
#undef func_00170fa8

/* func_001744b8 (from hand/text_00170000_h38.c). */
s32 func_0016c480(Wk *, Ob *, s32, s32);
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
s32 func_001744b8(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 40)) return 0;
        return func_0016c480(w, o, a2, 1);
    case 2:
        func_0016c480(w, o, a2, a3);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_00174570 (from hand/text_00170000_h38.c). */
s32 func_0016c650(Wk *, Ob *, s32, s32);
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
s32 func_00174570(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 41)) return 0;
        return func_0016c650(w, o, a2, 1);
    case 2:
        func_0016c650(w, o, a2, a3);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_00174628 (from hand/text_00170000_h38.c). */
s32 func_0016cb98(Wk *, Ob *, s32, s32);
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
s32 func_00174628(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 42)) return 0;
        return func_0016cb98(w, o, a2, 1);
    case 2:
        func_0016cb98(w, o, a2, a3);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_001746e0 (from hand/text_00170000_h38.c). */
s32 func_0016d040(Wk *, Ob *, s32, s32);
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
s32 func_001746e0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 43)) return 0;
        return func_0016d040(w, o, a2, 1);
    case 2:
        func_0016d040(w, o, a2, a3);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_00174950 (from auto/text_00170000_4.c). */
extern M2C_UNK D_0035C2C0;
void func_00174950(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 9;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C2C0;
}

/* func_00174968 (from hand/text_00170000_h38.c). */
s32 func_0016d2d0(Wk *, Ob *, s32, s32);
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
s32 func_00174968(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 45)) return 0;
        return func_0016d2d0(w, o, a2, 1);
    case 2:
        func_0016d2d0(w, o, a2, a3);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_00174a20 (from hand/text_00170000_h38.c). */
s32 func_0016d768(Wk *, Ob *, s32, s32);
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
s32 func_00174a20(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 46)) return 0;
        return func_0016d768(w, o, a2, 1);
    case 2:
        func_0016d768(w, o, a2, a3);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_00174ad8 (from hand/text_00170000_h38.c). */
s16 *func_00171b80(Wk *, Ob *, s32);
/* func_00171ae8 is an inline definition above (func_00171b18 inlines it);
 * the original calls it here: an alias gcc cannot see through */
s32 func_00171ae8_74ad8(Wk *, Ob *) __asm__("func_00171ae8");
#define func_00171ae8 func_00171ae8_74ad8
void func_00174ad8(Wk *w) {
    Ob *o = w->x144;
    Prm *q;
    if ((s32)(o->flags >> 17) & 1) {
        o->flags &= ~0x20000ULL;
        return;
    }
    q = o->x160->xc;
    o->x68 = func_00171aa8(q->x14, q->x18);
    o->x4c = *func_00171b80(w, o, q->x0);
    if (func_00171ae8(w, o)) o->x40->x50 = q->x1c;
    o->x164 = 1;
}
#undef func_00171ae8

/* func_00174d98 (from auto/text_00170000_4.c). */
extern M2C_UNK D_0035C360;
void func_00174d98(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xB;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C360;
}

/* func_00174db0 (from hand/text_00170000_h38.c). */
extern u8 D_0035C410[];
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
#define func_00170f90 ((void (*)(void)) func_00170f90)
#define func_00170fa8 ((void (*)(Wk *, Ob *, void *, void *, f32)) func_00170fa8)
s32 func_00174db0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 47)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C410, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_00170f90
#undef func_00170fa8

/* func_00174eb8 (from hand/text_00170000_h38.c). */
#define func_00171a88 ((s32 (*)(Wk *, Ob *, s32)) func_00171a88)
#define func_00170f90 ((void (*)(void)) func_00170f90)
#define func_00170fa8 ((void (*)(Wk *, Ob *, void *, void *, f32)) func_00170fa8)
s32 func_00174eb8(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 48)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C410, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_00170f90
#undef func_00170fa8

