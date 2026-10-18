/* 001636d0 (two-bone IK/skeleton update) near miss (hand/nostrict): size correct (4248), 817 words, mostly register/spill choice: orig spills j(364) trow(368) pp(372) bn(376) and keeps par in s3; ours keeps j in a reg, drops pp (always &pos) and spills par, shifting s-regs. Structure matches: outer switch((f>>21)&3) {1, 2/3 (two bones, i++ inside), default}, inner switch(f&3) in order case 2, 1, 0, default; sqc2 $vf0 store of trow is real VU0 asm. FLAG: size needs the empty __asm__("") at the end of inner case 0 to stop gcc cross-jumping its tail into case 1 (orig has the two tails separate) - a hack, not a real fix. */
#include "common.h"

typedef f32 IkMtx[4][4];
typedef struct {
    f32 a[4];
    f32 b[4];
    union {
        f32 t[4];
        struct { f32 x, y, z; u32 par; } p;
    } u;
} IkBone;
typedef struct {
    f32 len[4];
    u8 pad10[0x10 - 0x10];
} IkPad;
typedef struct {
    f32 len[4];   /* +0x00 */
    s32 x10;      /* +0x10 */
    u8 pad14[0xC];
    s32 x20;      /* +0x20 */
    u8 pad24[0x90 - 0x24];
    s32 bone[4];  /* +0x90 */
} IkHdr;
typedef struct {
    s16 n;
    IkBone *bones;
    IkHdr *h;
} IkMdl;
typedef struct { f32 a[4]; f32 s[4]; f32 r[4]; f32 t[4]; } IkXf;
typedef struct {
    IkMdl **mdl;
    u8 pad4[8];
    s32 xC;
    u8 pad10[0x150 - 0x10];
    IkXf *x150;
    IkMtx *x154;
    IkMtx *x158;
} IkObj;
typedef struct {
    u8 pad[0x14];
    u32 *fl;
} IkAnim;
typedef struct {
    f32 p0[4];
    f32 p1[4];
    f32 hit[4];
    s16 id;
} IkRay;

extern IkMtx D_00351E10[];
extern IkMtx D_00573F10[];
extern f32 D_00574F10[];
extern f32 D_00574F20[];

void func_00118590(IkRay *, s32);
void func_001625c8(IkMtx, IkMtx);
void func_001627d0(f32 *, f32 *, f32 *);
void func_00162848(f32 *, IkMtx, f32 *);
void func_001628a0(IkMtx, IkMtx, f32 *);
void func_00162c5c(IkMtx, IkMtx, IkMtx);
void func_00162cd0(f32 *, f32 *, IkMtx);
void func_00162d00(f32 *, s32, IkMtx, IkMtx, f32 *, f32, f32, f32, f32);
void func_00163150(IkObj *, s32);
void func_00267370(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267768(IkMtx, IkMtx, f32);
void func_00267e90(f32 *, f32 *, f32);
void sceVu0UnitMatrix(IkMtx);

void func_001636d0(IkObj *o, IkAnim *an)
{
    f32 v0[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    f32 up[4] __attribute__((aligned(16)));
    f32 tgt[4] __attribute__((aligned(16)));
    IkMtx pm __attribute__((aligned(16)));
    IkMtx rm __attribute__((aligned(16)));
    IkMtx sm __attribute__((aligned(16)));
    IkRay ray __attribute__((aligned(16)));
    f32 cr[4] __attribute__((aligned(16)));
    s32 i;
    s32 flg;
    s32 j;
    f32 *trow;
    f32 *pp;
    IkBone *bn;
    IkHdr *h;
    IkMtx *par, *tm, *lm, *lm1;
    u32 f;
    s32 s2;
    s32 k, s0, s1, hit;
    f32 hl;
    f32 *xs;
    IkMtx *wm;
    s32 n;

    h = (*o->mdl)->h;
    flg = (o->xC >> 4) & 1;
    if (h->x20 != -1) {
        an->fl[h->x20 - 1] &= ~0x02000000;
    } else if (h->x10 != 1) {
        an->fl[h->x10 - 1] &= ~0x02000000;
    }
    bn = (*o->mdl)->bones;
    for (i = 0; i < (*o->mdl)->n; i++, bn++) {
        f = an->fl[i];
        if ((f >> 26) & 1) continue;
        j = i;
        k = bn->u.p.par & 0x3FF;
        if (k == 0x3FF) {
            par = D_00573F10;
            o->x150[i].s[0] = o->x150[i].a[0];
            o->x150[i].s[1] = o->x150[i].a[1];
            o->x150[i].s[2] = o->x150[i].a[2];
        } else {
            par = &D_00351E10[k];
            func_001627d0(o->x150[i].s, o->x150[k].s, o->x150[i].a);
        }
        s2 = f >> 21;
        hit = 0;
        tm = &D_00351E10[i];
        hl = 0.0f;
        lm = &o->x158[i];
        switch (s2 & 3) {
        case 1:
            (*lm)[3][0] = o->x150[j].t[0];
            (*lm)[3][1] = o->x150[j].t[1];
            (*lm)[3][2] = o->x150[j].t[2];
            func_001625c8(o->x154[bn->u.p.par & 0x3FF], pm);
            s0 = ((an->fl[i + 1] >> 19) & 0x200) | ((an->fl[i + 1] >> 11) & 0x1FF);
            pos[3] = 1.0f;
            n = s0 - 1;
            pos[0] = D_00573F10[n][3][0];
            pos[1] = D_00573F10[n][3][1];
            pos[2] = D_00573F10[n][3][2];
            func_00162848(v0, pm, pos);
            if ((f & 3) == 3) {
                s1 = ((f >> 18) & 0x200) | ((f >> 2) & 0x1FF);
                func_00162848(tgt, pm, D_00573F10[s1 - 1][3]);
                func_00162d00(v0, 0, *lm, 0, tgt, o->x150[j].a[0] * bn[1].u.t[0], hl, o->x150[j].r[0], hl);
            } else {
                func_00162d00(v0, 0, *lm, 0, 0, o->x150[j].a[0] * bn[1].u.t[0], hl, o->x150[j].r[0], hl);
            }
            trow = (*tm)[3];
            xs = o->x150[i].a;
            func_00267e90(sm[0], (*lm)[0], xs[0]);
            func_00267e90(sm[1], (*lm)[1], xs[1]);
            func_00267e90(sm[2], (*lm)[2], xs[2]);
            func_002675a8(sm[3], (*lm)[3]);
            func_00162c5c(o->x154[i], o->x154[bn->u.p.par & 0x3FF], sm);
            func_00162848(o->x154[i][3], o->x154[bn->u.p.par & 0x3FF], o->x150[i].t);
            o->x154[i][3][3] = 1.0f;
            func_001628a0(*tm, o->x154[i], o->x150[i].s);
            func_00162848(o->x154[i + 1][3], o->x154[i], bn[1].u.t);
            o->x154[i + 1][3][3] = 1.0f;
            break;
        case 2:
        case 3:
            if (o->xC & 3) {
                for (k = 0; k < 4; k++) {
                    if (i == (*o->mdl)->h->bone[k] - 1) {
                        hit = 1;
                        hl = (*o->mdl)->h->len[k];
                        break;
                    }
                }
            }
            (*lm)[3][0] = o->x150[i].t[0];
            (*lm)[3][1] = o->x150[i].t[1];
            (*lm)[3][2] = o->x150[i].t[2];
            func_001625c8(o->x154[bn->u.p.par & 0x3FF], pm);
            lm1 = &o->x158[i + 1];
            func_001627d0(o->x150[i + 1].s, o->x150[i].s, o->x150[i + 1].a);
            s0 = ((an->fl[i + 2] >> 19) & 0x200) | ((an->fl[i + 2] >> 11) & 0x1FF);
            pos[3] = 1.0f;
            n = s0 - 1;
            pos[0] = D_00573F10[n][3][0];
            pos[1] = D_00573F10[n][3][1];
            pos[2] = D_00573F10[n][3][2];
            if (hit) {
                ray.p0[0] = pos[0] * D_00574F20[0] + D_00574F10[0];
                ray.p0[2] = pos[2] * D_00574F20[2] + D_00574F10[2];
                ray.p0[3] = 1.0f;
                ray.p1[0] = 0.0f;
                ray.p0[1] = (pos[1] - bn[2].u.t[0]) * D_00574F20[1] + D_00574F10[1];
                ray.p1[3] = 1.0f;
                ray.p1[2] = 0.0f;
                ray.p1[1] = (bn[2].u.t[0] + bn[2].u.t[0] + hl) * D_00574F20[1];
                func_00118590(&ray, flg);
                if (ray.id != -1 && ((o->xC & 2) || ray.hit[1] < (pos[1] + hl) * D_00574F20[1] + D_00574F10[1])) {
                    ray.hit[1] = (ray.hit[1] - D_00574F10[1]) / D_00574F20[1] - hl;
                    ray.hit[0] = (ray.hit[0] - D_00574F10[0]) / D_00574F20[0];
                    ray.hit[2] = (ray.hit[2] - D_00574F10[2]) / D_00574F20[2];
                    func_00162848(v0, pm, ray.hit);
                    o->xC |= 0x200000;
                } else {
                    func_00162848(v0, pm, pos);
                }
            } else {
                func_00162848(v0, pm, pos);
            }
            if ((f & 3) == 3) {
                s1 = ((f >> 18) & 0x200) | ((f >> 2) & 0x1FF);
                func_00162848(tgt, pm, D_00573F10[s1 - 1][3]);
                func_00162d00(v0, (s2 & 3) - 2, *lm, *lm1, tgt, o->x150[i].a[0] * bn[1].u.t[0], o->x150[i].a[0] * o->x150[i + 1].a[0] * bn[2].u.t[0], o->x150[i].r[0], o->x150[i + 1].r[0]);
            } else {
                func_00162d00(v0, (s2 & 3) - 2, *lm, *lm1, 0, o->x150[i].a[0] * bn[1].u.t[0], o->x150[i].a[0] * o->x150[i + 1].a[0] * bn[2].u.t[0], o->x150[i].r[0], o->x150[i + 1].r[0]);
            }
            trow = (*tm)[3];
            xs = o->x150[i].a;
            func_00267e90(sm[0], (*lm)[0], xs[0]);
            func_00267e90(sm[1], (*lm)[1], xs[1]);
            func_00267e90(sm[2], (*lm)[2], xs[2]);
            func_002675a8(sm[3], (*lm)[3]);
            func_00162c5c(o->x154[i], o->x154[bn->u.p.par & 0x3FF], sm);
            func_00162848(o->x154[i][3], o->x154[bn->u.p.par & 0x3FF], o->x150[i].t);
            o->x154[i][3][3] = 1.0f;
            func_001628a0(*tm, o->x154[i], o->x150[i].s);
            sceVu0UnitMatrix(sm);
            sm[0][0] = 1.0f / o->x150[i].a[0];
            sm[1][1] = 1.0f / o->x150[i].a[1];
            sm[2][2] = 1.0f / o->x150[i].a[2];
            func_00162c5c(sm, sm, *lm1);
            func_001627d0(o->x150[i + 1].s, o->x150[i].a, o->x150[i + 1].a);
            xs = o->x150[i + 1].s;
            func_00267e90(sm[0], sm[0], xs[0]);
            func_00267e90(sm[1], sm[1], xs[1]);
            func_00267e90(sm[2], sm[2], xs[2]);
            func_002675a8(sm[3], sm[3]);
            func_00162c5c(o->x154[i + 1], o->x154[i], sm);
            func_00162848(o->x154[i + 1][3], o->x154[i], bn[1].u.t);
            o->x154[i + 1][3][3] = 1.0f;
            func_001628a0(D_00351E10[i + 1], o->x154[i + 1], o->x150[i + 1].s);
            func_00162848(o->x154[i + 2][3], o->x154[i + 1], bn[2].u.t);
            o->x154[i + 2][3][3] = 1.0f;
            func_001625c8(o->x154[i], pm);
            func_00162c5c(*lm1, pm, o->x154[i + 1]);
            o->x150[i + 1].a[3] = o->x150[i + 1].r[0];
            i++;
            bn++;
            break;
        default:
            s1 = ((f >> 18) & 0x200) | ((f >> 2) & 0x1FF);
            s0 = ((f >> 19) & 0x200) | ((f >> 11) & 0x1FF);
            s2 = f >> 23;
            if ((s2 & 1) || s0 || (f & 0x01000003)) {
                k = bn->u.p.par & 0x3FF;
                if (k == 0x3FF) func_001625c8(D_00573F10[0], pm);
                else func_001625c8(o->x154[k], pm);
            }
            if (s2 & 1) {
                pp = pos;
                pos[0] = o->x154[i][3][0];
                pos[1] = o->x154[i][3][1];
                pos[3] = 1.0f;
                pos[2] = o->x154[i][3][2];
                func_00162848((*lm)[3], pm, pos);
            } else if (s0) {
                pp = pos;
                n = s0 - 1;
                pos[0] = D_00573F10[n][3][0];
                pos[1] = D_00573F10[n][3][1];
                pos[2] = D_00573F10[n][3][2];
                pos[3] = 1.0f;
                func_00162848((*lm)[3], pm, pp);
            } else {
                k = bn->u.p.par & 0x3FF;
                if (k == 0x3FF) {
                    pp = pos;
                    func_00162848(pos, D_00573F10[0], o->x150[i].t);
                } else {
                    pp = pos;
                    func_00162848(pos, o->x154[k], o->x150[i].t);
                }
                pos[3] = 1.0f;
            }
            switch (f & 3) {
            case 2:
                n = s1 - 1;
                for (k = 0; k < 3; k++) {
                    for (s0 = 0; s0 < 3; s0++) {
                        (*tm)[k][s0] = D_00573F10[n][k][s0];
                    }
                }
                func_002673b8((*tm)[0], (*tm)[0]);
                trow = (*tm)[3];
                func_002673b8((*tm)[1], (*tm)[1]);
                func_002673b8((*tm)[2], (*tm)[2]);
                wm = &o->x154[i];
                xs = o->x150[i].s;
                func_00267e90((*wm)[0], (*tm)[0], xs[0]);
                func_00267e90((*wm)[1], (*tm)[1], xs[1]);
                func_00267e90((*wm)[2], (*tm)[2], xs[2]);
                func_002675a8((*wm)[3], trow);
                break;
            case 1:
                func_00162848(v0, pm, D_00573F10[s1 - 1][3]);
                if ((s2 & 1) || s0) {
                    func_00267530(d, v0, (*lm)[3]);
                } else {
                    func_00267530(d, v0, o->x150[i].t);
                    func_002675a8((*lm)[3], o->x150[i].t);
                }
                up[0] = 0.0f;
                up[1] = 1.0f;
                up[2] = 0.0f;
                (*lm)[2][3] = 0.0f;
                (*lm)[1][3] = 0.0f;
                trow = (*tm)[3];
                (*lm)[0][3] = 0.0f;
                func_002673b8((*lm)[0], d);
                func_00267370(cr, d, up);
                func_00267370((*lm)[1], cr, d);
                func_002673b8((*lm)[1], (*lm)[1]);
                func_00267370((*lm)[2], d, (*lm)[1]);
                func_002673b8((*lm)[2], (*lm)[2]);
                sceVu0UnitMatrix(rm);
                func_00267768(rm, rm, o->x150[i].r[0]);
                func_00162c5c(*lm, *lm, rm);
                func_00162c5c(*tm, *par, *lm);
                wm = &o->x154[i];
                xs = o->x150[i].s;
                func_00267e90((*wm)[0], (*tm)[0], xs[0]);
                func_00267e90((*wm)[1], (*tm)[1], xs[1]);
                func_00267e90((*wm)[2], (*tm)[2], xs[2]);
                func_002675a8((*wm)[3], trow);
                break;
            case 0:
                if ((f >> 24) & 1) {
                    func_00162cd0(o->x150[i].r, o->x150[i].t, *lm);
                    func_00162c5c(*tm, D_00573F10[0], *lm);
                } else {
                    if (!((f >> 25) & 1)) func_00162cd0(o->x150[i].r, o->x150[i].t, *lm);
                    func_00162c5c(*tm, *par, *lm);
                }
                xs = o->x150[i].s;
                trow = (*tm)[3];
                wm = &o->x154[i];
                func_00267e90((*wm)[0], (*tm)[0], xs[0]);
                func_00267e90((*wm)[1], (*tm)[1], xs[1]);
                func_00267e90((*wm)[2], (*tm)[2], xs[2]);
                func_002675a8((*wm)[3], trow);
                __asm__("");
                break;
            default:
                trow = (*tm)[3];
                break;
            }
            func_002675a8(o->x154[i][3], pp);
            if (f & 0x01000003) {
                func_00162c5c(*lm, pm, o->x154[j]);
                func_001628a0(*lm, *lm, d);
            }
            break;
        }
        __asm__ volatile("sqc2 $vf0, 0(%0)" : : "r"(trow) : "memory");
        if (o->xC & 0xC) func_00163150(o, i);
    }
}
