/* newlib stdio/fvwrite.h. sdk segment. */
#ifndef KH1_SDK_FVWRITE_H
#define KH1_SDK_FVWRITE_H
#include "reent.h"

struct __siov {
    const void *iov_base;
    size_t iov_len;
};

struct __suio {
    struct __siov *uio_iov;
    int uio_iovcnt;
    int uio_resid;
};

int __sfvwrite(FILE *, struct __suio *);

#endif
