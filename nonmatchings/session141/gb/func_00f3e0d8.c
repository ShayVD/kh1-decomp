/* near miss: 108 words, score 24. Left: the stage-1 bound must load into v0 with a v1 copy (as in func_00f3e388), so the zero-trip exit isn't threaded past loop 2; entry spill order. */
typedef struct { f32 rot[4]; f32 pos[4]; u8 pad20[16]; s32 parent; u8 pad34[12]; } MdlBone;
typedef struct { s32 count; s32 off; u8 pad8[32]; } MdlPart;
typedef struct { s32 off; s32 bone; u8 pad8[32]; } MdlEnt;
typedef struct { u8 pad0[16]; OvlMtx m; OvlMtx m2; } MdlWork;
typedef struct { u8 pad0[0x90]; s32 nbones; s32 bones; s32 nparts; s32 parts; } MdlHdr;
extern u32 D_00F6C9C4;
void func_001bf048(OvlVec *, OvlVec *);
s32 func_00f3f548(s32, s32, MdlWork *, s32, void *, s32);
MdlWork *func_00f3e0d8(s32 *out, s32 a1, MdlWork *w, s32 *arg3, MdlHdr *h, s32 *arg5, OvlVec *root) {
    OvlMtx unit;
    OvlMtx r;
    OvlMtx tmp;
    MdlBone *b = (MdlBone *)((u8 *)h + h->bones);
    MdlPart *pt = (MdlPart *)((u8 *)h + h->parts);
    s32 i, j, k;
    PlatVu0UnitMatrix(unit);
    for (i = 0; i < h->nbones; i++) {
        PlatVu0RotMatrixX(r, unit, b[i].rot[0]);
        PlatVu0RotMatrixY(r, r, b[i].rot[1]);
        PlatVu0RotMatrixZ(w[i].m, r, b[i].rot[2]);
        w[i].m[3][0] = b[i].pos[0];
        w[i].m[3][1] = b[i].pos[1];
        w[i].m[3][2] = b[i].pos[2];
        if (root) {
            PlatVu0MulMatrix(w[i].m, root, w[i].m);
        }
        func_001bf048(w[i].m2, w[i].m);
    }
    for (i = 0; i < h->nbones; i++) {
        s32 p = b[i].parent;
        if (p >= 0) {
            PlatVu0MulMatrix(w[i].m2, w[p].m2, w[i].m2);
            PlatVu0MulMatrix(w[i].m, w[p].m, w[i].m);
        }
    }
    for (j = 0; j < h->nparts; j++, pt++) {
        s32 t = 0;
        MdlEnt *e;
        if (arg3) {
            t = arg3[j];
        }
        e = (MdlEnt *)((u8 *)h + pt->off);
        for (i = 0; i < pt->count; i++, e++) {
            if (D_00F6C9C4 & (1 << i)) {
                out[j] = func_00f3f548(out[j], a1, &w[e->bone], t, (u8 *)h + e->off, arg5[j]);
            }
        }
    }
    return &w[h->nbones];
}
