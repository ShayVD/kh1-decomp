#include "common.h"
#include "data/pieces/D_0035BD40.h"
typedef HpB_35BD40 HpB;
typedef EntB_35BD40 EntB;
typedef struct { u8 pad[0x21]; u8 n; u8 ids[1]; } ItB;
typedef struct { u8 pad[0xc8]; ItB *xc8; } SubB;

typedef struct { u32 x0; u8 pad4[0x68]; SubB *x6c; s32 w70; } ObjB;
s32 func_0012ca98(void);

static inline s32 inl_hp(EntB *e, s32 k) {
    if (e->x0 & 0x200) return 0;
    if (e->x6c->x40 * k < e->x6c->x3c * 255) return 0; return 1;
}

static inline s32 inl_has(ObjB *o, s32 id) {
    ItB *p; s32 n;
    s32 i;
    if (!func_0012ca98()) return 0;
    switch (o->w70) {
    case 0:
    case 8:
    case 24:
        p = o->x6c->xc8;
        for (i = 0; i < p->n; i++) {
            if (p->ids[i] == id) return 1;
        }
    }
    return 0;
}

static inline s32 inl_hp2(EntB *e, s32 k) {
    if (e->x0 & 0x200) return 0;
    if (e->x6c->x48 * k < e->x6c->x44 * 255) return 0; return 1;
}
#include "data/data_0035.h"
