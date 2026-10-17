#include "common.h"
typedef struct {
    u8 pad[8]; s32 x8; u8 padc[8]; s16 w; s16 h;
    u64 tex;
    u8 pad20[0x10];
} GsTexHdr;
typedef struct { u8 pad[0x10]; GsTexHdr h; u8 data[1]; } GsTex;
typedef struct { u64 a[6]; } Pkt6;
s32 FlushCache(s32);
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsSyncPath(s32, s32);
void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_00237018(void *, s32, s32);
void func_00249dc8(GsTex *t, s32 sync) {
    u8 li[0x60];
    Pkt6 pk;
    GsTexHdr *h = &t->h;
    u8 *d = t->data;
    if (h->x8) {
        sceGsSetDefLoadImage(li, (u16)(h->tex & 0x3fff), (u16)((h->tex >> 14) & 0x3f), (u16)((h->tex & 0x3f00000) >> 20), 0, 0, h->w, h->h);
        FlushCache(0);
        sceGsSyncPath(0, 0);
        sceGsExecLoadImage(li, d);
    }
    sceGsSyncPath(0, 0);
    pk.a[2] = 0x1000000000008001ULL;
    pk.a[3] = 0xe;
    pk.a[5] = 0x3f;
    pk.a[4] = 0;
    func_00237018(&pk, 3, 1);
    if (sync) sceGsSyncPath(0, 0);
}
