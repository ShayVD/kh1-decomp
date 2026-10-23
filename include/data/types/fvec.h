/* The float 4-vector of the vector data pieces and of the files that pass them
 * to the vector routines (session 29: D_002C58A0, D_002C58B0, D_002E2780,
 * D_002E2790; the files' own V4 / V4f / FVec4 types alias it), and the 4x4
 * matrix (session 30). */
#ifndef KH1_DATA_TYPES_FVEC_H
#define KH1_DATA_TYPES_FVEC_H

#include "common.h"

typedef struct {
    f32 x, y, z, w;
} FVec4;

/* The float 4x4 matrix of the matrix routines (sceVu0*Matrix, func_00267768 /
 * func_00267810 ...), as their callers pass it: f32 (*)[4] (session 30: the
 * identity matrix D_002C58D0 and c04's M4 locals). */
typedef f32 FMtx4[4][4];

#endif /* KH1_DATA_TYPES_FVEC_H */
