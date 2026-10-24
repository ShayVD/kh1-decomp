/* A named parameter list reader (docs/modules.md "Session 47"),
 * 0x0024ba28-0x0024bc68.  A list is a run of entries ended by a zero word:
 * a name's length, the name padded to words, a type, a count and the
 * values (D_0046A070 the size of each type).  func_0024ba28 copies value
 * idx of the named entry and returns its type (-1 when not found or out of
 * range); func_0024bb88 (an f32), func_0024bbc8 (an s32) and func_0024bc08
 * (a list of requests, ended by a NULL destination) stop at a BREAK when a
 * name is missing.  Its own file by the code order; who builds the lists
 * is not yet known. */
#include "common.h"
#include "platform/thread.h"
#include "data/data_0046.h"

#define BREAK() PlatBreak()

typedef struct { void *dst; s32 id; } Req;

s32 strlen(const char *);
s32 memcmp(const void *, const void *, s32);

s32 func_0024ba28(s32 *p, char *name, s32 idx, u8 *out) {
    s32 len = strlen(name);
    s32 n, w, type, cnt, sz;
    u8 *src, *dst;
    for (;;) {
        n = *p++;
        if (n == 0) return -1;
        w = (n + 3) / 4;
        if (len == n && memcmp(p, name, n) == 0) {
            p += w;
            type = *p++;
            cnt = *p++;
            sz = D_0046A070[type];
            if (idx >= cnt) return -1;
            src = (u8 *)p + idx * sz;
            dst = out;
            if (sz > 0) do { *dst++ = *src++; } while (--sz);
            return type;
        }
        p += w;
        type = *p++;
        cnt = *p++;
        sz = D_0046A070[type];
        w = (sz * cnt + 3) / 4;
        p += w;
    }
}

void func_0024bb88(s32 *list, char *name, f32 *out) {
    f32 v;
    if (func_0024ba28(list, name, 0, (u8 *)&v) < 0) {
        BREAK();
    }
    *out = v;
}

void func_0024bbc8(s32 *list, char *name, s32 *out) {
    s32 v;
    if (func_0024ba28(list, name, 0, (u8 *)&v) < 0) {
        BREAK();
    }
    *out = v;
}

void func_0024bc08(s32 *list, Req *r) {
    while (r->dst != 0) {
        if (func_0024ba28(list, (char *)r->id, 0, r->dst) < 0) {
            BREAK();
        }
        r++;
    }
}
