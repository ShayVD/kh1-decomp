/* libkernl DECI2 TTY drafts (src/sdk/libkernl/tty.c has the types and the
 * functions that match). ee-gcc 2.9-991111 -O2 -G0. What differs:
 * - func_00258f08 (event handler): 59 words. The original loads wlen with
 *   lw+andi (not lhu), compares rlen+param unsigned, and lays out the
 *   switch differently; probably a different field typing.
 * - func_002590a0 (write): register and scheduling differences.
 * - func_002591f0 (read): the original reads D_0066ABD0.q directly by
 *   address in the wait loop and through &D_0066ABD0 after it.
 * - func_002592c0 (open): the state stores come out in another order.
 * - func_00259380 (SIO putc): the original puts the volatile TX FIFO store
 *   in the jr delay slot, which 991111 does not do for a volatile store and
 *   2.96 does not reproduce either. */
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


/* DECI2 event handler: 1/2 data arriving, 3 ready to send, 4 send done. */
void func_00258f08(int event, int param, TtyState *s) {
    int i;
    Deci2Hdr *h;

    switch (event) {
    case 1:
    case 2:
        if (param != 0) {
            if (s->rlen + param > 320)
                func_00259c88(D_004920F8);
            i = func_0025ff88(s->sock, s->rbuf + s->rlen, param & 0xFFFF);
            if (i < 0)
                func_00259c88(D_00492120);
            s->rlen += i;
        } else {
            h = (Deci2Hdr *) s->rbuf;
            for (i = 12; i < h->len; i++) {
                *s->q->wp = s->rbuf[i];
                func_00258e88(s->q);
            }
            s->rlen = 0;
        }
        break;
    case 3:
        i = func_0025ffc0(s->sock, s->wbuf, s->wlen & 0xFFFF);
        if (i < 0) {
            func_00259c88(D_00492138);
        } else {
            s->wbuf = (TtyPacket *) ((u8 *) s->wbuf + i);
            s->wlen -= i;
            break;
        }
        s->busy = 0;
        break;
    case 4:
        if (s->wlen != 0)
            func_00259c88(D_00492150, s->wlen);
        s->busy = 0;
        break;
    }
}

int func_002590a0(const char *buf, int n) {
    TtyState *s = &D_0066ABD0;
    TtyPacket *p;
    u8 *d;
    int len = 0;
    int written = 0;

    if (s->busy)
        return -1;

    DIntr();
    s->busy = 1;
    s->wbuf = p = UNCACHED(&D_0066AC00);
    d = p->data;
    while (--n != -1) {
        if (*buf == '\n') {
            *d++ = '\r';
            if (++len >= 256)
                break;
        }
        *d++ = *buf++;
        len++;
        written++;
        if (len >= 256)
            break;
    }
    s->wlen = len + 12;
    p->h.len = s->wlen;
    if (func_0025ff30(s->sock, (s8) p->h.dst) < 0) {
        s->busy = 0;
        EIntr();
        return -1;
    }
    while (s->busy)
        func_0025ff60(s->sock);
    EIntr();
    return written;
}

int func_002591f0(char *buf, int n) {
    int i;
    char c;

    for (i = 0; i < n;) {
        ByteQueue *q = D_0066ABD0.q;

        while (q->count == 0)
            ;
        buf[i] = *D_0066ABD0.q->rp;
        func_00258ec8(D_0066ABD0.q);
        c = buf[i++];
        if (c == '\n' || c == '\r')
            return i;
    }
    return i;
}

int func_002592c0(void) {
    TtyState *s = &D_0066ABD0;
    TtyPacket *p;

    FlushCache(0);
    D_0066ABD0.sock = func_0025fec0(0x210, s, func_00258f08);
    if (D_0066ABD0.sock < 0)
        return 0;
    s->busy = 0;
    s->wlen = 0;
    s->rlen = 0;
    s->rbuf = UNCACHED(D_0066AD40);
    s->wbuf = p = UNCACHED(&D_0066AC00);
    p->h.proto = 0x210;
    p->h.src = 'E';
    p->h.dst = 'H';
    p->h.rsvd = 0;
    p->tty = 0;
    s->q = func_00258e60(256);
    return 1;
}

int func_00259380(int c) {
    while (SIO_ISR & 0x8000)
        ;
    SIO_TXFIFO = c;
    return c;
}
