
typedef struct { s32 bits; } Hash;
typedef struct { s32 next; s32 kind; u8 pad[8]; V4 pos; } Node;
void func_00237680(Hash *, Node *, s32);

s32 func_002376c8(Hash *h, Node *n, void *m) {
    V4 v;
    V4 *p = NULL;
    s32 s, r, k;
    k = n->kind;
    if (k == 2) p = &n->pos;
    else if (k == 3) p = &n->pos;
    else if (k == 1) p = &n->pos;
    s = 1 << h->bits;
    func_002672f8(&v, m, p);
    r = s - v.w / 3000.0f * s;
    func_00237680(h, n, r);
    return r;
}
