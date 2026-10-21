#include "common.h"

#include "data/pieces/D_002A6308.h"
#include "data/pieces/D_002A6318.h"
#include "data/pieces/D_002A6324.h"
void func_00104908(void) {
    (*(s32 (*)[3])&D_002A6318)[0] = (*(s32 (*)[3])&D_002A6308)[0] = (*(s32 (*)[3])&D_002A6318)[1] = (*(s32 (*)[3])&D_002A6318)[2] = (*(s32 (*)[3])&D_002A6308)[1] = (*(s32 (*)[3])&D_002A6308)[2] = -1;
    D_002A6324 = 0;
}

#include "data/types/text_00100000_s6_na.h"
extern E4 D_002BCB80[];
extern s32 D_002BC128;
extern s32 D_002BC130;
void func_00111480(void);
void func_00111380(void);
void func_001113f8(s32);

void func_00111510(void) {
    s32 i;
    E4 *e;
    func_00111480();
    for (i = 0; i < 39; i++) {
        e = &D_002BCB80[i];
        if (D_002BC128 == e->a && D_002BC130 == e->b) {
            func_001113f8(e->c);
            return;
        }
    }
    func_00111380();
}

typedef struct {
    u8 pad[7];
    u8 f7;
    u8 pad8[0x14];
} It28;
extern It28 *D_0062321C; /* src/data/bss_0062.c: s32 D_0062321C */

s32 func_001bb6d0(s32 i) {
    u8 x = D_0062321C[i].f7; s32 a, b; u16 c; a = (x & 3) + 1; x >>= 2; b = (x & 3) * 16 + 16; x >>= 2; c = (x & 3) + 1; return b | a | (c << 8);
}

/* func_001cdc58: 2 words off (strict src/hand, vm16.inc types). sw x (4) and sw zero (24) swapped around the jal delay slot; all statement orders give the same. */
typedef struct { u8 pad0[0x10]; f32 pos[3]; } Actor;
typedef struct {
    s32 x0;
    Actor *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    u8 pad24[0x15c];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VM;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
s32 func_001c4640(Msg *m);
s32 func_001cdc58(VM *vm) {
    Msg m;
    m.type = 15;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}
#include "data/data_002B.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002BCB80.h"
