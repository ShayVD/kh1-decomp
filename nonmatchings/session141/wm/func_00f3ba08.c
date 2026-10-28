/* 6 words left; tried 9 variants (a-i) */
typedef struct { s32 type; s32 a; s32 b; u8 pad[36]; } C3ba08;
typedef struct { u8 pad[0xA0]; s32 flags; u32 mask; s32 id; C3ba08 *conds; s32 cnt; u8 pad2[12]; } E3ba08;
typedef struct { u16 h0; u16 h2; u16 h4; u16 h6; } R3ba08;
typedef struct { u8 pad[0x540]; s32 x540; } G3ba08;
extern E3ba08 D_01067FE0[];
extern G3ba08 *D_00F864C0;
extern s32 D_00F850A4;
R3ba08 *func_00f3f260(s32, s32);
s32 func_00f3b8d0(s32, E3ba08 *, C3ba08 *);
void func_001c0310(s32, void (*)(E3ba08 *, C3ba08 *), ...);
void func_00f3b860(E3ba08 *, C3ba08 *);
void func_001bfac8(void);

void func_00f3ba08(s32 arg0) {
    E3ba08 *e = &D_01067FE0[arg0];
    C3ba08 *conds = e->conds;
    R3ba08 *r;
    C3ba08 *c;
    s32 i;
    u32 bit;
    e->cnt = 0;
    while ((e->flags & 1) && (r = func_00f3f260(e->id, D_00F864C0->x540)) != NULL && !(u16)(r->h6 & 1)) {
        if (D_00F850A4 == 0) {
            {
                s32 one = 1;
                c = conds;
                for (i = 0; i < 32 && c->type != one; i++, c++) {
                    bit = one << i;
                    if (!(e->mask & bit)) {
                        if (func_00f3b8d0(e->cnt, e, c)) {
                            e->mask |= bit;
                            func_001c0310(-1, func_00f3b860, e, c);
                        }
                    }
                }
            }
            e->cnt++;
        }
        func_001bfac8();
    }
    e->flags = 0;
}
