typedef unsigned int size_t;
typedef struct { char *(*f0)(void); s32 (*f4)(void); s32 (*f8)(void); s32 (*fc)(void); s32 x10; char *(*f14)(void); s32 x18; s32 (*f1c)(void); } Cfg;
void *memset(void *, int, size_t);
s32 memcmp(const void *, const void *, size_t);
size_t strlen(const char *);
u8 *func_00f26648(const char *, u8 *, s32, s32 *);
char *func_0011fd30(void);
void func_0011d768(s32);
void func_0024e468(s32);
void func_0020bda8(s32);
void func_0020be10(s32);
s32 func_001f31a8(void *, s32);
s32 func_0024e098(void);
s32 func_0024db68(void);
void func_0010c170(void *, s32);
s32 func_00f24a58(void);
s32 func_00f24a70(void);
void func_00f24a88(s32);
void func_00f24b28(void);
void func_00f26520(void);
void func_00f20000(void);
extern s32 D_0046A614;
extern s32 D_0046A678;
extern Cfg D_0046A688;
extern s32 D_00F26E20;
extern u8 *D_00F26E24;
extern char *D_00F26E28;
extern s32 D_00F26E2C;
extern u32 D_00F26E38;
extern u32 D_00F26E3C;
extern s32 D_00F26E64;
extern s32 D_00F26E68;
extern s32 D_00F26E6C;
extern u8 D_00F26EA0[];
extern char D_00F27448[], D_00F27460[], D_00F27478[], D_00F27488[], D_00F27498[], D_00F274A8[];
extern char D_00F274B0[], D_00F274C8[], D_00F274E0[], D_00F274F8[], D_00F27510[];
extern s32 D_00F2C890;
extern s32 D_00F2C894;
extern s32 D_00F2C898;
extern s32 D_00F2C89C;
extern u8 *D_00F2C8A4;
extern u8 *D_00F2C8A8;
extern u8 *D_00F2C8AC;
extern u8 *D_00F2C8B0;
extern u8 *D_00F2C8B4;
extern u8 *D_00F2C8B8;
extern u8 *D_00F2C8BC;
extern char *D_00F2C8C0;
extern s32 D_00F2C8C4, D_00F2C8C8, D_00F2C8CC;
extern s32 D_00F2C8D0;
extern s32 D_00F2C8D4;
extern s32 D_00F2C8D8;
extern s32 D_00F2C8E0[3];
extern s32 D_00F2C8F8;
extern s32 D_00F2C8FC;

#define ALIGN512(x) (((x) + 511) / 512 * 512)

void func_00f24b60(void) {
    s32 size;
    u8 *p;
    char *s;
    s32 i, j, n, r, no, v;

    p = D_00F2C8A4;
    D_00F2C8B8 = p;
    D_0046A614 = 131;
    D_00F2C8BC = func_00f26648(D_0046A678 ? D_00F27448 : D_00F27460, p, 64, &D_00F2C8C4);
    D_00F2C8C0 = (char *)func_00f26648(D_00F27478, D_00F2C8BC, 64, &D_00F2C8C8);
    if (D_0046A678) p = func_00f26648(D_00F27488, (u8 *)D_00F2C8C0, 64, &D_00F2C8CC);
    else p = func_00f26648(D_00F27498, (u8 *)D_00F2C8C0, 64, &D_00F2C8CC);
    D_00F26E28 = (char *)p;
    memset(p, 0, 0x900);
    i = 0;
    s = func_0011fd30();
    D_00F26E28[0] = s[0];
    while (s[i] != 0) {
        i++;
        D_00F26E28[i] = s[i];
    }
    j = 0;
    while (memcmp(D_00F274A8, D_00F2C8C0 + j, 4) != 0) j++;
    i = 0;
    while (memcmp(D_00F274A8, D_00F26E28 + i, 4) != 0) i++;
    {
        char *d = D_00F2C8C0 + j + 5;
        char *t = D_00F26E28 + i + 5;
        d[0] = t[0];
        d[1] = t[1];
        d[2] = t[2];
        d[3] = t[4];
        d[4] = t[5];
    }
    D_00F26E2C = strlen(D_00F26E28);
    if (D_00F26E28[D_00F26E2C - 1] == '\n') {
        D_00F26E2C--;
        D_00F26E28[D_00F26E2C] = 0;
    }
    D_00F26E28[D_00F26E2C] = '\n';
    n = strlen(D_00F26E28);
    D_00F26E2C = n;
    for (i = 0; i < n && D_00F26E28[i] != '#'; i++);
    if (i != D_00F26E2C) {
        j = i + 1;
        do {
            i--;
        } while (D_00F26E28[i] == ' ' || D_00F26E28[i] == '\t');
        i++;
        while (D_00F26E28[j] != '\r' && D_00F26E28[j] != '\n') j++;
        do {
            D_00F26E28[i++] = D_00F26E28[j++];
        } while (j < D_00F26E2C);
        D_00F26E2C = i;
        memset(D_00F26E28 + i, 0, 64);
    }
    p += ALIGN512(D_00F26E2C);
    D_00F26E24 = p;
    if (D_0046A678) p = func_00f26648(D_00F274B0, p, 64, &size);
    else p = func_00f26648(D_00F274C8, p, 64, &size);
    D_00F26E20 = size;
    p = (u8 *)(((s32)p + 63) & ~63);
    D_00F2C8A4 = p;
    D_00F2C8A8 = p;
    D_00F2C8AC = func_00f26648(D_00F274E0, p, 64, 0);
    D_00F2C8B0 = func_00f26648(D_00F274F8, D_00F2C8AC, 64, 0);
    D_00F2C8B4 = func_00f26648(D_00F27510, D_00F2C8B0, 256, 0);
    D_00F2C8D0 = 0x20000;
    if ((u32)(D_00F2C8B4 + 0x20000) >= (u32)func_00f20000) __asm__ volatile("break");
    func_001f31a8(D_00F26EA0, 1);
    D_00F2C89C = 1;
    func_0024e468(30);
    D_00F2C8F8 = 0;
    func_0020bda8(16);
    no = 1;
    D_00F26E64 = 1;
    for (;;) {
        if (func_00f24a58() & 0x2000) {
            if (D_00F26E64 != 0) func_0011d768(2);
            break;
        }
        if (func_00f24a58() & 0x4000) {
            func_0011d768(3);
            no = 1;
            break;
        }
        if (func_00f24a70() & 0xA0) {
            D_00F26E64++;
            func_0011d768(1);
        }
        no = D_00F26E64 = D_00F26E64 & 1;
        func_0024e468(1);
    }
    D_0046A614 = 132;
    func_0024e468(10);
    if (no != 0) {
        D_00F2C894 = 0;
        return;
    }
    D_0046A614 = 140;
    r = func_0024e098();
    if (r == 3) {
        func_0011d768(4);
        func_00f24a88(7);
    }
    if (r == 1) {
        func_0011d768(4);
        func_00f24a88(2);
    }
    if (func_0024db68() < 0) {
        func_0011d768(4);
        func_00f24a88(9);
    }
    D_00F2C8FC = 0;
    D_0046A614 = 150;
    func_0010c170(func_00f24b28, D_00F26E38);
    while (D_00F2C8FC == 0) func_0024e468(1);
    D_0046A614 = 160;
    if (func_0024db68() < 0) {
        func_0011d768(4);
        func_00f24a88(9);
    }
    D_0046A614 = 180;
    if (D_0046A688.f1c() == 2) {
        func_0011d768(2);
        v = 4;
ask:
        D_00F2C89C = v;
        D_00F26E68 = 1;
        func_0024e468(1);
        no = 1;
        for (;;) {
            if (func_00f24a58() & 0x2000) {
                func_0011d768(2);
                break;
            }
            if (func_00f24a58() & 0x4000) {
                func_0011d768(3);
                no = 1;
                break;
            }
            if (func_00f24a70() & 0xA0) {
                D_00F26E68++;
                func_0011d768(1);
            }
            no = D_00F26E68 = D_00F26E68 & 1;
            func_0024e468(1);
        }
        if (no != 0) {
            D_00F2C894 = 0;
            return;
        }
    } else {
        switch (func_0024e098()) {
        case 3:
            func_0011d768(4);
            func_00f24a88(7);
            break;
        case 2:
            func_0011d768(4);
            v = 5;
            goto ask;
        case 4:
            func_0011d768(4);
            func_00f24a88(6);
            break;
        }
    }
    func_0020be10(16);
    func_0011d768(2);
    for (;;) {
        if ((D_00F26E6C += 4) >= 128) break;
        func_0024e468(1);
    }
    D_00F26E6C = 128;
    D_00F2C89C = 3;
    D_00F2C8D4 = 1;
    D_00F2C8E0[2] = 0;
    D_00F26E6C = 8;
    D_00F2C8D8 = 0;
    D_00F2C8E0[0] = 0;
    D_00F2C8E0[1] = 0;
    do {
        func_0024e468(1);
    } while ((D_00F26E6C += 8) < 256);
    D_00F26E6C = 256;
    D_00F2C890 = 0;
    func_0010c170(func_00f26520, 0);
    for (;;) {
        if (D_00F26E38 != 0) D_00F2C8D8 = (s64)D_00F26E3C * 0x27600 / (s64)D_00F26E38;
        D_00F2C8E0[0] += 128;
        D_00F2C8E0[1] += 128;
        D_00F2C8E0[2] += 128;
        if (D_00F2C898 != 0) break;
        func_0024e468(1);
    }
    if (D_0046A688.f1c() != 2) func_00f24a88(6);
    else func_00f24a88(8);
}
