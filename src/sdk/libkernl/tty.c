/* libkernl: stdout/stdin over DECI2 (the TTY protocol, 0x210) and the SIO
 * fallback. A DECI2 socket is opened on first use (_write/_read in
 * kernl.c); the handler moves received bytes into a byte queue that
 * _read's helper drains. sdk segment, ee-gcc 2.9-991111. */
#include "common.h"

#define UNCACHED(p) ((void *) ((u32) (p) | 0x20000000))

typedef struct {
    u16 len;   /* +0 whole packet */
    u16 rsvd;  /* +2 */
    u16 proto; /* +4 0x210: TTY */
    u8 src;    /* +6 'E' (EE) */
    u8 dst;    /* +7 'H' (host) */
} Deci2Hdr;

typedef struct {
    Deci2Hdr h;
    int tty;       /* +8 */
    u8 data[256];  /* +12 */
} TtyPacket;

typedef struct {
    int size;           /* +0 */
    volatile int count; /* +4 */
    u8 *rp;             /* +8 */
    u8 *wp;             /* +12 */
    u8 buf[256];        /* +16 */
} ByteQueue;

typedef struct {
    volatile int sock; /* +0x00 */
    int wlen;          /* +0x04 bytes left to send */
    unsigned int rlen; /* +0x08 bytes received so far */
    volatile int busy; /* +0x0C a send is in flight */
    TtyPacket *wbuf;   /* +0x10 */
    u8 *rbuf;          /* +0x14 */
    ByteQueue *q;      /* +0x18 */
} TtyState;

extern ByteQueue D_0066AAC0;
extern TtyState D_0066ABD0;
extern TtyPacket D_0066AC00; /* send packet */
extern u8 D_0066AD40[];      /* receive buffer (320 bytes) */
extern char D_004920F8[];    /* handler messages */
extern char D_00492120[];
extern char D_00492138[];
extern char D_00492150[];

int func_00259c88(const char *, ...);
int func_0025fec0(int, void *, void (*)(int, int, void *));
int func_0025ff30(int, int);
int func_0025ff60(int);
int func_0025ff88(int, void *, int);
int func_0025ffc0(int, void *, int);
int DIntr(void);
int EIntr(void);
int FlushCache(int);

ByteQueue *func_00258e60(int size) {
    ByteQueue *q = &D_0066AAC0;

    q->size = size;
    q->count = 0;
    q->rp = q->wp = q->buf;
    return q;
}

void func_00258e88(ByteQueue *q) {
    q->count++;
    q->wp++;
    if (q->wp == q->buf + q->size)
        q->wp = q->buf;
}

void func_00258ec8(ByteQueue *q) {
    q->count--;
    q->rp++;
    if (q->rp == q->buf + q->size)
        q->rp = q->buf;
}

/* SIO: wait for TX FIFO room, then write the byte. */
#define SIO_ISR (*(volatile u32 *) 0x1000F130)
#define SIO_TXFIFO (*(volatile u8 *) 0x1000F180)

/* Line buffer for the kernel printf path: flushed on '\n' or when full. */
extern int D_0046AE4C;
extern char D_0066AE80[128];
void func_00260078(char *);

void func_002593b8(int c) {
    int n;

    if (D_0046AE4C >= 126) {
        D_0046AE4C = 0;
        D_0066AE80[127] = 0;
        func_00260078(D_0066AE80);
    }
    n = D_0046AE4C;
    if (c == '\n') {
        D_0046AE4C = 0;
        D_0066AE80[n] = c;
        D_0066AE80[n + 1] = 0;
        func_00260078(D_0066AE80);
        return;
    }
    D_0046AE4C = n + 1;
    D_0066AE80[n] = c;
}
