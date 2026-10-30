/* 3 words left; tried ~10 statement/temp variants (A-I) and the permuter. Round 6: struct pointer &e->s, (S*) byte-offset and array-of-S index forms; target keeps +224 in the index giv and loads buf with lw 4(s2). */
typedef struct { s32 on; u8 *buf; } S3a030;
typedef struct { u8 pad[224]; S3a030 s; u8 pad2[40]; } E3a030;
extern E3a030 D_00FCE390[256];
s32 func_00f39ef0(s32);
void func_0011d3c8(s32, u8 *, s32);

void func_00f3a030(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 256; i++) {
        if (D_00FCE390[i].s.on != 0) {
            for (j = 0; j < 5; j++) {
                u8 *p;
                p = D_00FCE390[i].s.buf;
                p += 0x2000;
                func_0011d3c8(func_00f39ef0(j), p, 60);
            }
        }
    }
}
