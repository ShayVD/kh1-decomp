/* func_00f62440: near miss (session 141 round 4), score 98: switch, loop and the call args are right. The original copies the 3-word vectors and the halved colour bytes field by field through several pointer copies (move a2,t0 / move a0,a2 ...), which looks like nested inline helpers; plain struct copies give ldl/sdl, and simple cp3/half3 inline helpers do not reproduce the copies. */
typedef s32 V3i[3];
typedef struct {
    V3i v;
    s32 pad;
} E16;
typedef struct {
    V3i a;
    s32 pad;
    V3i b;
} Loc;

extern E16 D_0108EE00[];
extern u8 D_00379F28[][4];
extern u8 *D_00F9B540;
s8 func_00f60f88(void);
void func_001c01b0();
void func_001bfac8(void);
void func_00f621b0();
void func_00f62348();

static inline void cp3(s32 *d, s32 *s) {
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
}
static inline void half3(s32 *d, u8 *c) {
    d[0] = c[0] >> 1;
    d[1] = c[1] >> 1;
    d[2] = c[2] >> 1;
}

void func_00f62440(s32 idx) {
    Loc l;
    u8 *col;
    s32 i;
    s8 c;

    c = func_00f60f88();
    col = D_00379F28[c];
    cp3(l.a, D_0108EE00[idx].v);
    half3(l.b, col);
    D_00F9B540[idx] = c;
    for (i = 0; i < 30; i++) {
        switch (i) {
        case 0:
            func_001c01b0(-1, func_00f621b0, 0, l.b);
            break;
        case 6:
            func_001c01b0(-1, func_00f621b0, 1, l.b);
            break;
        case 12:
            func_001c01b0(-1, func_00f621b0, 2, l.b);
            break;
        case 18:
            func_001c01b0(-1, func_00f62348, idx, l.a, l.b);
            break;
        }
        func_001bfac8();
    }
    cp3(D_0108EE00[idx].v, l.b);
}
