/* Round 35 (wgb): no change (13 words, score 24). -dl/-dg: the s6/s7 swap is a global-alloc priority tie. pt (refs 12, life 118: 3*12/118 = 0.3051) loses to the j*4 offset giv (refs 9, life 88: 3*9/88 = 0.3068), so the giv takes s6 first, pt gets s7 and root shares s6 with the giv; the target needs pt first. Setting pt after PlatVu0UnitMatrix gives the right registers (life 115) but moves the h->parts load after the call (149 words). Live lengths are counted after combine: none of these moved them: loop-1/2 shapes (wi/wp pointers, p = parent forms, f32 *v for the stores), h vs hh in loop 3, j init placement, while forms, pt indexing (716 bytes), t outside the loop. */
/* near miss: 13 words, score 24 (round 30 wgb: part loop `pt++, j++`, ported from wm func_00f651d0; was 14/26). hh = h after the unit matrix (as in func_00f3e388) fixed the loop guards; left: root and pt get s6/s7 the wrong way round. */
typedef struct { f32 rot[4]; f32 pos[4]; u8 pad20[16]; s32 parent; u8 pad34[12]; } MdlBone;
typedef struct { s32 count; s32 off; u8 pad8[32]; } MdlPart;
typedef struct { s32 off; s32 bone; u8 pad8[32]; } MdlEnt;
typedef struct { u8 pad0[16]; OvlMtx m; OvlMtx m2; } MdlWork;
typedef struct { u8 pad0[0x90]; s32 nbones; s32 bones; s32 nparts; s32 parts; } MdlHdr;
extern u32 D_00F6C9C4;
void func_001bf048(OvlVec *, OvlVec *);
void *func_00f3f548(void *, s32, MdlWork *, s32, void *, s32);
MdlWork *func_00f3e0d8(void **out, s32 a1, MdlWork *w, s32 *arg3, MdlHdr *h, s32 *arg5, OvlVec *root) {
    OvlMtx unit;
    OvlMtx r;
    OvlMtx tmp;
    MdlHdr *hh;
    MdlBone *b = (MdlBone *)((u8 *)h + h->bones);
    MdlPart *pt = (MdlPart *)((u8 *)h + h->parts);
    s32 i, j, k;
    PlatVu0UnitMatrix(unit);
    hh = h;
    for (i = 0; i < hh->nbones; i++) {
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
    for (i = 0; i < hh->nbones; i++) {
        s32 p = b[i].parent;
        if (p >= 0) {
            PlatVu0MulMatrix(w[i].m2, w[p].m2, w[i].m2);
            PlatVu0MulMatrix(w[i].m, w[p].m, w[i].m);
        }
    }
    for (j = 0; j < hh->nparts; pt++, j++) {
        s32 t = 0;
        MdlEnt *e;
        if (arg3) {
            t = arg3[j];
        }
        e = (MdlEnt *)((u8 *)hh + pt->off);
        for (i = 0; i < pt->count; i++, e++) {
            if (D_00F6C9C4 & (1 << i)) {
                out[j] = func_00f3f548(out[j], a1, &w[e->bone], t, (u8 *)hh + e->off, arg5[j]);
            }
        }
    }
    return &w[hh->nbones];
}
