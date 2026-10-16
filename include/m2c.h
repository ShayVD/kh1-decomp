/* Placeholder access macros for functions matched straight from m2c output
 * (tools/autodecomp.py) before their structs are known. Replace them with
 * real struct fields as the types get recovered; they compile to the same
 * code. Written for kh1-decomp; names follow m2c's --valid-syntax output. */
#ifndef KH1_M2C_H
#define KH1_M2C_H

#include "common.h"

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* *(type_ptr)((char *)expr + offset) */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))

#endif /* KH1_M2C_H */
