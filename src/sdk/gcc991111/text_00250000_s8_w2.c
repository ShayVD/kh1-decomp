#include "common.h"
/* s8 w2: func_0025c0f8 (fio ioctl). Context = header of text_00250000_s7_w23.c (volatile D_0046AE58, CONTEXT_ONLY func_0025ad68/func_0025b218). The constant 1 kept in s5 from the entry block for the case-1 compare is a local `one = 1` that CSE substitutes into the switch compare (cf. `two = 2` in 0010a5d0); its only other use is a constant-true `if (one)`. */
/* SCE SDK leftovers (libkernl: SIF/DECI2/file I/O helpers), matched with
 * ee-gcc 2.9-991111a -O2 -G0. sdk segment, session s1. */

typedef char *va_list;
#define va_start(v, l) (v = (char *) __builtin_next_arg(l) - 8 * (8 - __builtin_args_info(2)))
#define va_end(v)

int func_0025e4f0();
int func_0025eb00();
void SignalSema(int);
u32 sceSifGetReg(u32);
void func_002585e0(void);
int func_0025f3e0(void *, void *, int);
int func_00259698(const char *, va_list);
typedef void (*PutFn)(int);
int func_002594a0(unsigned long);
void func_002593b8();
extern int D_0046AEDC;
extern char D_00492348[];
extern u8 *D_0046AEF8;
extern PutFn D_0046AE50;
int DIntr(void);
int EIntr(void);
void SleepThread(void);
int Deci2Call(int, void *);
extern u8 D_0066E5C0[];
void func_002605d0(u32, void *, int, u32, u32, u32);
void func_0025ac80(void);
int WaitSema(int);
int iSignalSema(int);
extern int D_0046AEE0;
char *func_0025f7d0(const char *, int, char **);
void func_0025f8e8(void);
int ExecPS2(void *, void *, int, char **);
extern char D_00492380[];
extern char **D_0046C208;
extern int D_0046BE88;
extern int D_0066E1B0;

typedef struct Node {
    int id;             /* +0x00 */
    void *(*func)(int, void *, int); /* +0x04 */
    u32 buf;            /* +0x08 */
    int size;           /* +0x0c */
    u32 x10;
    u32 cbuf;           /* +0x14 */
    u32 x18;
    void *cd;           /* +0x1c client data, echoed back */
    u32 dpkt;           /* +0x20 IOP packet address */
    int fno;            /* +0x24 */
    u32 rdest;          /* +0x28 IOP receive buffer */
    int rsize;          /* +0x2c */
    int nowait;         /* +0x30 */
    u32 mode;           /* +0x34 */
    struct Node *next;  /* +0x38 */
    struct Node *next2; /* +0x3c */
} Node;
/* RPC data queue: one per serving thread */
typedef struct Q {
    int tid;          /* +0x00 */
    int busy;         /* +0x04 */
    Node *list;       /* +0x08 registered servers (->next) */
    Node *head;       /* +0x0c pending requests (->next2) */
    Node *tail;       /* +0x10 */
    struct Q *next;   /* +0x14 */
} Q;
typedef struct { u32 w[16]; } QEnt;
/* 64-byte SIF packet as allocated from the pool */
typedef struct { u8 pad[0x10]; int rid; void *pkt; int id; void *cd; u32 x20, x24, x28, x2c, x30, x34; u8 pad2[8]; } Pk;
/* the RPC library's state (D_0066C700) */
typedef struct {
    int id;       /* +0x00 last rpc id */
    Pk *pk;       /* +0x04 packet pool */
    int npk;      /* +0x08 */
    int x0c, x10;
    QEnt *buf;    /* +0x14 */
    int n;        /* +0x18 */
    QEnt *buf2;   /* +0x1c */
    int n2;       /* +0x20 */
    int cnt;      /* +0x24 */
    Q *qlist;     /* +0x28 */
} Ring;
void func_0025aa78(Node *);
int memcmp(const void *, const void *, unsigned int);
extern char D_0046AE40[];  /* "2500" */
extern char D_0066DA68[];
extern char D_0066DD28[];
extern char *D_0046AEE8;
extern char *D_0046AEF0;
extern int D_0046AEEC;
int func_0025e428(void);
int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
/* SIF RPC client of the file I/O server (+0x24: server) */
typedef struct {
    Pk *pkt;      /* +0x00 */
    int id;       /* +0x04 */
    int sema;     /* +0x08 */
    int xc;
    void *buf;    /* +0x10 */
    u8 pad14[0x10];
    void *server; /* +0x24 */
    u8 pad28[0x40];
} Client;
extern Client D_0066DD00;
/* file I/O RPC buffer: result words, then two 252-byte name fields */
typedef struct { int r0; int r1; char s1[252]; char s2[252]; } FBuf;
extern FBuf D_0066DB00;
char *func_00265190(char *, const char *, int);
int func_0025f668(void);
void func_0025f600(u32, u32);
void func_0025f610(u32, void *, int);
u32 func_0025f658(u32);
void FlushCache(int);
typedef struct { u32 a, b; } Seg;
extern Seg D_0046B6C0[];
extern u8 D_0046AF18[];
void func_0025fa20(u32, u32);
void func_0025fa30(u32, void *, int);
u32 func_0025fa78(u32);
extern Seg D_0046BE48[];
extern u8 D_0046B6E0[];
extern u8 D_0046BE20[];
int CreateSema(void *);
int DeleteSema(int);
int CreateThread(void *);
int StartThread(int, void *);
int GetThreadId(void);
int ChangeThreadPriority(int, int);
extern u8 D_0066DDB0[];
extern u8 D_00494050[];
typedef struct { int count, max, init, wait, attr, opt; } SemaParam;
typedef struct { int status; void *func; void *stack; int size; void *gp; int prio; int x18, x1c, x20, x24, x28, x2c; } ThreadParam;
void func_0025fb60();
/* IOP reset packet (SIF command 0x80000003) */
void func_00258430(void);
int sceSifSetReg(u32, u32);
int sceSifSetDma(void *, int);
void func_00260738(void *, int);
typedef struct {
    u32 psize:8;
    u32 dsize:24;
    u32 dest;
    u32 cid;
    u32 opt;
    u32 len;    /* +0x10 */
    int mode;   /* +0x14 */
    char path[80]; /* +0x18 */
} __attribute__((aligned(8))) Reset;
extern Reset D_0066DD40;
typedef struct { void *src; u32 dest; int size; int attr; } DmaT;
void sceSifInitRpc(int);
void func_00259ec0(void);
extern char D_00492350[];  /* "rom0:UDNL " */
extern char D_00492360[];  /* "too long parameter '%s'\n" */
extern Seg D_0046AF00[];
extern Seg D_0046B6D8[];
u8 *func_0025f468(u8 *, u8 *, void *);
void func_0025f3f0();
void func_0025f5b0(u32, u32);
void func_0025f7c0(u32, u32);
int func_0025f780(void *, const void *, int);
unsigned int strlen(const char *);
extern Ring D_0066C700;
Pk *func_00259ee8(Ring *p);
int func_00260590(u32, void *, int, u32, u32, u32);
int func_0025b1e8(int);
int func_0025b2f0(void);
extern int D_0046AED8;
typedef struct { int a, b; } Pair;
extern Pair D_0066DAC0;
int iWakeupThread(int);
int iSuspendThread(int);
typedef struct {
    void *x0;
    int x4;
    int sema;            /* +0x08 */
    u8 pad0c[8];
    u32 x14, x18;        /* +0x14 */
    void (*end)(void *); /* +0x1c */
    void *arg;           /* +0x20 */
    u32 x24;             /* +0x24 */
} Cli;
/* 64-byte SIF packet */
typedef struct {
    u8 hdr[0x14];
    void *x14;           /* +0x14 */
    u32 x18;
    Cli *cli;            /* +0x1c */
    u32 cmd;             /* +0x20 */
    u32 x24, x28, x2c;   /* +0x24 */
} Pkt;
/* request block for the file I/O server's simple calls */
typedef struct { int sema; int *res; int size; union {
        int arg[5];
        char name[1024];
        struct { int a; char name[1024]; } an;
        struct { int a, b; char name[1024]; } bn;
        struct { char n1[1024]; char n2[1024]; } nn;
        struct { int fd, cmd; char arg[1024]; void *buf; int blen; int alen; } io;
        struct { char name[1024]; char arg[1024]; int cmd; unsigned int alen; void *buf; unsigned int blen; } dv;
        struct { int mask; char stat[64]; char name[1024]; } cs;
        struct { char n1[1024]; char n2[1024]; char arg[1024]; int alen; } mt;
        struct { char n1[1024]; char n2[1024]; char arg[1024]; int flag; int alen; } mf;
        struct { int flags, mode; char name[1024]; int idx; } op;
    } u; } FioReq;
extern FioReq D_0066C780;
extern u8 D_0066DA40[];
extern int D_0066D3C0[];
void func_00259f90(void *);
typedef struct { u32 w[4]; } E16;
extern E16 D_0066D840[];
typedef struct { u8 a, b; } Ev;
typedef struct { u32 x0; u32 cnt; Ev ev[512]; } EvQ;
extern EvQ D_0066E1B8;

extern int D_0046AEE4;
extern volatile int D_0046AE58[];
extern int *D_0066C744;
extern u8 D_0066D410[];
void *memcpy(void *, const void *, unsigned int);
CONTEXT_ONLY E16 *func_0025ad68(u32 i) {
    E16 *p;
    func_0025ac80();
    WaitSema(D_0046AEE0);
    if (i >= 32) {
        SignalSema(D_0046AEE0);
        return 0;
    }
    p = &D_0066D840[i];
    SignalSema(D_0046AEE0);
    return p;
}

CONTEXT_ONLY void func_0025b218(void) { SignalSema(D_0046AEDC); }
int func_0025c0f8(int fd, int cmd, void *arg) {
    SemaParam sp;
    int res;
    int sema, r, i, one = 1;
    FioReq *rq = &D_0066C780;
    E16 *p = func_0025ad68(fd);
    func_0025b1e8(5);
    if (one) D_0066C744 = arg;
    if (!D_0046AED8)
        func_0025b2f0();
    if (!p || !p->w[1]) {
        func_0025b218();
        return -9;
    }
    rq->u.io.buf = 0;
    rq->u.io.blen = 0;
    switch (cmd) {
    case 1:
        WaitSema(D_0046AEE4);
        for (i = 0; i < 32; i++)
            if (D_0046AE58[i] != (int) -1)
                break;
        if (i == 32)
            *D_0066C744 = 0;
        else
            *D_0066C744 = 1;
        SignalSema(D_0046AEE4);
        func_0025b218();
        return 0;
    case 2:
        *(int *) arg = *(int *) ((u32) D_0066D410 | 0x20000000);
        func_0025b218();
        return 0;
    case 3:
        *(long *) arg = *(long *) ((u32) D_0066D410 | 0x20000000);
        func_0025b218();
        return 0;
    }
    rq->u.io.fd = p->w[0];
    rq->u.io.cmd = cmd;
    if (!arg)
        rq->u.io.alen = 0;
    else {
        rq->u.io.alen = 1024;
        memcpy(rq->u.io.arg, arg, 1024);
    }
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->res = &res;
    rq->sema = sema;
    rq->size = 4;
    func_00260738(&D_0066C780, 1056);
    if (sceSifCallRpc(D_0066DA40, 5, 0, &D_0066C780, 1056, D_0066D3C0, 4, 0, 0) < 0) {
        DeleteSema(sema);
        func_0025b218();
        return -11;
    }
    r = *(int *) ((u32) D_0066D3C0 | 0x20000000);
    func_0025b218();
    if (!r) {
        DeleteSema(sema);
        return -11;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return res;
}
