/* The KeShpDtt draw helpers, -fno-strict-aliasing (docs/modules.md "Session 49"):
 * func_001a99e8 writes a sprite batch's GS set up (TEX0, CLAMP, the frame's
 * scissor from s->d48) and loads the VU0 registers the second uses;
 * func_001a9c30 projects one point with them and writes its 608-byte packet
 * (nine quads in a fan), returning 0 when it is clipped.  Both almost all
 * inline VU0 asm; pppKeShpDttDraw calls them.  Read from the code, not
 * proved by a boot. */
#include "common.h"
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
    func_001aa9d0(144);
}


typedef unsigned int u128 __attribute__((mode(TI)));

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
    register W8Dtt *p asm("$6") = d;
    register u8 *q asm("$4") = p->p24;
    register s32 r asm("$5");

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
    if (r != 128) {
        s32 t = buf[2];
        p->p24 = q + 608;
        p->x2C = t;
        return 1;
    }
    return 0;
}
