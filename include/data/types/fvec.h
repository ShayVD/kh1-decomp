/* The float 4-vector of the vector data pieces and of the files that pass them
 * to the vector routines (session 29: D_002C58A0, D_002C58B0, D_002E2780,
 * D_002E2790; the files' own V4 / V4f / FVec4 types alias it). */
#ifndef KH1_DATA_TYPES_FVEC_H
#define KH1_DATA_TYPES_FVEC_H

#include "common.h"

typedef struct {
    f32 x, y, z, w;
} FVec4;

#endif /* KH1_DATA_TYPES_FVEC_H */
