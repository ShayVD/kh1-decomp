/* newlib stdlib/mallocr.c built with DEFINE_CALLOC: its own object, with
 * MALLOC_ZERO unrolled for 32-bit INTERNAL_SIZE_T. sdk segment. */
#include "reent.h"

#define INTERNAL_SIZE_T size_t

void *_malloc_r(struct _reent *, size_t);

struct malloc_chunk {
    INTERNAL_SIZE_T prev_size;
    INTERNAL_SIZE_T size;
    struct malloc_chunk *fd;
    struct malloc_chunk *bk;
};
typedef struct malloc_chunk *mchunkptr;

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define mem2chunk(mem) ((mchunkptr) ((char *) (mem) - 2 * SIZE_SZ))
#define chunksize(p) ((p)->size & ~(0x1 | 0x2))

#define MALLOC_ZERO(charp, nbytes)                                    \
    do {                                                              \
        INTERNAL_SIZE_T mzsz = (nbytes);                              \
        if (mzsz <= 9 * sizeof(mzsz)) {                               \
            INTERNAL_SIZE_T *mz = (INTERNAL_SIZE_T *) (charp);        \
            if (mzsz >= 5 * sizeof(mzsz)) {                           \
                *mz++ = 0;                                            \
                *mz++ = 0;                                            \
                if (mzsz >= 7 * sizeof(mzsz)) {                       \
                    *mz++ = 0;                                        \
                    *mz++ = 0;                                        \
                    if (mzsz >= 9 * sizeof(mzsz)) {                   \
                        *mz++ = 0;                                    \
                        *mz++ = 0;                                    \
                    }                                                 \
                }                                                     \
            }                                                         \
            *mz++ = 0;                                                \
            *mz++ = 0;                                                \
            *mz = 0;                                                  \
        } else                                                        \
            memset((charp), 0, mzsz);                                 \
    } while (0)

void *_calloc_r(struct _reent *reent_ptr, size_t n, size_t elem_size) {
    mchunkptr p;
    INTERNAL_SIZE_T csz;

    INTERNAL_SIZE_T sz = n * elem_size;

    void *mem = _malloc_r(reent_ptr, sz);

    if (mem == 0)
        return 0;
    else {
        p = mem2chunk(mem);

        csz = chunksize(p);

        MALLOC_ZERO(mem, csz - SIZE_SZ);
        return mem;
    }
}
