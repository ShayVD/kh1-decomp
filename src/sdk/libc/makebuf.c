/* newlib stdio/makebuf.c. sdk segment. */
#include "reent.h"

#define __SOPT 0x0400
#define __SNPT 0x0800
#define BUFSIZ 1024
#define S_IFMT 0170000
#define S_IFCHR 0020000
#define S_IFREG 0100000

/* Only st_mode is used; 112 bytes like the SDK's struct stat. */
struct stat {
    int st_dev;
    unsigned int st_mode;
    char _rest[104];
};

int _fstat_r(struct _reent *, int, struct stat *);
int _isatty(int);
void *_malloc_r(struct _reent *, size_t);
_fpos_t __sseek(void *, _fpos_t, int);
void _cleanup_r(struct _reent *);

void __smakebuf(register FILE *fp) {
    register size_t size, couldbetty;
    register void *p;
    struct stat st;

    if (fp->_flags & __SNBF) {
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
        return;
    }
    if (fp->_file < 0 || _fstat_r(fp->_data, fp->_file, &st) < 0) {
        couldbetty = 0;
        size = BUFSIZ;
        /* do not try to optimise fseek() */
        fp->_flags |= __SNPT;
    } else {
        couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
        size = BUFSIZ;
        /* Optimize fseek() only if it is a regular file. (The test for
           __sseek is mainly paranoia.) */
        if ((st.st_mode & S_IFMT) == S_IFREG && fp->_seek == __sseek) {
            fp->_flags |= __SOPT;
            fp->_blksize = 1024;
        } else
            fp->_flags |= __SNPT;
    }
    if ((p = _malloc_r(fp->_data, size)) == 0) {
        fp->_flags |= __SNBF;
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
    } else {
        fp->_data->__cleanup = _cleanup_r;
        fp->_flags |= __SMBF;
        fp->_bf._base = fp->_p = (unsigned char *) p;
        fp->_bf._size = size;
        if (couldbetty && _isatty(fp->_file))
            fp->_flags |= __SLBF;
    }
}
