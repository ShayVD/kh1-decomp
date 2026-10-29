/* gb.x func_00f4be48 near miss: 8 words differ, score 11 (ours 1580 bytes, original 1584; the 4-byte gap is the trailing alignment nop). Port of wm func_00f72f40 (nonmatchings/session141/wm) via tools/ovl/port.py; see that file for the findings. Same remaining diff: in the first func_00f445a8(14, 3, ...) call, D_00F703B8 (arg 12) and the constant 2 (arg 13) get v0/v1 swapped and the D_00F703B8 load is scheduled too early. Tried in round 19: (s32)2, 1 + 1 in either 2 slot, *&D_00F703B8, a block-local temp for D_00F703B8 or for 2 (all 11), and a temp shared by both calls (79). */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[4]; u8 b4; u8 pad5[2]; u8 b7; } Win;
typedef struct { u8 pad[16]; s32 x10; } Hdl;
typedef struct { u8 b0; u8 pad[3]; s32 x4; } Itm;
typedef struct { u8 pad[208]; u16 hd0; u16 hd2; } Obj;
extern Pad D_002C5AD0;
extern s32 D_00F702F0;
extern s32 D_00F703A4;
extern u8 D_00F703A8;
extern s32 D_00F703AC;
extern s32 D_00F703B8;
extern s32 D_00F703BC;
extern s32 D_00F703EC;
extern s32 D_00F703F0;
extern s32 D_00F70538, D_00F7053C, D_00F70540, D_00F70544;
extern s16 D_00F712A8[];
extern s32 D_00F712B8[];
extern s32 D_00F829CC;
extern s32 D_00F82D6C;
extern s32 D_00F82D70;
void func_0011d768(s32);
Itm *func_001bc4f0(void);
s32 func_001bc520(void);
void func_001bdb58(void);
void func_001f3dc0(Obj *);
void func_0024e468(s32);
void func_00f43cf0(s32);
void func_00f444d8(s32, s32, s32);
void *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f4d880(Win *, s32);

void func_00f4be48(Obj *o, Hdl *h)
{
    Win *w[5];
    Win **pw;
    Win **pw2;
    s16 *ps;
    s32 t, y, k, sel, n, cat, v, c;
    u32 a, b;
    Itm *e;

    t = D_00F702F0;
    y = D_00F703BC;
    pw = w;
    k = 4;
    ps = D_00F712A8;
    do {
        *pw = func_00f445a8(14, 0, 2, 1, 1, 15, *ps++, 1, D_00F703A4, y, 0, D_00F703AC, 0, 0, 0, 0, 0, 256, t);
        (*pw)->b7 = D_00F703A8;
        (*pw++)->b4 = 0;
        y += D_00F703EC;
    } while (--k >= 0);
    func_00f445a8(14, 3, 0, 2, 0, 0, 0, 0, 0, D_00F703BC + 12, 0, D_00F703B8, 2, D_00F70538, D_00F7053C, D_00F70540, D_00F70544, 256, t);
    func_00f445a8(14, 0, 2, 1, 0, 15, 85, 7, D_00F703B8, D_00F703BC, 0, D_00F703F0, 0, 0, 0, 0, 0, 256, t);
    h->x10 = 50;
    goto test;
loop: {
        c = (o->hd0 & 0xF) != 0; if (o->hd2 & 0xF) c = 1; if (D_002C5AD0.x4 & 0x10) c = 1; if (D_002C5AD0.x4 & 0x40) c = 1;
        if ((a & 0x2000) && !c) {
            e = func_001bc4f0() + D_00F82D70;
            if (e->b0 == 9) {
                func_0011d768(4);
            } else {
                func_0011d768(2);
                D_00F82D6C = 0;
                sel = 0;
                func_001f3dc0((Obj *)D_00F829CC);
                func_0024e468(1);
                goto itest;
            iloop:
                    c = (o->hd0 & 0xF) != 0; if (o->hd2 & 0xF) c = 1; if (D_002C5AD0.x4 & 0x10) c = 1; if (D_002C5AD0.x4 & 0x40) c = 1;
                    if ((a & 0x2000) && !c) {
                        func_001bc4f0();
                        func_0011d768(2);
                        n = func_001bc520();
                        for (k = 0; k < n; k++) {
                            e = func_001bc4f0() + k;
                            if (e->x4 == D_00F712B8[sel]) {
                                e->x4 = (func_001bc4f0() + D_00F82D70)->x4;
                            }
                        }
                        e = func_001bc4f0() + D_00F82D70;
                        switch (e->b0) {
                        case 0: cat = 0; break;
                        case 1: cat = 1; break;
                        case 2: cat = 2; break;
                        case 3: case 4: case 5: cat = 3; break;
                        case 6: case 7: case 8: cat = 4; break;
                        case 9: cat = 5; break;
                        default: cat = 6; break;
                        }
                        n = func_001bc520();
                        for (k = 0; k < n; k++) {
                            e = func_001bc4f0() + k;
                            switch (e->b0) {
                            case 0: v = 0; break;
                            case 1: v = 1; break;
                            case 2: v = 2; break;
                            case 3: case 4: case 5: v = 3; break;
                            case 6: case 7: case 8: v = 4; break;
                            case 9: v = 5; break;
                            default: v = -1; break;
                            }
                            if (v == cat) e->x4 = D_00F712B8[sel];
                        }
                        a = 0;
                        b = 0;
                        func_001bdb58();
                    }
                    if (b & 0x10) {
                        sel--;
                        if (sel < 0) {
                            if (a & 0x10) {
                                sel = 4;
                                func_0011d768(1);
                            } else {
                                sel = 0;
                            }
                        } else {
                            func_0011d768(1);
                        }
                        a = 0;
                        b = 0;
                    }
                    if (b & 0x40) {
                        sel++;
                        if (sel >= 5) {
                            if (a & 0x40) {
                                sel = 0;
                                func_0011d768(1);
                            } else {
                                sel = 4;
                            }
                        } else {
                            func_0011d768(1);
                        }
                    }
                    for (k = 0; k < 5; k++) {
                        if (sel == k)
                            w[k]->b4 = 1;
                        else
                            w[k]->b4 = 0;
                    }
                    func_00f4d880(w[sel], 8);
                    func_0024e468(1);
            itest:
                a = D_002C5AD0.x8 | D_002C5AD0.x8 >> 24;
                b = D_002C5AD0.x10 | D_002C5AD0.x10 >> 24;
                if (!(a & 0x4000)) goto iloop;
                func_0011d768(3);
                do {} while (0);
                pw2 = w;
                k = 4;
            clr:
                (*pw2++)->b4 = 0;
                if (--k >= 0) goto clr;
                D_00F82D6C = 1;
                func_001f3dc0(o);
            }
        }
        func_0024e468(1);
    }
test:
    a = D_002C5AD0.x8;
    if (!(a & 0x4000)) goto loop;
    func_0011d768(3);
    do {} while (0);
    func_00f444d8(14, 0, D_00F702F0);
    func_0024e468(D_00F702F0);
    func_00f43cf0(14);
}
