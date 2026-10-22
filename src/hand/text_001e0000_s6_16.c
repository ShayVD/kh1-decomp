#include "common.h"
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
typedef struct { s32 x0; u8 pad[844]; } E848;
s32 func_001c4640(Msg *m);

void func_001ea128(char *dst, char *src) {
    s32 n = 0, i = 0;
    while (src[i] != 0) {
        dst[n] = src[i];
        if ((u8)(src[i] - 5) < 3) {
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
        } else if (src[i] == 11) {
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
        } else if (src[i] == 10) {
            i++; n++;
            dst[n] = src[i];
            if (dst[n] == 0) {
                i++; n++;
                dst[n] = src[i];
                i++; n++;
                dst[n] = src[i];
            }
        } else if (src[i] == 13) {
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
        }
        if ((u8)(src[i] - 9) < 23) {
            i++; n++;
            dst[n] = src[i];
        }
        i++; n++;
    }
    dst[n] = 0;
}

s32 func_001ea5f8(E848 *e) {
    Msg m;
    m.type = 13;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = e->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001ea658(E848 *e) {
    Msg m;
    m.type = 14;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = e->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001ea808(E848 *e) {
    Msg m;
    m.type = 35;
    m.val = 0;
    m.x = e->x0;
    func_001c4640(&m);
    m.type = 42;
    m.val = 0;
    m.x = e->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001ea888(E848 *e) {
    Msg m;
    m.type = 36;
    m.val = 0;
    m.x = e->x0;
    func_001c4640(&m);
    m.type = 43;
    m.val = 0;
    m.x = e->x0;
    func_001c4640(&m);
    return 2;
}

typedef struct { u8 pad[28]; u8 n1c; u8 l1d[25]; u8 b36; u8 pad37[116 - 55]; } C116;
typedef struct { u8 pad[0x48e]; u8 f48e[4]; } W17;
#include "data/pieces/D_00304BE8_s.h"

s32 func_001eeeb8(s32 id) {
    s32 n = 0, i;
    u8 c;
    C116 *e;
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c == 0xff) break;
        e = &((C116 *)D_00304BE8)[c];
        if (e->b36 == id) n++;
    }
    return n;
}

s32 func_001eef38(s32 id) {
    s32 n = 0, i, j;
    u8 c;
    C116 *e;
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c == 0xff) break;
        e = &((C116 *)D_00304BE8)[c];
        for (j = 0; j < e->n1c; j++) {
            if (e->l1d[j] == id) n++;
        }
    }
    return n;
}

typedef struct { u8 pad[0x3034]; s32 f3034; s32 f3038; u8 pad2[0x316c - 0x303c]; s32 f316c; } B9C90;
#include "data/types/text_001e0000_s6_16.h"
extern B9C90 D_00389C90;
extern s32 D_003C54F0, D_003B4D90, D_003C21A0, D_0039A570, D_003A7980;
#include "data/pieces/D_003C3A70.h"
#include "data/pieces/D_003B4DA0.h"
#include "data/pieces/D_003A7990.h"
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0038D170.h"

s32 func_001e99e8(s32 kind, E848b *p) {
    s32 i;
    if (D_00389C90.f316c) {
        for (i = 0; i < D_003C54F0; i++) if (&D_003C3A70[i] == p) return i;
    } else if (kind == 1) {
        if (D_00389C90.f3038 == 0) {
            for (i = 0; i < D_003B4D90; i++) if (&D_003A7990[i] == p) return i;
        } else {
            for (i = 0; i < D_003C21A0; i++) if (&((E848b *)&D_003B4DA0)[i] == p) return i;
        }
    } else {
        if (D_00389C90.f3034 == 0) {
            for (i = 0; i < D_0039A570; i++) if (&((E848b *)&D_0038D170)[i] == p) return i;
        } else {
            for (i = 0; i < D_003A7980; i++) if (&((E848b *)&D_0039A580)[i] == p) return i;
        }
    }
    return -1;
}
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
