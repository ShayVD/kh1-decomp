/* Game-data queries (docs/modules.md "Session 36"), 0x001ee428-0x001ef950.
 *
 * Thin wrappers over the game's tables: items (func_00147840(id), ItemRec:
 * kind at +2, func_001ee768) and abilities (func_001478a0(id & 0x7f),
 * AbilRec: the AP cost at +0), with their message ids (func_001efc10 in
 * src/text/text.c); the party in the save block D_00304BE8 (the members of
 * x48e[], their weapon sub.x32, accessories sub.x19[sub.x18], items
 * sub.x22[sub.x21] and abilities sub.name[48], bit 7 = off); the stats a
 * member would have with another weapon or accessory (func_00141b10 into a
 * buffer); the munny in save block 5 (D_003F34B8->x1c, at most 99999); the
 * party count D_003E3D68 / D_003E3D6C and the stats D_003E3D70 refreshed by
 * func_001ef830; and the init list func_001ee520. */
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003F34B8.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003E3D6C.h"
#include "data/pieces/D_003E3D70.h"
#include "data/pieces/D_003E3CF8.h"
#include "data/pieces/D_003E3E50.h"

typedef W606Mem_304be8 Save1Mem;

/* func_00147840(id): an item. */
typedef struct { u16 x0; u8 kind; u8 x3; u16 x4; s16 x6; u16 x8; u16 xa; s32 xc; u16 x10; } ItemRec;
/* func_001478a0(id): an ability. */
typedef struct { u8 ap; u8 x1; u16 x2; s32 x4; s32 x8; } AbilRec;

extern u16 D_003E3CB8[];
extern u16 D_003E3CD0[];
extern s32 D_003E3D20[];
extern s32 D_003E3D48[];
extern s32 D_003E3D58[];

u32 func_00111b10();
u32 func_00111b48();
u32 func_00111b90();
u32 func_00111be8();
s32 func_00122ff8(void *);
void *func_0013daf8(s32);
void func_00141b10(s32, void *);
void func_00147808(u16);
ItemRec *func_00147840(s32);
AbilRec *func_001478a0(s32);
s32 func_00149440(s32, s32);
void *func_001496c8();
s32 func_001ba1e8(); /* u16, extended by the callee */
s32 func_001ba208();
s32 func_001ba3d8();
s32 func_001ba3f0(s32);
f32 func_001edc50(void *);
f32 func_001edcd8(f32);
void func_001ef948(void);
void func_001efaa8(void);
u8 *func_001efc10(s32);
void func_001f2eb8();
void func_0020d748();
void func_00216180(void);
void func_00219128(void);
void func_0021dbb8();
void func_0022bd20();
void func_0022d138();
void func_0022d728();
void func_0022db90();
void func_0022dfd0();
void func_0022e458();
void func_0022ebe8();
void func_0022ebf0();
void func_002319c0();
void func_00232790();
void func_00232ac8();
void *func_00232cc0(s32);
void func_00232de0(void);
void func_00233610();
void func_00233a80();
void *memset(void *, s32, u32);

u8 *func_001ee698(s32);
s32 func_001ee6d0(s32);
u8 func_001ee768(s32);
s32 func_001ee7c8(s32);
u8 func_001ef5c0(s32);

u32 func_001ee428(void) {
    return func_00111b10();
}

u32 func_001ee440(u32 a) {
    return func_00111b48(a);
}

u32 func_001ee458(u32 a) {
    return func_00111b90(a);
}

u32 func_001ee470(u32 a) {
    return func_00111be8(a);
}

s32 func_001ee488(u32 arg0) {
    s32 temp_v1;
    s32 var_a1;
    s32 var_lo;
    u32 var_a0;

    var_a0 = arg0;
    var_lo = 0;
    var_a1 = 1;
    do {
        temp_v1 = var_a0 & 0xF;
        var_a0 = var_a0 >> 4;
        var_lo += temp_v1 * var_a1;
        var_a1 *= 0xA;
    } while (var_a0 != 0);
    return var_lo;
}

void func_001ee4b8(void) {
    D_003F34B8 = (S34B8_3f34b8 *)func_00232cc0(5);
}

void func_001ee4e8(void) {
    func_00232de0();
    func_00219128();
    D_003F34B8->x1c = 0;
    func_00216180();
    func_0021dbb8();
}

void func_001ee520(void) {
    func_00233610();
    func_00233a80();
    func_001efaa8();
    func_001f2eb8();
    func_001ef948();
    func_0020d748();
    func_0022bd20();
    func_0022d138();
    func_0022d728();
    func_0022db90();
    func_0022dfd0();
    func_0022e458();
    func_0022ebe8();
    func_0022ebf0();
    func_002319c0();
    func_00232790();
    func_00232ac8();
}

void func_001ee5b8(void) {
    s32 sp[4];
    memset(sp, 0, 0x10);
    func_001edc50(sp);
    func_001edcd8(0.0f);
}

u8 *func_001ee5f0(s32 arg0) {
    return func_001efc10(D_003E3CB8[arg0]);
}

u8 *func_001ee618(s32 arg0) {
    return func_001efc10(D_003E3CB8[D_00304BE8->x48e[arg0]]);
}

void func_001ee650(s32 a) {
    if (a > 16) a = 0;
    func_001efc10(D_003E3CD0[a]);
}

void func_001ee680(s32 id) {
    func_00147840(id);
}

u8 *func_001ee698(s32 arg0) {
    if (arg0 != 0) {
        func_00147808(func_00147840(arg0)->x0);
        return;
    }
    return func_001efc10(0x97);
}

s32 func_001ee6d0(s32 arg0) {
    if ((u32) (arg0 - 1) < 0xFFU) {
        return func_00147840(arg0)->xc;
    }
    return 0;
}

u16 func_001ee708(s32 id) {
    return func_00147840(id)->x8;
}

u16 func_001ee728(s32 id) {
    return func_00147840(id)->xa;
}

s16 func_001ee748(s32 id) {
    return func_00147840(id)->x6;
}

u8 func_001ee768(s32 id) {
    return func_00147840(id)->kind;
}

u8 func_001ee788(s32 id) {
    return func_00147840(id)->x3;
}

u16 func_001ee7a8(s32 id) {
    return func_00147840(id)->x10;
}

s32 func_001ee7c8(s32 id) {
    return func_00147840(id)->x4 & 1;
}

s32 func_001ee7f0(s32 a) {
    s32 n = D_003E3D68;
    s32 i = 0;
    do {
        if (func_00149440(a, D_00304BE8->x48e[i++])) return 1;
    } while (--n);
    return 0;
}

s32 func_001ee870(s32 a, s32 i) {
    s32 n;
    if (func_001ee7c8(a)) {
        i = 0;
        n = D_003E3D68;
    } else {
        n = 1;
    }
    do {
        if (func_00149440(a, D_00304BE8->x48e[i++])) return 1;
    } while (--n);
    return 0;
}

s32 func_001ee900(s32 a) {
    s32 v = func_00149440(a, 0);
    s32 i;
    for (i = 1; i < 7; i++) {
        if ((v >> i) & 1) return i;
    }
    return -1;
}

s32 func_001ee958(s32 a, s32 b) {
    s32 v = func_00149440(a, b);
    s32 i;
    if (v & 1) {
        for (i = 1; i < 7; i++) {
            if ((v >> i) & 1) return i;
        }
    }
    return -1;
}

s32 func_001ee9b8(s32 id) {
    return func_001ee768(id) != 0xD;
}

s32 func_001ee9e0(s32 id) {
    return func_001ee768(id) == 0;
}

s32 func_001eea00(s32 a, s32 b) {
    s32 v;
    if (a) {
        v = func_001ee768(a);
        if ((u32)(v - 2) < 10) {
            if (v != D_003E3D20[b]) return 0;
        }
    }
    return 1;
}

s32 func_001eea60(s32 a) {
    u32 i;
    if (a) {
        u8 k = func_00147840(a)->kind;
        for (i = 0; i < 3; i++) {
            if (k == D_003E3D48[i]) return 1;
        }
    }
    return 0;
}

s32 func_001eeac0(s32 arg0) {
    s32 var_v0;

    if (!((arg0 == 0) || (var_v0 = 1, (func_00147840(arg0)->kind != 0)))) {
        return var_v0;
    }
    var_v0 = 0;
    return var_v0;
}

s32 func_001eeaf0(s32 i) {
    return func_001ba208(i);
}

s32 func_001eeb08(s32 i) {
    return func_001ba1e8(i);
}

s32 func_001eeb20(void) {
  s32 temp_a0;
  s32 temp_v0;
  s32 var_s0;
  s32 var_s2;
  s32 var_v0;
  var_s0 = 0;
  var_s2 = 0;
  temp_v0 = func_001ba3d8();
  var_v0 = 0;
  if (temp_v0 > 0)
  {
    do
    {
      temp_a0 = var_s0;
      var_s0 += 1;
      var_s2 += func_001ba3f0(temp_a0);
    }
    while (var_s0 < temp_v0);
    var_v0 = var_s2;
  }
  return var_s2;
}

u8 *func_001eeb88(s32 arg0) {
    if (arg0 != 0) {
        func_001ee698(arg0);
        return;
    }
    return func_001efc10(0xA7);
}

u8 *func_001eebb0(s32 arg0) {
    if (arg0 != 0) {
        func_001ee698(arg0);
        return;
    }
    return func_001efc10(0xA7);
}

u8 *func_001eebd8(s32 arg0) {
    if (arg0 != 0) {
        func_001ee6d0(arg0);
        return;
    }
    return func_001efc10(0xA8);
}

u8 *func_001eec00(s32 arg0) {
    if (arg0 != 0) {
        func_001ee6d0(arg0);
        return;
    }
    return func_001efc10(0xA8);
}

s8 func_001eec28(s32 a, s32 b) {
    return ((s8 *)func_001496c8(a, b))[0x30];
}

s32 func_001eec48(s32 i, u8 v) {
    s32 buf[60];
    Save1Mem *m = &D_00304BE8->m[i];
    u8 old = m->sub.x32;
    m->sub.x32 = v;
    func_00141b10(i, buf);
    m->sub.x32 = old;
    return buf[19];
}

s32 func_001eecb0(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Save1Mem *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[15];
}

s32 func_001eed18(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Save1Mem *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[17];
}

s32 func_001eed80(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Save1Mem *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[56];
}

s32 func_001eede8(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Save1Mem *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[19];
}

s32 func_001eee50(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Save1Mem *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[20];
}

s32 func_001eeeb8(s32 id) {
    s32 n = 0, i;
    u8 c;
    Save1Mem *e;
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c == 0xff) break;
        e = &D_00304BE8->m[c];
        if (e->sub.x32 == id) n++;
    }
    return n;
}

s32 func_001eef38(s32 id) {
    s32 n = 0, i, j;
    u8 c;
    Save1Mem *e;
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c == 0xff) break;
        e = &D_00304BE8->m[c];
        for (j = 0; j < e->sub.x18; j++) {
            if (e->sub.x19[j] == id) n++;
        }
    }
    return n;
}

s32 func_001eefd8(s32 a, s32 skip) {
    s32 n = 0, i, j;
    for (i = 0; i < 10; i++) {
        Save1Mem *m;
        if (i == skip) continue;
        m = &D_00304BE8->m[i];
        for (j = 0; j < m->sub.x18; j++) {
            if (m->sub.x19[j] == a) n++;
        }
    }
    return n;
}

s32 func_001ef050(s32 a) {
    s32 n = 0, i, j;
    Save_304be8 *d = D_00304BE8;
    for (i = 0; i < 10; i++) {
        Save1Mem *m = &d->m[i];
        if (m->sub.x32 == a) n++;
        for (j = 0; j < m->sub.x18; j++) {
            if (m->sub.x19[j] == a) n++;
        }
    }
    return n;
}

s32 func_001ef0c0(s32 a) {
    s32 i, j;
    Save_304be8 *d = D_00304BE8;
    s32 n = d->items[a];
    for (i = 0; i < 10; i++) {
        Save1Mem *m = &d->m[i];
        if (m->sub.x32 == a) n--;
        for (j = 0; j < m->sub.x18; j++) {
            if (m->sub.x19[j] == a) n--;
        }
    }
    if (n < 0) n = 0;
    return n;
}

s32 func_001ef140(s32 i, s32 id) {
    s32 c = 0;
    Save1Mem *m = &D_00304BE8->m[i];
    s32 t = func_001ee768(id);
    s32 j, n;
    if (t == 0) {
        n = m->sub.x21;
        for (j = 0; j < n; j++) {
            if (m->sub.x22[j] == id) c++;
        }
    } else if (t == 1) {
        n = m->sub.x18;
        for (j = 0; j < n; j++) {
            if (m->sub.x19[j] == id) c++;
        }
    } else if (t >= 2 && t < 12) {
        c = m->sub.x32 == id;
    }
    return c;
}

s32 func_001ef250(s32 id) {
    return func_001ee768(id) - 2;
}

s32 func_001ef270(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        return func_001ee768(arg0) == D_003E3CF8[arg1];
    }
    return 0;
}

s32 func_001ef2c0(s32 a) {
    u32 i;
    if (a) {
        s32 k = func_001ee768(a);
        for (i = 0; i < 10; i++) {
            if (k == D_003E3CF8[i]) return 1;
        }
    }
    return 0;
}

s32 func_001ef320(void) {
    s32 i;
    u8 k = D_00304BE8->m[0].sub.x32;
    for (i = 3; i >= 0; i--) {
        if (k == D_003E3D58[i]) return 0;
    }
    return 1;
}

s32 func_001ef370(s32 arg0) {
    if (arg0 != 0) {
        return func_001ee768(arg0) == 1;
    }
    return 0;
}

s32 func_001ef3a0(s32 i) {
    s32 n;
    Save1Mem *m = &D_00304BE8->m[i];
    for (n = 0; n < 48 && m->sub.name[n]; n++);
    return n;
}

s32 func_001ef408(void) {
    s32 n;
    for (n = 0; n < 48 && D_00304BE8->list599[n]; n++);
    return n;
}

s32 func_001ef450(s32 i, s32 a) {
    s32 n = 0, k;
    Save1Mem *m = &D_00304BE8->m[i];
    u8 c;
    for (k = 0; k < 48 && (c = m->sub.name[k]); k++) {
        if ((c & ~0x80) == a) n++;
    }
    return n;
}

s32 func_001ef4c0(s32 a) {
    s32 n = 0, k;
    u8 c;
    for (k = 0; k < 48 && (c = D_00304BE8->list599[k]); k++) {
        if ((c & ~0x80) == a) n++;
    }
    return n;
}

void func_001ef528(s32 id) {
    func_001478a0(id);
}

s32 func_001ef540(s32 arg0) {
    if (arg0 != 0) {
        return func_001478a0(arg0 & ~0x80)->x4;
    }
    return (s32)func_001efc10(0xB4);
}

s32 func_001ef580(s32 arg0) {
    if (arg0 != 0) {
        return func_001478a0(arg0 & ~0x80)->x8;
    }
    return (s32)func_001efc10(0xB4);
}

u8 func_001ef5c0(s32 arg0) {
    if (arg0 != 0) {
        return func_001478a0(arg0 & ~0x80)->ap;
    }
    return 0U;
}

u16 func_001ef5f8(s32 arg0) {
    if (arg0 != 0) {
        return func_001478a0(arg0 & ~0x80)->x2;
    }
    return 0U;
}

void func_001ef630(s32 arg0, s32 arg1) {
    func_001efc10((arg0 * 3) + arg1 + 0xD4);
}

s32 func_001ef658(s32 arg0) {
    return D_003E3E50[arg0].x0;
}

s32 func_001ef680(s32 i) {
    s32 n = 0, k = 0;
    u8 *p = D_00304BE8->m[i].sub.name;
    u8 c;
loop:
    if (k >= 48) goto end;
    k++;
    c = *p++;
    if (!c) goto end;
    if (c & 0x80) goto loop;
    n += func_001ef5c0(c);
    goto loop;
end:
    return n;
}

s32 func_001ef720(s32 i) {
    S3D70_3E3D70 *e = &D_003E3D70.s3D70[i];
    s32 r = e->xe0 - func_001ef680(i);
    if (r < 0) r = 0;
    return r;
}

void func_001ef778(u32 arg0) {
    D_003F34B8->x1c = (arg0 <= 99999U) ? arg0 : 99999U;
}

s32 func_001ef7a0(void) {
    return D_003F34B8->x1c;
}

void func_001ef7b0(s32 a) {
    S34B8_3f34b8 *p = D_003F34B8;
    p->x1c += a;
    if (p->x1c < 0) p->x1c = 0;
    else if ((u32)p->x1c > 99999) p->x1c = 99999;
}

void func_001ef7f0(s32 a) {
    S34B8_3f34b8 *p = D_003F34B8;
    p->x1c -= a;
    if (p->x1c < 0) p->x1c = 0;
    else if ((u32)p->x1c > 99999) p->x1c = 99999;
}

void func_001ef830(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (D_00304BE8->x48e[i] == 0xff) break;
    }
    D_003E3D6C = i;
    D_003E3D68 = i;
    if (D_00304BE8->x48e[3] != 0xff) D_003E3D68 = i + 1;
    for (i = 0; i < 10; i++) func_00141b10(i, &D_003E3D70.e228[i]);
}

void *func_001ef8f8(s32 i) {
    void *p = func_0013daf8(D_00304BE8->x48e[i]);
    if (p && func_00122ff8(p)) goto ok;
    return 0;
ok:
    return p;
}

void func_001ef948(void) {
}

