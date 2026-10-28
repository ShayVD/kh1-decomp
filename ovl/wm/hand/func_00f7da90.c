/* wm.x func_00f7da90: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
} Hdr;

typedef struct {
    s32 x0;
    s32 x4;
    f32 x8;
    s32 xC;
    f32 x10;
} Ent;

typedef struct {
    void (*f0)(void);
    void (*f4)(void);
    void (*f8)(void *, s32, s32);
} Mode;

extern s32 D_0108F6B4;
extern u8 D_00FBA718[];
extern u8 D_00FBA730[];
extern u8 D_00FBA748[];
extern u8 D_00FBA760[];
extern u8 D_00FBA778[];
extern u8 D_00FBA790[];
extern u8 D_00FBA7A8[];
extern u8 D_00FBA7C0[];
extern u8 D_00FB5C48[];
extern s32 D_0108F5D0[28];
extern s32 D_0108F640[28];
extern s32 D_0108FA68;
extern s32 D_0108FA7C;
extern s32 D_0108FA78;
extern s32 D_0108F6E8;
extern s32 D_0108FA6C;
extern s32 D_0108F6D4;
extern Hdr D_0108F6B8;
extern s32 D_0108F6D0;
extern s32 D_0108F6C8;
extern s32 D_0108F6CC;
extern Ent D_00FB5ED8[28];
extern s32 D_0108F6EC;
extern s32 D_00FB6108;
extern s32 D_00FB6164;
extern Mode *D_00FB5EA8;
extern s32 D_002B6774;
extern s32 D_002BBE0C;
extern s32 D_00FB6544;
s32 func_00f78838(void *, s32, s32, s32 *);
void func_00f78690(s32 *);
void func_0024bc08(s32, void *);
void func_00f787b0(s32);
s32 func_001b9e88(void);
CONTEXT_ONLY void func_00f7bde0(void) {}
void func_00f7b9e0(s32);
void func_00f7da20(void);
void func_00f7d0a8(void);
void func_0024e468(s32);
void func_00106780(s32);
void func_00106a58(s32);

void func_00f7da90(void) {
    s32 i;
    s32 j;
    s32 t;
    s32 v;

    func_00f78838(D_00FBA718, D_0108F6B4, 256, NULL);
    func_00f78690((s32 *)D_0108F6B4);
    for (i = 0; i < 28; i++) {
        D_0108F5D0[i] = 0;
        D_0108F640[i] = 0;
    }
    func_00f78838(D_00FBA730, D_0108F6B4, 256, NULL);
    func_0024bc08(D_0108F6B4, D_00FB5C48);
    D_0108FA78 = D_0108FA7C = D_0108FA68 = D_0108FA6C = D_0108F6D4 = 0;
    D_0108F6E8 = 0;
    t = D_0108F6B4;
    D_0108F6B8.x0 = t;
    D_0108F6B8.x4 = v = func_00f78838(D_00FBA748, t, 256, NULL);
    D_0108F6B8.x8 = v = func_00f78838(D_00FBA760, v, 256, NULL);
    D_0108F6D0 = v = func_00f78838(D_00FBA778, v, 256, NULL);
    D_0108F6C8 = v = func_00f78838(D_00FBA790, v, 16, NULL);
    D_0108F6CC = v = func_00f78838(D_00FBA7A8, v, 16, NULL);
    func_00f78838(D_00FBA7C0, v, 16, NULL);
    for (i = 0; i < 28; i++) {
        D_00FB5ED8[i].x4 = 0;
        D_00FB5ED8[i].x8 = D_00FB5ED8[i].x10;
    }
    for (i = 2; i < 28; i++) {
        if ((u32)i < 28 && (u32)i >= 2) {
            for (j = 0; j < D_00FB5ED8[i].x0; j++) {
                func_00f787b0(i);
            }
        }
    }
    if (func_001b9e88()) {
        D_0108F6EC = 1;
    } else {
        D_0108F6EC = 0;
    }
    func_00f7bde0();
    func_00f7b9e0(D_00FB6108);
    func_00f7da20();
    D_00FB6164 = 0;
    D_00FB5EA8->f8(func_00f7d0a8, 1, 0);
    func_0024e468(2);
    while (D_002B6774) {
        func_0024e468(1);
    }
    D_002BBE0C = 1;
    for (i = 0; i < 2; i++) {
        func_00f7bde0();
        func_00f7b9e0(D_00FB6108);
        func_0024e468(1);
    }
    func_0024e468(4);
    if (D_00FB6544 == 0) {
        func_00106780(30);
    } else {
        func_00106a58(30);
    }
    for (i = 0; i < 30; i++) {
        func_00f7bde0();
        func_00f7b9e0(D_00FB6108);
        func_0024e468(1);
    }
    D_0108F6D4 = 1;
    D_00FB6164 = 1;
    for (;;) {
        func_00f7bde0();
        func_00f7b9e0(D_00FB6108);
        func_0024e468(1);
    }
}
