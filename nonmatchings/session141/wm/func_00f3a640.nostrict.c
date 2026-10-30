/* Round 46 wwm2: score 78 -> 76, func_001c0310 declared s32. Earlier header below. */
/* Round 45 wwm2: score 86 -> 78, hill3o statement order under this build mode. Earlier header below. */
/* Round 44 wwm2: score 94 -> 86 under the nostrict build mode (r44/modescan.py). Earlier header below. */
/* 127 words (528 vs 544). Structure and calls right (entry of 272 bytes, S/T/U sub-structs at 224/240/256). Left: the target adds each sub-struct offset to id*272 before adding the base (s4 = (id*272+224)+D, s0 = (id*272+240)+D, U computed lazily), keeps id and id*16 in s7/s8, and recomputes &D[id] after the loop. Tried direct D[id] fields (136), sub-struct pointers (127), a single E pointer (96 words but 396 bytes) and a base-pointer local (this one, best score). */
typedef struct { s32 type; u8 pad[44]; } Q3a640;
typedef struct { u8 b0; u8 pad[3]; u16 h4; } D3a640;
typedef struct { s32 on; s32 x4; f32 f8; D3a640 *desc; } S3a640;
typedef struct { s32 t0; s32 t1; s32 t2; s32 t3; } T3a640;
typedef struct { s32 u0; s32 u1; s32 u2; Q3a640 *list; } U3a640;
typedef struct {
    u8 pad0[32];
    f32 v32[4];
    f32 v48[4];
    f32 v64[4];
    f32 v80[4];
    f32 m96[4][4];
    f32 m160[4][4];
    S3a640 s;
    T3a640 t;
    U3a640 u;
} E3a640;
extern E3a640 D_00FCE390[];
extern s32 D_00F87020;
extern s32 D_00F8704C;
s32 func_00f64c38(s32, s32);
s32 func_00f650f0(s32, s32);
void func_00f37028(E3a640 *, f32 *);
s32 func_00f3a5a0(E3a640 *);
void sceVu0UnitMatrix(f32 (*)[4]);
void func_001bf098(f32 (*)[4], E3a640 *);
void sceVu0CopyVector(f32 *, f32 *);
void func_00f39b10(E3a640 *, Q3a640 *, s32);
void func_00f39de8(E3a640 *);
s32 func_00f3a1d8(f32 *);
s32 func_001c0310(s32, void *, void *);
void func_00f3a268(void);

s32 func_00f3a640(s32 id, f32 *pos, D3a640 *desc, s32 val) {

    E3a640 *bs = D_00FCE390; S3a640 *sp = &bs[id].s;
    T3a640 *tp = &bs[id].t;
    Q3a640 *q;
    E3a640 *e = &D_00FCE390[id];
    sp->x4 = val;
    sp->desc = desc;
    tp->t0 = func_00f64c38(desc->b0, D_00F87020);
    sp->f8 = pos[0];
    tp->t1 = func_00f650f0(1, tp->t0);
    D_00FCE390[id].u.list = (Q3a640 *)func_00f64c38(desc->h4, D_00F8704C);
    func_00f37028(e, pos);
    sp->on = 0;
    if (!func_00f3a5a0(e)) {
        sp->on = 0;
        return 0;
    }
    sceVu0UnitMatrix(D_00FCE390[id].m96);
    func_001bf098(D_00FCE390[id].m96, e);
    sceVu0CopyVector(D_00FCE390[id].v80, D_00FCE390[id].v48);
    sceVu0CopyVector(D_00FCE390[id].v64, D_00FCE390[id].v32);
    D_00FCE390[id].v64[3] = 1.0f;
    D_00FCE390[id].v80[3] = 1.0f;
    sceVu0UnitMatrix(D_00FCE390[id].m160);
    for (q = D_00FCE390[id].u.list; q->type != 1; q++) {
        if (q->type == 8) {
            func_00f39b10(&D_00FCE390[id], q, 0);
        }
    }
    func_00f39de8(&D_00FCE390[id]);
    if (!func_00f3a1d8(D_00FCE390[id].v48)) {
        return 0;
        D_00FCE390[id].s.on = 0;
    }
    D_00FCE390[id].s.on = 1;
    func_001c0310(11, func_00f3a268, &D_00FCE390[id]);
    return 1;
}
