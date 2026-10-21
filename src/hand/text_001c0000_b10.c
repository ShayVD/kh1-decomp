#include "common.h"
#include "platform/math.h"

#include "data/types/text_001c0000_b10.h"
typedef f32 Mtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad0[0x10];
    f32 x10, x14, x18;
    u8 pad1c[0x14];
    f32 x30, x34, x38;
} Obj;

/* Script VM instance (0x350 bytes). */
typedef struct {
    s32 x0;
    Obj *obj;
    u8 pad8[0xc];
    f32 x14, x18, x1c, x20;
    u8 pad24[0x3c];
    Obj *x60;
    s32 x64;
    u8 pad68[8];
    s8 *code;
    s32 n;
    s32 x78;
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[91];
    s32 x2f0;
    f32 x2f4;
    s32 ret[8];
    s32 rsp;
    u8 pad31c[0xc];
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:22;
    u8 pad32c[0x24];
} __attribute__((aligned(8))) VM;

typedef struct {
    u8 pad0[0x10];
    u16 h10[8][256];
    s32 cnt[8];
    u8 pad1030[0x3034 - 0x1030];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    s8 *x3040;
    s8 *x3044;
    s32 x3048;
    s32 *x304c;
    s32 x3050;
    s32 *x3054;
    u8 pad3058[4];
    s32 x305c;
    s32 *x3060;
    s32 x3064;
    s32 *x3068;
    u8 pad306c[4];
    u64 f3070;
    u64 f3078;
    u8 pad3080[0xc0];
    s32 x3140;
    u8 pad3144[4];
    s32 x3148;
    f32 f314c;
} Big;

/* Camera state: channels 0-3 (pos, rot, ...) with Hermite moves, plus shake. */

typedef struct { u32 b0:1, b1:1, b2:1, b3:1, rest:28; } Bits;

typedef struct {
    u8 pad[0x10];
    VM *vm;
    s32 n;
    s32 x18;
} Task;

typedef struct {
    u32 type:8, id:24;
    s32 x4;
    u8 pad8[8];
    f32 x, y, z;
    f32 ang;
} __attribute__((aligned(16))) Msg;

typedef struct { u8 pad[0xdc4]; u32 xdc4; } Save;
typedef struct { u16 t:4, s:4, b1:8; } Ent;
typedef struct { u8 b0, b1, b2; } Ent2;

extern Big D_00389C90;
extern u32 D_00389C80;
extern u8 *D_00388480[];
extern u8 *D_003C21A8[];
extern u32 D_003C39A8;
extern s8 *D_003C39AC;
extern Bits D_0037A378;
extern VM D_003C3A70[];
extern s32 D_003C54F0;
extern s32 D_002C5958;
extern u8 D_006297F8[];
extern s32 (*D_0037A198[])(VM *, s32);
extern CamS D_003C5510;
extern Vec D_003C55F0;
extern Vec D_002E2780, D_002E2790;
extern f32 D_002E27A4;
extern f32 D_002BBDFC;
extern s32 D_002BBAB0, D_002BBAB8, D_002BBAC8;
extern u8 D_003C5660[], D_003C5680[], D_003C56A0[], D_003C56C0[], D_003C56F0[], D_003C5728[], D_003C5750[], D_003C5780[], D_003C57B0[];

s32 func_001c1ce8(s8 *, s32);
s32 func_001c1cf8(s8 *, s32);
void func_001c6720(void);
void func_001c2d20(s8 *, u32 *, u8 **);
Task *func_0011f090(void *, s32, void *);
void func_001c3b10(void);
void *memset(void *, s32, u32);
s32 rand(void);
void func_001c6890(void);
void func_001e9fe8(f32 *, f32 *);
void func_00124c68(f32);
void sceVu0UnitMatrix(Mtx);
void func_00267768(Mtx, Mtx, f32);
void func_00267810(Mtx, Mtx, f32);
void func_002676c0(Mtx, Mtx, f32);
void func_00267578(Mtx, Mtx, f32 *);
void func_002672f8(f32 *, Mtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
s32 func_001c4640(Msg *);
void func_002673b8(f32 *, f32 *);
Save *func_00232cc0(s32);
Ent *func_00147778(s32);
Ent2 *func_00147840(s32);
void *func_0011ef10(s32, void *);
void func_001caa50(void);

void func_001c4198(s8 *h, s32 a1)
{
  s32 done = 0;
  VM *e;
  VM *e2;
  s32 i;
  s32 *cnt;
  s32 *o;
  s32 *o1;
  s32 n0;
  s32 n1;
  s32 j;
  s32 k;
  s8 *p;
  s8 *q;
  s32 op;
  s64 mask;
  s32 arg;
  s32 r;
  Task *t;
  s32 *src;
  D_00389C90.x3044 = D_00389C90.x3040;
  D_00389C90.x3050 = D_00389C90.x3048;
  D_00389C90.x3054 = D_00389C90.x304c;
  D_00389C90.x3064 = D_00389C90.x305c;
  D_00389C90.x3068 = D_00389C90.x3060;
  D_003C39A8 = D_00389C80;
  for (i = 0; i < D_00389C80; i++)
  {
    D_003C21A8[i] = D_00388480[i];
  }

  D_0037A378.b0 = 0;
  D_0037A378.b1 = 0;
  D_0037A378.b2 = 0;
  D_0037A378.b3 = 0;
  D_003C39AC = h;
  D_00389C90.x3148 = -1;
  D_00389C90.f314c = 1.0f;
  D_00389C90.x3140 = 0;
  func_001c6720();
  o = (s32 *) (h + 12);
  o1 = (s32 *) (h + 16);
  mask = ~8;
  n0 = ((s32 *) h)[0];
  D_00389C90.x3048 = n0;
  D_00389C90.x3040 = h;
  n1 = ((s32 *) h)[1];
  D_00389C90.x3060 = (o + n0) + 1;
  D_00389C90.x305c = n1;
  q = h + o[0];
  D_00389C90.x304c = o1;
  p = h + o[(a1 + (n1 + n0)) + 1];
  p += 12;
  e = D_003C3A70;
  cnt = &D_003C54F0;
  *cnt = *(p++);
  for (i = 0; i < (*cnt); i++, e++)
  {
    s32 m;
    e->x0 = 0;
    e->obj = 0;
    e->code = p + 4;
    e->n = *p;
    e->pc = 0;
    e->sp = -1;
    e->x78 = 0;
    e->x2f0 = 0;
    e->rsp = 7;
    for (m = 7; m >= 0; m--)
    {
      e->ret[m] = -1;
    }

    p += 4;
    e->ret[7] = e->pc;
    e->b0 = 0;
    e2 = e;
    e2->b1 = 0;
    e->b2 = 0;
    e->b3 = 0;
    e->b4 = 0;
    e->b5 = 0;
    e->b6 = 0;
    e->b7 = 0;
    e2->b8 = 0;
    e2->b9 = 0;
    k = 0;
    for (m = 0; m < e2->n; m++)
    {
      e2->lbl[m] = k;
      while (p[3] != 5)
      {
        p += 4;
        k++;
      }

      p += 4;
      k++;
    }

  }

  func_001c2d20(q, &D_00389C80, D_00388480);
  e = D_003C3A70;
  cnt = &D_003C54F0;
  for (i = 0; i < (*cnt); i++, e++)
  {
    e->pc = e->lbl[0];
    while (1)
    {
      op = func_001c1ce8(e->code, e->pc);
      arg = func_001c1cf8(e->code, e->pc);
      if (op == 5)
      {
        break;
      }
      r = D_0037A198[op](e, arg);
      if (r & 2)
      {
        e->pc++;
      }
      if (r & 8)
      {
        done = 1;

        D_002C5958 &= mask;
        D_002C5958 &= ~4;
        break;
      }
    }

    e->x78 = 1;
    e->pc = e->lbl[1];
  }

  if (done == 0)
  {
    t = func_0011f090(D_006297F8, 1, func_001c3b10);
    t->vm = D_003C3A70;
    t->n = D_003C54F0;
    t->x18 = 0;
  }
}

void func_001c6a20(void) {
    Vec rot;
    Mtx m;
    Vec v;
    Vec t;
    memset(rot, 0, 16);
    memset(v, 0, 16);
    v[3] = 1.0f;
    memset(t, 0, 16);
    t[3] = 1.0f;
    func_001e9fe8(rot, D_003C55F0);
    if (rot[0] > 1.5707964f || rot[0] < -1.5707964f) {
        if (rot[2] < 0.0f) rot[2] = rot[2] + 3.1415928f;
        else rot[2] = rot[2] - 3.1415928f;
    }
    func_00124c68(D_003C5510.f124);
/*P*/
    D_003C5510.v100[0] = 0.0f;
    D_003C5510.v100[2] = 1.0f;
    D_003C5510.v100[1] = 0.0f;
    t[2] = D_003C5510.f120;
    D_003C5510.v100[3] = 1.0f;
    D_003C5510.v110[1] = 1.0f;
    D_003C5510.v110[3] = 1.0f;
    D_003C5510.v110[0] = 0.0f;
    D_003C5510.v110[2] = 0.0f;
/*Q*/
    sceVu0UnitMatrix(m);
    func_00267768(m, m, D_003C5510.rx);
    func_00267810(m, m, D_003C5510.ry);
    func_002676c0(m, m, D_003C5510.rz);
    func_00267578(m, m, t);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002676c0(m, m, 0.0f);
    func_002672f8(v, m, v);
    sceVu0UnitMatrix(m);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002676c0(m, m, 0.0f);
    func_002672f8(D_003C5510.v100, m, D_003C5510.v100);
    v[0] = -v[0];
    v[1] = -v[1];
    v[2] = -v[2];
    sceVu0UnitMatrix(m);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002676c0(m, m, rot[2]);
    func_002672f8(D_003C5510.v110, m, D_003C5510.v110);
    v[0] += D_003C5510.pos[0];
    v[1] += D_003C5510.pos[1];
    v[2] += D_003C5510.pos[2];
    func_002675a8(D_002E2780, v);
    func_002675a8(D_002E2790, D_003C5510.pos);
    D_002E27A4 = rot[2];
}

s32 func_001c8e20(void) {
    Vec v;
    Mtx m;
    Vec rot;
    f32 x, y, z, k;
    z = x = y = 0.0f;
    func_001c6890();
    switch (D_003C5510.smode) {
    case 0:
        x = (f32)rand() / 2147483647.0f * D_003C5510.amp[0]; x -= D_003C5510.amp[0] * 0.5f;
        y = (f32)rand() / 2147483647.0f * D_003C5510.amp[1]; y -= D_003C5510.amp[1] * 0.5f;
        z = (f32)rand() / 2147483647.0f * D_003C5510.amp[2]; z -= D_003C5510.amp[2] * 0.5f;
        break;
    case 1:
        k = D_003C5510.st / D_003C5510.sdur;
        if (0.5f < k) k = (1.0f - k) * 2.0f;
        else k = k * 2.0f;
        x = (f32)rand() / 2147483647.0f * D_003C5510.amp[0]; x -= D_003C5510.amp[0] * 0.5f; x *= k;
        y = (f32)rand() / 2147483647.0f * D_003C5510.amp[1]; y -= D_003C5510.amp[1] * 0.5f; y *= k;
        z = (f32)rand() / 2147483647.0f * D_003C5510.amp[2]; z -= D_003C5510.amp[2] * 0.5f; z *= k;
        break;
    case 2:
        k = D_003C5510.st / D_003C5510.sdur;
        x = (f32)rand() / 2147483647.0f * D_003C5510.amp[0]; x -= D_003C5510.amp[0] * 0.5f; x *= k;
        y = (f32)rand() / 2147483647.0f * D_003C5510.amp[1]; y -= D_003C5510.amp[1] * 0.5f; y *= k;
        z = (f32)rand() / 2147483647.0f * D_003C5510.amp[2]; z -= D_003C5510.amp[2] * 0.5f; z *= k;
        break;
    case 3:
        k = 1.0f - D_003C5510.st / D_003C5510.sdur;
        x = (f32)rand() / 2147483647.0f * D_003C5510.amp[0]; x -= D_003C5510.amp[0] * 0.5f; x *= k;
        y = (f32)rand() / 2147483647.0f * D_003C5510.amp[1]; y -= D_003C5510.amp[1] * 0.5f; y *= k;
        z = (f32)rand() / 2147483647.0f * D_003C5510.amp[2]; z -= D_003C5510.amp[2] * 0.5f; z *= k;
        break;
    }
    func_001e9fe8(rot, D_003C5510.rot);
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
    sceVu0UnitMatrix(m);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002672f8(v, m, v);
    func_00267518(D_003C5510.pos, D_003C5510.base, v);
    func_001c6a20();
    D_003C5510.st += D_002BBDFC;
    if (D_003C5510.sdur <= D_003C5510.st) {
        D_003C5510.b8 = 0;
        func_002675a8(D_003C5510.pos, D_003C5510.base);
    }
    return 4;
}

void func_001c9308(void) {
    f32 a[4];
    f32 b[4];
    s32 i;
    f32 s, u, u2, u3, d;
    f32 *p0, *p1;
    for (i = 0; i < 3; i++) {
        a[i] = 0.0f;
        b[i] = 0.0f;
    }
    D_003C5510.t[0] += D_002BBDFC;
    p0 = D_003C5510.p0[0];
    p1 = D_003C5510.p1[0];
    switch (D_003C5510.mode[0]) {
    case 0:
    case 3:
        s = D_003C5510.dur[0];
        for (i = 0; i < 3; i++) a[i] = (p1[i] - p0[i]) / s;
        break;
    case 1:
    case 2:
        for (i = 2; i >= 0; i--) a[i] = 0.0f;
        break;
    }
    switch (D_003C5510.mode[0]) {
    case 0:
    case 2:
        s = D_003C5510.dur[0];
        for (i = 0; i < 3; i++) b[i] = (p1[i] - p0[i]) / s;
        break;
    case 1:
    case 3:
        for (i = 2; i >= 0; i--) b[i] = 0.0f;
        break;
    }
    s = 0.0f;
    if (D_003C5510.t[0] == s) {
        D_003C5510.pos[0] = p0[0];
        D_003C5510.pos[1] = p0[1];
        D_003C5510.pos[2] = p0[2];
    } else if (D_003C5510.dur[0] <= D_003C5510.t[0]) {
        D_003C5510.pos[0] = p1[0];
        D_003C5510.pos[1] = p1[1];
        D_003C5510.pos[2] = p1[2];
    } else {
        d = D_003C5510.dur[0] - s;
        u = (D_003C5510.t[0] - s) / d;
        u2 = u * u;
        u3 = u * u2;
        for (i = 0; i < 3; i++) {
            D_003C5510.pos[i] = (2.0f * u3 - 3.0f * u2 + 1.0f) * p0[i]
                + (-2.0f * u3 + 3.0f * u2) * p1[i]
                + ((u3 - 2.0f * u2 + u) * a[i] + (u3 - u2) * b[i]) * d;
        }
    }
    func_001c6a20();
    if (D_003C5510.t[0] > D_003C5510.dur[0]) D_003C5510.b4 = 0;
}

void func_001c96c0(void) {
    f32 a[4];
    f32 b[4];
    s32 i;
    f32 s, u, u2, u3, d;
    f32 *p0, *p1;
    for (i = 0; i < 3; i++) {
        a[i] = 0.0f;
        b[i] = 0.0f;
    }
    D_003C5510.t[1] += D_002BBDFC;
    p0 = D_003C5510.p0[1];
    p1 = D_003C5510.p1[1];
    s = D_003C5510.dur[1];
    switch (D_003C5510.mode[1]) {
    case 0:
    case 3:
        for (i = 0; i < 3; i++) a[i] = (p1[i] - p0[i]) / s;
        break;
    case 1:
    case 2:
        for (i = 2; i >= 0; i--) a[i] = 0.0f;
        break;
    }
    switch (D_003C5510.mode[1]) {
    case 0:
    case 2:
        s = D_003C5510.dur[1];
        for (i = 0; i < 3; i++) b[i] = (p1[i] - p0[i]) / s;
        break;
    case 1:
    case 3:
        for (i = 2; i >= 0; i--) b[i] = 0.0f;
        break;
    }
    s = 0.0f;
    if (D_003C5510.t[1] == s) {
        D_003C5510.rot[0] = p0[0];
        D_003C5510.rot[1] = p0[1];
        D_003C5510.rot[2] = p0[2];
    } else if (D_003C5510.dur[1] <= D_003C5510.t[1]) {
        D_003C5510.rot[0] = p1[0];
        D_003C5510.rot[1] = p1[1];
        D_003C5510.rot[2] = p1[2];
    } else {
        d = D_003C5510.dur[1] - s;
        u = (D_003C5510.t[1] - s) / d;
        u2 = u * u;
        u3 = u * u2;
        for (i = 0; i < 3; i++) {
            D_003C5510.rot[i] = (2.0f * u3 - 3.0f * u2 + 1.0f) * p0[i]
                + (-2.0f * u3 + 3.0f * u2) * p1[i]
                + ((u3 - 2.0f * u2 + u) * a[i] + (u3 - u2) * b[i]) * d;
        }
    }
    func_001c6a20();
    if (D_003C5510.t[1] > D_003C5510.dur[1]) D_003C5510.b5 = 0;
}

s32 func_001d2c68(VM *vm) {
    Vec v;
    Msg m;
    f32 a, t, r, s, dx, dz;
    if (D_0037A378.b0) {
        m.type = 3;
        m.id = 0;
        m.x4 = vm->x0;
        m.x = vm->stk[vm->sp - 2];
        m.y = vm->stk[vm->sp - 1];
        m.z = vm->stk[vm->sp];
        m.ang = 1.0f;
        func_001c4640(&m);
        vm->sp -= 4;
        return 6;
    }
    a = vm->stk[vm->sp - 3];
    t = D_002BBDFC;
    r = PlatSqrtf(a * t / 0.48469386f);
    r = (r + PlatSqrtf((a + (vm->obj->x14 - (f32)vm->stk[vm->sp - 1])) * t / 0.48469386f)) * 0.5f;
    dx = (f32)vm->stk[vm->sp - 2] - vm->obj->x10;
    dz = (f32)vm->stk[vm->sp] - vm->obj->x18;
    s = PlatSqrtf(dx * dx + dz * dz) / r;
    m.type = 4;
    m.id = 0;
    m.x4 = vm->x0;
    m.x = -(vm->obj->x10 - (f32)vm->stk[vm->sp - 2]);
    m.y = 0.0f;
    m.z = -(vm->obj->x18 - (f32)vm->stk[vm->sp]);
    m.ang = 1.0f;
    vm->b1 = 1;
    func_001c4640(&m);
    m.type = 12;
    m.id = 0;
    m.x4 = vm->x0;
    m.x = -(vm->obj->x10 - (f32)vm->stk[vm->sp - 2]);
    m.y = a;
    m.z = -(vm->obj->x18 - (f32)vm->stk[vm->sp]);
    m.ang = 1.0f;
    v[0] = -(vm->obj->x10 - (f32)vm->stk[vm->sp - 2]);
    v[1] = 0.0f;
    v[2] = -(vm->obj->x18 - (f32)vm->stk[vm->sp]);
    v[3] = 1.0f;
    func_002673b8(v, v);
    m.x = v[0] = v[0] * s;
    m.z = v[2] = v[2] * s;
    func_001c4640(&m);
    vm->x20 = s;
    vm->b2 = 1;
    vm->x14 = vm->stk[vm->sp - 2];
    vm->x18 = vm->stk[vm->sp - 1];
    vm->x1c = vm->stk[vm->sp];
    vm->sp -= 4;
    vm->x2f4 = r * (2.0f - D_002BBDFC + 2.0f);
    return 6;
}

/* needs make: uses rodata */
s32 func_001cb120(VM *vm) {
    s32 id = vm->stk[vm->sp];
    s32 k = vm->stk[vm->sp - 1];
    Save *sv = func_00232cc0(1);
    Ent *e = func_00147778(id);
    s32 n;
    switch (e->t) {
    case 0:
        n = D_002BBAB0 = e->b1;
        D_002BBAC8 = e->s;
        switch (func_00147840(n)->b2) {
        case 0: D_00388480[D_00389C80] = D_003C5660; break;
        case 12: D_00388480[D_00389C80] = D_003C5680; break;
        case 13: D_00388480[D_00389C80] = D_003C56A0; break;
        case 2: D_00388480[D_00389C80] = D_003C5750; break;
        case 3: D_00388480[D_00389C80] = D_003C5780; break;
        case 4: D_00388480[D_00389C80] = D_003C57B0; break;
        case 1: D_00388480[D_00389C80] = D_003C5728; break;
        }
        break;
    case 1:
        if (e->s == 11) {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_00388480[D_00389C80] = D_003C56F0;
            if (!((sv->xdc4 >> 4) & 1)) {
                sv->xdc4 |= 0x10;
                func_0011ef10(50000, func_001caa50);
            }
        } else {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_00388480[D_00389C80] = D_003C56C0;
        }
        break;
    }
    { u16 v = D_00389C80; n = D_00389C90.cnt[k]++; D_00389C90.h10[k][n] = v; }
    vm->sp -= 2;
    return 2;
}
#include "data/bss_0062_mixed.h"
#include "data/data_002B.h"
#include "data/data_003C.h"
#include "data/pieces/D_003C5510.h"
