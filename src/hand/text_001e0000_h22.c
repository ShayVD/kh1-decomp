#include "common.h"

u32 func_001ee118(void);

void func_001ee230(u32 *a, u32 *b, u32 *c, u32 *d) {
    u32 t = func_001ee118();
    *a = t / 216000U;
    t = t % 216000U;
    *b = t / 3600U;
    t = t % 3600U;
    *c = t / 60U;
    *d = t % 60U;
}

typedef struct { u8 pad[0x18]; u8 cnt; u8 a19[0x19]; u8 f32; u8 pad33[0x40 - 0x33]; u8 name[0x30]; u8 pad70[4]; } Member;
typedef struct { u8 pad[4]; Member m[10]; u8 pad2[2]; u8 party[4]; u8 pad492[0x499 - 0x492]; u8 x499[0x100]; u8 list599[0x30]; } S4BE8;
extern S4BE8 *D_00304BE8;
extern s32 D_003E3D68;
extern u16 D_003E3CD0[];
s32 func_00149440(s32, s32);
s32 func_001ee7c8(void);
void func_001efc10(s32);

void func_001ee650(s32 a) {
    if (a > 16) a = 0;
    func_001efc10(D_003E3CD0[a]);
}

s32 func_001ee7f0(s32 a) {
    s32 n = D_003E3D68;
    s32 i = 0;
    do {
        if (func_00149440(a, D_00304BE8->party[i++])) return 1;
    } while (--n);
    return 0;
}

s32 func_001ee870(s32 a, s32 i) {
    s32 n;
    if (func_001ee7c8()) {
        i = 0;
        n = D_003E3D68;
    } else {
        n = 1;
    }
    do {
        if (func_00149440(a, D_00304BE8->party[i++])) return 1;
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

s32 func_001ee768(void);
extern s32 D_003E3D20[];

s32 func_001eea00(s32 a, s32 b) {
    s32 v;
    if (a) {
        v = func_001ee768();
        if ((u32)(v - 2) < 10) {
            if (v != D_003E3D20[b]) return 0;
        }
    }
    return 1;
}

u8 *func_00147840(void);
extern s32 D_003E3D48[];

s32 func_001eea60(s32 a) {
    u32 i;
    if (a) {
        u8 k = func_00147840()[2];
        for (i = 0; i < 3; i++) {
            if (k == D_003E3D48[i]) return 1;
        }
    }
    return 0;
}

void func_00141b10(s32, s32 *);

s32 func_001eec48(s32 i, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->f32;
    m->f32 = v;
    func_00141b10(i, buf);
    m->f32 = old;
    return buf[19];
}

s32 func_001eecb0(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->a19[j];
    m->a19[j] = v;
    func_00141b10(i, buf);
    m->a19[j] = old;
    return buf[15];
}

s32 func_001eed18(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->a19[j];
    m->a19[j] = v;
    func_00141b10(i, buf);
    m->a19[j] = old;
    return buf[17];
}

s32 func_001eed80(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->a19[j];
    m->a19[j] = v;
    func_00141b10(i, buf);
    m->a19[j] = old;
    return buf[56];
}

s32 func_001eede8(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->a19[j];
    m->a19[j] = v;
    func_00141b10(i, buf);
    m->a19[j] = old;
    return buf[19];
}

s32 func_001eee50(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->a19[j];
    m->a19[j] = v;
    func_00141b10(i, buf);
    m->a19[j] = old;
    return buf[20];
}

s32 func_001eefd8(s32 a, s32 skip) {
    s32 n = 0, i, j;
    for (i = 0; i < 10; i++) {
        Member *m;
        if (i == skip) continue;
        m = &D_00304BE8->m[i];
        for (j = 0; j < m->cnt; j++) {
            if (m->a19[j] == a) n++;
        }
    }
    return n;
}

s32 func_001ef050(s32 a) {
    s32 n = 0, i, j;
    S4BE8 *d = D_00304BE8;
    for (i = 0; i < 10; i++) {
        Member *m = &d->m[i];
        if (m->f32 == a) n++;
        for (j = 0; j < m->cnt; j++) {
            if (m->a19[j] == a) n++;
        }
    }
    return n;
}

s32 func_001ef0c0(s32 a) {
    s32 i, j;
    S4BE8 *d = D_00304BE8;
    s32 n = d->x499[a];
    for (i = 0; i < 10; i++) {
        Member *m = &d->m[i];
        if (m->f32 == a) n--;
        for (j = 0; j < m->cnt; j++) {
            if (m->a19[j] == a) n--;
        }
    }
    if (n < 0) n = 0;
    return n;
}

extern s32 D_003E3CF8[];

s32 func_001ef2c0(s32 a) {
    u32 i;
    if (a) {
        s32 k = func_001ee768();
        for (i = 0; i < 10; i++) {
            if (k == D_003E3CF8[i]) return 1;
        }
    }
    return 0;
}

extern s32 D_003E3D58[];

s32 func_001ef320(void) {
    s32 i;
    u8 k = D_00304BE8->m[0].f32;
    for (i = 3; i >= 0; i--) {
        if (k == D_003E3D58[i]) return 0;
    }
    return 1;
}

s32 func_001ef3a0(s32 i) {
    s32 n;
    Member *m = &D_00304BE8->m[i];
    for (n = 0; n < 48 && m->name[n]; n++);
    return n;
}

s32 func_001ef408(void) {
    s32 n;
    for (n = 0; n < 48 && D_00304BE8->list599[n]; n++);
    return n;
}
