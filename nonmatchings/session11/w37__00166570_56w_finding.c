/* 00166570: 56 LCS (finding; best stays s7 w7 21w), hand/nostrict, no context. m40/m80 used directly in the bone-chain while loop (no pa/pb). Dumps show this reproduces the original preheader RTL after cse2 exactly: gcse PRE turns the in-loop sp+64/sp+128 into reaching-reg copies, CPROP2 rewrites them to the pre-loop A40/A80 pseudos, loop.c hoists the copies after the exit tests, cse2 leaves `1087 = 1067; 1093 = 1072; li 1023` (orig: move s6,s2; move s2,s0; li s8,1023). What is off: PRE also replaces the POST-loop sp+64/sp+128 with the reaching regs (CPROP2 -> A40/A80), so A40/A80 live across the loop; global-alloc then leaves A40 and the 1023 pseudo without hard regs (reload rematerialises addiu sp,64 and li 1023 in the loop), A80 takes s8. The original recomputes the post-loop addresses, i.e. its A40/A80 die at the preheader copies. Gcse does not treat calls as killing the soft frame pointer ($1), so no dead set of a user variable can kill availability of (plus $1 64); the pa/pb version with a dead set of a copy source in the loop (a40 = 0 after `pa = a40`) does keep the pa/pb copies (move s7,v1) but loop.c then sees the extra insn and the exit test is cross-jumped (52-85w). Second step tried (s11w37): CopyMatrix args through function-level a40 = m40 / a80 = m80 plus a flagged dead one-path set `if (par == 0x3FF) { a40 = 0; a80 = 0; }` before the while: gcse CPROP2 then rewrites the in-loop PRE reaching regs to a40/a80 but keeps the post-loop ones (exactly the split the original implies), still 56: cse2 canonicalises a40's CopyMatrix/preheader uses to the longer-lived reaching reg (REGNO_LAST_UID rule), a40 dies, and the reaching reg (CopyMatrix..post-loop, 5 calls) is spilled and rematerialised everywhere; the 1023 constant is no longer hoisted. A dead set in the post-loop block itself is unsafe: CPROP ignores a source set earlier in the use block. */
/* func_00166570: hand/nostrict. ~27 words off by sequence diff (s6: ~59 seq-diff lines), 4168 vs 4176 bytes. Fixed from s6: the bone-chain while loop uses pointer locals pa = m40, pb = m80 declared after the two sceVu0CopyMatrix calls: the gcse PRE reuse of sp+128 and the 1023 reload are gone and the loop body now matches. Still off: the original copies the pre-loop m40/m80 address regs (s2/s0) into the loop regs (move s6,s2; move s2,s0: 2 missing words), so m0 lands in s8 instead of s6 on the other path. */
#include "common.h"
#include "platform/math.h"

typedef f32 G2Mtx[4][4];
typedef struct { u32 par:10; u32 pad:20; u32 flag:1; u32 top:1; } G2BBits;
typedef struct { f32 s[4]; f32 r[4]; f32 t[3]; G2BBits b; } G2Bone;
typedef struct { f32 f[4]; u8 pad[0x90 - 0x10]; s32 x90[4]; } G2Sk8;
typedef struct { s16 n; s16 pad2; G2Bone *bones; G2Sk8 *p8; s32 xC; } G2Hdr;
typedef struct { s16 h0; s16 h2; s32 w4; u8 pad8[8]; f32 v10[4]; f32 v20[4]; } G2Lnk;
typedef struct {
    G2Hdr **p0;          /* 0x0 */
    void *p4;            /* 0x4 */
    f32 f8;              /* 0x8 */
    s32 wC;              /* 0xC */
    u8 pad10[0x90 - 0x10];
    f32 v90[4];          /* 0x90 */
    f32 vA0[4];          /* 0xA0 */
    f32 vB0[4];          /* 0xB0 */
    f32 vC0[4];          /* 0xC0 */
    G2Mtx mD0;           /* 0xD0 */
    G2Mtx m110;          /* 0x110 */
    G2Mtx *p150;         /* 0x150 */
    G2Mtx *p154;         /* 0x154 */
    G2Mtx *p158;         /* 0x158 */
    G2Mtx *p15C;         /* 0x15C */
    G2Mtx *p160;         /* 0x160 */
    f32 (*p164)[4];      /* 0x164 */
    f32 (*p168)[4];      /* 0x168 */
    G2Lnk *p16C;         /* 0x16C */
} G2Mdl;
typedef struct { f32 p[4]; f32 d[4]; f32 out[4]; s16 hit; } G2Ray;

extern G2Mtx D_00573F10[];
extern f32 D_00574F10[4];
extern f32 D_00574F20[4];

void func_00118590(G2Ray *, s32);
void func_001625c8(G2Mtx, G2Mtx);
void func_001627d0(f32 *, f32 *, f32 *);
void func_00162848(f32 *, G2Mtx, f32 *);
void func_001628a0(G2Mtx, G2Mtx, f32 *);
f32 func_00162c20(f32 *);
void func_00162c5c(G2Mtx, G2Mtx, G2Mtx);
void func_00162d00(f32 *, s32, G2Mtx, G2Mtx, f32 *, f32, f32, f32, f32);
void func_00267370(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
void func_002674b0(f32 *, f32 *, f32);
void func_002674f0(f32 *, f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267e60(f32 *, f32 *, f32 *, f32);
void func_00267e90(f32 *, f32 *, f32);
void sceVu0CopyMatrix(G2Mtx, G2Mtx);
void sceVu0UnitMatrix(G2Mtx);

static inline f32 inl_wrap(f32 v) {
    for (;;) {
        if (v > 3.14159251f) { v -= 6.28318501f; continue; }
        if (v < -3.14159251f) { v += 6.28318501f; continue; }
        break;
    }
    return v;
}

static inline void inl_scl(G2Mtx d, G2Mtx s, f32 *v) {
    func_00267e90(d[0], s[0], v[0]);
    func_00267e90(d[1], s[1], v[1]);
    func_00267e90(d[2], s[2], v[2]);
    func_002675a8(d[3], s[3]);
}

#define INL2(a, b, o, p) do { func_00162c5c(a, (o)->p15C[p], a); func_00162c5c(b, (o)->p160[p], b); } while (0)
void func_00166570(G2Mtx pos, G2Mdl *o, f32 f) {
    G2Mtx m0;
    G2Mtx m40;
    G2Mtx m80;
    f32 v[4];
    f32 w[4];
    f32 e[4];
    f32 ff[4];
    G2Mtx m100;
    G2Ray q;
    s32 i;
    G2Bone *bones;
    G2Lnk *lnk;
    s32 fl4;
    s32 par;
    s32 j, found;
    f32 h;
    G2Sk8 *p8;
    s32 fl;

    fl4 = (o->wC >> 4) & 1;
    D_00574F20[0] = PlatSqrtf(func_00267390(pos[0], pos[0]));
    D_00574F20[1] = PlatSqrtf(func_00267390(pos[1], pos[1]));
    D_00574F20[2] = PlatSqrtf(func_00267390(pos[2], pos[2]));
    sceVu0CopyMatrix(D_00573F10[0], pos);
    D_00573F10[0][1][0] = -D_00573F10[0][1][0];
    D_00573F10[0][1][1] = -D_00573F10[0][1][1];
    D_00573F10[0][1][2] = -D_00573F10[0][1][2];
    D_00573F10[0][2][0] = -D_00573F10[0][2][0];
    D_00573F10[0][2][1] = -D_00573F10[0][2][1];
    D_00573F10[0][2][2] = -D_00573F10[0][2][2];
    func_002674b0(D_00573F10[0][0], D_00573F10[0][0], D_00574F20[0]);
    func_002674b0(D_00573F10[0][1], D_00573F10[0][1], D_00574F20[1]);
    func_002674b0(D_00573F10[0][2], D_00573F10[0][2], D_00574F20[2]);
    func_00267e60(o->vA0, o->vC0, o->vB0, f);
    o->v90[0] = o->vA0[0] * D_00574F20[0] + D_00573F10[0][3][0];
    o->v90[1] = o->vA0[1] * D_00574F20[1] + D_00573F10[0][3][1];
    o->v90[2] = o->vA0[2] * D_00574F20[2] + D_00573F10[0][3][2];
    D_00574F10[0] = D_00573F10[0][3][0];
    D_00574F10[1] = D_00573F10[0][3][1];
    D_00574F10[2] = D_00573F10[0][3][2];
    D_00573F10[0][3][0] = 0.0f;
    D_00573F10[0][3][1] = 0.0f;
    D_00573F10[0][3][2] = 0.0f;
    for (i = 0; o->p16C[i].h0 >= 0; i++) {
        o->p16C[i].w4 = (*o->p0)->bones[(*o->p0)->bones[o->p16C[i].h0].b.par].b.flag;
        (*o->p0)->bones[(*o->p0)->bones[o->p16C[i].h0].b.par].b.flag = 1;
    }
    lnk = o->p16C;
    bones = (*o->p0)->bones;
    for (i = 0; i < (*o->p0)->n; i++) {
        func_002674f0(o->p150[i][0], o->p168[i], o->p164[i], f);
        if (bones[i].b.par == 0x3FF) {
            o->p150[i][1][0] = o->p150[i][0][0];
            o->p150[i][1][1] = o->p150[i][0][1];
            o->p150[i][1][2] = o->p150[i][0][2];
        } else {
            func_001627d0(o->p150[i][1], o->p150[bones[i].b.par][1], o->p150[i][0]);
        }
        if (lnk->h0 == i) {
            func_00267e60(v, lnk->v20, lnk->v10, f);
            v[3] = 1.0f;
            func_00162848(v, D_00573F10[0], v);
            o->p158[i][3][0] = o->p150[i][3][0];
            o->p158[i][3][1] = o->p150[i][3][1];
            o->p158[i][3][2] = o->p150[i][3][2];
            func_00267e60(w, o->p160[i][1], o->p15C[i][1], f);
            func_00267518(w, w, o->p150[i][3]);
            w[3] = 0.0f;
            switch (lnk->h2) {
            case 1:
                lnk++;
                func_001625c8(o->p154[bones[i].b.par], m100);
                func_00162848(v, m100, v);
                { f32 ln = o->p150[i][0][0] * bones[i + 1].t[0]; func_00162d00(v, 0, o->p158[i], 0, w, ln, 0.0f, 0.0f, 0.0f); }
                inl_scl(m0, o->p158[i], o->p150[i][0]);
                func_00162c5c(o->p154[i], o->p154[bones[i].b.par], m0);
                func_00162848(o->p154[i][3], o->p154[bones[i].b.par], o->p150[i][3]);
                o->p154[i][3][3] = 1.0f;
                func_001628a0(o->p158[i], o->p154[i], o->p150[i][1]);
                continue;
            case 2:
            case 3:
                func_002675a8(e, o->p164[i + 1]);
                func_002675a8(ff, o->p168[i + 1]);
                ff[3] = inl_wrap(ff[3] - e[3]);
                e[3] = 0.0f;
                func_002674f0(o->p150[i + 1][0], ff, e, f);
                o->p150[i + 1][0][3] = inl_wrap(o->p150[i + 1][0][3] + o->p164[i + 1][3]);
                h = 0.0f;
                func_001625c8(o->p154[bones[i].b.par], m100);
                found = 0;
                if (o->wC & 3) {
                    for (j = 0; j < 4; j++) {
                        if (i == (*o->p0)->p8->x90[j] - 1) {
                            found = 1;
                            if (!(o->wC & 0x20)) h = (*o->p0)->p8->f[j];
                        }
                    }
                }
                if (found) {
                    q.p[0] = v[0] * D_00574F20[0] + D_00574F10[0];
                    q.p[1] = (v[1] - bones[i + 2].t[0]) * D_00574F20[1] + D_00574F10[1];
                    q.p[2] = v[2] * D_00574F20[2] + D_00574F10[2];
                    q.p[3] = 1.0f;
                    q.d[0] = 0.0f;
                    q.d[1] = (bones[i + 2].t[0] + bones[i + 2].t[0] + h) * D_00574F20[1];
                    q.d[2] = 0.0f;
                    q.d[3] = 1.0f;
                    func_00118590(&q, fl4);
                    if (q.hit != -1) {
                        fl = o->wC;
                        if ((fl & 2) || q.out[1] < (v[1] + h) * D_00574F20[1] + D_00574F10[1]) {
                            v[0] = (q.out[0] - D_00574F10[0]) / D_00574F20[0];
                            v[1] = (q.out[1] - D_00574F10[1]) / D_00574F20[1] - h;
                            v[2] = (q.out[2] - D_00574F10[2]) / D_00574F20[2];
                            o->wC = fl | 0x200000;
                        }
                    }
                }
                func_00162848(v, m100, v);
                {
                    f32 ln = o->p150[i][0][0] * bones[i + 1].t[0];
                    f32 *s1 = o->p150[i + 1][0];
                    func_00162d00(v, lnk->h2 - 2, o->p158[i], o->p158[i + 1], w,
                                  ln, o->p150[i][0][0] * s1[0] * bones[i + 2].t[0], 0.0f, s1[3]);
                }
                lnk++;
                inl_scl(m0, o->p158[i], o->p150[i][0]);
                func_00162c5c(o->p154[i], o->p154[bones[i].b.par], m0);
                func_00162848(o->p154[i][3], o->p154[bones[i].b.par], o->p150[i][3]);
                o->p154[i][3][3] = 1.0f;
                func_001628a0(o->p158[i], o->p154[i], o->p150[i][1]);
                sceVu0UnitMatrix(m0);
                m0[0][0] = 1.0f / o->p150[i][0][0];
                m0[1][1] = 1.0f / o->p150[i][0][1];
                m0[2][2] = 1.0f / o->p150[i][0][2];
                func_00162c5c(m0, m0, o->p158[i + 1]);
                func_001627d0(o->p150[i + 1][1], o->p150[i][0], o->p150[i + 1][0]);
                inl_scl(m0, m0, o->p150[i + 1][1]);
                func_00162c5c(o->p154[i + 1], o->p154[i], m0);
                func_00162848(o->p154[i + 1][3], o->p154[i], bones[i + 1].t);
                o->p154[i + 1][3][3] = 1.0f;
                func_001628a0(o->p158[i + 1], o->p154[i + 1], o->p150[i + 1][1]);
                i++;
                continue;
            }
        }
        par = bones[i].b.par;
        if (bones[i].b.flag) {
            sceVu0CopyMatrix(m40, o->p15C[i]);
            sceVu0CopyMatrix(m80, o->p160[i]);
            
            while (par != 0x3FF && !bones[par].b.flag) {
                func_00162c5c(m40, o->p15C[par], m40);
                func_00162c5c(m80, o->p160[par], m80);
                par = bones[par].b.par;
            }
            func_00267e60(m0[3], m80[3], m40[3], f);
            func_00267e60(m0[0], m80[0], m40[0], f);
            func_00162c20(m0[0]);
            func_00267e60(m0[1], m80[1], m40[1], f);
            func_00162c20(m0[1]);
            func_00267370(m0[2], m0[0], m0[1]);
            func_00162c20(m0[2]);
            func_00267370(m0[1], m0[2], m0[0]);
            func_00162c20(m0[1]);
            if (par == 0x3FF) {
                func_00162c5c(o->p158[i], D_00573F10[0], m0);
                inl_scl(o->p154[i], o->p158[i], o->p150[i][1]);
                func_00162848(o->p154[i][3], D_00573F10[0], m0[3]);
            } else {
                func_00162c5c(o->p158[i], o->p158[par], m0);
                inl_scl(o->p154[i], o->p158[i], o->p150[i][1]);
                func_00162848(o->p154[i][3], o->p154[par], m0[3]);
            }
        }
    }
    for (i = 0; o->p16C[i].h0 >= 0; i++) {
        (*o->p0)->bones[(*o->p0)->bones[o->p16C[i].h0].b.par].b.flag = o->p16C[i].w4;
    }
    if (fabsf(D_00574F20[0] - 1.0f) > 0.005f || fabsf(D_00574F20[1] - 1.0f) > 0.005f
        || fabsf(D_00574F20[2] - 1.0f) > 0.005f) {
        sceVu0UnitMatrix(m40);
        m40[0][0] = D_00574F20[0];
        m40[1][1] = D_00574F20[1];
        m40[2][2] = D_00574F20[2];
        for (i = 0; i < (*o->p0)->n; i++) func_00162c5c(o->p154[i], m40, o->p154[i]);
    }
    for (i = 0; i < (*o->p0)->n; i++) {
        o->p154[i][3][0] += D_00574F10[0];
        o->p154[i][3][1] += D_00574F10[1];
        o->p154[i][3][2] += D_00574F10[2];
    }
}
