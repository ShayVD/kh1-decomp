/* Page 5's section 4 (D_003F5A00[4]; docs/modules.md "Session 42"),
 * 0x00223508-0x00223980.  Opener func_00223938 keeps the section's window in
 * D_006436C8; set up func_00223948 (D_003F5C28 = "not empty"), reset
 * func_00223978 (empty).
 *
 * func_00223508 lists the five entries func_001ec5d8(i) has (D_003F6828,
 * D_003F6854 of them) with a count each from func_001c0da0(D_003F6758[i],
 * D_003F6770[i], ...) into D_003F6840; D_003F5C30[4] (journal.c's "complete"
 * flags) once all five are there and each count reaches D_003F6740[i].
 * func_002236d0 draws them: an icon (journalfx.c's func_0021bbe0, picture
 * D_003F6788[i]), the name (message 0x2a + i) and "count / goal" (message
 * 47).  Not proved by a boot. */
#include "common.h"
#include "platform/pad.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E8E08.h"
#include "vm/script_vm.h"
#include "menu/journal.h"

extern s32 D_003F5C28;
extern s32 D_003F5C30[];
extern s32 D_003F6740[];
extern s32 D_003F6758[];
extern s32 D_003F6770[];
extern s32 D_003F6788[];
extern s32 D_003F6828[];
extern s32 D_003F6840[];
extern s32 D_003F6854;
extern u8 D_003F67A0[], D_003F67D0[];
JsWin *D_006436C8 ALIGNED(8);

void func_0011d768(s32);
s32 func_001ec5d8(s32);
void *func_001f31a8(void *, s32);
void func_001f3758(void *);
void func_001f3e48(void *, void *);
s32 func_001f42b8(void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
void func_002072e0(s32);
void func_0021af38(void *);
s32 func_0021b800(s32);
void func_0021b820(void);
void func_0021bbe0(void *, s32, s32, s32, s32, s32, s32);
void func_0021c9a0(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
void func_0021ccd0(void *, s32);

void func_00223508(void) {
    s32 i;
    D_003F6854 = 0;
    for (i = 0; i < 5; i++) {
        if (func_001ec5d8(i) != 0) {
            D_003F6828[D_003F6854] = i;
            func_001c0da0(D_003F6758[i], D_003F6770[i], &D_003F6840[D_003F6854]);
            D_003F6854++;
        }
    }
    D_003F5C30[4] = 0;
    if (D_003F6854 == 5) {
        for (i = 0; i < 5; i++) {
            if (D_003F6840[i] != D_003F6740[i]) return;
        }
        D_003F5C30[4] = 1;
    }
}

s32 func_00223638(s32 i) {
    return func_0021b800(i + 0x2A);
}

s32 func_00223650(s32 i) {
    return D_003F6788[i];
}

void func_00223668(JsWin *arg0) {
    if ((func_001f42b8(arg0) != 0) && (D_00425BC8->x8 & PAD_CROSS)) {
        func_001f3758(D_006436C8);
        func_0011d768(3);
    }
    func_0021b820();
    func_0021ccd0(arg0, 0xD);
    func_0021af38(arg0);
}

void func_002236d0(JsWin *a0) {
    s32 i, y, s;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 103, 11, 25);
    func_0021cb00(a0, 280, 103, 11, 25);
    y = 106;
    for (i = 0; i < D_003F6854; i++) {
        s = D_003F6828[i];
        func_0021bbe0(a0, 287, y, 0, 0, 30, func_00223650(s));
        func_001f94f0(a0, 0, 326, y + 4, func_00223638(s), 15, 0x80461e00);
        ((S4_3e8e08 *)D_003E8E08)->a = D_003F6840[i];
        ((S4_3e8e08 *)D_003E8E08)->b = D_003F6740[s];
        func_001f94f0(a0, 0, 391, y + 28, func_0021b800(47), 15, 0x80461e00);
        y += 50;
    }
}

void func_00223870(JsWin *arg0) {
    JsWin *h[2];
    h[0] = func_001f31a8(D_003F67D0, 50);
    if (h[0] != 0) {
        func_001f3e48(h[0], arg0);
        h[1] = func_001f31a8(D_003F67A0, 50);
        if (h[1] != 0) {
            func_001f3e48(h[1], h[0]);
        }
    }
}

void func_002238e0(JsWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        func_00223870(arg0);
    }
}

void func_00223920(void) {
    func_002072e0(4);
}

void func_00223938(JsWin *a) {
    D_006436C8 = a;
}

void func_00223948(void) {
    func_00223508();
    D_003F5C28 = D_003F6854 != 0;
}

void func_00223978(void) {

}
