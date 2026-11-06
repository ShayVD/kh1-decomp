/* xs_genie.x func_00f20cb8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x370]; u64 f370; } Act;
typedef struct { Act *act; s32 id; } Cur;
#ifdef KH1_PS2
void func_0012ec60(Act *, s32, f32 *);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_0012ec60(Act *, s32, f32 *);
#endif
Act *func_001230a0(Act *);
s32 func_0012ee70(Act *, s32);
s32 func_0012f040(Act *, s32);
s32 func_0012f0f8(void *, f32 *, s32);
extern Cur D_002E31B0;
extern u8 D_002E2780[];
extern Cur D_00FC1748[];
extern s32 D_00FC1A48;
void func_00f20cb8(Cur *out) {
    Cur c;
    OvlVec me;
    OvlVec p;
    f32 best = 0.0f;
    f32 d;
    s32 i;

    func_0012ec60(D_002E31B0.act, D_002E31B0.id, me);
    out->act = NULL;
    c.act = NULL;
    while ((c.act = func_001230a0(c.act)) != NULL) {
        if ((c.act->f370 & (0xD000ULL << 23)) != (0x9000ULL << 23))
            continue;
        c.id = -1;
        while ((c.id = func_0012ee70(c.act, c.id)) >= 0) {
            if (!func_0012f040(c.act, c.id))
                continue;
            for (i = 0; i < D_00FC1A48; i++)
                if (D_00FC1748[i].act == c.act && D_00FC1748[i].id == c.id)
                    break;
            if (i < D_00FC1A48)
                continue;
            func_0012ec60(c.act, c.id, p);
            if (!func_0012f0f8(D_002E2780, p, 0))
                continue;
            PlatVu0SubVector(p, p, me);
            d = PlatVu0InnerProduct(p, p);
            if (out->act == NULL || d < best) {
                *out = c;
                best = d;
            }
        }
    }
}
