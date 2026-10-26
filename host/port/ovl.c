/* The native overlays (include/platform/ovl.h, docs/native-overlays.md): the port links
 * an overlay's decompiled C (ovl/NAME/, built by tools/host/ovlnative.py into kh1_ovl_modules)
 * instead of running its MIPS bytes.  The game's loader still reads the file into the overlay
 * area, so the C finds its data (strings, tables, the variables past the file) where the PS2
 * code did; PlatOvlLoaded checks the bytes are the pinned file (ovl/overlays.tsv) and rewrites
 * the data's pointers into the overlay (ovl/NAME/relocs.tsv) to native ones.  Not part of the
 * PS2 build. */
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "platform/ovl.h"

extern u8 D_00F20000[];
extern u8 kh1_memmap[];
#define KH1_MEM_BASE 0x6A0000u

static const KH1OvlModule *current;

/* SHA-256 (FIPS 180-4), for the pin check */
static const u32 K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};
#define ROR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
static void sha_block(u32 h[8], const u8 *p) {
    u32 w[64], a, b, c, d, e, f, g, k, t1, t2;
    int i;
    for (i = 0; i < 16; i++) w[i] = (u32)p[4 * i] << 24 | (u32)p[4 * i + 1] << 16 | (u32)p[4 * i + 2] << 8 | p[4 * i + 3];
    for (; i < 64; i++)
        w[i] = (ROR(w[i - 2], 17) ^ ROR(w[i - 2], 19) ^ (w[i - 2] >> 10)) + w[i - 7] +
               (ROR(w[i - 15], 7) ^ ROR(w[i - 15], 18) ^ (w[i - 15] >> 3)) + w[i - 16];
    a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], k = h[7];
    for (i = 0; i < 64; i++) {
        t1 = k + (ROR(e, 6) ^ ROR(e, 11) ^ ROR(e, 25)) + ((e & f) ^ (~e & g)) + K[i] + w[i];
        t2 = (ROR(a, 2) ^ ROR(a, 13) ^ ROR(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
        k = g, g = f, f = e, e = d + t1, d = c, c = b, b = a, a = t1 + t2;
    }
    h[0] += a, h[1] += b, h[2] += c, h[3] += d, h[4] += e, h[5] += f, h[6] += g, h[7] += k;
}
static void sha256_hex(const u8 *p, u32 n, char out[65]) {
    u32 h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    u8 last[128];
    u32 i, rest = n % 64, tail;
    for (i = 0; i + 64 <= n; i += 64) sha_block(h, p + i);
    memset(last, 0, sizeof last);
    memcpy(last, p + i, rest);
    last[rest] = 0x80;
    tail = rest < 56 ? 64 : 128;
    for (i = 0; i < 4; i++) last[tail - 1 - i] = (u8)((u64)n * 8 >> (8 * i));
    last[tail - 5] = (u8)(n >> 29);
    sha_block(h, last);
    if (tail == 128) sha_block(h, last + 64);
    for (i = 0; i < 8; i++) sprintf(out + 8 * i, "%08x", (unsigned)h[i]);
}

static int same_name(const char *a, const char *b) {
    for (; *a && *b; a++, b++)
        if ((*a | 0x20) != (*b | 0x20)) return 0;
    return *a == *b;
}

void PlatOvlLoaded(const char *name, void *buf, s32 size) {
    int i;
    char hex[65];
    if (buf != (void *)D_00F20000) return;
    current = 0;
    for (i = 0; i < kh1_ovl_module_count; i++) {
        const KH1OvlModule *m = &kh1_ovl_modules[i];
        if (!same_name(name, m->file)) continue;
        if ((u32)size != m->size) {
            printf("kh1-ovl: %s: %d bytes, not the pinned %u: its native C stays off\n", name, (int)size, m->size);
            return;
        }
        sha256_hex(D_00F20000, m->size, hex);
        if (strcmp(hex, m->sha256) != 0) {
            printf("kh1-ovl: %s is not the pinned file (sha256 %.12s...): its native C stays off\n", name, hex);
            return;
        }
        for (i = 0; i < m->nfix; i++) {
            const KH1OvlFix *f = &m->fix[i];
            u32 v = f->func ? (u32)(unsigned long)f->func : (u32)(unsigned long)(kh1_memmap + f->target - KH1_MEM_BASE);
            memcpy(kh1_memmap + f->at - KH1_MEM_BASE, &v, 4);
        }
        current = m;
        printf("kh1-ovl: %s loaded: native C (%d pointers fixed up)\n", name, m->nfix);
        return;
    }
    i = (int)strlen(name);
    if (i > 2 && name[i - 2] == '.' && (name[i - 1] | 0x20) == 'x') /* session 136: music also loads here */
        printf("kh1-ovl: %s loaded (%d bytes): no native C\n", name, (int)size);
}

int PlatOvlCall(int cmd, int arg, int *ret) {
    if (!current) return 0;
    *ret = current->entry(cmd, arg);
    return 1;
}

const char *PlatOvlCurrent(void) { return current ? current->file : 0; }

/* include/platform/ovlsdk.h: func_0024e640(stack, size, fn, arg) runs fn(arg) on a stack of its
 * own; a port's thread already has one */
void PlatCallOnStack(void *stack, int size, void (*fn)(void *), void *arg) {
    (void)stack;
    (void)size;
    fn(arg);
}
