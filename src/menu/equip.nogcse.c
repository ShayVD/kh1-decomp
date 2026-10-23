/* The equipment page (src/menu/equip.c; docs/modules.md "Session 40"):
 * func_00211738 closes the weapon list.  When the chosen weapon (D_00641BF0)
 * is not the one the party model holds (D_00641BE0) it loads it
 * (func_00149f10, callback func_00211718), then equips it in the member's
 * Sub_304be8 (+0x32).  It needs -fno-gcse (was
 * src/hand/nogcse/text_00210000_s6_21.c). */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003F34C8.h"

extern s32 D_003F34C0;
extern Sub_304be8 *D_00641BB0;
extern s32 D_00641BE0[], D_00641BF0[];
extern s32 D_00641C04;

void func_00149f10(s32, void (*)(void));
void func_001ef830(void);
void func_001f36b8(void *);
s32 func_001f4390(void);
void func_00211718(void);

void func_00211738(void *a0) {
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
