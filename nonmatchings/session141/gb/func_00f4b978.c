/* Round 54 wgb: score 35, now 1236 vs 1232 bytes (was 1244): wwm2's goto-entered outer loop (as in the wm twin func_00f72a70) plus the CONTEXT_ONLY func_0024e468. Earlier header below. */
/* Round 46 wwm2: score 39 -> 37, port.py of the wm twin func_00f72a70 draft. Earlier header below. */
/* gb.x func_00f4b978 near miss: 218 words differ, score 39 (ours 1244 bytes, original 1232). Port of wm func_00f72a70's near miss (port.py), not worked further. See the wm notes: lui s2,0x2c should go into the delay slot of the jump to the outer test, but ours schedules it before the second func_00f445a8 call (in s6). */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[4]; u8 b4; u8 pad5[2]; u8 b7; } Win;
typedef struct { u8 pad[16]; s32 x10; } Hdl;
typedef struct { u8 b0; u8 pad[3]; s32 x4; } Itm;
extern Pad D_002C5AD0;
extern s32 D_00F702F0;
extern s32 D_00F70398;
extern u8 D_00F7039C;
extern s32 D_00F703A0;
extern s32 D_00F703B8;
extern s32 D_00F703BC;
extern s32 D_00F703EC;
extern s32 D_00F703F0;
extern s32 D_00F70538, D_00F7053C, D_00F70540, D_00F70544;
extern s16 D_00F712A0[];
extern s32 D_00F829CC;
extern s32 D_00F82D6C;
void func_0011d768(s32);
Itm *func_001bc4f0(void);
s32 func_001bc520(void);
void func_001bdb58(void);
void func_001f3dc0(s32);
void func_0024e468(s32); CONTEXT_ONLY void func_0024e468(s32 a0) {}
void func_00f43cf0(s32);
void func_00f444d8(s32, s32, s32);
void *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f4d880(Win *, s32);

void func_00f4b978(s32 arg0, Hdl *h)
{
    Win *w[8];
    Win **pw;
    Win **pw2;
    s16 *ps;
    s32 t, y, k, sel, n;
    u32 a, b;
    Itm *e;

    pw = w;
    t = D_00F702F0;
    h->x10 = 109;
    y = D_00F703BC;
    ps = D_00F712A0;
    for (k = 0; k < 2; k++) {
        *pw = func_00f445a8(14, 0, 2, 1, 2, 15, *ps++, 1, D_00F70398, y, 0, D_00F703A0, 0, 0, 0, 0, 0, 256, t);
        (*pw)->b7 = D_00F7039C;
        (*pw++)->b4 = 0;
        y += D_00F703EC;
    }
    func_00f445a8(14, 3, 0, 2, 0, 0, 0, 0, 0, D_00F703BC + 12, 0, D_00F703B8, 2, D_00F70538, D_00F7053C, D_00F70540, D_00F70544, 256, t);
    func_00f445a8(14, 0, 2, 1, 0, 15, 86, 7, D_00F703B8, D_00F703BC, 0, D_00F703F0, 0, 0, 0, 0, 0, 256, t);
    goto test;
top:
        if (a & 0x2000) {
            func_0011d768(2);
            D_00F82D6C = 0;
            sel = 1;
            func_001f3dc0(D_00F829CC);
            func_0024e468(1);
            for (;;) {
                a = D_002C5AD0.x8 | D_002C5AD0.x8 >> 24;
                b = D_002C5AD0.x10 | D_002C5AD0.x10 >> 24;
                if (a & 0x4000) {
                    func_0011d768(3);
                    break;
                }
                if (a & 0x2000) {
                    func_0011d768(2);
                    if (sel == 0) {
                        n = func_001bc520();
                        for (k = 0; k < n; k++) {
                            e = func_001bc4f0() + k;
                            switch (e->b0) {
                            case 0:
                                e->x4 = 0x4000;
                                break;
                            case 1:
                                e->x4 = 0x8000;
                                break;
                            case 2:
                                e->x4 = 0x400;
                                break;
                            case 3:
                            case 4:
                            case 5:
                                e->x4 = 0x2000;
                                break;
                            case 6:
                            case 7:
                            case 8:
                                e->x4 = 0x1000;
                                break;
                            case 9:
                            default:
                                e->x4 = 0;
                                break;
                            }
                        }
                    }
                    func_001bdb58();
                    break;
                }
                if (b & 0x10) {
                    sel--;
                    if (sel < 0) {
                        if (a & 0x10) {
                            sel = 1;
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
                    if (sel >= 2) {
                        if (a & 0x40) {
                            sel = 0;
                            func_0011d768(1);
                        } else {
                            sel = 1;
                        }
                    } else {
                        func_0011d768(1);
                    }
                }
                for (k = 0; k < 2; k++) {
                    if (sel == k)
                        w[k]->b4 = 1;
                    else
                        w[k]->b4 = 0;
                }
                func_00f4d880(w[sel], 8);
                func_0024e468(1);
            }
            for (k = 0; k < 2; k++) w[k]->b4 = 0;
            D_00F82D6C = k;
            func_001f3dc0(arg0);
        }
        func_0024e468(1);
test:
    if (!((a = D_002C5AD0.x8) & 0x4000)) goto top;
    func_0011d768(3);
    func_00f444d8(14, 0, D_00F702F0);
    func_0024e468(D_00F702F0);
    func_00f43cf0(14);
}
