/* Round 51 wwm2: score 52 -> 4 at exact size 784. The findrec inline is gone: both search loops sit in the body with `if (k < 0) return;`, which gives the target's bltzl straight to the epilogue and the e == 0 test on s1. The q walk is an index loop `for (i = 0; q[i] != 1; i += 12)` (strength reduction makes the target's fresh q giv in s2 and the fresh li 1). i/e registers: global alloc priority is floor_log2(refs)*refs/live; with `e = func_00f62c78(i, ..); i++;` in loop 2 (not i++ in the call) i outranks e and takes s0 as in the target. Left: one store pair, x10C vs xE8 (sched). */
/* Round 46 wwm2: score 56 -> 52, func_00f64c38 declared s32. Earlier header below. */
/* wm f3ac48 near miss: 94 words differ, score 56 (784 vs 784 bytes). Two 1-word struct params give the sw a0/a1 to 0/4(sp). The search loops are in a static inline findrec(), which fixes the i/e registers. D_00FCE390[slot] is indexed directly everywhere. Left: the inline's return 0 / e==0 test is not threaded (orig bltzl k straight to the epilogue), store scheduling of the E fields (x10C), and the q loop's fresh li 1. Tried: plain loops, a j var for the second loop, separate r/e vars, an out-param inline (worse), an id-search inline (worse), while/for/do-while q loops. */
typedef struct {
    OvlMtx m;
    OvlVec v40;
    OvlVec v50;
    OvlMtx m60;
    OvlMtx mA0;
    s32 xE0, xE4, xE8, xEC, xF0, xF4;
    s32 padF8[5];
    s32 *x10C;
} Ent;
typedef struct { u8 pad[0x540]; s32 x540; } Ctx;
typedef struct { u8 x0; u8 x1; u16 x2; u8 pad4[12]; u8 x10; u8 x11; } Rec;
typedef struct { u8 pad[32]; u16 x20; } Obj;
extern f32 D_00F8509C;
extern s32 D_00F850A0;
extern s32 D_00F85098;
extern Ctx *D_00F864C0;
extern Rec *D_00FCE38C;
extern Ent D_00FCE390[];
extern s32 D_00F87020;
extern s32 D_00F8705C;
extern s32 D_00FCE380, D_00FCE384;
extern f32 D_00F86480[4][4];
s32 func_00f36218(void);
s32 func_00f43d88(s32);
Obj *func_00f3f260(s32, s32);
Rec *func_00f62c78(s32, s32);
s32 func_00f62c90(s32);
s32 func_00f64c38(s32, s32);
s32 func_00f20020(void);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0CopyVector(OvlVec, OvlVec);
void func_001bf098(OvlMtx, OvlMtx);
void func_00f39b10(Ent *, s32 *, s32);
void func_00f39de8(Ent *);
void func_00f3a268(void);
void func_001c0310(s32, void *, void *);

typedef struct { s32 a; } W;
void func_00f3ac48(W pa, W pb) {
    s32 slot;
    s32 k;
    Rec *e;
    Ent *E;
    s32 *q;
    s32 v;
    s32 i, n, id;

    D_00F8509C = 1.0f;
    slot = func_00f36218();
    if (slot < 0) return;
    if (D_00F850A0 != 0) return;
    k = -1;
    i = 0;
    n = func_00f43d88(D_00F864C0->x540);
    while (i < n) {
        Obj *o = func_00f3f260(i, D_00F864C0->x540);
        i++;
        e = func_00f62c78(o->x20, D_00F864C0->x540);
        if ((u16)(e->x2 - 3) < 2) {
            k = e->x2 - 3;
            break;
        }
    }
    if (k < 0) return;
    if (k != 0) {
        i = 0;
        id = e->x11;
        n = func_00f62c90(D_00F864C0->x540);
        while (i < n) {
            e = func_00f62c78(i, D_00F864C0->x540);
            i++;
            if (e->x10 == id) break;
            e = 0;
        }
    }
    if (e == 0) return;
    D_00FCE38C = e;
    func_00f64c38(e->x0, D_00F87020);
    D_00F85098 = 1;
    D_00F850A0 = 1;
    v = func_00f20020() + 0x80000000;
    D_00FCE380 = pa.a;
    D_00FCE384 = pb.a;
    D_00FCE390[slot].xE4 = v;
    D_00FCE390[slot].xF4 = 0;
    D_00FCE390[slot].x10C = (s32 *)D_00F8705C;
    D_00FCE390[slot].xE0 = 1;
    D_00FCE390[slot].xEC = 0;
    D_00FCE390[slot].xE8 = 0;
    D_00FCE390[slot].xF0 = 0;
    sceVu0CopyMatrix(D_00FCE390[slot].m, D_00F86480);
    sceVu0UnitMatrix(D_00FCE390[slot].m60);
    func_001bf098(D_00FCE390[slot].m60, D_00FCE390[slot].m);
    sceVu0CopyVector(D_00FCE390[slot].v50, D_00FCE390[slot].m[3]);
    sceVu0CopyVector(D_00FCE390[slot].v40, D_00FCE390[slot].m[2]);
    sceVu0UnitMatrix(D_00FCE390[slot].mA0);
    q = D_00FCE390[slot].x10C;
    for (i = 0; q[i] != 1; i += 12) {
        if (q[i] == 8) {
            func_00f39b10(&D_00FCE390[slot], &q[i], 0);
        }
    }
    func_00f39de8(&D_00FCE390[slot]);
    func_001c0310(11, func_00f3a268, &D_00FCE390[slot]);
}
