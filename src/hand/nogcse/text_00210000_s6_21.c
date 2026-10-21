#include "common.h"
#include "data/bss_0064.h"
typedef struct { u8 pad[0x32]; u8 x32; } B32;
extern s32 D_003F34C0;
extern s32 D_003F34C8;
extern s32 D_00641BA8;
extern B32 *D_00641BB0; /* src/data/bss_0064.c: s32 D_00641BB0 */
extern s32 D_00641BE0[];
extern s32 D_00641BF0[];
extern s32 D_00641C04;
void func_00211718(void);
s32 func_001f4390(void);
void func_00149f10(s32, void (*)(void));
void func_001ef830(void);
void func_001f36b8(s32);
typedef struct { u8 pad[0x599]; u8 x599[48]; } P599;
extern P599 *D_00304BE8;
extern s32 D_00642C88;

void func_00211738(s32 a0) {
    s32 n;
    if (func_001f4390() == 0) return;
    if (D_00641C04 != 0) return;
    if (D_00641BE0[n = D_00641BA8] != D_00641BF0[n]) {
        D_00641C04 = 1;
        D_003F34C8++;
        func_00149f10(D_00641BF0[n], func_00211718);
        n = D_00641BA8;
        D_00641BE0[n] = D_00641BF0[n];
    }
    D_00641BB0->x32 = D_00641BF0[n];
    func_001ef830();
    func_001f36b8(a0);
    D_003F34C0 &= ~2;
}

void func_00214f50(void) {
    s32 i;
    P599 *p = D_00304BE8;
    D_00642C88 = 0;
    i = 0;
    if (p->x599[i]) {
        D_00642C88 = 1;
        for (;;) {
            i++;
            if (i >= 48 || !D_00304BE8->x599[i]) return;
            D_00642C88++;
        }
    }
}
#include "data/data_003F.h"
#include "data/pieces/D_003F34C8.h"
