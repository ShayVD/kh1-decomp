/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00100ab0();
M2C_UNK func_00100ae0();
M2C_UNK func_00103828();
M2C_UNK func_00104288();
M2C_UNK func_00111020(s32);
M2C_UNK func_00111060();
M2C_UNK func_00111778(s32);
M2C_UNK func_001118a0();
M2C_UNK func_001118b0();
M2C_UNK func_001118f0();
M2C_UNK func_00112230();
M2C_UNK func_001124c0();
M2C_UNK func_001124d8();
M2C_UNK func_00112c20(s32);
M2C_UNK func_00112e08();
M2C_UNK func_00112e90();
M2C_UNK func_00114800();
M2C_UNK func_00114810();
M2C_UNK func_0011c788();
M2C_UNK func_001259b0(M2C_UNK);
M2C_UNK func_0012cac8(M2C_UNK, M2C_UNK);
M2C_UNK func_00135a10(s32, s32);
M2C_UNK func_00135a38(s32, s32);
M2C_UNK func_0013bf90(s32);
M2C_UNK func_0013c1b8(s32);
M2C_UNK func_0013c250(s32);
M2C_UNK func_0013c260(s32);
M2C_UNK func_0013c3a8(s32);
M2C_UNK func_00141468(s32, s32);
M2C_UNK func_00141540(s32, s32);
M2C_UNK func_00141608(s32, s32);
M2C_UNK func_001422b0(s32);
M2C_UNK func_00145080(M2C_UNK, s32);
M2C_UNK func_00145138();
M2C_UNK func_00149eb8(s32);
M2C_UNK func_0014ec10(s32);
M2C_UNK func_0014ec38(s32);
M2C_UNK func_00156678(s32);
M2C_UNK func_001566a8(s32);
M2C_UNK func_00156c28(s32);
M2C_UNK func_00157818(s32, s32);
M2C_UNK func_0017f078(s32);
M2C_UNK func_0017f110();
M2C_UNK func_001ba2f8(s32);
M2C_UNK func_001eac68();
M2C_UNK func_001ec570(s32, M2C_UNK);
M2C_UNK func_001ec7c0(M2C_UNK);
M2C_UNK func_001ef7b0(s32);
M2C_UNK func_002414a8(s32, M2C_UNK);
M2C_UNK func_0024d418();
extern M2C_UNK D_0062A630; /* src/data/bss_0062.c: u8 D_0062A630[0x10] */
extern M2C_UNK func_001dd5c0;
extern f32 D_002A6200;
extern f32 D_002BBE00;
extern s32 D_002B6474;
extern s32 D_002BBAB0;
extern s32 D_002BBAB4;
extern s32 D_002BBAB8;
extern s32 D_002BBAC4;
extern s32 D_002BC128;
extern s32 D_002BCA04;
extern s32 D_002BCC1C;
extern s32 D_002BCC20;
extern s32 D_002BCDE8;
extern s32 D_002BD110;
extern s32 D_002C5958;
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_0037A378.h"
extern s32 D_0038CDE8;
extern s32 D_0038CDEC;
extern s32 D_0038CDF0;
extern s32 D_0038CDF4;
extern s32 D_0038CDF8;
extern s32 D_0038CE00;
extern s32 D_0038D010;
extern s32 D_0038D0D4;
extern s32 D_0038D0E0;
extern s32 D_003F6E24;
extern s32 D_0062A220;
extern s32 D_0062A224;
#include "data/pieces/D_002C6440.h"
s32 func_00105ce0(s32);
s32 func_00125a00(M2C_UNK);
s32 func_0013c2f0(s32);
s32 func_0013c6a8(s32);
s32 func_001586d8(s32);
s32 func_001bad78(s32);
s32 func_001ee200();
s32 func_001ef7a0();
s32 func_0021add8();
void *func_0011f090(M2C_UNK *, M2C_UNK, M2C_UNK *);
void *func_001760b0(s32);
void *func_001760d0(s32);
void *func_001760f0(s32);

s32 func_001d5408(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_00141468(temp_v0, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d5458(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_00141540(temp_v0, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d54d8(void) {
    func_0012cac8(0, 0);
    return 2;
}

s32 func_001d5500(void) {
    func_0012cac8(0, 1);
    return 2;
}

s32 func_001d5528(void) {
    func_0012cac8(1, 0);
    return 2;
}

s32 func_001d5550(void) {
    func_0012cac8(1, 1);
    return 2;
}

s32 func_001d5578(void) {
    func_0012cac8(2, 0);
    return 2;
}

s32 func_001d55a0(void) {
    func_0012cac8(2, 1);
    return 2;
}

s32 func_001d55c8(void) {
    func_0012cac8(6, 0);
    return 2;
}

s32 func_001d55f0(void) {
    func_0012cac8(6, 1);
    return 2;
}

s32 func_001d57d0(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_0013c6a8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    return 2;
}

s32 func_001d5828(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038CDEC;
    return 2;
}

s32 func_001d5850(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038CDF0;
    return 2;
}

s32 func_001d5878(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038CDF4;
    return 2;
}

s32 func_001d58a0(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038CDF8;
    return 2;
}

s32 func_001d5978(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038CDE8;
    return 2;
}

s32 func_001d5ed8(void *arg0) {
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x180);
    D_002BBE00 = (f32) M2C_FIELD(((temp_a1 * 4) + arg0), s32 *, 0x184) / 100.0f;
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a1 - 1);
    return 2;
}

s32 func_001d5f18(void *arg0) {
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x180);
    D_002A6200 = (f32) M2C_FIELD(((temp_a1 * 4) + arg0), s32 *, 0x184) / 100.0f;
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a1 - 1);
    return 2;
}

s32 func_001d5f58(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038CE00;
    return 2;
}

s32 func_001d5ff0(void *arg0) {
    func_0014ec10(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6038(void *arg0) {
    func_0014ec38(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6100(void *arg0) {
    s32 temp_a2;

    temp_a2 = M2C_FIELD(arg0, s32 *, 0x180);
    D_002BBAB0 = M2C_FIELD(((temp_a2 * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a2 - 1);
    return 2;
}

s32 func_001d6128(void *arg0) {
    s32 temp_a0;
    s32 var_a0;
    s32 var_a2;
    u8 *var_v1;
    u8 temp_v0;

    var_a2 = 0;
    var_a0 = 3;
    var_v1 = ((s32)D_00304BE8) + 0x48E;
    do {
        temp_v0 = *var_v1;
        var_v1 += 1;
        var_a0 -= 1;
        var_a2 += temp_v0 < 0x14U;
    } while (var_a0 >= 0);
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_a0;
    M2C_FIELD(((temp_a0 * 4) + arg0), s32 *, 0x184) = var_a2;
    return 2;
}

s32 func_001d6180(void *arg0) {
    func_00145080(0, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d61c8(void *arg0) {
    func_00145080(1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6210(void) {
    func_00145138();
    return 2;
}

s32 func_001d6230(void) {
    func_00112e90();
    return 2;
}

s32 func_001d65b8(void *arg0) {
    func_00111778(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6600(void) {
    func_001eac68();
    func_0024d418();
    return 2;
}

s32 func_001d66b8(void) {
    func_00104288();
    return 2;
}

s32 func_001d66d8(void) {
    func_00100ab0();
    return 2;
}

s32 func_001d66f8(void) {
    func_00100ae0();
    return 2;
}

s32 func_001d6718(void *arg0) {
    func_0017f078(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6760(void) {
    func_0017f110();
    return 2;
}

s32 func_001d6780(void *arg0) {
    func_00135a10(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d67c8(void *arg0) {
    func_00135a38(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6810(void *arg0) {
    func_002414a8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), 1);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6858(void *arg0) {
    func_002414a8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), 3);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d68a0(void *arg0) {
    func_002414a8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), 1);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d68e8(void *arg0) {
    func_002414a8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), 0);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6958(void) {
    D_002C5958 |= 0x08000000;
    return 2;
}

s32 func_001d6978(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_00105ce0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    return 2;
}

s32 func_001d6a20(void) {
    func_001118a0();
    return 2;
}

s32 func_001d6a40(void) {
    func_001118b0();
    return 2;
}

s32 func_001d6bf8(void) {
    D_002BD110 = 0;
    return 2;
}

s32 func_001d6c08(void) {
    D_002BD110 = 1;
    return 2;
}

s32 func_001d6d60(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_00141608(temp_v0, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6db0(void) {
    D_002C5958 &= ~0x800;
    return 2;
}

s32 func_001d6dd0(void) {
    D_002C5958 |= 0x800;
    return 2;
}

s32 func_001d6df0(void) {
    D_002C5958 &= ~0x200;
    return 2;
}

s32 func_001d6e10(void) {
    D_002C5958 |= 0x200;
    return 2;
}

s32 func_001d6e30(void) {
    D_002C5958 &= ~0x400;
    return 2;
}

s32 func_001d6e50(void) {
    D_002C5958 |= 0x400;
    return 2;
}

s32 func_001d6ef0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) + 1);
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = func_00125a00(1);
    return 2;
}

s32 func_001d6f38(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038D010;
    return 2;
}

s32 func_001d6f60(void) {
    D_0038D010 = 0;
    return 2;
}

s32 func_001d6f70(void) {
    D_002C5958 |= 0x1000;
    return 2;
}

s32 func_001d6f90(void) {
    D_002C5958 &= ~0x1000;
    return 2;
}

s32 func_001d6fb0(void *arg0) {
    func_001ef7b0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d6ff8(void *arg0) {
    func_00112c20(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d7220(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d7520(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038D0D4;
    return 2;
}

s32 func_001d85a8(void *arg0) {
    func_001566a8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d85f0(void *arg0) {
    func_00156678(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8660(void) {
    D_002C5958 |= 0x8000;
    return 2;
}

s32 func_001d8738(void *arg0) {
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_a1;
    M2C_FIELD(((temp_a1 * 4) + arg0), s32 *, 0x184) = (s32) M2C_FIELD(arg0, s32 *, 0x324);
    return 2;
}

s32 func_001d8760(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_001586d8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    return 2;
}

s32 func_001d88c8(void *arg0) {
    func_0013c250(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8910(void *arg0) {
    func_0013c260(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8958(void *arg0) {
    func_0013c1b8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d89a0(void *arg0) {
    if (M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) != 0) {
        func_0012cac8(3, 1);
    } else {
        func_0012cac8(3, 0);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8a00(void *arg0) {
    if (M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) != 0) {
        func_0012cac8(4, 1);
    } else {
        func_0012cac8(4, 0);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8a60(void *arg0) {
    if (M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) != 0) {
        func_0012cac8(5, 1);
    } else {
        func_0012cac8(5, 0);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8ac0(void *arg0) {
    func_00149eb8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8b08(void) {
    func_00114800();
    return 2;
}

s32 func_001d8b28(void) {
    func_00114810();
    return 2;
}

s32 func_001d8b48(void) {
    func_00112e08();
    return 2;
}

s32 func_001d8b98(void *arg0) {
    func_00111020(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8be0(void) {
    func_00111060();
    return 2;
}

s32 func_001d8c80(void *arg0) {
    func_001422b0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8d18(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_0013c2f0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    return 2;
}

s32 func_001d8d70(void *arg0) {
    func_00156c28(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d8eb0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) + 1);
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = func_001ee200();
    return 2;
}

s32 func_001d8ef8(void) {
    func_001124c0();
    return 2;
}

s32 func_001d8f18(void) {
    func_001124d8();
    return 2;
}

s32 func_001d9728(void) {
    func_001118f0();
    func_0011c788();
    return 6;
}

s32 func_001d9750(void *arg0) {
    D_0038D0E0 = M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d9830(void) {
    func_00103828();
    return 2;
}

s32 func_001d9e90(void *arg0) {
    s32 temp_a2;

    temp_a2 = M2C_FIELD(arg0, s32 *, 0x180);
    D_002BBAB4 = M2C_FIELD(((temp_a2 * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a2 - 1);
    return 2;
}

s32 func_001d9eb8(void *arg0) {
    s32 temp_a2;

    temp_a2 = M2C_FIELD(arg0, s32 *, 0x180);
    D_002BBAB8 = M2C_FIELD(((temp_a2 * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a2 - 1);
    return 2;
}

s32 func_001d9f88(void *arg0) {
    s32 temp_a2;

    temp_a2 = M2C_FIELD(arg0, s32 *, 0x180);
    D_002BBAC4 = M2C_FIELD(((temp_a2 * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a2 - 1);
    return 2;
}

s32 func_001d9fb0(void *arg0) {
    func_0013c3a8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001da040(void *arg0) {
    func_001ba2f8(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001da1a8(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_003F6E24;
    return 2;
}

s32 func_001da9f0(void) {
    D_002BCDE8 = 0;
    return 2;
}

s32 func_001daa00(void) {
    D_002BCDE8 = 1;
    return 2;
}

s32 func_001daad8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) + 1);
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = func_001ef7a0();
    return 2;
}

s32 func_001dab48(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_00157818(temp_v0, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001dab98(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_002BCC20;
    return 2;
}

s32 func_001dabc0(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_002BCC1C;
    return 2;
}

s32 func_001db018(void *arg0) {
    func_001ec570(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), 1);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001db060(void) {
    func_00112230();
    return 2;
}

s32 func_001db5a0(void) {
    D_0037A378 |= 0x10;
    return 2;
}

s32 func_001db5c0(void) {
    D_0037A378 &= ~0x10;
    return 2;
}

s32 func_001db5e0(void) {
    func_001ec7c0(0);
    return 2;
}

s32 func_001db888(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_001bad78(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    return 2;
}

s32 func_001dbae0(void) {
    D_002C5958 |= 0x20;
    return 2;
}

s32 func_001dbb00(void) {
    D_002C5958 &= ~0x20;
    return 2;
}

s32 func_001dbb60(void *arg0) {
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x180);
    if (D_002BCA04 & M2C_FIELD(((temp_a1 * 4) + arg0), s32 *, 0x184)) {
        M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a1 - 1);
        return 2;
    }
    return 4;
}

s32 func_001dbbf0(void) {
    D_002C5958 |= 0x200000;
    return 2;
}

s32 func_001dbfb8(void *arg0) {
    func_0013bf90(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001dc100(void) {
    func_001259b0(1);
    return 2;
}

s32 func_001dc120(void) {
    func_001259b0(0);
    return 2;
}

s32 func_001dc2e0(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_002B6474;
    return 2;
}

s32 func_001dca88(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) + 1);
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = func_0021add8();
    return 2;
}

void func_001dd1f0(s32 arg0, s32 arg1) {
    D_0062A220 = arg0;
    D_0062A224 = arg1;
}

s32 func_001de558(void *arg0) {
    void *temp_v0;

    temp_v0 = func_001760d0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001df130(void) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 1;
    M2C_FIELD(temp_v0, s32 *, 0x28) = 0;
    return 2;
}

s32 func_001df268(void) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 4;
    M2C_FIELD(temp_v0, s32 *, 0x28) = 0;
    return 2;
}

s32 func_001df5d8(void *arg0) {
    void *temp_v0;

    temp_v0 = func_001760f0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001dfe50(void *arg0) {
    void *temp_v0;

    temp_v0 = func_001760b0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_003F.h"
#include "data/data_0038.h"
#include "data/data_0042.h"
#include "data/pieces/D_002C5AD0.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002BCC1C.h"
#include "data/pieces/D_002BD110.h"
