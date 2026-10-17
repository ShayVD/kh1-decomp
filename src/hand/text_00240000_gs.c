/* A flags word at +0x60 followed by three 20-byte sub-states at +0x64,
 * +0x78 and +0x8C, each ending in a flags word (+0x74, +0x88, +0x9C).
 * func_0024ae00/func_0024ae90 only match with these callees defined above
 * them in the same file (session 5, worker 26). */
#include "common.h"

typedef struct { s32 a; s32 b; u8 pad[8]; u32 flags; } GsSub;
typedef struct {
    u8 pad[0x60];
    u32 flags;
    GsSub s64;
    GsSub s78;
    GsSub s8c;
} Gs;

void func_0024a088(Gs *g) {
    g->flags |= 8;
    g->s64.flags |= 2;
}

void func_0024a0a8(Gs *g) {
    g->s64.flags = 0;
    g->flags &= ~8;
}

void func_0024a0c0(Gs *g) {
    GsSub *s = &g->s64;
    s->b = 0;
    s->a = 0;
    s->flags &= ~4;
}

void func_0024a2e0(Gs *g) {
    GsSub *s = &g->s78;
    s->b = 0;
    s->a = 0;
    s->flags &= ~4;
}

void func_0024a450(Gs *g) {
    g->flags |= 0x80;
    g->s78.flags |= 2;
}

void func_0024a470(Gs *g) {
    g->s78.flags = 0;
    g->flags &= ~0x80;
}

void func_0024a568(Gs *g) {
    GsSub *s = &g->s8c;
    s->b = 0;
    s->a = 0;
    s->flags &= ~4;
}

void func_0024a678(Gs *g) {
    g->flags |= 0x10;
    g->s8c.flags |= 2;
}

void func_0024a698(Gs *g) {
    g->s8c.flags = 0;
    g->flags &= ~0x10;
}

void func_0024ae00(Gs *g) {
    if (g->flags & 4) { func_0024a568(g); func_0024a678(g); }
    if (g->flags & 2) { func_0024a0c0(g); func_0024a088(g); }
    if (g->flags & 0x40) { func_0024a2e0(g); func_0024a450(g); }
}

void func_0024ae90(Gs *g) {
    if (g->flags & 4) func_0024a698(g);
    if (g->flags & 2) func_0024a0a8(g);
    if (g->flags & 0x40) func_0024a470(g);
}
