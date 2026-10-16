/* newlib stdio/vfprintf.c, the vfprintf wrapper (the _vfprintf_r engine is
 * not decompiled yet). sdk segment. */
#include "reent.h"

/* vfprintf.c's static __sbprintf: flush a temporary buffer for unbuffered
 * files. */
#define __sbprintf func_00252370
static int __sbprintf(register FILE *fp, const char *fmt, va_list ap) {
    int ret;
    FILE fake;
    unsigned char buf[1024]; /* BUFSIZ */

    /* copy the important variables */
    fake._data = fp->_data;
    fake._flags = fp->_flags & ~__SNBF;
    fake._file = fp->_file;
    fake._cookie = fp->_cookie;
    fake._write = fp->_write;

    /* set up the buffer */
    fake._bf._base = fake._p = buf;
    fake._bf._size = fake._w = sizeof(buf);
    fake._lbfsize = 0; /* not actually used, but Just In Case */

    /* do the work, then copy any error status */
    ret = vfprintf(&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake))
        ret = EOF;
    if (fake._flags & __SERR)
        fp->_flags |= __SERR;
    return (ret);
}

int vfprintf(FILE *fp, const char *fmt0, va_list ap) {
    CHECK_INIT(fp);
    return _vfprintf_r(fp->_data, fp, fmt0, ap);
}
