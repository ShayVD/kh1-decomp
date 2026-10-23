/* Message windows, 0x001ca9e8-0x001cce38 (include/msgwin/msgwin.h,
 * docs/modules.md "Session 32"), in address order:
 *
 * - func_001ca9e8 .. func_001caa50: the closing chain of the extra window
 *   D_0062A130 (func_001cb120 starts it with func_0011ef10);
 * - func_001caae0 / func_001cab48: reset the window state and the 8 templates
 *   D_006298F0 (func_001cab48 runs at script load);
 * - the callbacks the window code calls when a window closes (func_001cae20),
 *   shows the next message of its template (func_001cafe8, func_001cbab0,
 *   func_001cbd80, func_001cbea0) or answers a choice (func_001cac60);
 * - the script functions (entries of func_001dcad0's table D_003D9FE0):
 *   queue messages for a template (func_001cb120, func_001cb3c0,
 *   func_001cb738, func_001cb7d0, func_001cb960), open / close a template
 *   (func_001cbbd0, func_001cbfc0, func_001cae78), set its fields
 *   (func_001cc170 .. func_001cc420, func_001cc548, func_001ccbf8,
 *   func_001cc640) and wait for the windows (func_001cae00, func_001cc470,
 *   func_001cc508).
 *
 * They share VmMgr's window fields (wst / tst / xc, tbl / cnt / ids) and the
 * data D_003C5640-D_003C5890, which sits between the camera's D_003C5510
 * and opcode 1's D_003C5898 (src/vm/vm_calc.c), as the code does. */
#include "common.h"
#include "msgwin/msgwin.h"
#include "vm/vm_mgr.h"
#include "data/types/vm_rec.h"
#include "data/pieces/D_00388480.h"
#include "data/pieces/D_00389C80.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002E26A0.h"
#include "data/data_002B.h"
#include "data/data_003C.h"

extern VmMgr D_00389C90;
extern s32 D_0038CD04;              /* D_00389C90.f3070's high word */
extern volatile s32 D_00629924;     /* D_006298F0[0].v30[1] */
/* h6 / h8 of the templates through their own labels, as h14 matched them
 * (the float build keeps D_006298F8 because of this reference). */
typedef struct { u16 h; u8 pad[174]; } MsgWinH;
extern MsgWinH D_006298F6[], D_006298F8[];

/* The choice callback's record (func_001cac98 passes it to func_0010f558). */
typedef struct { s32 a; s32 b; void (*fn)(); s32 d; } MsgCb;
MsgCb D_0062A1E0 ALIGNED(16);
/* func_001cb7d0's number text. */
char D_0062A1F0[0x20] ALIGNED(16);

typedef struct { u8 pad[0xdc4]; u32 xdc4; } MsgSave;
typedef struct { u16 t:4, s:4, b1:8; } MsgEnt;
typedef struct { u8 b0, b1, b2; } MsgEnt2;
/* func_001cb440's view of the VM from +4 (obj, then sp and stk). */
typedef struct { void *obj; u8 pad4[0x178]; s32 sp; s32 stk[105]; } MsgVmSub;

void func_0010bd90(MsgWin *, void *);
void func_0010bdd0(MsgWin *, void *);
void func_0010ef70(MsgWin *, void *, void *);
void func_0010e3f0(void *);
void func_0010f558(void *, void *, s32);
s32 func_0010f098(void *);
void *func_0011ef10(s32, void *);
MsgSave *func_00232cc0(s32);
MsgEnt *func_00147778(s32);
MsgEnt2 *func_00147840(s32);
s32 func_0017e428(void *, void *);
void func_0017e768(void);

void func_001cae20(s32 id, MsgWin *t);
void func_001cafe8(s32 id, MsgWin *t);
void func_001cbab0(s32 id, MsgWin *t);
void func_001cbd80(s32 id, MsgWin *t);
void func_001cbea0(s32 id, MsgWin *t);

void func_001ca9e8(void) {
    D_00389C90.wst[0] = 0;
}

void func_001ca9f8(void) {
    func_0010bd90(&D_0062A130, &func_001ca9e8);
}

void func_001caa20(void) {
    func_0010ef70(&D_0062A130, &D_003C5808, &func_001ca9f8);
}

s32 func_001caa50(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00389C90.wst[i] != 0) break;
    }
    if (i < 4) return 0;
    func_0010bdd0(&D_0062A130, func_001caa20);
    D_00389C90.ids[0] = 0;
    D_00389C90.wst[0] = 2;
    return 4;
}

void func_001caae0(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        D_00389C90.wst[i] = 0;
        D_00389C90.cnt[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        D_00389C90.tst[i] = 0;
        D_00389C90.xc[i] = 0;
    }
}

void func_001cab48(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        D_00389C90.wst[i] = 0;
        D_00389C90.tst[i] = 0;
        D_00389C90.xc[i] = 0;
        D_00389C90.cnt[i] = 0;
        D_006298F0[i].v30[0] = -1.0f;
        D_006298F0[i].v30[1] = 30.0f;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].v40[1] = 3.0f;
        D_006298F0[i].h4 = 2;
        D_006298F0[i].hc = 2;
        D_006298F0[i].he = 2;
        D_006298F0[i].h6 = 0;
        D_006298F0[i].h8 = 0;
        D_006298F0[i].f1c = 45.0f;
        D_006298F0[i].x0 = -1;
        D_006298F0[i].b90 = 0;
        D_006298F0[i].f94 = 1.0f;
    }
    D_0062A130.v30[0] = 0.0f;
    D_0062A130.v30[1] = 0.0f;
    D_0062A130.v40[0] = 12.0f;
    D_0062A130.v40[1] = 3.0f;
    D_0062A130.h4 = 1;
    D_0062A130.hc = 1;
    D_0062A130.he = 1;
    D_0062A130.h6 = 0;
    D_0062A130.h8 = 0;
    D_0062A130.f1c = 45.0f;
    D_0062A130.x0 = -1;
    D_0062A130.b90 = 0;
    D_0062A130.f94 = 1.0f;
}

void func_001cac60(s32 x) {
    D_00389C90.x3140 = x;
    D_00389C90.f3070.x &= ~(1ULL << 32);
    *D_00389C90.x3144 = x;
}

s32 func_001cac98(VmRec *vm) {
    s32 i;
    s32 v = vm->stk[32];
    for (i = 0; i < 4; i++) {
        if (D_00389C90.wst[i] && D_00389C90.ids[i] == vm->stk[vm->sp - 3]) break;
    }
    if (i >= 4) return 2;
    {
        D_0062A1E0.a = vm->stk[vm->sp - 2];
        D_0062A1E0.fn = func_001cac60;
        D_0062A1E0.b = vm->stk[vm->sp - 1];
        if (v >= 256) { v -= 2304; D_00389C90.x3144 = &D_00389C90.a1034[v]; }
        func_0010f558(&D_0062A1E0, &D_00629E70[i], D_0062A1E0.a);
        D_00389C90.f3070.x |= 0x100000000ULL;
        vm->sp -= 4;
    }
    return 2;
}

s32 func_001cae00(void) {
    return (D_0038CD04 & 1) ? 4 : 2;
}

void func_001cae20(s32 id, MsgWin *e) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (&D_00629E70[i] == e) {
            s32 k = D_00389C90.ids[i];
            D_00389C90.wst[i] = 0;
            D_00389C90.tst[k] = 0;
            D_00389C90.cnt[k] = 0;
        }
    }
}

s32 func_001cae78(VmRec *vm) {
    s32 v = vm->stk[vm->sp];
    s32 i;
    for (i = 0; i < 4; i++) {
        if (v == D_00389C90.ids[i]) break;
    }
    if (i < 4 && D_00389C90.wst[i] != 0) {
        func_0010bd90(&D_00629E70[i], func_001cae20);
        D_00389C90.wst[i] = 3;
    }
    vm->sp--;
    return 2;
}

void func_001caf58(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00389C90.wst[i]) {
            func_0010bd90(&D_00629E70[i], func_001cae20);
            D_00389C90.wst[i] = 3;
        }
    }
}

void func_001cafe8(s32 id, MsgWin *t) {
    s32 i;
    D_003C5890 = id;
    for (i = 0; i < 4; i++) {
        MsgWin *o = &D_00629E70[i];
        if (o == t) {
            s32 k = D_00389C90.ids[i];
            if (D_00389C90.cnt[k] == id) {
                func_0010bd90(o, func_001cae20);
            } else {
                D_00389C90.wst[i] = 2;
                D_00389C90.tst[k] = 2;
                func_0010e3f0(D_00629E70[i].f80);
                func_0010ef70(o, (void *)((s32 *)&D_00388480)[D_00389C90.tbl[k][id]], func_001cafe8);
            }
        }
    }
}

s32 func_001cb120(VmRec *vm) {
    s32 id = vm->stk[vm->sp];
    s32 k = vm->stk[vm->sp - 1];
    MsgSave *sv = func_00232cc0(1);
    MsgEnt *e = func_00147778(id);
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
    { u16 v = D_00389C80; n = D_00389C90.cnt[k]++; D_00389C90.tbl[k][n] = v; }
    vm->sp -= 2;
    return 2;
}

s32 func_001cb3c0(VmRec *vm) {
    s32 n, i, k;
    u16 h;
    VmMgr *b;
    b = &D_00389C90;
    n = vm->stk[vm->sp];
    i = (*(union { s32 i; u16 h; }(*))&D_00389C80).i;
    h = (*(union { s32 i; u16 h; }(*))&D_00389C80).h;
    D_00388480[i] = D_003C57E0;
    k = b->cnt[n];
    b->cnt[n] = k + 1;
    ((u16 *)b)[8 + n * 256 + k] = h;
    vm->sp--;
    return 2;
}

s32 func_001cb440(VmRec *vm) {
    MsgVmSub *s = (MsgVmSub *)&vm->obj;
    s32 y = s->stk[vm->sp];
    s32 k = s->stk[vm->sp - 3];
    s32 x = s->stk[vm->sp - 1];
    MsgEnt *e = func_00147778(s->stk[vm->sp - 2]);
    s32 n;
    switch (e->t) {
    case 0:
        n = D_002BBAB0 = e->b1;
        D_002BBAC8 = e->s;
        if ((u32)(n - 1) < 16) D_006298F0[k].v40[0] = func_0010f098(D_003C5660);
        else if ((u32)(n - 142) < 16) D_006298F0[k].v40[0] = func_0010f098(D_003C5680);
        else if ((u32)(n - 192) < 64) D_006298F0[k].v40[0] = func_0010f098(D_003C56A0);
        else if ((u32)(n - 81) < 22) D_006298F0[k].v40[0] = func_0010f098(D_003C5750);
        else if ((u32)(n - 103) < 16) D_006298F0[k].v40[0] = func_0010f098(D_003C5780);
        else if ((u32)(n - 119) < 16) D_006298F0[k].v40[0] = func_0010f098(D_003C57B0);
        else if ((u32)(n - 17) < 64) D_006298F0[k].v40[0] = func_0010f098(D_003C5728);
        break;
    case 1:
        if (e->s == 11) {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_006298F0[k].v40[0] = func_0010f098(D_003C56F0);
        } else {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_006298F0[k].v40[0] = func_0010f098(D_003C56C0);
        }
        break;
    }
    { f32 a = D_006298F0[k].v40[0];
    vm->sp -= 4;
    D_006298F0[k].v30[0] = x + a * 12.0f;
    D_006298F0[k].v30[1] = y + D_006298F0[k].v40[1] * 12.0f; }

    return 2;
}

s32 func_001cb738(VmRec *vm) {
    s32 idx = vm->stk[vm->sp - 1];
    s32 val = vm->stk[vm->sp];
    vm->sp -= 2;
    D_002BBAB0 = val;
    ((char **)&D_00388480)[D_00389C80] = D_003C5640;
    D_00389C90.tbl[idx][D_00389C90.cnt[idx]++] = *(u16 *)&D_00389C80;
    D_00389C80++;
    return 2;
}

s32 func_001cb7d0(VmRec *vm) {
    s32 val = vm->stk[vm->sp];
    s32 idx = vm->stk[vm->sp - 1];
    s32 n, i, j, d, q;
    vm->sp -= 2;
    n = 1;
    for (d = val / 10; d > 0; d /= 10) n++;
    for (i = 0; i < n; i++) {
        d = 1;
        for (j = 0; j < n - 1 - i; j++) d *= 10;
        q = val / d;
        D_0062A1F0[i] = q + 33;
        val -= q * d;
    }
    for (j = 0; (u32)j < 12; j++) D_0062A1F0[i++] = D_003C5650[j];
    ((char **)&D_00388480)[D_00389C80] = D_0062A1F0;
    D_00389C90.tbl[idx][D_00389C90.cnt[idx]++] = *(u16 *)&D_00389C80;
    D_00389C80++;
    return 2;
}

s32 func_001cb960(VmRec *vm) {
    s32 idx, v, i;
    if (D_0037A378 & 1) { vm->sp -= 2; return 2; }
    idx = vm->stk[vm->sp - 1];
    v = vm->stk[vm->sp];
    vm->sp -= 2;
    D_00389C90.tbl[idx][D_00389C90.cnt[idx]++] = v;
    for (i = 0; i < 4; i++) if (idx == D_00389C90.ids[i]) break;
    if (i < 4) {
        if (D_00389C90.wst[i] == 4) {
            D_00389C90.wst[i] = 2;
            D_00389C90.tst[idx] = 2;
            func_0010ef70(&D_00629E70[i], ((char **)&D_00388480)[v], func_001cbd80);
        }
    }
    return 2;
}

void func_001cbab0(s32 id, MsgWin *t) {
    s32 i;
    D_003C5890 = 0;
    for (i = 0; i < 4; i++) {
        MsgWin *o = &D_00629E70[i];
        if (o == t) {
            s32 k = D_00389C90.ids[i];
            if (D_00389C90.cnt[k] == 0) {
                func_0010bd90(o, func_001cae20);
            } else {
                D_00389C90.wst[i] = 2;
                D_00389C90.tst[k] = 2;
                func_0010ef70(o, (void *)((s32 *)&D_00388480)[D_00389C90.tbl[k][id]], func_001cafe8);
            }
        }
    }
}

s32 func_001cbbd0(VmRec *vm) {
    s32 idx, i;
    if (D_0037A378 & 1) { vm->sp--; return 2; }
    idx = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) if (D_00389C90.wst[i] == 0) break;
    if (i >= 4 || D_00389C90.tst[idx] != 0) return 4;
    vm->sp--;
    D_00629E70[i] = D_006298F0[idx];
    D_00389C90.ids[i] = idx;
    func_0010bdd0(&D_00629E70[i], func_001cbab0);
    D_00389C90.wst[i] = 1;
    D_00389C90.tst[idx] = 1;
    return 2;
}

void func_001cbd80(s32 id, MsgWin *t) {
    s32 i;
    D_003C5890 = id;
    for (i = 0; i < 4; i++) {
        MsgWin *o = &D_00629E70[i];
        if (o == t) {
            s32 k = D_00389C90.ids[i];
            if (D_00389C90.cnt[k] == id) {
                D_00389C90.wst[i] = 4;
                D_00389C90.tst[k] = 4;
            } else {
                D_00389C90.wst[i] = 2;
                D_00389C90.tst[k] = 2;
                func_0010ef70(o, (void *)((s32 *)&D_00388480)[D_00389C90.tbl[k][id]], func_001cbd80);
            }
        }
    }
}

void func_001cbea0(s32 id, MsgWin *t) {
    s32 i;
    D_003C5890 = 0;
    for (i = 0; i < 4; i++) {
        MsgWin *o = &D_00629E70[i];
        if (o == t) {
            s32 k = D_00389C90.ids[i];
            if (D_00389C90.cnt[k] == 0) {
                D_00389C90.wst[i] = 4;
                D_00389C90.tst[k] = 4;
            } else {
                D_00389C90.wst[i] = 2;
                D_00389C90.tst[k] = 2;
                func_0010ef70(o, (void *)((s32 *)&D_00388480)[D_00389C90.tbl[k][id]], func_001cbd80);
            }
        }
    }
}

s32 func_001cbfc0(VmRec *vm) {
    s32 idx, i;
    if (D_0037A378 & 1) { vm->sp--; return 2; }
    idx = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) if (D_00389C90.wst[i] == 0) break;
    if (i >= 4 || D_00389C90.tst[idx] != 0) return 4;
    vm->sp--;
    D_00629E70[i] = D_006298F0[idx];
    D_00389C90.ids[i] = idx;
    func_0010bdd0(&D_00629E70[i], func_001cbea0);
    D_00389C90.wst[i] = 1;
    D_00389C90.tst[idx] = 1;
    return 2;
}

s32 func_001cc170(VmRec *v) {
    s32 k = v->stk[v->sp - 1];
    u16 val = v->stk[v->sp];
    v->sp -= 2;
    D_006298F6[k].h = val;
    return 2;
}

s32 func_001cc1c0(VmRec *v) {
    s32 k = v->stk[v->sp - 1];
    u16 val = v->stk[v->sp];
    v->sp -= 2;
    D_006298F8[k].h = val;
    return 2;
}

s32 func_001cc210(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    f32 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].f1c = v;
    return 2;
}

s32 func_001cc260(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 2];
    f32 a = vm->stk[sp - 1];
    f32 b = vm->stk[sp];
    vm->sp = sp - 3;
    D_006298F0[i].v30[0] = a;
    D_006298F0[i].v30[1] = b;
    return 2;
}

s32 func_001cc2c8(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 2];
    f32 a = vm->stk[sp - 1];
    f32 b = vm->stk[sp];
    vm->sp = sp - 3;
    D_006298F0[i].v40[0] = a;
    D_006298F0[i].v40[1] = b;
    return 2;
}

s32 func_001cc330(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    u16 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].h4 = v;
    return 2;
}

s32 func_001cc380(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    u16 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].hc = v;
    return 2;
}

s32 func_001cc3d0(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    u16 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].he = v;
    return 2;
}

s32 func_001cc420(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    f32 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].f94 = v;
    return 2;
}

s32 func_001cc470(VmRec *vm) {
    s32 i;
    if (D_0037A378 & 1) return 2;
    for (i = 0; i < 4; i++) {
        if (D_00389C90.wst[i] && D_00389C90.ids[i] != 7) break;
    }
    if (i < 4) {
        if (!((s32)(vm->fl.x >> 4) & 1)) return 4;
    }
    return 2;
}

s32 func_001cc508(VmRec *vm) {
    s32 sp = vm->sp;
    u8 c = D_00389C90.tst[vm->stk[sp]];
    if (c != 0 && c != 4) return 4;
    vm->sp = sp - 1;
    return 2;
}

s32 func_001cc548(VmRec *vm) {
    s32 c = vm->stk[vm->sp - 2];
    s32 x = vm->stk[vm->sp - 1];
    s32 y = vm->stk[vm->sp];
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00389C90.wst[i] == 2 && c == D_00389C90.ids[i]) break;
    }
    if (i < 4) {
        MsgWin *o = &D_00629E70[i];
        o->v30[0] = x;
        D_00629E70[i].v30[1] = y;
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001cc628(VmRec *vm) {
    vm->sp = vm->sp - 1;
    return 2;
}

s32 func_001cc640(VmRec *vm) {
    if (vm->obj == 0) {
        vm->sp -= 2;
        return 2;
    }
    switch (func_0017e428((u8 *)D_002E26A0[0] + 16, (u8 *)vm->obj + 16)) {
    case 0: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 315.0f;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[j].h8 = 3;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 135.0f;
        D_006298F0[i].h8 = 13;
        break;
    }
    case 1: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].v30[1] = -120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 225.0f;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = 120.0f;
        D_006298F0[j].h8 = 11;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 45.0f;
        D_006298F0[i].h8 = 1;
        break;
    }
    case 2: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = -100.0f;
        D_006298F0[j].v30[1] = -120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 135.0f;
        D_006298F0[i].v30[0] = 100.0f;
        D_006298F0[i].v30[1] = 120.0f;
        D_006298F0[j].h8 = 13;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 315.0f;
        D_006298F0[i].h8 = 3;
        break;
    }
    case 3: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = -100.0f;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 45.0f;
        D_006298F0[i].v30[0] = 100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[j].h8 = 1;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 225.0f;
        D_006298F0[i].h8 = 11;
        break;
    }
    case 4: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 315.0f;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[j].h8 = 3;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 135.0f;
        D_006298F0[i].h8 = 13;
        func_0017e768();
        break;
    }
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001ccbd8(void) {
    func_0017e768();
    return 2;
}

s32 func_001ccbf8(VmRec *vm) {
    s32 n = vm->stk[vm->sp - 3];
    s32 t = vm->stk[vm->sp - 2];
    s32 x = vm->stk[vm->sp - 1];
    s32 y = vm->stk[vm->sp];
    f32 r = func_0010f098((void *)((s32 *)&D_00388480)[t]);
    D_006298F0[n].v40[0] = r;
    D_006298F0[n].v30[0] = x + r * 12.0f;
    D_006298F0[n].v30[1] = y + D_006298F0[n].v40[1] * 12.0f;
    vm->sp -= 4;
    return 2;
}

s32 func_001cccf0(VmRec *vm) {
    D_003C5870[vm->stk[vm->sp - 1]] = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

MsgWin func_001ccd30(s32 i) {
    return D_006298F0[i];
}

/* func_001ccda8 / func_001ccdf0: replace stk[sp] (a template index) with
 * that template's position x / y.  m2c's code, kept as it matched: it reads
 * through the volatile labels D_00629920 / D_00629924 (D_006298F0[0].v30)
 * and takes the VM as an s32; the VmRec forms tried differ. */
volatile s32 D_00629920 ALIGNED(16);

s32 func_001ccda8(s32 arg0) {
  void *temp_a1;
  temp_a1 = ((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0;
  *((s32 *) (((s8 *) temp_a1) + 0x184)) = (s32) (*((f32 *) (((s8 *) ((s8 *) (&D_00629920))) + ((*((s32 *) (((s8 *) (((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0)) + 0x184))) * 0xB0))));
  return 2;
}

s32 func_001ccdf0(s32 arg0) {
  void *temp_a1;
  temp_a1 = ((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0;
  *((s32 *) (((s8 *) (((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0)) + 0x184)) = (s32) (*((f32 *) (((s8 *) ((s8 *) (&D_00629924))) + ((*((s32 *) (((s8 *) temp_a1) + 0x184))) * 0xB0))));
  return 2;
}
