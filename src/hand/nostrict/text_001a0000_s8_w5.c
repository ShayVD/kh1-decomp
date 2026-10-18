#include "common.h"
typedef struct { s32 p; } R4;
typedef struct { u8 pad[20]; s32 p; u8 pad2[8]; } R32;
typedef struct { s32 a; s32 p; u8 pad[8]; } R16;
typedef struct {
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    s32 o4;
    u8 pad14[0xC];
    s32 o5;
    s32 o6;
    u8 pad28[0x1A];
    u16 n1;
    u16 n2;
    u16 n3;
    u16 n4;
    u8 pad4a[6];
    u16 n5;
    u16 n6;
} Oef;
s32 printf(const char *, ...);
void exit(s32);
/* rodata (string at 0x0048fe30; verified with wqb03_rr.py 0048fe30) */
void func_001aab98(Oef *d, Oef *s) {
    s32 i;
    s32 *src;
    R4 *t4;
    R32 *t32;
    R16 *t16;
    if ((u32)s & 0xF) {
        printf("op_oef2_set error : \x83\x66\x81\x5b\x83\x5e\x83\x41\x83\x68\x83\x8c\x83\x58\x82\xaa 16 byte align \x82\xb3\x82\xea\x82\xc4\x82\xa2\x82\xdc\x82\xb9\x82\xf1\n");
        exit(1);
    }
#define LOOP(N, O, T, TY) \
    if (s->N) { \
        src = (s32 *)(s->O + (s32)s); \
        T = (TY *)(d->O + (s32)d); \
        for (i = 0; i < s->N; i++, T++) { \
            s32 v = *src++; \
            if (v) T->p = v + (s32)s; \
        } \
    }
    LOOP(n1, o1, t4, R4)
    LOOP(n2, o2, t32, R32)
    LOOP(n3, o3, t16, R16)
    LOOP(n4, o4, t4, R4)
    LOOP(n5, o5, t4, R4)
    LOOP(n6, o6, t4, R4)
}
