/* The English fan patch on the port (include/lang.h, docs/english-patch.md).  When the disc image
 * holds the patch's SLPS_251.98 (its SHA-256 pinned in kh1.toml [english]), kh1_lang_en turns on
 * the English variants of the patched functions and the patch's data runs (lang_en.h, from
 * tools/host/en_ranges.py) are copied from that ELF into the data pieces, before the game's main
 * runs.  Any other disc (the retail one, a patched test build) leaves the port as it was.  Called
 * by kh1_cd_image_open (cd_image.c).  Not part of the PS2 build. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "lang_en.h"

int kh1_lang_en;

int kh1_cd_image_search(const char *name, u32 *lsn, u32 *size);
int kh1_cd_image_read(u32 lsn, u32 n, void *buf);
void kh1_sha256_hex(const u8 *p, u32 n, char out[65]);

void kh1_lang_detect(void) {
    u32 lsn, size, i, n = 0;
    char hex[65];
    u8 *elf;
    kh1_lang_en = 0;
    if (!kh1_cd_image_search("\\SLPS_251.98;1", &lsn, &size) || size != KH1_EN_ELF_SIZE) return;
    elf = malloc((size + 2047) & ~2047u);
    if (!elf) return;
    if (kh1_cd_image_read(lsn, (size + 2047) / 2048, elf)) {
        kh1_sha256_hex(elf, size, hex);
        if (strcmp(hex, KH1_EN_ELF_SHA256) == 0) {
            for (i = 0; i < sizeof kh1_en_runs / sizeof kh1_en_runs[0]; i++) {
                memcpy(kh1_en_runs[i].piece + kh1_en_runs[i].off, elf + kh1_en_runs[i].at, kh1_en_runs[i].len);
                n += kh1_en_runs[i].len;
            }
            kh1_lang_en = 1;
            printf("kh1-lang: the disc's ELF is the English patch's: English text (%u data bytes)\n", (unsigned)n);
        }
    }
    free(elf);
}
