/* loop GIV split: target uses a1 pointer to flags plus an offset reg; tried variants b-d */
typedef struct { u8 pad[0x40]; f32 m[4][4]; f32 v80[4]; f32 v90[4]; s32 flags; u32 mask; s32 id; void *conds; s32 cnt; u8 pad2[12]; } E3bc48;
typedef struct { u8 pad[0x20]; u16 h20; } R3bc48;
typedef struct { u16 h0; u16 h2; u16 h4; } Q3bc48;
typedef struct { u8 pad[0x540]; s32 x540; } G3bc48;
extern E3bc48 D_01067FE0[256];
extern G3bc48 *D_00F864C0;
extern s32 D_00F8704C;
void func_00f3bbf8(E3bc48 *);
R3bc48 *func_00f3f260(s32, s32);
Q3bc48 *func_00f62c78(s32, s32);
void *func_00f64c38(s32, s32);
void sceVu0UnitMatrix(f32 (*)[4]);
void func_00f3bb68(s32);

E3bc48 *func_00f3bc48(s32 arg0) {
    s32 i;
    E3bc48 *e;
    G3bc48 **pg;
    R3bc48 *r;
    Q3bc48 *q;
    for (i = 0; i < 256; i++) {
        if (D_01067FE0[i].flags & 4) {
            D_01067FE0[i].flags = 0;
        }
        if (D_01067FE0[i].id == arg0 && (D_01067FE0[i].flags & 1)) {
            D_01067FE0[i].flags |= 2;
            func_00f3bbf8(&D_01067FE0[i]);
            return &D_01067FE0[i];
        }
    }
    pg = &D_00F864C0;
    for (i = 0; i < 256; i++) {
        if (D_01067FE0[i].flags == 0) {
            r = func_00f3f260(arg0, (*pg)->x540);
            q = func_00f62c78(r->h20, (*pg)->x540);
            D_01067FE0[i].flags = 2;
            sceVu0UnitMatrix(D_01067FE0[i].m);
            D_01067FE0[i].cnt = 0;
            D_01067FE0[i].id = arg0;
            D_01067FE0[i].conds = func_00f64c38(q->h4, D_00F8704C);
            D_01067FE0[i].mask = 0;
            D_01067FE0[i].v80[0] = 0.0f;
            D_01067FE0[i].v80[1] = 0.0f;
            D_01067FE0[i].v80[2] = 0.0f;
            D_01067FE0[i].v80[3] = 1.0f;
            D_01067FE0[i].v90[0] = 0.0f;
            D_01067FE0[i].v90[1] = 0.0f;
            D_01067FE0[i].v90[2] = 0.0f;
            D_01067FE0[i].v90[3] = 1.0f;
            func_00f3bb68(i);
            return &D_01067FE0[i];
        }
    }
    return NULL;
}
