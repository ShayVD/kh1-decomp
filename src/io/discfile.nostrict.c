/* Files on the disc: the file table looked up by a name hash (func_001200f8
 * the hash, func_00120190 a binary search, func_00120170 the compare), the
 * read requests (func_001204a0 starts one for a name, func_001201d0 reads
 * through sceCdRead, func_001202c0 the other path when func_002193b8 is set,
 * func_00120040 decodes a compressed file), the synchronous / asynchronous
 * loads (func_001205f0, func_00120678, func_00120748 with a callback),
 * func_00120930 builds a path in D_004E4500 (the prefix D_0048D278, then the
 * name upper-cased), and the disc set up at boot (func_00120b10 sceCdInit /
 * sceSifInitRpc, func_00120ba0 sceCdSearchFile). The read queue itself is
 * below 0x00120000 (func_0011ffd0 ...), still in src/hand. Flag mode:
 * nostrict (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/thread.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00110000_s6_04.h"
#include "data/pieces/D_002C5C48.h"

/* func_00120040 (from hand/nostrict/text_00110000_s6_04.c). */
s32 func_00120040(u8 *buf, s32 len) {
    u8 *p = buf + len;
    u8 key, c, n;
    s32 size, i, cnt;
    u8 *dst;
    key = *--p;
    { u8 b0 = *--p; u8 b1 = *--p; u8 b2 = *--p; size = b0 | b1 << 8 | b2 << 16; }
    dst = buf + size;
    while (buf < p) {
        c = *--p;
        if (c == key) {
            n = *--p;
            if (n != 0) {
                cnt = *--p + 3;
                for (i = 0; i < cnt; i++) {
                    dst--;
                    *dst = dst[n];
                }
            } else {
                *--dst = c;
            }
        } else {
            *--dst = c;
        }
    }
    return size;
}

/* func_001205f0 (from hand/nostrict/text_00110000_s6_04.c). */
typedef struct { u8 pad[0x30]; s32 result; } CdReq30;
CdReq30 *func_001204a0(char *, u8 *);
void func_0011fd40(void);
void func_00120038(CdReq30 *);
void kh1_ovl_flush0(CdReq30 *); /* shift build only (shift/ovl_fixup.c): overlay fixups + PlatFlushCache(0) */
s32 func_001205f0(char *name, u8 *buf) {
    CdReq30 *r = func_001204a0(name, buf);
    while (r->result < 0) {
        func_0011fd40();
        __asm__ volatile("nop\nnop\nnop\nnop\nnop");
    }
    D_002C5C48 = r->result;
    func_00120038(r);
#ifdef KH1_OVL_FIXUPS
    kh1_ovl_flush0(r); /* relocate an overlay before it is flushed and run; same size as PlatFlushCache(0) */
#else
    PlatFlushCache(0);
#endif
    PlatFlushCache(2);
    return D_002C5C48;
}

