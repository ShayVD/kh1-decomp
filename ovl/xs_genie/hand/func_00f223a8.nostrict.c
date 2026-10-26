/* xs_genie.x func_00f223a8: matched by hand. */
#include "ovl.h"

typedef struct {
    f32 start;
    f32 end;
    s32 a;
    s32 b;
    void (*on_start)(s32, s32);
    s32 (*on_update)(s32, s32);
    void (*on_end)(s32, s32);
} Ev;
typedef struct { s32 active; s32 pad; s32 started; } St;
typedef struct { f32 t; s32 n; s32 remaining; St st[16]; Ev *ev; } Seq;
s32 func_00f223a8(Seq *s, f32 dt) {
    s32 i;
    s32 done;
    St *st;
    Ev *ev;
    if (s->remaining == 0) {
        return 1;
    }
    st = s->st;
    ev = s->ev;
    for (i = 0; i < s->n; i++, st++, ev++) {
        done = 0;
        if (st->active == 0) {
            continue;
        }
        if (s->t < ev->start) {
            continue;
        }
        if (st->started == 0) {
            st->started = 1;
            if (ev->on_start) {
                ev->on_start(ev->a, ev->b);
            }
        }
        if (ev->on_update) {
            done = ev->on_update(ev->a, ev->b);
        }
        if (ev->end != -1.0f && ev->end <= s->t) {
            done = 1;
        }
        if (done) {
            if (ev->on_end) {
                ev->on_end(ev->a, ev->b);
            }
            st->active = 0;
            if (--s->remaining == 0) {
                return 1;
            }
        }
    }
    s->t += dt;
    return 0;
}
