#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
typedef struct Node { u16 type; u16 f2; s32 key; struct Node *next; s32 data; } Node;
typedef struct { u16 size; u16 count; u8 *base; Node *head; u8 *cur; } Pool;
u8 *func_0011efe8(Pool *p);
Node *func_0011f090(Pool *l, s32 key, s32 val) {
    Node *n = (Node *)func_0011efe8(l);
    Node *prev, *p;
    if (n) {
        n->data = val;
        n->type = 17;
        prev = 0;
        n->key = key;
        n->f2 = 0;
        for (p = l->head; p && key >= p->key; p = p->next) prev = p;
        if (prev) prev->next = n;
        else l->head = n;
        n->next = p;
    }
    l->cur = (u8 *)n;
    return n;
}
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
typedef struct { u8 x0[2]; u8 x2; u8 pad[17]; } Prof;
extern s16 D_002C597A;
extern PadSt D_002C5AD0[];
extern PadSt D_002C5BB0;
extern s32 D_004E4280;
extern s32 D_004E44C0[];
Prof D_004E44C8[0x2] ALIGNED(8);
extern s32 D_004E44F0;
#include "data/pieces/D_002C58B0.h"
extern u8 D_002C5A80[];
s32 scePad2GetState(s32);
s32 scePad2GetButtonProfile(s32, void *);
s32 scePad2Read(s32, u8 *);
s32 sceVibSetActParam(s32, s32, u8 *, s32, s32 *);
s32 func_0011f370(PadSt *, u8 *);
void func_0011f548(PadSt *, s32);
u32 func_0011f628(u32);
s32 func_00219348(void);
void func_0011fec0(void);
void func_002675a8(void *, void *);

void func_0011f668(void) {
    u8 buf[256];
    s32 vib;
    s32 i;
    PadSt *p;
    s32 btn;
    u16 act;
    { s32 m = (*(volatile Sema_2c5968 *)&D_002C5968).mode; if (m) return; }
    (*(volatile Sema_2c5968 *)&D_002C5968).b0 = 0;
    i = 0;
    goto top;
body:
    if (p->active == 0 && scePad2GetButtonProfile(D_004E44C0[i], &D_004E44C8[i]) < 0) goto join;
    if (scePad2Read(D_004E44C0[i], buf) >= 0) {
        btn = (buf[0] | (buf[1] << 8)) ^ 0xffff;
        if ((D_004E44C8[i].x2 & 0xf) == 0xf) btn |= func_0011f370(p, buf);
        if (func_00219348() == 0 && !(D_002C597A & 1)) {
            { u32 t = p->b3 << 1; vib = (u32)p->b2 >> 31; vib |= t; }
            sceVibSetActParam(D_004E44C0[i], 1, D_002C5A80, 2, &vib);
        }
        p->b3 = 0;
        act = 1;
        p->b2 = 0;
    }
    goto join;
top:
    p = &D_002C5AD0[i ^ D_004E4280];
    act = 0;
    btn = 0;
    if (scePad2GetState(D_004E44C0[i]) == 1) goto body;
join:
    func_0011f548(p, btn);
    i++;
    p->active = act;
    if (i <= 0) goto top;
    if (D_002C5AD0[D_004E4280].active != 1) {
        if (D_004E44F0 >= 31) (*(volatile Sema_2c5968 *)&D_002C5968).b0 = 1;
        else D_004E44F0++;
    } else {
        D_004E44F0 = 0;
    }
    if (D_002C5960.b) {
        D_002C5BB0.active = 0;
        func_002675a8(&D_002C5BB0.v[0], &D_002C58B0);
        func_002675a8(&D_002C5BB0.v[1], &D_002C58B0);
        func_002675a8(&D_002C5BB0.v[2], &D_002C58B0);
        func_002675a8(&D_002C5BB0.v[3], &D_002C58B0);
        func_0011f548(&D_002C5BB0, 0);
    } else {
        func_002675a8(&D_002C5BB0.v[0], &D_002C5AD0[0].v[0]);
        func_002675a8(&D_002C5BB0.v[1], &D_002C5AD0[0].v[1]);
        func_002675a8(&D_002C5BB0.v[2], &D_002C5AD0[0].v[2]);
        func_002675a8(&D_002C5BB0.v[3], &D_002C5AD0[0].v[3]);
        func_0011f548(&D_002C5BB0, func_0011f628(D_002C5AD0[0].x4));
        D_002C5BB0.active = 1;
    }
    func_0011fec0();
}
#include "data/types/nostrict_text_00110000_s6_04.h"
extern FileEnt D_004E4A00[];
extern s32 D_002C5C30;
extern u32 D_004F3200;
extern s32 D_004F3208;
void func_00120580(char *, FileEnt *);
FileEnt *func_00120190(char *);
/* rodata */
void func_0011fe20(void) {
    FileEnt *p;
    func_00120580("\\KINGDOM.IDX;1", D_004E4A00);
    D_002C5C30 = 0;
    p = D_004E4A00;
    while (p->lsn != 0 || p->size != 0) {
        p->lsn += D_004F3208;
        D_002C5C30++;
        p++;
        if (D_002C5C30 >= 3584) goto done;
    }
done:
    {FileEnt *e = func_00120190("kingdom.img"); D_004F3200 = e->lsn;}
}
s32 func_00120040(u8 *buf, s32 len) {
    u8 *p = buf + len;
    u8 key, c, n;
    s32 size, i, cnt;
    u8 *dst;
    key = *--p;
    { u8 b0 = *--p; u8 b1 = *--p; u8 b2 = *--p; size = b0 | b1 << 8 | b2 << 16; }
    dst = buf + size;
    while (buf < p) {
        c = *--p;
        if (c == key) {
            n = *--p;
            if (n != 0) {
                cnt = *--p + 3;
                for (i = 0; i < cnt; i++) {
                    dst--;
                    *dst = dst[n];
                }
            } else {
                *--dst = c;
            }
        } else {
            *--dst = c;
        }
    }
    return size;
}
typedef struct { u8 pad[0x30]; s32 result; } CdReq30;
#include "data/pieces/D_002C5C48.h"
CdReq30 *func_001204a0(char *, u8 *);
void func_0011fd40(void);
void func_00120038(CdReq30 *);
s32 FlushCache(s32);
#ifdef KH1_OVL_FIXUPS
void kh1_ovl_flush0(CdReq30 *); /* shift build only (shift/ovl_fixup.c): overlay fixups + FlushCache(0) */
#endif
s32 func_001205f0(char *name, u8 *buf) {
    CdReq30 *r = func_001204a0(name, buf);
    while (r->result < 0) {
        func_0011fd40();
        __asm__ volatile("nop\nnop\nnop\nnop\nnop");
    }
    D_002C5C48 = r->result;
    func_00120038(r);
#ifdef KH1_OVL_FIXUPS
    kh1_ovl_flush0(r); /* relocate an overlay before it is flushed and run; same size as FlushCache(0) */
#else
    FlushCache(0);
#endif
    FlushCache(2);
    return D_002C5C48;
}
f32 func_00120c18(f32 *v) {
    f32 r;
    f32 x = v[0] * v[0] + v[2] * v[2];
    __asm__ volatile(".set noreorder\nsqrt.s %0, %1\n.set reorder" : "=f"(r) : "f"(x));
    return r;
}
void func_001219c8(f32 *d, f32 *a, f32 *b) {
    s32 i;
    for (i = 0; i < 3; i++) d[i] = a[i] / b[i];
}
f32 asinf(f32);
f32 atan2f(f32, f32);
void func_002673b8(f32 *, f32 *);
void func_00121a78(f32 m[4][4], f32 *out) {
    f32 t[4][4];
    s32 i;
    for (i = 0; i < 3; i++) func_002673b8(t[i], m[i]);
    out[0] = atan2f(-t[1][2], t[0][2]);
    out[1] = asinf(-t[2][2]);
    out[2] = atan2f(t[2][1], t[2][0]);
}
typedef struct { s32 x0; void *x4; s32 x8; s32 xc; s32 x10; } E20;
extern E20 D_004F45B0[]; /* src/data/bss_004F.c: Block D_004F45B0[0x200] */
extern E20 *D_004F6DB0; /* src/data/bss_004F.c: Block *D_004F6DB0 */
extern u8 D_00820000[];
s32 func_00121b98(void);
typedef struct { s16 x0; s16 x2; } Tsk;
Tsk *func_0011ef10(s32, s32 (*)(void));
void func_00121c78(void) {
    E20 *p;
    s32 i;
    for (i = 1; i < 512; i++) D_004F45B0[i].x4 = 0;
    p = D_004F45B0;
    D_004F6DB0 = p + 1;
    p->x4 = D_00820000;
    p->xc = 0;
    p->x10 = 0;
    p->x8 = 0;
    func_0011ef10(200000, func_00121b98)->x2 = -1;
}
#include "data/pieces/D_002C5C80.h"
typedef Lt64_2c5c80 Lt64;
typedef struct { u8 pad[0x420]; u32 mask; u8 pad2[0xc]; f32 pos[4]; } Obj430;
#include "data/pieces/D_002C5910.h"
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);

void func_001229c0(Obj430 *o, f32 m[4][4]) {
    s32 i;
    s32 b;
    f32 *row;
    Lt64 *e;
    sceVu0CopyMatrix(m, D_002C5910);
    { s32 j; for (j = 3; j >= 0; j--) m[3][j] = 1.0f; }
    for (i = 0, e = &D_002C5C80, b = 1, row = m[0]; i < 31; i++, e++) {
        if (o->mask & (b << i)) {
            if (e->kind < 5) if (e->kind >= 2) {
                func_002675a8(row, &e->col.x);
                row += 4;
            }
        }
    }
    func_002675a8(m[3], o->pos);
}
typedef struct { u8 pad[0x44]; f32 x44; u8 pad48[0x16]; u8 x5e; u8 x5f; } Sub130;
typedef struct { u8 pad[0x130]; Sub130 *p; } Obj130;
void func_00122f58(Obj130 *o, f32 a, f32 b, f32 c) {
    o->p->x44 = a;
    o->p->x5e = b;
    o->p->x5f = c;
}
typedef struct { u8 pad[6]; volatile u8 x6; } Sub134;
typedef struct { u64 x0; u8 pad8[0x12c]; Sub134 *x134; u8 pad138[0x270]; u32 x3a8; } Ent3a8;
s32 func_00123368(Ent3a8 *e) {
    Sub134 *s = e->x134;
    s32 i;
    if (s == 0 || s->x6 == 0 || ((u8 *)e)[6] == 2 || (e->x0 & 0x8048) != 0x8000) return 0;
    for (i = 0; i < s->x6; i++) {
        if (!(e->x3a8 & (1 << i))) return 1;
    }
    return 0;
}
extern s32 D_004F82C0;
extern s32 D_004F82C4;
void func_00114f50(s32, void *);
s32 *func_0015ed80(s32, void (*)(void));
void func_00127500(void);
u32 *func_00121e28(s32, s32 *);
s32 func_00115018(void *, s32, f32 (*)[4]);
void func_00115058(void *, s32, f32 (*)[4]);
void func_00115098(void *, s32, f32 *);
f32 func_00267390(f32 *, void *);
void func_00120ef0(f32 *, void *, f32 *);

void func_00127568(s32 *list, s32 n, void *a2, void *a3, void *a4, f32 scale) {
    f32 v[4][4];
    f32 c[4][4];
    f32 out[4];
    f32 nrm[4];
    u32 *base;
    u32 *tag1;
    u32 *tag2;
    u32 *q;
    s32 count;
    s32 total;
    s32 k;
    s32 i;
    s32 j;
    s32 m;
    s32 idx;

    count = 0;
    func_00114f50(D_004F82C4 + D_004F82C0++, a4);
    tag1 = 0;
    tag2 = 0;
    base = func_00121e28(n * 224 + 16, func_0015ed80(D_004F82C4 + D_004F82C0++, func_00127500) + 4);
    q = base + 4;
    for (i = 0; i < n; i++) {
        k = func_00115018(a4, list[i], v);
        func_00115058(a4, list[i], c);
        func_00115098(a4, list[i], nrm);
        if (func_00267390(nrm, a3) >= 0.0f) continue;
        total = count + k;
        if (total > 50) {
            *tag1 = ((count * 3 + 1) << 16) | 0x6C008000;
            *tag2 = count | 0x8000;
            *q++ = 0x17000000;
            *q++ = 0;
            *q++ = 0;
            *q++ = 0;
            count = 0;
            total = k;
        }
        if (count == 0) {
            *q++ = 0x13000000;
            *q++ = 0;
            *q++ = 0;
            tag1 = q++;
            tag2 = q++;
            *q++ = 0x312E4000;
            *q++ = 1042;
            *q++ = 0;
        }
        for (j = 0; j < k; j++) {
            if (k == 3) idx = j; else idx = j ^ (j >> 1);
            for (m = 0; m < 3; m++) *(f32 *)q++ = v[idx][m];
            *(f32 *)q++ = 1.0f;
            for (m = 0; m < 4; m++) *(f32 *)q++ = 128.0f;
            func_00120ef0(out, a2, c[idx]);
            *(f32 *)q++ = out[0] / scale + 0.5f;
            *(f32 *)q++ = out[1] / scale + 0.5f;
            *(f32 *)q++ = 1.0f;
            if (j < 2) {
                *q = 0;
            } else if (j == 2) {
                *q = 0xBF800020;
            } else {
                *q = 0x3F800020;
            }
            q++;
        }
        count = total;
    }
    if (count > 0) {
        *tag1 = ((count * 3 + 1) << 16) | 0x6C008000;
        *tag2 = count | 0x8000;
        *q++ = 0x17000000;
        *q++ = 0x13000000;
        *q++ = 0;
        *q++ = 0;
    }
    *(u64 *)base = (((u8 *)q - (u8 *)base + 15) / 16 - 1) | 0x70000000;
}
#include "data/bss_004E_mixed.h"
#include "data/bss_004E_typed.h"
#include "data/data_002C.h"
#include "data/pieces/D_002C5BB0.h"
