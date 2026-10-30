/* gb.x func_00f29c40: matched by hand. */
#include "ovl.h"

/* gb.x func_00f29c40: matched by hand (session 141). Same table lookup as func_00f30d80 (k = q * 4 + 8); the lock test is `if ((u16)(h116 & 1) == 0) { ... return 1; } return 0;`. */
typedef struct { s32 x0, x4; } Pad;
typedef struct { u16 h0; u16 h2; u16 h4; u16 h6; u16 h8; u16 h10; } T12;
typedef struct { u8 pad[72]; T12 t; u8 pad84[12]; u16 h96; u16 h98; u8 pad100[16]; u16 h116; u8 pad118[0x10D8 - 118]; s32 ang; } G;
typedef struct { s32 f0, i, n, pad; s32 pad2[4]; s32 a[4]; s32 b[4]; } Anim;
extern G *D_00F56DC0;
extern s32 D_00F56DC4;
extern s8 D_00F56DA8[];
Pad *func_001ba488(s32);
s32 func_00f25418(Pad *);
void func_001bbf88(void *, s32, s32);
u16 func_001bbdf0(void *);
void func_00f24240(s32, s32);
s32 func_00f21470(Anim *);
void func_00f2e538(f32 *);
void func_001bfac8(void);
void func_00f24680(T12 *);
void func_00f23e30(s32);
void func_00f24780(s32);
s32 func_00f29c40(void) {
    T12 t;
    Anim an;
    f32 v[4];
    Pad *p;
    s32 btn, q, k, x, z, moved;
    u16 cur = D_00F56DC0->h96;
    if (func_001ba488(0)->x4 & 0x2000) {
        do {
            p = func_001ba488(0);
            z = 0;
            x = 0;
            btn = func_00f25418(p);
            D_00F56DC0->h96 = cur;
            q = D_00F56DC0->ang / 1024;
            k = q * 4 + 8;
            if (btn & 0x10) {
                x = D_00F56DA8[k];
                z = D_00F56DA8[q * 4 + 10];
            }
            if (btn & 0x40) {
                x = -D_00F56DA8[k];
                z = -D_00F56DA8[q * 4 + 10];
            }
            moved = 0;
            an.a[0] = 0;
            an.a[1] = 0;
            an.a[2] = 0;
            an.b[0] = 0;
            an.b[1] = 0;
            an.b[2] = 0;
            if (x != 0) {
                func_001bbf88(&D_00F56DC0->t, 0, x);
                moved = 1;
                an.a[0] = -x << 10;
            }
            if (z != 0) {
                func_001bbf88(&D_00F56DC0->t, 2, z);
                moved = 1;
                an.a[2] = -z << 10;
            }
            if (btn & 0x20) {
                func_001bbf88(&D_00F56DC0->t, 1, 1);
                moved = 1;
                an.a[1] = 1024;
            }
            if (btn & 0x80) {
                func_001bbf88(&D_00F56DC0->t, 1, -1);
                moved = 1;
                an.a[1] = -1024;
            }
            D_00F56DC0->h98 = func_001bbdf0(&D_00F56DC0->t);
            func_00f24240(D_00F56DC4, 0);
            if (moved) {
                an.i = 0;
                an.n = 4;
                while (func_00f21470(&an)) {
                    func_00f2e538(v);
                    func_001bfac8();
                }
                func_00f2e538(0);
            }
            func_001bfac8();
        } while (p->x4 & 0x2000);
    }
    func_00f24240(D_00F56DC4, 0);
    if ((u16)(D_00F56DC0->h116 & 1) == 0) {
    t = D_00F56DC0->t;
    t.h0 = D_00F56DC0->h96;
    func_00f24680(&t);
    func_00f23e30(t.h4 - 1);
    func_00f24780(D_00F56DC4);
    func_00f24240(D_00F56DC4, 0);
    return 1;
    }
    return 0;
}
