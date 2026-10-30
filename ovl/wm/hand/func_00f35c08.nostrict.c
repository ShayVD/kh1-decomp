/* wm.x func_00f35c08: matched by hand. */
#include "ovl.h"

typedef struct { f32 x; u8 type; u8 pad5; u16 flags; u8 kind; u8 id; u8 pad[0x2A]; f32 f34; } Ev35c08;
typedef struct { u8 pad[0x540]; s32 f540; u8 pad2[0xC]; f32 f550; s32 f554; } P35c08;
int abs(int);
s32 func_00f62b90(s32);
Ev35c08 *func_00f62b98(s32, s32);
extern P35c08 *D_00F864C0;

s32 func_00f35c08(s32 *out) {
    s32 dist[8];
    s32 cnt = 0;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 d;
    Ev35c08 *e;
    s32 id;
    u8 *p;

    n = func_00f62b90(D_00F864C0->f540);
    for (i = 0; i < n; i++) {
        e = func_00f62b98(i, D_00F864C0->f540);
        if (e == NULL || e->type != 1 || (e->flags & 1) || e->f34 != 0.0f) {
            continue;
        }
        if (D_00F864C0->f554 == 0 ? e->x < D_00F864C0->f550 : D_00F864C0->f550 < e->x) {
            continue;
        }
        d = abs((s32)e->x - (s32)D_00F864C0->f550);
        if (d > 100) {
            continue;
        }
        p = &e->kind;
        if (p[0] != 5) {
            continue;
        }
        for (j = 0; j < cnt && d >= dist[j]; j++) {
        }
        for (k = cnt; k > j; k--) {
            out[k] = out[k - 1];
            dist[k] = dist[k - 1];
        }
        id = p[1];
        dist[j] = d;
        out[j] = id;
        cnt++;
        e->flags |= 1;
    }
    return cnt;
}
