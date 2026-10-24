/* The party members' records in the save data D_00304BE8: abilities, items
 * and equipment by member (func_0013c968 asks whether a member has ability
 * c, func_0013c318, func_0013c598 ...), member stats, and func_0013cb98
 * builds the records from the new-game data D_00351530. Flag mode: default
 * (the other modes are in the sibling files). Read from the code, not proved
 * by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"
#include "common.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00130000_h32.h"
#include "data/types/text_00130000_h32_p.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00351530.h"
#include "vm/script_vm.h"

/* func_0013bf68 (from auto/text_00130000.c). */
s32 func_002193f0();
s32 func_0013bf68(void) {
    return func_002193f0() == 2;
}

/* func_0013bf90 (from hand/text_00130000_h6.c). */
void func_0013bf90(s32 on) {
    if (on) {
        D_00304BE8->f880 = 1;
    } else {
        D_00304BE8->f880 = 0;
    }
}

/* func_0013bfb8 (from hand/text_00130000_h32.c). */
typedef struct { u16 x0; u16 x2; } W32Ent;
extern W32Ent *func_001478a0(s32 id);
void func_0013bfb8(u8 *a) {
    s32 i, j;
    u8 t;
    for (i = 47; i > 0; i--) {
        if (a[i] == 0) continue;
        for (j = 0; j < i; j++) {
            W32Ent *p = func_001478a0(a[j]);
            W32Ent *q = func_001478a0(a[j + 1]);
            if (p->x2 > q->x2) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

/* func_0013c078 (from hand/text_00130000_h6.c). */
typedef W606Mem_304be8 W6SEnt;
typedef struct {
    u8 pad00[0x40];
    u8 b40;
    u8 pad41[0x48 - 0x41];
    s32 w48;
    u8 pad4c[0xF0 - 0x4C];
} W6Info;
void func_00141b10(s32 i, W6Info *info);
void func_0013c078(void) {
    W6Info info;
    W6SEnt *e;
    s32 i;
    for (i = 0; i < 10; i++) {
        e = &D_00304BE8->m[i];
        func_00141b10(i, &info);
        e->sub.x1 = info.b40;
        if (e->sub.x3 < info.w48) {
            e->sub.x38 = 0;
            e->sub.x3 = info.w48;
        }
    }
}

/* func_0013c188 (from hand/text_00130000_h7.c). */
typedef W606Mem_304be8 W7Member;
s32 func_0013c188(s32 i, s32 b) {
    W7Member *m = D_00304BE8->m;
    return (m[i].bits >> b) & 1;
}

/* func_0013c1b8 (from auto/text_00130000_15.c). */
void func_0013c1b8(s32 arg0) {
    s32 temp_a0;
    void *temp_a1;

    temp_a0 = (arg0 * 4) + 0xD0;
    temp_a1 = ((s32)D_00304BE8) + 4;
    M2C_FIELD(temp_a1, u8 *, 6) = (u8) (M2C_FIELD(temp_a1, u8 *, 6) + *(M2C_UNK *)((s32) (*(s32 *)&D_00308CDC) + (s32) temp_a0));
    M2C_FIELD(temp_a1, u8 *, 7) = (u8) (M2C_FIELD(temp_a1, u8 *, 7) + M2C_FIELD(((*(s32 *)&D_00308CDC) + temp_a0), u8 *, 1));
    M2C_FIELD(temp_a1, u8 *, 4) = (u8) (M2C_FIELD(temp_a1, u8 *, 4) + M2C_FIELD(((*(s32 *)&D_00308CDC) + temp_a0), u8 *, 2));
    M2C_FIELD(temp_a1, u8 *, 3) = (u8) (M2C_FIELD(temp_a1, u8 *, 3) + M2C_FIELD(((*(s32 *)&D_00308CDC) + temp_a0), u8 *, 2));
    M2C_FIELD(temp_a1, u8 *, 5) = (u8) (M2C_FIELD(temp_a1, u8 *, 5) + M2C_FIELD(((*(s32 *)&D_00308CDC) + temp_a0), u8 *, 3));
}

/* func_0013c250 (from auto/text_00130000.c). */
void func_0013c250(s8 arg0) {
    M2C_FIELD(D_00304BE8, s8 *, 0x48C) = arg0;
}

/* func_0013c260 (from auto/text_00130000.c). */
void func_0013c260(s8 arg0) {
    M2C_FIELD(D_00304BE8, s8 *, 0x48D) = arg0;
}

/* func_0013c270 (from auto/text_00130000_1.c). */
void func_0013c270(s32 arg0, s8 arg1) {
    M2C_FIELD((arg0 + ((s32)D_00304BE8)), s8 *, 0x844) = arg1;
}

/* func_0013c288 (from auto/text_00130000_1.c). */
s8 func_0013c288(s32 arg0) {
    return M2C_FIELD((arg0 + ((s32)D_00304BE8)), s8 *, 0x844);
}

/* func_0013c2a0 (from hand/text_00130000_h7.c). */
void func_0013c2a0(s32 b, s32 on) {
    if (on) {
        D_00304BE8->x878 |= (u64)1 << b;
    } else {
        D_00304BE8->x878 &= ~((u64)1 << b);
    }
}

/* func_0013c318 (from hand/text_00130000_h7.c). */
s32 func_0013c318(s32 v) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00304BE8->x48e[i] == v) {
            return i;
        }
    }
    return -1;
}

/* func_0013c360 (from hand/text_00130000_h7.c). */
s32 func_0013c360(s32 v) {
    s32 i;
    for (i = 0; i < 7; i++) {
        if (D_00304BE8->x7d0[i] == v) {
            return 1;
        }
    }
    return 0;
}

/* func_0013c3a8 (from hand/text_00130000_h7.c). */
void func_0013c3a8(s32 v) {
    s32 i;
    for (i = 0; i < 7; i++) {
        if (D_00304BE8->x7d0[i] == v) {
            return;
        }
        if (D_00304BE8->x7d0[i] == -1) {
            D_00304BE8->x7d0[i] = v;
            return;
        }
    }
}

/* func_0013c3f8 (from hand/text_00130000_h7.c). */
typedef Save_304be8 W7Save;
extern u16 *D_00304BB0[];
extern u16 *D_00304B88[];
void *func_001477c8(void *p);
u16 *func_0013c3f8(s32 i) {
    W7Save *s = D_00304BE8;
    u16 *r;
    if (i == 0) {
        r = func_001477c8(D_00304BB0[s->x48d]);
    } else {
        r = func_001477c8(D_00304B88[i]);
    }
    return r;
}

/* func_0013c548 (from auto/text_00130000_7.c). */
M2C_UNK func_0013c458(s32, s32);
void func_0013c548(s32 arg0) {
    s32 var_a0;
    s32 var_s0;

    var_s0 = 0;
    var_a0 = 0;
    do {
        var_a0 = var_s0;
        var_s0 += 1;
        func_0013c458(var_a0, arg0);
    } while (var_s0 < 0xA);
}

/* func_0013c598 (from hand/text_00130000_h7.c). */
s32 func_0013c598(s32 i) {
    u16 *p;
    s32 e;
    if (D_00304BE8->m[i].sub.lv >= 100) {
        return 0;
    }
    p = func_0013c3f8(i);
    e = D_00304BE8->m[i].sub.exp;
    while (e >= 0) {
        e -= *p++;
    }
    return -e;
}

/* func_0013c638 (from hand/text_00130000_h7.c). */
void func_0013c638(u32 i, s32 on) {
    if (on) {
        D_00304BE8->bits5cc[i >> 2] |= 1 << (i & 3);
    } else {
        D_00304BE8->bits5cc[i >> 2] &= ~(1 << (i & 3));
    }
}

/* func_0013c6a8 (from auto/text_00130000_1.c). */
s32 func_0013c6a8(u32 arg0) {
    return M2C_FIELD((((arg0 >> 2) * 4) + ((s32)D_00304BE8)), s32 *, 0x5CC) & (1 << (arg0 & 3));
}

/* func_0013c6d8 (from hand/text_00130000_h7.c). */
#define func_00141b10 ((void (*)(s32 c, u8 *buf)) func_00141b10)
void func_0013c6d8(void) {
    u8 buf[0xF0];
    s32 i;
    for (i = 0; i < 4; i++) {
        u8 c = D_00304BE8->x48e[i];
        if (c != 0xFF) {
            W7Member *m = &D_00304BE8->m[c];
            func_00141b10(c, buf);
            m->sub.x1 = buf[64];
            m->sub.x3 = buf[72];
            m->sub.x38 = 0;
        }
    }
}
#undef func_00141b10

/* func_0013c778 (from hand/text_00130000_h7.c). */
void func_0013c778(u32 a, u32 b, u32 c) {
    D_00304BE8->x48e[1] = a < 10 ? a : -1;
    D_00304BE8->x48e[2] = b < 10 ? b : -1;
    D_00304BE8->x48e[3] = c < 10 ? c : -1;
}

/* func_0013c7d8 (from hand/text_00130000_h7.c). */
void func_0013c7d8(u32 v) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00304BE8->x48e[i] == v) {
            return;
        }
        if (D_00304BE8->x48e[i] == 0xFF) {
            if (v < 10) {
                D_00304BE8->x48e[i] = v;
            } else {
                D_00304BE8->x48e[i] = -1;
            }
            return;
        }
    }
}

/* func_0013c840 (from hand/text_00130000_h7.c). */
void func_0013c840(u32 v) {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        if (D_00304BE8->x48e[i] == v) {
            for (j = i; j < 3; j++) {
                D_00304BE8->x48e[j] = D_00304BE8->x48e[j + 1];
            }
            D_00304BE8->x48e[j] = -1;
            return;
        }
    }
}

/* func_0013c8c8 (from hand/text_00130000_h7.c). */
void func_0013c8c8(s32 c, u32 k) {
    u8 *p;
    s32 i;
    if (k < 10) {
        p = D_00304BE8->m[k].sub.name;
    } else {
        p = D_00304BE8->list599;
    }
    i = 0;
    while (p[i] != 0) {
        i++;
        if (i >= 48) return;
    }
    p[i] = c | 0x80;
}

/* func_0013c968 (from hand/text_00130000_h7.c). */
s32 func_0013c968(s32 c, u32 k) {
    u8 *p;
    s32 n;
    if (k < 10) {
        p = D_00304BE8->m[k].sub.name;
    } else {
        p = D_00304BE8->list599;
    }
    n = 0;
    while (*p) {
        if (*p++ == c) n++;
    }
    return n;
}

/* func_0013cb98 (from hand/text_00130000_b03.c). */
typedef W606Mem_304be8 B3SvEnt;
typedef Save_304be8 B3Sv;
typedef struct {
    u8 x0, x1, x2, x3, x4;
    u8 x5[16];
    u8 x15, x16;
} B3SvSrc;
extern s32 D_00304BC0[10];
B3Sv *func_00232cc0(s32);
void func_0013c9e0(s32, s32);
#define func_001477c8 ((B3SvSrc *(*)(s32)) func_001477c8)
#define func_0013c638 ((void (*)(s32, s32)) func_0013c638)
void func_0013cb98(void) {
    B3Sv *s;
    B3SvSrc *d;
    B3SvEnt *e;
    s32 i, j;

    B3Sv **pp = &D_00304BE8;
    s = func_00232cc0(0);
    *pp = s;
    s->x0 = 5;
    for (i = 0; i < 256; i++) s->items[i] = 0;
    for (i = 0; i < 10; i++) {
        s->m[i].sub.x32 = D_00304BC0[i];
        func_0013c9e0(D_00304BC0[i], 12);
    }
    s->x48e[0] = 0;
    for (i = 1; i < 4; i++) s->x48e[i] = -1;
    for (i = 0; i < 48; i++) s->list599[i] = 0;
    e = s->m;
    d = func_001477c8(14808);
    for (i = 0; i < 10; i++) {
        e->sub.w34.h.x34 = 1;
        e->sub.lv = 1;
        e->sub.x1 = e->sub.hpmax = d->x0;
        e->sub.x3 = e->sub.mpmax = d->x1;
        e->sub.x38 = 0;
        e->sub.x5 = d->x2;
        e->sub.x6 = d->x3;
        e->sub.x7 = d->x4;
        e->sub.x18 = d->x15;
        e->sub.x21 = d->x16;
        e->sub.exp = 0;
        for (j = 0; j < 16; j++) e->sub.x8[j] = d->x5[j];
        for (j = 0; j < 8; j++) e->sub.x19[j] = 0;
        for (j = 0; j < 16; j++) e->sub.x22[j] = 0;
        for (j = 0; j < 48; j++) e->sub.name[j] = 0;
        e++;
        d++;
    }
    for (i = 0; i < 512; i++) func_0013c638(i, (*(u16 (*)[512])&D_00351530)[i] & 1);
    for (i = 0; i < 7; i++) s->x7d0[i] = -1;
    for (i = 0; i < 7; i++) D_00304BE8->b492[i] = 1;
    for (i = 0; i < 3; i++) s->x844[i] = -1;
}
#undef func_001477c8
#undef func_0013c638

/* func_0013ce98 (from auto/text_00130000_4.c). */
#define func_00232cc0 ((u32 (*)(M2C_UNK)) func_00232cc0)
void func_0013ce98(void) {
    D_00304BE8 = (void *)(func_00232cc0(0));
}
#undef func_00232cc0

