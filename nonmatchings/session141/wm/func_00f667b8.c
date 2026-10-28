/* score 93: DMA tag + vertex packet; load order of the float globals and constant materialisation order differ. */
#include "ovl.h"

typedef struct {
    s32 w0;
    s32 addr;
    s32 w8;
    s32 wC;
} Tag;

typedef struct {
    s32 hdr[3];
    f32 v[12];
    s32 tail;
} Pkt;

extern s32 D_0108EEC0;
extern s32 D_0108EEC4;
extern f32 D_0108EEC8;
extern f32 D_0108EECC;
extern f32 D_0108EED0;
extern f32 D_0108EED4;
extern Pkt D_0108EFF0;

Tag *func_00f667b8(Tag *t, s32 addr, s32 qwc) {
    Pkt *p = &D_0108EFF0;
    f32 hw = (f32)D_0108EEC0 * 0.5f;
    f32 hh = (f32)D_0108EEC4 * 0.5f;
    f32 a = D_0108EECC;
    f32 b = D_0108EEC8;
    f32 c = D_0108EED0;
    f32 d = D_0108EED4;
    f32 *v;

    p->hdr[0] = 0x13000000;
    p->hdr[1] = 0x01000404;
    p->hdr[2] = 0x6C0303FA;
    p->tail = 0;
    t->w0 = 0x30000004;
    t->addr = (s32)p;
    t->w8 = 0;
    t->wC = 0;
    t++;
    t->w0 = qwc | 0x30000000;
    t->addr = addr;
    t->w8 = 0;
    t->wC = 0;
    t++;
    v = p->v;
    v[0] = 2048.0f - hw;
    v[1] = 2048.0f - hh;
    v[2] = 0;
    v[3] = a;
    v[4] = hw + 2048.0f;
    v[5] = hh + 2048.0f;
    v[6] = 0;
    v[7] = b;
    v[8] = b;
    v[9] = c;
    v[10] = d;
    v[11] = a;
    t->w0 = 0x70000000;
    t->addr = 0;
    t->w8 = 0;
    t->wC = 0;
    return t;
}
