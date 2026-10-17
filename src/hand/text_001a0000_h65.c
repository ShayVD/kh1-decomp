#include "common.h"

typedef struct { u8 b[64]; } Blk64;
typedef struct { u8 pad[0x9c20]; Blk64 a; u8 pad2[0xa420 - 0x9c60]; Blk64 b; } SaveRow;
void func_001b9b30(void);
Blk64 *func_00232cc0(s32);
s32 func_001baf70(s32, Blk64 *, Blk64 *);

s32 func_001bafb0(s32 i, Blk64 *src) {
    SaveRow *r;
    func_001b9b30();
    r = (SaveRow *)(i * 64 + (u32)func_00232cc0(4));
    r->a = *src;
    if (func_001baf70(i, src, &r->b) > 0) {
        r->b = *src;
        return 1;
    }
    return 0;
}

/* needs make: uses rodata */

typedef struct { u8 id; u8 b; u8 pad[2]; s32 c; } Ent8;
extern Ent8 D_00625750[];
extern s32 D_00625748;
u8 func_001be600(s32);
s32 func_001b9df0(s32);
s32 func_001ba3d8(void);
s32 func_001ba3f0(s32);
typedef struct { u16 id; u8 pad[10]; } It12;
typedef struct { u16 n; u8 pad[0x6e]; It12 it[1]; } ItList;
typedef struct { s32 x0; ItList l; } ItOwner;

void func_001bd880(void) {
    s32 f[16];
    s32 i, k, n;
    Ent8 *base = D_00625750;
    Ent8 *e;

    for (i = 0; i < 16; i++)
        f[i] = 0;
    for (i = 0; i < func_001ba3d8(); i++) {
        if (func_001ba3f0(i) <= 0)
            continue;
        k = -1;
        switch (i) {
        case 4: case 5: case 6: case 7: case 8:
            k = 0;
            break;
        case 52: case 53:
            k = 1;
            break;
        case 48:
            k = 2;
            break;
        case 58:
            k = 3;
            break;
        case 59:
            k = 4;
            break;
        case 60:
            k = 5;
            break;
        case 61:
            k = 6;
            break;
        case 62:
            k = 7;
            break;
        case 63:
            k = 8;
            break;
        case 44: case 45: case 46: case 47:
            k = 9;
            break;
        }
        f[k] = 1;
    }
    n = 0;
    e = base;
    for (i = 0; i < 10; i++) {
        if (f[i]) {
            e->id = i;
            e->b = func_001be600(i);
            e->c = func_001b9df0(i);
            e++;
            n++;
        }
    }
    D_00625748 = n;
}

void func_001bd9e8(ItOwner *o) {
    s32 f[16];
    s32 i, k, n;
    Ent8 *base = D_00625750;
    Ent8 *e;

    for (i = 0; i < 16; i++)
        f[i] = 0;
    for (i = 0; i < o->l.n; i++) {
        k = -1;
        switch (o->l.it[i].id) {
        case 5: case 6: case 7: case 8: case 9:
            k = 0;
            break;
        case 53: case 54:
            k = 1;
            break;
        case 49:
            k = 2;
            break;
        case 59:
            k = 3;
            break;
        case 60:
            k = 4;
            break;
        case 61:
            k = 5;
            break;
        case 62:
            k = 6;
            break;
        case 63:
            k = 7;
            break;
        case 64:
            k = 8;
            break;
        case 45: case 46: case 47: case 48:
            k = 9;
            break;
        }
        f[k] = 1;
    }
    n = 0;
    e = base;
    for (i = 0; i < 10; i++) {
        if (f[i]) {
            e->id = i;
            n++;
            e->b = func_001be600(i);
            e->c = func_001b9df0(i);
            e++;
        }
    }
    D_00625748 = n;
}
