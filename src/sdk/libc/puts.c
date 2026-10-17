/* newlib stdio/puts.c. sdk segment. */
#include "reent.h"

#include "fvwrite.h"


/* "\n" */
extern const char D_00491B28[];

int _puts_r(struct _reent *ptr, const char *s) {
    size_t c = strlen(s);
    struct __suio uio;
    struct __siov iov[2];

    iov[0].iov_base = s;
    iov[0].iov_len = c;
    iov[1].iov_base = D_00491B28;
    iov[1].iov_len = 1;
    uio.uio_resid = c + 1;
    uio.uio_iov = &iov[0];
    uio.uio_iovcnt = 2;

    return (__sfvwrite(_stdout_r(ptr), &uio) ? EOF : '\n');
}

int puts(const char *s) {
    return _puts_r(_REENT, s);
}
