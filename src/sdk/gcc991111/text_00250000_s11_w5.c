#include "common.h"
/* libkernl SIF RPC: sceSifCallRpc (0x25a560), ee-gcc 2.9-991111a (sdk/gcc991111). Session 11, s11w5.
 * The client fields that sceSifCallRpc fills for the completion handler (pkt, end, arg) are
 * volatile: their stores then keep source order (arg, pkt, end) while the pk->id load issues
 * first and the plain id store falls between pkt and end, as in the original. */

typedef struct { int count, max, init, wait, attr, opt; } SemaParam;
typedef struct { u8 pad[0x10]; int rid; void *pkt; int id; void *cd; u32 x20, x24, x28, x2c, x30, x34; u8 pad2[8]; } Pk;
typedef struct { int id; Pk *pk; int npk; } Ring;
extern Ring D_0066C700;
Pk *func_00259ee8(Ring *p);
int func_00260590(u32, void *, int, u32, u32, u32);
void func_00259f90(void *);
void func_00260738(void *, int);
int CreateSema(void *);
int DeleteSema(int);
int WaitSema(int);
/* SIF RPC client data as the RPC code sees it (all word fields) */
typedef struct {
    volatile u32 pkt;   /* +0x00 */
    int id;             /* +0x04 */
    int sema;           /* +0x08 */
    u32 xc, x10, x14, x18;
    volatile u32 end;   /* +0x1c end function */
    volatile u32 arg;   /* +0x20 its argument */
    u32 server;         /* +0x24 */
} CliW;
/* 64-byte SIF RPC packet */
typedef struct { u32 w0, w1, w2, w3, w4; u32 pkt; u32 id; u32 cd; u32 fno, ssize, recv, rsize, rmode, server, w14, w15; } PkW;

int sceSifCallRpc(void *c, int fno, int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg) {
    SemaParam sp;
    CliW *cd = c;
    PkW *pk = (PkW *) func_00259ee8(&D_0066C700);
    if (!pk)
        return -1;
    {
        int id = pk->id;
        cd->arg = (u32) earg;
        cd->pkt = (u32) pk;
        cd->id = id;
        cd->end = (u32) end;
    }
    pk->fno = fno;
    pk->ssize = ssize;
    pk->recv = (u32) recv;
    pk->rsize = rsize;
    pk->pkt = (u32) pk;
    pk->server = cd->server;
    pk->cd = (u32) cd;
    if (!(mode & 2)) {
        if (send == recv)
            func_00260738(send, ssize < rsize ? rsize : ssize);
        else {
            if (ssize > 0)
                func_00260738(send, ssize);
            if (rsize > 0)
                func_00260738(recv, rsize);
        }
    }
    if (mode & 1) {
        if (!end)
            pk->rmode = 0;
        else
            pk->rmode = 1;
        cd->sema = -1;
        if (func_00260590(0x8000000a, pk, 64, (u32) send, cd->x14, ssize))
            return 0;
        func_00259f90(pk);
        return -2;
    }
    sp.max = 1;
    sp.init = 0;
    cd->sema = CreateSema(&sp);
    if (cd->sema < 0) {
        func_00259f90(pk);
        return -3;
    }
    pk->rmode = 1;
    if (!func_00260590(0x8000000a, pk, 64, (u32) send, cd->x14, ssize)) {
        DeleteSema(cd->sema);
        func_00259f90(pk);
        return -2;
    }
    WaitSema(cd->sema);
    DeleteSema(cd->sema);
    return 0;
}
