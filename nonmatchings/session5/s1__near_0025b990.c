/* gcc991111: 568 vs 572 bytes; one extra lui (D_0066DA40 hi duplicated into both slot-search paths), else identical; prepend m991.c */
extern int D_0046AEE4;
extern int D_0046AE58[];
int func_0025b990(int fd, int ofs, int whence) {
    SemaParam sp;
    int res;
    int sema, r, i, mode;
    FioReq *rq = &D_0066C780;
    E16 *p = func_0025ad68(fd);
    func_0025b1e8(4);
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
    rq->u.arg[1] = ofs;
    rq->u.arg[2] = whence;
    rq->u.arg[3] = p - D_0066D840;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->size = 4;
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
    if (sceSifCallRpc(D_0066DA40, 4, 0, &D_0066C780, 28, D_0066D3C0, 4, 0, 0) < 0) {
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
