/* newlib stdio/vfprintf.c, the vfprintf wrapper (the _vfprintf_r engine is
 * not decompiled yet). sdk segment. */
#include "reent.h"

int vfprintf(FILE *fp, const char *fmt0, va_list ap) {
    CHECK_INIT(fp);
    return _vfprintf_r(fp->_data, fp, fmt0, ap);
}
