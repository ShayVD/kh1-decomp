/* gcc991111: 8 words differ (prologue sd order, v0/v1 swap for D_0066D400); prepend m991.c */
void func_00260400(u32, void *, void *);
void func_0025add8();
void func_0025b2c0();
extern u8 D_0066DA80[];
extern u32 D_0066C740;
extern u8 D_0066D400[];
typedef struct { char c[4]; } C4;
int func_0025b2f0(void) {
    int st, i;
    E16 *e;
    Client *c;
    Pair *p = &D_0066DAC0;
    sceSifInitRpc(0);
    p->a = 0;
    p->b = 0;
    st = DIntr();
    func_00260400(0x80000011, func_0025add8, D_0066DA80);
    func_00260400(0x80000013, func_0025b2c0, p);
    if (st)
        EIntr();
    while (1) {
        if (sceSifBindRpc(D_0066DA40, 0x80000001, 0) < 0)
            return -1;
        if (((Client *) D_0066DA40)->server)
            break;
        i = 0x100000;
        while (i--)
            ;
    }
    func_0025ac80();
    WaitSema(D_0046AEE0);
    for (e = D_0066D840; e < D_0066D840 + 32; e++)
        e->w[1] = 0;
    SignalSema(D_0046AEE0);
    D_0066C740 = (u32) D_0066D400;
    if (sceSifCallRpc(D_0066DA40, 255, 0, &D_0066C740, 4, D_0066D3C0, 4, 0, 0) < 0)
        return -0x10001;
    *(C4 *) D_0066DA68 = *(C4 *) ((u32) D_0066D3C0 | 0x20000000);
    D_0046AED8 = 1;
    return 0;
}
