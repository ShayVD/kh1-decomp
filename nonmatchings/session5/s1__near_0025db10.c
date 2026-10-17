/* gcc991111: same 1-insn issue as near_0025b990.c (572 vs 568); prepend m991.c */
extern int D_0046AEE4; extern int D_0046AE58[];
long func_0025db10(int fd, long ofs, int whence) {
    SemaParam sp;
    long res;
    int sema, r, i, mode;
    FioReq *rq = &D_0066C780;
    E16 *p = func_0025ad68(fd);
    func_0025b1e8(22);
    if (!D_0046AED8) {
        func_0025b218();
        return -1;
    }
    if (!p || !p->w[1]) {
        func_0025b218();
        return -9;
    }
    mode = p->w[1];
    rq->u.arg[0] = p->w[0];
    *(long *) &rq->u.arg[1] = ofs;
    rq->u.arg[3] = whence;
    rq->u.arg[4] = p - D_0066D840;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->size = 8;
    rq->res = &res;
    rq->sema = sema;
    if (mode & 0x8000) {
        WaitSema(D_0046AEE4);
        for (i = 0; i < 32; i++)
            if (D_0046AE58[i] == -1) {
                D_0046AE58[i] = rq->sema;
                rq->sema = -rq->sema;
                break;
            }
        SignalSema(D_0046AEE4);
    }
    if (sceSifCallRpc(D_0066DA40, 22, 0, &D_0066C780, 32, D_0066D3C0, 4, 0, 0) < 0) {
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
    if (mode & 0x8000) {
        DeleteSema(sema);
        return 0;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return res;
}
