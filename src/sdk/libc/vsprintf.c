/* newlib stdio/vsprintf.c. sdk segment. */
#include "reent.h"

int vsprintf(char *str, const char *fmt, va_list ap) {
    int ret;
    FILE f;

    f._flags = __SWR | __SSTR;
    f._bf._base = f._p = (unsigned char *) str;
    f._bf._size = f._w = INT_MAX;
    f._data = _REENT;
    ret = vfprintf(&f, fmt, ap);
    *f._p = 0;
    return ret;
}

int _vsprintf_r(struct _reent *ptr, char *str, const char *fmt, va_list ap) {
    int ret;
    FILE f;

    f._flags = __SWR | __SSTR;
    f._bf._base = f._p = (unsigned char *) str;
    f._bf._size = f._w = INT_MAX;
    f._data = ptr;
    ret = vfprintf(&f, fmt, ap);
    *f._p = 0;
    return ret;
}
