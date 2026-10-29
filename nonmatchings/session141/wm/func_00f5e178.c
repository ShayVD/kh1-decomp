/* 4 words. Twin of f355a8 (same lui order issue); fix one and the other should follow. */
typedef struct { u8 pad[8]; u8 b8; } I5e178;
typedef struct { s32 r; u8 pad[36]; } E5e178;
I5e178 *func_001bb658(s32);
s32 func_00f4a958(s32);
s32 func_00f650e8(s32);
void func_001be820(void *, s32);
extern E5e178 *D_0108DB90[192];
extern E5e178 D_0108D190[];

void func_00f5e178(void) {
    s32 i;
    I5e178 *info;
    s32 r;
    E5e178 *p;

    for (i = 191; i >= 0; i--) {
        D_0108DB90[i] = 0;
    }
    p = D_0108D190;
    for (i = 128; i < 160; i++) {
        info = func_001bb658(i);
        if (info != NULL && info->b8 != 255) {
            r = func_00f650e8(func_00f4a958(info->b8));
            if (r != 0) {
                func_001be820(p, 40);
                p->r = r;
                D_0108DB90[info->b8] = p;
                p++;
            }
        }
    }
}
