/* wm.x func_00f65480: matched by hand. */
#include "ovl.h"

typedef struct { f32 rot[4]; f32 pos[4]; f32 sc[4]; s32 parent; u8 pad34[12]; } MdlBone;
typedef struct { s32 count; s32 off; u8 pad8[32]; } MdlPart;
typedef struct { s32 off; s32 bone; u8 pad8[32]; } MdlEnt;
typedef struct { u8 pad0[16]; OvlMtx m; OvlMtx m2; } MdlWork;
typedef struct { u8 pad0[0x90]; s32 nbones; s32 bones; s32 nparts; s32 parts; } MdlHdr;
typedef struct { u8 chan; u8 pad[3]; void *curve; } AnmKey;
typedef struct { u16 bone; u16 nkeys; u8 pad4[4]; AnmKey *keys; } AnmTrack;
typedef struct { u8 pad0[8]; u32 count; AnmTrack *tracks; } Anm;
typedef struct { f32 rot[4]; f32 pos[4]; f32 sc[4]; } Pose;
extern u32 D_00FB1144;
f32 func_00f64d48(void *, f32);
void *func_00f66640(void *, s32, MdlWork *, s32, void *, s32);
MdlWork *func_00f65480(void **out, s32 a1, MdlWork *w, s32 *arg3, MdlHdr *h, Anm *an, s32 *arg5, f32 time) {
    Pose ps;
    OvlMtx unit;
    OvlMtx r;
    OvlMtx t;
    MdlHdr *hh;
    MdlPart *pt;
    MdlBone *b;
    s32 i, j, k;
    b = (MdlBone *)((u8 *)h + h->bones);
    pt = (MdlPart *)((u8 *)h + h->parts);
    PlatVu0UnitMatrix(unit);
    hh = h;
    for (i = 0; i < hh->nbones; i++) {
        PlatVu0RotMatrixX(r, unit, b[i].rot[0]);
        PlatVu0RotMatrixY(r, r, b[i].rot[1]);
        PlatVu0RotMatrixZ(r, r, b[i].rot[2]);
        PlatVu0TransMatrix(t, unit, b[i].pos);
        PlatVu0MulMatrix(w[i].m, t, r);
        PlatVu0CopyMatrix(w[i].m2, r);
    }
    if (an) {
        Pose *pp = &ps;
        ps.rot[3] = 1.0f;
        ps.pos[3] = 1.0f;
        ps.sc[3] = 1.0f;
        {
            AnmTrack *tr;
            for (i = 0, tr = an->tracks; i < an->count; i++, tr++) {
                s32 bone = tr->bone;
                AnmKey *ky;
                f32 *p;
                pp->rot[0] = b[bone].rot[0];
                pp->rot[1] = b[bone].rot[1];
                pp->rot[2] = b[bone].rot[2];
                pp->pos[0] = b[bone].pos[0];
                pp->pos[1] = b[bone].pos[1];
                pp->pos[2] = b[bone].pos[2];
                pp->sc[0] = b[bone].sc[0];
                pp->sc[1] = b[bone].sc[1];
                pp->sc[2] = b[bone].sc[2];
                for (j = 0, ky = tr->keys; j < tr->nkeys; j++, ky++) {
                    ((f32 *)pp)[ky->chan] = func_00f64d48(ky->curve, time);
                }
                for (k = 0; k < 3; k++) {
                    while (ps.rot[k] > 180.0f) ps.rot[k] -= 360.0f;
                    while (ps.rot[k] < -180.0f) ps.rot[k] += 360.0f;
                    ps.rot[k] = ps.rot[k] * 3.1415926f / 180.0f;
                }
                PlatVu0RotMatrixX(r, unit, ps.rot[0]);
                PlatVu0RotMatrixY(r, r, ps.rot[1]);
                PlatVu0RotMatrixZ(r, r, ps.rot[2]);
                PlatVu0TransMatrix(t, unit, ps.pos);
                PlatVu0MulMatrix(w[bone].m, t, r);
                PlatVu0CopyMatrix(w[bone].m2, r);
            }
        }
    }
    for (i = 0; i < hh->nbones; i++) {
        s32 p = b[i].parent;
        if (p >= 0) {
            PlatVu0MulMatrix(w[i].m2, w[p].m2, w[i].m2);
            PlatVu0MulMatrix(w[i].m, w[p].m, w[i].m);
        }
    }
    for (j = 0; j < hh->nparts; j++, pt++) {
        s32 tt = 0;
        MdlEnt *e;
        if (arg3) {
            tt = arg3[j];
        }
        e = (MdlEnt *)((u8 *)hh + pt->off);
        for (i = 0; i < pt->count; i++, e++) {
            if (D_00FB1144 & (1 << i)) {
                out[j] = func_00f66640(out[j], a1, &w[e->bone], tt, (u8 *)hh + e->off, arg5[j]);
            }
        }
    }
    return &w[hh->nbones];
}
