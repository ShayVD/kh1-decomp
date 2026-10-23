#include "common.h"
#include "data/pieces/D_003F7A70.h"
#include "data/bss_0064.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { s32 a, b, c, d; } Q4;
typedef struct { u8 pad0[0xA0]; f32 xa0; u8 pad[0x10]; s32 xb4; u8 pad2[2]; u16 xba; u8 pad3[4]; u16 xc0; u8 pad4[0xA]; u16 xcc; u8 pad5[2]; s16 xd0; s16 xd2; } Obj;

void func_00109278(void);
void func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
s32 func_001efd98(s32);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f4040(void *, s32);
void func_001f4058(void *, s32);
void func_001f40a0(void *, s32);
s32 func_001f42b8(void);
void func_0020bb90(s32, s32);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);
s32 func_0020d030(void);
void func_0020d2f8(void);
void func_0020d530(void);
void func_00228e70(void *);
void func_00229490(s32);
void func_00233ef8(s32);

extern s32 D_003F3468[];
extern s32 D_003F3488[];
extern s32 D_003F34A8;
#include "data/pieces/D_003F34C4.h"
extern u8 D_003F6D10[];
extern void *D_003F6E18[];
extern s32 D_003F6E24;
extern s32 D_003F6E2C;
extern u8 D_003F6FD0[];
extern s32 D_003F6FF8[];
extern Q4 D_00643720; /* src/data/bss_0064.c: s32 D_00643720[0x4] */
extern s32 D_00643730;
extern s32 D_006437C4;

void func_002295a0(s32 arg0, s32 arg1) {
    s32 r;
    func_001f3110();
    D_003F34A8 = 1;
    func_0020d530();
    D_003F6E24 = 1;
    D_003F6E2C = arg1;
    if (arg1 != 1) {
        D_00643720.a = 0;
        D_00643720.b = 1;
        D_00643720.c = 2;
        D_00643720.d = 3;
        D_00643730 = 4;
    } else {
        D_00643730 = 3;
        D_00643720.b = arg1;
        D_00643720.c = 3;
        D_00643720.a = 0;
    }
    func_0011d768(6);
    r = func_0020d030();
    D_003F34C4 = (N_3f34c4 *)r;
    if (r != 0) {
        func_00229490(r);
    }
    func_0011ef10(0x270FF, func_0020d2f8)[1] = arg0;
}

void func_00229690(void *arg0) {
    void *objs[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        objs[i] = func_001f31a8(D_003F6E18[i], D_003F3468[i]);
        if (objs[i] != 0) {
            func_001f3e48(objs[i], arg0);
            func_001f3d58(objs[i], D_003F3488[i]);
            arg0 = objs[i];
        }
    }
    objs[0] = func_001f31a8(D_003F6D10, 4);
    if (objs[0] != 0) {
        func_001f3e48(objs[0], arg0);
        func_00228e70(objs[0]);
    }
    func_0020bb90(0x85, 0);
    func_0020bd18(objs[0], 8);
    func_0020bda8(0x10);
}

void func_0022b2e0(void *arg0) {
    Obj *o;
    s32 d;
    func_0011d768(4);
    o = func_001f31a8(D_003F6FD0, 6);
    if (o != NULL) {
        func_001f3e48(o, arg0);
        func_001f4058(o, 2);
        func_001f3d58(o, 6);
        d = func_001efd98(D_003F6FF8[D_006437C4]) * 0x170;
        o->xb4 -= d;
        o->xba += d;
        o->xc0 += d;
        func_0020bda8(0x10);
    }
}

extern u8 D_003F7000[];
extern u8 D_003F7030[];
extern u8 D_003F7060[];
#include "data/pieces/D_00425C28.h"
extern s32 D_006437E4;
extern s32 D_006469A4;

void func_0022b8a0(void *arg0) {
    Obj *o[3];
    if (func_001f42b8() != 0) {
        func_00109278();
        func_00233ef8(0);
        D_006469A4 = 0;
        D_006437E4 = 0;
        ((s32 *)&D_00425C28)[0] = 3;
        ((s32 *)&D_00425C28)[4] = 3;
        o[0] = func_001f31a8(D_003F7060, 6);
        if (o[0] != NULL) {
            func_001f3e48(o[0], arg0);
            func_001f4040(o[0], 4);
            func_001f40a0(o[0], 0x5A000000);
            o[1] = func_001f31a8(D_003F7030, 6);
            if (o[1] != NULL) {
                func_001f3e48(o[1], o[0]);
                o[1]->xd2 = *(u16 *)&D_006437C4 << 4;
                o[2] = func_001f31a8(D_003F7000, 6);
                if (o[2] != NULL) {
                    func_001f3e48(o[2], o[1]);
                    func_001f3dc0(o[1]);
                }
            }
        }
    }
}

extern void *D_003F71C8[];
extern s32 D_003F71E0[];
extern s32 D_003F71F8[];

void func_0022bb48(void *arg0) {
    void *objs[5];
    s32 i;
    for (i = 0; i < 5; i++) {
        objs[i] = func_001f31a8(D_003F71C8[i], D_003F71E0[i]);
        if (objs[i] != 0) {
            func_001f3e48(objs[i], arg0);
            func_001f3d58(objs[i], D_003F71F8[i]);
            arg0 = objs[i];
        }
    }
    func_001f3dc0(objs[4]);
    func_0020bb90(0, 0);
    func_0020bda8(0x10);
}

extern s32 D_003F34A4;
extern u8 D_003F7380[];
extern s32 D_003F73A4;
extern s32 D_006469B0;
extern s32 D_006469B4;
s32 func_00219428(void);
void func_0022d038(void);

void func_0022d080(s32 arg0) {
    void *objs[4];
    s32 v;
    s32 *p = &D_006469B4, *q = &D_006469B0;
    func_001f3110();
    objs[0] = func_001f31a8(D_003F7380, 12);
    v = func_00219428() != 0 ? 1 : 2;
    *q = v;
    *p = v;
    func_0020bb90(0, 0);
    func_0020bda8(0x10);
    D_003F34A4 = 1;
    D_003F73A4 = 0;
    func_0011ef10(0x2BFE7, func_0022d038)[1] = arg0;
}

extern u8 D_003F7510[];
extern u8 D_003F7540[];
extern u8 D_003F7570[];
extern s32 D_003F76B4;
void func_0020bbc0(void *);
void func_0022da58(void);

void func_0022daa0(s32 arg0) {
    Obj *o[3];
    func_001f3110();
    D_003F76B4 = 0;
    o[0] = func_001f31a8(D_003F7570, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7540, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F7510, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022da58)[1] = arg0;
}

extern u8 D_003F75A0[];
extern u8 D_003F75D0[];
extern u8 D_003F7600[];
extern s32 D_003F76B8;
void func_0022de98(void);

void func_0022dee0(s32 arg0) {
    Obj *o[3];
    func_001f3110();
    D_003F76B8 = 0;
    o[0] = func_001f31a8(D_003F7600, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F75D0, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F75A0, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022de98)[1] = arg0;
}

extern u8 D_003F7630[];
extern u8 D_003F7660[];
extern u8 D_003F7690[];
extern s32 D_003F76BC;
void func_0022e320(void);

void func_0022e368(s32 arg0) {
    Obj *o[3];
    func_001f3110();
    D_003F76BC = 0;
    o[0] = func_001f31a8(D_003F7690, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7660, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F7630, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022e320)[1] = arg0;
}

extern u8 D_003F7720[];
extern u8 D_003F7750[];
extern s32 D_003F7774;
extern s32 D_006469D0;
extern s32 D_006469D4;
extern s32 D_006469DC;
extern s32 D_006469E4;
extern s32 D_006469EC;
extern s32 D_006469F4;
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
void func_0020b968(void);
void func_0022eab8(void);

void func_0022eb00(s32 arg0) {
    Obj *o[2];
    func_001f3110();
    o[0] = func_001f31a8(D_003F7750, 44);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7720, 45);
        if (o[1] != NULL) {
            func_001f3e90(o[0], o[1]);
            func_001f3e20(o[1], o[0]);
            o[1]->xa0 = 0;
        }
    }
    D_006469DC = 0;
    D_006469E4 = 0;
    D_006469EC = 0;
    D_006469F4 = 0;
    D_003F7774 = 1;
    D_006469D0 = 0;
    D_006469D4 = 0;
    func_0020b968();
    func_0020bb90(0x153, 0xA4);
    func_0020bda8(0x28);
    func_0011ef10(0x2BFE9, func_0022eab8)[1] = arg0;
}

#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D6C.h"
extern s32 D_00646A14;
extern s32 D_00646A18;
extern u32 D_00646A20;
extern s32 D_00646A28;
extern s32 D_00647634;
extern u8 *D_00647638; /* src/data/bss_0064.c: s32 D_00647638 */
extern s32 D_0064763C;
void func_001ef7f0(s32);
void func_0022ebf8(s32);

s32 func_0022ee08(void) {
    s32 *p = &D_00646A18;
    func_0022ebf8(D_00646A14);
    if (*p > 0) {
        func_0011d768(8);
        func_001ef7f0(D_0064763C);
        if (D_00646A20 < D_003E3D6C) {
            { s32 o = D_00647634; D_00647638[o + 0x22] = *p; }
        } else {
            D_00304BE8->items[*p] += D_00646A28;
        }
    } else {
        func_0011d768(4);
    }
    D_00646A28 = 1;
    return D_00646A18;
}

extern s32 D_00646A1C;
extern u32 D_00646A24;
extern s32 D_00646A30[];
extern s32 D_00647630;
extern s32 D_00646E30[];
extern u8 *D_00647230[]; /* src/data/bss_0064.c: s32 D_00647230[0x100] */
u32 func_001ef7a0(void);

void func_0022fa58(s32 i) {
    if (D_00647630 != 0) {
        s32 *p = &D_00646A1C;
        s32 n = D_00646A28;
        *p = D_00646A30[i];
        if (n == 1) {
            if (*p != 0) goto call;
        } else if (D_00646A24 >= D_003E3D6C && D_00646E30[i] >= n) {
            goto call;
        } else {
            *p = -3;
        }
        goto end;
    call:
        if (func_001ef7a0() > 99998) {
            *p = -1;
        }
    } else {
        D_00646A1C = -2;
    }
end:
    D_00647638 = D_00647230[i];
}

extern s32 *D_00646A0C;
s32 func_001eeaf0(s32);
s32 func_001ba458(s32);

void func_002305b0(s32 i) {
    s32 *p = &D_0064763C;
    s32 *q;
    s32 id = D_00646A0C[i];
    s32 a;
    *p = func_001eeaf0(id) * *(q = &D_00646A28);
    if (func_001ef7a0() >= (u32)*p) {
        a = func_001ba3f0(id);
        if (a == func_001ba458(id)) {
            D_00646A18 = -2;
            return;
        }
        a = func_001ba3f0(id) + *q;
        if (func_001ba458(id) < a) {
            D_00646A18 = -4;
            return;
        }
        D_00646A18 = id;
        return;
    }
    D_00646A18 = -1;
}

extern s32 D_00647640;
s32 func_001eeb08(s32);
void func_001ba420(s32, s32);
s32 func_001ba3d8(void);
void func_0020be10(s32);

void func_00230f18(void) {
    s32 *p = &D_00646A1C;
    if (*p >= 0) {
        s32 *q = &D_00646A28;
        s32 *r;
        s32 i, n;
        func_0011d768(8);
        i = 0;
        func_001ef7b0(func_001eeb08(*p) * *q);
        func_001ba420(*p, func_001ba3f0(*p) - *q);
        r = &D_00647640;
        *r -= *q;
        n = func_001ba3d8();
        for (; i < n; i++) {
            if (func_001ba3f0(i) != 0 && func_001eeb08(i) != 0) {
                goto done;
            }
        }
        func_0020be10(16);
    } else {
        func_0011d768(4);
    }
done:
    D_00646A28 = 1;
}

extern s32 D_003F7D10[];
extern s32 D_00647664;
extern s32 D_00647668;
extern s32 D_00647670[];
extern s32 D_006476F4;
s32 func_001ec360(void);
s32 func_001ec258(s32);

void func_002319d0(void) {
    s32 i;
    s32 v = func_001ec360();

    D_00647664 = v;
    D_00647668 = D_003F7D10[v];
    D_006476F4 = 0;
    for (i = 0; i < D_00647668; i++) {
        if ((D_00647670[i] = func_001ec258(i)) != 0) {
            D_006476F4++;
        }
    }
}

#include "data/pieces/D_003F7C48.h"
typedef T7C48_3f7c48 E7C48;
typedef T7A70 E7A70;
extern s32 D_00647660;
extern s32 D_0064765C;
void func_001ec2c0(s32, s32);

void func_00231b98(void) {
    s32 *p = &D_00647660;
    s32 *k;
    s32 *e;
    E7C48 *c;
    E7A70 *l;
    s32 n;
    if (*p > 0) {
        func_0011d768(18);
        k = &D_0064765C;
        e = &D_00647670[*k];
        if (*e == 0) {
            *e = 1;
            D_006476F4++;
            func_001ec2c0(*k, 1);
        }
        D_00304BE8->items[*p]++;
        c = &((T7C48_3f7c48 *)&D_003F7C48)[*k];
        n = c->n;
        l = &D_003F7A70[c->b2];
        for (; n > 0; n--) {
            D_00304BE8->items[l->id] -= (u8)l->max;
            l++;
        }
    } else {
        func_0011d768(4);
    }
}


void func_00231cd0(s32 arg0) {
    E7C48 *c = &((T7C48_3f7c48 *)&D_003F7C48)[D_0064765C];
    E7A70 *l;
    s32 n;
    if (c->flag == 1 && D_00647670[D_0064765C] != 0) {
        D_00647660 = -3;
        return;
    }
    n = c->n;
    l = &D_003F7A70[c->b2];
    D_00647660 = arg0;
    for (; n > 0; n--) {
        if (D_00304BE8->items[l->id] < l->max) {
            D_00647660 = -1;
            return;
        }
        l++;
    }
    if (D_00304BE8->items[D_00647660] >= 99) {
        D_00647660 = -2;
    }
}


s32 func_00231dd0(s32 k) {
    E7C48 *c = &((T7C48_3f7c48 *)&D_003F7C48)[k];
    E7A70 *l;
    s32 n;
    if (c->flag == 1 && D_00647670[k] != 0) {
        return -3;
    }
    n = c->n;
    l = &D_003F7A70[c->b2];
    for (; n > 0; n--) {
        if (D_00304BE8->items[l->id] < l->max) {
            return -1;
        }
        l++;
    }
    return D_00304BE8->items[c->id] < 99 ? 0 : -2;
}


extern s32 D_003F7E94;
extern s32 D_003F7E98;
extern u8 D_003F7D60[];
extern u8 D_003F7E70[];
extern s32 D_00647648;
extern s32 D_0064764C;
extern Obj *D_00647650; /* src/data/bss_0064.c: s32 D_00647650 */
extern s32 D_00647654;
extern s32 D_00647658;
void func_001ef830(void);
void func_002325f8(void);

void func_00232640(s32 arg0, s32 arg1) {
    s32 *p = &D_003F7E94;
    if (*p == 0) {
        Obj **q;
        Obj *o, *a;
        func_001f3110();
        func_0020b968();
        func_0020bb90(0xE7, 0);
        func_0020bda8(0x10);
        *p = 1;
        D_003F7E98 = 1;
        func_001ef830();
        D_00647648 = arg0;
        D_0064764C = arg1;
        func_002319d0();
        a = func_001f31a8(D_003F7E70, 1);
        q = &D_00647650;
        *q = a;
        if (a != NULL) {
            o = func_001f31a8(D_003F7D60, 1);
            if (o != NULL) {
                func_001f3e48(o, *q);
                o->xcc = D_00647668;
                o->xd0 = D_00647654 << 4;
                o->xd2 = D_00647658 << 4;
            }
        }
        do {
            func_0011ef10(0x2BF84, func_002325f8);
        } while (0);
    }
}


typedef struct { u8 pad[0x664]; u32 x664, x668, x66c, x670; } Scr;
#include "data/types/text_00220000_h48.h"
extern s32 D_003F7EC4;
extern s32 D_003F7EC8;
extern Win D_003F7EA0;
extern s32 D_006476F8;
extern s32 D_006476FC;
extern Scr *D_00647700; /* src/data/bss_0064.c: u16 *D_00647700 */
extern void *D_00647704; /* src/data/bss_0064.c: u8 *D_00647704 */
extern void *D_00647708; /* src/data/bss_0064.c: s32 D_00647708 */
extern void *D_0064770C;
void func_00232960(void);

void func_002329a0(Scr *arg0, s32 arg1, s32 arg2) {
    u32 x, y;
    s32 w;
    func_001f3110();
    D_003F7EC4 = 1;
    D_003F7EC8 = 1;
    D_00647700 = arg0;
    D_006476F8 = arg1;
    D_006476FC = arg2;
    D_00647704 = (u8 *)arg0 + 4;
    D_00647708 = (u8 *)arg0 + 0x644;
    x = (arg0->x664 - 0x7000) >> 4;
    y = (arg0->x668 - 0x7400) >> 4;
    w = ((arg0->x66c - 0x7000) >> 4) - x;
    D_003F7EA0.x10 = w + 1;
    D_003F7EA0.x12 = ((arg0->x670 - 0x7400) >> 4) - y + 1;
    D_003F7EA0.x18 = w - 39;
    D_003F7EA0.xc = x;
    D_003F7EA0.xe = y;
    D_0064770C = func_001f31a8(&D_003F7EA0, 0);
    func_0011ef10(0x2C01A, func_00232960);
}


typedef struct { s32 type; s32 id; s32 a[6]; } Cmd;
extern Cmd D_006477B0[64];
extern s32 D_00647FB0;
extern s32 D_00647FB8;
extern s32 D_00647FBC;
extern s32 D_00647FC4;

s32 func_00233d08(s32 id) {
    s32 i, x;
    if (id != 0) {
        i = D_00647FBC;
        while (i != D_00647FB8) {
            x = D_006477B0[i].id;
            i++;
            i &= 63;
            if (x == id) {
                goto found;
            }
        }
        if (D_00647FB0 == 0 || D_00647FC4 != id) {
            goto none;
        }
    found:
        return 1;
    }
    if (D_00647FB8 != D_00647FBC || D_00647FB0 != 0) {
        goto found;
    }
none:
    return 0;
}


extern s32 D_00647FC0;

s32 func_00234098(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 2;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[4] = arg4;
    return id;
}


s32 func_00234148(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 3;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}


s32 func_00234440(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 8;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}


s32 func_002345a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 10;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}


s32 func_00234668(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 11;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}



s32 func_00234730(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 9;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[4] = arg4;
    return id;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_003F7090[];
extern u8 D_003F70C0[];
extern u8 D_003F7100[];
extern u8 D_003F7140[];
extern u8 D_003F7170[];
void *D_003F71C8[0x6] ALIGNED(8) = {
    (void *)D_003F7170, (void *)D_003F7140, (void *)D_003F7100, (void *)D_003F70C0,
    (void *)D_003F7090, 0,
};
#include "data/data_003F.h"
#include "data/pieces/D_003F3488.h"
#include "data/pieces/D_003F7EA0.h"
