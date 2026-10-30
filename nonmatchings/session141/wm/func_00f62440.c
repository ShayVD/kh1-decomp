/* Round 51 (wgb): value fix, score 96 -> 92. The drafttwins port kept the gb callbacks func_00f3b0b8 / func_00f3b250 as the func_001c01b0 arguments; the target passes the wm twins func_00f621b0 / func_00f62348 (lui 0xf6 + 8624 / 9032). Found by r51/audit.py (per-jal argument sources). Earlier header below. */
/* drafttwins.py: score 98 -> 96, port.py of the gb twin func_00f3b348 draft. Earlier header below. */
/* func_00f62440: near miss (session 141 round 4), score 98: switch, loop and the call args are right. The original copies the 3-word vectors and the halved colour bytes field by field through several pointer copies (move a2,t0 / move a0,a2 ...), which looks like nested inline helpers; plain struct copies give ldl/sdl, and simple cp3/half3 inline helpers do not reproduce the copies. */
typedef struct { s32 v[3]; s32 pad; } GbRec;
extern GbRec D_0108EE00[];
extern u8 D_00379F28[];
extern u8 *D_00F9B540;
s32 func_00f60f88(void);
void func_001c01b0(s32, void *, ...);
void func_001bfac8(void);
void func_00f621b0();
void func_00f62348();

void func_00f62440(s32 id) {
    s32 pos[4];
    s32 col[4];
    s32 i;
    s32 c = func_00f60f88();
    u8 *src = &D_00379F28[c * 4];
    GbRec *r = &D_0108EE00[id];
    col[0] = src[0] >> 1;
    pos[1] = r->v[1];
    col[2] = src[2] >> 1;
    col[1] = src[1] >> 1;
    pos[0] = r->v[0];
    pos[2] = r->v[2];
    D_00F9B540[id] = c;
    for (i = 0; i < 30; i++) {
        switch (i) {
        case 0:
            func_001c01b0(-1, func_00f621b0, 0, col);
            break;
        case 6:
            func_001c01b0(-1, func_00f621b0, 1, col);
            break;
        case 12:
            func_001c01b0(-1, func_00f621b0, 2, col);
            break;
        case 18:
            func_001c01b0(-1, func_00f62348, id, pos, col);
            break;
        }
        func_001bfac8();
    }
    r = &D_0108EE00[id];
    r->v[1] = col[1];
    r->v[0] = col[0];
    r->v[2] = col[2];
}
