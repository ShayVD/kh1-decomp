/* tests/host/vu1chain_test.c's stand-in for out/gen/vu1_tr.c (the user's programs, never committed): five one-word
 * "programs" numbered as the native parses' (P18, P11, P10, P0, P4), each told apart by its MPG word; running one
 * records what it reads (vu1chain_test.c fk_run).  No game data. */
static int fk_run(u32 pc);
static const u32 fk_w[5][2] = {
    { 0x11110018u, 0x8000033Cu }, { 0x11110011u, 0x8000033Cu }, { 0x11110010u, 0x8000033Cu },
    { 0x11110000u, 0x8000033Cu }, { 0x11110004u, 0x8000033Cu },
};
static const TrProg tr_progs[] = {
    { fk_w[0], 1, fk_run, 18 }, { fk_w[1], 1, fk_run, 11 }, { fk_w[2], 1, fk_run, 10 },
    { fk_w[3], 1, fk_run, 0 },  { fk_w[4], 1, fk_run, 4 },
};
#define TR_PROGS 5
