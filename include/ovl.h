/* Common header for the EE overlays' hand-written C (ovl/<name>/, docs/overlays.md). */
#ifndef KH1_OVL_H
#define KH1_OVL_H

#include "common.h"
#include "platform/vu.h"
#include "m2c.h"  /* M2C_FIELD: fields of structs not recovered yet */

/* libvu0's vector and matrix, quadword aligned (as the game's own V4 types are). */
typedef f32 OvlVec[4] __attribute__((aligned(16)));
typedef f32 OvlMtx[4][4] __attribute__((aligned(16)));

#endif
