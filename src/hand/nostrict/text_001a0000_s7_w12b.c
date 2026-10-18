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


