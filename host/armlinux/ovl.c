/* The overlay entry for the ARM Linux check (tools/vita/build.py --linux-arm, docs/vita-build.md):
 * the null runner built for 32-bit ARM and run under qemu-arm, with the Vita build's overlay calls
 * (kh1_ovl_entry, the preprocessed calls of D_00F20000) answered as the host's KH1_HOST_OVL=stub[:N]
 * answers them on x86 (host/null/main.c), so the two runs' logs can be compared line by line.  Not
 * part of the PS2 build. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func_00109558(int state);
unsigned long kh1_host_frame(void);

int kh1_ovl_entry(int cmd, int arg) {
    static int state = -2;
    if (state == -2) {
        const char *s = getenv("KH1_HOST_OVL");
        state = s && strncmp(s, "stub:", 5) == 0 ? atoi(s + 5) : -1;
    }
    printf("kh1-host: frame %lu: overlay entry D_00F20000(%d, %d) answered 0\n", kh1_host_frame(), cmd, arg);
    if (state >= 0 && cmd == 0) {
        printf("kh1-host: KH1_HOST_OVL: func_00109558(%d), the title's choice (a guess)\n", state);
        func_00109558(state);
        state = -1;
    }
    return 0;
}
