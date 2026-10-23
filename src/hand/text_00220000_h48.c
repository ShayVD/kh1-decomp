#include "common.h"
#include "data/bss_0064.h"

typedef int u128 __attribute__((mode(TI)));
s16 *func_0011ef10(s32, void *);
void func_001f3110(void);
void *func_001f31a8(void *, s32);

extern void *D_003F71C8[];

typedef struct { u8 pad[0x664]; u32 x664, x668, x66c, x670; } Scr;
#include "data/types/text_00220000_h48.h"
extern s32 D_003F7EC4;
extern s32 D_003F7EC8;
extern Win D_003F7EA0;
extern s32 D_006476F8;
extern s32 D_006476FC;
extern Scr *D_00647700; /* src/data/bss_0064.c: u16 *D_00647700 */
extern void *D_00647704; /* src/data/bss_0064.c: u8 *D_00647704 */
extern void *D_00647708; /* src/data/bss_0064.c: s32 D_00647708 */
extern void *D_0064770C;
void func_00232960(void);

void func_002329a0(Scr *arg0, s32 arg1, s32 arg2) {
    u32 x, y;
    s32 w;
    func_001f3110();
    D_003F7EC4 = 1;
    D_003F7EC8 = 1;
    D_00647700 = arg0;
    D_006476F8 = arg1;
    D_006476FC = arg2;
    D_00647704 = (u8 *)arg0 + 4;
    D_00647708 = (u8 *)arg0 + 0x644;
    x = (arg0->x664 - 0x7000) >> 4;
    y = (arg0->x668 - 0x7400) >> 4;
    w = ((arg0->x66c - 0x7000) >> 4) - x;
    D_003F7EA0.x10 = w + 1;
    D_003F7EA0.x12 = ((arg0->x670 - 0x7400) >> 4) - y + 1;
    D_003F7EA0.x18 = w - 39;
    D_003F7EA0.xc = x;
    D_003F7EA0.xe = y;
    D_0064770C = func_001f31a8(&D_003F7EA0, 0);
    func_0011ef10(0x2C01A, func_00232960);
}

typedef struct { s32 type; s32 id; s32 a[6]; } Cmd;
extern Cmd D_006477B0[64];
extern s32 D_00647FB0;
extern s32 D_00647FB8;
extern s32 D_00647FBC;
extern s32 D_00647FC4;

s32 func_00233d08(s32 id) {
    s32 i, x;
    if (id != 0) {
        i = D_00647FBC;
        while (i != D_00647FB8) {
            x = D_006477B0[i].id;
            i++;
            i &= 63;
            if (x == id) {
                goto found;
            }
        }
        if (D_00647FB0 == 0 || D_00647FC4 != id) {
            goto none;
        }
    found:
        return 1;
    }
    if (D_00647FB8 != D_00647FBC || D_00647FB0 != 0) {
        goto found;
    }
none:
    return 0;
}

extern s32 D_00647FC0;

s32 func_00234098(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 2;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[4] = arg4;
    return id;
}

s32 func_00234148(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 3;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}

s32 func_00234440(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 8;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}

s32 func_002345a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 10;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}

s32 func_00234668(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 11;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}

s32 func_00234730(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 9;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[4] = arg4;
    return id;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_003F7090[];
extern u8 D_003F70C0[];
extern u8 D_003F7100[];
extern u8 D_003F7140[];
extern u8 D_003F7170[];
void *D_003F71C8[0x6] ALIGNED(8) = {
    (void *)D_003F7170, (void *)D_003F7140, (void *)D_003F7100, (void *)D_003F70C0,
    (void *)D_003F7090, 0,
};
#include "data/data_003F.h"
#include "data/pieces/D_003F7EA0.h"
