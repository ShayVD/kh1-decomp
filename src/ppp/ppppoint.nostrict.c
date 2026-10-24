/* pppPointApFrame, -fno-strict-aliasing (docs/modules.md "Session 50"):
 * starts an effect (func_00182588) at the owner's position at the key's
 * frame.  Read from the code, not proved by a boot. */
#include "ppp.h"
#include "data/types/nostrict_text_00180000_h39.h"
#include "data/pieces/D_00362730.h"
#include "data/pieces/D_003701F0.h"

/* pppPointApFrame (from hand/nostrict/text_00180000_h39.c). */
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
H39Inst *func_00182588(H39PSys *, H39Slot2 *);
extern H39PSys *D_00615E60;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
extern s32 D_0061621C;
typedef struct {
    s32 frame;
    s32 slot;   /* +0x4: program slot to start, -1 none */
    s32 off;    /* +0x8: work offset of its position */
    u8 every;   /* +0xC */
} H39PApKey;
void pppPointApFrame(PppObject *obj, H39PApKey *key, PppEntry *e) {
    f32 *pos = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);
    u8 *w = (u8 *) obj + e->offsets[1] + 0xA0;
    H39Inst *inst;
    H39Slot2 *s;
    f32 *out;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (w[1] == 0) {
        if (key->slot == -1)
            return;
        inst = NULL;
        s = &D_00615E60->slots[key->slot];
        if (s != NULL) {
            inst = func_00182588(D_00615E60, s);
            inst->unk04 = (s32) obj;
        }
        out = (f32 *) ((u8 *) inst + key->off + 0xA0);
        out[0] = pos[0];
        out[1] = pos[1];
        out[2] = pos[2];
        w[1] = key->every;
    }
    w[1]--;
}

