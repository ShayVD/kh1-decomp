/* Round 42 wwm2: score 230 -> 228, port.py of the wm twin func_00f6d810 draft, with wm D_00FB4C7C mapped by hand to gb D_00F704FC. Earlier header below. */
/* score 236 (1992 vs 1992). Port of the wm func_00f6d810 near miss (same score), with symbols mapped by portmap.py plus D_00F704FC by hand. The draw-loop register difference is the same as in wm; see nonmatchings/session141/wm/func_00f6d810.c. Round 22 (wwm1): the if/else at line(s) 169 with the arms swapped and the test negated (ifswap.py): score 236 -> 230. */
typedef struct { u8 pad[176]; s32 x; s32 y; u8 pad2[6]; s16 hbe; s16 pad3; s16 hc2; u8 pad4[12]; s16 hd0; s16 hd2; } Obj;
typedef struct { u8 b0; u8 pad1[4]; u8 b5; u8 b6; u8 b7; u8 pad8[8]; } Ent;
typedef struct { u64 tex; u16 u, v, w, h; s16 x, y, sw, sh; s32 col; } Spr;
typedef struct { s32 v[2]; } Pair;
extern s32 D_002C5AD8;
extern u32 D_002C5AE0;
extern s32 D_00F702F0;
extern s32 D_00F703C8;
extern s32 D_00F704C8;
extern s32 D_00F704D0, D_00F704D4, D_00F704D8, D_00F704DC;
extern s32 D_00F704E0, D_00F704E4, D_00F704E8, D_00F704EC;
extern s32 D_00F704F0, D_00F704F4, D_00F704F8, D_00F704FC;
extern s32 D_00F70500, D_00F70504, D_00F70508, D_00F7050C;
extern s32 D_00F70510;
extern s32 D_00F70514;
extern Pair D_00F74048;
extern s32 D_00F829C8;
extern s32 D_00F829D4;
extern s32 D_00F829D8;
extern s32 D_00F829FC;
extern s32 D_00F82A00;
extern f32 D_00F82A24;
extern f32 D_00F82A28;
extern f32 D_00F82A2C;
extern f32 D_00F82A30;
extern s32 D_00F82A38;
extern s32 D_00F82A94;
extern s32 D_00F82AC8;
extern s32 D_00F82ACC;
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
void func_00f32668(s32, Spr *);
void func_00f39450(s32, s32, s32, OvlMtx, f32);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0UnitMatrix(OvlMtx);

void func_00f46718(Obj *o)
{
    Pair c;
    Spr spr;
    OvlMtx m;
    OvlVec rot;
    s32 n, i, cur, k, moved, y, sel, col1, col2;
    u32 b;
    s32 v;
    Ent *e;
    Ent *p;

    c = D_00F74048;
    func_001bc4d0();
    for (i = 0, n = 0; i < func_001bc500(); i++) n++;
    e = func_001bc4d0();
    if (func_001f42b8(o)) {
        b = D_002C5AE0 | D_002C5AE0 >> 24;
        moved = 0;
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
            if (i < 0) i = 0;
win:
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
    o->hc2 = (u16)D_00F704C8 * 16;
    for (k = 0; k < 10; k++) {
        if (i < n) {
            p = &e[i];
            func_002078f0(o, c.v[sel == i], 2, 0, 0, y, D_00F704C8, D_00F703C8, p->b7);
            if (sel == i) {
                col1 = D_00F704E0 | (D_00F704E4 << 8) | (D_00F704E8 << 16) | (D_00F704EC << 24);
                col2 = D_00F70500 | (D_00F70504 << 8) | (D_00F70508 << 16) | (D_00F7050C << 24);
                spr.col = 0x80808080;
                if (func_001f4390(o)) {
                    D_00F829D4 = (o->x >> 4) + D_00F704C8 - 1792;
                    D_00F829D8 = (o->y >> 4) + y - 1856;
                }
            } else {
                col1 = D_00F704D0 | (D_00F704D4 << 8) | (D_00F704D8 << 16) | (D_00F704DC << 24);
                spr.col = 0x40404040;
                col2 = D_00F704F0 | (D_00F704F4 << 8) | (D_00F704F8 << 16) | (D_00F704FC << 24);
            }
            func_002016b0(o, D_00F704C8 + 6, y + 2, col1);
            func_001fb428(o, 1, 4, 0, D_00F704C8 + 42, y + 5, p->b0, 15, col2);
            func_00f32668(p->b5, &spr);
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
    D_00F82AC8 = sel;
    if (D_00F829C8 == 0) {
        D_00F82A94 = 0;
        D_00F829FC = 0;
        D_00F82A28 = 0;
    }
    if (p->b5) {
        rot[0] = 0.43633226f;
        D_00F82ACC = -1;
        rot[2] = 0;
        rot[1] = 0.43633226f;
        rot[3] = 1.0f;
        if (D_00F82A2C != D_00F82A30) {
            if (D_00F82A30 < D_00F82A2C) {
                D_00F82A2C = D_00F82A2C - 128.0f / D_00F702F0;
                if (D_00F82A2C < D_00F82A30) D_00F82A2C = D_00F82A30;
            } else {
                D_00F82A24 += 128.0f / D_00F702F0;
            }
        }
        if (!(D_00F82A00)) {
            sceVu0UnitMatrix(m);
            sceVu0RotMatrix(m, m, rot);
            func_00f39450(D_00F70510, D_00F70514, p->b6, m, D_00F82A2C * 0.0078125f);
            D_00F82A00 = 0;
        } else {
            D_00F82A00 = 0;
        }
    } else if (D_00F829C8 == 0) {
        D_00F82ACC = p->b6;
        if (p->b6 >= 71) {
            D_00F82A94 = 1;
            D_00F82A38 = p->b6;
            D_00F829FC = 4;
            D_00F82A28 = 128.0f;
        }
    }
    func_001f8f30();
    if (func_001f4390(o)) {
        if (D_002C5AD8 & 0x4000) {
            func_001f3840(o);
            func_0011d768(3);
            D_00F829C8 = 1;
            D_00F82A30 = 0.0f;
        }
    }
}
