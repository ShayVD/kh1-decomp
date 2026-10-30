/* Round 51 wwm2: score 30 -> 8 at exact size 416. Loop 2 goes through D_01067FE0b, an asm-label second declaration of D_01067FE0 (extern ... __asm__("D_01067FE0")), so the reloc is the real symbol but loop.c/CSE do not reuse loop 1's base; b2 = D_01067FE0b feeds the return. Caveat: gcc treats the two names as non-aliasing (harmless here, the array is only written in loop 2 via one name). Left: loop 1 bne vs our bnel at the id test (and the beqzl slot), and loop 2 emits sw conds before swc1 v80[3] (target reverse); condtmp/maskfirst/v3first/if-split variants and hill3 200s gave nothing. */
/* Round 50 wwm2: score 89 -> 30 (latescan MORE lw 0 x5/3). The target walks the flags words with their own pointer giv (base + 160, step 192) next to an i*192 offset giv. Loop 1 reads flags through `p = &D_01067FE0[i].flags` but id through D_01067FE0[i].id, and returns i * sizeof + (u32)b. Loop 2 reaches flags/mask/id/conds/cnt through an H3bc48 view of &D_01067FE0[i].flags. Left: loop 1 base CSE (the target recomputes the base for loop 2), bne vs bnel at the id test, and one store pair. Earlier header below. */
/* loop GIV split: target uses a1 pointer to flags plus an offset reg; tried variants b-d */
typedef struct { u8 pad[0x40]; f32 m[4][4]; f32 v80[4]; f32 v90[4]; s32 flags; u32 mask; s32 id; void *conds; s32 cnt; u8 pad2[12]; } E3bc48;
typedef struct { u8 pad[0x20]; u16 h20; } R3bc48;
typedef struct { u16 h0; u16 h2; u16 h4; } Q3bc48;
typedef struct { u8 pad[0x540]; s32 x540; } G3bc48;
extern E3bc48 D_01067FE0[256];
extern E3bc48 D_01067FE0b[256] __asm__("D_01067FE0");
typedef struct { s32 flags; u32 mask; s32 id; void *conds; s32 cnt; } H3bc48;
extern G3bc48 *D_00F864C0;
extern s32 D_00F8704C;
void func_00f3bbf8(E3bc48 *);
R3bc48 *func_00f3f260(s32, s32);
Q3bc48 *func_00f62c78(s32, s32);
void *func_00f64c38(s32, s32);
void sceVu0UnitMatrix(f32 (*)[4]);
void func_00f3bb68(s32);

E3bc48 *func_00f3bc48(s32 arg0) {
    s32 i;
    E3bc48 *e;
    G3bc48 **pg;
    R3bc48 *r;
    Q3bc48 *q;
    H3bc48 *h;
    s32 *p;
    E3bc48 *b = D_01067FE0;
    E3bc48 *b2;
    for (i = 0; i < 256; i++) {
        p = &D_01067FE0[i].flags;
        if (*p & 4) {
            *p = 0;
        }
        if (D_01067FE0[i].id == arg0 && (*p & 1)) {
            *p |= 2;
            e = (E3bc48 *)(i * sizeof(E3bc48) + (u32)b);
            func_00f3bbf8(e);
            return e;
        }
    }
    b2 = D_01067FE0b;
    pg = &D_00F864C0;
    for (i = 0; i < 256; i++) {
        h = (H3bc48 *)&D_01067FE0b[i].flags;
        if (h->flags == 0) {
            r = func_00f3f260(arg0, (*pg)->x540);
            q = func_00f62c78(r->h20, (*pg)->x540);
            h->flags = 2;
            sceVu0UnitMatrix(D_01067FE0b[i].m);
            h->cnt = 0;
            h->id = arg0;
            h->conds = func_00f64c38(q->h4, D_00F8704C);
            h->mask = 0;
            D_01067FE0b[i].v80[0] = 0.0f;
            D_01067FE0b[i].v80[1] = 0.0f;
            D_01067FE0b[i].v80[2] = 0.0f;
            D_01067FE0b[i].v80[3] = 1.0f;
            D_01067FE0b[i].v90[0] = 0.0f;
            D_01067FE0b[i].v90[1] = 0.0f;
            D_01067FE0b[i].v90[2] = 0.0f;
            D_01067FE0b[i].v90[3] = 1.0f;
            func_00f3bb68(i);
            return (E3bc48 *)(i * sizeof(E3bc48) + (u32)b2);
        }
    }
    return NULL;
}
