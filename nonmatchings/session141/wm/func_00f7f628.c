/* score 21 (111 words, mostly a 1-word shift): debug value editor over a NULL-name-terminated list. Left: `move s8,a0` sits in the first bnez slot in the original, and the `--sel < 0` test is bgezl with the pad reload in its slot. Count loop must be the if + do-while form (no alignment nop). 10 min permuter: nothing valid. */
#include "ovl.h"

typedef struct {
    s32 name;
    s32 id;
} Ent;

typedef struct {
    u8 pad0[0x78];
    s32 x78;
    s32 x7C;
    s32 x80;
} Pad;

extern volatile Pad D_002C5AD0;
extern u8 D_00FB64AC[];
void func_0011d768(s32);
void func_001bfac8(void);
s32 func_00f7f5d8(s32);
void func_00f7f600(s32, s8);
void func_00f7f438(s32, Ent *, s32, s32, s32);
void func_00f2ac98(u8 *);

void func_00f7f628(s32 arg0, Ent *list) {
    s32 sel = 0;
    s32 bit = 0;
    s32 last = -1;
    s32 n;
    s32 v;
    s32 b;
    Ent *e;

    while (!(D_002C5AD0.x78 & 0x4000)) {
        if (D_002C5AD0.x80 & 0x10) {
            if (--sel < 0) {
                n = 0;
                if (list[0].name != 0) {
                    do {
                        n++;
                    } while (list[n].name != 0);
                }
                n--;
                sel = 0;
                if (n >= 0) {
                    sel = n;
                }
            }
        }
        if (D_002C5AD0.x80 & 0x40) {
            sel++;
            if (list[sel].name == 0) {
                sel = 0;
            }
        }
        if (sel != last) {
            bit = 0;
            last = sel;
            func_0011d768(1);
        }
        e = sel + list;
        if (e->name != 0) {
            v = func_00f7f5d8(e->id);
            b = D_002C5AD0.x80;
            if (b & 0x800) {
                v--;
            }
            if (b & 0x400) {
                v++;
            }
            if (b & 0x200) {
                v -= 16;
            }
            if (b & 0x100) {
                v += 16;
            }
            if (b & 0x80) {
                bit++;
            }
            if (b & 0x20) {
                bit--;
            }
            v &= 0xFF;
            bit &= 7;
            if (b & 0x2000) {
                v ^= 1 << bit;
            }
            func_00f7f600(e->id, v);
            func_00f7f438(arg0, e, v, bit, e->id);
            func_00f2ac98(D_00FB64AC);
        }
        func_001bfac8();
    }
    func_0011d768(3);
}
