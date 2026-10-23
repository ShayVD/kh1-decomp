#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/vm_rec.h"
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

typedef W606Mem_304be8 C116;
typedef struct { u8 pad[0x48e]; u8 f48e[4]; } W17;

s32 func_001eeeb8(s32 id) {
    s32 n = 0, i;
    u8 c;
    C116 *e;
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c == 0xff) break;
        e = &D_00304BE8->m[c];
        if (e->sub.x32 == id) n++;
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
        e = &D_00304BE8->m[c];
        for (j = 0; j < e->sub.x18; j++) {
            if (e->sub.x19[j] == id) n++;
        }
    }
    return n;
}

/* func_001e99e8 is in src/vm/vm_find.nofill.c. */
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
