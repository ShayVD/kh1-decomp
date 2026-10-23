/* Page 5's section 2 (D_003F5A00[2], the first in address order; docs/modules.md
 * "Session 42"), 0x0021dbb8-0x0021fbb8.  Its opener func_0021faf8 keeps the
 * section's window in D_00643110; set up func_0021fb28 (D_003F5C20, called by
 * journal.c's func_0021dad8), reset func_0021fb50 (journal.c's func_0021db30).
 *
 * Three lists of entries (D_0064324C picks one, func_0021f5f8's window):
 * func_0021dc40 (func_0021fb10) fills D_006431F0[0..2] / D_00643200[0..2]
 * with the entries 0-48, 49-126 and 127-183 whose flag func_001eb038(
 * func_0021dc08(i)) is set (list 2 also marks D_00643210 for the entries
 * seen), sets the "new" marks with func_00207000 / func_00207048 and the
 * "complete" flags D_00643278[0..2] / D_003F5C38.  func_0021ed60 is the entry
 * list (eight rows a page), func_0021e8d8 (journal_s2.nostrict.c) an entry's
 * detail with its model (journalmdl.c), func_0021e670 the model viewer (zoom,
 * turn, move), func_0021e538 loads entry D_0064324C's file (D_003F5C50) into
 * D_003F3510.  Entry names are messages 0x51 + i (func_0021dc20).  Not proved
 * by a boot; most likely the journal's character / enemy lists.
 *
 * Views: JsWin (include/menu/journal.h), Ed (the model viewer: f32 at +0x24 /
 * +0x28). */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "vm/script_vm.h"
#include "menu/journal.h"

typedef struct { u8 pad[0x24]; f32 x24; f32 x28; s32 x2c; s32 x30; } Ed;

extern JsWin *D_00643110; /* src/data/bss_0064.c: s32 D_00643110 */
extern s32 D_0064324C;
extern u8 *D_006431F0[3];
extern s32 D_00643200[3];
extern u8 D_00643210[];
extern s32 D_00643278[3]; /* src/data/bss_0064.c: s32 D_00643278[0x6] */
extern u16 D_003F5C60[0x17];
extern u16 D_003F5C90[0xb8];
extern u8 D_00491030[], D_00491048[], D_00491060[];
/* The entries' files (func_0021e538), by list. */
s32 D_003F5C50[0x4] ALIGNED(16) = {
    (s32)D_00491060, (s32)D_00491048, (s32)D_00491030, 0,
};
extern s32 D_003F5E58[2];
extern s32 D_003F5F18[3];
extern s32 D_003F34C8;
extern s32 D_003F350C;
extern s32 D_003F3510;
extern s32 D_003F34F8;
extern s32 D_003F5C20;
extern s32 D_003F5C38;
extern s32 D_003F50E0[0xb8];
extern u16 D_003E9104;
extern u8 D_003F5E60[];
extern u8 D_003F5E90[], D_003F5EC0[], D_003F5EF0[];
extern u8 D_003F5F30[], D_003F5F60[], D_003F5F90[];

void func_0011d768(s32);
void func_00120748(s32, s32, void (*)(void), s32);
s32 func_0010eb78(s32);
s32 func_00131c30(s32);
s32 func_001eb038(s32);
void func_001eb0a0(s32, s32);
f32 func_001edcd8(f32);
s32 func_001effc0(s32);
void *func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3758(void *);
void func_001f3e48(void *, void *);
s32 func_001f42b8(void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fade0(void *, s32, s32, s32, s32, u32);
s32 func_001fd518(void *);
s32 func_001fd668(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00203788(void *, s32, s32, s32, u32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
void func_00207000(s32);
void func_00207048(s32);
s32 func_00207088(s32);
void func_00207140(s32);
s32 func_00207180(s32);
void func_00207298(s32);
void func_002072e0(s32);
void func_00207428(void *, s32, s32);
void func_00207560(void *, s32, s32);
void func_0021af38(void *);
void func_0021b1b0(f32, f32, s32, s32);
s32 func_0021b800(s32);
void func_0021b820(void);
void func_0021c4f8(void *);
void func_0021c780(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
void func_0021cb88(void *, s32, s32, s32, s32);
void func_0021ccd0(void *, s32);
s32 strcmp(const char *, const char *);

s32 func_0021dbb8(void) {
    s32 temp_v0;
    u16 *var_s0;
    u16 temp_a0;
    u32 var_s1;

    var_s0 = D_003F5C60;
    var_s1 = 0;
    do {
        temp_a0 = *var_s0;
        var_s0 += 1;
        func_001eb0a0((s32) temp_a0, 1);
        var_s1 += 1;
        temp_v0 = var_s1 < 0x17U;
    } while (temp_v0 != 0);
    return temp_v0;
}

u16 func_0021dc08(s32 i) {
    return D_003F5C90[i];
}

s32 func_0021dc20(s32 i) {
    return func_0021b800(i + 0x51);
}

s32 func_0021dc38(s32 arg0) {
    return arg0;
}

void func_0021dc40(void) {
    s32 i, j;
    s32 *c;
    char *p, *s;
    c = D_00643200;
    D_006431F0[0] = D_00643128;
    c[0] = 0;
    for (i = 0; i < 49; i++) {
        if (func_001eb038(func_0021dc08(i))) { s32 n = D_00643200[0]; D_00643200[0] = n + 1; D_00643128[n] = i; }
    }
    D_006431F0[1] = D_00643160;
    D_00643200[1] = 0;
    for (; i < 127; i++) {
        if (func_001eb038(func_0021dc08(i))) { D_00643160[D_00643200[1]] = i; D_00643200[1]++; }
    }
    D_006431F0[2] = D_006431B0;
    D_00643200[2] = 0;
    for (; i < 184; i++) {
        if (func_001eb038(func_0021dc08(i)) || func_00131c30(D_003F50E0[i])) D_00643210[D_00643200[2]] = 1;
        else D_00643210[D_00643200[2]] = 0;
        D_006431B0[D_00643200[2]] = i;
        D_00643200[2]++;
    }
    for (j = D_00643200[0] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08(D_00643128[j]))) {
            func_00207000(0);
            goto l1;
        }
    }
    func_00207048(0);
l1:
    for (j = D_00643200[1] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08(D_00643160[j]))) {
            func_00207000(1);
            goto l2;
        }
    }
    func_00207048(1);
l2:
    for (j = D_00643200[2] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08(D_006431B0[j])) && D_00643210[j]) {
            func_00207000(2);
            goto l3;
        }
    }
    func_00207048(2);
l3:
    if (func_00207088(0) && func_00207088(1) && func_00207088(2)) {
        func_002072e0(2);
    } else {
        func_00207298(2);
    }
    s = (char *)func_0021dc20(0);
    for (i = 1; i < 49; i++) {
        p = s;
        s = (char *)func_0021dc20(i);
        if (i != 38 && strcmp(p, s) && !func_001eb038(func_0021dc08(i - 1))) goto z0;
    }
    if (!func_001eb038(func_0021dc08(48))) { z0: D_00643278[0] = 0; }
    else D_00643278[0] = 1;
    s = (char *)func_0021dc20(49);
    for (i = 50; i < 127; i++) {
        p = s;
        s = (char *)func_0021dc20(i);
        if (strcmp(p, s) && !func_001eb038(func_0021dc08(i - 1))) goto z1;
    }
    if (!func_001eb038(func_0021dc08(126))) { z1: D_00643278[1] = 0; }
    else D_00643278[1] = 1;
    for (i = 127; i < 184; i++) {
        if (!func_001eb038(func_0021dc08(i)) && !func_00131c30(D_003F50E0[i])) { D_00643278[2] = 0; goto e2; }
    }
    D_00643278[2] = 1;
e2:
    if (D_00643278[0] && D_00643278[1] && D_00643278[2]) D_003F5C38 = 1;
    else D_003F5C38 = 0;
}

void func_0021e508(void) {
    D_003F350C += 1;
    D_003F34C8 -= 1;
}

void func_0021e538(void) {
    s32 k;
    switch (D_00643118) {
    case 0:
        switch (D_003F350C) {
        case 0:
            k = D_0064324C;
            D_003F34C8++;
            D_003F350C = 1;
            D_00643118 = 1;
            D_00643120 = k;
            func_00120748(D_003F5C50[k], D_003F3510, func_0021e508, 0);
            return;
        case 1:
            D_00643118 = D_003F350C;
            return;
        default:
            if (D_00643120 != D_0064324C) {
                D_003F350C = 0;
                D_00643118 = 0;
            } else {
                D_0064311C = D_00643120;
                D_00643118 = 2;
            }
            break;
        }
        break;
    case 2:
        break;
    case 1:
        if (D_003F350C == 2) {
            if (D_00643120 != D_0064324C) {
                D_003F350C = 0;
                D_00643118 = 0;
                return;
            }
            D_00643118 = D_003F350C;
            D_0064311C = D_00643120;
        }
        break;
    }
}

void func_0021e670(Ed *a) {
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f36b8(a);
            func_0011d768(3);
        } else {
            if (D_00425BC8->x4 & 0x100000) {
                a->x24 -= 0.02f;
                if (a->x24 < 0.1f) a->x24 = 0.1f;
            } else if (D_00425BC8->x4 & 0x400000) {
                a->x24 += 0.02f;
                if (10.0f < a->x24) a->x24 = 10.0f;
            }
            if (D_00425BC8->x4 & 0x800000) {
                a->x28 += 0.05235987755982988f;
                a->x28 = func_001edcd8(a->x28);
            } else if (D_00425BC8->x4 & 0x200000) {
                a->x28 -= 0.05235987755982988f;
                a->x28 = func_001edcd8(a->x28);
            }
            if ((s32)D_00425BC8->x4 < 0) {
                a->x2c -= 4;
                if (a->x2c < 0) a->x2c = 0;
            } else if (D_00425BC8->x4 & 0x20000000) {
                a->x2c += 4;
                if (a->x2c > 512) a->x2c = 512;
            }
            if (D_00425BC8->x4 & 0x10000000) {
                a->x30 -= 4;
                if (a->x30 < 0) a->x30 = 0;
            } else if (D_00425BC8->x4 & 0x40000000) {
                a->x30 += 4;
                if (a->x30 > 384) a->x30 = 384;
            }
        }
    }
    func_002053e8(a, 17, 73, 479, 295, 0x40357966);
    func_0021b1b0(a->x24, a->x28, a->x2c, a->x30);
    func_0021af38(a);
}

void func_0021e890(void) {

}

s32 func_0021e898(s32 arg0) {
    s32 *var_a2;
    s32 temp_v1;
    s32 var_v0;
    u32 var_a1;

    var_a1 = 0;
    var_a2 = D_003F5E58;
loop_1:
    temp_v1 = *var_a2;
    var_a2 += 1;
    var_v0 = 1;
    if (temp_v1 == arg0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 2U) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

void func_0021ed48(JsWin *a) {
    func_00207140(a->x40);
}

void func_0021ed60(JsWin *o) {
    s32 ch, n, k, v, j, i, y, dy, c, x, cnt;
    JsWin *p;
    if (func_001f42b8(o)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643110->x10);
            func_0011d768(3);
            goto draw;
        }
        func_0021e538();
        func_001fd858(o);
        D_00643268[D_0064324C] = func_001fd518(o);
        ch = 0;
        n = o->xd8;
        if (D_00425BC8->x10 & 0x80000480) {
            if (o->xda > 0) {
                o->xda -= 16;
                ch = 1;
            }
        } else if (D_00425BC8->x10 & 0x20000820) {
            if (o->xda < (n - 1) << 4) {
                o->xda += 16;
                ch = 1;
            }
        }
        D_00643258[D_0064324C] = func_001fd668(o);
        if (ch) {
            func_0011d768(1);
            k = D_00643200[D_0064324C];
            if (k < 8 || D_00643258[D_0064324C] == n - 1) {
                v = (k - 1) % 8 + 1;
                o->xce = v;
                o->xcc = v;
            } else {
                o->xce = 8;
                o->xcc = 8;
            }
        }
        if (func_001fe5a0(o)) {
            if (D_0064324C == 2 && !D_00643210[D_00643258[2] * 8 + D_00643268[2]]) {
                func_0011d768(4);
                goto draw;
            }
            func_0011d768(2);
            D_00643274 = D_006431F0[D_0064324C][D_00643258[D_0064324C] * 8 + D_00643268[D_0064324C]];
            func_001f3758(D_00643110->x10);
            p = func_001f31a8(D_003F5E60, 50);
            if (p) {
                p->x24 = func_00131c30(D_003F50E0[D_00643274]);
                p->x40 = func_0021dc08(D_00643274);
                func_001f3e48(p, o);
                { f32 f = D_003E9104; D_00643250 = 0; p->xa0 = f; }
                n = func_0010eb78((s32)func_001c2df0((s8 *)D_003F34F8, func_0021dc38(D_00643274)));
                p->xda = D_00643250 << 4;
                p->xd8 = (n + 1) / 2;
            }
        }
    }
draw:
    func_00203788(o, D_0064324C != 1 ? 372 : 329, 40, 486, 0x80C8C8C8);
    dy = o->xc4 >> 4;
    y = 116;
    for (i = 0, j = D_00643258[D_0064324C] * 8; i < 8 && j < D_00643200[D_0064324C]; i++, j++) {
        c = D_006431F0[D_0064324C][j];
        if (D_0064324C == 2 && !D_00643210[j]) {
            cnt = func_001effc0(func_0021dc20(c));
            x = 322;
            for (; cnt > 0; cnt--) x = func_001fade0(o, x, y, 41, 15, 0x40461E00);
        } else {
            func_001f94f0(o, 0, 322, y, func_0021dc20(D_006431F0[D_0064324C][j]), 15, 0x80461E00);
            if (!func_00207180(func_0021dc08(c))) func_00207428(o, 450, y + 10);
        }
        y += dy;
    }
    func_0021b820();
    func_0021c4f8(o);
}

void func_0021f278(void) {
    s32 i;
    for (i = D_00643200[D_0064324C] - 1; i >= 0; i--) {
        if (func_00207180(func_0021dc08(D_006431F0[D_0064324C][i])) == 0) {
            if (D_0064324C != 2) {
                func_00207000(D_0064324C);
                return;
            }
            if (D_00643210[i] != 0) {
                func_00207000(2);
                return;
            }
        }
    }
    func_00207048(D_0064324C);
}

void func_0021f390(JsWin *arg0) {
    func_0021b820();
    func_0021cb88(arg0, 0xB0, 8, 0x140, 1);
}

void func_0021f3c8(JsWin *arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_0021f410(JsWin *a) {
    JsWin *o[3];
    if (!(o[0] = func_001f31a8(D_003F5EF0, 50))) return;
    o[0]->xa0 = D_003E9104;
    func_001f3e48(o[0], a);
    if (!(o[1] = func_001f31a8(D_003F5EC0, 50))) return;
    func_001f3e48(o[1], o[0]);
    o[1]->xa0 = o[0]->xa0;
    if (!(o[2] = func_001f31a8(D_003F5E90, 50))) return;
    func_001f3e48(o[2], o[1]);
    o[2]->xa0 = o[0]->xa0;
    if (D_00643200[D_0064324C] / 8 * 8 < D_00643258[D_0064324C] * 8) D_00643258[D_0064324C] = 0;
    if (D_00643200[D_0064324C] < D_00643258[D_0064324C] * 8 + D_00643268[D_0064324C]) D_00643268[D_0064324C] = 0;
    o[2]->xca = D_00643200[D_0064324C];
    o[2]->xda = D_00643258[D_0064324C] << 4;
    o[2]->xd8 = (D_00643200[D_0064324C] + 7) / 8;
    if (D_00643200[D_0064324C] < 8 || D_00643258[D_0064324C] == o[2]->xd8 - 1) o[2]->xcc = (D_00643200[D_0064324C] - 1) % 8 + 1;
    else o[2]->xcc = 8;
    o[2]->xd2 = D_00643268[D_0064324C] << 4;
}

void func_0021f5f8(JsWin *a) {
    s32 i, y;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643110);
            func_0011d768(3);
        } else {
            s32 *p;
            func_001fd858(a);
            i = func_001fd518(a);
            p = &D_0064324C;
            *p = i;
            if (func_001fe5a0(a)) {
                if (D_00643200[*p]) {
                    func_001f3758(D_00643110->x10);
                    func_0021f410(a);
                    D_00643118 = 0;
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
            }
        }
    }
    y = 116;
    for (i = 0; i < 3; i++) {
        func_001f94f0(a, 0, 322, y, func_0021b800(D_003F5F18[i]), 15, D_00643200[i] ? 0x80461E00 : 0x40461E00);
        if (D_00643278[i]) func_00207560(a, 456, y - 2);
        if (!func_00207088(i)) func_00207428(a, 450, y + 10);
        y += 60;
    }
    func_0021b820();
    func_0021c4f8(a);
}

void func_0021f7d8(JsWin *arg0) {
    func_0021b820();
    func_0021ccd0(arg0, 1);
    func_0021af38(arg0);
}

void func_0021f810(JsWin *arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_0021f858(JsWin *a0) {
    JsWin *b[3];
    b[0] = func_001f31a8(D_003F5F90, 50);
    if (b[0] == 0) return;
    func_001f3e48(b[0], a0);
    b[1] = func_001f31a8(D_003F5F60, 50);
    if (b[1] == 0) return;
    func_001f3e48(b[1], b[0]);
    b[2] = func_001f31a8(D_003F5F30, 50);
    if (b[2] == 0) return;
    func_001f3e48(b[2], b[1]);
    b[2]->xd2 = *(u16 *)&D_0064324C * 16;
}

/* func_0021f900 only matches with its callee func_0021f410 defined above it. */
void func_0021f900(JsWin *a) {
    s32 *p;
    if (!func_001f42b8(a)) return;
    p = &D_00643114;
    if (*p == 0) {
        func_0021f858(a);
        return;
    }
    func_0021f410(a);
    *p = 0;
}

void func_0021f968(void) {
    s32 i;
    for (i = D_00643200[0] - 1; i >= 0; i--) {
        if (!func_00207180(func_0021dc08(D_00643128[i]))) {
            func_00207000(0);
            goto l1;
        }
    }
    func_00207048(0);
l1:
    for (i = D_00643200[1] - 1; i >= 0; i--) {
        if (!func_00207180(func_0021dc08(D_00643160[i]))) {
            func_00207000(1);
            goto l2;
        }
    }
    func_00207048(1);
l2:
    for (i = D_00643200[2] - 1; i >= 0; i--) {
        if (!func_00207180(func_0021dc08(D_006431B0[i])) && D_00643210[i]) {
            func_00207000(2);
            goto l3;
        }
    }
    func_00207048(2);
l3:
    if (func_00207088(0) && func_00207088(1) && func_00207088(2)) {
        func_002072e0(2);
        return;
    }
    func_00207298(2);
}

void func_0021faf8(JsWin *a) {
    D_00643110 = a;
    D_00643114 = 0;
}

void func_0021fb10(void) {
    func_0021dc40();
}

void func_0021fb28(void) {
    D_003F5C20 = 1;
    D_0064311C = -1;
    D_00643120 = -1;
}

void func_0021fb50(void) {
    s32 i;
    D_0064324C = 0;
    D_00643250 = 0;
    for (i = 0; i < 3; i++) {
        D_00643258[i] = 0;
        D_00643268[i] = 0;
    }
    D_0064311C = -1;
    D_00643120 = -1;
    D_00643118 = 0;
}
