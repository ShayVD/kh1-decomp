/* SCE SDK leftovers (libkernl: SIF/DECI2/file I/O helpers), matched with
 * ee-gcc 2.9-991111a -O2 -G0. sdk segment, session s1. */
#include "common.h"

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
int sceFsInit(void);
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


int func_00259c88(const char *fmt, ...) {
    va_list ap;
    int r;
    va_start(ap, fmt);
    r = func_00259698(fmt, ap);
    va_end(ap);
    return r;
}

int scePrintf(const char *fmt, ...) {
    va_list ap;
    int r;
    void *old = D_0046AE50;
    D_0046AE50 = (PutFn) func_002593b8;
    va_start(ap, fmt);
    r = func_00259698(fmt, ap);
    D_0046AE50 = old;
    va_end(ap);
    return r;
}

QEnt *func_00259fb0(Ring *q) {
    int i;
    QEnt *r;
    i = q->cnt % q->n;
    r = &q->buf[i];
    q->cnt = i + 1;
    return r;
}

QEnt *func_00259fe0(Ring *q, int i) {
    if (i < 0 || i >= q->n2)
        return func_00259fb0(q);
    return &q->buf2[i];
}

void func_0025a020(Pkt *r) {
    Cli *c;
    switch (r->cmd) {
    case 0x8000000a:
        c = r->cli;
        if (c->end)
            c->end(c->arg);
        break;
    case 0x80000009:
        c = r->cli;
        c->x24 = r->x24;
        c->x14 = r->x28;
        c->x18 = r->x2c;
        break;
    case 0x8000000b:
        break;
    }
    c = r->cli;
    if (c->sema >= 0)
        iSignalSema(c->sema);
    func_00259f90(c->x0);
    c->x0 = 0;
}

void func_0025a0d8(Pkt *s, Ring *q) {
    QEnt *e = func_00259fb0(q);
    e->w[5] = (u32) s->x14;
    e->w[7] = (u32) s->cli;
    e->w[8] = 0x8000000c;
    func_002605d0(0x80000008, e, 64, s->cmd, s->x24, s->x28);
}

Node *func_0025a290(int id, Ring *c) {
    Q *g;
    Node *p;
    for (g = c->qlist; g; g = g->next)
        for (p = g->list; p; p = p->next)
            if (p->id == id)
                return p;
    return 0;
}

int sceSifBindRpc(Client *cd, u32 sid, u32 mode) {
    SemaParam sp;
    Pk *e;
    cd->buf = 0;
    cd->server = 0;
    e = func_00259ee8(&D_0066C700);
    if (!e)
        return -1;
    cd->pkt = e;
    cd->id = e->id;
    e->x20 = sid;
    e->pkt = e;
    e->cd = cd;
    if (!(mode & 1)) {
        sp.max = 1;
        sp.init = 0;
        cd->sema = CreateSema(&sp);
        if (cd->sema < 0) {
            func_00259f90(e);
            return -3;
        }
        if (!func_00260590(0x80000009, e, 64, 0, 0, 0)) {
            func_00259f90(e);
            DeleteSema(cd->sema);
            return -2;
        }
        WaitSema(cd->sema);
        DeleteSema(cd->sema);
        return 0;
    }
    cd->sema = -1;
    if (!func_00260590(0x80000009, e, 64, 0, 0, 0)) {
        func_00259f90(e);
        return -2;
    }
    return 0;
}

void func_0025a790(Q *n, int v) {
    Q *p;
    DIntr();
    n->tid = v;
    n->busy = 0;
    n->list = 0;
    n->head = 0;
    n->tail = 0;
    n->next = 0;
    if (!D_0066C700.qlist)
        D_0066C700.qlist = n;
    else {
        p = D_0066C700.qlist;
        while (p->next)
            p = p->next;
        p->next = n;
    }
    EIntr();
}

Node *func_0025a8f8(Node *n, Q *g) {
    Node *p;
    DIntr();
    p = g->list;
    if (p == n)
        g->list = p->next;
    else {
        while (p) {
            if (p->next == n) {
                p->next = n->next;
                break;
            }
            p = p->next;
        }
    }
    EIntr();
    return p;
}

Q *func_0025a990(Q *n) {
    Q *p;
    DIntr();
    p = D_0066C700.qlist;
    if (p == n)
        D_0066C700.qlist = p->next;
    else {
        while (p) {
            if (p->next == n) {
                p->next = n->next;
                break;
            }
            p = p->next;
        }
    }
    EIntr();
    return p;
}

int func_0025a138(Client *cd, u32 a, u32 b, u32 c, u32 mode) {
    SemaParam sp;
    Pk *e;
    e = func_00259ee8(&D_0066C700);
    if (!e)
        return -1;
    cd->pkt = e;
    cd->id = e->id;
    e->x20 = a;
    e->x24 = b;
    e->x28 = c;
    e->pkt = e;
    e->cd = cd;
    if (!(mode & 1)) {
        sp.max = 1;
        sp.init = 0;
        cd->sema = CreateSema(&sp);
        if (cd->sema < 0) {
            func_00259f90(e);
            return -3;
        }
        if (!func_00260590(0x8000000c, e, 64, 0, 0, 0)) {
            func_00259f90(e);
            DeleteSema(cd->sema);
            return -2;
        }
        WaitSema(cd->sema);
        DeleteSema(cd->sema);
        return 0;
    }
    cd->sema = -1;
    if (!func_00260590(0x8000000c, e, 64, 0, 0, 0)) {
        func_00259f90(e);
        return -2;
    }
    return 0;
}

void func_0025a2e0(Pkt *s, Ring *c) {
    QEnt *e = func_00259fb0(c);
    Node *n;
    e->w[5] = (u32) s->x14;
    e->w[7] = (u32) s->cli;
    e->w[8] = 0x80000009;
    n = func_0025a290(s->cmd, c);
    if (!n) {
        e->w[9] = 0;
        e->w[10] = 0;
        e->w[11] = 0;
    } else {
        e->w[9] = (u32) n;
        e->w[10] = n->buf;
        e->w[11] = n->cbuf;
    }
    func_002605d0(0x80000008, e, 64, 0, 0, 0);
}

Node *func_0025aa20(Q *q) {
    Node *p;
    DIntr();
    p = q->head;
    if (!p)
        q->busy = 0;
    else {
        q->busy = 1;
        q->head = p->next2;
    }
    EIntr();
    return p;
}

E16 *func_0025ace0(void) {
    E16 *p;
    func_0025ac80();
    WaitSema(D_0046AEE0);
    for (p = D_0066D840; p < D_0066D840 + 32; p++) {
        if (p->w[1] == 0) {
            p->w[1] = 0x10000000;
            SignalSema(D_0046AEE0);
            return p;
        }
    }
    SignalSema(D_0046AEE0);
    return 0;
}

E16 *func_0025ad68(u32 i) {
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

void func_0025b218(void) { SignalSema(D_0046AEDC); }

int func_0025b228(int a, int b) {
    Pair *p = &D_0066DAC0;
    int old;
    func_0025b1e8(27);
    if (!D_0046AED8)
        sceFsInit();
    {
        int r = DIntr();
        old = p->a;
        p->b = b;
        p->a = a;
        if (r)
            EIntr();
    }
    func_0025b218();
    return old;
}

/* Nonzero when the IOP module version differs from the library's "2500". */
int func_0025b4c0(void) {
    char *v = D_0046AE40;
    char *m = D_0066DA68;
    int r = 0;
    if (memcmp(m, v, 4) && memcmp(m, D_0046AEE8, 4))
        r = memcmp(v, D_0046AEE8, 4) != 0;
    return r;
}

int func_0025cc30(int a) {
    SemaParam sp;
    int res;
    int sema, r;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(15);
    if (!D_0046AED8)
        sceFsInit();
    rq->u.arg[0] = a;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 15, 0, &D_0066C780, 16, D_0066D3C0, 4, 0, 0) < 0) {
        DeleteSema(sema);
        func_0025b218();
        return -1;
    }
    r = *(int *) ((u32) D_0066D3C0 | 0x20000000);
    func_0025b218();
    if (!r) {
        DeleteSema(sema);
        return -1;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return res;
}

int sceDopen(const char *name) {
    E16 *p;
    int r;
    func_0025b1e8(9);
    if (!D_0046AED8)
        sceFsInit();
    func_0025b218();
    p = func_0025ace0();
    if (!p)
        return -19;
    r = func_0025c628(name, 9);
    if (r < 0) {
        WaitSema(D_0046AEE0);
        p->w[1] = 0;
        SignalSema(D_0046AEE0);
        return r;
    }
    WaitSema(D_0046AEE0);
    p->w[0] = r;
    r = p - D_0066D840;
    SignalSema(D_0046AEE0);
    return r;
}

int sceClose(int fd) {
    SemaParam sp;
    int res;
    int sema, r;
    E16 *p = func_0025ad68(fd);
    FioReq *rq = &D_0066C780;
    func_0025b1e8(1);
    if (!D_0046AED8) {
        func_0025b218();
        return -1;
    }
    if (!p || !p->w[1]) {
        func_0025b218();
        return -9;
    }
    rq->u.arg[0] = p->w[0];
    rq->u.arg[1] = p - D_0066D840;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 1, 0, &D_0066C780, 20, D_0066D3C0, 4, 0, 0) < 0) {
        DeleteSema(sema);
        func_0025b218();
        return -11;
    }
    p->w[1] = 0;
    r = *(int *) ((u32) D_0066D3C0 | 0x20000000);
    func_0025b218();
    if (!r) {
        DeleteSema(sema);
        return -11;
    }
    WaitSema(sema);
    DeleteSema(sema);
    if (res < 0)
        return res;
    return 0;
}

int func_0025c628(const char *name, int fno) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(fno);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.name[i] = name[i]) == 0)
            break;
    if (i == 1024) {
        rq->u.name[1023] = 0;
        i = 1023;
    }
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, fno, 0, &D_0066C780, i + 13, D_0066D3C0, 4, 0, 0) < 0) {
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

int sceRemove(const char *a) { return func_0025c628(a, 6); }
int sceRmdir(const char *a) { return func_0025c628(a, 8); }
int func_0025cd50(const char *a) { return func_0025c628(a, 16); }
int sceDclose(int fd) {
    SemaParam sp;
    int res;
    int sema, r;
    E16 *p = func_0025ad68(fd);
    FioReq *rq = &D_0066C780;
    func_0025b1e8(10);
    if (!D_0046AED8) {
        func_0025b218();
        return -1;
    }
    if (!p || !p->w[1]) {
        func_0025b218();
        return -9;
    }
    rq->u.arg[0] = p->w[0];
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 10, 0, &D_0066C780, 20, D_0066D3C0, 4, 0, 0) < 0) {
        DeleteSema(sema);
        func_0025b218();
        return -11;
    }
    p->w[1] = 0;
    r = *(int *) ((u32) D_0066D3C0 | 0x20000000);
    func_0025b218();
    if (!r) {
        DeleteSema(sema);
        return -11;
    }
    WaitSema(sema);
    DeleteSema(sema);
    if (res < 0) return res; return 0;
}

int sceDread(int fd, int a) {
    SemaParam sp;
    int res;
    int sema, r;
    E16 *p = func_0025ad68(fd);
    FioReq *rq = &D_0066C780;
    func_0025b1e8(11);
    if (!D_0046AED8) {
        func_0025b218();
        return -1;
    }
    if (!p || !p->w[1]) {
        func_0025b218();
        return -9;
    }
    rq->u.arg[0] = p->w[0];
    rq->u.arg[1] = a;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 11, 0, &D_0066C780, 32, D_0066D3C0, 4, 0, 0) < 0) {
        WaitSema(sema);
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

int sceGetstat(const char *name, int a) {
    unsigned char c;
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(12);
    if (!D_0046AED8)
        sceFsInit();
    i = 0;
    c = rq->u.an.name[0] = name[0];
    if (c) {
        do {
            i++;
            if (i >= 1024)
                break;
            c = rq->u.an.name[i] = name[i];
        } while (c);
    }
    if (i == 1024) {
        rq->u.an.name[1023] = 0;
        i = 1023;
    }
    rq->u.an.a = a;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 12, 0, &D_0066C780, i + 17, D_0066D3C0, 4, 0, 0) < 0) {
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

int sceChdir(const char *a) { return func_0025c628(a, 18); }
int sceSync(const char *name, int a) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(19);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.bn.name[i] = name[i]) == 0)
            break;
    if (i == 1024)
        rq->u.bn.name[1023] = 0;
    rq->u.bn.b = a;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 19, 0, &D_0066C780, 1044, D_0066D3C0, 4, 0, 0) < 0) {
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

int func_0025e328(void) {
    int i;
    if (D_0046AEEC < 0) {
        while (1) {
            if (sceSifBindRpc(&D_0066DD00, 0x80000006, 0) < 0)
                return -1;
            if (D_0066DD00.server) {
                D_0046AEEC = 0;
                if (sceSifCallRpc(&D_0066DD00, 255, 0, 0, 0, &D_0066DB00, 4, 0, 0) < 0)
                    return -0x10001;
                __builtin_memcpy(D_0066DD28, (char *)&D_0066DB00, 4);
                return 0;
            }
            i = 0x100000;
            while (i--);
        }
    }
    return 0;
}

int func_0025e428(void) {
    char *v = D_0046AE40;
    char *m = D_0066DD28;
    int r = 0;
    if (memcmp(m, v, 4) && memcmp(m, D_0046AEF0, 4))
        r = memcmp(v, D_0046AEF0, 4) != 0;
    return r;
}

int sceSifUnloadModule(int a) {
    if (func_0025e328() < 0)
        return -0x10000;
    if (func_0025e428())
        return -0x10004;
    D_0066DB00.r0 = a;
    if (sceSifCallRpc(&D_0066DD00, 8, 0, &D_0066DB00, 4, &D_0066DB00, 4, 0, 0) < 0)
        return -0x10001;
    return D_0066DB00.r0;
}

int sceSifSearchModuleByName(const char *a) {
    if (func_0025e328() < 0)
        return -0x10000;
    if (func_0025e428())
        return -0x10004;
    func_00265190(D_0066DB00.s1, a, 252);
    D_0066DB00.s1[251] = 0;
    if (sceSifCallRpc(&D_0066DD00, 9, 0, &D_0066DB00, 512, &D_0066DB00, 4, 0, 0) < 0)
        return -0x10001;
    return D_0066DB00.r0;
}

int sceSifSearchModuleByAddress(int a) {
    if (func_0025e328() < 0)
        return -0x10000;
    if (func_0025e428())
        return -0x10004;
    D_0066DB00.r0 = a;
    if (sceSifCallRpc(&D_0066DD00, 10, 0, &D_0066DB00, 4, &D_0066DB00, 4, 0, 0) < 0)
        return -0x10001;
    return D_0066DB00.r0;
}

int sceSifLoadStartModuleBuffer(int a) { return func_0025e4f0(a); }
int sceSifLoadStartModule(int a, int b, int c, int d) { return func_0025eb00(a, b, c, d, 0); }
int func_0025ed68(const char *a, const char *b, int *out, int c) {
    if (func_0025e328() < 0)
        return -0x10000;
    if (func_0025e428())
        return -0x10004;
    func_00265190(D_0066DB00.s1, a, 252);
    D_0066DB00.s1[251] = 0;
    func_00265190(D_0066DB00.s2, b, 252);
    D_0066DB00.s2[251] = 0;
    if (sceSifCallRpc(&D_0066DD00, c, 0, &D_0066DB00, 512, &D_0066DB00, 16, 0, 0) < 0)
        return -0x10001;
    if (D_0066DB00.r0 == 0)
        return -0x10003;
    out[0] = D_0066DB00.r0;
    out[1] = D_0066DB00.r1;
    return 0;
}

int sceSifLoadElfPart(const char *a, const char *b, int *c) { return func_0025ed68(a, b, c, 1); }
int sceSifLoadElf(const char *a, int *b) { return func_0025ed68(a, D_00492348, b, 1); }

int func_0025eeb8(int a, void *out, u32 size) {
    if (func_0025e328() < 0)
        return -0x10000;
    if (size >= 3)
        return -0x10002;
    D_0066DB00.r0 = a;
    D_0066DB00.r1 = size;
    if (sceSifCallRpc(&D_0066DD00, 3, 0, &D_0066DB00, 32, &D_0066DB00, 32, 0, 0) < 0)
        return -0x10001;
    if (size == 0)
        *(u8 *) out = *(u8 *) &D_0066DB00;
    else if (size == 1)
        *(u16 *) out = *(u16 *) &D_0066DB00;
    else if (size == 2)
        *(u32 *) out = *(u32 *) &D_0066DB00;
    else
        return -0x10002;
    return 0;
}

int func_0025efa8(int a, void *data, int size) {
    if (func_0025e328() < 0)
        return -0x10000;
    D_0066DB00.r0 = a;
    D_0066DB00.r1 = size;
    if (size == 0)
        *(u8 *) D_0066DB00.s1 = *(u8 *) data;
    else if (size == 1)
        *(u16 *) D_0066DB00.s1 = *(u16 *) data;
    else if (size == 2)
        *(u32 *) D_0066DB00.s1 = *(u32 *) data;
    else
        return -0x10002;
    if (sceSifCallRpc(&D_0066DD00, 2, 0, &D_0066DB00, 32, &D_0066DB00, 16, 0, 0) < 0)
        return -0x10001;
    return 0;
}

int sceSifResetIop(const char *path, int mode) {
    DmaT dt;
    u32 dst;
    int i;
    func_00258430();
    dst = sceSifGetReg(0x80000000);
    D_0066DD40.mode = mode;
    for (i = 0; path[i]; i++)
        D_0066DD40.path[i] = path[i];
    D_0066DD40.dest = 0;
    D_0066DD40.len = i;
    D_0066DD40.cid = 0x80000003;
    D_0066DD40.dsize = 0;
    D_0066DD40.psize = 104;
    dt.src = &D_0066DD40;
    dt.dest = dst;
    dt.size = 104;
    dt.attr = 68;
    func_00260738(&D_0066DD40, 104);
    sceSifSetReg(4, 0x40000);
    if (sceSifSetDma(&dt, 1)) {
        sceSifSetReg(4, 0x10000);
        sceSifSetReg(4, 0x20000);
        sceSifSetReg(0x80000002, 0);
        sceSifSetReg(0x80000000, 0);
        return 1;
    }
    return 0;
}

int sceSifSyncIop(void) {
    if (sceSifGetReg(4) & 0x40000) {
        func_002585e0();
        return 1;
    }
    return 0;
}

u32 *func_0025f428(u32 *p, u32 *end, u32 v) {
    while (*p != v && p < end)
        p++;
    if (p >= end)
        return 0;
    return p;
}

int sceSifRebootIop(const char *arg) {
    char buf[80];
    char *d;
    const char *s = D_00492350;
    const char *p;
    for (p = arg; *p; p++)
        ;
    if ((u32)(p + 11 - arg) > 80) {
        scePrintf(D_00492360, arg);
        return 0;
    }
    sceSifInitRpc(0);
    func_00259ec0();
    d = buf;
    while (*s)
        *d++ = *s++;
    while (*arg)
        *d++ = *arg++;
    *d = 0;
    return sceSifResetIop(buf, 0);
}

void func_0025f4b0(void) {
    u8 *a, *b, *pa, *pb;
    func_0025f5b0(D_0046AF00[0].a, D_0046AF00[0].b);
    func_0025f5b0(D_0046AF00[1].a, D_0046AF00[1].b);
    a = func_0025f468((u8 *) 0x80000000, (u8 *) 0x80080000, func_0025f428);
    b = func_0025f468((u8 *) 0x80000000, (u8 *) 0x80080000, func_0025f3f0);
    pa = a - 524;
    pb = b - 360;
    while (pa != pb) {
        if (pa < pb) {
            a = func_0025f468(a + 4, (u8 *) 0x80080000, func_0025f428);
            pa = a - 524;
        } else {
            b = func_0025f468(b + 4, (u8 *) 0x80080000, func_0025f3f0);
            pb = b - 360;
        }
    }
    D_0046AEF8 = pa;
}

int func_0025f478(int a) {
    int v;
    func_0025f3e0(&v, D_0046AEF8 + a * 4, 4);
    return v;
}

void func_0025f6d0(void) {
    u32 i;
    if (!func_0025f668())
        return;
    func_0025f600(D_0046B6C0[0].a, D_0046B6C0[0].b);
    func_0025f610(0x80074000, D_0046AF18, 1960);
    FlushCache(0);
    FlushCache(2);
    func_0025f600(D_0046B6C0[1].a, D_0046B6C0[1].b);
    for (i = 2; i < 3; i++)
        func_0025f600(D_0046B6C0[i].a, func_0025f658(D_0046B6C0[i].a));
}

char *func_0025f7d0(const char *name, int argc, char **argv) {
    char **p = D_0046C208;
    char *dst = (char *) (p + 16);
    char *ret = dst;
    int n, i;
    func_0025f7c0(D_0046B6D8[0].a, D_0046B6D8[0].b);
    if (argc > 15)
        argc = 15;
    func_0025f780(p++, &dst, 4);
    n = strlen(name) + 1;
    func_0025f780(dst, name, n);
    dst += n;
    for (i = 0; i < argc; i++) {
        func_0025f780(p++, &dst, 4);
        n = strlen(argv[i]) + 1;
        func_0025f780(dst, argv[i], n);
        dst += n;
    }
    return ret;
}

void func_0025fa88(void) {
    u32 i;
    if (*(volatile u32 *) 0x10001810 & 0x100)
        return;
    func_0025fa20(D_0046BE48[0].a, D_0046BE48[0].b);
    func_0025fa30(0x80076000, D_0046B6E0, 1856);
    func_0025fa30(0x00082000, D_0046BE20, 40);
    FlushCache(0);
    FlushCache(2);
    func_0025fa20(D_0046BE48[1].a, D_0046BE48[1].b);
    for (i = 2; i < 8; i++)
        func_0025fa20(D_0046BE48[i].a, func_0025fa78(D_0046BE48[i].a));
}

int func_0025f8f0(void *a, void *b, int c, char **d) {
    func_0025f7d0(D_00492380, c, d);
    func_0025f8e8();
    return ExecPS2(a, b, c, D_0046C208 + 1);
}

/* fd10/fe28 open with an inlined iGetThreadId (syscall -47); the
 * kernel call has no C form, so it stays inline asm. */
int func_0025fc38(void) {
    ThreadParam tp;
    SemaParam sp;
    if (D_0046BE88 > 0)
        return -1;
    sp.init = 0;
    sp.max = 255;
    D_0066E1B0 = CreateSema(&sp);
    if (D_0066E1B0 < 0)
        return -1;
    tp.func = func_0025fb60;
    tp.stack = D_0066DDB0;
    tp.size = 1024;
    tp.gp = D_00494050;
    tp.prio = 0;
    D_0046BE88 = CreateThread(&tp);
    if (D_0046BE88 < 0) {
        DeleteSema(D_0066E1B0);
        return -1;
    }
    D_0066E1B8.x0 = 0;
    D_0066E1B8.cnt = 0;
    StartThread(D_0046BE88, &D_0066E1B8);
    ChangeThreadPriority(GetThreadId(), 1);
    return D_0046BE88;
}

int func_0025fd10(int tid) {
    EvQ *q;
    int n;
    u32 self;
    {
        register int v0 asm("$2");
        __asm__ volatile("li $3, -47\n\tsyscall" : "=r"(v0) : : "$3");
        self = v0;
    }
    if (self != tid)
        return iWakeupThread(tid);
    if (self >= 256 || !D_0046BE88)
        return -1;
    q = &D_0066E1B8;
    n = q->cnt & 0x1ff;
    q->cnt = n + 1;
    q->ev[n].a = 0;
    q->ev[n].b = self;
    iSignalSema(D_0066E1B0);
    return self;
}

int func_0025fe28(int tid) {
    EvQ *q;
    int n;
    u32 self;
    {
        register int v0 asm("$2");
        __asm__ volatile("li $3, -47\n\tsyscall" : "=r"(v0) : : "$3");
        self = v0;
    }
    if (self != tid)
        return iSuspendThread(tid);
    if (self >= 256 || !D_0046BE88)
        return -1;
    q = &D_0066E1B8;
    n = q->cnt & 0x1ff;
    q->cnt = n + 1;
    q->ev[n].a = 2;
    q->ev[n].b = self;
    iSignalSema(D_0066E1B0);
    return self;
}

int func_0025fda8(u32 c) {
    EvQ *q;
    Ev *e;
    int n;
    if (c >= 128 || !D_0046BE88)
        return -1;
    q = &D_0066E1B8;
    n = q->cnt & 0x1ff;
    q->cnt = n + 1;
    q->ev[n].a = 1;
    q->ev[n].b = c;
    iSignalSema(D_0066E1B0);
    return c;
}

int func_0025fec0(u16 proto, void *opt, void *h) {
    int buf[4];
    buf[0] = proto;
    buf[1] = (int) opt;
    buf[2] = (int) h;
    buf[3] = (int) D_0066E5C0 | 0x20000000;
    return Deci2Call(1, buf);
}

int func_0025ff30(int a, char b) {
    int buf[2];
    buf[0] = a;
    buf[1] = b;
    return Deci2Call(3, buf);
}

int func_0025fff8(int a, char b) {
    int buf[2];
    buf[0] = a;
    buf[1] = b;
    return Deci2Call(-7, buf);
}

int sceMkdir(const char *name, int a) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(7);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.an.name[i] = name[i]) == 0)
            break;
    if (i == 1024) {
        rq->u.an.name[1023] = 0;
        i = 1023;
    }
    rq->u.an.a = a;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 7, 0, &D_0066C780, i + 17, D_0066D3C0, 4, 0, 0) < 0) {
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
int sceRename(const char *n1, const char *n2) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(17);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.nn.n1[i] = n1[i]) == 0)
            break;
    if (i == 1024)
        rq->u.nn.n1[1023] = 0;
    for (i = 0; i < 1024; i++)
        if ((rq->u.nn.n2[i] = n2[i]) == 0)
            break;
    if (i == 1024)
        rq->u.nn.n2[1023] = 0;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    func_00260738(&D_0066C780, 2060);
    if (sceSifCallRpc(D_0066DA40, 17, 0, &D_0066C780, 2060, D_0066D3C0, 4, 0, 0) < 0) {
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
/* sceSifSetDma transfer with the source as an address */
typedef struct { u32 src, dest; int size, attr; } DmaU;
void func_0025aa78(Node *n) {
    DmaU dt[2];
    QEnt *e;
    void *r;
    int rsize = 0;
    int k;
    int d;
    r = n->func(n->fno, (void *) n->buf, n->size);
    if (r)
        rsize = n->rsize;
    if (n->size > 0)
        func_00260738((void *) n->buf, n->size);
    if (rsize > 0)
        func_00260738(r, rsize);
    DIntr();
    if (n->mode & 4)
        e = func_00259fe0(&D_0066C700, n->mode >> 16);
    else
        e = func_00259fb0(&D_0066C700);
    EIntr();
    e->w[8] = 0x8000000a;
    e->w[7] = (u32) n->cd;
    if (n->nowait) {
        while (!func_00260590(0x80000008, e, 64, (u32) r, n->rdest, rsize))
            ;
    } else {
        int i;
        e->w[6] = 0;
        e->w[4] = 0;
        k = 0;
        if (rsize > 0) {
            k = 1;
            dt[0].src = (u32) r;
            dt[0].dest = n->rdest;
            dt[0].size = rsize;
            dt[0].attr = 0;
        }
        dt[k].src = (u32) e;
        dt[k].dest = n->dpkt;
        dt[k].size = 64;
        dt[k].attr = 0;
        k++;
        do {
            d = sceSifSetDma(dt, k);
            if (!d) {
                i = 0x100000;
                do
                    i--;
                while (i != -1);
            }
        } while (!d);
    }
}
void func_0025ac40(Q *q) {
    Node *p;
    for (;;) {
        while ((p = func_0025aa20(q)) != 0) func_0025aa78(p);
        SleepThread();
    }
}

int sceReadlink(const char *name, void *buf, unsigned int len) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(17);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.bn.name[i] = name[i]) == 0)
            break;
    if (i == 1024)
        rq->u.bn.name[1023] = 0;
    if (len >= 1024)
        len = 1023;
    rq->u.bn.b = (int) buf;
    rq->u.bn.a = len;
    func_00260738(buf, len);
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 25, 0, &D_0066C780, 2060, D_0066D3C0, 4, 0, 0) < 0) {
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
void *memcpy(void *, const void *, unsigned int);
int sceIoctl2(int fd, int cmd, void *arg, unsigned int alen, void *buf, unsigned int blen) {
    SemaParam sp;
    int res;
    int sema, r;
    FioReq *rq = &D_0066C780;
    E16 *p = func_0025ad68(fd);
    func_0025b1e8(26);
    if (!D_0046AED8)
        sceFsInit();
    if (!p || !p->w[1]) {
        func_0025b218();
        return -9;
    }
    if (alen > 1024 || blen > 1024) {
        func_0025b218();
        return -22;
    }
    if (!arg)
        rq->u.io.alen = 0;
    else
        memcpy(rq->u.io.arg, arg, alen);
    rq->u.io.fd = p->w[0];
    rq->u.io.cmd = cmd;
    rq->u.io.alen = alen;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->u.io.blen = blen;
    rq->res = &res;
    rq->size = 4;
    rq->u.io.buf = buf;
    rq->sema = sema;
    func_00260738(&D_0066C780, 1056);
    if (sceSifCallRpc(D_0066DA40, 26, 0, &D_0066C780, 1056, D_0066D3C0, 4, 0, 0) < 0) {
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
int sceSymlink(const char *n1, const char *n2) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(17);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.nn.n1[i] = n1[i]) == 0)
            break;
    if (i == 1024)
        rq->u.nn.n1[1023] = 0;
    for (i = 0; i < 1024; i++)
        if ((rq->u.nn.n2[i] = n2[i]) == 0)
            break;
    if (i == 1024)
        rq->u.nn.n2[1023] = 0;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 24, 0, &D_0066C780, 2060, D_0066D3C0, 4, 0, 0) < 0) {
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
typedef struct { char c[252]; } B252;
int func_0025e4f0(int a, int len, void *data, int *out) {
    if (func_0025e328() < 0)
        return -0x10000;
    if (func_0025e428())
        return -0x10004;
    D_0066DB00.r0 = a;
    if (data) {
        if (len > 252) {
            *(B252 *) D_0066DB00.s2 = *(B252 *) data;
            D_0066DB00.r1 = 252;
        } else {
            memcpy(D_0066DB00.s2, data, len);
            D_0066DB00.r1 = len;
        }
    } else
        D_0066DB00.r1 = 0;
    if (sceSifCallRpc(&D_0066DD00, 6, 0, &D_0066DB00, 512, &D_0066DB00, 8, 0, 0) < 0)
        return -0x10001;
    {
        int r = D_0066DB00.r0;
        *out = D_0066DB00.r1;
        return r;
    }
}
int sceSifStopModule(int a, int len, void *data, int *out) {
    if (func_0025e328() < 0)
        return -0x10000;
    if (func_0025e428())
        return -0x10004;
    D_0066DB00.r0 = a;
    if (data) {
        if (len > 252) {
            *(B252 *) D_0066DB00.s2 = *(B252 *) data;
            D_0066DB00.r1 = 252;
        } else {
            memcpy(D_0066DB00.s2, data, len);
            D_0066DB00.r1 = len;
        }
    } else
        D_0066DB00.r1 = 0;
    if (sceSifCallRpc(&D_0066DD00, 7, 0, &D_0066DB00, 512, &D_0066DB00, 8, 0, 0) < 0)
        return -0x10001;
    {
        int r = D_0066DB00.r0;
        *out = D_0066DB00.r1;
        return r;
    }
}
int func_0025eb00(const char *name, int len, void *data, int *out, int fno) {
    if (func_0025e328() < 0)
        return -0x10000;
    if (func_0025e428())
        return -0x10004;
    func_00265190(D_0066DB00.s1, name, 252);
    D_0066DB00.s1[251] = 0;
    if (data) {
        if (len > 252) {
            *(B252 *) D_0066DB00.s2 = *(B252 *) data;
            D_0066DB00.r0 = 252;
        } else {
            memcpy(D_0066DB00.s2, data, len);
            D_0066DB00.r0 = len;
        }
    } else {
        D_0066DB00.s2[0] = 0;
        D_0066DB00.r0 = 0;
    }
    if (sceSifCallRpc(&D_0066DD00, fno, 0, &D_0066DB00, 512, &D_0066DB00, 8, 0, 0) < 0)
        return -0x10001;
    {
        int r = D_0066DB00.r0;
        *out = D_0066DB00.r1;
        return r;
    }
}
int sceDevctl(const char *name, int cmd, const char *arg, unsigned int alen, void *buf, unsigned int blen) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(23);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.dv.name[i] = name[i]) == 0)
            break;
    if (i == 1024)
        rq->u.dv.name[1023] = 0;
    if (alen > 1024 || blen > 1024) {
        func_0025b218();
        return -22;
    }
    for (i = 0; i < alen; i++)
        rq->u.dv.arg[i] = arg[i];
    rq->u.dv.alen = alen;
    rq->u.dv.cmd = cmd;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->u.dv.blen = blen;
    rq->res = &res;
    rq->size = 4;
    rq->u.dv.buf = buf;
    rq->sema = sema;
    func_00260738(&D_0066C780, 2076);
    if (sceSifCallRpc(D_0066DA40, 23, 0, &D_0066C780, 2076, D_0066D3C0, 4, 0, 0) < 0) {
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
typedef struct { char c[64]; } B64;
int sceChstat(const char *name, void *stat, int mask) {
    unsigned char c;
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(13);
    if (!D_0046AED8)
        sceFsInit();
    i = 0;
    c = rq->u.cs.name[0] = name[0];
    if (c) {
        do {
            i++;
            if (i >= 1024)
                break;
            c = rq->u.cs.name[i] = name[i];
        } while (c);
    }
    if (i == 1024) {
        rq->u.cs.name[1023] = 0;
        i = 1023;
    }
    *(B64 *) rq->u.cs.stat = *(B64 *) stat;
    rq->u.cs.mask = mask;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    func_00260738(&D_0066C780, 1104);
    if (sceSifCallRpc(D_0066DA40, 13, 0, &D_0066C780, i + 81, D_0066D3C0, 4, 0, 0) < 0) {
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
int sceFormat(const char *n1, const char *n2, const char *arg, int alen) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(14);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.mt.n1[i] = n1[i]) == 0)
            break;
    if (i == 1024)
        rq->u.mt.n1[1023] = 0;
    if (!n2)
        rq->u.mt.n2[0] = 0;
    else {
        for (i = 0; i < 1024; i++)
            if ((rq->u.mt.n2[i] = n2[i]) == 0)
                break;
        if (i == 1024)
            rq->u.mt.n2[1023] = 0;
    }
    if (alen > 1024) {
        func_0025b218();
        return -7;
    }
    for (i = 0; i < alen; i++)
        rq->u.mt.arg[i] = arg[i];
    rq->u.mt.alen = alen;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    func_00260738(&D_0066C780, 3088);
    if (sceSifCallRpc(D_0066DA40, 14, 0, &D_0066C780, 3088, D_0066D3C0, 4, 0, 0) < 0) {
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
int sceMount(const char *n1, const char *n2, int flag, const char *arg, int alen) {
    SemaParam sp;
    int res;
    int sema, r, i;
    FioReq *rq = &D_0066C780;
    func_0025b1e8(20);
    if (!D_0046AED8)
        sceFsInit();
    for (i = 0; i < 1024; i++)
        if ((rq->u.mf.n1[i] = n1[i]) == 0)
            break;
    if (i == 1024)
        rq->u.mf.n1[1023] = 0;
    for (i = 0; i < 1024; i++)
        if ((rq->u.mf.n2[i] = n2[i]) == 0)
            break;
    if (i == 1024)
        rq->u.mf.n2[1023] = 0;
    if (alen > 1024) {
        func_0025b218();
        return -7;
    }
    for (i = 0; i < alen; i++)
        rq->u.mf.arg[i] = arg[i];
    rq->u.mf.alen = alen;
    rq->u.mf.flag = flag;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    func_00260738(&D_0066C780, 3092);
    if (sceSifCallRpc(D_0066DA40, 20, 0, &D_0066C780, 3092, D_0066D3C0, 4, 0, 0) < 0) {
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

void func_00260400(u32, void *, void *);
void func_0025a4d0();
extern int D_0046AE54;
extern u8 D_0066AF00[];
extern QEnt D_0066B700[];
extern QEnt D_0066BF00[];
void func_00260118(void);
int func_002600d0(int);
void sceSifInitRpc(int mode) {
    Ring *r;
    DIntr();
    if (D_0046AE54) {
        EIntr();
        return;
    }
    D_0046AE54 = 1;
    EIntr();
    func_00260118();
    DIntr();
    r = &D_0066C700;
    r->pk = (Pk *) ((u32) D_0066AF00 | 0x20000000);
    r->npk = 32;
    r->x0c = 0;
    r->x10 = 0;
    r->buf = (QEnt *) ((u32) D_0066B700 | 0x20000000);
    r->n = 32;
    r->buf2 = (QEnt *) ((u32) D_0066BF00 | 0x20000000);
    r->n2 = 32;
    r->cnt = 0;
    r->id = 1;
    func_00260400(0x80000008, func_0025a020, r);
    func_00260400(0x80000009, func_0025a2e0, r);
    func_00260400(0x8000000a, func_0025a4d0, r);
    func_00260400(0x8000000c, func_0025a0d8, r);
    EIntr();
    if (sceSifGetReg(0x80000002))
        return;
    {
        u32 *p = (u32 *) (D_0066AF00 + 64);
        p[3] = 1;
        func_00260590(0x80000002, p, 16, 0, 0, 0);
    }
    while (!func_002600d0(0))
        ;
    sceSifSetReg(0x80000002, 1);
}
int sceOpen(const char *name, int flags, ...) {
    va_list ap;
    SemaParam sp;
    int res;
    int sema, r, i, mode, idx;
    E16 *p;
    FioReq *rq = &D_0066C780;
    va_start(ap, flags);
    mode = *(int *) ap;
    func_0025b1e8(0);
    if (!D_0046AED8)
        sceFsInit();
    if (func_0025b4c0()) {
        func_0025b218();
        return -0x10004;
    }
    p = func_0025ace0();
    if (!p) {
        func_0025b218();
        return -19;
    }
    va_start(ap, flags);
    mode = *(int *) ap;
    for (i = 0; i < 1024; i++)
        if ((rq->u.op.name[i] = name[i]) == 0)
            break;
    if (i == 1024)
        rq->u.op.name[1023] = 0;
    idx = p - D_0066D840;
    rq->u.op.flags = flags & 0x6fffffff;
    rq->u.op.mode = mode;
    rq->u.op.idx = idx;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->sema = sema;
    rq->res = &res;
    rq->size = 4;
    if (sceSifCallRpc(D_0066DA40, 0, 0, &D_0066C780, 1048, D_0066D3C0, 4, 0, 0) < 0) {
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
    if (res < 0) {
        WaitSema(D_0046AEE0);
        p->w[1] = 0;
        SignalSema(D_0046AEE0);
        return res;
    }
    r = idx;
    WaitSema(D_0046AEE0);
    p->w[0] = res;
    p->w[1] |= flags;
    SignalSema(D_0046AEE0);
    return r;
}

/* needs make: uses rodata (its strings and doubles at 0x00492170) */
void func_00259530(double d) {
    int e = 0;
    int e2;
    if (d < 0) {
        d = 0 - d;
        D_0046AE50('-');
    }
    if (d < 0.1) {
        while (d < 0.1) {
            d *= 10.0;
            e--;
        }
    } else if (d >= 1.0) {
        while (d >= 1.0) {
            d /= 10.0;
            e++;
        }
    }
    e2 = func_002594a0((unsigned long) (d * 1000000.0));
    func_00259c88("0.%d", e2);
    if (e >= 0)
        func_00259c88("e+%d", e);
    else
        func_00259c88("e%d", e);
}
