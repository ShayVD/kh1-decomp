/* wm.x func_00f23018: matched by hand. */
#include "ovl.h"

/* Round 28 wwm1: matched. func_00f29aa0 returns s32 (ovl/wm/hand/func_00f29aa0.c), and so does func_0011ef10; declared void, both calls scheduled their argument setup and the draw-call registers differently. Earlier header below. */
/* Round 28 wwm1: score 19 -> 13. func_0011ef10 declared s32 (it returns a value; declared void, gcc scheduled the D_00F878F0 clear and the D_00FBB338 lui differently; the permuter found it as a non-void return, the same callee fix as dktitle f20258). The 4-byte size gap is the alignment nop after jr ra (the next function is 16-aligned), not code. Left: the 15001 call's li a0/move t0 order and v0/v1 in the draw call. Earlier header below. */
/* Round 27 wwm1: score 85 -> 19 (1332 vs 1336). valaudit: the target stores D_00FBAA78 and D_00FBAA7C through two address registers (sw 0(s1), sw 0(s0)) and D_00FBAA80..8C by %lo, so they are scalars, the first two written through pointer locals; pa is set before the second func_001bb7c8 call and pb just before the stores (that gives the target's s1/s0; together: 47). The target stores xac = arg after the second func_00f2b298 call (sw s2,172 follows that jal), id = 2 comes after the xc/x10 stores, D_00F873F0 = 1 after p = *D_00F85160, and D_00F878F0 is cleared a, b, c, d. Left: v0/v1 in the draw call, the 15001 call's a0/t0 order, and the lui register of D_00FBB338. Earlier header below. */
/* Round 46 wwm2: score 89 -> 85, hill3o statement order. Earlier header below. */
/* Round 46 wwm2: score 91 -> 89, func_00f294a0 declared s32. Earlier header below. */
/* Round 36 (wgb): wm.x func_00f23018 near miss: 251 -> 251 words, score 99 -> 91 (aligned diff 73 -> 66). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* score 99 (1308 vs 1336). World-map main: heap/texture setup, D_00FB6498 callbacks (init/draw/done), handler registration, then the frame loop with two GIF end packets. D_00FBAA78..8C as one array (149 -> 99). Left: orig keeps &D_00FBAA78/&D_00FBAA7C in s1/s0 and stores the rest by %lo, scheduling of the D_00FB6498 field stores, 28 bytes. Round 26 wwm2. */
typedef struct {
    void (*init)(s32, s32);
    void (*draw)(u64 **);
    s32 (*done)(void);
    s32 xc;
    s32 x10;
    u8 x14[128];
    s32 x94;
    s32 x98;
    s32 x9c;
    s32 xa0;
    u8 pada4[8];
    s32 xac;
} Wm;
typedef struct { s32 a, b, c, d; } Q4;
extern s32 D_00F850BC;
extern u64 **D_00F85160;
extern s32 D_00F873F0;
extern s32 D_00F873F4;
extern Q4 D_00F878F0;
extern s32 D_00F9B2EC;
extern Wm D_00FB6498;
extern char D_00FB6690[];
extern char D_00FB66A8[];
extern s32 D_00FBAA70;
extern s32 D_00FBAA74;
extern s32 D_00FBAA78;
extern s32 D_00FBAA7C;
extern s32 D_00FBAA80, D_00FBAA84, D_00FBAA88, D_00FBAA8C;
extern s32 D_00FBAA94;
extern s32 D_00FBB32C;
extern s32 D_00FBB334;
extern s32 D_00FBB338;
s32 func_0011ef10(s32, void (*)(void));
void func_001ba708(s32);
s32 func_001bb500(s32, s32);
void func_001bb7c8(char *, s32);
void func_001bfac8(void);
void func_001c01b0(s32, void (*)(void));
void func_001c0310(s32, void (*)(void));
void func_001c06c0(s32, void (*)(void));
void func_00f206d8(s32, s32, s32);
void func_00f21ef0(f32);
void func_00f22240(void);
void func_00f222a0(void);
void func_00f22e20(void);
void func_00f22e60(void);
void func_00f23008(void);
void func_00f23878(void);
void func_00f25420(void);
void func_00f254f8(void);
s32 func_00f294a0(s32, s32, s32);
void func_00f29810(s32, u8 *, u8 *);
s32 func_00f29aa0(s32, u64 **, s32, u8 *, u8 *, f32 (*)[4], f32);
void func_00f2ac98(u8 *);
s32 func_00f2b298(s32);
void func_00f64b88(s32);
void func_00f65a68(s32);
u64 *func_00f66ac8(u64 *);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void func_00f66f78(s32, u64 *);
void func_00f67fd0(s32, s32);
void func_00f68008(s32, s32);
void func_00f68070(void);
void func_00f78bb0(s32);
s32 func_00f7d098(void);
void sceVu0UnitMatrix(f32 (*)[4]);

s32 func_00f23018(s32 id, s32 arg)
{
    u64 *lim[2];
    s32 i;
    s32 tex[2];
    s32 pal[2];
    u8 work[2048];
    u64 *p;
    f32 m[4][4];
    s32 heap;
    s32 *pa, *pb;
    u8 cam[128];
    D_00FBAA70 = 0;
    D_00FBAA74 = 0;
    D_00FBB334 = 0;
    D_00F873F4 = 0;
    heap = func_001bb500(0x200000, 128);
    func_00f67fd0(125, heap);
    func_00f68008(125, heap);
    func_00f68070();
    func_00f206d8(0, 0, 0);

    D_00FB6498.xc = 0x3600;
    D_00FB6498.x10 = 0x800;
    if (id == 0) {
        id = 2;
    }
    D_00FB6498.x94 = func_00f2b298(id);
    D_00FB6498.x98 = func_00f2b298(id);
    D_00FB6498.xac = arg;
    func_00f2ac98(D_00FB6498.x14);
    for (i = 0; i < 2; i++) {
        tex[i] = func_001bb500(0x30000, 128);
        pal[i] = func_001bb500(0x14000, 128);
    }
    func_001bb7c8(D_00FB6690, tex[0]);
    pa = &D_00FBAA78;
    func_001bb7c8(D_00FB66A8, pal[0]);
    func_00f64b88(tex[0]);
    func_00f65a68(pal[0]);
    func_00f29810(tex[0], work, cam);
    sceVu0UnitMatrix(m);
    pb = &D_00FBAA7C;
    *pa = func_001bb500(0x60000, 128);
    *pb = func_001bb500(0x64000, 128);
    D_00FBAA80 = func_001bb500(0x34000, 128);
    D_00FBAA84 = func_001bb500(0x4000, 128);
    D_00FBAA88 = func_001bb500(0x67000, 128);
    D_00FBAA8C = func_001bb500(0x20000, 128);
    D_00FB6498.init(heap, 0x200000);
    p = *D_00F85160;
    D_00F873F0 = 1;
    lim[0] = p;
    lim[1] = p;
    func_001c06c0(-1, func_00f23008);
    func_00f23878();
    func_00f21ef0(0.0f);
    D_00FBB32C = 0;
    D_00F878F0.a = 0;
    D_00F878F0.b = 0;
    D_00F878F0.c = 0;
    D_00F878F0.d = 0;
    func_0011ef10(0x249F0, func_00f22240);
    func_0011ef10(0x249F1, func_00f222a0);
    func_0011ef10(0x270FE, func_00f25420);
    func_0011ef10(0x27CB6, func_00f254f8);
    D_00FBB338 = 1;
    func_001c01b0(1, func_00f22e20);
    func_001c0310(-1, func_00f22e60);
    func_001bfac8();
    D_00FBAA94 = 0;
    do {
        if (func_00f7d098() && D_00F9B2EC == 0 && D_00F873F4 == 0) {
            func_001ba708(0);
            func_00f78bb0(1);
        } else {
            func_00f78bb0(0);
        }
        func_00f294a0(15000, 0x2A00, pal[0]);
        func_00f29aa0(15001, D_00F85160, tex[0], work, cam, m, 1.0f);
        p = *D_00F85160;
        lim[0] = p;
        lim[1] = p;
        D_00FB6498.draw(lim);
        if (p < lim[0]) {
            func_00f66f78(20001, p);
            p = lim[0];
        }
        if (p < lim[1]) {
            func_00f66f78(80001, p);
            p = lim[1];
        }
        *D_00F85160 = p;
        p = func_00f66b78(func_00f66ac8(p));
        p[0] = 0x0000740000007000LL;
        p[1] = 24;
        p += 2;
        p[0] = 0x800D0;
        p[1] = 76;
        p += 2;
        func_00f66b90(p);
        func_00f66f78(20000, (u64 *)func_00f66ae0(p));
        *D_00F85160 = p;
        p = func_00f66b78(func_00f66ac8(p));
        p[0] = 0x0000740000007000LL;
        p[1] = 24;
        p += 2;
        p[0] = 0x800D0;
        p[1] = 76;
        p += 2;
        func_00f66b90(p);
        func_00f66f78(80000, (u64 *)func_00f66ae0(p));
        *D_00F85160 = p;
        func_001bfac8();
    } while (D_00FB6498.done() == 0);
    D_00F873F0 = 0;
    if (D_00FB6498.xa0 == 1) {
        return -1;
    }
    D_00F850BC = D_00FB6498.x9c;
    return D_00FB6498.x98;
}
