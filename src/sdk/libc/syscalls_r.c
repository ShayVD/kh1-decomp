/* newlib reent/{write,close,fstat,lseek,read}r.c: the reentrant wrappers
 * over the SDK's low-level I/O (whose _read and _write return int, widened
 * to long here). errno is D_00494028. sdk segment. */
#include "reent.h"

extern int D_00494028;
#define errno D_00494028

struct stat;

int _write(int, const void *, size_t);
int _close(int);
int _fstat(int, struct stat *);
_fpos_t _lseek(int, _fpos_t, int);
int _read(int, void *, size_t);

long _write_r(struct _reent *ptr, int fd, const void *buf, size_t cnt) {
    long ret;

    errno = 0;
    if ((ret = (long) _write(fd, buf, cnt)) == -1 && errno != 0)
        ptr->_errno = errno;
    return ret;
}

int _close_r(struct _reent *ptr, int fd) {
    int ret;

    errno = 0;
    if ((ret = _close(fd)) == -1 && errno != 0)
        ptr->_errno = errno;
    return ret;
}

int _fstat_r(struct _reent *ptr, int fd, struct stat *pstat) {
    int ret;

    errno = 0;
    if ((ret = _fstat(fd, pstat)) == -1 && errno != 0)
        ptr->_errno = errno;
    return ret;
}

_fpos_t _lseek_r(struct _reent *ptr, int fd, _fpos_t pos, int whence) {
    _fpos_t ret;

    errno = 0;
    if ((ret = _lseek(fd, pos, whence)) == (_fpos_t) -1 && errno != 0)
        ptr->_errno = errno;
    return ret;
}

long _read_r(struct _reent *ptr, int fd, void *buf, size_t cnt) {
    long ret;

    errno = 0;
    if ((ret = (long) _read(fd, buf, cnt)) == -1 && errno != 0)
        ptr->_errno = errno;
    return ret;
}
