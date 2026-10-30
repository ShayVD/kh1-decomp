/* Round 41 wwm2: score 37 -> 25 (77 -> 12 words, 372 vs 376 with the trailing nop). Two changes: index the groups as g[i].offset / g[i].count instead of stepping g, and divide the sums in place (sx /= f->n; ... *ox = sx;), so each quotient reuses its sum's register. Left: register naming of h, the group count and i in the outer loop. The original keeps h in v1 with a copy in a1 and the count in t1 with a copy in a0; ours keeps h in t8 and copies the count and g. Tried g set before or in the for, an n = h->count bound (27), h assigned late. */
/* func_00f79868: 77 words differ, score 37 (364 vs 376 bytes). Round 29 (wgb): the loop test `i < h->count` with f based on h moves `i = 0` to the top as in the target (78 -> 77 words). Left: the target keeps copies of the header pointer (move a1,v1) and of the group count (move a0,t1) for the loops, and gives every failed test its own likely-slot i++, three words more. Tried i declared or set first, a separate base pointer, D_0108F6B8 read in the loop (worse, reloads), while-loop form, (s32) casts, all flag modes; an earlier permuter run found nothing. */
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
    s32 i;
    s32 j;
    s32 k;
    f32 sx;
    f32 sy;
    f32 sz;

    for (i = 0; i < h->count; i++) {
        Face *f = (Face *)((u8 *)h + g[i].offset);
        for (j = 0; j < g[i].count; j++, f++) {
            if (id == f->id && (u32)id < 28 && (u32)id >= 2 && (any || (D_00FB649C[id + 16] & 4))) {
                if ((u32)(f->n - 3) < 2) {
                    sx = sy = sz = 0.0f;
                    for (k = 0; k < f->n; k++) {
                        sx += f->x[k];
                        sy += f->y[k];
                        sz += f->z[k];
                    }
                    sx /= f->n;
                    sy /= f->n;
                    sz /= f->n;
                    *ox = sx;
                    *oy = sy;
                    *oz = sz;
                    return 1;
                }
            }
        }
    }
    return 0;
}
