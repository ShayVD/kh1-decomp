/* The mark over an actor (docs/modules.md "Session 46"), 0x00245238-0x00245798,
 * default flags part.  D_006627B0 (Req): the kind (0-2), the actor, the state,
 * the alpha and two flags.  func_00245238 asks for a mark of a kind over an
 * actor for this frame (a new kind or actor restarts it); func_00245280 does
 * the same and keeps it while the actor is busy; func_002452c8 lets it fade
 * (state 4) when nobody asked this frame; func_002452f0 is the HUD's step
 * for it (off; it writes D_006627B8, the state, by its own name).  Which
 * marks these are (talk, look) is not known (no boot). */
#include "common.h"

typedef struct { s32 id; s32 arg; s32 on; f32 t; s32 unk10; s32 unk14; } Req;

extern Req D_006627B0;
/* The request D_006627B0 (Req, 0x18 bytes, cleared whole by func_002456e8; D_006627B8 is its on). One definition (vita-port-plan 5.1i). */
Req D_006627B0 ALIGNED(16);
extern s32 D_006627B8;

void func_00245238(s32 id, s32 arg) {
    Req *r = &D_006627B0;
    r->unk10 = 1;
    if (r->on == 0 || r->id != id) {
        r->id = id;
        r->arg = arg;
        r->on = 1;
        r->t = 1.0f;
    }
}

void func_00245280(s32 id, s32 arg) {
    Req *r = &D_006627B0;
    r->unk10 = 1;
    r->unk14 = 1;
    if (r->on == 0 || r->id != id) {
        r->id = id;
        r->arg = arg;
        r->on = 1;
        r->t = 1.0f;
    }
}

void func_002452c8(void) {
    if (D_006627B0.on != 0 && D_006627B0.on < 4) {
        D_006627B0.on = 4;
    }
}

void func_002452f0(void) {
    D_006627B8 = 0;
}
