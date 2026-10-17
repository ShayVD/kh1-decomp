/* newlib stdio/fiprintf.c. sdk segment. */
#include "reent.h"

int fiprintf(FILE *fp, const char *fmt, ...) {
    int ret;
    va_list ap;

    va_start(ap, fmt);
    ret = vfiprintf(fp, fmt, ap);
    va_end(ap);
    return ret;
}
