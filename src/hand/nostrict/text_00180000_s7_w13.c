#include "common.h"
/* func_00182ec0 (w13): c->draw read into a local before the 'fn == 0 || dr' test (loaded before the branch, fills the beqz slot). */
typedef struct Cls { char *name; void (*frame)(void *, void *, void *); void *fn08; void *draw; } Cls;
typedef struct Ent { Cls *cls; u16 stride; u16 pad6; void *data; s32 *offsets; } Ent;
typedef struct Prog { u8 pad0[0x20]; s32 off20; u8 pad24[2]; s16 n; Ent ent[1]; } Prog;
typedef struct Obj {
    struct Obj *next;
    u8 pad4[8];
    s32 frame;
    u8 pad10[0x9c - 0x10];
    u8 x9c, x9d, x9e;
} Obj;
typedef struct { Prog *prog; Obj *obj; s32 val; u16 cnt; s8 idx; u8 padf; } Slot;
typedef struct { u8 pad[0xB0]; u64 flags; } PppSystem;
typedef struct { u8 pad0[0x68]; s32 nslot; u8 pad6c[0x80 - 0x6c]; Slot *slots; } PSys;
extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern Obj *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
void pppResetComponents(Obj *);

void func_00182ec0(PSys *o) {
    s32 i, j;
    for (i = 0; i < o->nslot; i++) {
        Slot *sl = &o->slots[i];
        Prog *pg = sl->prog;
        Ent *e;
        if (sl->cnt == 0) continue;
        for (j = 0; j < pg->n; j++) {
            Cls *c = (e = &pg->ent[j])->cls;
            Obj *ob = sl->obj;
            void (*fn)(void *, void *, void *) = c->frame;
            void *dr = c->draw;
            s32 k;
            if (fn == 0 || dr) continue;
            k = sl->cnt;
            do {
                s32 *pp = (s32 *)((u8 *)ob + pg->off20 + j * 4);
                Obj *nx = ob->next;
                if (!ob->x9c) {
                    s32 *d = (s32 *)*pp;
                    s32 *d2 = (s32 *)((u8 *)d + e->stride);
                    D_00615E68 = ob;
                    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) && ob->x9e) {
                        ob->frame = 0;
                        ob->x9d = 1;
                        pppResetComponents(ob);
                        ob->x9e = 0;
                    }
                    if (*d2 == ob->frame) {
                        d = d2;
                        *pp = (s32)d;
                    }
                    fn(ob, d, e);
                }
                ob = nx;
            } while (--k);
        }
    }
}
