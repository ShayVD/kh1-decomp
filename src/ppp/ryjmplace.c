/* The pppRyjMegaPlace classes' default-flag functions (docs/modules.md
 * "Session 50"): pppRyjMegaPlace places shapes, models and lamps from a
 * table.  Its frame allocates the three blocks (32-byte shape and model
 * entries, 0x30-byte lamp entries) the counts in its work area ask for, the
 * draw calls the three drawers in ryjmplace.nostrict.c, the Des frees the
 * blocks.  The pppRyjMegaPlaceShape / Model / Lamp classes each add one
 * entry to the owner's count in their Con and fill it once in their frame
 * (func_0019e028 / e108 / e1e8, from the key's table entry that
 * func_0019dfc8 finds in D_0035E710).  Read from the code, not proved by a
 * boot. */
#include "m2c.h"
#include "ppp.h"
#include "data/types/text_00180000_h12_p.h"
#include "data/pieces/D_0035E710.h"

extern volatile void *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern s32 D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
M2C_UNK memset(s32, M2C_UNK, s32);
s32 func_0017f958(s32, s32);
M2C_UNK func_00183b20(s32, s32);
M2C_UNK func_0019e3f0(s32);
M2C_UNK func_0019e710(s32);
M2C_UNK func_0019ea58(s32);
s32 func_0019e028(void *, void *);
s32 func_0019e108(void *, void *);
s32 func_0019e1e8(void *, void *);

PppTblEnt *func_0019dfc8(s32 key) {
    PppTblEnt *e = D_0035E710.ent;
    PppTblEnt *r = NULL;
    s32 i;

    if (e != NULL) {
        for (i = 0; i < D_0035E710.hdr->n; i++, e++) {
            if (key == e->key) {
                r = e;
                break;
            }
        }
    }
    return r;
}

void pppRyjMegaPlaceFrame(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    void *temp_a0;
    void *temp_s0;

    temp_a0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
    temp_s0 = temp_a0 + 0xA0;
    if (M2C_FIELD(temp_s0, s32 *, 0xC) == 0) {
        temp_v0 = M2C_FIELD(temp_a0, s32 *, 0xA0);
        if (temp_v0 != 0) {
            temp_v0_2 = func_0017f958(D_00615E64, temp_v0 << 5);
            M2C_FIELD(temp_s0, s32 *, 0xC) = temp_v0_2;
            memset(temp_v0_2, 0, M2C_FIELD(temp_a0, s32 *, 0xA0) << 5);
        }
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x10) == 0) {
        temp_a1 = M2C_FIELD(temp_s0, s32 *, 4);
        if (temp_a1 != 0) {
            temp_v0_3 = func_0017f958(D_00615E64, temp_a1 << 5);
            M2C_FIELD(temp_s0, s32 *, 0x10) = temp_v0_3;
            memset(temp_v0_3, 0, M2C_FIELD(temp_s0, s32 *, 4) << 5);
        }
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x14) == 0) {
        temp_v1 = M2C_FIELD(temp_s0, s32 *, 8);
        if (temp_v1 != 0) {
            temp_v0_4 = func_0017f958(D_00615E64, temp_v1 * 0x30);
            M2C_FIELD(temp_s0, s32 *, 0x14) = temp_v0_4;
            memset(temp_v0_4, 0, M2C_FIELD(temp_s0, s32 *, 8) * 0x30);
        }
    }
}

void pppRyjMegaPlaceDraw(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC) + 0xA0;
    func_0019e3f0(temp_s0);
    func_0019e710(temp_s0);
    func_0019ea58(temp_s0);
}

void pppRyjMegaPlaceCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x14) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x10) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0xC) = 0;
    M2C_FIELD(D_00615E60, s8 *, 0xB3) = 1;
    M2C_FIELD(D_00615E60, s8 *, 0xB0) = 1;
}

void pppRyjMegaPlaceDes(s32 arg0, PppEntry *arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 0xC);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 0x10);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
    }
    temp_a1_2 = M2C_FIELD(temp_s0, s32 *, 0x14);
    if (temp_a1_2 != 0) {
        func_00183b20(D_00615E64, temp_a1_2);
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
    }
}

void pppRyjMegaPlaceShapeFrame(void *obj, void *k, PppEntry *e) {
    u8 *w = (u8 *) obj + e->offsets[1] + 0xA0;

    if (*w == 0) {
        if (func_0019e028((u8 *) obj + e->offsets[0] + 0xA0, k))
            *w = 1;
    }
}

void pppRyjMegaPlaceShapeCon(s32 arg0, void *arg1) {
  void *temp_v1;
  s8 *new_var;
  void *temp_a0;
  temp_v1 = *((void **) (((s8 *) arg1) + 0xC));
  temp_a0 = arg0 + (*((s32 *) (((s8 *) temp_v1) + 0)));
  *((s8 *) (((s8 *) (arg0 + (*((s32 *) (((s8 *) temp_v1) + 4))))) + 0xA0)) = 0;
  new_var = ((s8 *) temp_a0) + 0xA0;
  *((s32 *) new_var) = (s32) ((*((s32 *) (((s8 *) temp_a0) + 0xA0))) + 1);
}

void pppRyjMegaPlaceModelFrame(void *obj, void *k, PppEntry *e) {
    u8 *w = (u8 *) obj + e->offsets[1] + 0xA0;

    if (*w == 0) {
        if (func_0019e108((u8 *) obj + e->offsets[0] + 0xA0, k))
            *w = 1;
    }
}

void pppRyjMegaPlaceModelCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg1, void **, 0xC);
    temp_a0 = arg0 + M2C_FIELD(temp_v1, s32 *, 0) + 0xA0;
    M2C_FIELD((arg0 + M2C_FIELD(temp_v1, s32 *, 4)), s8 *, 0xA0) = 0;
    M2C_FIELD(temp_a0, s32 *, 4) = (s32) (M2C_FIELD(temp_a0, s32 *, 4) + 1);
}

void pppRyjMegaPlaceLampFrame(void *obj, void *k, PppEntry *e) {
    u8 *w = (u8 *) obj + e->offsets[1] + 0xA0;

    if (*w == 0) {
        if (func_0019e1e8((u8 *) obj + e->offsets[0] + 0xA0, k))
            *w = 1;
    }
}

void pppRyjMegaPlaceLampCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg1, void **, 0xC);
    temp_a0 = arg0 + M2C_FIELD(temp_v1, s32 *, 0) + 0xA0;
    M2C_FIELD((arg0 + M2C_FIELD(temp_v1, s32 *, 4)), s8 *, 0xA0) = 0;
    M2C_FIELD(temp_a0, s32 *, 8) = (s32) (M2C_FIELD(temp_a0, s32 *, 8) + 1);
}

