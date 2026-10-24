/* pppColorFrame, -fno-strict-aliasing (docs/modules.md "Session 50"): adds
 * the key's colour step at its frame.  The other component classes are in
 * pppcomp.c.  Read from the code, not proved by a boot. */
#include "ppp.h"
#ifndef KH1_PS2
#include "platform/vu.h"
#endif
#include "data/types/nostrict_text_00180000_h39.h"
#include "data/pieces/D_00362730.h"

/* pppColorFrame (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    u8 pad00[0x20];
    s32 dataoff;  /* +0x20 */
    s16 prio;     /* +0x24 */
    s16 n;        /* +0x26 */
    PppEntry ent[1]; /* +0x28 */
} H39Prog;
struct H39Inst;
typedef struct {
    H39Prog *prog;          /* +0x0 */
    struct H39Inst *last;   /* +0x4 */
    s32 time;               /* +0x8 */
    u16 count;              /* +0xC */
} H39Slot2;
typedef struct H39Inst {
    struct H39Inst *next;   /* +0x0 */
    s32 unk04;
    H39Slot2 *slot;         /* +0x8 */
    s32 frame;              /* +0xC */
    u8 pad10[0x80];
    s32 unk90, unk94;
    u8 pad98[4];
    u8 unk9C, unk9D, unk9E;
} H39Inst;
typedef struct {
    u8 pad00[0x30];
    f32 col[4];             /* +0x30: colour scale */
    u8 pad40[0x34];
    H39Inst *head;          /* +0x74 */
    u8 pad78[8];
    H39Slot2 *slots;        /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;              /* +0xB0 */
} H39PSys;
extern H39PSys *D_00615E60;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef struct {
    s32 frame;
    u16 d[4]; /* +0x4 */
} H39ColKey;
typedef struct {
    u16 c[4]; /* +0x0 */
    u32 rgba; /* +0x8: c scaled by the system colour, packed */
} H39Col;
extern s32 D_0061621C;
void pppColorFrame(PppObject *obj, H39ColKey *key, PppEntry *e) {
    H39Col *w = (H39Col *) ((u8 *) obj + e->offsets[0] + 0xA0);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        w->c[0] += key->d[0];
        w->c[1] += key->d[1];
        w->c[2] += key->d[2];
        w->c[3] += key->d[3];
    }
    /* Widen the four u16 to words, scale by col in VU0, pack to bytes. */
#ifdef KH1_PS2
    __asm__ volatile(
        "lw $2, 4(%0)\n"
        "pextlw $2, $2, $0\n"
        "lw $3, 0(%0)\n"
        "or $2, $2, $3\n"
        "pextlh $2, $0, $2\n"
        "qmtc2 $2, $vf1\n"
        "vitof0.xyzw $vf1xyzw, $vf1xyzw\n"
        "lqc2 $vf2, 0(%1)\n"
        "vmul.xyzw $vf1xyzw, $vf1xyzw, $vf2xyzw\n"
        "vftoi0.xyzw $vf1xyzw, $vf1xyzw\n"
        "qmfc2 $2, $vf1\n"
        "psrlw $2, $2, 7\n"
        "ppach $2, $0, $2\n"
        "ppacb $2, $0, $2\n"
        "sw $2, 8(%0)\n"
        :
        : "r"(w), "r"(D_00615E60->col)
        : "$2", "$3", "memory");
#else
    {
        /* each u16 times its colour scale, >> 7, packed to a byte */
        u32 v = 0;
        int i;
        for (i = 0; i < 4; i++)
            v |= (((u32)PlatVu0Ftoi0((f32)w->c[i] * D_00615E60->col[i]) >> 7) & 0xFF) << (i * 8);
        w->rgba = v;
    }
#endif
}

