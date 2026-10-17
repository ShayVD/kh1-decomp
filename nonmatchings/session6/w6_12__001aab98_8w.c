/* rodata (string at 0x48FE30); 8 words off in mode hand/nostrict (test: tools/matching/wqb03_rr.py 0048fe30): only the last (n6) block allocates count/t/v to a3/a0/a2 instead of a2/a3/a0. */
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
void func_001aab98(Oef *d, Oef *s) {
    s32 i;
    s32 *src;
    if ((u32)s & 0xF) {
        printf("op_oef2_set error : \x83\x66\x81\x5b\x83\x5e\x83\x41\x83\x68\x83\x8c\x83\x58\x82\xaa 16 byte align \x82\xb3\x82\xea\x82\xc4\x82\xa2\x82\xdc\x82\xb9\x82\xf1\n");
        exit(1);
    }
    if (s->n1) {
        R4 *t;
        src = (s32 *)(s->o1 + (s32)s);
        t = (R4 *)(d->o1 + (s32)d);
        for (i = 0; i < s->n1; i++, t++) {
            s32 v = *src++;
            if (v) t->p = v + (s32)s;
        }
    }
    if (s->n2) {
        R32 *t;
        src = (s32 *)(s->o2 + (s32)s);
        t = (R32 *)(d->o2 + (s32)d);
        for (i = 0; i < s->n2; i++, t++) {
            s32 v = *src++;
            if (v) t->p = v + (s32)s;
        }
    }
    if (s->n3) {
        R16 *t;
        src = (s32 *)(s->o3 + (s32)s);
        t = (R16 *)(d->o3 + (s32)d);
        for (i = 0; i < s->n3; i++, t++) {
            s32 v = *src++;
            if (v) t->p = v + (s32)s;
        }
    }
    if (s->n4) {
        R4 *t;
        src = (s32 *)(s->o4 + (s32)s);
        t = (R4 *)(d->o4 + (s32)d);
        for (i = 0; i < s->n4; i++, t++) {
            s32 v = *src++;
            if (v) t->p = v + (s32)s;
        }
    }
    if (s->n5) {
        R4 *t;
        src = (s32 *)(s->o5 + (s32)s);
        t = (R4 *)(d->o5 + (s32)d);
        for (i = 0; i < s->n5; i++, t++) {
            s32 v = *src++;
            if (v) t->p = v + (s32)s;
        }
    }
    if (s->n6) {
        R4 *t;
        src = (s32 *)(s->o6 + (s32)s);
        t = (R4 *)(d->o6 + (s32)d);
        for (i = 0; i < s->n6; i++, t++) {
            s32 v = *src++;
            if (v) t->p = v + (s32)s;
        }
    }
}

