/* Placeholder access macros for functions matched straight from m2c output
 * (tools/autodecomp.py) before their structs are known. Replace them with
 * real struct fields as the types get recovered; they compile to the same
 * code. Written for kh1-decomp; names follow m2c's --valid-syntax output. */
#ifndef KH1_M2C_H
#define KH1_M2C_H

#include "common.h"
#include "platform/math.h"

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* *(type_ptr)((char *)expr + offset) */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
/* Reinterpret the bits (float <-> int), through memory like fdlibm's
 * GET_FLOAT_WORD / SET_FLOAT_WORD unions. */
#define M2C_BITWISE(type, expr) \
    ({ union { __typeof__(expr) m2c_from; type m2c_to; } m2c_u; m2c_u.m2c_from = (expr); m2c_u.m2c_to; })

#endif /* KH1_M2C_H */
