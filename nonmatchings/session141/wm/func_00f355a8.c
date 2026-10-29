/* 4 words. Only the order of the two lui (v0 vs v1) differs. Tried CONTEXT_ONLY subsets, all modes, p init placement, first loop shape, tbl local. */
typedef struct { u8 pad[8]; u8 b8; } I355a8;
typedef struct { s32 r; u8 pad[36]; } E355a8;
I355a8 *func_001bb658(s32);
s32 func_00f200a8(s32);
s32 func_00f650e8(s32);
void func_001be820(void *, s32);
extern E355a8 *D_00FCE040[192];
extern E355a8 D_00FCD640[];

void func_00f355a8(void) {
    s32 i;
    I355a8 *info;
    s32 r;
    E355a8 *p;

    for (i = 191; i >= 0; i--) {
        D_00FCE040[i] = 0;
    }
    p = D_00FCD640;
    for (i = 128; i < 160; i++) {
        info = func_001bb658(i);
        if (info != NULL && info->b8 != 255) {
            r = func_00f650e8(func_00f200a8(info->b8));
            if (r != 0) {
                func_001be820(p, 40);
                p->r = r;
                D_00FCE040[info->b8] = p;
                p++;
            }
        }
    }
}
