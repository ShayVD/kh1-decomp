/* Round 62d (wwm2): score 113 -> 23, 3556 vs 3560 bytes (the 4 bytes are the trailing alignment nop). D_00F2C708 = 18/23 written `if (!D_00F26E10) 23; else 18`, b = 2 set before a = 1 in the 364 arm, and case 18 ends `if (S[0] == 4 || S[1] == 4) {19/20} } D_00F2C708 = 23;` so the 23 store is shared. Left: case 27's v0/v1 swap, one beqz that we fill as beqzl, and case 31's lui register. */
/* Round 62c (wwm2): score 177 -> 113: cases 19, 20 and 21 are three full copies of the menu (func_001efc10(11/12/13)) instead of one copy reached by goto with msg; cross-jumping merges them back as in the target, with the D_002C5AD0 high part set in each case. */
/* Round 62b (wwm2): score 259 -> 177, 3564 vs 3560 bytes; the callee sequence now matches. case 4/9/14 moved between cases 13 and 15 (the target's block order). case 18 tests `S[0] == 2 || S[1] == 2` first and only then the both-2 case, and the 19/20 arms are swapped. func_00111600 takes three arguments (as in src/game/progress.c), so no & args are computed. case 31 reads D_003F720C once into a local. case 27 decrements D_00F2C6FC before the D_002BC07C == 128 test. Left: the case 18 jump threading (the target reuses the loaded S[0] and S[1]) and the placement of the D_002C5AD0 high part (s3). */
/* Round 62 (wwm2): score 374 -> 259, size 3464 -> 3604 vs 3560 bytes (the gap goes from 96 to 44). (1) func_00f21068 returns s32, from wwm1's rettype.py: 374 -> 370. (2) The trig test is `(trig & 0x20000020) ? 1 : (trig & 0x80000080) != 0`, so fold does not merge the two masks into one 0xA00000A0 test. Gives the target's two tests. (3) In both menu copies, a and b are set before the func_0020bc48 call (they live across it in s0/s1, as in the target). Cross-jumping then stops at the D_00F26E10 test, and case 22 keeps its own func_001f1ed8 / trig / xor copy, so the callee sequence matches the target's. Left: the extra bytes are in small hunks across the function. */
/* dktitle.x func_00f228c8: near-miss draft (session 132), not byte-identical; the port runs it (ovl/dktitle/drafts.tsv). Session 141 round 21 (wwm1): score 408 -> 398 with sclimb.py. Round 22 (wwm1): the if/else at line(s) 149,357 with the arms swapped and the test negated (ifswap.py): score 398 -> 378. Round 23 (wwm1): score 378 -> 374 with w4.py (dependency-checked statement order plus if/else polarity flips). */

typedef struct { s32 x0; s32 x4; u64 x8; } Pad;
typedef struct { void (*f0)(s32, s32); s32 (*f1)(void); } Cb;
typedef struct { u8 pad[8]; s32 a; s32 b; } Ent;
typedef struct { f32 v; s32 st; s32 t; } Fade;

void func_00106780(s32);
void func_00106a58(s32);
void func_00106b18(void *);
void func_00109268(void);
void func_00109558(s32);
void func_00110448(s32);
void func_00111600(s32, s32, s32);
s32 func_001117e0(void); CONTEXT_ONLY s32 func_001117e0() { return 0; }
void func_00111830(void); CONTEXT_ONLY void func_00111830() {}
void func_0011c5e8(void);
void func_0011c7a8(s32, s32, s32, s32, s32, s32);
void func_0011d140(s32, s32);
void func_0011d768(s32);
Ent *func_00120190(void *);
void func_00120748(void *, void *, void *, s32);
s32 func_001efc10(s32);
void func_001f1ed8(s32, s32, s32, s32, s32);
void func_001fd100(s32, s32);
void func_00207630(s32, s32, s32, s32, s32, s32, s32);
void func_00207748(s32, s32, s32, s32);
void func_0020b968(void);
void func_0020b998(void);
void func_0020bb90(s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bdf0(void);
void func_0020d748(void); CONTEXT_ONLY void func_0020d748() {}
void func_0022bcb8(s32);
void func_0022d080(s32);
void func_00233158(void); CONTEXT_ONLY void func_00233158() {}
s32 func_00233168(void);
void func_00f20020(void);
void func_00f20118(void *);
void func_00f20198(void);
void func_00f20860(void);
void func_00f208a8(void); CONTEXT_ONLY void func_00f208a8() {}
void func_00f20da0(void *);
void func_00f20f30(void);
void func_00f20f98(void); CONTEXT_ONLY void func_00f20f98() {}
void func_00f21000(void); CONTEXT_ONLY void func_00f21000() {}
s32 func_00f21068(void); CONTEXT_ONLY s32 func_00f21068() { return 0; }
void func_00f213a8(void); CONTEXT_ONLY void func_00f213a8() {}
void func_00f21808(void); CONTEXT_ONLY void func_00f21808() {}
void func_00f21928(void);
void func_00f21ca0(void);
void func_00f22238(void); CONTEXT_ONLY void func_00f22238() {}
void func_00f227b0(void);
void func_00f227e0(void);
void func_00f227f8(void);
void func_00f22880(void);
void func_00f228a0(void); CONTEXT_ONLY void func_00f228a0() {}
extern s32 D_002A3F44, D_002A6B80, D_002B6478, D_002B6480, D_002B6774, D_002BBD40, D_002BBE0C;
extern s32 D_002BC07C, D_002BC128, D_002BC130, D_002BC134, D_002BC73C, D_002BCDA8;
extern Pad D_002C5AD0;
extern s32 D_003F34A4, D_003F720C, D_003F73A4;
extern s32 D_003F8370[2];
extern s32 (*D_0046A6A4)(void);
extern u8 D_009A0000[];
extern u8 D_00F26DA0[];
extern s32 D_00F26E10, D_00F26E14, D_00F26E18;
extern Cb D_00F27220;
extern u8 D_00F272E8[], D_00F27300[], D_00F27318[], D_00F27330[], D_00F27340[];
extern void *D_00F2C6F8;
extern s32 D_00F2C6FC, D_00F2C700, D_00F2C704, D_00F2C708;
extern Fade D_00F2C738, D_00F2C748, D_00F2C758, D_00F2C768, D_00F2C778, D_00F2C788, D_00F2C798;
extern Fade D_00F2C7A8, D_00F2C7B8, D_00F2C7C8, D_00F2C7D8, D_00F2C7E8, D_00F2C7F8;
extern Fade D_00F2C808, D_00F2C818, D_00F2C828, D_00F2C838, D_00F2C848, D_00F2C860, D_00F2C870, D_00F2C880;

s32 func_00f228c8(void) {
    s32 a, b, msg;
    Ent *e;
    u64 trig;

    if (D_002B6774 != 0) return 0;
    if (D_00F26E14 == 0) {
        D_002BBE0C = 0;
        D_00F26E14 = 1;
    }
    D_00F2C6F8 = 0;
    func_00f20020();
    switch (D_00F2C708) {
    case 0:
        D_002B6478 = D_0046A6A4();
        if (D_002B6478 == 3) D_00F2C708 = 1;
        else D_00F2C708 = 2;
        break;
    case 1:
        func_00106b18(D_00F26DA0);
        func_001fd100(11, 139);
        func_001f1ed8(0x64FFFFFF, 53, 144, func_001efc10(10), 15);
        func_00207748(1, 380, 220, 90);
        if ((s32)D_002C5AD0.x8 & 0x2000) {
            func_0011d768(2);
            D_00F2C708 = 2;
        }
        break;
    case 2:
        D_00F26E10 = 1;
        func_00233158();
        func_0020b968();
        func_0020bb90(460, 220);
        D_00F2C708 = 3;
        break;
    case 18:
        if (func_00233168() != 1) break;
        if (D_00F26E18 && D_003F8370[0] == 4 && D_003F8370[1] == 4) {
            D_00F2C708 = 22;
            break;
        }
        D_00F26E18 = 1;
        if (D_003F8370[0] == 2 || D_003F8370[1] == 2) {
            if (D_003F8370[0] == 2 && D_003F8370[1] == 2) {
                D_00F2C708 = 21;
                goto c21;
            }
            if (D_003F8370[0] == 4 || D_003F8370[1] == 4) {
                if (D_003F8370[0] == 2) {
                    D_00F2C708 = 19;
                    goto c19;
                } else {
                    D_00F2C708 = 20;
                    goto c20;
                }
            }
        }
        D_00F2C708 = 23;
        break;
    case 19:
    c19:
        func_00f22880();
        func_00106b18(D_00F26DA0);
        func_001fd100(23, 139);
        func_001f1ed8(0x64FFFFFF, 65, 144, func_001efc10(11), 15);
        trig = D_002C5AD0.x8;
        if ((trig & 0x20000020) ? 1 : (trig & 0x80000080) != 0) {
            func_0011d768(1);
            D_00F26E10 ^= 1;
        }
        if (!(D_00F26E10)) {
            b = 2; a = 1;
            func_0020bc48(8, 364, 220);
        } else {
            a = 2; b = 1;
            func_0020bc48(8, 460, 220);
        }
        func_00207630(a, 0, 274, 220, 90, 300, 44);
        func_00207630(b, 0, 370, 220, 90, 396, 45);
        func_0020b998();
        func_0020bdf0();
        if ((s32)D_002C5AD0.x8 & 0x2000) {
            func_0011d768(2);
            if (!D_00F26E10) D_00F2C708 = 23;
            else D_00F2C708 = 18;
        }
        break;
    case 20:
    c20:
        func_00f22880();
        func_00106b18(D_00F26DA0);
        func_001fd100(23, 139);
        func_001f1ed8(0x64FFFFFF, 65, 144, func_001efc10(12), 15);
        trig = D_002C5AD0.x8;
        if ((trig & 0x20000020) ? 1 : (trig & 0x80000080) != 0) {
            func_0011d768(1);
            D_00F26E10 ^= 1;
        }
        if (!(D_00F26E10)) {
            b = 2; a = 1;
            func_0020bc48(8, 364, 220);
        } else {
            a = 2; b = 1;
            func_0020bc48(8, 460, 220);
        }
        func_00207630(a, 0, 274, 220, 90, 300, 44);
        func_00207630(b, 0, 370, 220, 90, 396, 45);
        func_0020b998();
        func_0020bdf0();
        if ((s32)D_002C5AD0.x8 & 0x2000) {
            func_0011d768(2);
            if (!D_00F26E10) D_00F2C708 = 23;
            else D_00F2C708 = 18;
        }
        break;
    case 21:
    c21:
        func_00f22880();
        func_00106b18(D_00F26DA0);
        func_001fd100(23, 139);
        func_001f1ed8(0x64FFFFFF, 65, 144, func_001efc10(13), 15);
        trig = D_002C5AD0.x8;
        if ((trig & 0x20000020) ? 1 : (trig & 0x80000080) != 0) {
            func_0011d768(1);
            D_00F26E10 ^= 1;
        }
        if (!(D_00F26E10)) {
            b = 2; a = 1;
            func_0020bc48(8, 364, 220);
        } else {
            a = 2; b = 1;
            func_0020bc48(8, 460, 220);
        }
        func_00207630(a, 0, 274, 220, 90, 300, 44);
        func_00207630(b, 0, 370, 220, 90, 396, 45);
        func_0020b998();
        func_0020bdf0();
        if ((s32)D_002C5AD0.x8 & 0x2000) {
            func_0011d768(2);
            if (!D_00F26E10) D_00F2C708 = 23;
            else D_00F2C708 = 18;
        }
        break;
    case 22:
        func_00f22880();
        func_00106b18(D_00F26DA0);
        func_001fd100(21, 139);
        func_001f1ed8(0x64FFFFFF, 63, 144, func_001efc10(14), 15);
        trig = D_002C5AD0.x8;
        if ((trig & 0x20000020) ? 1 : (trig & 0x80000080) != 0) {
            func_0011d768(1);
            D_00F26E10 ^= 1;
        }
        if (!(D_00F26E10)) {
            b = 2; a = 1;
            func_0020bc48(8, 364, 220);
        } else {
            a = 2; b = 1;
            func_0020bc48(8, 460, 220);
        }
        func_00207630(a, 0, 274, 220, 90, 300, 44);
        func_00207630(b, 0, 370, 220, 90, 396, 45);
        func_0020b998();
        func_0020bdf0();
        if ((s32)D_002C5AD0.x8 & 0x2000) {
            func_0011d768(2);
            if (!D_00F26E10) D_00F2C708 = 23;
            else D_00F2C708 = 18;
        }
        break;
    case 3:
        func_00233168();
        func_00f228a0();
        func_00120748(D_00F272E8, D_009A0000, func_00f227e0, 0);
        func_00106780(10);
        D_00F2C708++;
        break;
    case 5:
        func_00233168();
        func_00f208a8();
        func_00f20da0(&D_00F2C778);
        func_00f20f30();
        D_00F2C708++;
        D_00F2C6FC = 300;
        break;
    case 6:
        func_00233168();
        if (--D_00F2C6FC == 0) {
            D_00F2C6FC = 10;
            D_00F2C708++;
        }
        func_00f20f30();
        break;
    case 7:
        func_00233168();
        if (--D_00F2C6FC == 0) {
            D_00F2C708++;
        }
        func_00f20f30();
        break;
    case 8:
        func_00233168();
        func_00120748(D_00F27300, D_009A0000, func_00f227e0, 0);
        D_00F2C708++;
        break;
    case 10:
        func_00233168();
        func_00f208a8();
        func_00f20da0(&D_00F2C788);
        func_00f20f98();
        D_00F2C6FC = 300;
        D_00F2C708++;
        break;
    case 11:
        func_00233168();
        if (--D_00F2C6FC == 0) {
            D_00F2C6FC = 10;
            D_00F2C708++;
        }
        func_00f20f98();
        break;
    case 12:
        func_00233168();
        if (--D_00F2C6FC == 0) {
            D_00F2C708++;
        }
        func_00f20f98();
        break;
    case 13:
        func_00233168();
        func_00120748(D_00F27318, D_009A0000, func_00f227e0, 0);
        D_00F2C708++;
        break;
    case 4:
    case 9:
    case 14:
        func_00233168();
        break;
    case 15:
        func_00233168();
        func_00f20860();
        func_00f20da0(&D_00F2C798);
        func_00f21000();
        D_00F2C6FC = 300;
        D_00F2C708++;
        break;
    case 16:
        func_00233168();
        if (--D_00F2C6FC == 0) {
            D_00F2C708++;
            D_00F2C6FC = 10;
        }
        func_00f21000();
        break;
    case 17:
        func_00233168();
        if (--D_00F2C6FC == 0) {
            D_00F2C708++;
        }
        func_00f21000();
        break;
    case 23:
        func_00109268();
        func_00f228a0();
        func_00120748(D_00F27330, D_009A0000, func_00f227e0, 0);
        D_00F2C708++;
        if (D_002BC73C) {
            func_00106780(1);
        }
        break;
    case 24:
        break;
    case 25:
        if (D_002BC73C) {
            D_002A6B80 = 0;
            func_00106a58(8);
        }
        if (!D_002BC73C) {
            D_002BC73C = 1;
        }
        func_0011d140(0x4E49, 0);
        func_0011c7a8(0, 0x3000, 0x3000, 0, 0, 360);
        func_00f20da0(&D_00F2C758);
        func_00f20da0(&D_00F2C748);
        func_00f20da0(&D_00F2C768);
        func_00f20da0(&D_00F2C738);
        func_00f20da0(&D_00F2C7A8);
        func_00f20da0(&D_00F2C7B8);
        func_00f20da0(&D_00F2C7C8);
        func_00f20da0(&D_00F2C7D8);
        func_00f20da0(&D_00F2C7E8);
        func_00f20da0(&D_00F2C7F8);
        func_00f20da0(&D_00F2C808);
        func_00f20da0(&D_00F2C818);
        func_00f20da0(&D_00F2C828);
        func_00f20da0(&D_00F2C838);
        func_00f20da0(&D_00F2C848);
        func_00f20da0(&D_00F2C860);
        func_00f20da0(&D_00F2C870);
        func_00f20da0(&D_00F2C880);
        func_00f21068();
        D_00F2C708++;
        D_00F2C6FC = 240;
        break;
    case 26:
        if (--D_00F2C6FC == 0) {
            D_00F2C6FC = 2505;
            D_00F2C708++;
        } else if (D_002C5AD0.x4) {
            func_00f21808();
            D_00F2C708++;
            D_00F2C6FC = 2505;
        }
        func_00f21068();
        func_00f213a8();
        func_00f21928();
        func_00f22238();
        break;
    case 27:
        func_00f21068();
        --D_00F2C6FC;
        if (D_002BC07C == 128) {
            if (D_00F2C6FC == 0) {
                func_00109558(11);
                func_00f21ca0();
                func_00f21928();
                func_00f22238();
                func_00f20198();
                break;
            }
            if ((s32)D_002C5AD0.x8 & 0x2000) {
                func_0020d748();
                D_002B6478 = D_0046A6A4();
                switch (D_00F2C700) {
                case 0:
                    func_001117e0();
                    func_0011d768(54);
                    D_00F2C708 = 32;
                    break;
                case 1:
                    func_0011d768(54);
                    D_00F2C708 = 30;
                    break;
                case 2:
                    func_0011d768(54);
                    func_00109558(16);
                    func_00f20198();
                    break;
                case 3:
                    func_0011d768(54);
                    D_00F2C708 = 28;
                    break;
                }
            } else if (D_002C5AD0.x8 & 0x10000010) {
                func_0011d768(29);
                D_00F2C6FC = 2505;
                if (--D_00F2C700 < 0) D_00F2C700 = D_00F2C704;
            } else if (D_002C5AD0.x8 & 0x40000040) {
                func_0011d768(29);
                D_00F2C6FC = 2505;
                if (D_00F2C704 < ++D_00F2C700) D_00F2C700 = 0;
            }
        }
        func_00f21ca0();
        func_00f21928();
        func_00f22238();
        break;
    case 30:
        func_00f227b0();
        func_0022bcb8(0xFFFF);
        D_00F2C708 = 31;
        break;
    case 31:
        func_00f227b0();
        if (D_003F34A4 == 0) {
            a = D_003F720C;
            if (a != 1) {
                D_00F2C708 = 27;
                D_00F2C6FC = 2505;
            } else {
                func_0011c5e8();
                func_00109558(2);
                func_00111830();
                D_002B6480 = a;
                func_00f20198();
            }
        }
        break;
    case 32:
        func_00f227b0();
        func_0022d080(0xFFFF);
        D_00F2C708 = 33;
        break;
    case 33:
        func_00f227b0();
        if (D_003F34A4 == 0) {
            if (D_003F73A4 == 1) {
                func_0011d768(28);
                func_00109558(2);
                D_002BBE0C = 1;
                func_00f20198();
                D_002A3F44 = 1;
                func_00f227f8();
                func_00110448(0);
                D_002BC128 = 0;
                D_002BC130 = 0;
                D_002BC134 = 2;
                D_002BCDA8 = 0;
                func_00111600(0, 0, 2);
            } else {
                D_00F2C708 = 27;
                D_00F2C6FC = 2505;
            }
        }
        break;
    case 28:
        func_00f227b0();
        e = func_00120190(D_00F27340);
        if (e) D_00F27220.f0(e->a, e->b);
        else D_00F27220.f0(0, 0);
        D_00F2C708 = 29;
    case 29:
        D_002BBD40 = 1;
        func_00f227b0();
        if (D_00F27220.f1() == 0) {
            D_002BBD40 = 0;
            D_00F2C708 = 27;
            D_00F2C6FC = 2505;
        }
        break;
    }
    if (D_00F2C6F8) {
        func_00f20118(D_00F2C6F8);
    }
    return 0;
}
