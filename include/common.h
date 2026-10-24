/* Shared basic types for kh1-decomp. Keep this header free of PS2-specific
 * declarations so it can be reused unchanged by the Vita port. */
#ifndef KH1_COMMON_H
#define KH1_COMMON_H

/* Build targets: KH1_PS2 for the matching build (default), KH1_VITA for the
 * port, KH1_HOST for the -m32 desktop build (docs/vita-port-plan.md section 5:
 * gcc / clang -m32 -malign-double, so pointers are 32 bits and long long
 * aligns to 8 as on the EE and the Vita). */
#if !defined(KH1_VITA) && !defined(KH1_HOST) && !defined(KH1_PS2)
#define KH1_PS2 1
#endif

typedef unsigned char      u8;
typedef signed char        s8;
typedef unsigned short     u16;
typedef signed short       s16;
typedef unsigned int       u32;
typedef signed int         s32;
#if defined(KH1_N32) || !defined(KH1_PS2)
/* src/hand/n32*: -mabi=n32 makes long 32-bit (kh1.toml); so do the Vita and
 * the -m32 host */
typedef unsigned long long u64;
typedef signed long long   s64;
#else
typedef unsigned long      u64; /* EE ABI: long is 64-bit */
typedef signed long        s64;
#endif
typedef float              f32;

/* 128-bit EE registers (lq / sq copies). gcc on 32-bit ARM / x86 has no
 * 128-bit integer, so off the EE it is a 16-byte struct: copies and
 * assignments work, arithmetic does not compile (docs/vita-port-plan.md). */
#ifdef KH1_PS2
typedef int kh1_s128 __attribute__((mode(TI)));
typedef unsigned int kh1_u128 __attribute__((mode(TI)));
#else
typedef struct { u32 w[4]; } kh1_s128 __attribute__((aligned(16)));
typedef kh1_s128 kh1_u128;
#endif

#ifndef NULL
#define NULL 0
#endif

/* CONTEXT_ONLY: a copy of a function whose real definition lives elsewhere
 * (or is not matched yet), defined above its callers only so gcc 2.96 sees
 * its register use while compiling them (the callee-earlier effect,
 * docs/context-only-plan.md). The build never places it; calls resolve to the
 * original address. Must not be static. */
#define CONTEXT_ONLY __attribute__((weak, section(".ctx")))

/* Alignment of a variable defined in C (phase 4): DMA packets and VU data need
 * 16 bytes (qword), wherever the shiftable build puts them. */
#define ALIGNED(n) __attribute__((aligned(n)))

#endif /* KH1_COMMON_H */
