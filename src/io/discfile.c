/* Files on the disc: the file table looked up by a name hash (func_001200f8
 * the hash, func_00120190 a binary search, func_00120170 the compare), the
 * read requests (func_001204a0 starts one for a name, func_001201d0 reads
 * through sceCdRead, func_001202c0 the other path when func_002193b8 is set,
 * func_00120040 decodes a compressed file), the synchronous / asynchronous
 * loads (func_001205f0, func_00120678, func_00120748 with a callback),
 * func_00120930 builds a path in D_004E4500 (the prefix D_0048D278, then the
 * name upper-cased), and the disc set up at boot (func_00120b10 sceCdInit /
 * sceSifInitRpc, func_00120ba0 sceCdSearchFile). The read queue itself is
 * below 0x00120000 (func_0011ffd0 ...), still in src/hand. Flag mode:
 * default (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C5C48.h"
#include "common.h"
#include "platform/file.h"
#include "platform/cd.h"
#include "platform/iop.h"
#include "platform/thread.h"
#include "platform/math.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/types/text_00110000_h4_p.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h30_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/text_00110000_h53_p.h"
#include "actor.h"
#include "data/pieces/D_002E26A0.h"

/* func_00120038 (from auto/text_00120000.c). */
void func_00120038(s32 *arg0) {
    *arg0 = 0;
}

/* func_001200f8 (from auto/text_00120000_8.c). */
s32 strlen_200f8(s32) __asm__("strlen");
s32 func_001200f8(s32 arg0) {
    s32 temp_v0;
    s32 var_a0;
    s32 var_a3;
    s8 *temp_v0_2;

    temp_v0 = strlen_200f8(arg0);
    var_a3 = 0;
    var_a0 = 0;
    if (temp_v0 > 0) {
        do {
            temp_v0_2 = arg0 + var_a3;
            var_a3 += 1;
            var_a0 = (var_a0 * 2) ^ ((s32) (*temp_v0_2 << 0x10) % 69665);
        } while (var_a3 < temp_v0);
    }
    return var_a0;
}

/* func_00120170 (from hand/text_00110000_h4.c). */
s32 func_00120170(u32 a, u32 *b) {
    if (a < *b) return -1;
    return *b < a;
}

/* func_00120190 (from auto/text_00120000_9.c). */
void *func_0024f318(s32, M2C_UNK *, s32, M2C_UNK, M2C_UNK *);
extern M2C_UNK D_004E4A00;
extern s32 D_002C5C30;
#define func_001200f8 ((s32 (*)()) func_001200f8)
void *func_00120190(s32 arg0) {
    return func_0024f318(func_001200f8(arg0), &D_004E4A00, D_002C5C30, 0x10, &func_00120170);
}
#undef func_001200f8

/* func_001201d0 (from hand/text_00110000_h30.c). */
extern u8 D_002C5C38[];
typedef struct {
    u32 b0 : 1;
    u32 comp : 1;
    u32 r : 30;
    u8 pad4[32];
    u32 lsn;
    u32 size;
    u8 *buf;
    u32 result;
} CdReq;
void func_0010c150(void);
void func_0010c1b8(void (*)(CdReq *));
u32 func_00120040(u8 *, u32);
void func_001201d0(CdReq *r) {
    u32 n = (r->size + 2047) >> 11;
    u32 res;
    do {
        while (PlatCdDiskReady(1) != 2 || !PlatCdRead(r->lsn, n, r->buf, D_002C5C38)) func_0010c150();
        while (PlatCdSync(1)) func_0010c150();
    } while (PlatCdGetError());
    if (r->comp) {
        PlatFlushCache(0);
        res = func_00120040(r->buf, r->size);
    } else {
        res = r->size;
    }
    func_0010c1b8(func_001201d0);
    r->result = res;
}

/* func_001202c0 (from hand/text_00110000_h53.c). */
typedef struct {
    u32 b0 : 1;
    u32 comp : 1;
    u32 r : 30;
    u8 pad4[32];
    u32 lsn;
    u32 size;
    u8 *buf;
    u32 result;
} CdReq53;
extern char D_0048D260[];
extern u32 D_002C5B44;
extern void (*D_0046A6A8)(s32);
void func_002193e0(s32);
void func_0010c170(void (*)(CdReq53 *), CdReq53 *);
#define func_0010c1b8 ((void (*)(void (*)(CdReq53 *))) func_0010c1b8)
void func_001202c0(CdReq53 *r) {
    s32 err = 0;
    s32 fd, left, n;
    fd = PlatFsOpen(D_0048D260, 1);
    if (fd >= 0) {
        if (!(D_002C5B44 & 0x2000)) {
            PlatFsLseek(fd, r->lsn << 11, 0);
            goto rd;
        }
        err = 1;
        goto out;
    }
    err = 1;
    goto out;
rd:
    n = 0;
    left = r->size;
    while (left > 0) {
        n = PlatFsRead(fd, r->buf, left);
        if (n < 0) {
            err = 1;
            break;
        }
        left -= n;
    }
    PlatFsClose(fd);
    if (err == 0) {
        if (r->comp) {
            PlatFlushCache(0);
            n = func_00120040(r->buf, r->size);
        }
        r->result = n;
    }
out:
    if (err) {
        D_0046A6A8(4);
        (*(volatile Fl_2c5968 *)&D_002C5968).b2 = 1;
        do func_0010c150(); while ((*(volatile Fl_2c5968 *)&D_002C5968).b2);
        func_002193e0(0);
        r->lsn += D_004F3200;
        func_0010c170(func_001201d0, r);
    }
    func_0010c1b8(func_001202c0);
}
#undef func_0010c1b8

/* func_00120438 (from hand/text_00110000_h4.c). */
void func_0011fd40(void);
void func_00120438(s32 a, s32 b) {
    while (PlatCdDiskReady(1) != 2 || PlatCdSearchFile(a, b) == 0) func_0011fd40();
}

/* func_001204a0 (from hand/text_00110000_h30.c). */
typedef struct { s32 x0; u32 flags; u32 lsn; u32 size; } FileEnt;
CdReq *func_0011ffd0(void);
s32 func_002193b8(void);
#define func_00120190 ((FileEnt *(*)(char *)) func_00120190)
#define func_0010c170 ((void (*)(void (*)(CdReq *), CdReq *)) func_0010c170)
CdReq *func_001204a0(char *name, u8 *buf) {
    CdReq *r = func_0011ffd0();
    FileEnt *e;
    r->buf = buf;
    r->result = -1;
    e = func_00120190(name);
    if (e == 0) {
        r->result = 0;
    } else {
        r->size = e->size;
        r->comp = e->flags & 1;
        r->lsn = e->lsn;
        if (func_002193b8() == 0) {
            func_0010c170(func_001201d0, r);
            return r;
        }
        r->lsn -= D_004F3200;
        func_0010c170(func_001202c0, r);
    }
    return r;
}
#undef func_00120190
#undef func_0010c170

/* func_00120580 (from auto/text_00120000_8.c). */
M2C_UNK func_0011fd60(s32, u32, s32);
#define func_00120438 ((M2C_UNK (*)(void *, s32)) func_00120438)
s32 func_00120580(s32 arg0, s32 arg1) {
    s32 sp[12];
    func_00120438(sp, arg0);
    func_0011fd60(M2C_FIELD(sp, M2C_UNK *, 0x0), (u32) (M2C_FIELD(sp, M2C_UNK *, 0x4) + 0x7FF) >> 0xB, arg1);
    D_002C5C48 = M2C_FIELD(sp, M2C_UNK *, 0x4);
    PlatFlushCache(0);
    PlatFlushCache(2);
    return D_002C5C48;
}
#undef func_00120438

/* func_00120678 (from hand/text_00110000_h30.c). */
typedef struct {
    u8 pad0[16];
    char name[40];
    u8 *buf;
    void (*cb)(u32, s32, u8 *);
    s32 wait;
    s32 user;
    CdReq *req;
} LoadTask;
s32 func_00146878(void);
void kh1_ovl_flush0(CdReq *); /* shift build only (shift/ovl_fixup.c): overlay fixups + PlatFlushCache(0) */
#define func_00120038 ((void (*)(CdReq *)) func_00120038)
s32 func_00120678(LoadTask *t) {
    CdReq *r;
    if (t->wait > 0) {
        t->wait--;
        return 8;
    }
    if (func_00146878() == 0) return 8;
    if (t->wait == 0) t->req = func_001204a0(t->name, t->buf);
    r = t->req;
    t->wait--;
    if ((s32)r->result < 0) return 8;
    D_002C5C48 = r->result;
#ifdef KH1_OVL_FIXUPS
    kh1_ovl_flush0(r); /* relocate an overlay before it is flushed and run; same size as PlatFlushCache(0) */
#else
    PlatFlushCache(0);
#endif
    PlatFlushCache(2);
    if (t->cb) t->cb(r->result, t->user, r->buf);
    func_00120038(r);
    return 4;
}
#undef func_00120038

/* func_00120748 (from hand/text_00110000_h30.c). */
extern s32 D_004E4520;
extern u8 D_004E49E8[];
LoadTask *func_0011f090(void *, s32, s32 (*)(LoadTask *));
char *strcpy(char *, const char *);
s32 func_00120748(char *name, s32 buf, void (*cb)(void), s32 wait) {
    s32 *cnt;
    LoadTask *t = func_0011f090(D_004E49E8, 0, func_00120678);
    cnt = &D_004E4520;
    t->user = (*cnt)++;
    t->wait = wait;
    strcpy(t->name, name);
    t->buf = (u8 *)buf;
    *(s32 *)&t->cb = (s32)cb;
    *cnt = (u16)*cnt;
    return t->user;
}

/* func_001207f8 (from hand/text_00110000_h4.c). */
typedef struct { u8 pad[68]; s32 x44; s32 x48; } Ent4C;
Ent4C D_004E4528[0x10] ALIGNED(8);  /* moved from hand/text_00110000_h4.c (session 54) */
s32 func_0011f2d0(Ent4C *);
s32 func_001207f8(s32 id) {
    s32 i;
    Ent4C *e = D_004E4528;
    for (i = 0; i < 16; i++, e++) {
        if (func_0011f2d0(e) && (id == -1 || id == e->x44)) return 1;
    }
    return 0;
}

/* func_00120888 (from auto/text_00120000.c). */
#define func_00120190 ((void *(*)(s32)) func_00120190)
void func_00120888(s32 arg0) {
    void *temp_v0;

    if (PlatCdDiskReady(1) == 2) {
        temp_v0 = func_00120190(arg0);
        if (temp_v0 != NULL) {
            PlatCdSeek(M2C_FIELD(temp_v0, s32 *, 8));
        }
    }
}
#undef func_00120190

/* func_001208e0 (from auto/text_00120000_8.c). */
#define func_0011f090 ((M2C_UNK (*)(M2C_UNK *, M2C_UNK, s32)) func_0011f090)
#define D_004E49E8 (*(M2C_UNK (*)) &D_004E49E8)
M2C_UNK func_001208e0(s32 arg0) {
    return func_0011f090(&D_004E49E8, 0, arg0);
}
#undef func_0011f090
#undef D_004E49E8

/* func_00120908 (from auto/text_00120000_8.c). */
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
#define D_004E49E8 (*(M2C_UNK (*)) &D_004E49E8)
s32 func_00120908(void) {
    func_0011f130(&D_004E49E8, 0);
    return 0;
}
#undef D_004E49E8

/* func_00120930 (from hand/text_00110000_h30.c). */
char *strcat(char *, const char *);
extern char D_0048D278[] __attribute__((aligned(8)));
char D_004E4500[0x20] __attribute__((aligned(8)));  /* moved from hand/text_00110000_h30.c (session 54) */
extern u8 D_00491A18[];
u32 strlen(const char *);
char *func_00120930(char *name) {
    s32 i, n;
    __builtin_memcpy(D_004E4500, D_0048D278, 9);
    strcat(D_004E4500, name);
    n = strlen(D_004E4500);
    for (i = 8; i < n; i++) {
        D_004E4500[i] = __extension__ ({ s32 __c = D_004E4500[i]; ((D_00491A18 + 1)[__c] & 2) ? __c - 'a' + 'A' : __c; });
    }
    return D_004E4500;
}

/* func_001209d8 (from auto/text_00120000.c). */
#define func_00120930 ((s32 (*)()) func_00120930)
void func_001209d8(char *name) {
    s32 temp_a0;
    s32 temp_s0;

    temp_s0 = func_00120930(name);
    temp_a0 = temp_s0;
    do {

    } while (PlatSifLoadModule(temp_a0, 0, 0) < 0);
}
#undef func_00120930

/* func_00120a20 (from auto/text_00120000_3.c). */
#define func_00120930 ((s32 (*)()) func_00120930)
s32 func_00120a20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return PlatSifLoadStartModule(func_00120930(arg0), arg1, arg2, arg3);
}
#undef func_00120930

/* func_00120a70 (from auto/text_00120000.c). */
void *func_0011ef10(M2C_UNK, M2C_UNK *);
void func_00120a70(void) {
    M2C_FIELD(func_0011ef10(0x2D2A8, &func_00120908), s16 *, 2) = -1;
}

/* func_00120aa0 (from hand/text_00110000_h4.c). */
typedef struct Node { u16 type; u16 f2; s32 key; struct Node *next; s32 data; } Node;
typedef struct { u16 size; u16 count; u8 *base; Node *head; u8 *cur; } Pool;
typedef struct { u32 flags; u8 pad[44]; s32 x30; s32 x34; } Slot;
Slot D_004F3230[0x10] ALIGNED(16);  /* moved from hand/text_00110000_h4.c (session 54) */
void func_0011efa8(Pool *, void *, s32, s32);
#define D_004E49E8 (*(Pool (*)) &D_004E49E8)
#define func_00120038 ((void (*)(Slot *)) func_00120038)
void func_00120aa0(void) {
    s32 i;
    Slot *s;
    func_0011efa8(&D_004E49E8, D_004E4528, 76, 16);
    D_004E4520 = 0;
    s = D_004F3230;
    for (i = 15; i >= 0; i--) func_00120038(s++);
}
#undef D_004E49E8
#undef func_00120038

/* func_00120b10 (from hand/text_00110000_h4.c). */
extern char D_0048D288[];
u8 D_004F35B0[0x1000] ALIGNED(16);  /* moved from hand/text_00110000_h4.c (session 54) */
void func_001101e8(void);
void func_00120b10(void) {
    PlatSifInitRpc(0);
    PlatFsReset();
    PlatCdInit(0);
    PlatCdMmode(2);
    while (!PlatSifRebootIop(D_0048D288));
    while (!PlatSifSyncIop());
    func_001101e8();
    PlatSifInitRpc(0);
    PlatCdInit(0);
    PlatCdMmode(2);
    PlatCdInitEeCB(0, D_004F35B0, 4096);
}

/* func_00120ba0 (from auto/text_00120000_1.c). */
M2C_UNK func_0011fe20();
extern M2C_UNK D_0048D2A0;
extern M2C_UNK D_004F2A00;
extern s32 D_004F3208;
#define func_0011fd60 ((M2C_UNK (*)(s32, M2C_UNK, M2C_UNK *)) func_0011fd60)
#define func_00120438 ((M2C_UNK (*)(s32 *, M2C_UNK *)) func_00120438)
void func_00120ba0(void) {
    PlatCdDiskReady(0);
    func_00120438(&D_004F3208, &D_0048D2A0);
    func_0011fd60(D_004F3208, 1, &D_004F2A00);
    PlatCdSync(0);
    func_0011fe20();
}
#undef func_0011fd60
#undef func_00120438

