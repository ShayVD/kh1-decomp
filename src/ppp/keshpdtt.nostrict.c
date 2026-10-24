/* The KeShpDtt draw helpers, -fno-strict-aliasing (docs/modules.md "Session 49"):
 * func_001a99e8 writes a sprite batch's GS set up (TEX0, CLAMP, the frame's
 * scissor from s->d48) and loads the VU0 registers the second uses;
 * func_001a9c30 projects one point with them and writes its 608-byte packet
 * (nine quads in a fan), returning 0 when it is clipped.  Both almost all
 * inline VU0 asm; pppKeShpDttDraw calls them.  Read from the code, not
 * proved by a boot. */
#include "common.h"
#ifndef KH1_PS2
#include "platform/vu.h"
#endif
typedef struct { s32 a, b; } W8;
typedef struct {
    u8 pad0[0x20];
    f32 *p20;
    s32 pad24;
    f32 *p28;
    s32 pad2c;
    f32 v30[3];
    s32 w3c;
    u64 d40;
    u64 d48;
    u16 h50;
    u16 h52;
    u16 h54;
    u16 h56;
} S99e8;
extern W8 D_0061E860;
typedef struct { u64 lo : 32; u64 hi : 32; } B16;
u64 *func_001aa950(s32);
void func_001aa9d0(s32);
void func_001a99e8(S99e8 *s) {
    u64 *p = func_001aa950(144);
    u64 r;
    p[0] = 0x4000000000000001ULL;
    p[1] = 0xEEEE;
    p[2] = (s->d40 & 0xFFFFFFFC03FFFFFFULL) | (0xAAULL << 26);
    p[3] = 6;
    if (s->w3c & 4) p[4] = 0x31001;
    else p[4] = 0x71001;
    p[5] = 71;
    p[6] = 68;
    p[7] = 66;
    r = s->d48;
    p[8] = ((r & 0x7ff) << 4) | (((r & 0x7ff00000000ULL) >> 32) << 24) | ((((r & 0x7ff0000) >> 16) - 1) << 14) | 10 | ((((r & 0x7ff000000000000ULL) >> 48) - 1) << 34);
    p[9] = 8;
    p[10] = 0x302EC0000000000AULL;
    p[11] = 1042;
    p[12] = 0x1000000000008001ULL;
    p[13] = 14;
    ((s32 *)p)[28] = D_0061E860.a;
    ((s32 *)p)[29] = D_0061E860.b;
    p[15] = 71;
    { u64 a = (u64)s->h50 - 8; ((B16 *)&p[16])->lo = a; }
    { u64 b = (u64)s->h54 - 8; ((B16 *)&p[16])->hi = b; }
#ifdef KH1_PS2
    __asm__ volatile(
        "lqc2 $vf25, 0(%0)\n"
        "lqc2 $vf27, 16(%0)\n"
        "lqc2 $vf29, 32(%0)\n"
        "lqc2 $vf21, 48(%0)\n"
        "lqc2 $vf14, 64(%0)\n"
        "lqc2 $vf20, 80(%0)\n"
        "lqc2 $vf9, 96(%0)\n"
        "lqc2 $vf3, 112(%0)\n"
        "lqc2 $vf2, 0(%2)\n"
        "lqc2 $vf31, 16(%2)\n"
        "vadd.y $vf2y, $vf0y, $vf31y\n"
        "lui $2, 0x3a80\n"
        "qmtc2 $2, $vf24\n"
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 16(%1)\n"
        "lqc2 $vf6, 32(%1)\n"
        "lqc2 $vf7, 48(%1)\n"
        "lqc2 $vf11, 128(%0)\n"
        "vitof4.xyzw $vf11xyzw, $vf11xyzw\n"
        "lqc2 $vf31, 80(%3)\n"
        "vmove.x $vf15x, $vf0x\n"
        "vaddw.y $vf15y, $vf0y, $vf31w\n"
        "vaddz.x $vf17x, $vf0x, $vf31z\n"
        "vmove.y $vf17y, $vf0y\n"
        "lui $2, 0x3f35\n"
        "ori $2, $2, 0x4f3\n"
        "dsll $2, $2, 16\n"
        "ori $2, $2, 0x3f35\n"
        "dsll $2, $2, 16\n"
        "ori $2, $2, 0x4f3\n"
        "qmtc2 $2, $vf16\n"
        "vmul.xy $vf16xy, $vf16xy, $vf2xy\n"
        "lqc2 $vf1, 48(%3)\n"
        "vmul.xy $vf1xy, $vf2xy, $vf1xy\n"
        "vmulz.xy $vf18xy, $vf2xy, $vf1z\n"
        "vmulz.xy $vf19xy, $vf16xy, $vf1z\n"
        "vmul.x $vf16x, $vf16x, $vf17x\n"
        "vmul.y $vf16y, $vf16y, $vf15y\n"
        "vmul.y $vf15y, $vf15y, $vf2y\n"
        "vmul.x $vf17x, $vf17x, $vf2x\n"
        "lui $2, 0x4580\n"
        "qmtc2 $2, $vf28\n"
        "vaddx.y $vf28y, $vf0y, $vf28x\n"
        "vaddw.z $vf26z, $vf0z, $vf0w\n"
        "vsubw.w $vf30w, $vf0w, $vf0w\n"
        : : "r"(p), "r"(s->p28), "r"(s->p20), "r"(s) : "$2", "memory");
#else
    /* tools/host/vu2c.py */
    {
        u64 g2;
        PlatVu0Lq(25, (void *)(p));
        PlatVu0Lq(27, (u8 *)(p) + 16);
        PlatVu0Lq(29, (u8 *)(p) + 32);
        PlatVu0Lq(21, (u8 *)(p) + 48);
        PlatVu0Lq(14, (u8 *)(p) + 64);
        PlatVu0Lq(20, (u8 *)(p) + 80);
        PlatVu0Lq(9, (u8 *)(p) + 96);
        PlatVu0Lq(3, (u8 *)(p) + 112);
        PlatVu0Lq(2, (void *)(s->p20));
        PlatVu0Lq(31, (u8 *)(s->p20) + 16);
        PlatVu0Fmac(PLAT_VU0_ADD, 2, 4, 0, 31, -1);
        g2 = (u64)(s64)(s32)0x3a800000;
        PlatVu0Qmtc2(24, g2);
        PlatVu0Lq(4, (void *)(s->p28));
        PlatVu0Lq(5, (u8 *)(s->p28) + 16);
        PlatVu0Lq(6, (u8 *)(s->p28) + 32);
        PlatVu0Lq(7, (u8 *)(s->p28) + 48);
        PlatVu0Lq(11, (u8 *)(p) + 128);
        PlatVu0Itof(11, 15, 11, 4);
        PlatVu0Lq(31, (u8 *)(s) + 80);
        PlatVu0Move(15, 8, 0);
        PlatVu0Fmac(PLAT_VU0_ADD, 15, 4, 0, 31, 3);
        PlatVu0Fmac(PLAT_VU0_ADD, 17, 8, 0, 31, 2);
        PlatVu0Move(17, 4, 0);
        g2 = (u64)(s64)(s32)0x3f350000;
        g2 = g2 | 0x4f3;
        g2 = (u64)g2 << 16;
        g2 = g2 | 0x3f35;
        g2 = (u64)g2 << 16;
        g2 = g2 | 0x4f3;
        PlatVu0Qmtc2(16, g2);
        PlatVu0Fmac(PLAT_VU0_MUL, 16, 12, 16, 2, -1);
        PlatVu0Lq(1, (u8 *)(s) + 48);
        PlatVu0Fmac(PLAT_VU0_MUL, 1, 12, 2, 1, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 18, 12, 2, 1, 2);
        PlatVu0Fmac(PLAT_VU0_MUL, 19, 12, 16, 1, 2);
        PlatVu0Fmac(PLAT_VU0_MUL, 16, 8, 16, 17, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 16, 4, 16, 15, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 15, 4, 15, 2, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 17, 8, 17, 2, -1);
        g2 = (u64)(s64)(s32)0x45800000;
        PlatVu0Qmtc2(28, g2);
        PlatVu0Fmac(PLAT_VU0_ADD, 28, 4, 0, 28, 0);
        PlatVu0Fmac(PLAT_VU0_ADD, 26, 2, 0, 0, 3);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 1, 0, 0, 3);
    }
#endif
    func_001aa9d0(144);
}


typedef kh1_u128 u128;

typedef struct {
    f32 v[4];
    f32 col[4];
    void *p20;
    u8 *p24;
    void *p28;
    s32 x2C;
} W8Dtt;

s32 func_001a9c30(W8Dtt *d) {
    s32 buf[4];
    register W8Dtt *p KH1_REG("$6") = d;
    register u8 *q KH1_REG("$4") = p->p24;
    register s32 r KH1_REG("$5");

#ifdef KH1_PS2
    __asm__ volatile(
        ".set noreorder\n"
        "lqc2 $vf8, 0($6)\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "vdiv Q, $vf0w, $vf12w\n"
        "vwaitq \n"
        "vmulq.xyz $vf12xyz, $vf12xyz, Q\n"
        "vmulq.y $vf15y, $vf15y, Q\n"
        "vmulq.xy $vf16xy, $vf16xy, Q\n"
        "vmulq.x $vf17x, $vf17x, Q\n"
        "vmove.zw $vf10zw, $vf12zw\n"
        "vsub.x $vf10x, $vf12x, $vf17x\n"
        "vsub.y $vf10y, $vf12y, $vf15y\n"
        "vadd.x $vf13x, $vf17x, $vf17x\n"
        "vadd.y $vf13y, $vf15y, $vf15y\n"
        "vsub.xy $vf13xy, $vf28xy, $vf13xy\n"
        "ctc2 $0, $vi16\n"
        "vsub.xyw $vf0xyw, $vf10xyw, $vf0xyw\n"
        "vsub.xy $vf0xy, $vf13xy, $vf10xy\n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "cfc2 $5, $vi16\n"
        "andi $5, $5, 0x80\n"
        "bnez $5, .Lw8a_001A9E40\n"
        "nop \n"
        "vnop \n"
        "vmulq.xy $vf22xy, $vf18xy, Q\n"
        "vmulq.xy $vf23xy, $vf19xy, Q\n"
        "vmulq.xy $vf31xy, $vf1xy, Q\n"
        "vadd.xy $vf11xy, $vf11xy, $vf31xy\n"
        "lqc2 $vf31, 16($6)\n"
        "vftoi0.xyzw $vf31xyzw, $vf31xyzw\n"
        "sqc2 $vf31, 112($4)\n"
        "lb $2, 60($6)\n"
        "andi $2, $2, 0x1\n"
        "bnez $2, .Lw8a_001A9CE8\n"
        "nop \n"
        "nop \n"
        "vsub.w $vf31w, $vf0w, $vf0w\n"
        ".Lw8a_001A9CE8:\n"
        "sqc2 $vf25, 0($4)\n"
        "sqc2 $vf27, 16($4)\n"
        "sqc2 $vf29, 32($4)\n"
        "sqc2 $vf21, 48($4)\n"
        "sqc2 $vf14, 64($4)\n"
        "sqc2 $vf20, 80($4)\n"
        "sqc2 $vf31, 160($4)\n"
        "sqc2 $vf31, 208($4)\n"
        "sqc2 $vf31, 256($4)\n"
        "sqc2 $vf31, 304($4)\n"
        "sqc2 $vf31, 352($4)\n"
        "sqc2 $vf31, 400($4)\n"
        "sqc2 $vf31, 448($4)\n"
        "sqc2 $vf31, 496($4)\n"
        "sqc2 $vf31, 544($4)\n"
        "sqc2 $vf9, 576($4)\n"
        "sqc2 $vf3, 592($4)\n"
        "vftoi4.xyz $vf30xyz, $vf12xyz\n"
        "sqc2 $vf30, 128($4)\n"
        "vsub.xy $vf30xy, $vf12xy, $vf11xy\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 96($4)\n"
        "vadd.xy $vf10xy, $vf12xy, $vf15xy\n"
        "vftoi4.xyz $vf30xyz, $vf10xyz\n"
        "sqc2 $vf30, 176($4)\n"
        "sqc2 $vf30, 560($4)\n"
        "vsub.xy $vf30xy, $vf10xy, $vf11xy\n"
        "vadd.y $vf30y, $vf30y, $vf22y\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 144($4)\n"
        "sqc2 $vf26, 528($4)\n"
        "vadd.xy $vf10xy, $vf12xy, $vf16xy\n"
        "vftoi4.xyz $vf30xyz, $vf10xyz\n"
        "sqc2 $vf30, 224($4)\n"
        "vsub.xy $vf30xy, $vf10xy, $vf11xy\n"
        "vadd.xy $vf30xy, $vf30xy, $vf23xy\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 192($4)\n"
        "vadd.xy $vf10xy, $vf12xy, $vf17xy\n"
        "vftoi4.xyz $vf30xyz, $vf10xyz\n"
        "sqc2 $vf30, 272($4)\n"
        "vsub.xy $vf30xy, $vf10xy, $vf11xy\n"
        "vadd.x $vf30x, $vf30x, $vf22x\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 240($4)\n"
        "vadd.x $vf10x, $vf12x, $vf16x\n"
        "vsub.y $vf10y, $vf12y, $vf16y\n"
        "vftoi4.xyz $vf30xyz, $vf10xyz\n"
        "sqc2 $vf30, 320($4)\n"
        "vsub.xy $vf30xy, $vf10xy, $vf11xy\n"
        "vadd.x $vf30x, $vf30x, $vf23x\n"
        "vsub.y $vf30y, $vf30y, $vf23y\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 288($4)\n"
        "vsub.xy $vf10xy, $vf12xy, $vf15xy\n"
        "vftoi4.xyz $vf30xyz, $vf10xyz\n"
        "sqc2 $vf30, 368($4)\n"
        "vsub.xy $vf30xy, $vf10xy, $vf11xy\n"
        "vsub.y $vf30y, $vf30y, $vf22y\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 336($4)\n"
        "vsub.xy $vf10xy, $vf12xy, $vf16xy\n"
        "vftoi4.xyz $vf30xyz, $vf10xyz\n"
        "sqc2 $vf30, 416($4)\n"
        "vsub.xy $vf30xy, $vf10xy, $vf11xy\n"
        "vsub.xy $vf30xy, $vf30xy, $vf23xy\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 384($4)\n"
        "vsub.xy $vf10xy, $vf12xy, $vf17xy\n"
        "vftoi4.xyz $vf30xyz, $vf10xyz\n"
        "sqc2 $vf30, 464($4)\n"
        "vsub.xy $vf30xy, $vf10xy, $vf11xy\n"
        "vsub.x $vf30x, $vf30x, $vf22x\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 432($4)\n"
        "vsub.x $vf10x, $vf12x, $vf16x\n"
        "vadd.y $vf10y, $vf12y, $vf16y\n"
        "vftoi4.xyz $vf30xyz, $vf10xyz\n"
        "sqc2 $vf30, 512($4)\n"
        "vsub.xy $vf30xy, $vf10xy, $vf11xy\n"
        "vsub.x $vf30x, $vf30x, $vf23x\n"
        "vadd.y $vf30y, $vf30y, $vf23y\n"
        "vmulx.xy $vf26xy, $vf30xy, $vf24x\n"
        "sqc2 $vf26, 480($4)\n"
        "sqc2 $vf12, 0($29)\n"
        "add $5, $0, $0\n"
        ".Lw8a_001A9E40:\n"
        ".set reorder\n"
        : "=r"(r), "=m"(buf[0])
        : "r"(p), "r"(q)
        : "$2", "memory");
#else
    /* tools/host/vu2c.py */
    {
        u64 g2;
        PlatVu0Lq(8, (void *)(p));
        PlatVu0Fmac(PLAT_VU0_MUL, PLAT_VU0_ACC, 15, 4, 8, 0);
        PlatVu0Fmac(PLAT_VU0_MADD, PLAT_VU0_ACC, 15, 5, 8, 1);
        PlatVu0Fmac(PLAT_VU0_MADD, PLAT_VU0_ACC, 15, 6, 8, 2);
        PlatVu0Fmac(PLAT_VU0_MADD, 12, 15, 7, 8, 3);
        PlatVu0Div(0, 3, 12, 3);
        PlatVu0Fmac(PLAT_VU0_MUL, 12, 14, 12, 0, PLAT_VU0_BC_Q);
        PlatVu0Fmac(PLAT_VU0_MUL, 15, 4, 15, 0, PLAT_VU0_BC_Q);
        PlatVu0Fmac(PLAT_VU0_MUL, 16, 12, 16, 0, PLAT_VU0_BC_Q);
        PlatVu0Fmac(PLAT_VU0_MUL, 17, 8, 17, 0, PLAT_VU0_BC_Q);
        PlatVu0Move(10, 3, 12);
        PlatVu0Fmac(PLAT_VU0_SUB, 10, 8, 12, 17, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 10, 4, 12, 15, -1);
        PlatVu0Fmac(PLAT_VU0_ADD, 13, 8, 17, 17, -1);
        PlatVu0Fmac(PLAT_VU0_ADD, 13, 4, 15, 15, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 13, 12, 28, 13, -1);
        PlatVu0.stat = 0;
        PlatVu0Fmac(PLAT_VU0_SUB, 0, 13, 10, 0, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 0, 12, 13, 10, -1);
        r = PlatVu0.stat;
        r = r & 0x80;
        if (r != 0)
            goto Lw8a_001A9E40;
        PlatVu0Fmac(PLAT_VU0_MUL, 22, 12, 18, 0, PLAT_VU0_BC_Q);
        PlatVu0Fmac(PLAT_VU0_MUL, 23, 12, 19, 0, PLAT_VU0_BC_Q);
        PlatVu0Fmac(PLAT_VU0_MUL, 31, 12, 1, 0, PLAT_VU0_BC_Q);
        PlatVu0Fmac(PLAT_VU0_ADD, 11, 12, 11, 31, -1);
        PlatVu0Lq(31, (u8 *)(p) + 16);
        PlatVu0Ftoi(31, 15, 31, 0);
        PlatVu0Sq(31, (u8 *)(q) + 112);
        g2 = (u64)(s64)*(s8 *)((u8 *)(p) + 60);
        g2 = g2 & 0x1;
        if (g2 != 0)
            goto Lw8a_001A9CE8;
        PlatVu0Fmac(PLAT_VU0_SUB, 31, 1, 0, 0, -1);
    Lw8a_001A9CE8:;
        PlatVu0Sq(25, (void *)(q));
        PlatVu0Sq(27, (u8 *)(q) + 16);
        PlatVu0Sq(29, (u8 *)(q) + 32);
        PlatVu0Sq(21, (u8 *)(q) + 48);
        PlatVu0Sq(14, (u8 *)(q) + 64);
        PlatVu0Sq(20, (u8 *)(q) + 80);
        PlatVu0Sq(31, (u8 *)(q) + 160);
        PlatVu0Sq(31, (u8 *)(q) + 208);
        PlatVu0Sq(31, (u8 *)(q) + 256);
        PlatVu0Sq(31, (u8 *)(q) + 304);
        PlatVu0Sq(31, (u8 *)(q) + 352);
        PlatVu0Sq(31, (u8 *)(q) + 400);
        PlatVu0Sq(31, (u8 *)(q) + 448);
        PlatVu0Sq(31, (u8 *)(q) + 496);
        PlatVu0Sq(31, (u8 *)(q) + 544);
        PlatVu0Sq(9, (u8 *)(q) + 576);
        PlatVu0Sq(3, (u8 *)(q) + 592);
        PlatVu0Ftoi(30, 14, 12, 4);
        PlatVu0Sq(30, (u8 *)(q) + 128);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 12, 11, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 96);
        PlatVu0Fmac(PLAT_VU0_ADD, 10, 12, 12, 15, -1);
        PlatVu0Ftoi(30, 14, 10, 4);
        PlatVu0Sq(30, (u8 *)(q) + 176);
        PlatVu0Sq(30, (u8 *)(q) + 560);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 10, 11, -1);
        PlatVu0Fmac(PLAT_VU0_ADD, 30, 4, 30, 22, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 144);
        PlatVu0Sq(26, (u8 *)(q) + 528);
        PlatVu0Fmac(PLAT_VU0_ADD, 10, 12, 12, 16, -1);
        PlatVu0Ftoi(30, 14, 10, 4);
        PlatVu0Sq(30, (u8 *)(q) + 224);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 10, 11, -1);
        PlatVu0Fmac(PLAT_VU0_ADD, 30, 12, 30, 23, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 192);
        PlatVu0Fmac(PLAT_VU0_ADD, 10, 12, 12, 17, -1);
        PlatVu0Ftoi(30, 14, 10, 4);
        PlatVu0Sq(30, (u8 *)(q) + 272);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 10, 11, -1);
        PlatVu0Fmac(PLAT_VU0_ADD, 30, 8, 30, 22, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 240);
        PlatVu0Fmac(PLAT_VU0_ADD, 10, 8, 12, 16, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 10, 4, 12, 16, -1);
        PlatVu0Ftoi(30, 14, 10, 4);
        PlatVu0Sq(30, (u8 *)(q) + 320);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 10, 11, -1);
        PlatVu0Fmac(PLAT_VU0_ADD, 30, 8, 30, 23, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 4, 30, 23, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 288);
        PlatVu0Fmac(PLAT_VU0_SUB, 10, 12, 12, 15, -1);
        PlatVu0Ftoi(30, 14, 10, 4);
        PlatVu0Sq(30, (u8 *)(q) + 368);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 10, 11, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 4, 30, 22, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 336);
        PlatVu0Fmac(PLAT_VU0_SUB, 10, 12, 12, 16, -1);
        PlatVu0Ftoi(30, 14, 10, 4);
        PlatVu0Sq(30, (u8 *)(q) + 416);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 10, 11, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 30, 23, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 384);
        PlatVu0Fmac(PLAT_VU0_SUB, 10, 12, 12, 17, -1);
        PlatVu0Ftoi(30, 14, 10, 4);
        PlatVu0Sq(30, (u8 *)(q) + 464);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 10, 11, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 8, 30, 22, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 432);
        PlatVu0Fmac(PLAT_VU0_SUB, 10, 8, 12, 16, -1);
        PlatVu0Fmac(PLAT_VU0_ADD, 10, 4, 12, 16, -1);
        PlatVu0Ftoi(30, 14, 10, 4);
        PlatVu0Sq(30, (u8 *)(q) + 512);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 12, 10, 11, -1);
        PlatVu0Fmac(PLAT_VU0_SUB, 30, 8, 30, 23, -1);
        PlatVu0Fmac(PLAT_VU0_ADD, 30, 4, 30, 23, -1);
        PlatVu0Fmac(PLAT_VU0_MUL, 26, 12, 30, 24, 0);
        PlatVu0Sq(26, (u8 *)(q) + 480);
        PlatVu0Sq(12, (void *)(buf));
        r = 0;
    Lw8a_001A9E40:;
    }
#endif
    if (r != 128) {
        s32 t = buf[2];
        p->p24 = q + 608;
        p->x2C = t;
        return 1;
    }
    return 0;
}
