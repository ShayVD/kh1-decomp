/* Round 47 wwm2: score 228 -> 220, hill3o statement order. Earlier header below. */
/* Round 36 (wwm2): wm.x func_00f6d810 near miss: score 236 -> 234 (357 -> 358 words, 1992 = 1992); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, 120 s, seed 363). Earlier header below. Round 22 (wwm1): the if/else at line(s) 170 with the arms swapped and the test negated (ifswap.py): score 234 -> 228. */
/* score 236 (1992 vs 1992). The pad-search section matches exactly: the up path does goto win into the down path tail, and the window calc is (n - 8) << 4 / (i - n + 8) << 4. Left: in the 10-entry draw loop the original keeps the counter in s0 and spills n (sp144), while this draft hoists &D_00FB4C48 into s7 and spills the counter instead, which shifts every register after that point. Tried volatile D_00FB4C48, do-while and goto loops, and a register asm counter. None fixed it. The tail ordering of D_0108F1C0 and p->b5 also differs a little. */
typedef struct { u8 pad[176]; s32 x; s32 y; u8 pad2[6]; s16 hbe; s16 pad3; s16 hc2; u8 pad4[12]; s16 hd0; s16 hd2; } Obj;
typedef struct { u8 b0; u8 pad1[4]; u8 b5; u8 b6; u8 b7; u8 pad8[8]; } Ent;
typedef struct { u64 tex; u16 u, v, w, h; s16 x, y, sw, sh; s32 col; } Spr;
typedef struct { s32 v[2]; } Pair;
extern s32 D_002C5AD8;
extern u32 D_002C5AE0;
extern s32 D_00FB4A70;
extern s32 D_00FB4B48;
extern s32 D_00FB4C48;
extern s32 D_00FB4C50, D_00FB4C54, D_00FB4C58, D_00FB4C5C;
extern s32 D_00FB4C60, D_00FB4C64, D_00FB4C68, D_00FB4C6C;
extern s32 D_00FB4C70, D_00FB4C74, D_00FB4C78, D_00FB4C7C;
extern s32 D_00FB4C80, D_00FB4C84, D_00FB4C88, D_00FB4C8C;
extern s32 D_00FB4C90;
extern s32 D_00FB4C94;
extern Pair D_00FBA0F8;
extern s32 D_0108F188;
extern s32 D_0108F194;
extern s32 D_0108F198;
extern s32 D_0108F1BC;
extern s32 D_0108F1C0;
extern f32 D_0108F1E4;
extern f32 D_0108F1E8;
extern f32 D_0108F1EC;
extern f32 D_0108F1F0;
extern s32 D_0108F1F8;
extern s32 D_0108F254;
extern s32 D_0108F288;
extern s32 D_0108F28C;
void func_0011d768(s32);
void func_001bb558(void);
Ent *func_001bc4d0(void);
s32 func_001bc500(void);
void func_001f3840(Obj *);
s32 func_001f42b8(Obj *);
s32 func_001f4390(Obj *);
void func_001f8ee0(Obj *);
void func_001f8f30(void);
void func_001fb428(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd548(Obj *);
s32 func_001fd590(Obj *);
s32 func_001fd618(Obj *);
void func_001fd858(Obj *);
void func_002016b0(Obj *, s32, s32, s32);
void func_00202fc0(Obj *);
void func_00206b70(Obj *, Spr *);
void func_002078f0(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f59760(s32, Spr *);
void func_00f60548(s32, s32, s32, OvlMtx, f32);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0UnitMatrix(OvlMtx);

void func_00f6d810(Obj *o)
{
    u32 b;
    Pair c;
    Ent *e;

    Spr spr;
    OvlMtx m;
    s32 n, i, cur, k, moved, y, sel, col1, col2;
    Ent *p;
    s32 v;
    OvlVec rot;
    c = D_00FBA0F8;
    func_001bc4d0();
    for (i = 0, n = 0; i < func_001bc500(); i++) n++;
    e = func_001bc4d0();
    if (func_001f42b8(o)) {
        moved = 0;
        b = D_002C5AE0 | D_002C5AE0 >> 24;
        if (b & 0x20) {
            cur = func_001fd548(o);
            v = e[cur].b5;
            for (i = cur + 1; i < n && e[i].b5 == v; i++);
            if (i == n) {
                for (i = 0; i < cur && e[i].b5 == v; i++);
            }
            goto win;
        } else if (b & 0x80) {
            cur = func_001fd548(o);
            v = e[cur].b5;
            for (i = cur - 1; i >= 0 && e[i].b5 == v; i--);
            if (i < 0) {
                for (i = n - 1; cur < i && e[i].b5 == v; i--);
            }
            if (i > 0) {
                v = e[i].b5;
                for (i--; i >= 0; i--) {
                    if (e[i].b5 != v) {
                        i++;
                        break;
                    }
                }
            }
win:
            if (i < 0) i = 0;
            if (n - i < 8) {
                o->hd0 = (n - 8) << 4;
                o->hd2 = (i - n + 8) << 4;
            } else {
                o->hd2 = 0;
                o->hd0 = i * 16;
            }
            func_0011d768(1);
            moved = 1;
        }
        if (!moved) func_001fd858(o);
    }
    func_001bb558();
    func_00202fc0(o);
    func_001f8ee0(o);
    i = func_001fd618(o);
    y = func_001fd590(o);
    sel = func_001fd548(o);
    o->hbe = 0;
    o->hc2 = (u16)D_00FB4C48 * 16;
    for (k = 0; k < 10; k++) {
        if (i < n) {
            p = &e[i];
            func_002078f0(o, c.v[sel == i], 2, 0, 0, y, D_00FB4C48, D_00FB4B48, p->b7);
            if (sel == i) {
                col1 = D_00FB4C60 | (D_00FB4C64 << 8) | (D_00FB4C68 << 16) | (D_00FB4C6C << 24);
                col2 = D_00FB4C80 | (D_00FB4C84 << 8) | (D_00FB4C88 << 16) | (D_00FB4C8C << 24);
                spr.col = 0x80808080;
                if (func_001f4390(o)) {
                    D_0108F194 = (o->x >> 4) + D_00FB4C48 - 1792;
                    D_0108F198 = (o->y >> 4) + y - 1856;
                }
            } else {
                spr.col = 0x40404040;
                col1 = D_00FB4C50 | (D_00FB4C54 << 8) | (D_00FB4C58 << 16) | (D_00FB4C5C << 24);
                col2 = D_00FB4C70 | (D_00FB4C74 << 8) | (D_00FB4C78 << 16) | (D_00FB4C7C << 24);
            }
            func_002016b0(o, D_00FB4C48 + 6, y + 2, col1);
            func_001fb428(o, 1, 4, 0, D_00FB4C48 + 42, y + 5, p->b0, 15, col2);
            func_00f59760(p->b5, &spr);
            spr.x = 10;
            spr.y = y + 6;
            spr.sw = 16;
            spr.sh = 16;
            y += 28;
            func_00206b70(o, &spr);
        }
        i++;
    }
    p = &e[sel];
    D_0108F288 = sel;
    if (D_0108F188 == 0) {
        D_0108F254 = 0;
        D_0108F1BC = 0;
        D_0108F1E8 = 0;
    }
    if (p->b5) {
        rot[0] = 0.43633226f;
        rot[1] = 0.43633226f;
        rot[2] = 0;
        D_0108F28C = -1;
        rot[3] = 1.0f;
        if (D_0108F1EC != D_0108F1F0) {
            if (D_0108F1F0 < D_0108F1EC) {
                D_0108F1EC = D_0108F1EC - 128.0f / D_00FB4A70;
                if (D_0108F1EC < D_0108F1F0) D_0108F1EC = D_0108F1F0;
            } else {
                D_0108F1E4 += 128.0f / D_00FB4A70;
            }
        }
        if (!(D_0108F1C0)) {
            sceVu0UnitMatrix(m);
            sceVu0RotMatrix(m, m, rot);
            func_00f60548(D_00FB4C90, D_00FB4C94, p->b6, m, D_0108F1EC * 0.0078125f);
            D_0108F1C0 = 0;
        } else {
            D_0108F1C0 = 0;
        }
    } else if (D_0108F188 == 0) {
        D_0108F28C = p->b6;
        if (p->b6 >= 71) {
            D_0108F254 = 1;
            D_0108F1F8 = p->b6;
            D_0108F1BC = 4;
            D_0108F1E8 = 128.0f;
        }
    }
    func_001f8f30();
    if (func_001f4390(o)) {
        if (D_002C5AD8 & 0x4000) {
            func_001f3840(o);
            func_0011d768(3);
            D_0108F188 = 1;
            D_0108F1F0 = 0.0f;
        }
    }
}
