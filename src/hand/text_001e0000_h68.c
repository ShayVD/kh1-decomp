#include "common.h"
#include "data/bss_0062.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { s32 a, b, c, d; } Q4;
typedef union { u128 q; u32 w; } U128;
typedef struct { U128 dma; u64 gif[8]; Q4 v[400]; U128 end; } Pkt620;

typedef struct {
    s32 x0;
    s16 h4, h6, h8, ha, hc, he;
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
    f32 f30, f34;
    u8 pad38[8];
    f32 f40, f44;
    u8 pad48[0x48];
    u8 b90;
    u8 pad91[3];
    f32 f94;
    u8 pad98[0x18];
} Win;

typedef struct { u8 pad0[8]; u16 w[1]; u8 pad[0x48f - 10]; u8 b48f; u8 b490; } SaveB;
typedef struct { s32 a; s32 n; void (*fn)(); } Cb;
typedef struct { s32 x0; char s[9][32]; u8 pad[0x644 - 4 - 9 * 32]; char x644[0x20]; s32 a, b, c, d; } Big498;
typedef struct {
    u8 pad0[0x3034];
    s32 f3034;
    s32 f3038;
    u8 pad303c[0x3070 - 0x303c];
    u64 f3070;
} Big20;
typedef struct {
    u8 pad0[0xa80];
    u8 a80[10];
    u8 pada8a[0xad0 - 0xa8a];
    u32 ad0;
} Sv;
typedef Sv SvA80;
typedef Sv SvAD0;
typedef struct { void *p; u8 pad[0x34c]; } E848;
typedef struct { u8 pad[0x24]; s32 server; u8 pad2[0x10]; } RpcCd;
typedef struct { s8 used; u8 pad1[3]; s32 x4; s32 x8; s32 xc; s32 x10; u8 pad[180 - 20]; } Ent180;
typedef struct { u8 b0; u8 b1; s8 x2; s8 x3; s8 used; u8 pad5[11]; s32 x10; u8 pad[72 - 20]; } Ent72;

extern Win D_0062F6E0;
extern Win D_0062F790;
extern Win D_00630300;
extern Win D_006303B0;
extern Win D_00630460;
extern Win D_00630510;
extern SaveB *D_00304BE8;
extern Cb D_0062F8F0;
extern Cb D_006305C0;
extern Big498 D_003DC498;
extern Big20 D_00389C90;
extern u8 D_0062F760[];
u8 D_0062F900[0x100] ALIGNED(64);
extern s32 D_003DC478;
extern s32 D_003DC47C;
extern s32 D_003DC480;
extern s32 D_003DC484;
extern s32 D_003DC488;
extern s32 D_003DC48C;
extern s32 D_003DC490;
extern s32 D_003DC494;
extern s32 D_003F7A68;
extern u64 D_0038CD00;
extern s32 D_002C5BB8;
extern volatile s32 D_002C5958;
extern u8 D_003DBA68[];
extern u8 D_003DC068[][64];
extern u8 D_003DC0A8[];
extern u8 D_003DC0E8[];
extern u8 D_003DC128[];
extern u8 D_003DC1A8[];
extern u8 D_003DC2A8[];
extern u8 D_003DC2B8[];
extern u8 D_003DC2C8[];
extern u8 D_003DC2E0[];
extern u8 D_003DC318[];
extern u8 D_003DC338[];
extern u8 D_003DC358[];
extern u8 D_003DC368[];
extern u8 D_003DC370[];
extern u8 D_003DC380[];
extern u8 D_003DC460[];
extern u8 D_003DC468[];
extern u8 D_003DCB10[][32];
extern char D_003DCB90[][32];
extern u8 D_003DCEF0[];
extern u8 D_003DD230[];
extern s32 D_003DD258;
extern s32 D_003DD25C;
extern s32 D_003DD264;
extern s32 D_003DD268;
extern s32 D_003DD27C;
extern s32 D_003DD280;
extern s32 D_003DD284;
extern s32 D_003DD288;
extern s32 D_003DD28C;
extern s32 D_003DD308;
extern s32 D_003DD30C;
extern s32 D_003DD310;
extern s32 D_003DD314;
extern char D_006305D0[][10];
extern u8 D_006304E0[];
extern s8 D_006307C8[];
extern u8 D_00630FC8[];
extern E848 D_0038D170[];
extern s32 D_0039A570;
extern E848 D_0039A580[];
extern s32 D_003A7980;
extern E848 D_003A7990[];
extern s32 D_003B4D90;
extern E848 D_003B4DA0[];
extern s32 D_003C21A0;
extern E848 D_003C3A70[];
extern s32 D_003C54F0;
extern RpcCd D_003E3C88;
extern s32 D_003E3CB0;
extern u32 D_00633640[2048];
extern s32 D_00635640[1024][8];
extern Ent180 D_0063D640[];
extern Ent72 D_0063EE40[];
extern u8 D_0063F640[256];
extern char D_00490910[];
extern u8 D_00490940[];
extern Pkt620 D_00631620;

void func_0010bd90(void *, void (*)());
void func_0010bdd0(void *, void (*)());
void func_0010e3f0(void *);
void func_0010ef70(void *, void *, void *);
void func_0010f520(void);
void func_0010f558(void *, void *, s32);
void func_0011d768(s32);
s32 func_0011ef10(s32, void (*)());
void func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *);
s32 func_00123618(void *);
s32 func_001205f0(void *, void *);
void *func_001559f0(s32, s32);
s32 func_001ba1e8(s32);
s32 func_001e2800(s32);
void func_001e2810();
void func_001e2920();
void func_001e2a30();
void func_001e2a40(s32);
void func_001e2a88(void);
void func_001e3178();
void func_001e3f00();
void func_001e3fc8();
void func_001e42b0();
s32 func_001e4318(void);
void func_001e44e0();
void func_001e4558();
void func_001e4b08(void);
void func_001e4c20(void);
void func_001e5810();
s32 func_001e6038(void);
void func_001e6578();
void func_001e6580();
void func_001e6ba8();
void func_001e6e20();
void func_001e6eb0();
void func_001e7228();
void func_001e7278();
void func_001e7b48();
void func_001e7b50();
s32 func_001e9418(void);
void func_001ea128(void *, void *);
void func_001ea268(void *, void *);
void func_001ec7c0(s32);
s32 func_001ef7a0(void);
s32 func_0022ee08(void);
void func_0022fc88(s32);
void func_00230728(void);
void func_00231958(void);
void func_002329a0(void *, void (*)(), void (*)());
Sv *func_00232cc0(s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);
int sceSifBindRpc(void *, u32, s32);
int sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
int printf(const char *, ...);

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
    if (D_00304BE8->b48f == 1 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC0A8);
        D_003DC488++;
    } else if (D_00304BE8->b48f == 2 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC0E8);
        D_003DC488++;
    } else if (D_00304BE8->b48f == 5 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC1A8);
        D_003DC488++;
    }
    if (D_00304BE8->b490 == 1 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC0A8);
        D_003DC488++;
    } else if (D_00304BE8->b490 == 2 && ok) {
        n++;
        func_001ea268(D_0062F900, D_003DC0E8);
        D_003DC488++;
    } else if (D_00304BE8->b490 == 5 && ok) {
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
        D_0062F790.f44 = 1.5f;
        func_0010bdd0(&D_0062F790, func_001e3fc8);
        return;
    }
    D_003DC490 = 0;
    D_003F7A68 = 0;
    D_0062F790.f44 = 1.5f;
    func_0010bdd0(&D_0062F790, func_001e3fc8);
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

void func_001e4578(void) {
    s32 n = 2;
    D_003DC488 = 0;
    D_003DC490 = 1;
    func_001ea128(D_0062F900, D_003DC468);
    func_001ea268(D_0062F900, D_003DC068[0]);
    D_003DC488++;
    if (D_00304BE8->b48f == 1) {
        n++;
        func_001ea268(D_0062F900, D_003DC068[1]);
        D_003DC488++;
    } else if (D_00304BE8->b48f == 2) {
        n++;
        func_001ea268(D_0062F900, D_003DC068[2]);
        D_003DC488++;
    } else if (D_00304BE8->b48f == 5) {
        n++;
        func_001ea268(D_0062F900, D_003DC068[5]);
        D_003DC488++;
    }
    if (D_00304BE8->b490 == 1) {
        n++;
        func_001ea268(D_0062F900, D_003DC0A8);
        D_003DC488++;
    } else if (D_00304BE8->b490 == 2) {
        n++;
        func_001ea268(D_0062F900, D_003DC0E8);
        D_003DC488++;
    } else if (D_00304BE8->b490 == 5) {
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
    func_0011ef10(0xC350, (void (*)())func_001e4318);
}

s32 func_001e5d78(void) {
    u8 buf[16];
    s32 i;
    D_003DD264 = 0;
    D_002C5958 |= 0xC;
    func_001e4b08();
    for (i = 0; i < 10; i++) {
        if (D_00304BE8->w[i + 1000] < 9) {
            buf[0] = 1;
            buf[1] = 1;
            buf[2] = D_00304BE8->w[i + 1000] + 33;
            buf[3] = 1;
            buf[4] = 0;
        } else {
            buf[0] = (D_00304BE8->w[i + 1000] + 1) / 10 + 33;
            buf[1] = (D_00304BE8->w[i + 1000] + 1) % 10 + 33;
            buf[2] = 1;
            buf[3] = 0;
        }
        func_001ea268(D_006307C8, buf);
    }
    func_001e4c20();
    D_00630300.f30 = -60.0f;
    D_00630300.f34 = -30.0f;
    D_00630300.f40 = 10.0f;
    D_00630300.f44 = 11.0f;
    func_0010bdd0(&D_00630300, func_001e5810);
    return 2;
}

void func_001e5ee0(void) {
    D_00630460.f30 = -130.0f;
    D_00630460.f34 = -90.0f;
    D_00630460.f40 = 7.0f;
    D_00630460.f44 = 5.0f;
    D_00630460.h4 = 6;
    D_00630460.hc = 2;
    D_00630460.he = 2;
    D_00630460.h6 = 1;
    D_00630460.h8 = 13;
    D_00630460.b90 = 0;
    D_00630460.f1c = 135.0f;
    D_00630460.x0 = -1;
    D_00630460.f94 = 1.0f;
    D_00630510.f30 = 100.0f;
    D_00630510.f34 = -90.0f;
    D_00630510.f40 = 5.0f;
    D_00630510.f44 = 4.5f;
    D_00630510.h4 = 2;
    D_00630510.hc = 2;
    D_00630510.he = 2;
    D_00630510.h6 = 1;
    D_00630510.h8 = 13;
    D_00630510.b90 = 0;
    D_00630510.f1c = 200.0f;
    D_00630510.x0 = -1;
    D_00630510.f94 = 1.0f;
    D_00630300.f30 = 110.0f;
    D_00630300.f34 = 0.0f;
    D_00630300.f40 = 10.0f;
    D_00630300.f44 = 11.0f;
    D_00630300.h4 = 6;
    D_00630300.hc = 1;
    D_00630300.he = 1;
    D_00630300.h6 = 0;
    D_00630300.h8 = 13;
    D_00630300.b90 = 0;
    D_00630300.f1c = 200.0f;
    D_00630300.x0 = -1;
    D_00630300.f94 = 1.0f;
    D_003DC498.a = 0x7E60;
    D_003DC498.b = 0x7540;
    D_003DC498.c = 0x8FE0;
    D_003DC498.d = 0x8B20;
}

void func_001e61c0(void) {
    s32 ok = 0;
    SvAD0 *sv = func_00232cc0(1);
    switch (D_003DD258) {
    case 1:
        func_0010bd90(&D_00630460, 0);
        break;
    case 2:
        switch (D_003DD25C) {
        case 0:
            if (sv->ad0 & 1) ok = 1;
            break;
        case 1:
            if (sv->ad0 & 2) ok = 1;
            break;
        case 2:
            if (sv->ad0 & 4) ok = 1;
            break;
        case 3:
            if (sv->ad0 & 8) ok = 1;
            break;
        }
        if (ok == 1) {
            func_002329a0(&D_003DC498, func_001e6578, func_001e6580);
            func_0010bdd0(&D_00630300, func_001e6ba8);
            func_0010e3f0(D_006304E0);
            func_0010ef70(D_006304E0 - 0x80, D_003DCEF0, 0);
            D_003DD284 = ok;
            D_003DD288 = 60;
            func_0011ef10(0xC350, (void (*)())func_001e6038);
            D_003DD280 = 0;
            D_003DD27C = 0;
        } else {
            func_0010e3f0(D_006304E0);
            func_0010ef70(D_006304E0 - 0x80, D_00630FC8, 0);
            do { func_0010bdd0(&D_00630510, func_001e6e20); } while (0);
        }
        break;
    }
}

void func_001e72a0(void) {
    SvAD0 *sv = func_00232cc0(1);
    s32 i;
    func_001ea128(D_006307C8, D_003DCB10[0]);
    func_001ea268(D_006307C8, D_003DD230);
    D_003DD268 = 1;
    if (sv->ad0 & 1) {
        func_001ea268(D_006307C8, D_003DCB10[1]);
        func_001ea268(D_006307C8, D_003DD230);
        D_003DD268++;
    }
    if (sv->ad0 & 2) {
        func_001ea268(D_006307C8, D_003DCB10[2]);
        func_001ea268(D_006307C8, D_003DD230);
        D_003DD268++;
    }
    if (sv->ad0 & 4) {
        func_001ea268(D_006307C8, D_003DCB10[3]);
        func_001ea268(D_006307C8, D_003DD230);
        D_003DD268++;
    }
    i = 0;
    while (D_006307C8[i] != 0) {
        i += (u32)((u8)D_006307C8[i] - 9) < 23;
        i++;
    }
    D_006307C8[i] = 4;
    func_0010ef70(&D_00630510, D_006307C8, func_001e7278);
    D_006305C0.n = D_003DD268 + 1;
    D_006305C0.fn = func_001e7228;
    D_006305C0.a = 1;
    func_0010f558(&D_006305C0, &D_00630510, 1);
    func_0011ef10(0xC350, func_001e6eb0);
    D_003DD28C = 1;
}

void func_001e7ba8(void) {
    SvA80 *sv = func_00232cc0(1);
    s32 i;
    switch (D_003DD258) {
    default: return;
    case 1:
        D_00389C90.f3070 &= ~0x0020000000000000ULL;
        break;
    case 2:
        D_00389C90.f3070 &= ~0x0020000000000000ULL;
        break;
    case 3:
        D_003DC498.x0 = 9;
        func_001ea128(D_006307C8, D_006305D0[0]);
        func_001ea268(D_006307C8, D_003DCB90[sv->a80[0]]);
        func_001ea128(D_003DC498.x644, D_006307C8);
        for (i = 1; i < 10; i++) {
            func_001ea128(D_006307C8, D_006305D0[i]);
            func_001ea268(D_006307C8, D_003DCB90[sv->a80[i]]);
            func_001ea128(D_003DC498.s[i - 1], D_006307C8);
        }
        func_002329a0(&D_003DC498, func_001e7b48, func_001e7b50);
        func_0010bdd0(&D_00630300, 0);
        break;
        break;
    }
}

void func_001e9670(void) {
#define pk (&D_00631620)
    Q4 *p;
    s32 i;
    Pkt620 *q;
    U128 *e;
    pk->dma.q = 0;
    pk->dma.w = 0x10000194;
    pk->gif[0] = 0x1000000000000002ULL;
    pk->gif[1] = 14;
    pk->gif[2] = 0x4000d;
    pk->gif[3] = 71;
    pk->gif[4] = 68;
    pk->gif[5] = 66;
    pk->gif[6] = 0x2024c000000080c8ULL;
    pk->gif[7] = 65;
    p = pk->v;
    for (i = 0; i < 100; i++) {
        p->a = i + 32;
        p->b = i + 96;
        p->c = i + 16;
        p->d = 96;
        p++;
        p->a = 0x7880;
        p->b = (i + 2098) << 4;
        p->c = 0xFFFFFF;
        p->d = 0;
        p++;
        p->a = i + 32;
        p->b = i + 96;
        p->c = i + 16;
        p->d = 96;
        p++;
        p->a = 0x8780;
        p->b = (i + 2098) << 4;
        p->c = 0xFFFFFF;
        p->d = 0;
        p++;
    }
    q = &D_00631620;
    e = &q->end;
    e->q = 0;
    e->w = 0x70000000;
    D_003DD308 = 0;
    D_003DD30C = 0;
    D_003DD310 = 4;
    D_003DD314 = 2;
    func_0011ef10(0xC350, (void (*)())func_001e9418);
}

E848 *func_001e9b98(s32 a, s32 id) {
    s32 i;
    if (a == 1) {
        if (!D_00389C90.f3038) {
            for (i = 0; i < D_003B4D90; i++) {
                if (func_00123618(D_003A7990[i].p) == id) return &D_003A7990[i];
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123618(D_0039A580[i].p) == id) return &D_0039A580[i];
            }
        }
    } else {
        if (!D_00389C90.f3034) {
            for (i = 0; i < D_0039A570; i++) {
                if (func_00123618(D_0038D170[i].p) == id) return &D_0038D170[i];
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123618(D_0039A580[i].p) == id) return &D_0039A580[i];
            }
        }
    }
    return 0;
}

s32 func_001ec7d0(s32 arg) {
    u32 i, j;
    func_001ec7c0(0);
    for (i = 0; i < 2048; i++) D_00633640[i] = 0;
    { u8 *p = (u8 *)D_0063D640; for (i = 0; i < 8192; i++) p[i] = 0; }
    { u8 *p = D_0063F640; for (i = 0; i < 256; i++) p[i] = 0; }
    for (;;) {
        if (sceSifBindRpc(&D_003E3C88, 17, 0) < 0) {
            printf(D_00490910);
            return -1;
        }
        if (D_003E3C88.server != 0) break;
        i = 0x10000; while (i--) ;
    }
    D_003E3CB0 = 0;
    for (j = 0; j < 1024; j++) {
        for (i = 0; i < 8; i++) D_00635640[j][i] = -1;
    }
    D_00633640[0] = (u32)D_0063D640;
    D_00633640[1] = arg;
    D_00633640[2] = (u32)D_0063F640;
    sceSifCallRpc(&D_003E3C88, 0, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return 0;
}

s32 func_001ecb08(s32 a, s32 b, s32 c) {
    Ent180 *p;
    s32 i;
    FlushCache(0);
    p = D_0063D640;
    if (b < 0 && c < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a) return 1;
        }
    } else if (b < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a && p->x4 == c) return 1;
        }
    } else if (c < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a && p->x10 == b) return 1;
        }
    }
    for (i = 0; i < 24; i++, p++) {
        if (p->used && p->xc == a && p->x10 == b && p->x4 == c) return 1;
    }
    return 0;
}

s32 func_001ecd08(s32 a, s32 b, s32 c) {
    Ent72 *p;
    s32 i, n;
    FlushCache(0);
    p = D_0063EE40;
    if (a < 0 && b < 0 && c == 0) {
        n = 0;
        for (i = 0; i < 4; i++, p++) {
            if (p->used) n++;
        }
        return n;
    } else if (a < 0) {
        if (c == 0) {
            n = 0;
            for (i = 0; i < 4; i++, p++) {
                if (p->used && (p->b0 & 0x7f) == 1) n++;
            }
            return n;
        }
        for (i = 0; i < 4; i++, p++) {
            if (p->used && (p->b0 & 0x7f) == 1 && p->x10 == c) return 1;
        }
        return 0;
    }
    for (i = 0; i < 4; i++, p++) {
        if (p->used && p->b0 == 0 && p->x2 == a && p->x3 == b) return 1;
    }
    return 0;
}

void func_001ef950(void)
{
    u128 b[11];
    u128 a[11];
    u8 *p;

    p = func_001559f0(52, 12);
    func_001205f0(D_00490940, p);
    func_0011fbb0(16380, 1, 0, 0, 0, 16, 16, 64, p + 0x10000, a);
    FlushCache(0);
    func_00266f38(func_00266c08(2), a);
    sceGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 36, 0, 0, 256, 256, 2048, p, b);
    FlushCache(0);
    func_00266f38(func_00266c08(2), b);
    sceGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 44, 0, 0, 256, 256, 2048, p + 0x8000, b);
    FlushCache(0);
    func_00266f38(func_00266c08(2), b);
    sceGsSyncPath(0, 0);
}

