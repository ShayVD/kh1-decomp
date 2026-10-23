/* Screen image effects (docs/modules.md "Session 34"), 0x001e0ab0-0x001e2748.
 *
 * The frame captured to / loaded from the 512x384 RGB buffer D_00F20000
 * (sceGsExecStoreImage / LoadImage), drawn back as a sprite (frame.c's
 * func_001e05a8 with the packets D_003DAE40 / D_003DAF60 / D_003DB050):
 * the cross-fades of func_001e0ab0 .. func_001e10f8, the tint fade
 * func_001e15a0, the ripple func_001e1838 and the edge filter func_001e1c20
 * (screen.nofill.c), "image/<name>_<n>.rgb" (func_001e24c8), and the script
 * functions and library calls that start them.  The data D_003DACB0-
 * D_003DB070 and the bss D_0062F640-D_0062F6D0 are theirs alone and follow
 * the event voices' D_003DACA0 / the effects' D_0062A640; the code after
 * 0x001e2748 works on D_002BBBA0 / D_0062F760 instead. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "data/bss_0062.h"
#include "data/data_003D.h"
#include "data/pieces/D_003DABD0.h"
#include "data/pieces/D_003DACC0.h"
#include "data/pieces/D_003DAD3C.h"

extern VmMgr D_00389C90;
extern u64 D_0038CD00;
extern s32 D_0062F670;      /* the image transfer record */
extern u8 D_00F20000[];     /* the 512x384 RGB frame */

s32 func_0011ef10(s32, void *);
s32 FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsExecStoreImage(void *, void *);
s32 func_002660c0(void *, s32, s32, s32, s32, s32, s32, s32);

/* func_001e05a8 .. func_001e08d8 are in frame.c. */
void func_001e05a8(void *);
void func_001e0608(void);
void func_001e07a8(s32);
s32 func_001e0898(void);
s32 func_001e08d8(void);

/* The three cross-fades (s11_w55; FLAGGED dead test: each has
 * `if (t == (s32)&TIMER) { REST } else { REST }` with identical arms right
 * after the `t <= 0` early return.  The test is never true and generates no
 * code: jump2 cross-jumps the arms and deletes the branch, but flow2's
 * live_at_start of the bgtz target block already includes t's register
 * (v0), so reorg's steal_delay_list_from_fallthrough may not move `li v0,4`
 * from the `b` slot into the bgtz slot, as in the original).  Their frame
 * counter and the two alphas: */
s32 D_0062F640 ALIGNED(16);
s32 D_0062F644 ALIGNED(4);
s32 D_0062F648 ALIGNED(8);
s32 D_0062F64C ALIGNED(4);
s32 D_0062F650 ALIGNED(16);
s32 D_0062F654 ALIGNED(4);
s32 D_0062F664 ALIGNED(4);
s32 D_0062F668 ALIGNED(8);
s32 D_0062F66C ALIGNED(4);

/* Cross-fade from the captured frame over D_0062F6D0 frames. */
s32 func_001e0ab0(void) {
    f32 f;
    switch (D_003DB060) {
    case 0:

        D_0062F640 = D_0062F6D0;
        D_0062F644 = 0;
        D_0062F648 = 128;
        D_003DB060 = 1;

    case 1:
        break;
    default:
        goto ret0;
    }
    /* t == (s32)&D_0062F640 is never true: a dead test with identical arms. jump2
       cross-jumps the arms and deletes the test, but flow2 already counted the read of
       t (v0) at the bgtz target, so reorg cannot steal `li v0,4` into the bgtz slot. */
    {
        s32 t = D_0062F640;
        if (t <= 0) {
            D_003DB060 = 0;
            return 4;
        }
        if (t == (s32)&D_0062F640) {
        func_001e0608();
        D_003DAE40[15] = (u64)D_0062F644 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F648 << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_0062F640--;
        f = (f32)D_0062F640 / (f32)D_0062F6D0 * 128.0f;
        D_0062F648 = f;
        D_0062F644 = 128.0f - f;
            } else {
        func_001e0608();
        D_003DAE40[15] = (u64)D_0062F644 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F648 << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_0062F640--;
        f = (f32)D_0062F640 / (f32)D_0062F6D0 * 128.0f;
        D_0062F648 = f;
        D_0062F644 = 128.0f - f;
            }
    }
ret0:
    return 0;
}

/* Start it over arg0 frames (vm_lib's func_001d2468). */
void func_001e0d68(s32 arg0) {
    D_0062F6D0 = arg0;
    func_0011ef10(0x2E630, func_001e0ab0);
}

/* The same from the image D_003DABD0[1]. */
s32 func_001e0d98(void) {
    f32 f;
    switch (D_003DB064) {
    case 0:
        D_0062F64C = D_0062F6D0;
        D_0062F650 = 0;
        D_0062F654 = 128;
        D_003DB064 = 1;
    case 1:
        break;
    default:
        goto ret0;
    }
    /* t == (s32)&D_0062F64C is never true: a dead test with identical arms. jump2
       cross-jumps the arms and deletes the test, but flow2 already counted the read of
       t (v0) at the bgtz target, so reorg cannot steal `li v0,4` into the bgtz slot. */
    {
        s32 t = D_0062F64C;
        if (t <= 0) {
            D_003DB064 = 0;
            return 4;
        }
        if (t == (s32)&D_0062F64C) {
        func_001e07a8(0);
        D_003DAE40[22] = 0x8000000664020E00ULL;
        D_003DAE40[15] = (u64)D_0062F650 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F654 << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_003DAE40[22] = 0x8008000264120E00ULL;
        D_0062F64C--;
        f = (f32)D_0062F64C / (f32)D_0062F6D0 * 128.0f;
        D_0062F654 = f;
        D_0062F650 = 128.0f - f;
            } else {
        func_001e07a8(0);
        D_003DAE40[22] = 0x8000000664020E00ULL;
        D_003DAE40[15] = (u64)D_0062F650 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F654 << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_003DAE40[22] = 0x8008000264120E00ULL;
        D_0062F64C--;
        f = (f32)D_0062F64C / (f32)D_0062F6D0 * 128.0f;
        D_0062F654 = f;
        D_0062F650 = 128.0f - f;
            }
    }
ret0:
    return 0;
}

void func_001e1088(s32 arg0) {
    D_0062F6D0 = arg0;
    func_0011ef10(0x2E630, func_001e0d98);
}

/* Stop drawing the frame. */
s32 func_001e10b8(void) {
    D_003DAD38 = 0;
    return 4;
}

void func_001e10c8(s32 arg0) {
    D_0062F6D0 = arg0;
    func_0011ef10(0x2E630, func_001e10b8);
}

/* The same in the other direction. */
s32 func_001e10f8(void) {
    f32 f;
    switch (D_003DB06C) {
    case 0:
/*P*/
        D_0062F664 = D_0062F6D0;
        D_0062F668 = 128;
        D_0062F66C = 0;
        D_003DB06C = 1;
/*Q*/
    case 1:
        break;
    default:
        goto ret0;
    }
    /* t == (s32)&D_0062F664 is never true: a dead test with identical arms. jump2
       cross-jumps the arms and deletes the test, but flow2 already counted the read of
       t (v0) at the bgtz target, so reorg cannot steal `li v0,4` into the bgtz slot. */
    {
        s32 t = D_0062F664;
        if (t <= 0) {
            D_003DB06C = 0;
            return 4;
        }
        if (t == (s32)&D_0062F664) {
        func_001e07a8(0);
        D_003DAE40[22] = 0x8000000664020E00ULL;
        D_003DAE40[15] = (u64)D_0062F668 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F66C << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_003DAE40[22] = 0x8008000264120E00ULL;
        D_0062F664--;
        f = (f32)D_0062F664 / (f32)D_0062F6D0 * 128.0f;
        D_0062F668 = f;
        D_0062F66C = 128.0f - f;
            } else {
        func_001e07a8(0);
        D_003DAE40[22] = 0x8000000664020E00ULL;
        D_003DAE40[15] = (u64)D_0062F668 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F66C << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_003DAE40[22] = 0x8008000264120E00ULL;
        D_0062F664--;
        f = (f32)D_0062F664 / (f32)D_0062F6D0 * 128.0f;
        D_0062F668 = f;
        D_0062F66C = 128.0f - f;
            }
    }
ret0:
    return 0;
}

void func_001e13e8(s32 arg0) {
    D_0062F6D0 = arg0;
    func_0011ef10(0x2E630, func_001e10f8);
}

/* Offset (arg0, arg1) pixels and scale (arg0, arg1) percent of the frame
 * func_001e08d8 draws (vm_lib). */
void func_001e1418(s32 arg0, s32 arg1) {
    D_003DACB8 = arg0 * 0x10;
    D_003DACBC = arg1 * 0x10;
}

void func_001e1438(s32 arg0, s32 arg1) {
    D_003DACB0 = (f32) arg0 / 100.0f;
    D_003DACB4 = (f32) arg1 / 100.0f;
}

/* Capture the screen into D_00F20000. */
void func_001e1480(void) {
    s32 sp[28];
    func_002660c0(sp, 0x1A00, 8, 1, 0, 0, 0x200, 0x180);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecStoreImage(sp, &D_00F20000);
}

/* Load D_00F20000 back (as func_001e0608). */
void func_001e14e0(void) {
    sceGsSetDefLoadImage(&D_0062F670, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, &D_00F20000);
    sceGsSetDefLoadImage(&D_0062F670, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, (s8 *)&D_00F20000 + 0x48000);
}

/* Every frame: step the tint alpha D_003DACC0.d by D_003DACD0 (up to 128,
 * stop below 0), capture the screen, make it grey (green to all three) and
 * draw it tinted with D_003DACC0's colour. */
s32 func_001e15a0(void) {
    s32 i, j;
    u8 *p;
    D_003DACC0.d += D_003DACD0;
    if (D_003DACC0.d > 128) {
        D_003DACC0.d = 128;
    } else if (D_003DACC0.d < 0) {
        return 4;
    }
    {
        u64 r = (s64)D_003DACC0.a | 0x100000000LL;
        r |= (s64)D_003DACC0.c << 16 | (s64)D_003DACC0.b << 8;
        r |= (s64)D_003DACC0.d << 24;
        D_003DB028 = r;
    }
    func_001e1480();
    p = D_00F20000;
    for (i = 0; i < 384; i++) {
        for (j = 0; j < 512; j++) {
            p[2] = p[0] = p[1];
            p += 3;
        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}

void func_001e1688(void) {
    func_0011ef10(0x280A0, func_001e15a0);
}

/* h20's view of a VM from +4 (obj, then the stack at +0x180). */
typedef struct { struct VmObj *obj; u8 pad4[0x17c]; s32 stk[33]; } ScrVmSub;

/* The tint colour stk[sp-2..sp]. */
s32 func_001e16b0(VmRec *vm) {
    ScrVmSub *s = (ScrVmSub *)&vm->obj;
    u64 r;
    D_003DACC0.a = s->stk[vm->sp - 2];
    D_003DACC0.b = s->stk[vm->sp - 1];
    D_003DACC0.c = s->stk[vm->sp];
    r = (s64)D_003DACC0.a | 0x100000000LL; r |= (s64)D_003DACC0.c << 16 | (s64)D_003DACC0.b << 8; r |= (s64)D_003DACC0.d << 24;
    vm->sp -= 3; D_003DB028 = r;
    return 2;
}

/* Fade the tint in over stk[sp] frames (at once when 0). */
s32 func_001e1748(VmRec *vm) {
    s32 n = ((ScrVmSub *)&vm->obj)->stk[vm->sp];
    if (n > 0) {
        D_003DACD0 = 128 / n; D_003DACCC = 0;
    } else {
        D_003DACD0 = 0;
        D_003DACCC = 128;
    }
    func_0011ef10(0x280a0, func_001e15a0);
    vm->sp -= 1;
    return 2;
}

/* Fade it out over stk[sp] frames. */
s32 func_001e17e0(VmRec *vm) {
    s32 n = ((ScrVmSub *)&vm->obj)->stk[vm->sp];
    if (n > 0) {
        D_003DACD0 = -128 / n;
    } else {
        D_003DACD0 = -128;
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001e1838(void);
s32 func_001e1c20(void);

/* func_001e1838 is in screen.nofill.c. */

void func_001e1bf8(void) {
    func_0011ef10(0x280A0, func_001e1838);
}

/* func_001e1c20 is in screen.nofill.c. */

void func_001e2470(void) {
    func_0011ef10(0x280A0, func_001e1c20);
}

/* The image is loaded: clear bit 50 of f3070. */
void func_001e2498(void) {
    D_00389C90.f3070.x = D_00389C90.f3070.x & ~(1ULL << 50);
}

char *strcpy(char *, const char *);
char *strcat(char *, const char *);
int sprintf(char *, const char *, ...);
s32 func_00120748(void *, void *, void (*)(), s32);

/* Load image/<D_003DACD8[stk[sp-1]]>_<stk[sp]>.rgb into the frame (bit 50
 * of f3070 until it is in). */
s32 func_001e24c8(VmRec *vm) {
    char buf[256];
    char tmp[16];
    strcpy(buf, "image/");
    strcat(buf, D_003DACD8[vm->stk[vm->sp - 1]]);
    sprintf(tmp, "_%03d.rgb", vm->stk[vm->sp]);
    strcat(buf, tmp);
    func_00120748(buf, D_00F20000, func_001e2498, 0);
    D_00389C90.f3070.w.b50 = 1;
    vm->sp -= 2;
    return 2;
}

/* Wait until it is loaded (bit 50 of D_0038CD00). */
s32 func_001e25c8(VmRec *vm) {
    if ((s32)(D_0038CD00 >> 50) & 1) return 4;
    return 2;
}

/* Draw the frame every frame (func_001e0898 / func_001e08d8); stop. */
s32 func_001e25e8(void) {
    func_0011ef10(0x2E630, func_001e0898);
    D_003DAD3C = 0;
    D_003DAD38 = 1;
    return 2;
}

s32 func_001e2628(void) {
    func_0011ef10(0x2E630, func_001e08d8);
    D_003DAD3C = 0;
    D_003DAD38 = 1;
    return 2;
}

s32 func_001e2668(void) {
    D_003DAD38 = 0;
    return 2;
}

/* Every frame for D_003DAD44 frames: scroll D_003DAD3C by D_003DAD40. */
s32 func_001e2678(void) {
    s32 temp_v1;

    temp_v1 = D_003DAD44 - 1;
    D_003DAD44 = temp_v1;
    D_003DAD3C += D_003DAD40;
    return (temp_v1 > 0) ? 0 : 4;
}

/* Scroll to line stk[sp-1] over stk[sp] frames. */
s32 func_001e26b8(VmRec *vm) {
    ScrVmSub *s = (ScrVmSub *)&vm->obj;
    s32 i = vm->sp;
    f32 x = s->stk[i - 1], y = s->stk[i];
    D_003DAD44 = y;
    D_003DAD40 = (x - D_003DAD3C) / y;
    func_0011ef10(50000, func_001e2678);
    vm->sp -= 2;
    return 2;
}
