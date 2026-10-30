/* wm.x func_00f5c4e0: matched by hand. */
#include "ovl.h"

typedef struct { u16 a, b, c, flags, d, e; } GbEnt;
typedef struct {
    u8 pad0[4];
    u16 count;
    u16 w;
    u16 pad8;
    u16 h;
    u8 padc[0x70 - 0xC];
    GbEnt ents[1];
} GbHdr;
typedef struct {
    u8 pad0[0xA0];
    GbHdr hdr;
} GbMap;
extern GbMap *D_00F9B540;
extern s32 D_0108D184;
void func_001bfac8(void);
void func_00f4fd68(void);
void func_00f4ff08(s32, f32, s32);
void func_00f5ac80(s32);
void func_00f5acb8(s32);
void func_00f5ad68(s32);
void func_00f5aeb0(s32);
s32 func_00f5b448(s32);
s32 func_00f5ba40(s32);
void func_00f5bba0(void);
void func_00f5bd28(void);
void func_00f5be40(s32);
void func_00f5bfa0(void);
void func_00f5c380(void);

/* The flag names are guesses; each one records that an entity kind in that range is on the map. */
void func_00f5c4e0(void) {
    s32 i;
    s32 k;
    s32 grow = 0;
    s32 burst = 0;
    s32 spin = 0;
    s32 ring = 0;
    s32 fade = 0;
    s32 flash = 0;
    s32 last = 0;
    D_0108D184 = 1;
    for (i = 0; i < D_00F9B540->hdr.count; i++) {
        switch (D_00F9B540->hdr.ents[i].c) {
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            grow = 1;
            break;
        case 45:
        case 46:
        case 47:
        case 48:
            fade = 1;
            break;
        case 49:
            last = 1;
            break;
        case 59:
        case 60:
        case 61:
            spin = 1;
            break;
        case 62:
        case 63:
        case 64:
            ring = 1;
            break;
        case 53:
            burst = 1;
            break;
        case 54:
            burst = 2;
            break;
        }
    }
    if (grow) {
        func_00f5bfa0();
        func_00f5ad68(1);
        for (i = 59; i >= 0; i--)
            func_001bfac8();
        func_00f5aeb0(2);
    }
    if (burst) {
        func_00f5be40(burst - 1);
        func_00f5ad68(burst + 1);
        for (i = 59; i >= 0; i--)
            func_001bfac8();
        func_00f5aeb0(3);
    }
    if (grow || burst) {
        func_00f5aeb0(1);
        func_00f5aeb0(3);
        func_00f5aeb0(2);
        func_00f5c380();
        func_00f5ad68(0);
    }
    if (spin) {
        for (i = 0; i < 60; i++) {
            k = -1;
            if (i % 6 == 0 && func_00f5ba40(0))
                k = 0;
            if (i % 12 == 0 && func_00f5ba40(1))
                k = 1;
            if (i == 0 && func_00f5ba40(2))
                k = 2;
            if (k >= 0)
                func_00f5ac80(k);
            func_001bfac8();
        }
        for (i = 29; i >= 0; i--)
            func_001bfac8();
    }
    if (ring) {
        for (i = 0; i < 60; i++) {
            k = -1;
            if (i == 0 && func_00f5b448(0))
                k = 0;
            if (i % 30 == 0 && func_00f5b448(1))
                k = 1;
            if (i == 0 && func_00f5b448(2))
                k = 2;
            if (k >= 0)
                func_00f5acb8(k);
            func_001bfac8();
        }
        for (i = 29; i >= 0; i--)
            func_001bfac8();
    }
    if (fade) {
        func_00f5bba0();
        for (i = 79; i >= 0; i--) {
            func_00f4ff08(44, 0.5f, 0);
            func_00f4ff08(45, 0.5f, 0);
            func_00f4ff08(46, 0.5f, 0);
            func_00f4ff08(47, 0.5f, 0);
            func_001bfac8();
        }
        func_00f4fd68();
    }
    if (last) {
        func_00f5bd28();
        for (i = 147; i >= 0; i--)
            func_001bfac8();
    }
    D_0108D184 = 0;
}
