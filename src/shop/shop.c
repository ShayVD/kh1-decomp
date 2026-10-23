/* The shops (docs/modules.md "Session 34"), 0x001e2748-0x001e4918.
 *
 * The buy / sell menus a script opens (func_001e3770 / func_001e38b0 with
 * the item lists D_003DB078 / D_003DB718, func_001e3dd0, func_001e4790 /
 * func_001e4868) and their windows: the item text in D_0062F6E0 (its text
 * at D_0062F760), the choice window D_0062F790 (D_0062F810) and D_0062F840,
 * three window records of 0xb0 bytes like the message windows' (MsgWin),
 * with the choice list D_0062F8F0 / D_0062F900, the name tables
 * D_0062FA00-D_0062FF00 and the replies D_003DBA68-D_003DC494.  That data
 * is theirs alone; it follows the screen effects' D_003DB070 / D_0062F6D0,
 * and the code after 0x001e4918 works on D_00630300.. / D_003DC498 instead. */
#include "common.h"
#include "vm/vm_sub.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "msgwin/msgwin.h"
#include "data/bss_0062.h"
#include "data/data_002B.h"
#include "data/data_003D.h"
#include "data/data_003F.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003DBA68.h"
#include "data/pieces/D_003DC2A8.h"
#include "data/pieces/D_003DC370.h"
#include "data/pieces/D_003DC390.h"
#include "data/pieces/D_003F7A68.h"

/* A choice list (func_0010f558): fn gets the index picked. */
typedef struct { s32 a; s32 n; void (*fn)(); s32 d; } ShopCb;
/* An entry of the item lists D_003DB078 / D_003DB718. */
typedef struct { s32 x0; s32 x4; u8 pad[0xcc]; } ShopList;
/* h45's view of a VM from +4 (obj, then the stack at +0x180). */

extern VmMgr D_00389C90;
extern u64 D_0038CD00;
extern s32 D_002C5BB8;
extern volatile s32 D_002C5958;
extern MsgWin D_0062F6E0;
extern MsgWin D_0062F790;
extern MsgWin D_0062F840;  /* src/data/bss_0062.c: u8 D_0062F840[0xb0] */
extern u8 D_0062F810[];    /* D_0062F790.f80 */
extern ShopCb D_0062F8F0;  /* src/data/bss_0062.c: Cb20 D_0062F8F0 */
extern u8 D_0062FA00[];
extern s32 D_0062FB00[];
extern s32 D_0062FF00[];
extern s32 D_003E1CB0;
extern s32 D_003E3700;
extern ShopList D_003DB078[];
extern ShopList D_003DB718[];

void func_0010bd90(void *, void *);
void func_0010bdd0(void *, void *);
void func_0010ef70(void *, void *, void *);
void func_0010e3f0(void *);
void func_0010f558(void *, void *, s32);
void func_0010f520(void);
void func_0011d768(s32);
s32 func_0011ef10(s32, void *);
void func_001ea128(void *, void *);
void func_001ea268(void *, void *);
void func_001c2d20(s8 *p, s32 *cnt, s8 **tbl);
void func_00231740(s32, void *, void (*)(), void (*)());
void func_00232640(void (*)(), void (*)());
void func_00232780(void);
void func_00232758(void);
void func_00231980(void);
void func_00231958(void);
void func_0022fc88(s32);
void func_0022fba8(void);
void func_00230f18(void);
void func_00230728(void);
s32 func_001ef7a0(void);
s32 func_001ba1e8(s32);
s32 func_0022ee08(void);
void func_0022eee0(s32);
void func_00231b98(void);

void func_001e2748(void);
void func_001e2778(void);
void func_001e27b0(void);
s32 func_001e2800(s32 arg0);
void func_001e2810(void);
s32 func_001e2920(void);
void func_001e2a30(s32 arg0);
void func_001e2a40(s32 a);
void func_001e2a88(void);
void func_001e2d08(void);
void func_001e2f88(s32 arg0);
void func_001e2f98(void);
void func_001e30f8(void);
s32 func_001e3178(void);
void func_001e31b0(void);
s32 func_001e31b8(void);
void func_001e32c8(s32 arg0);
void func_001e32d8(s32 a);
void func_001e3600(void);
void func_001e3728(void);
s32 func_001e3770(VmRec *vm);
s32 func_001e38b0(VmRec *vm);
void func_001e39f0(void);
void func_001e3a00(void);
void func_001e3a98(s32 arg0);
void func_001e3aa8(void);
void func_001e3b28(void);
s32 func_001e3b40(void);
void func_001e3c08(s32 arg0);
void func_001e3c70(s32 a);
void func_001e3da8(void);
s32 func_001e3dd0(VmRec *vm);
s32 func_001e3ed0(VmRec *vm);
void func_001e3ef0(s32 arg0);
void func_001e3f00(void);
void func_001e3f20(void);
void func_001e3fc8(void);
void func_001e4048(s32 arg0);
void func_001e4070(s32 r);
void func_001e4250(void);
void func_001e4268(void);
void func_001e42b0(void);
s32 func_001e4318(void);
void func_001e44e0(s32 arg0);
void func_001e4558(void);
void func_001e4578(void);
s32 func_001e4790(void);
s32 func_001e4868(void);

/* The choice window's list (h68). */
u8 D_0062F900[0x100] ALIGNED(64);

void func_001e2748(void) {
    D_002BBBA0 = 1;
    D_00389C90.f3070.x = D_00389C90.f3070.x | (0x8000ULL << 31);
}

void func_001e2778(void) {
    D_002BBBA0 = 0;
    D_00389C90.f3070.x &= ~0x400000000000LL;
}

void func_001e27b0(void) {
    s32 sp[4];
    func_001c2d20((s8 *) &D_003E1CB0, sp, (s8 **) D_0062FB00);
    func_001c2d20((s8 *) &D_003E3700, sp, (s8 **) D_0062FF00);
    D_0062FA00[0] = 0;
}

s32 func_001e2800(s32 arg0) {
    return (u32) (arg0 - 1) < 0x10U;
}

void func_001e2810(void) {
    s32 n = D_003DC470;
    if (n != D_003DC474 && n != 0) {
        {
            D_003DC474 = n;
            if (D_003DC478 == 0) {
                func_0010e3f0(D_0062F760);
                func_001ea128(D_0062FA00, D_003DC468);
                if (D_003DC494) {
                    func_001ea268(D_0062FA00, (void *)D_0062FF00[D_003DC470]);
                } else {
                    func_001ea268(D_0062FA00, (void *)D_0062FB00[D_003DC470]);
                }
                func_0010ef70(&D_0062F6E0, D_0062FA00, func_001e2810);
            } else {
                D_003DC47C = 0;
            }
        }
    }
}

s32 func_001e2920(void) {
    if (D_003DC478 == 0) return 4;
    if (--D_003DC47C < 0) {
        D_003DC478 = 0;
        if (D_003F7A68 == 1 && D_003DC470 != 0) {
            func_0010e3f0(D_0062F760);
            func_001ea128(D_0062FA00, D_003DC468);
            if (D_003DC494) {
                func_001ea268(D_0062FA00, (void *)D_0062FF00[D_003DC470]);
            } else {
                func_001ea268(D_0062FA00, (void *)D_0062FB00[D_003DC470]);
            }
            func_0010ef70(&D_0062F6E0, D_0062FA00, func_001e2810);
        }
        return 4;
    }
    return 0;
}

void func_001e2a30(s32 arg0) {
    D_003DC484 = arg0;
}

void func_001e2a40(s32 a) {
    if (a == 3) {
        if (!D_002E26A0[1]) a = 2;
        if (!D_002E26A0[2]) a = a - 1;
    }
    func_0022eee0(a);
}

void func_001e2a88(void) {
    s32 r;
    D_003DC478 = 1;
    D_003DC47C = 0x3C;
    func_0011ef10(0xC350, func_001e2920);
    D_003DC490 = 0;
    func_0010bd90(&D_0062F790, func_001e3f00);
    if (D_003DC488 == D_003DC484) {
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 0x80, D_003DBA68, func_001e2810);
        return;
    }
    if (D_003DC488 - 1 == D_003DC484) {
        func_001e2a40(3);
    } else {
        func_001e2a40(D_003DC484 - 1);
    }
    r = func_0022ee08();
    if (r == -1) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 0x80, D_003DC2A8, func_001e2810);
        return;
    } else if (r == -2) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 0x80, D_003DC370, func_001e2810);
        return;
    } else if (r == -3) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 0x80, D_003DC370, func_001e2810);
        return;
    } else if (r == -4) {
        if (D_003DC488 - 1 == D_003DC484) {
            func_0011d768(4);
            func_0010e3f0(D_0062F760);
            func_0010ef70(D_0062F760 - 0x80, D_003DC2E0, func_001e2810);
        return;
        } else {
            func_0011d768(4);
            func_0010e3f0(D_0062F760);
            func_0010ef70(D_0062F760 - 0x80, D_003DC318, func_001e2810);
        return;
        }
    } else {
        func_0010e3f0(D_0062F760);
        do { func_0010ef70(D_0062F760 - 0x80, D_003DC368, func_001e2810); } while (0);
    }
}

void func_001e2d08(void) {
    s32 n;
    s32 ok;
    D_003DC490 = 1;
    D_003DC488 = 0;
    n = 1;
    ok = func_001e2800(D_003DC480);
    func_001ea128(D_0062F900, D_003DC468);
    if (ok) {
        n = 2;
        func_001ea268(D_0062F900, D_003DC068[0]);
        D_003DC488++;
    }
    if (D_00304BE8->x48e[1] == 1 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC0A8);
        D_003DC488++;
    } else if (D_00304BE8->x48e[1] == 2 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC0E8);
        D_003DC488++;
    } else if (D_00304BE8->x48e[1] == 5 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC1A8);
        D_003DC488++;
    }
    if (D_00304BE8->x48e[2] == 1 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC0A8);
        D_003DC488++;
    } else if (D_00304BE8->x48e[2] == 2 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC0E8);
        D_003DC488++;
    } else if (D_00304BE8->x48e[2] == 5 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC1A8);
        D_003DC488++;
    }
    func_001ea268(D_0062F900, D_003DC128);
    D_003DC488++;
    func_001ea268(D_0062F900, D_003DC128 + 0x40);
    D_003DC488++;
    func_001ea268(D_0062F900, D_003DC460);
    func_0010ef70(&D_0062F790, D_0062F900, func_001e2a88);
    D_0062F8F0.a = 1;
    D_0062F8F0.n = D_003DC488;
    D_0062F8F0.fn = func_001e2a30;
    func_0010f558(&D_0062F8F0, &D_0062F790, n);
}

void func_001e2f88(s32 arg0) {
    D_003DC484 = arg0;
}

void func_001e2f98(void) {
    s32 d;
    D_003DC490 = 0;
    func_0010bd90(&D_0062F790, func_001e3f00);
    if (D_003DC484 != 1) return;
    if (D_003DC494 != 0) {
        func_00230728();
        d = func_001ef7a0();
        d -= func_001ba1e8(D_003DC480);
        if (d < 0) {
            func_0010e3f0(D_0062F760);
            func_0010ef70(D_0062F760 - 0x80, D_003DC2A8, func_001e2810);
        } else {
            func_0010e3f0(D_0062F760);
            func_0010ef70(D_0062F760 - 0x80, D_003DC368, func_001e2810);
        }
    } else {
        func_0022ee08();
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 0x80, D_003DC368, func_001e2810);
    }
    D_003DC478 = 1;
    D_003DC47C = 0x3C;
    func_0011ef10(0xC350, func_001e2920);
}

void func_001e30f8(void) {
    D_003DC490 = 1;
    func_0010ef70(&D_0062F790, D_003DC1E8, func_001e2f98);
    D_0062F8F0.a = 1;
    D_0062F8F0.n = 2;
    D_0062F8F0.fn = func_001e2f88;
    func_0010f558(&D_0062F8F0, &D_0062F790, 1);
}

s32 func_001e3178(void) {
    if (D_003F7A64 == 0) {
        func_001e2778();
        return 4;
    }
    return 0;
}

void func_001e31b0(void) {

}

s32 func_001e31b8(void) {
    if (D_002C5BB8 & 2) {
        s32 *p = &D_003DC490;
        if (*p == 0) return 0;
        func_0011d768(3);
        if (D_003F7A68 != 0) {
            D_003DC478 = 0;
            func_0010bd90(&D_0062F6E0, func_001e31b0);
            func_00231980();
            func_0011ef10(0xC350, func_001e3178);
            return 4;
        }
        if (D_003DC48C != 0) {
            *p = 0;
            func_0010bd90(&D_0062F790, func_001e3f00);
            func_0010f520();
            func_0010e3f0(D_0062F760);
            func_0010ef70(D_0062F760 - 0x80, D_003DBA68, func_001e2810);
            D_003DC478 = 1;
            D_003DC47C = 0x3C;
            func_0011ef10(0xC350, func_001e2920);
        }
    }
    return 0;
}

void func_001e32c8(s32 arg0) {
    D_003DC470 = arg0;
}

/* 001e32d8: one `*pD = 0` reached by goto from the first branch: pD 7 refs (not 8)
   drops its global-alloc priority below pC (s4/s5 order). */
void func_001e32d8(s32 a) {
    s32 v;
    s32 b = a;
    s32 one = 1;
    s32 *pA;
    s32 *pB;
    s32 *pC;
    s32 *pD;
    pA = &D_003F7A68;
    pB = &D_003DC478;
    pC = &D_003DC480;
    pD = &D_003DC48C;
    *pA = 0;
    *pB = 0;
    *pC = a;
    *pD = one;
    func_0011d768(2);
    if (D_003DC494) {
        if (a == -1) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2A8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; goto dz;
        } else if (a == -2) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2F8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; dz: *pD = 0;
        } else if (a == -3) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2F8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
        } else if (a == -4) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2F8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
        } else {
            D_0062F790.v40[1] = 1.5f;
            D_003DC490 = 0;
            func_0010bdd0(&D_0062F790, func_001e30f8);
            return;
        }
    } else if (a == -1) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2A8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
    } else if (a == -2 || b == -3 || a == -4) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC370, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
    } else {
        goto deflt;
    }
    return;
deflt:
    v = func_001e2800(*pC);
    D_0062F790.v40[1] = 1.5f;
    if (v) D_0062F790.v40[1] = 2.0f;
    if (D_002E26A0[1] && v) D_0062F790.v40[1] = 3.0f;
    if (D_002E26A0[2] && v) D_0062F790.v40[1] = 4.0f;
    D_003DC490 = 0;
    func_0010bdd0(&D_0062F790, func_001e2d08);
}

void func_001e3600(void) {
    D_0062F6E0.v30[0] = -130.0f;
    D_0062F6E0.v30[1] = 110.0f;
    D_0062F6E0.v40[0] = 8.0f;
    D_0062F6E0.v40[1] = 3.0f;
    D_0062F6E0.h4 = 2;
    D_0062F6E0.hc = 1;
    D_0062F6E0.he = 1;
    D_0062F6E0.h6 = 1;
    D_0062F6E0.h8 = 0;
    D_0062F6E0.b90 = 0;
    D_0062F6E0.f1c = 45.0f;
    D_0062F6E0.x0 = -1;
    D_0062F6E0.f94 = 0.0f;
    D_0062F790.v30[0] = -90.0f;
    D_0062F790.v30[1] = 90.0f;
    D_0062F790.v40[0] = 6.0f;
    D_0062F790.v40[1] = 4.0f;
    D_0062F790.h4 = 6;
    D_0062F790.hc = 1;
    D_0062F790.he = 1;
    D_0062F790.h6 = 0;
    D_0062F790.h8 = 0;
    D_0062F790.b90 = 0;
    D_0062F790.f1c = 45.0f;
    D_0062F790.x0 = -1;
    D_0062F790.f94 = 0.0f;
    D_0062F840.v30[0] = 0.0f;
    D_0062F840.v30[1] = -10.0f;
    D_0062F840.v40[0] = 3.0f;
    D_0062F840.v40[1] = 3.0f;
    D_0062F840.h4 = 6;
    D_0062F840.hc = 1;
    D_0062F840.he = 1;
    D_0062F840.h6 = 0;
    D_0062F840.h8 = 0;
    D_0062F840.b90 = 0;
    D_0062F840.f1c = 45.0f;
    D_0062F840.x0 = -1;
    D_0062F840.f94 = 0.0f;
    D_003DC470 = 0;
    D_003DC474 = 0;
}

void func_001e3728(void) {
    func_0010ef70(&D_0062F6E0, D_003DBA68, func_001e2810);
    D_003F7A68 = 1;
    D_003DC490 = 1;
}

s32 func_001e3770(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i;
    D_002C5958 |= 0xc;
    func_001e27b0();
    func_001e3600();
    func_0010bdd0(&D_0062F6E0, func_001e3728);
    func_00231740(0, &D_003DB078[s->stk[vm->sp]], func_001e32c8, func_001e32d8);
    D_003F7A68 = 0;
    D_003DC478 = 1;
    D_003DC47C = 60;
    func_0011ef10(0xc350, func_001e2920);
    func_0011ef10(0xc350, func_001e31b8);
    D_003DC494 = 0;
    D_003DC48C = 0;
    D_003DC490 = 0;
    func_001e2748();
    i = vm->sp;
    D_003DC470 = D_003DC474 = D_003DB078[s->stk[i]].x4;
    vm->sp = i - 1;
    return 2;
}

s32 func_001e38b0(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i;
    D_002C5958 |= 0xc;
    func_001e27b0();
    func_001e3600();
    func_0010bdd0(&D_0062F6E0, func_001e3728);
    func_00231740(2, &D_003DB718[s->stk[vm->sp]], func_001e32c8, func_001e32d8);
    D_003DC478 = 1;
    D_003DC47C = 60;
    func_0011ef10(0xc350, func_001e2920);
    func_0011ef10(0xc350, func_001e31b8);
    D_003F7A68 = 0;
    D_003DC494 = 1;
    D_003DC490 = 0;
    func_001e2748();
    i = vm->sp;
    D_003DC470 = D_003DC474 = D_003DB718[s->stk[i]].x4;
    vm->sp = i - 1;
    return 2;
}

void func_001e39f0(void) {
    D_003F7E98 = 1;
}

/* func_00231b98 takes no arguments; D_0062F810 written out in both branches (gcse hoists it). */
void func_001e3a00(void) {
    func_0010bd90(&D_0062F840, func_001e39f0);
    if (D_003DC484 == 1) {
        func_00231b98();
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 0x80, D_003DC3C0, 0);
    } else {
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 0x80, D_003DC390, 0);
    }
}

void func_001e3a98(s32 arg0) {
    D_003DC484 = arg0;
}

void func_001e3aa8(void) {
    D_003DC48C = 1;
    func_0010ef70(&D_0062F840, D_003DC268, func_001e3a00);
    D_0062F8F0.a = 1;
    D_0062F8F0.n = 2;
    D_0062F8F0.fn = func_001e3a98;
    func_0010f558(&D_0062F8F0, &D_0062F840, 1);
}

void func_001e3b28(void) {
    func_001e2778();
}

s32 func_001e3b40(void) {
    if (D_002C5BB8 & 2) {
        s32 *p;
        if (D_003F7E98) {
            func_00232758();
            func_0010bd90(&D_0062F790, func_001e3b28);
            func_0011d768(3);
            return 4;
        }
        p = &D_003DC48C;
        if (*p) {
            func_0010e3f0(D_0062F810);
            func_0010ef70(D_0062F810 - 0x80, D_003DC390, 0);
            func_0010bd90(&D_0062F840, func_001e39f0);
            func_0011d768(3);
            *p = 0;
        }
    }
    return 0;
}

void func_001e3c08(s32 arg0) {
    D_003DC470 = arg0;
    if (arg0 != D_003DC474) {
        D_003DC474 = arg0;
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 0x80, D_003DC390, 0);
    }
}

void func_001e3c70(s32 a) {
    if (a == -1) {
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 0x80, D_003DC3D0, 0);
        func_0011d768(4);
        return;
    }
    if (a == -2) {
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 0x80, D_003DC408, 0);
        func_0011d768(4);
        return;
    }
    if (a == -3) {
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 0x80, D_003DC428, 0);
        func_0011d768(4);
        return;
    }
    D_003F7E98 = 0;
    D_0062F840.v30[0] = 90.0f;
    D_0062F840.v30[1] = 140.0f;
    D_0062F840.v40[0] = 6.0f;
    D_0062F840.v40[1] = 1.5f;
    func_0010bdd0(&D_0062F840, func_001e3aa8);
    func_0011d768(2);
}

void func_001e3da8(void) {
    func_0010ef70(&D_0062F790, D_003DC390, 0);
}

s32 func_001e3dd0(VmRec *vm) {
    D_002C5958 |= 0xc;
    func_001e3600();
    D_003DC48C = 0;
    func_00232780();
    func_00232640(func_001e3c08, func_001e3c70);
    D_0062F790.v30[0] = 80.0f;
    D_0062F790.v30[1] = 150.0f;
    D_0062F790.v40[0] = 12.0f;
    D_0062F790.v40[1] = 1.8f;
    D_0062F790.h4 = 2;
    D_0062F790.h6 = 1;
    D_0062F790.h8 = 17;
    D_0062F790.f1c = 270.0f;
    func_0010bdd0(&D_0062F790, func_001e3da8);
    func_0011ef10(0xc350, func_001e3b40);
    func_001e2748();
    D_003DC474 = D_003DC470 = 0;
    vm->sp -= 1;
    return 2;
}

s32 func_001e3ed0(VmRec *vm) {
    if ((s32)(D_0038CD00 >> 46) & 1) return 4;
    return 2;
}

void func_001e3ef0(s32 arg0) {
    D_003DC484 = arg0;
}

void func_001e3f00(void) {
    D_003F7A68 = 1;
    D_003DC48C = 0;
    D_003DC490 = 1;
}

void func_001e3f20(void) {
    D_003DC490 = 0;
    func_0010bd90(&D_0062F790, func_001e3f00);
    if (D_003DC484 == 1) {
        if (D_003DC494) func_00230f18(); else func_0022fba8();
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 0x80, D_003DC368, 0);
    }
}

void func_001e3fc8(void) {
    D_003DC490 = 1;
    func_0010ef70(&D_0062F790, D_003DC228, func_001e3f20);
    D_0062F8F0.a = 1;
    D_0062F8F0.n = 2;
    D_0062F8F0.fn = func_001e3ef0;
    func_0010f558(&D_0062F8F0, &D_0062F790, 1);
}

void func_001e4048(s32 arg0) {
    D_003DC470 = arg0;
    if (D_003DC474 == 0) {
        D_003DC474 = arg0;
    }
}

void func_001e4070(s32 r) {
    if (r == -1) {
        func_0010ef70(&D_0062F6E0, D_003DC2B8, 0);
        func_0011d768(4);
        return;
    }
    if (r == -2) {
        if (D_003DC494 != 0) {
            func_0010ef70(&D_0062F6E0, D_003DC358, 0);
            func_0011d768(4);
            return;
        }
        func_0010ef70(&D_0062F6E0, D_003DC380, 0);
        func_0011d768(4);
        return;
    }
    if (r == -3) {
        if (D_003DC494 != 0) {
            func_0010ef70(&D_0062F6E0, D_003DC2C8, 0);
            func_0011d768(4);
            return;
        }
        if (D_003DC488 - 1 == D_003DC480) {
            func_0010ef70(&D_0062F6E0, D_003DC2C8, 0);
            func_0011d768(4);
            return;
        }
        func_0010ef70(&D_0062F6E0, D_003DC338, 0);
        func_0011d768(4);
        return;
    }
    func_0011d768(2);
    if (D_003DC494 != 0) {
        D_003DC490 = 0;
        D_003F7A68 = 0;
        D_003DC48C = 1;
        D_0062F790.v40[1] = 1.5f;
        func_0010bdd0(&D_0062F790, func_001e3fc8);
        return;
    }
    D_003DC490 = 0;
    D_003F7A68 = 0;
    D_0062F790.v40[1] = 1.5f;
    func_0010bdd0(&D_0062F790, func_001e3fc8);
}

void func_001e4250(void) {
    func_001e2778();
}

void func_001e4268(void) {
    D_003DC490 = 1;
    D_003F7A68 = 1;
    D_003DC48C = 0;
    func_0010ef70(&D_0062F6E0, &D_003DBD68, 0);
}

void func_001e42b0(void) {
    D_0062F790.v40[1] = 2.0f;
    if (D_002E26A0[1]) D_0062F790.v40[1] = 3.0f;
    if (D_002E26A0[2]) D_0062F790.v40[1] = 4.0f;
    func_0010bdd0(&D_0062F790, func_001e4578);
}

s32 func_001e4318(void) {
    if (!((D_0038CD00 >> 46) & 1)) return 4;
    if (D_002C5BB8 & 2) {
        s32 *p = &D_003DC490;
        if (*p == 0) return 0;
        func_0011d768(3);
        if (D_003DC494 != 0) {
            s32 *q = &D_003DC48C;
            if (*q != 0) {
                *p = 0;
                func_0010bd90(&D_0062F790, func_001e3f00);
                func_0010f520();
                D_003F7A68 = 0;
                *q = 0;
                return 0;
            }
            D_003DC478 = 0;
            func_0010bd90(&D_0062F6E0, 0);
            func_00231958();
            func_0011ef10(0xC350, func_001e3178);
            goto r4;
        } else {
            s32 *q = &D_003F7A68;
            if (*q != 0) {
                *p = 0;
                func_0010bd90(&D_0062F6E0, func_001e42b0);
                func_0022fc88(-1);
                *q = 0;
                D_003DC48C = 1;
                D_003DC478 = 0;
                goto r4;
            }
            if (D_003DC48C != 0) {
                D_003DC478 = 0;
                func_0010bd90(&D_0062F790, 0);
                func_0010f520();
                func_00231958();
                func_0011ef10(0xC350, func_001e3178);
                goto r4;
            }
            *p = 0;
            func_0010bd90(&D_0062F790, func_001e3f00);
            func_0010f520();
            return 0;
        }
r4:
        return 4;
    }
    return 0;
}

void func_001e44e0(s32 arg0) {
    D_003DC490 = 0;
    if (D_003DC488 == arg0) {
        func_001e2778();
        func_00231958();
        return;
    }
    D_003DC480 = arg0;
    func_0022fc88(arg0 - 1);
    func_0010bdd0(&D_0062F6E0, func_001e4268);
    D_003DC470 = 0;
    D_003DC474 = 0;
}

void func_001e4558(void) {
    func_0010bd90(&D_0062F790, 0);
}

void func_001e4578(void) {
    s32 n = 2;
    D_003DC488 = 0;
    D_003DC490 = 1;
    func_001ea128(D_0062F900, D_003DC468);
    func_001ea268(D_0062F900, D_003DC068[0]);
    D_003DC488++;
    if (D_00304BE8->x48e[1] == 1) {
        n++;
        func_001ea268(D_0062F900, D_003DC068[1]);
        D_003DC488++;
    } else if (D_00304BE8->x48e[1] == 2) {
        n++;
        func_001ea268(D_0062F900, D_003DC068[2]);
        D_003DC488++;
    } else if (D_00304BE8->x48e[1] == 5) {
        n++;
        func_001ea268(D_0062F900, D_003DC068[5]);
        D_003DC488++;
    }
    if (D_00304BE8->x48e[2] == 1) {
        n++;
        func_001ea268(D_0062F900, D_003DC0A8);
        D_003DC488++;
    } else if (D_00304BE8->x48e[2] == 2) {
        n++;
        func_001ea268(D_0062F900, D_003DC0E8);
        D_003DC488++;
    } else if (D_00304BE8->x48e[2] == 5) {
        n++;
        func_001ea268(D_0062F900, D_003DC1A8);
        D_003DC488++;
    }
    func_001ea268(D_0062F900, D_003DC128);
    D_003DC488++;
    func_001ea268(D_0062F900, D_003DC128 + 0x40);
    D_003DC488++;
    func_001ea268(D_0062F900, D_003DC460);
    func_0010ef70(&D_0062F790, D_0062F900, func_001e4558);
    D_0062F8F0.a = 1;
    D_0062F8F0.n = D_003DC488;
    D_0062F8F0.fn = func_001e44e0;
    func_0010f558(&D_0062F8F0, &D_0062F790, n);
    func_0011ef10(0xC350, func_001e4318);
}

s32 func_001e4790(void) {
    D_002C5958 |= 0xc;
    func_001e27b0();
    func_001e3600();
    D_0062F790.v40[1] = 2.0f;
    if (D_002E26A0[1]) D_0062F790.v40[1] = 3.0f;
    if (D_002E26A0[2]) D_0062F790.v40[1] = 4.0f;
    func_0010bdd0(&D_0062F790, func_001e4578);
    func_00231740(1, 0, func_001e4048, func_001e4070);
    D_003F7A68 = 0;
    D_003DC494 = 0;
    D_003DC48C = 1;
    D_003DC490 = 0;
    func_001e2748();
    return 2;
}

s32 func_001e4868(void) {
    D_002C5958 |= 0xc;
    func_001e27b0();
    func_001e3600();
    func_0010bdd0(&D_0062F6E0, func_001e4268);
    func_00231740(3, 0, func_001e4048, func_001e4070);
    func_0011ef10(0xc350, func_001e4318);
    D_003F7A68 = 0;
    D_003DC494 = 1;
    D_003DC48C = 0;
    D_003DC490 = 0;
    func_001e2748();
    D_003DC470 = D_003DC474 = 0;
    return 2;
}
