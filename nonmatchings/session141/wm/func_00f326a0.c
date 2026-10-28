/* 9 words left (same size); tried a reordered and a b-variant, both worse */
typedef struct { s32 used; s32 val; u32 time; u8 pad[20]; } E326a0;
extern E326a0 D_00FBB5D0[16];

s32 func_00f326a0(void) {
    s32 i;
    s32 idx = -1;
    u32 best = -1;
    E326a0 *e = D_00FBB5D0;
    for (i = 0; i < 16; i++, e++) {
        if (e->used != 0) {
            if ((s32)best < 0 || e->time < best) {
                best = e->time;
                idx = i;
            }
        }
    }
    if (idx < 0) {
        return -1;
    }
    return D_00FBB5D0[idx].val;
}
