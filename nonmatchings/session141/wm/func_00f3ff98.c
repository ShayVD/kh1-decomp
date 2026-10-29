/* 3 words left (round 12): only the reorg delay-slot fill in the second loop (target bne with slt in the slot and bc1f with nop; we get bnel/bc1fl). Keys that got it from 159 to 3: the ssf() address helper (same idea as func_00f3fb28), array expressions instead of a Sub pointer, a local for k->f0, and dir = D[idx].s.dir = k->b8 & 1. Tried: continue/nested/reordered conditions (6 orders), k->sp > 0 forms; a 10 min permuter found nothing usable. */
typedef struct { s32 id; s32 a; s32 b; f32 val; f32 v2; s32 dir; } Sub;
typedef struct { f32 m0[4][4]; f32 m1[4][4]; f32 m2[4][4]; f32 m3[16][4][4]; f32 m4[2][4][4]; Sub s; u8 pad2[0x590 - 0x558]; } W;
typedef struct { f32 f0; u8 kind; u8 pad; u16 flag; u8 b8; u8 pad9[23]; u16 h32; u8 pad34[2]; u16 h36; u8 pad38[14]; f32 sp; } K;
typedef struct { u8 pad[8]; u16 h8; } Q;
extern W D_00F86500[];
extern W *D_00F864C0;
extern s32 D_00F9B2D4, D_00F9B2D8, D_00F85098;
f32 func_00f62b60(s32);
K *func_00f62bc8(s32, s32);
f32 func_00f3f718(s32);
s32 func_00f62b90(s32);
K *func_00f62b98(s32, s32);
Q *func_00f62c78(s32, s32);
void func_00f3fe68(K *, s32);
void func_00f3de10(void);
void func_00f3cac8(void);
void sceVu0UnitMatrix(f32 (*)[4]);
void func_00f405d8(s32, f32 (*)[4], f32 (*)[4]);

#define SS ({ s32 b_ = (s32)D_00F86500; (Sub *)((u8 *)(Sub *)(idx * 0x590 + 0x540) + b_); })
s32 func_00f3ff98(s32 idx, s32 dir, s32 sel) {
    f32 v;
    Sub *s;
    K *k;
    s32 i;
    s32 n;
    f32 t;

    if (dir >= 0) D_00F86500[idx].s.dir = dir;
    if (D_00F86500[idx].s.dir == 0) {
        SS->val = 0;
        D_00F9B2D4 = 0;
        D_00F9B2D8 = func_00f62b60(SS->id);
    } else {
        SS->val = func_00f62b60(SS->id);
        D_00F9B2D4 = 0;
        D_00F9B2D8 = func_00f62b60(SS->id);
    }
    if (sel >= 0) {
        s = SS;
        k = func_00f62bc8(sel, s->id);
        if (k != NULL) {
            v = k->f0;
            s->val = v;
            dir = D_00F86500[idx].s.dir = k->b8 & 1;
            if (dir == 0) {
                D_00F9B2D4 = v;
                t = func_00f3f718(s->id);
                if (s->val < t) {
                    D_00F9B2D8 = t;
                } else {
                    D_00F9B2D8 = func_00f62b60(s->id);
                }
            } else {
                D_00F9B2D8 = v;
                t = func_00f3f718(s->id);
                if (t < s->val) {
                    D_00F9B2D4 = t;
                } else {
                    D_00F9B2D4 = 0;
                }
            }
        }
    }
    D_00F86500[idx].s.v2 = SS->val;
    n = func_00f62b90(SS->id);
    for (i = 0; i < n; i++) {
        k = func_00f62b98(i, SS->id);
        k->flag = 0;
        if ((u8)(k->kind - 2) < 2) {
            k->h36 = func_00f62c78(k->h32, D_00F864C0->s.id)->h8;
        }
    }
    n = func_00f62b90(SS->id);
    for (i = 0; i < n; i++) {
        k = func_00f62b98(i, SS->id);
        if (k->kind == 1 && !(k->flag & 0x80) && 0.0f < k->sp) {
            func_00f3fe68(k, SS->id);
        }
    }
    func_00f3de10();
    func_00f3cac8();
    D_00F85098 = 0;
    sceVu0UnitMatrix(D_00F86500[idx].m2);
    func_00f405d8(idx, D_00F86500[idx].m0, D_00F86500[idx].m1);
    return dir;
}
