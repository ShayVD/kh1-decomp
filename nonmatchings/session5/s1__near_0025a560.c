/* sceSifCallRpc, gcc991111: 2 words differ (cd->pkt / cd->id stores swapped); prepend m991.c */
/* SIF RPC client data as the RPC code sees it (all word fields) */
typedef struct { u32 pkt; int id; int sema; u32 xc, x10, x14, x18; u32 end; u32 arg; u32 server; } CliW;
typedef struct { u32 w0, w1, w2, w3, w4; u32 pkt; u32 id; u32 cd; u32 fno, ssize, recv, rsize, rmode, server, w14, w15; } PkW;
int sceSifCallRpc(void *c, int fno, int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg) {
    SemaParam sp;
    CliW *cd = c;
    PkW *pk = (PkW *) func_00259ee8(&D_0066C700);
    if (!pk)
        return -1;
    cd->id = pk->id;
    cd->arg = (void *) earg;
    cd->pkt = (void *) pk;
    cd->end = (void *) end;
    pk->fno = fno;
    pk->ssize = ssize;
    pk->recv = (u32) recv;
    pk->rsize = rsize;
    pk->pkt = (void *) pk;
    pk->server = cd->server;
    pk->cd = (void *) cd;
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
