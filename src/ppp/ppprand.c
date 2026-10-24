/* The ppp random-value classes' adders, default flags (docs/modules.md
 * "Session 50"): each returns amp * r - amp (or amp * r for the Up / Down
 * classes) for a random number r drawn by the frames in ppprand.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "ppp.h"
#include "data/pieces/D_00370130.h"

/* func_00187df0 (from auto/text_00180000.c). */
f32 func_00187df0(f32 fparg0, f32 fparg1) {
    return (fparg0 * fparg1) - fparg0;
}

/* func_00187f98 (from auto/text_00180000.c). */
f32 func_00187f98(f32 fparg0, f32 fparg1) {
    return fparg0 * fparg1;
}

/* func_00188148 (from auto/text_00180000.c). */
f32 func_00188148(f32 fparg0, f32 fparg1) {
    return fparg0 * fparg1;
}

/* func_00188498 (from auto/text_00180000.c). */
s32 func_00188498(s32 arg0, f32 fparg0) {
    return (s32) ((f32) arg0 * fparg0);
}

/* func_00188640 (from auto/text_00180000.c). */
s32 func_00188640(s32 arg0, f32 fparg0) {
    return (s32) ((f32) arg0 * fparg0);
}

/* func_001887e8 (from auto/text_00180000.c). */
s8 func_001887e8(s8 arg0, f32 fparg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    return (s8) (s32) ((temp_f0 * fparg0) - temp_f0);
}

/* func_001889b0 (from auto/text_00180000.c). */
s8 func_001889b0(s8 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

/* func_00188b78 (from auto/text_00180000.c). */
s8 func_00188b78(s8 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

/* func_00188d40 (from auto/text_00180000.c). */
s16 func_00188d40(s16 arg0, f32 fparg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    return (s16) (s32) ((temp_f0 * fparg0) - temp_f0);
}

/* func_00188f08 (from auto/text_00180000.c). */
s16 func_00188f08(s16 arg0, f32 fparg0) {
    return (s16) (s32) ((f32) arg0 * fparg0);
}

/* func_001890d0 (from auto/text_00180000.c). */
s16 func_001890d0(s16 arg0, f32 fparg0) {
    return (s16) (s32) ((f32) arg0 * fparg0);
}

/* func_00189298 (from auto/text_00180000.c). */
f32 func_00189298(f32 fparg0, f32 fparg1) {
    return (fparg0 * fparg1) - fparg0;
}

/* func_00189468 (from auto/text_00180000.c). */
f32 func_00189468(f32 fparg0, f32 fparg1) {
    return fparg0 * fparg1;
}

/* func_00189640 (from auto/text_00180000.c). */
f32 func_00189640(f32 fparg0, f32 fparg1) {
    return fparg0 * fparg1;
}

/* func_00189818 (from auto/text_00180000.c). */
s8 func_00189818(s8 arg0, f32 fparg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    return (s8) (s32) ((temp_f0 * fparg0) - temp_f0);
}

/* func_00189a18 (from auto/text_00180000.c). */
s8 func_00189a18(s8 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

/* func_00189c20 (from auto/text_00180000.c). */
s8 func_00189c20(s8 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

/* func_00189e28 (from auto/text_00180000.c). */
s8 func_00189e28(s16 arg0, f32 fparg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    return (s8) (s32) ((temp_f0 * fparg0) - temp_f0);
}

/* func_0018a028 (from auto/text_00180000.c). */
s8 func_0018a028(s16 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

/* func_0018a230 (from auto/text_00180000.c). */
s8 func_0018a230(s16 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

