/* func_001cf3e0: 19 words (score 6), nostrict_nogcse; same as 001cf348. */
typedef struct { u8 pad[12400]; u64 d12400; } Big3;
extern Big3 D_00389C90;
typedef struct { s32 x0; u8 n; s32 off[1]; } Tbl;
extern Tbl *D_003DABD4;
void func_00155be0(void *p);
void func_001cf3e0(void) {
    Tbl *base;
    Tbl *t;
    s32 i, n;
    D_00389C90.d12400 &= ~0x400000000ULL;
    base = D_003DABD4;
    n = base->n;
    t = base;
    for (i = 0; i < n; i++) {
        func_00155be0((u8 *)t + *(s32 *)(i * 4 + (u8 *)t + 8));
        t = base;
    }
}
