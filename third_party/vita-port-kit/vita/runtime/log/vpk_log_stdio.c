/* printf / vprintf / puts straight into the log (vpk_log.h), in place of newlib's: link this file and every
 * printf in the app, the game's included, lands in the log (gcc turns a bare printf("...\n") into puts).
 * From kh1-decomp host/vita/main.c @ e1575e1a. */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "vpk_log.h"

int vprintf(const char *fmt, va_list ap) {
    char buf[1024];
    int n = vsnprintf(buf, sizeof buf, fmt, ap);
    if (n > (int)sizeof buf - 1) n = sizeof buf - 1;
    vpk_log_write(buf, n);
    return n;
}

int printf(const char *fmt, ...) {
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vprintf(fmt, ap);
    va_end(ap);
    return n;
}

int puts(const char *s) {
    int n = (int)strlen(s);
    vpk_log_write(s, n);
    vpk_log_write("\n", 1);
    return n + 1;
}
