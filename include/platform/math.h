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
#define PlatSqrtf(x) __builtin_sqrtf(x)
#endif

#endif /* KH1_PLATFORM_MATH_H */
