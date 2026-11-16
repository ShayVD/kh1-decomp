/* Platform wrapper: float maths the game inlines. See docs/portability.md.
 *
 * KH1 takes square roots with a bare `sqrt.s` (49 of the 53 in the ELF have
 * no NaN check, which a call to sqrtf would add), so the original source
 * used an inline: PlatSqrtf reproduces it on the PS2 build. */
#ifndef KH1_PLATFORM_MATH_H
#define KH1_PLATFORM_MATH_H

#include "common.h"

#ifdef KH1_PS2
static inline f32 PlatSqrtf(f32 x) {
    f32 r;
    __asm__ volatile("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}
#else
/* The EE's `sqrt.s` of a negative number is the root of its magnitude (the FPU has no NaN; it only raises the
 * invalid flag), and the game leans on it: the script library's jump (vm_lib.c func_001d2c68) takes
 * sqrt(height + drop), negative when the landing point lies further below than the jump is high, and the IEEE
 * root's NaN went into the jump's speed and from there into the entity's position (the port's Destiny Islands:
 * the second morning's first event, the player's position a NaN from then on and the picture black).
 * platform/vu.h's PlatVu0Sqrt does the same for the VU's root. */
static __inline__ f32 PlatSqrtf(f32 x) { return __builtin_sqrtf(__builtin_fabsf(x)); }
#endif

#endif /* KH1_PLATFORM_MATH_H */
