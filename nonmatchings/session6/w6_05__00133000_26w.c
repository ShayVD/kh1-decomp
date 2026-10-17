/* func_00133000: 26 words off (nostrict). Original builds &D_00525368[i] with the la/at macro form and keeps t->f0 in v0; ours uses lui/addiu/addu into a3. */
#include "common.h"
typedef struct { u8 pad[0x4c]; u16 f4c; } Info;
typedef struct { u8 pad[0x130]; Info *f130; } Ent;
typedef struct { u8 pad[0x30]; s32 f30; } Q30;
typedef struct { s32 f0; u8 pad[8]; Q30 *fc; u8 pad10[0xc]; } T28;
typedef struct { u8 b74; u8 pad[0x73]; } E74;
typedef struct { E74 e[1]; } Sv;
extern u32 D_002E31A8;
extern Sv *D_00304BE8;
extern T28 D_00525368[];
extern s32 func_00141288(Ent *, s32, s32);

s32 func_00133000(Ent *o, s32 i) {
    T28 *t = &D_00525368[i];
    Q30 *q;
    if ((D_002E31A8 >> 2) & 1) return 0;
    if (!t->f0) return 0;
    if (!(q = t->fc)) return 0;
    if (*(s32 *)((u8 *)D_00304BE8 + 0x874) & 1) return 0;
    if ((D_00304BE8->e[o->f130->f4c + 1].b74 >> i) & 1) return func_00141288(o, q->f30, i);
    return 0;
}
