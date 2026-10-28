/* ~3 real instructions differ (56 words shown due to shift): extra move a1,v0 (e lands in a1); permuter found nothing */
typedef struct { u8 pad[0x18]; f32 v[4]; s32 flag; f32 len; } N3f998;
typedef struct { u8 pad[4]; s32 n; N3f998 e[1]; } M3f998;
typedef struct { u8 pad[0xA0]; s32 xa0; u8 pada4[12]; f32 lo[3]; f32 hi[3]; } E3f998;
s32 func_00f64c10(s32);
E3f998 *func_00f64c38(s32, s32);
M3f998 *func_00f650f0(s32);

static inline f32 vlen_3f998(f32 *v) {
    return PlatSqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void func_00f3f998(s32 arg0) {
    s32 n, i, j;
    E3f998 *e;
    M3f998 *m;
    N3f998 *p;
    f32 c[4];
    f32 h[4];
    n = func_00f64c10(arg0);
    for (i = 0; i < n; i++) {
        e = func_00f64c38(i, arg0);
        c[0] = (e->hi[0] + e->lo[0]) * 0.5f;
        c[1] = (e->hi[1] + e->lo[1]) * 0.5f;
        c[2] = (e->hi[2] + e->lo[2]) * 0.5f;
        h[0] = fabsf(e->hi[0] - e->lo[0]) * 0.5f;
        h[1] = fabsf(e->hi[1] - e->lo[1]) * 0.5f;
        h[2] = fabsf(e->hi[2] - e->lo[2]) * 0.5f;
        e->lo[0] = c[0];
        e->lo[1] = c[1];
        e->lo[2] = c[2];
        e->hi[0] = h[0];
        e->hi[1] = h[1];
        e->hi[2] = h[2];
        if (e->xa0 > 0) {
            m = func_00f650f0(0);
            p = m->e;
            for (j = 0; j < m->n; j++, p++) {
                if (p->flag) {
                    p->len = vlen_3f998(p->v);
                } else {
                    p->len = p->v[0];
                }
            }
        }
    }
}
