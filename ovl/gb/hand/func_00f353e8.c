/* gb.x func_00f353e8: matched by hand. */
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
extern GbMap *D_00F56DC0;
extern s32 D_00F809C4;
void func_001bfac8(void);
void func_00f28c70(void);
void func_00f28e10(s32, f32, s32);
void func_00f33b88(s32);
void func_00f33bc0(s32);
void func_00f33c70(s32);
void func_00f33db8(s32);
s32 func_00f34350(s32);
s32 func_00f34948(s32);
void func_00f34aa8(void);
void func_00f34c30(void);
void func_00f34d48(s32);
void func_00f34ea8(void);
void func_00f35288(void);

/* The flag names are guesses; each one records that an entity kind in that range is on the map. */
void func_00f353e8(void) {
    s32 i;
    s32 k;
    s32 grow = 0;
    s32 burst = 0;
    s32 spin = 0;
    s32 ring = 0;
    s32 fade = 0;
    s32 flash = 0;
    s32 last = 0;
    D_00F809C4 = 1;
    for (i = 0; i < D_00F56DC0->hdr.count; i++) {
        switch (D_00F56DC0->hdr.ents[i].c) {
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
        func_00f34ea8();
        func_00f33c70(1);
        for (i = 59; i >= 0; i--)
            func_001bfac8();
        func_00f33db8(2);
    }
    if (burst) {
        func_00f34d48(burst - 1);
        func_00f33c70(burst + 1);
        for (i = 59; i >= 0; i--)
            func_001bfac8();
        func_00f33db8(3);
    }
    if (grow || burst) {
        func_00f33db8(1);
        func_00f33db8(3);
        func_00f33db8(2);
        func_00f35288();
        func_00f33c70(0);
    }
    if (spin) {
        for (i = 0; i < 60; i++) {
            k = -1;
            if (i % 6 == 0 && func_00f34948(0))
                k = 0;
            if (i % 12 == 0 && func_00f34948(1))
                k = 1;
            if (i == 0 && func_00f34948(2))
                k = 2;
            if (k >= 0)
                func_00f33b88(k);
            func_001bfac8();
        }
        for (i = 29; i >= 0; i--)
            func_001bfac8();
    }
    if (ring) {
        for (i = 0; i < 60; i++) {
            k = -1;
            if (i == 0 && func_00f34350(0))
                k = 0;
            if (i % 30 == 0 && func_00f34350(1))
                k = 1;
            if (i == 0 && func_00f34350(2))
                k = 2;
            if (k >= 0)
                func_00f33bc0(k);
            func_001bfac8();
        }
        for (i = 29; i >= 0; i--)
            func_001bfac8();
    }
    if (fade) {
        func_00f34aa8();
        for (i = 79; i >= 0; i--) {
            func_00f28e10(44, 0.5f, 0);
            func_00f28e10(45, 0.5f, 0);
            func_00f28e10(46, 0.5f, 0);
            func_00f28e10(47, 0.5f, 0);
            func_001bfac8();
        }
        func_00f28c70();
    }
    if (last) {
        func_00f34c30();
        for (i = 147; i >= 0; i--)
            func_001bfac8();
    }
    D_00F809C4 = 0;
}
