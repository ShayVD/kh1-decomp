/* 54 words left; tried variants b-c */
typedef struct { s8 a; s8 b; s8 c; } E2b598;
extern E2b598 D_00F8BBC8[];
extern s32 D_00F8AA88[];
void func_001c0da0(s32, s32, s8 *);
CONTEXT_ONLY s32 func_00f2ab98(s32 arg0) {
    s8 b[16];
    func_001c0da0(arg0 + 752, 1, b);
    return b[0];
}

static inline s32 big_2b598(void) {
    if ((func_00f2ab98(7) & 0xF) < 2) return 0;
    return 1;
}

s32 *func_00f2b598(s32 arg0, s32 arg1) {
    s32 ok;
    s32 i;
    if (arg0 == 27) arg0 = 13;
    if (arg1 == 27) arg1 = 13;
    ok = big_2b598() && ((arg0 == 9 && arg1 == 10) || (arg0 == 10 && arg1 == 9));
    if (!ok) {
        for (i = 0; D_00F8BBC8[i].a >= 0; i++) {
            if (D_00F8BBC8[i].a == arg0 && D_00F8BBC8[i].b == arg1) {
                return &D_00F8AA88[D_00F8BBC8[i].c];
            }
        }
    }
    for (i = 0; D_00F8BBC8[i].a >= 0; i++) {
        if (D_00F8BBC8[i].a == 99 && D_00F8BBC8[i].b == arg1) {
            return &D_00F8AA88[D_00F8BBC8[i].c];
        }
    }
    return NULL;
}
