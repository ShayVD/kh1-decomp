/* Shared basic types for kh1-decomp. Keep this header free of PS2-specific
 * declarations so it can be reused unchanged by the Vita port. */
#ifndef KH1_COMMON_H
#define KH1_COMMON_H

typedef unsigned char      u8;
typedef signed char        s8;
typedef unsigned short     u16;
typedef signed short       s16;
typedef unsigned int       u32;
typedef signed int         s32;
typedef unsigned long      u64; /* EE ABI: long is 64-bit */
typedef signed long        s64;
typedef float              f32;

#ifndef NULL
#define NULL 0
#endif

/* Build targets: KH1_PS2 for the matching build (default), KH1_VITA later. */
#if !defined(KH1_VITA) && !defined(KH1_PS2)
#define KH1_PS2 1
#endif

#endif /* KH1_COMMON_H */
