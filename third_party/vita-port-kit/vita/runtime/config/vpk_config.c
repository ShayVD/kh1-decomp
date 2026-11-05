/* config.txt's key=value lines (vpk_config.h).  From kh1-decomp host/vita/main.c config() @ e1575e1a. */
#include <stdio.h>
#include <string.h>
#include "vpk_config.h"

int vpk_config_read(const char *path, VpkConfigFn fn, void *user) {
    char line[256];
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    while (fgets(line, sizeof line, f)) {
        char *v = strchr(line, '='), *e;
        if (line[0] == '#' || !v) continue;
        *v++ = 0;
        for (e = v + strlen(v); e > v && (e[-1] == '\n' || e[-1] == '\r' || e[-1] == ' '); e--) e[-1] = 0;
        fn(line, v, user);
    }
    fclose(f);
    return 1;
}
