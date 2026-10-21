#include "common.h"
#include "data/types/nostrict_nogcse_text_00240000_s6_25.h"
typedef struct { u8 pad[0x55]; s8 x55; } EntInfo;
typedef struct { u8 pad[0x10]; V4f pos; u8 pad20[0x1c]; f32 x3c; u8 pad40[0xf0]; EntInfo *info; } Ent;
typedef struct { s32 x0; u8 pad[0x48]; u16 id; u8 pad4e[6]; s8 kind; s8 x55; } Obj;
typedef struct { u8 pad[0x491]; u8 cur; } Sys;
typedef struct { u8 pad[3]; u8 id; } Req;
#include "data/pieces/D_00304BE8.h"
extern V4f D_0066AA90;
extern Obj *D_0066AA84; /* src/data/bss_0066.c: s32 *D_0066AA84 */
extern void (*D_0066AA80)(void);
Ent *func_0013daf8(u8);
void func_002675a8(V4f *, V4f *);
void func_00141218(Ent *);
void func_001236f8(Ent *);
void func_001247e8(Ent *);
Obj *func_00132040(Obj *);
s32 func_001571a8(u16, s32);
s32 func_001560f8(s32, void *);
void func_0024f070(void);
void func_0024ef88(void);
void func_0024f098(Req *r, void (*cb)(void)) {
    if (r->id != ((Sys *)D_00304BE8)->cur) {
        Ent *e = func_0013daf8(((Sys *)D_00304BE8)->cur);
        Obj **pp;
        s8 v;
        func_002675a8(&D_0066AA90, &e->pos);
        D_0066AA90.w = e->x3c;
        v = e->info->x55;
        func_00141218(e);
        func_001236f8(e);
        func_001247e8(e);
        D_0066AA84 = 0;
        pp = &D_0066AA84;
        while ((*pp = func_00132040(*pp)) != 0) {
            if ((*pp)->id == r->id && (*pp)->kind == 1) break;
        }
        (*pp)->x55 = v;
        func_001571a8((*pp)->id, 0);
        func_001560f8((*pp)->x0, func_0024f070);
        D_0066AA80 = cb;
    } else {
        func_0024ef88();
        cb();
    }
}
#include "data/bss_0066_typed.h"
