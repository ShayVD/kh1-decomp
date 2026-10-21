#include "common.h"
#include "data/bss_0049.h"

typedef __builtin_va_list va_list;
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
#include "data/types/text_00100000_h28.h"
typedef struct { u16 code; u16 v; u16 x; u16 y; u16 lw; u16 w; u16 padc[2]; } Glyph;
#include "data/pieces/D_002BC0C0.h"
typedef View30_2BC0C0 View30;
typedef struct { f32 a, b, c, d; } F16;
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002A6234.h"
typedef struct { s32 currentCount; s32 maxCount; s32 initCount; s32 numWaitThreads; u32 attr; u32 option; } SemaParam;
typedef struct { s32 m[32][16]; s32 v[4]; } Blk810;
typedef struct { s32 status; void (*entry)(void); void *stack; s32 stackSize; void *gpReg; s32 initPriority; s32 currentPriority; u32 attr; u32 option; s32 waitType; s32 waitId; s32 wakeupCount; } ThreadParam;
typedef struct { u16 n; u8 pad2[0xb]; s8 col; u8 pade[2]; Glyph g[1]; } GlyphStr;
typedef struct { u16 pad0; u16 n; f32 a; f32 b; s8 state; u8 padd[0x1803]; f32 t[1]; } Track;
#include "data/pieces/D_002BC0A8.h"
typedef Flags_2BC0A8_2 Flags;
typedef struct { u64 a; s32 b; } Pad8;
#include "data/types/text_00100000_h28_p.h"
typedef struct { u8 pad0[0x54]; f32 rot; u8 pad58[8]; f32 x; s32 y; f32 z; u8 pad6c[0x14]; } Cam80;
typedef struct { u8 pad0[4]; u16 mode; u8 pad6[2]; u16 w; u8 pada[2]; s16 cx; u8 pade[0x22]; f32 x, y; u8 pad38[0x38]; f32 ox, oy; } TextBox;
typedef struct { u8 pad[0x10]; f32 f10, f14; u8 pad18[4]; u8 b1c, b1d, b1e; } Task;
typedef struct { u8 pad[0x18]; s32 (*f18)(s32); s32 (*f1c)(void); } Api;
typedef struct { u8 pad[0x1c]; f32 ry; } Rot;
typedef struct { u8 pad[0x24]; s32 b; s32 a; } Seq;
typedef struct { u8 pad[0xa]; u8 act; u8 id; u8 pad2[4]; u32 on:1; u32 rest:31; } Ent14;
typedef struct { u8 pad[0xc]; s32 v; } Res;
typedef struct { u8 pad[16]; void *p; } Obj10;
typedef struct {
    u8 pad0[0x21];
    u8 b21, b22, b23, b24, b25;
    u8 pad26[0xe];
    f32 f34, f38, f3c;
    f32 uv[16][2];
} Setup;
typedef struct {
    void (*cb)(u16, s32);
    u8 pad4[0xa];
    u16 cnt;
    u8 pad10;
    u8 state;
    u8 b12;
    u8 flags;
    u8 pad14[0xc];
    void *res;
    s32 arg;
} Fade;

extern Api D_0046A688;
extern Cam80 D_00494310[2];
#include "data/pieces/D_002B1C60.h"
extern E90 D_00494F20[][2];
#include "data/pieces/D_002AA060.h"
extern ED0 D_00494D80[];
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_0037A378.h"
extern Mtx D_00495190;
extern Mtx D_00495210; /* src/data/bss_0049.c: u8 D_00495210[0x40] */
extern Obj10 *func_0015ed80(s32, void (*)(void));
extern Pad8 D_002BCA00;
extern Pkt D_002B6490;
extern Res *func_00120190(char *);
extern Task *func_0011f090(void *, s32, void (*)(void));
#include "data/pieces/D_002BC0F0.h"
extern char D_0048CCA0[];
extern char D_0048CCB8[];
extern f32 D_0029B270;
extern f32 D_002A6200;
extern f32 D_002BBDFC;
extern f32 D_00494A88;
extern f32 D_00494A8C;
f32 D_00495168 ALIGNED(8);
f32 D_0049516C ALIGNED(4);
f32 D_00495170 ALIGNED(16);
f32 D_00495178 ALIGNED(8);
extern f32 D_00495184;
extern s32 ChangeThreadPriority(s32, s32);
extern s32 CreateSema(SemaParam *);
extern s32 CreateThread(ThreadParam *);
extern s32 D_0029B2F0;
extern s32 D_0029B2F4;
extern s32 D_0029B2FC;
extern s32 D_0029BE20[][32][16];
#include "data/pieces/D_002A3E20.h"
extern s32 D_002A3F24;
extern s32 D_002A3F28;
#include "data/pieces/D_002A3F30.h"
extern s32 D_002A3F44;
#include "data/pieces/D_002A3F50.h"
extern s32 D_002A61F4;
extern s32 D_002A6258;
#include "data/pieces/D_002A62D0.h"
extern s32 D_002A6B84;
extern s32 D_002B6474;
extern s32 D_002B6478;
extern s32 D_002B647C;
extern s32 D_002B6480;
extern s32 D_002B6484;
extern s32 D_002B6770;
extern s32 D_002B6774;
extern s32 D_002BBBA0;
#include "data/pieces/D_002BBDE4.h"
extern s32 D_002BC130;
extern s32 D_002BC734;
extern s32 D_002BC738;
extern s32 D_002BC73C;
extern s32 D_002BC740;
extern s32 D_002BC744;
extern s32 D_002BCAE0;
extern s32 D_002BCDA8;
extern s32 D_002BCDC0;
extern s32 D_002BCDC4;
extern s32 D_002BCDD8;
extern s32 D_002BCDDC;
extern s32 D_002C1304;
extern s32 D_00351BD0;
extern s32 D_0046E150[];
extern s32 D_00472190[];
extern s32 D_004761D0[];
extern s32 D_0047A210[];
extern s32 D_0048CAE0[];
extern s32 D_0048CB28[];
extern s32 D_0048CB70[];
extern s32 D_0048CBB8[];
extern s32 D_00494410[2];
extern s32 D_004948B0[4][4]; /* src/data/bss_0049.c: f32 D_004948B0[4][4] */
extern s32 D_004948F0[4][4]; /* src/data/bss_0049.c: f32 D_004948F0[4][4] */
s32 D_00494930[4][4] ALIGNED(16);
s32 D_00494970[4][4] ALIGNED(16);
extern s32 D_00494A7C;
extern s32 D_00494A80;
extern s32 D_00494A84;
extern s32 D_00494AA0[]; /* src/data/bss_0049.c: s32 D_00494AA0[32] */
extern s32 D_00494B20[]; /* src/data/bss_0049.c: s32 D_00494B20[32] */
extern s32 D_00494BA0;
extern s32 D_00494BA4;
s32 D_00495174 ALIGNED(4);
extern s32 D_00495180;
extern s32 D_00495188;
s32 D_0049525C ALIGNED(4);
extern s32 D_00495260;
extern s32 FlushCache(s32);
extern s32 GetThreadId(void);
extern s32 StartThread(s32, void *);
extern s32 func_00100228(void);
extern s32 func_00100610(void);
extern s32 func_001007e8(void);
extern s32 func_001008e8(void);
extern s32 func_00101f10(void);
extern s32 func_00102a28(void);
extern s32 func_00103258(void);
extern s32 func_001037e8(void);
extern s32 func_001039f8(void);
extern s32 func_00104220(void);
extern s32 func_00106b18(void *);
extern s32 func_0010c078(void);
extern s32 func_0010c200(void);
extern s32 func_0010c720(s32, s32, s32, s32 *, s32, s32, s32);
extern s32 func_0010e8d0(void);
extern s32 func_0010f258(s32, s32);
extern s32 func_0010f368(s32, s32);
extern s32 func_0010fd40(void);
extern s32 func_00111150(void);
extern s32 func_001129c8(void);
extern s32 func_00112fd0(s32);
extern s32 func_00114c00(void);
extern s32 func_00114e50(void);
extern s32 func_0011a068(void);
extern s32 func_0011c898(s32);
extern s32 func_0011e528(void);
extern s32 func_0011e538(void);
extern s32 func_0011e5f0(void);
extern s32 func_0011ef10(s32, void *);
extern s32 func_00121ee0(void *);
extern s32 func_001ecfd8(void);
extern s32 func_00266c08(s32);
extern s32 sceGsExecLoadImage(void *, void *);
extern s32 sceGsSyncPath(s32, s32);
extern u64 D_002B6668;
extern u8 D_0029B1C0[];
extern u8 D_0029B200[];
extern u8 D_0029B260[];
#include "data/pieces/D_0029B280.h"
extern u8 D_002B6460[];
extern u8 D_002B65E0[];
extern u8 D_002B66B0[];
extern u8 D_002B75C0[];
extern u8 D_002BC1B0[];
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
extern u8 D_0046E120[];
extern u8 D_00472160[];
extern u8 D_004761A0[];
extern u8 D_0047A1E0[];
extern u8 D_0047E220[];
extern u8 D_00482260[];
extern u8 D_00494050[];
u8 D_004945F8[0x280] ALIGNED(8);
extern u8 D_00494878[];
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
extern void func_00101660(void);
extern void func_00102118(void);
extern void func_00106460(void);
extern void func_00106780(s32);
extern void func_00106900(void);
extern void func_00106910(void);
extern void func_00106a08(void);
extern void func_00106bd8(void *, s32);
extern void func_00106db0(void);
extern void func_00106e98(s32);
extern void func_00107120(s32 *, s32 *, s32, s32);
extern void func_00107548(void *, s32);
extern void func_00108708(void);
extern void func_00108b60(s32, ED0 *);
extern void func_00108be8(s32, s32, E90 *);
extern void func_00108c58(s32, E90 *);
extern void func_00108cd0(E90 *, s32);
extern void func_00108d90(void);
extern void func_00109cd0(void);
extern void func_00109f88(void);
extern void func_0010c0c8(void);
extern void func_0010c240(void);
extern void func_0010ff60(s32);
extern void func_00110068(void);
extern void func_00110380(void);
extern void func_00110448(s32);
extern void func_001104e0(void);
extern void func_00111190(void);
extern void func_001111b0(void);
extern void func_001118a0(void);
extern void func_00111ca8(void);
extern void func_00113de0(void);
extern void func_00114090(void);
extern void func_00114820(void);
extern void func_00114840(void);
extern void func_0011d240(s32, s32, void *, s32);
extern void func_0011ecd8(void *, char *);
extern void func_0011efa8(void *, void *, s32, s32);
extern void func_0011f988(void);
extern void func_001220d0(void);
extern void func_00176c60(s32);
extern void func_001ec7d0(s32);
extern void func_001ee4b8(void);
extern void func_00232ad0(s32);
extern void func_00239488(void);
extern void func_00267578(Mtx, Mtx, void *);
extern void func_002676c0(Mtx, void *, f32);
extern void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
extern void sceVu0MulMatrix(Mtx, Mtx, Mtx);
extern void vsprintf(char *, const char *, va_list);
extern volatile s32 D_002BBE08;
extern volatile s32 D_00495258;
extern void func_00100670(u32, s32);
extern void func_00107d30(s32, s32);
extern void func_0010c278(void);
extern s32 func_00107c48(s32);
extern void func_00100818(void);
extern void func_00100988(void);
extern s32 func_00100448(void);
extern E32 D_004941D0[];
extern E32 D_00494210[];
extern E32 D_00494250[];
extern E32 D_00494290[];
extern E32 D_004942D0[];

void func_00100278(void) {
    D_002A6B84 = func_00266c08(2);
    D_002B6770 = 0;
    func_00106900();
    func_00106910();
    D_002B6474 = 0;
    (*(Flags *)&D_0037A378).b0 = 0;
    D_002BCDA8 = 0;
    D_002A3F44 = 0;
    D_002BC740 = 0;
    D_002BC744 = 0;
    func_00114090();
    func_00113de0();
    func_00114840();
    func_00111ca8();
    { s32 z = 0; D_002BCDDC = z; D_002BCDD8 = z; func_00112fd0(z); }
    func_00101660();
    D_002BC0A8.flags_2.b1 = 0;
    (*(void **)&D_002BC140) = D_002BCAF0;
    (*(void **)&D_002BC144) = D_002BCAF0;
}

void func_00100360(void) {
    D_002C1304 = 0;
    func_0011c898(0);
    func_001118a0();
    D_002BBBA0 = 0;
    func_0011ef10(0x2903, func_0011a068);
    func_0011ef10(0x280A3, func_001039f8);
    func_00100228();
    func_0011e528();
    D_002BCDC4 = 0;
    D_002BC0A8.flags_2.b1 = 0;
    func_0011e5f0();
    D_002BCDC0 = 0;
    func_0010e8d0();
    func_0010c078();
    func_0011ef10(0xC350, func_001129c8);
    func_00100610();
    func_00114e50();
    func_0011ef10(0x1D4C0, func_00100448);
    D_002A6200 = 0.05f;
}

s32 func_00100448(void) {
    D_002BC744 = D_002BC740;
    D_002BC740 = (*(Flags *)&D_0037A378).b0;
    func_00114c00();
    if (D_002BC0A8.flags_2.b1 == 1) {
        func_001007e8();
        if (D_002BC0A8.flags_2.b0 == 1) {
            if (D_002BC0A8.flags_2.b3 == 1) {
                func_00100818();
                func_001008e8();
            }
            func_00100988();
            func_00101f10();
            func_00102a28();
        }
    }
    if (D_002A61F4 != 0) {
        func_00103258();
    }
    if (D_002BC734 != 0) {
        func_001037e8();
    }
    if (D_002BC738 != 0) {
        func_00104220();
    }
    func_0011e538();
    return 0;
}

void func_00100818(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        D_00494310[i].x = (*(V3_2e2780 *)&D_002E2780).x;
        D_00494310[i].y = 0;
        D_00494310[i].z = (*(V3_2e2780 *)&D_002E2780).z;
    }
    D_00494310[1].rot += D_0029B270 * D_002BBDFC;
    if (D_00494310[1].rot > 3.1415928f) {
        D_00494310[1].rot -= 6.2831855f;
    }
    if (D_00494310[1].rot < -3.1415928f) {
        D_00494310[1].rot += 6.2831855f;
    }
}

void func_00100988(void) {
    D_0029B2F0 = 0;
    func_00106e98(10020);
    func_00106bd8(D_0029B1C0, 10020);
    func_00107548(&D_0029B280, D_002A3F30);
    if (D_0029B2F4 != 0) {
        func_00100670(1, 10020);
        func_00107d30(10020, 1);
    }
    if (D_0029B2FC != 0) {
        if (D_002BC0A8.flags_2.b4 == 1) {
            func_00100670(6, 10020);
        } else {
            func_00100670(0, 10020);
        }
        func_00107d30(10020, 0);
    }
    func_00106bd8(D_0029B200, 50000);
    func_00106e98(50000);
    if ((D_0029B2F0 = func_00107c48(D_002A3F30)) != 0) {
        func_00100670(3, 50000);
        func_00107d30(50000, 3);
    }
    func_00108708();
    func_00106bd8(D_0029B260, 50100);
}

void func_00100b18(Setup *s) {
    s32 i;
    D_002BC0F0.view30.near_ = 15000.0f;
    D_002BC0F0.view30.far_ = 20000.0f;
    for (i = 0; i < 16; i++) {
        D_002A3F60.v[i].a = 0;
        D_002A3F60.v[i].b = 0;
        D_002A4060.v[i].a = s->uv[i][0] * 0.00006103515625f;
        D_002A4060.v[i].b = s->uv[i][1] * 0.00006103515625f;
    }
    D_0029B270 = s->f34;
    D_002BC0F0.view30.a = s->f3c;
    D_002BC0F0.view30.b = s->f38;
    D_002BC0F0.view30.c = s->b21;
    D_002BC0F0.view30.d = s->b22;
    D_002BC0F0.view30.e = s->b23;
    D_002BC0F0.view30.f = s->b24;
    D_002BC0F0.view30.g = s->b25;
    D_002BC0C0.view30 = D_002BC0F0.view30;
}

void func_00100f70(Blk810 *src) {
    s32 i, j, k;
    for (i = 0; i < D_002A3F24; i++) {
        for (j = 0; j < 32; j++) {
            for (k = 0; k < 16; k++) {
                D_0029BE20[i][j][k] = src[i].m[j][k];
            }
        }
        ((s32 (*)[4])&D_002A3E20)[i][0] = src[i].v[0];
        ((s32 (*)[4])&D_002A3E20)[i][1] = src[i].v[1];
        ((s32 (*)[4])&D_002A3E20)[i][2] = src[i].v[2];
        ((s32 (*)[4])&D_002A3E20)[i][3] = src[i].v[3];
    }
}

void func_00101680(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (D_00494410[i] != (*(s32 (*)[2])&D_002A3F50)[i]) {
            if ((*(s32 (*)[2])&D_002A3F50)[i] != 0) {
                func_0011d240((*(s32 (*)[2])&D_002A3F50)[i], i, D_002BCAF0, 0x3FFF);
            }
            D_00494410[i] = (*(s32 (*)[2])&D_002A3F50)[i];
        }
    }
}

void func_00102978(void) {
    s32 i;
    Task *t;
    func_0011efa8(D_00494878, D_004945F8, 40, 16);
    for (i = 0; i < D_002A3F24; i++) {
        t = func_0011f090(D_00494878, 120000, func_00102118);
        if (t != NULL) {
            t->b1c = 0;
            t->b1d = i;
            t->b1e = 1;
        }
    }
}

void func_00103a70(void) {
    s32 i, j, k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            D_0048CBB8[k] = D_00494930[i][j];
            D_0048CB70[k] = D_00494970[i][j];
            D_0048CB28[k] = D_004948B0[i][j];
            D_0048CAE0[k] = D_004948F0[i][j];
            k++;
        }
    }
}

void func_00104850(f32 *pos, s32 *out) {
    out[0] = (pos[0] - D_002A6234->x0) / D_002A6234->cw;
    out[2] = (pos[2] - D_002A6234->z0) / D_002A6234->ch;
    if (out[0] < 0) {
        out[0] = 0;
    } else if (out[0] >= D_002A6234->nx) {
        out[0] = D_002A6234->nx - 1;
    }
    if (out[2] < 0) {
        out[2] = 0;
    } else if (out[2] >= D_002A6234->nz) {
        out[2] = D_002A6234->nz - 1;
    }
}

void func_001057b8(s32 id, s32 on) {
    s32 i;
    for (i = 0; i < D_002A6258; i++) {
        if (((Ent14 *)D_002A6238)[i].id == id) {
            ((Ent14 *)D_002A6238)[i].on = on;
        }
    }
    if (D_002A3F28 != 0) {
        for (i = 0; i < D_002A62D0; i++) {
            if (((Ent14 *)D_002A62B0)[i].id == id) {
                ((Ent14 *)D_002A62B0)[i].on = on;
            }
        }
    }
}

void func_00105860(void) {
    s32 i;
    for (i = 0; i < D_002A6258; i++) {
        if (((Ent14 *)D_002A6238)[i].act != 0 && ((Ent14 *)D_002A6238)[i].id != 0 && ((Ent14 *)D_002A6238)[i].id < 100) {
            ((Ent14 *)D_002A6238)[i].on = 0;
            if (((Ent14 *)D_002A6238)[i].id != D_002BC130 + 1) {
                ((Ent14 *)D_002A6238)[i].on = 1;
            }
        }
    }
    if (D_002A3F28 != 0) {
        for (i = 0; i < D_002A62D0; i++) {
            if (((Ent14 *)D_002A62B0)[i].id != 0 && ((Ent14 *)D_002A62B0)[i].id < 100) {
                ((Ent14 *)D_002A62B0)[i].on = 0;
                if (((Ent14 *)D_002A62B0)[i].id != D_002BC130 + 1) {
                    ((Ent14 *)D_002A62B0)[i].on = 1;
                }
            }
        }
    }
}

void func_00106648(s32 n, s32 m, s32 x, s32 y) {
    f32 t;

    D_00494A7C = x * 16 + 0x7000;
    D_00494A80 = y * 16 + 0x7400;
    t = 800.0f / (f32)m / (f32)(n - 1);
    D_00494A88 = -t;
    D_00494A8C = (f32)n * t + 1.0f;
    D_00494A84 = m;

    func_0011ef10(190022, func_00106460);
}

void func_00106a58(s32 n) {
    Task *t;
    if (D_002B647C == 1 || D_002B6480 == 1) {
        func_00106780(n);
        func_00106900();
        func_00106910();
        return;
    }
    if ((t = func_0011f090(D_002BC720, 0, func_00106a08)) != NULL) {
        t->f10 = n * 2;
        if (n == 0) n = 1;
        t->f14 = 128.0f / (f32)(n * 2);
    }

}

void func_001072c0(s32 unused, s32 *out) {
    s32 i;
    s32 a = 0;
    s32 b = 0;
    if (D_00351BD0 != 0) {
        for (i = 0; i < D_00494BA0; i++) {
            func_00107120(&out[a], &D_0047A210[b], D_00494AA0[i], 4);
            a += D_00494AA0[i];
            b += D_00494AA0[i] * 4;
        }
    } else {
        for (i = 0; i < D_00494BA0; i++) {
            func_00107120(&out[a], &D_004761D0[b], D_00494AA0[i], 4);
            a += D_00494AA0[i];
            b += D_00494AA0[i] * 4;
        }
    }
}

void func_001073f0(s32 unused, s32 *out) {
    s32 i;
    s32 a = 0;
    s32 b = 0;
    if (D_00351BD0 != 0) {
        for (i = 0; i < D_00494BA4; i++) {
            func_00107120(&out[a], &D_00472190[b], D_00494B20[i], 4);
            a += D_00494B20[i];
            b += D_00494B20[i] * 4;
        }
    } else {
        for (i = 0; i < D_00494BA4; i++) {
            func_00107120(&out[a], &D_0046E150[b], D_00494B20[i], 4);
            a += D_00494B20[i];
            b += D_00494B20[i] * 4;
        }
    }
}

void func_00107d30(s32 arg0, s32 arg1) {
    Obj10 *o = func_0015ed80(arg0, func_00106db0);
    switch (arg1) {
    case 1:
        o->p = D_00351BD0 ? D_00472160 : D_0046E120;
        break;
    case 0:
        o->p = D_00351BD0 ? D_0047A1E0 : D_004761A0;
        break;
    case 3:
        o->p = D_00351BD0 ? D_00482260 : D_0047E220;
        break;
    }
}

void func_00108f18(s32 a, s32 b, s32 c) {
    func_00108be8(a, c, &D_00494F20[D_00351BD0][a]);
    func_0015ed80(b, func_00108d90)->p = &D_00494D80[a].e[D_00351BD0];
}

void func_00108fd0(s32 a, s32 b, s32 c, s32 d, s32 e) {
    func_00108b60(d, &D_002AA060[a]);
    func_00108c58(c, &D_002B1C60[D_00351BD0][a]);
    func_00108cd0(&D_002B1C60[D_00351BD0][a], e);
    func_0015ed80(b, func_00108d90)->p = &D_002AA060[a].e[D_00351BD0];
}

void func_00109288(void) {
    Res *r;
    D_002BBDE4 = 7;
    func_00110068();
    func_0010c278();
    func_001ee4b8();
    func_00232ad0(-1);
    func_0011ecd8(D_002B6460, D_0048CCA0);
    r = func_00120190(D_0048CCB8);
    if (r != NULL) {
        D_0046A688.f18(r->v);
    } else {
        D_0046A688.f18(0);
    }
    D_002B6478 = D_0046A688.f1c();
    func_00110448(0);
    D_002BC73C = 0;
    func_001ec7d0(0);
    func_0011f988();
}

s32 func_00109658(void) {
    if (D_002B6484 == 0 && (D_002BCA00.a & 0xF0900000000ull) == 0xF0900000000ull && (D_002BCA00.b & 0xF09)
        && func_0010c200() == 0 && func_001ecfd8() == 0) {
        D_002BBE08 = 0;
        func_001ec7d0(1);
        func_00114820();
        func_00239488();
        func_00176c60(0);
        func_0010fd40();
        if (D_002BCAE0 != 0) {
            do {
                func_001220d0();
                func_00111190();
                func_001104e0();
            } while (func_00111150() != 1);
            func_001111b0();
        }
        func_001104e0();
        func_0010ff60(0);
    }
    return D_002BBE08;
}

s32 func_00109e20(void) {
    switch (D_00495188) {
    case 0:
        D_00495188 = 1;
        D_00495168 = D_00495184;
        D_0049516C = 128.0f / D_00495184;
    case 1:
        if (D_00495184 <= 0.0f) {
            return 4;
        }
        func_00109cd0();
        {
        f32 a = D_00495168 - D_00495184;
        f32 b = D_00495184 * D_0049516C;
        a *= D_0049516C;
        D_002B6490.b = ((u64)(s32)b << 24) | 0x100808080ull;
        D_002B6490.a = ((u64)(s32)a << 24) | 0x100808080ull;
        }
        func_00106b18(D_002B65E0);
        D_00495184 -= D_002BBDFC;
        return 0;
    }
    return 0;
}

s32 func_0010a120(void) {
    switch (D_00495180) {
    case 0:

        D_00495174 = 128;
        D_00495170 = 64.0f;
        D_00495178 = 2.0f;
        D_00495180 = 1;

    case 1:
        if (D_00495170 <= 0.0f) {
            D_002B6774 = 0;
            func_00110380();
            return 4;
        }
        func_00109f88();
        { s32 c = D_00495174;
        D_002B6668 = (u64)c | ((u64)c << 8) | ((u64)c << 16) | ((u64)0x80 << 24) | ((u64)1 << 32); }

        func_00106b18(D_002B66B0);
        D_00495170 -= D_002BBDFC;
        D_00495174 = D_00495170 * D_00495178;
        return 0;
    }
    return 0;
}

void func_0010b030(u8 *buf) {
    u8 *clut;
    u8 *p;
    s32 i;
    sceGsSetDefLoadImage(D_002BC1B0, 0x1800, 4, 27, 0, 0, 256, 128);
    clut = buf + 0x8000;
    FlushCache(0);
    sceGsExecLoadImage(D_002BC1B0, buf);
    sceGsSyncPath(0, 0);
    sceGsSetDefLoadImage(D_002BC1B0, 0x3FF4, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(D_002BC1B0, clut);
    p = clut;
    for (i = 0; i < 256; i++) {
        *p++ = 0;
        *p++ = 0;
        *p = 0;
        p += 2;
    }
    sceGsSyncPath(0, 0);
    sceGsSetDefLoadImage(D_002BC1B0, 0x3FF8, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(D_002BC1B0, clut);
    sceGsSyncPath(0, 0);
}

void func_0010b2d0(Mtx out, Rot *r, void *t) {
    Mtx m;
    f32 a = r->ry;
    if (a > 180.0f) {
        a -= 180.0f;
    } else {
        a += -180.0f;
    }
    func_002676c0(m, D_002BCAF0, a / 180.0f * 3.1415928f);
    func_00267578(m, m, t);
    sceVu0MulMatrix(m, D_00495190, m);
    sceVu0MulMatrix(out, D_00495210, m);
}

void func_0010c278(void) {
    ThreadParam tp;
    u8 pad[32];
    SemaParam sp;

    func_0010c240();
    ChangeThreadPriority(GetThreadId(), 30);
    sp.maxCount = 1;
    sp.currentCount = 0;
    sp.initCount = 0;
    sp.option = 0;
    D_00495258 = CreateSema(&sp);
    D_00495260 = CreateSema(&sp);
    tp.entry = func_0010c0c8;
    tp.stack = D_002B75C0;
    tp.stackSize = 0x4000;
    tp.initPriority = 40;
    tp.gpReg = D_00494050;
    D_0049525C = CreateThread(&tp);
    if (D_0049525C != -1) {
        StartThread(D_0049525C, 0);
    }
}

void func_0010cb80(GlyphStr *s, s32 max, s32 v, TextBox *b) {
    s32 dx, dy, dv;
    s32 i;
    Glyph *g;
    if (b == NULL) {
        dx = 0;
        dy = 0;
        dv = 48;
    } else {
        dx = b->x - b->ox;
        dy = b->y - b->oy;
        switch (b->mode) {
        case 0:
        case 1:
            dv = 32;
            break;
        default:
            dv = 16;
            break;
        }
    }
    for (i = 0; i < s->n; i++) {
        if (i >= max) return;
        g = &s->g[i];
        v = func_0010c720(g->x + dx, g->y + dy, g->code, &v, g->v + dv, g->w, s->col);
    }
}

s32 func_0010cc98(Track *p) {
    s32 i;
    if (p->n >= 2) {
        for (i = 0; i < p->n - 1; i++) {
            if (p->t[i] != 0.0f) return 0;
        }
    }
    if (p->t[p->n - 1] != 0.0f && p->b == p->a) return 1;
    return 0;
}

void func_0010cd40(Track *t, Seq *s) {
    if (s->a == 0) return;
    switch (t->state) {
    case 0:
        if ((t->state = func_0010cc98(t)) == 0) break;
    case 1:
        func_0010f258(s->a, s->b);
        t->state = 2;
    case 2:
        if (func_0010f368(s->a, s->b) != 0) {
            t->state = 0;
            s->a = 0;
        }
        break;
    }
}

void func_0010d138(TextBox *b, GlyphStr *s) {
    s32 lines[32];
    s32 i, j, k, start, last, off;
    k = 0;
    for (j = 0; j < s->n - 1; j++) {
        if (s->g[j].y != s->g[j + 1].y) {
            lines[k++] = j;
        }
    }
    lines[k++] = s->n - 1;
    start = 0;
    for (j = 0; j < k; j++) {
        last = lines[j];
        off = b->cx - (((Glyph *)s)[last + 1].lw >> 1) - b->w;
        for (i = start; i < last + 1; i++) {
            ((Glyph *)s)[i + 1].x += off;
        }
        start = last + 1;
    }
}

void func_0010d230(TextBox *b, GlyphStr *s) {
    s32 lines[32];
    s32 i, j, k, start, last, off;
    k = 0;
    for (j = 0; j < s->n - 1; j++) {
        if (s->g[j].y != s->g[j + 1].y) {
            lines[k++] = j;
        }
    }
    lines[k++] = s->n - 1;
    if (k - 2 < 2) return;
    start = lines[k - 3] + 1;
    for (j = k - 2; j < k; j++) {
        last = lines[j];
        off = b->cx + (b->cx - b->w) - ((Glyph *)s)[last + 1].lw - b->w;
        for (i = start; i < last + 1; i++) {
            ((Glyph *)s)[i + 1].x += off;
        }
        start = last + 1;
    }
}

s32 func_0010d388(char *buf, const char *fmt, ...) {
    va_list ap;
    s32 n;
    __builtin_stdarg_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    for (n = 0; *buf != 0; n++) {
        if (*buf == ' ') {
            *buf = 1;
        } else {
            *buf -= 15;
        }
        buf++;
    }
    return n;
}

typedef struct {
    u16 pad0;
    u16 n;
    u8 pad[0x180c];
    f32 w[1];
} WeightBlk;

/* 1 if every weight at +0x1810 is zero. */
s32 func_0010ce00(WeightBlk *b) {
    s32 i;
    for (i = 0; i < b->n; i++) {
        if (b->w[i] != 0.0f) return 0;
    }
    return 1;
}

void func_0010e430(Fade *f) {
    switch (f->state) {
    case 1:
        if (f->cb != NULL) {
            if (!(f->flags & 1)) {
                f->flags |= 1;
                f->cnt++;
            }
            f->cb(f->cnt, f->arg);
        }
        break;
    case 0:
        f->b12 = 0;
        if (f->res != NULL) {
            func_00121ee0(f->res);
            f->res = NULL;
        }
        if (f->cb != NULL) {
            f->cnt++;
            f->cb(f->cnt, f->arg);
        }
        break;
    }
}

typedef struct { u16 x0; u8 pad2[10]; u8 xc; } W29Sub;
typedef struct { u8 pad0[0x12]; u8 x12; u8 pad13[0xd]; W29Sub *x20; s32 x24; } W29Obj;
typedef struct { u32 lo:13; u32 b13:1; u32 hi:18; } F29;
extern F29 D_002C5958;
void func_00106d48(s32);
s32 func_0010c540(s32, s32 *);
void func_0010ce50(W29Obj *, s32);
s32 func_0010d0c0(W29Sub *, W29Obj *);
void func_0010d470(W29Obj *, W29Sub *);
W29Sub *func_00121e28(s32, W29Sub **);

void func_0010e4f0(W29Obj *o) {
    s32 n, r;
    s32 buf[2];
    if (D_002C1304 == 1) return;
    if (D_002C5958.b13 == 1) return;
    switch (o->x12) {
    case 0:
        if (o->x20 == NULL) {
            o->x20 = func_00121e28(0x1890, &o->x20);
        }
        func_0010d470(o, o->x20);
        o->x12 = 1;
        o->x20->xc = 0;
    case 1:
        n = func_0010d0c0(o->x20, o);
        func_0010ce50(o, n);
        r = func_0010c540(n, buf);
        func_0010cb80((GlyphStr *)o->x20, n, buf[0], (TextBox *)o->x24);
        func_00106d48(r);
        if (n == o->x20->x0 && func_0010ce00((WeightBlk *)o->x20)) {
            func_0010e430((Fade *)o);
        }
        break;
    }
}

/* func_0010a248 only matches with func_00109f88 defined above it. */
extern u8 D_002BC210[];
#include "data/pieces/D_002B677C.h"
f32 D_0049517C ALIGNED(4);
extern s32 func_00106978(s32);

void func_00109f88(void) {
    sceGsSetDefLoadImage(D_002BC1B0, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(D_002BC1B0, (void *)D_002B677C);
    sceGsSetDefLoadImage(D_002BC210, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(D_002BC210, (void *)(D_002B677C + 0x48000));
}

s32 func_0010a248(void) {
    switch (D_00495180) {
    case 0: func_00106978(32); D_00495180++; D_0049517C = 64.0f;
    case 1:
        if (!(D_0049517C <= 0.0f)) {
            func_00109f88(); D_002B6668 = 0x180808080ull;
            func_00106b18(D_002B66B0); D_0049517C -= D_002BBDFC; return 0;
        }
        D_002B6774 = 0; return 4;
    }
    return 0;
}

/* needs make: uses rodata */
void func_00100670(u32 arg0, s32 arg1) {
    Obj10 *o = func_0015ed80(arg1, func_00108d90);
    switch (arg0) {
    case 1:
        o->p = &D_00494210[D_00351BD0];
        break;
    case 3:
        o->p = &D_00494250[D_00351BD0];
        break;
    case 0:
        o->p = &D_004941D0[D_00351BD0];
        break;
    case 6:
        o->p = &D_00494290[D_00351BD0];
        break;
    case 7:
        o->p = &D_004942D0[D_00351BD0];
        break;
    }
}

#include "data/bss_0049_typed.h"
#include "data/data_0029.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0035.h"
#include "data/data_0048.h"
#include "data/data_0046.h"
#include "data/data_0047.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002B6490.h"
