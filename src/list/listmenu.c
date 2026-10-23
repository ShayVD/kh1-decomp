/* The list menu (docs/modules.md "Session 44"), 0x002327b0-0x00232ad0.
 * func_002329a0(menu, on_cursor, on_choice) opens it by itself
 * (D_003F7EC4 = 1, the task func_00232960; D_003F7EC8 = 1 lets the list
 * take input): the window D_003F7EA0 sized from the menu's corners, drawn
 * by func_002327b0 (the title, then 12 rows of the menu's n entries from
 * the scroll position).  The hooks D_006476F8 / D_006476FC get the cursor
 * every frame / on the choice.  src/list/list.c fills D_003DC498 and opens
 * it; func_00232aa8 closes the window (D_0064770C).  func_00232ac8 is
 * empty (src/game/gamedata.c calls it). */
#include "common.h"
#include "list/listmenu.h"
#include "text/textwin.h"

extern ListMenuDesc D_003F7EA0;
extern s32 D_003F7EC4;
extern s32 D_003F7EC8;
extern void (*D_006476F8)(s32);   /* src/data/bss_0064.c: s32 D_006476F8 */
extern void (*D_006476FC)(s32);   /* src/data/bss_0064.c: s32 D_006476FC */
extern ListMenu *D_00647700;      /* src/data/bss_0064.c: u16 *D_00647700 */
extern u8 *D_00647704;
extern char *D_00647708;          /* src/data/bss_0064.c: s32 D_00647708 */
extern void *D_0064770C;   /* the window; TextWin * moves its address into s1 in func_002329a0 */

void func_0010ea70(s32, s32, void *);
s16 *func_0011ef10(s32, void *);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f3840(void *);
s32 func_001f40c8(void);
s32 func_001f42b8(void *);
s32 func_001f4390(void);
void func_001f82b0(void);
void func_001f8e18(void *);
void func_001f8f30(void);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858(void *);
void func_001fe180(void *);
s32 func_001fe570(void *);
void func_001fea38(void *);
void func_002040c8(void *);

void func_002327b0(TextWin *a0) {
    s32 x, y, k, n;
    s32 i, y0;
    a0->xcc = *(u16 *)D_00647700;
    if (func_001f42b8(a0) != 0) {
        if (D_003F7EC8 != 0) {
            func_001fd858(a0);
            if (func_001fe570(a0) != 0) {
                D_003F7EC8 = 0;
                if (D_006476FC != 0) D_006476FC(func_001fd548(a0));
            }
        } else {
            func_001fe180(a0);
        }
    }
    if (func_001f4390 != 0) {
        x = ((a0->xb0 - 0x7000) >> 4) + 28;
        y0 = (a0->xb4 - 0x7400) >> 4;
        func_0010ea70(x, y0 + 40, D_00647708);
        func_001fea38(a0);
        func_002040c8(a0);
        i = func_001fd618(a0);
        n = a0->xcc;
        y = y0 + func_001fd590(a0);
        func_001f8e18(a0);
        for (k = 11; k >= 0; k--) {
            if (i < n) func_0010ea70(x, y, D_00647704 + i * 32);
            i++;
            y += 24;
        }
        func_001f8f30();
    }
    if (D_006476F8 != 0) D_006476F8(func_001fd548(a0));
}

s32 func_00232960(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        return 0;
    }
    D_003F7EC4 = 0;
    return 4;
}

void func_002329a0(ListMenu *arg0, void (*arg1)(s32), void (*arg2)(s32)) {
    u32 x, y;
    s32 w;
    func_001f3110();
    D_003F7EC4 = 1;
    D_003F7EC8 = 1;
    D_00647700 = arg0;
    D_006476F8 = arg1;
    D_006476FC = arg2;
    D_00647704 = (u8 *)arg0->str;
    D_00647708 = arg0->last;
    x = (arg0->a - 0x7000) >> 4;
    y = (arg0->b - 0x7400) >> 4;
    w = ((arg0->c - 0x7000) >> 4) - x;
    D_003F7EA0.x10 = w + 1;
    D_003F7EA0.x12 = ((arg0->d - 0x7400) >> 4) - y + 1;
    D_003F7EA0.x18 = w - 39;
    D_003F7EA0.xc = x;
    D_003F7EA0.xe = y;
    D_0064770C = func_001f31a8(&D_003F7EA0, 0);
    func_0011ef10(0x2C01A, func_00232960);
}

void func_00232aa8(void) {
    func_001f3840(D_0064770C);
}

void func_00232ac8(void) {

}

#include "data/data_003F.h"
#include "data/pieces/D_003F7EA0.h"
