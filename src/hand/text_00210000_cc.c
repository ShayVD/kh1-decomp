/* func_0021f900 only matches with its callee func_0021f410 defined above it. */
#include "common.h"
#include "data/bss_0064.h"
typedef struct {
    u8 pad[0xA0];
    f32 xa0;
    u8 pada4[0xCA - 0xA4];
    s16 xca;
    s16 xcc;
    u8 padce[4];
    s16 xd2;
    u8 padd4[4];
    s16 xd8;
    s16 xda;
} Obj410;
extern u8 D_003F5EF0[];
extern u8 D_003F5EC0[];
extern u8 D_003F5E90[];
extern u16 D_003E9104;
extern s32 D_0064324C;
extern s32 D_00643200[];
extern s32 D_00643258[];
extern s32 D_00643268[];
Obj410 *func_001f31a8(u8 *, s32);
void func_001f3e48(Obj410 *, void *);

void func_0021f410(void *a) {
    Obj410 *o[3];
    if (!(o[0] = func_001f31a8(D_003F5EF0, 50))) return;
    o[0]->xa0 = D_003E9104;
    func_001f3e48(o[0], a);
    if (!(o[1] = func_001f31a8(D_003F5EC0, 50))) return;
    func_001f3e48(o[1], o[0]);
    o[1]->xa0 = o[0]->xa0;
    if (!(o[2] = func_001f31a8(D_003F5E90, 50))) return;
    func_001f3e48(o[2], o[1]);
    o[2]->xa0 = o[0]->xa0;
    if (D_00643200[D_0064324C] / 8 * 8 < D_00643258[D_0064324C] * 8) D_00643258[D_0064324C] = 0;
    if (D_00643200[D_0064324C] < D_00643258[D_0064324C] * 8 + D_00643268[D_0064324C]) D_00643268[D_0064324C] = 0;
    o[2]->xca = D_00643200[D_0064324C];
    o[2]->xda = D_00643258[D_0064324C] << 4;
    o[2]->xd8 = (D_00643200[D_0064324C] + 7) / 8;
    if (D_00643200[D_0064324C] < 8 || D_00643258[D_0064324C] == o[2]->xd8 - 1) o[2]->xcc = (D_00643200[D_0064324C] - 1) % 8 + 1;
    else o[2]->xcc = 8;
    o[2]->xd2 = D_00643268[D_0064324C] << 4;
}

extern s32 D_00643114;
s32 func_001f42b8(void *);
void func_0021f858(void *);

void func_0021f900(void *a) {
    s32 *p;
    if (!func_001f42b8(a)) return;
    p = &D_00643114;
    if (*p == 0) {
        func_0021f858(a);
        return;
    }
    func_0021f410(a);
    *p = 0;
}
#include "data/bss_0064_mixed.h"
