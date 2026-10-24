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
#ifdef KH1_OVL_FIXUPS
#endif
#include "data/bss_004E_mixed.h"
#include "data/bss_004E_typed.h"
#include "data/data_002C.h"
#include "data/pieces/D_002C5BB0.h"
