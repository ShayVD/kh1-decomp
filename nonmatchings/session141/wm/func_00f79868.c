/* func_00f79868: score 37, 78 words differ. see diff; permuter tried */
typedef struct {
    s32 x0;
    s32 n;
    s32 id;
    f32 x[4];
    f32 y[4];
    f32 z[4];
    u8 pad3C[0x5C - 0x3C];
} Face;

typedef struct {
    s32 count;
    s32 offset;
} Group;

typedef struct {
    s32 count;
    s32 offset;
} MapHdr;

extern MapHdr *D_0108F6B8;
extern u8 D_00FB649C[];

s32 func_00f79868(f32 *ox, f32 *oy, f32 *oz, s32 id, s32 any) {
    MapHdr *h = D_0108F6B8;
    Group *g = (Group *)((u8 *)h + h->offset);
    s32 n = h->count;
    u8 *base = (u8 *)h;
    s32 i;
    s32 j;
    s32 k;
    f32 sx;
    f32 sy;
    f32 sz;

    for (i = 0; i < n; i++, g++) {
        Face *f = (Face *)(base + g->offset);
        for (j = 0; j < g->count; j++, f++) {
            if (id == f->id && (u32)id < 28 && (u32)id >= 2 && (any || (D_00FB649C[id + 16] & 4))) {
                if ((u32)(f->n - 3) < 2) {
                    sx = sy = sz = 0.0f;
                    for (k = 0; k < f->n; k++) {
                        sx += f->x[k];
                        sy += f->y[k];
                        sz += f->z[k];
                    }
                    *ox = sx / f->n;
                    *oy = sy / f->n;
                    *oz = sz / f->n;
                    return 1;
                }
            }
        }
    }
    return 0;
}
