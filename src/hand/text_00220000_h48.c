#include "common.h"
#include "data/bss_0064.h"

typedef int u128 __attribute__((mode(TI)));

extern void *D_003F71C8[];

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
