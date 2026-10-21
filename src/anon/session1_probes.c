/* Session 1 compiler-identification probes (docs/toolchain.md). Original
 * source files unknown, so these live in src/anon/ until placed. */

typedef struct {
    char pad0[128];
    int f80;
    int f84;
    char pad1[10];
    unsigned char f92;
    unsigned char f93;
} S10EF70;

void func_0010ef70(S10EF70 *s, int a, int b)
{
    s->f80 = b;
    s->f84 = a;
    s->f93 &= ~1;
    s->f92 = 0;
}

extern int D_004D925C;
extern int D_002BCC24;

void func_00111f70(void)
{
    D_004D925C = 0;
    D_002BCC24 = 0;
}

int func_001882f8(int a, float f)
{
    return (float)a * f - (float)a;
}

typedef struct {
    char pad0[384];
    int count;
    int list[1];
} S1D5F80;

extern int D_0038CE04;

int func_001d5f80(S1D5F80 *s)
{
    s->count++;
    s->list[s->count] = D_0038CE04;
    return 2;
}

void func_0018ad70(int a, int *p)
{
    p[2] = 0;
    p[1] = 0;
    p[0] = 0;
    p[3] = a;
}

int func_002466e8(int a)
{
    int v = a / 2;
    if (v > 150)
        v = 150;
    return v;
}

typedef struct {
    int flags;
    char pad0[1184];
    float inv;
} S137418;

void func_00137418(S137418 *s, float x)
{
    s->flags |= 0x18;
    s->inv = 1.0f / x;
}

int func_0023d1e0(float x)
{
    return x / 0.7853981f; /* original constant is 0x3F490FD9 */
}
#include "data/bss_004D_mixed.h"
#include "data/data_0038.h"
#include "data/pieces/D_002BCC24.h"
