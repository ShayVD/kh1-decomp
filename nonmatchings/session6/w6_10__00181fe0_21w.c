/* func_00181fe0 (nostrict): ~21 words off. Orig loop is not rotated: 'b test; L: e++ (move v1,s0; addiu s0,v1,192); test: slti i,256; beqz exit; i++ (slot); ld/and flags; bnez L'. Every for/while form here gets rotated by gcc; goto forms lose the hoisted 0x3000000000000 constant. */
#include "common.h"
typedef struct E0C0 {
    u8 pad0[0x80];
    u64 x80;
    u8 pad88[0xc0 - 0x88];
} E0C0;
extern E0C0 D_00364130[256];
void func_00181f50(E0C0 *);

void func_00181fe0(E0C0 **out) {
    s32 i = 0;
    E0C0 *e = D_00364130;
    while (i++ < 256) {
        if (!(e->x80 & 0x3000000000000)) {
            func_00181f50(e);
            *out = e;
            break;
        }
        e++;
    }
}
