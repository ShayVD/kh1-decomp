/* 48 words left (round 12): 42-case condition switch over func_00f353a8 stats. Left: t-register numbering off by one (sum lives in a2 in the target), case 43 gives xori where the target has sltiu, and a bnezl at the loop end. */
typedef struct { s32 h[5]; s16 n; s16 m; s16 cnt[192]; s16 best[192]; } R2ba68;
typedef struct { u16 type; u16 val; u16 c; u16 d; } E2ba68;
typedef struct { u8 pad[4]; u16 h4; u16 h6; E2ba68 e[8]; } A2ba68;
typedef struct { s32 w[9]; } P2ba68;
s32 func_001bb2e0(s32);
A2ba68 *func_00f2b9a0(s32, s32);
s32 func_00f2b9e8(A2ba68 *);
void func_00f353a8(R2ba68 *);
s32 func_001baf08(P2ba68 *);
s32 func_001baf38(P2ba68 *);
void func_001bb218(s32, s32);
void func_001ba358(s32, s32);

A2ba68 *func_00f2ba68(s32 id, P2ba68 *p) {
    R2ba68 r;
    A2ba68 *a;
    u16 *v;
    s32 n;
    s32 lvl;
    s32 x;
    s32 sum;
    s32 i;
    s32 ok;

    n = func_001bb2e0(id);
    a = func_00f2b9a0(id, n);
    if (a == NULL) return 0;
    if (!func_00f2b9e8(a)) return 0;
    func_00f353a8(&r);
    lvl = func_001baf08(p);
    x = func_001baf38(p);
    for (i = 0; i < 8; i++) {
        if (a->e[i].type == 0) continue;
        v = &a->e[i].val;
        ok = 0;
        sum = r.cnt[58];
        sum += r.cnt[59];
        sum += r.cnt[60];
        sum += r.cnt[61];
        sum += r.cnt[62];
        sum += r.cnt[63];
        sum += r.best[58];
        sum += r.best[59];
        sum += r.best[60];
        sum += r.best[61];
        sum += r.best[62];
        sum += r.best[63];
        switch (a->e[i].type) {
        case 2: if (!(lvl < *v)) ok = 1; break;
        case 3: if (!(p->w[0] < *v)) ok = 1; break;
        case 4: if (!(p->w[1] < *v)) ok = 1; break;
        case 5: if (!(x < *v)) ok = 1; break;
        case 6: if (!(p->w[2] < *v)) ok = 1; break;
        case 7: if (!(p->w[3] < *v)) ok = 1; break;
        case 8: if (!(p->w[4] < *v)) ok = 1; break;
        case 9: if (!(p->w[5] < *v)) ok = 1; break;
        case 10: if (!(p->w[6] < *v)) ok = 1; break;
        case 11: if (!(p->w[7] < *v)) ok = 1; break;
        case 18: if (!(*v < lvl)) ok = 1; break;
        case 19: if (!(*v < p->w[0])) ok = 1; break;
        case 20: if (!(*v < p->w[1])) ok = 1; break;
        case 21: if (!(*v < x)) ok = 1; break;
        case 22: if (!(*v < p->w[2])) ok = 1; break;
        case 23: if (!(*v < p->w[3])) ok = 1; break;
        case 24: if (!(*v < p->w[4])) ok = 1; break;
        case 25: if (!(*v < p->w[5])) ok = 1; break;
        case 26: if (!(*v < p->w[6])) ok = 1; break;
        case 27: if (!(*v < p->w[7])) ok = 1; break;
        case 32: if (p->w[8] == *v) ok = 1; break;
        case 33: if (sum == r.cnt[*v] + r.best[*v]) ok = 1; break;
        case 34: if (((s32 *)&r)[33] == 0) ok = 1; break;
        case 35: if (((s32 *)&r)[28] == 0 && ((s32 *)&r)[29] == 0) ok = 1; break;
        case 36: if (r.h[4] == 0) ok = 1; break;
        case 37: if (r.h[2] == 0) ok = 1; break;
        case 38: if (!(*v < r.n)) ok = 1; break;
        case 39: if (!(r.m < *v)) ok = 1; break;
        case 41: if (!(r.h[0] + r.h[1] < *v)) ok = 1; break;
        case 42: if (!(r.h[1] < *v)) ok = 1; break;
        case 43: ok = !(*v < r.h[3]); break;
        }
        if (!ok) return 0;
    }
    func_001bb218(id, n + 1);
    if (a->h4 != 0) {
        func_001ba358(a->h4, a->h6);
    }
    return a;
}
