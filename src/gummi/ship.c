/* The Gummi ships (docs/modules.md "Session 48"), 0x001bb558-0x001be758:
 *
 * - the block table D_00377848 (func_001bb580 counts the kinds that can be
 *   held, D_00623214, and the rest, D_00623218; func_001bb658(i) is block
 *   i's GumiBlock, func_001bb6d0 its size in the grid), the block names
 *   (func_001bb558 opens the text D_00378A48), the grid size allowed
 *   (func_001bb678: 6, 8 or 10 by the held blocks 66 / 67), two align
 *   helpers and a file read that yields to the tasks until it is done
 *   (func_001bb7c8);
 * - func_001bb880 packs the ten saved ships to the front, keeping the
 *   pairs (GumiShip.link) and the current ship; func_001bbbd0 /
 *   func_001bbce0 / func_001bbf38 a placed block's turn and place as
 *   matrices (200 units a cell), func_001bbdf0 its turned size and
 *   func_001bbf88 turns it a quarter about an axis;
 * - the garage: func_001bc530 a ship's bounds and radius, func_001bc900 its
 *   summary (GumiInfo), func_001bcd10 copies a ship keeping only the blocks
 *   that are held and within the limits (func_001be680 / func_001be6c8 /
 *   func_001be710: blocks, engines?, the 58-63 kinds), func_001bd090 its
 *   stats; func_001bd470 builds the lists: the edited ship, the preset
 *   ships of held blocks 71-118 (D_00625640 of them, D_00625648 their
 *   numbers), the ten saved ships (D_00623E40) and the held blocks
 *   (D_00623230); func_001bd880 / func_001bd9e8 / func_001bdb58 the part
 *   slots D_00625750 (ten kinds, each with a colour?), func_001be010 /
 *   func_001be110 save the edited ship into a slot.
 *
 * Names are read from the code and the save block, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "gummi/gummi.h"
#include "data/bss_0062.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "platform/math.h"

typedef f32 Mtx[4][4];
/* A turned size's nibbles (func_001bbdf0) */
#define DX ((u16)r & 0xf)
#define DY (((u16)r >> 4) & 0xf)
#define DZ (((u16)r >> 8) & 0xf)
typedef union { u16 h; struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 w : 4; } b; } GumiRot;
typedef struct { u8 p0[36]; s32 w24; u8 p28[8]; } Info48;

extern s32 D_0037A128;
extern GumiDir D_0037A130[16];
extern s32 D_0037A158;
extern GumiBlockTbl D_00377848;
extern s32 D_00378A48;
extern s32 D_00379C78;
extern GumiBlockTbl *D_00623210;
extern GumiBlock *D_0062321C;
extern s32 D_00625640;
extern s32 D_00625648[];
extern GumiShip *D_006257D0;
extern GumiShip D_00621320;
extern GumiShip D_00622290;
extern GumiCell D_00623230[];
extern GumiInfo D_00623E40[];
/* D_00623E40[k + 1].name; sized as the old files did, for cover_check
 * (unsized, D_00625640 after it became covered). */
extern s32 D_00623ED4;
#define D_00623ED4_NAME ((u8 (*)[96])&D_00623ED4)
extern u8 D_00623E49[][96];
extern GumiSlot D_00625750[];

s32 func_001efb18(void *, void *);
s32 func_00120748(char *, void *, void (*)(s32), s32);
void func_001bfac8(void);
void *memset(void *, s32, u32);
void func_001be820(void *, u32);
s32 func_001ba3f0(s32);
s32 func_001ba3d8(void);
void func_001ba060(GumiShip *, s32);
void func_001ba108(GumiShip *, s32);
s32 func_001baad0(void);
void func_001baaa8(s32);
s32 func_001b9df0(s32);
void func_001b9e40(s32, s32);
GumiBlock *func_001bb658(s32);
s32 func_001bb678(void);
s32 func_001bb6d0(s32);
s32 func_001bb740(void);
void func_001bb7b0(s32);
s32 func_001bb880(s32);
void func_001bbbd0(Mtx, GumiPiece *);
void func_001bbce0(Mtx, GumiPiece *);
s32 func_001bbdf0(GumiPiece *);
s32 func_001bc4a8(void);
s32 func_001bc4b8(s32);
void func_001bc530(FVec4 *, FVec4 *, FVec4 *, GumiShip *);
void func_001bc900(GumiShip *, GumiInfo *);
s32 func_001bcd10(GumiShip *, GumiShip *);
void func_001bd010(GumiShip *);
void func_001bd090(GumiShip *, GumiStat *);
void func_001bd470(void);
void func_001bd880(GumiShip *);
s32 func_001be110(s32, GumiShip *);
s32 func_001be5c8(s32);
s32 func_001be5d0(s32);
s32 func_001be600(s32);
s32 func_001be680(void);
s32 func_001be6c8(void);
s32 func_001be710(void);

void func_001bb558(void) {
    func_001efb18(&D_00378A48, &D_00379C78);
}

void func_001bb580(void) {
    s32 i, j;
    D_00623210 = &D_00377848;
    D_0062321C = D_00377848.e;
    D_00623214 = 0;
    for (i = 0; D_0062321C[i].type != 0; i++) D_00623214++;
    for (j = 0; D_0062321C[i + j].type == 0; j++);
    D_00623218 = D_00623210->n - D_00623214 - j;
}

GumiBlock *func_001bb658(s32 i) {
    return &D_0062321C[i];
}

s32 func_001bb678(void) {
    s32 r = 6;
    if (func_001ba3f0(66) > 0) r = 8;
    if (func_001ba3f0(67) > 0) r = 10;
    return r;
}

s32 func_001bb6d0(s32 i) {
    u8 x = D_0062321C[i].size; s32 a, b; u16 c; a = (x & 3) + 1; x >>= 2; b = (x & 3) * 16 + 16; x >>= 2; c = (x & 3) + 1; return b | a | (c << 8);
}

s32 func_001bb720(void) {
    return D_00623214;
}

s32 func_001bb730(void) {
    return D_00623218;
}

s32 func_001bb740(void) {
    return D_00623210->n;
}

u32 func_001bb750(u32 a, u32 b) {
    if (a % b) a += b - a % b;
    return a;
}

u32 func_001bb780(u32 a, u32 b) {
    if (a % b) a -= a % b;
    return a;
}

void func_001bb7b0(s32 arg0) {
    D_00623224 = arg0;
    D_00623220 = 0;
}

s32 func_001bb7c8(char *a, void *b) {
    D_00623220 = 1;
    D_00623224 = -1;
    func_00120748(a, b, func_001bb7b0, 0);
    while (D_00623220) func_001bfac8();
    return D_00623224;
}

s32 func_001bb848(void) {
    return D_00623220;
}

void func_001bb858(s32 arg0, s32 arg1) {
    D_002BC140 = arg0;
    D_002BC144 = arg1;
}

void func_001bb870(GumiShip *s) {
    D_006257D0 = s;
}

s32 func_001bb880(s32 idx) {
    s32 map[16];
    s32 list[10];
    GumiShip *e;
    s32 i, n, j, k;

    e = func_001ba9d8(0);
    k = -1;
    n = 0;
    for (i = 0; i < 10; i++, e++) {
        if (e->n == 0)
            map[i] = k;
        else
            map[i] = n++;
    }
    i = func_001baad0();
    if (i >= 0) {
        if (map[i] >= 0)
            func_001baaa8(map[i]);
        else
            func_001baaa8(0);
    }
    e = func_001ba9d8(0);
    for (i = 0; i < 10; i++, e++) {
        if (e->n && e->link)
            e->link = map[e->link - 1] + 1;
    }
    if (D_006257D0) {
        e = D_006257D0;
        if (e->n && e->link)
            e->link = map[e->link - 1] + 1;
    }
    e = func_001ba9d8(0);
    n = 0;
    for (i = 0; i < 10; i++) {
        if (e[i].n)
            list[n++] = i;
    }
    for (i = 0; i < 10 && i < n; i++) {
        if (i != list[i])
            e[i] = e[list[i]];
    }
    for (; i < 10; i++)
        func_001be820(&e[i], sizeof(GumiShip));
    e = func_001ba9d8(0);
    for (i = 0; i < 10; i++, e++) {
        if (e->link) {
            j = e->link - 1;
            if (j == i || func_001ba9d8(j)->link - 1 != i)
                e->link = 0;
        }
    }
    return map[idx];
}

void func_001bbbd0(f32 (*m)[4], GumiPiece *o) {
    m[0][0] = D_0037A130[*(u16 *)&o->rot & 15].x;
    m[0][1] = D_0037A130[*(u16 *)&o->rot & 15].y;
    m[0][2] = D_0037A130[*(u16 *)&o->rot & 15].z;
    m[0][3] = 0;
    m[1][0] = D_0037A130[(*(u16 *)&o->rot >> 4) & 15].x;
    m[1][1] = D_0037A130[(*(u16 *)&o->rot >> 4) & 15].y;
    m[1][2] = D_0037A130[(*(u16 *)&o->rot >> 4) & 15].z;
    m[1][3] = 0;
    m[2][0] = D_0037A130[(*(u16 *)&o->rot >> 8) & 15].x;
    m[2][1] = D_0037A130[(*(u16 *)&o->rot >> 8) & 15].y;
    m[2][2] = D_0037A130[(*(u16 *)&o->rot >> 8) & 15].z;
    m[2][3] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1.0f;
}

void func_001bbce0(f32 (*m)[4], GumiPiece *o) {
    FVec4 t;
    s32 v = func_001bbdf0(o);
    t.x = (f32)(o->pos & 15) * 200.0f + (f32)(v & 15) * 200.0f * 0.5f;
    t.y = -((f32)((o->pos >> 4) & 15) * 200.0f + (f32)(((u16)v >> 4) & 15) * 200.0f * 0.5f);
    t.z = (f32)((o->pos >> 8) & 15) * 200.0f + (f32)(((u16)v >> 8) & 15) * 200.0f * 0.5f;
    t.w = 1.0f;
    PlatVu0UnitMatrix(m);
    PlatVu0TransMatrix(m, m, &t);
}

s32 func_001bbdf0(GumiPiece *o) {
    GumiRot s, r;
    s32 ax, ay, az;
    
    s.h = func_001bb6d0(o->id - 1);
    ax = D_0037A130[o->rot.b.x].x * s.b.x;
    ay = D_0037A130[o->rot.b.x].y * s.b.x;
    az = D_0037A130[o->rot.b.x].z * s.b.x;
    ax += D_0037A130[o->rot.b.y].x * s.b.y;
    ay += D_0037A130[o->rot.b.y].y * s.b.y;
    az += D_0037A130[o->rot.b.y].z * s.b.y;
    ax += D_0037A130[o->rot.b.z].x * s.b.z;
    ay += D_0037A130[o->rot.b.z].y * s.b.z;
    az += D_0037A130[o->rot.b.z].z * s.b.z;
    r.b.x = abs(ax);
    r.b.y = abs(ay);
    r.b.z = abs(az);
    return r.h;
}

void func_001bbf38(Mtx m, GumiPiece *pc) {
    Mtx r;
    func_001bbce0(m, pc);
    func_001bbbd0(r, pc);
    PlatVu0MulMatrix(m, m, r);
}

void func_001bbf88(GumiPiece *o, s32 axis, s32 dir) {
    GumiDir a, b, c, t;
    s32 i;

    a = D_0037A130[o->rot.b.x];
    b = D_0037A130[o->rot.b.y];
    c = D_0037A130[o->rot.b.z];
    switch (axis) {
    case 0:
        switch (dir) {
        case -1:
            t.x = a.x; t.y = -a.z; t.z = a.y; a = t;
            t.x = b.x; t.y = -b.z; t.z = b.y; b = t;
            t.x = c.x; t.y = -c.z; t.z = c.y; c = t;
            break;
        case 1:
            t.x = a.x; t.y = a.z; t.z = -a.y; a = t;
            t.x = b.x; t.y = b.z; t.z = -b.y; b = t;
            t.x = c.x; t.y = c.z; t.z = -c.y; c = t;
            break;
        }
        break;
    case 1:
        switch (dir) {
        case 1:
            t.x = -a.z; t.y = a.y; t.z = a.x; a = t;
            t.x = -b.z; t.y = b.y; t.z = b.x; b = t;
            t.x = -c.z; t.y = c.y; t.z = c.x; c = t;
            break;
        case -1:
            t.x = a.z; t.y = a.y; t.z = -a.x; a = t;
            t.x = b.z; t.y = b.y; t.z = -b.x; b = t;
            t.x = c.z; t.y = c.y; t.z = -c.x; c = t;
            break;
        }
        break;
    case 2:
        switch (dir) {
        case -1:
            t.x = -a.y; t.y = a.x; t.z = a.z; a = t;
            t.x = -b.y; t.y = b.x; t.z = b.z; b = t;
            t.x = -c.y; t.y = c.x; t.z = c.z; c = t;
            break;
        case 1:
            t.x = a.y; t.y = -a.x; t.z = a.z; a = t;
            t.x = b.y; t.y = -b.x; t.z = b.z; b = t;
            t.x = c.y; t.y = -c.x; t.z = c.z; c = t;
            break;
        }
        break;
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == a.x && D_0037A130[i].y == a.y && D_0037A130[i].z == a.z) {
            o->rot.b.x = i;
            break;
        }
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == b.x && D_0037A130[i].y == b.y && D_0037A130[i].z == b.z) {
            o->rot.b.y = i;
            break;
        }
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == c.x && D_0037A130[i].y == c.y && D_0037A130[i].z == c.z) {
            o->rot.b.z = i;
            break;
        }
    }
}

s32 func_001bc4a8(void) {
    return D_00625640;
}

s32 func_001bc4b8(s32 i) {
    return D_00625648[i];
}

GumiCell *func_001bc4d0(void) {
    return D_00623230;
}

GumiInfo *func_001bc4e0(void) {
    return D_00623E40;
}

GumiSlot *func_001bc4f0(void) {
    return D_00625750;
}

s32 func_001bc500(void) {
    return D_00623228;
}

s32 func_001bc510(void) {
    return D_00623E30;
}

s32 func_001bc520(void) {
    return D_00625748;
}

/* func_001bc530 (hand, strict): matched in s10 r2_8. Key: lo->x/y/z computed first and v[0..2] copied from them (v[k] = lo->x), then hi, sz, v[3..5]; natural min/max order. */
void func_001bc530(FVec4 *lo, FVec4 *hi, FVec4 *sz, GumiShip *a) {
    f32 v[6];
    f32 h[3];
    s32 i, first;
    s32 x0, y0, z0, x1, y1, z1;
    s32 px, py, pz, dx, dy, dz;
    s32 r, pos;
    GumiPiece *pc;
    if (a->n == 0) {
        sz->x = 200.0f;
        sz->y = 200.0f;
        sz->z = 200.0f;
        sz->w = 200.0f;
        return;
    }
    
    x0 = 0;
    y0 = 0;
    z0 = 0;
    x1 = 0;
    y1 = 0;
    z1 = 0;

    pc = a->p;
    first = 0;
    for (i = 0; i < a->n; i++, pc++) {
        r = func_001bbdf0(pc);
        pos = pc->pos;
        px = (u16)pos & 0xf;
        py = ((u16)pos >> 4) & 0xf;
        pz = ((u16)pos >> 8) & 0xf;
        if (first) {
            if (px < x0) x0 = px;
            if (py < y0) y0 = py;
            if (pz < z0) z0 = pz;
            if (x1 < px + DX - 1) x1 = px + DX - 1;
            if (y1 < py + DY - 1) y1 = py + DY - 1;
            if (z1 < pz + DZ - 1) z1 = pz + DZ - 1;
        } else {
            x0 = px;
            y0 = py;
            z0 = pz;
            x1 = x0 + DX - 1;
            y1 = y0 + DY - 1;
            z1 = z0 + DZ - 1;
        }
        first = 1;
    }
    h[0] = a->sx * 200.0f * 0.5f;
    h[1] = a->sy * 200.0f * 0.5f;
    h[2] = a->sz * 200.0f * 0.5f;
    lo->x = x0 * 200.0f - h[0];
    lo->y = y0 * 200.0f - h[1];
    lo->z = z0 * 200.0f - h[2];
    v[0] = lo->x;
    v[1] = lo->y;
    v[2] = lo->z;
    hi->x = (x1 + 1) * 200.0f - h[0];
    hi->y = (y1 + 1) * 200.0f - h[1];
    hi->z = (z1 + 1) * 200.0f - h[2];
    sz->x = (x1 - x0 + 1) * 200.0f;
    sz->y = (y1 - y0 + 1) * 200.0f;
    sz->z = (z1 - z0 + 1) * 200.0f;
    v[3] = x1 * 200.0f - h[0];
    v[4] = y1 * 200.0f - h[1];
    v[5] = z1 * 200.0f - h[2];
    for (i = 0; i < 6; i++) {
        if (v[i] < 0.0f) v[i] = -v[i];
    }
    if (v[3] > v[0]) v[0] = v[3];
    if (v[4] > v[1]) v[1] = v[4];
    if (v[5] > v[2]) v[2] = v[5];
    sz->w = PlatSqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (sz->w <= 0.0f) sz->w = 200.0f;
}

/* func_001bc900 (s7 w34): MATCH with wqb03_rr.py 004900C0 (rodata jtbl 0x4900C0), mode hand. From the s6 51w draft: (1) loop 2 reads rot as *(u16 *)((u8 *)a + off + 2) with a block-local s32 off = i * 12 + 0x70 (no a+2 giv, frame 192); (2) the size tier written out with the function-level t: t = total; if (t < 75) t = 1; else if (t < 150) t = 2; else t = 3; (gives the param-copy move, xori 0 and t in a1 in the lv block too). */
void func_001bc900(GumiShip *a, GumiInfo *o) {
    FVec4 v;
    s32 cnt[16];
    GumiStat st;
    s32 i, k, r, t, total, flag;
    GumiBlock *it;
    func_001bd090(a, &st);
    o->b10 = 0;
    r = func_001bcd10(&D_00622290, a);
    if (r) o->b10 |= r << 4;
    for (i = 0; i < 16; i++) cnt[i] = 0;
    o->b3 = *(u8 *)&st.x36;
    o->b7 = *(u8 *)&st.x16;
    o->b4 = 0;
    if (func_001ba3f0(49) > 0) o->b4 = 1;
    if (st.lv == 0) t = 0;
    else if (st.lv < 100) t = 1;
    else if (st.lv < 120) t = 2;
    else t = 3;
    o->b5 = t;
    total = 0;
    o->b11 = 0;
    for (i = 0; i < a->n; i++) {
        s32 id = a->p[i].id;
        it = func_001bb658(id - 1);
        switch (id) {
        case 55: if (o->b7 == 0) o->b7 = 1; break;
        case 56: if (o->b7 < 2) o->b7 = 2; break;
        case 49: o->b3 = 1; break;
        case 59: if (o->b11 == 0) o->b11 = 1; break;
        case 60: if (o->b11 < 2) o->b11 = 2; break;
        case 62: if (o->b11 == 0) o->b11 = 1; break;
        case 63: if (o->b11 < 2) o->b11 = 2; break;
        case 61: case 64: if (o->b11 < 3) o->b11 = 3; break;
        }
        cnt[it->type] = 1;
        if (it->type != 1) total = total + it->f24;
    }
    t = total;
    if (t < 75) t = 1; else if (t < 150) t = 2; else t = 3;
    o->b6 = t;
    if (cnt[2]) {
        flag = 1;
        for (i = 0; i < a->n; i++) {
            if (func_001bb658(a->p[i].id - 1)->type == 2) {
                { s32 off = i * 12 + 0x70; if (((*(u16 *)((u8 *)a + off + 2) >> 8) & 0xf) == 4) flag = 0; }
            }
        }
    } else {
        flag = 0;
    }
    if (cnt[1] == 0) o->b10 |= 1;
    if (cnt[2] == 0) o->b10 |= 2;
    else if (flag) o->b10 |= 4;
    if (a->sx > func_001bb678()) o->b10 |= 8;
    if ((o->b10 & 0xf) == 0) o->b2 = 1;
    else { o->b2 = 0; o->b3 = 0; }
    o->b0 = *(u8 *)&a->n;
    for (i = 0; i < 32; i++) o->name[i] = a->name[i];
    if (a->link) o->b9 = a->link + *(u8 *)&D_00625640;
    else o->b9 = 0;
    o->b8 = 1;
    func_001bc530(&o->v16, &o->v32, &v, a);
    o->f48 = v.w;
}

s32 func_001bcd10(GumiShip *dst, GumiShip *src) {
    s16 cnt[192];
    s32 i, ret, ok, t;
    s32 nc, nb, nd, f, e;

    for (i = 0; i < 192; i++)
        cnt[i] = 0;
    *dst = *src;
    nd = 0;
    dst->n = 0;
    nc = 0;
    nb = 0;
    ret = 0;
    for (i = 0; i < src->n; i++) {
        if (src->p[i].id == 0)
            continue;
        ok = 1;
        t = src->p[i].id - 1;
        e = 0;
        f = 0;
        switch (t) {
        case 4 ... 8:
            if (nb >= func_001be6c8()) {
                ok = 0;
                ret |= 4;
            }
            f = 1;
            break;
        case 58 ... 63:
            if (nc >= func_001be710()) {
                ok = 0;
                ret |= 8;
            }
            e = 1;
            break;
        }
        if (cnt[t] >= func_001ba3f0(t)) {
            ok = 0;
            ret |= 1;
        }
        if (nd >= func_001be680()) {
            ok = 0;
            ret |= 2;
        }
        if (ok) {
            nb += f;
            nc += e;
            cnt[t]++;
            nd++;
            dst->p[dst->n] = src->p[i];
            dst->n++;
        }
    }
    return ret;
}

void func_001bd010(GumiShip *dst) {
    s32 i;

    i = func_001baad0();
    if (!(i & 0x80)) {
        func_001bcd10(dst, func_001ba9d8(i));
        return;
    }
    func_001ba108(&D_00621320, i & 0x7F);
    func_001bcd10(dst, &D_00621320);
}

/* func_001bd090 (hand, strict). num/b/maxid/cnt/flag are plain locals that global-alloc spills
   (all nine s-registers are taken), so they live in reload stack slots 0..16(sp); the old drafts' local
   struct was a stand-in for those spill slots. The lv sets in the 68/69 arms are dead (lv is assigned on
   every path after the loop): life1 deletes them, which is what makes the 69 arm convert at the ce pass
   (fresh zero pseudo, first num = 3 store kept). */
void func_001bd090(GumiShip *a, GumiStat *st) {
    s32 i, id, n, sum, lv;
    s32 num, b, maxid, cnt, flag;
    f32 f;
    GumiBlock *it;
    n = 0;
    sum = 0;
    func_001be820(st, 40);
    f = 0.0f;
    if (func_001ba3f0(68) > 0) lv = 1;
    num = 3;
    cnt = 0;
    if (func_001ba3f0(69) > 0) { num = 5; lv = 2; }
    maxid = 0;
    flag = 0;
    b = 0;
    if (func_001ba3f0(70) > 0) num = num < 8 ? 8 : num;
    for (i = 0; i < a->n; i++) {
        id = a->p[i].id - 1;
        it = func_001bb658(id);
        switch (id) {
        case 0: case 1: case 2: case 3: st->x28 = id; break;
        case 52: if (st->x20 <= 0) st->x20 = 1; break;
        case 53: if (st->x20 < 2) st->x20 = 2; break;
        case 54: if (st->x16 <= 0) st->x16 = 1; break;
        case 55: if (st->x16 < 2) st->x16 = 2; break;
        case 50: if (st->x24 <= 0) st->x24 = 1; break;
        case 51: if (st->x24 < 2) st->x24 = 2; break;
        case 61: case 62: case 63: flag = 1; cnt++; break;
        case 48: st->x36 = 1; break;
        case 131: case 132: n++; sum += it->b12; break;
        }
        switch (it->type) {
        case 2: if (maxid < id) maxid = id; break;
        case 6: n++; sum += it->b12; break;
        }
        f += it->f24;
        b += it->b14;
    }
    if (flag) st->x32 = cnt;
    st->x0 = f * 4.0f / 100.0f;
    if (st->x0 > 96) st->x0 = 96;
    st->x4 = num;
    if (maxid == 0) lv = 0;
    else {
        it = func_001bb658(maxid);
        if (a->n) lv = it->b13 * b / a->n;
        else lv = it->b12;
        if (lv > it->b13) lv = it->b13;
        if (lv < it->b12) lv = it->b12;
    }
    st->lv = lv;
    if (n != 0 && sum > 0) st->x8 = sum / n;
    else st->x8 = 100;
}

void func_001bd470(void) {
    s32 i, k, n, t;
    GumiBlock *it;
    GumiCell *e = D_00623230;
    GumiInfo *o;
    GumiInfo *p = D_00623E40;
    s32 x;
    s32 buf[16];
    D_00625640 = 0;
    func_001bc900(D_006257D0, &p[0]);
    p[0].b8 = 1;
    k = 0;
    for (i = 71; i < 119; i++) {
        if (func_001ba3f0(i) > 0) {
            func_001ba060(&D_00621320, i - 71);
            func_001bc900(&D_00621320, &p[k + 1]);
            D_00625648[k] = i - 71;
            p[k + 1].b8 = 1;
            k++;
        }
    }
    D_00625640 = k;
    for (i = 0; i < 10; i++) {
        func_001bc900(func_001ba9d8(i), &p[k + 1 + i]);
        p[k + 1 + i].b8 = 0;
    }
    if (func_001ba3f0(70) > 0) D_00623E30 = k + 11;
    else if (func_001ba3f0(69) > 0) D_00623E30 = k + 6;
    else D_00623E30 = k + 2;
    it = func_001bb658(0);
    n = 0;
    o = &D_00623E40[1];
    for (i = 0; i < func_001bb740(); i++) {
        if (func_001ba3f0(i) <= 0) continue;
        e->b0 = func_001ba3f0(i);
        x = it[i].size;
        e->b6 = i;
        { s32 a; a = (x & 3) + 1; x >>= 2; a *= (x & 3) + 1; x >>= 2; a *= (x & 3) + 1; e->b1 = a; }
        e->b2 = 0;
        e->b3 = 0;
        e->b4 = 0;
        e->b5 = it[i].type;
        e->b7 = func_001be5c8(i);
        e->b8 = func_001be5d0(i);
        if ((u32)(i - 71) < 48) {
            e->b2 = o->b6;
            e->b3 = o->b5;
            e->b4 = o->b11;
            o++;
        } else {
            switch (i) {
            case 58: e->b4 = 1; break;
            case 59: e->b4 = 2; break;
            case 61: e->b4 = 1; break;
            case 62: e->b4 = 2; break;
            case 60: case 63: e->b4 = 3; break;
            }
            if (it[i].type == 1) e->b2 = 4;
            else {
                t = it[i].f24;
                if (t <= 0) e->b2 = 0;
                else if (t < 10) e->b2 = 1;
                else if (t < 20) e->b2 = 2;
                else e->b2 = 3;
            }
            if (it[i].type == 2 || it[i].type == 6) {
                if (it[i].b13 < 100) e->b3 = 1;
                else if (it[i].b13 < 120) e->b3 = 2;
                else e->b3 = 3;
            }
        }
        e++;
        n++;
    }
    D_00623228 = n;
    func_001bd010(&D_00622290);
}

void func_001bd7f8(s32 k) {
    if (k >= func_001bc4a8()) {
        func_001bcd10(&D_00622290, func_001ba9d8(k - func_001bc4a8()));
    } else {
        func_001ba108(&D_00621320, func_001bc4b8(k));
        func_001bcd10(&D_00622290, &D_00621320);
    }
    func_001bd880(&D_00622290);
}

void func_001bd880(GumiShip *unused) {
    s32 f[16];
    s32 i, k, n;
    GumiSlot *base = D_00625750;
    GumiSlot *e;

    for (i = 0; i < 16; i++)
        f[i] = 0;
    for (i = 0; i < func_001ba3d8(); i++) {
        if (func_001ba3f0(i) <= 0)
            continue;
        k = -1;
        switch (i) {
        case 4: case 5: case 6: case 7: case 8:
            k = 0;
            break;
        case 52: case 53:
            k = 1;
            break;
        case 48:
            k = 2;
            break;
        case 58:
            k = 3;
            break;
        case 59:
            k = 4;
            break;
        case 60:
            k = 5;
            break;
        case 61:
            k = 6;
            break;
        case 62:
            k = 7;
            break;
        case 63:
            k = 8;
            break;
        case 44: case 45: case 46: case 47:
            k = 9;
            break;
        }
        f[k] = 1;
    }
    n = 0;
    e = base;
    for (i = 0; i < 10; i++) {
        if (f[i]) {
            e->id = i;
            e->b = func_001be600(i);
            e->n = func_001b9df0(i);
            e++;
            n++;
        }
    }
    D_00625748 = n;
}

void func_001bd9e8(GumiShip *o) {
    s32 f[16];
    s32 i, k, n;
    GumiSlot *base = D_00625750;
    GumiSlot *e;

    for (i = 0; i < 16; i++)
        f[i] = 0;
    for (i = 0; i < o->n; i++) {
        k = -1;
        switch (o->p[i].id) {
        case 5: case 6: case 7: case 8: case 9:
            k = 0;
            break;
        case 53: case 54:
            k = 1;
            break;
        case 49:
            k = 2;
            break;
        case 59:
            k = 3;
            break;
        case 60:
            k = 4;
            break;
        case 61:
            k = 5;
            break;
        case 62:
            k = 6;
            break;
        case 63:
            k = 7;
            break;
        case 64:
            k = 8;
            break;
        case 45: case 46: case 47: case 48:
            k = 9;
            break;
        }
        f[k] = 1;
    }
    n = 0;
    e = base;
    for (i = 0; i < 10; i++) {
        if (f[i]) {
            e->id = i;
            n++;
            e->b = func_001be600(i);
            e->n = func_001b9df0(i);
            e++;
        }
    }
    D_00625748 = n;
}

void func_001bdb58(void) {
    u32 a[16];
    s32 b[16];
    s32 i, j;

    for (i = 0; i < 16; i++) {
        a[i] = 0;
        b[i] = 0;
    }
    for (i = 0; i < D_00625748; i++) {
        a[D_00625750[i].id] = D_00625750[i].n;
        switch (D_00625750[i].n) {
        case 0x400: b[10] = 1; break;
        case 0x1000: b[12] = 1; break;
        case 0x2000: b[13] = 1; break;
        case 0x4000: b[14] = 1; break;
        case 0x8000: b[15] = 1; break;
        }
    }
    a[4] = a[3];
    a[7] = a[6];
    a[5] = a[3];
    a[8] = a[6];
    j = 0;
    if (a[j] == 0) {
        if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 1;
    if (a[j] == 0) {
        if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 2;
    if (a[j] == 0) {
        if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 3;
    if (a[j] == 0) {
        if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    a[j+1] = a[j]; a[j+2] = a[j];
    j = 6;
    if (a[j] == 0) {
        if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    a[j+1] = a[j]; a[j+2] = a[j];
    func_001b9e40(0, a[0]);
    func_001b9e40(1, a[1]);
    func_001b9e40(2, a[2]);
    func_001b9e40(3, a[3]);
    func_001b9e40(4, a[4]);
    func_001b9e40(5, a[5]);
    func_001b9e40(6, a[6]);
    func_001b9e40(7, a[7]);
    func_001b9e40(8, a[8]);
}

s32 func_001be010(s32 k) {
    s32 i, r;
    GumiShip *q, *p;
    for (i = 0; i < D_00625748; i++) func_001b9e40(D_00625750[i].id, D_00625750[i].n);
    q = D_006257D0;
    p = func_001ba9d8(k - D_00625640);
    for (i = 0; i < 32; i++) {
        p->name[i] = D_00623ED4_NAME[k][i];
        q->name[i] = D_00623ED4_NAME[k][i];
    }
    r = func_001be110(k - D_00625640, q);
    func_001bd470();
    return r + D_00625640;
}

s32 func_001be110(s32 k, GumiShip *c) {
    u8 buf[32];
    Info48 inf;
    GumiShip *p;
    u8 save;
    s32 i;
    if (k < 10) {
        if (c == NULL) c = D_006257D0;
        func_001bd090(c, (GumiStat *)&inf);
        p = func_001ba9d8(k);
        save = p->link;
        for (i = 0; i < 32; i++) buf[i] = p->name[i];
        func_001bcd10(p, c);
        for (i = 0; i < 32; i++) p->name[i] = buf[i];
        if (inf.w24 != 0) p->link = save;
        else p->link = 0;
        return func_001bb880(k);
    }
}

void func_001be1e8(GumiShip *p, s32 k) {
    GumiShip **pp = &p; /* keeps the calls below from becoming tail calls */
    if (p == NULL) p = D_006257D0;
    func_001be820(p, 3952);
    if (!(k & 0x80)) {
        if (k < 10) func_001bcd10(D_006257D0, func_001ba9d8(k));
    } else {
        func_001ba108(p, k & 0x7f);
    }
}

s32 func_001be278(void) {
    s32 v, i;
    if (D_0037A128 != 0) return -1;
    v = func_001baad0();
    if (!(v & 0x80)) return v + D_00625640;
    for (i = 0; i < D_00625640; i++) {
        if (D_00625648[i] == (v & 0x7f)) return i;
    }
    func_001baaa8(0x80);
    return 0;
}

void func_001be320(s32 k) {
    if (k >= D_00625640) {
        func_001baaa8(k - D_00625640);
        return;
    }
    func_001baaa8(D_00625648[k] | 0x80);
}

void func_001be370(s32 k) {
    if (k >= D_00625640) {
        func_001baaa8(k - D_00625640);
        return;
    }
    func_001baaa8(D_00625648[k] | 0x80);
}

void func_001be3c0(s32 arg0) {
    s32 var_a1;
    u8 *var_a0;
    u8 *var_v1;
    u8 temp_v0;

    var_a0 = (u8 *)func_001ba9d8(arg0 - D_00625640) + 0x50;
    var_v1 = (u8 *)&D_00623ED4 + (arg0 * 0x60);
    var_a1 = 0x1F;
    do {
        temp_v0 = *var_v1;
        var_v1 += 1;
        var_a1 -= 1;
        *var_a0 = temp_v0;
        var_a0 += 1;
    } while (var_a1 >= 0);
}

void func_001be430(s32 arg0) {
    memset(func_001ba9d8(arg0 - D_00625640), 0, 0xF70);
    func_001bb880(0);
    func_001bd470();
}

void func_001be470(void) {
    s32 i;
    for (i = 0; i < D_00625748; i++) func_001b9e40(D_00625750[i].id, D_00625750[i].n);
}

void func_001be4d8(void) {
    s32 i;
    GumiShip *c;
    for (i = D_00625640 + 1; i < D_00623E30; i++) {
        c = func_001ba9d8(i - D_00625640 - 1);
        if (D_00623E49[i][0]) c->link = D_00623E49[i][0] - (u8)D_00625640;
        else c->link = 0;
        if ((u8)(c->link - 1) >= 10) c->link = 0;
    }
}

void func_001be5b0(void) {
    func_001bd470();
}

s32 func_001be5c8(s32 arg0) {
    return arg0 + 1;
}

s32 func_001be5d0(s32 arg0) {
    return arg0 + func_001bb740() + 1;
}

s32 func_001be600(s32 arg0) {
    return arg0 + (func_001bb740() * 2) + 1;
}

s32 func_001be630(s32 arg0) {
    return arg0 + (func_001bb740() * 2) + 0xB;
}

s32 func_001be660(void) {
    return D_0037A158;
}

void func_001be670(s32 arg0) {
    D_0037A158 = arg0;
}

s32 func_001be680(void) {
    if (func_001ba3f0(70)) return 200;
    return func_001ba3f0(69) ? 150 : 100;
}

s32 func_001be6c8(void) {
    if (func_001ba3f0(70)) return 6;
    return func_001ba3f0(69) ? 4 : 2;
}

s32 func_001be710(void) {
    if (func_001ba3f0(70)) return 10;
    return func_001ba3f0(69) ? 6 : 4;
}

