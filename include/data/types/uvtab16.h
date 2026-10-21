/* The UV tables D_002A3F60 / D_002A4060: 16 entries of 4 floats, read as fields
 * (h28, s6_00: .a .b), as float rows (s8_w5) and copied as ints (b00)
 * (phase 4, session 26). */
#ifndef KH1_DATA_TYPES_UVTAB16_H
#define KH1_DATA_TYPES_UVTAB16_H

#include "common.h"
#include "data/types/text_00100000_s6_00.h"

typedef union { V4f v[16]; f32 f[16][4]; s32 i[4][4][4]; } UvTab16;

#endif /* KH1_DATA_TYPES_UVTAB16_H */
