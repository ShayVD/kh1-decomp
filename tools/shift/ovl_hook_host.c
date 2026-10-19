/*
 * Host driver for the static proof (tools/shift/ovl_proof.py): runs the real
 * KH1_OVL_FIXUPS hook code (shift/ovl_fixup.c, compiled for the build host) on
 * one overlay with the table bytes taken from a linked shift ELF.
 *
 *   ovl_hook_host TABLE.bin OVERLAY.x NAME OUT.bin
 *
 * Prints the hook's return value; writes the patched overlay to OUT.bin
 * (under out/ only: it holds the user's overlay bytes).
 */
#include <stdio.h>
#include <stdlib.h>

int kh1_ovl_apply(const unsigned char *tab, const char *name, unsigned char *buf, unsigned int size,
                  unsigned int base);

static unsigned char *slurp(const char *path, long *n) {
    FILE *f = fopen(path, "rb");
    unsigned char *b;
    if (!f) {
        perror(path);
        exit(2);
    }
    fseek(f, 0, SEEK_END);
    *n = ftell(f);
    fseek(f, 0, SEEK_SET);
    b = malloc(*n + 4);
    if (!b || fread(b, 1, *n, f) != (size_t)*n) {
        perror(path);
        exit(2);
    }
    fclose(f);
    return b;
}

int main(int argc, char **argv) {
    long nt, no;
    unsigned char *tab, *ovl;
    FILE *f;
    int r;
    if (argc != 5) {
        fprintf(stderr, "usage: %s TABLE.bin OVERLAY.x NAME OUT.bin\n", argv[0]);
        return 2;
    }
    tab = slurp(argv[1], &nt);
    ovl = slurp(argv[2], &no);
    r = kh1_ovl_apply(tab, argv[3], ovl, (unsigned int)no, 0x00F20000u);
    printf("%d\n", r);
    f = fopen(argv[4], "wb");
    if (!f || fwrite(ovl, 1, no, f) != (size_t)no) {
        perror(argv[4]);
        return 2;
    }
    fclose(f);
    return 0;
}
