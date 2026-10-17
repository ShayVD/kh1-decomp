/* gcc991111: 624 vs 632 bytes; same slot-search scheduling issue as near_0025b990.c (i=0 lands in the bne delay slot, duplicating lui); prepend m991.c */
extern int D_0046AEE4;
extern int D_0046AE58[];
extern u8 D_0066D400[];
int func_0025bbc8(int fd, void *buf, int size) {
    SemaParam sp;
    int res;
    int sema, r, mode;
    int i;
    FioReq *rq = &D_0066C780;
    E16 *p = func_0025ad68(fd);
    func_0025b1e8(2);
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
    rq->u.arg[4] = p - D_0066D840;
    rq->u.arg[1] = (int) buf;
    rq->u.arg[2] = size;
    sp.max = 1;
    sp.init = 0;
    sp.opt = 0;
    sema = CreateSema(&sp);
    rq->res = &res;
    rq->size = 4;
    rq->sema = sema;
    if (mode & 0x8000) {
        WaitSema(D_0046AEE4);
        for (i = 0; i < 32; i++)
            if (D_0046AE58[i] < 0) {
                D_0046AE58[i] = rq->sema;
                rq->sema = -rq->sema;
                break;
            }
        SignalSema(D_0046AEE4);
    }
    if (!(mode & 0x20000000))
        func_00260738(buf, size);
    func_00260738(D_0066D400, 164);
    func_00260738(&D_0066C780, 32);
    if (sceSifCallRpc(D_0066DA40, 2, 0, &D_0066C780, 32, D_0066D3C0, 4, 0, 0) < 0) {
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
