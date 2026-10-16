/* newlib stdlib/mallocr.c: Doug Lea's malloc 2.6.x as newlib built it for
 * the EE (MALLOC_ALIGNMENT 16, INTERNAL_SIZE_T = 32-bit size_t, the
 * statistics as unsigned long). sdk segment. */
#include "reent.h"

#define INTERNAL_SIZE_T size_t
#define Void_t void
#define RARG struct _reent *reent_ptr,
#define RONEARG struct _reent *reent_ptr
#define RCALL reent_ptr,

void __malloc_lock(struct _reent *);
void __malloc_unlock(struct _reent *);
void *_sbrk_r(struct _reent *, int); /* ptrdiff_t */
int _malloc_trim_r(struct _reent *, size_t);
void _free_r(struct _reent *, void *);

#define MALLOC_LOCK __malloc_lock(reent_ptr)
#define MALLOC_UNLOCK __malloc_unlock(reent_ptr)
#define MORECORE(size) _sbrk_r(reent_ptr, (size))
#define MORECORE_FAILURE (-1)
#define malloc_getpagesize (4096)

#define fREe(p) _free_r(reent_ptr, p)
#define malloc_trim(pad) _malloc_trim_r(reent_ptr, pad)

struct malloc_chunk {
    INTERNAL_SIZE_T prev_size; /* Size of previous chunk (if free). */
    INTERNAL_SIZE_T size;      /* Size in bytes, including overhead. */
    struct malloc_chunk *fd;   /* double links -- used only if free. */
    struct malloc_chunk *bk;
};

typedef struct malloc_chunk *mchunkptr;

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define MALLOC_ALIGNMENT 16
#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MINSIZE (sizeof(struct malloc_chunk))

#define chunk2mem(p) ((Void_t *) ((char *) (p) + 2 * SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr) ((char *) (mem) - 2 * SIZE_SZ))

#define request2size(req)                                                      \
    (((long) ((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) < (long) (MINSIZE + MALLOC_ALIGN_MASK)) \
         ? MINSIZE                                                             \
         : (((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) & ~(MALLOC_ALIGN_MASK)))

/* Subtract two size_t values and return the result as a long. */
#define long_sub_size_t(x, y) \
    (sizeof(long) > sizeof(INTERNAL_SIZE_T) && x < y ? -(long) (y - x) : (long) (x - y))

#define PREV_INUSE 0x1
#define IS_MMAPPED 0x2
#define SIZE_BITS (PREV_INUSE | IS_MMAPPED)

#define next_chunk(p) ((mchunkptr) (((char *) (p)) + ((p)->size & ~PREV_INUSE)))
#define prev_chunk(p) ((mchunkptr) (((char *) (p)) - ((p)->prev_size)))
#define chunk_at_offset(p, s) ((mchunkptr) (((char *) (p)) + (s)))

#define inuse_bit_at_offset(p, s) (((mchunkptr) (((char *) (p)) + (s)))->size & PREV_INUSE)
#define set_inuse_bit_at_offset(p, s) (((mchunkptr) (((char *) (p)) + (s)))->size |= PREV_INUSE)

#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head_size(p, s) ((p)->size = (((p)->size & PREV_INUSE) | (s)))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr) ((char *) (p) + (s)))->prev_size = (s))

#define NAV 128 /* number of bins */
typedef struct malloc_chunk *mbinptr;

/* The SDK's malloc state, in .data at its original addresses. */
extern mbinptr D_0046A9D0[NAV * 2 + 2];      /* av_ */
extern unsigned long D_0046ADD8;             /* trim_threshold */
extern unsigned long D_0046ADE0;             /* top_pad */
extern char *D_0046ADE8;                     /* sbrk_base */
extern unsigned long D_0046ADF0;             /* max_sbrked_mem */
extern unsigned long D_0046ADF8;             /* max_total_mem */
struct mallinfo {
    int arena;    /* total space allocated from system */
    int ordblks;  /* number of non-inuse chunks */
    int smblks;   /* unused -- always zero */
    int hblks;    /* number of mmapped regions */
    int hblkhd;   /* total space in mmapped regions */
    int usmblks;  /* unused -- always zero */
    int fsmblks;  /* unused -- always zero */
    int uordblks; /* total allocated space */
    int fordblks; /* total non-inuse space */
    int keepcost; /* top-most, releasable (via malloc_trim) space */
};
extern struct mallinfo D_0046AE00;           /* current_mallinfo */
#define av_ D_0046A9D0
#define trim_threshold D_0046ADD8
#define top_pad D_0046ADE0
#define sbrk_base D_0046ADE8
#define max_sbrked_mem D_0046ADF0
#define max_total_mem D_0046ADF8
#define current_mallinfo D_0046AE00
#define sbrked_mem current_mallinfo.arena

#define bin_at(i) ((mbinptr) ((char *) &(av_[2 * (i) + 2]) - 2 * SIZE_SZ))
#define next_bin(b) ((mbinptr) ((char *) (b) + 2 * sizeof(mbinptr)))
#define prev_bin(b) ((mbinptr) ((char *) (b) - 2 * sizeof(mbinptr)))

#define top (bin_at(0)->fd)            /* The topmost chunk */
#define last_remainder (bin_at(1))     /* remainder from last split */
#define initial_top ((mchunkptr) (bin_at(0)))

#define first(b) ((b)->fd)
#define last(b) ((b)->bk)

#define bin_index(sz)                                                                  \
    (((((unsigned long) (sz)) >> 9) == 0)      ? (((unsigned long) (sz)) >> 3)       \
     : ((((unsigned long) (sz)) >> 9) <= 4)    ? 56 + (((unsigned long) (sz)) >> 6)  \
     : ((((unsigned long) (sz)) >> 9) <= 20)   ? 91 + (((unsigned long) (sz)) >> 9)  \
     : ((((unsigned long) (sz)) >> 9) <= 84)   ? 110 + (((unsigned long) (sz)) >> 12) \
     : ((((unsigned long) (sz)) >> 9) <= 340)  ? 119 + (((unsigned long) (sz)) >> 15) \
     : ((((unsigned long) (sz)) >> 9) <= 1364) ? 124 + (((unsigned long) (sz)) >> 18) \
                                               : 126)

#define MAX_SMALLBIN 63
#define MAX_SMALLBIN_SIZE 512
#define SMALLBIN_WIDTH 8

#define smallbin_index(sz) (((unsigned long) (sz)) >> 3)
#define is_small_request(nb) (nb < MAX_SMALLBIN_SIZE - SMALLBIN_WIDTH)

#define BINBLOCKWIDTH 4 /* bins per block */
#define binblocks (bin_at(0)->size) /* bitvector of nonempty blocks */
#define idx2binblock(ix) ((unsigned long) 1 << (ix / BINBLOCKWIDTH))
#define mark_binblock(ii) (binblocks |= idx2binblock(ii))
#define clear_binblock(ii) (binblocks &= ~(idx2binblock(ii)))

#define frontlink(P, S, IDX, BK, FD)                                   \
    {                                                                  \
        if (S < MAX_SMALLBIN_SIZE) {                                   \
            IDX = smallbin_index(S);                                   \
            mark_binblock(IDX);                                        \
            BK = bin_at(IDX);                                          \
            FD = BK->fd;                                               \
            P->bk = BK;                                                \
            P->fd = FD;                                                \
            FD->bk = BK->fd = P;                                       \
        } else {                                                       \
            IDX = bin_index(S);                                        \
            BK = bin_at(IDX);                                          \
            FD = BK->fd;                                               \
            if (FD == BK)                                              \
                mark_binblock(IDX);                                    \
            else {                                                     \
                while (FD != BK && S < chunksize(FD))                  \
                    FD = FD->fd;                                       \
                BK = FD->bk;                                           \
            }                                                          \
            P->bk = BK;                                                \
            P->fd = FD;                                                \
            FD->bk = BK->fd = P;                                       \
        }                                                              \
    }

#define unlink(P, BK, FD) \
    {                     \
        BK = P->bk;       \
        FD = P->fd;       \
        FD->bk = BK;      \
        BK->fd = FD;      \
    }

#define link_last_remainder(P)                                \
    {                                                         \
        last_remainder->fd = last_remainder->bk = P;          \
        P->fd = P->bk = last_remainder;                       \
    }

#define clear_last_remainder (last_remainder->fd = last_remainder->bk = last_remainder)

#define check_malloced_chunk(P, N)
#define check_chunk(P)
#define check_inuse_chunk(P)

/* Extend the top-most chunk by obtaining memory from system. Main
   interface to sbrk (but see also malloc_trim). */
static void malloc_extend_top(RARG INTERNAL_SIZE_T nb) {
    char *brk;                      /* return value from sbrk */
    INTERNAL_SIZE_T front_misalign; /* unusable bytes at front of sbrked space */
    INTERNAL_SIZE_T correction;     /* bytes for 2nd sbrk call */
    char *new_brk;                  /* return of 2nd sbrk call */
    INTERNAL_SIZE_T top_size;       /* new size of top chunk */

    mchunkptr old_top = top; /* Record state of old top */
    INTERNAL_SIZE_T old_top_size = chunksize(old_top);
    char *old_end = (char *) (chunk_at_offset(old_top, old_top_size));

    /* Pad request with top_pad plus minimal overhead */

    INTERNAL_SIZE_T sbrk_size = nb + top_pad + MINSIZE;
    unsigned long pagesz = malloc_getpagesize;

    /* If not the first time through, round to preserve page boundary */
    /* Otherwise, we need to correct to a page size below anyway. */
    /* (We also correct below if an intervening foreign sbrk call.) */

    if (sbrk_base != (char *) (-1))
        sbrk_size = (sbrk_size + (pagesz - 1)) & ~(pagesz - 1);

    brk = (char *) (MORECORE(sbrk_size));

    /* Fail if sbrk failed or if a foreign sbrk call killed our space */
    if (brk == (char *) (MORECORE_FAILURE) || (brk < old_end && old_top != initial_top))
        return;

    sbrked_mem += sbrk_size;

    if (brk == old_end) { /* can just add bytes to current top */
        top_size = sbrk_size + old_top_size;
        set_head(top, top_size | PREV_INUSE);
    } else {
        if (sbrk_base == (char *) (-1)) /* First time through. Record base */
            sbrk_base = brk;
        else /* Someone else called sbrk().  Count those bytes as sbrked_mem. */
            sbrked_mem += brk - (char *) old_end;

        /* Guarantee alignment of first new chunk made from this space */
        front_misalign = (unsigned long) chunk2mem(brk) & MALLOC_ALIGN_MASK;
        if (front_misalign > 0) {
            correction = (MALLOC_ALIGNMENT) - front_misalign;
            brk += correction;
        } else
            correction = 0;

        /* Guarantee the next brk will be at a page boundary */
        correction += pagesz - ((unsigned long) (brk + sbrk_size) & (pagesz - 1));

        /* Allocate correction */
        new_brk = (char *) (MORECORE(correction));
        if (new_brk == (char *) (MORECORE_FAILURE))
            return;

        sbrked_mem += correction;

        top = (mchunkptr) brk;
        top_size = new_brk - brk + correction;
        set_head(top, top_size | PREV_INUSE);

        if (old_top != initial_top) {
            /* There must have been an intervening foreign sbrk call. */
            /* A double fence post is necessary to prevent consolidation */

            /* If not enough space to do this, then user did something very wrong */
            if (old_top_size < MINSIZE) {
                set_head(top, PREV_INUSE); /* will force null return from malloc */
                return;
            }

            /* Also keep size a multiple of MALLOC_ALIGNMENT */
            old_top_size = (old_top_size - 3 * SIZE_SZ) & ~MALLOC_ALIGN_MASK;
            set_head_size(old_top, old_top_size);
            chunk_at_offset(old_top, old_top_size)->size = SIZE_SZ | PREV_INUSE;
            chunk_at_offset(old_top, old_top_size + SIZE_SZ)->size = SIZE_SZ | PREV_INUSE;
            /* If possible, release the rest. */
            if (old_top_size >= MINSIZE)
                fREe(chunk2mem(old_top));
        }
    }

    if ((unsigned long) sbrked_mem > (unsigned long) max_sbrked_mem)
        max_sbrked_mem = sbrked_mem;
    if ((unsigned long) (sbrked_mem) > (unsigned long) max_total_mem)
        max_total_mem = sbrked_mem;
}

Void_t *_malloc_r(RARG size_t bytes) {
    mchunkptr victim;            /* inspected/selected chunk */
    INTERNAL_SIZE_T victim_size; /* its size */
    int idx;                     /* index for bin traversal */
    mbinptr bin;                 /* associated bin */
    mchunkptr remainder;         /* remainder from a split */
    long remainder_size;         /* its size */
    int remainder_index;         /* its bin index */
    unsigned long block;         /* block traverser bit */
    int startidx;                /* first bin of a traversed block */
    mchunkptr fwd;               /* misc temp for linking */
    mchunkptr bck;               /* misc temp for linking */
    mbinptr q;                   /* misc temp */

    INTERNAL_SIZE_T nb = request2size(bytes); /* padded request size; */

    MALLOC_LOCK;

    /* Check for exact match in a bin */

    if (is_small_request(nb)) { /* Faster version for small requests */
        idx = smallbin_index(nb);

        /* No traversal or size check necessary for small bins.  */

        q = bin_at(idx);
        victim = last(q);

        if (victim != q) {
            victim_size = chunksize(victim);
            unlink(victim, bck, fwd);
            set_inuse_bit_at_offset(victim, victim_size);
            check_malloced_chunk(victim, nb);
            MALLOC_UNLOCK;
            return chunk2mem(victim);
        }

        idx += 2; /* Set for bin scan below. We've already scanned 2 bins. */
    } else {
        idx = bin_index(nb);
        bin = bin_at(idx);

        for (victim = last(bin); victim != bin; victim = victim->bk) {
            victim_size = chunksize(victim);
            remainder_size = long_sub_size_t(victim_size, nb);

            if (remainder_size >= (long) MINSIZE) { /* too big */
                --idx; /* adjust to rescan below after checking last remainder */
                break;
            }

            else if (remainder_size >= 0) { /* exact fit */
                unlink(victim, bck, fwd);
                set_inuse_bit_at_offset(victim, victim_size);
                check_malloced_chunk(victim, nb);
                MALLOC_UNLOCK;
                return chunk2mem(victim);
            }
        }

        ++idx;
    }

    /* Try to use the last split-off remainder */

    if ((victim = last_remainder->fd) != last_remainder) {
        victim_size = chunksize(victim);
        remainder_size = long_sub_size_t(victim_size, nb);

        if (remainder_size >= (long) MINSIZE) { /* re-split */
            remainder = chunk_at_offset(victim, nb);
            set_head(victim, nb | PREV_INUSE);
            link_last_remainder(remainder);
            set_head(remainder, remainder_size | PREV_INUSE);
            set_foot(remainder, remainder_size);
            check_malloced_chunk(victim, nb);
            MALLOC_UNLOCK;
            return chunk2mem(victim);
        }

        clear_last_remainder;

        if (remainder_size >= 0) { /* exhaust */
            set_inuse_bit_at_offset(victim, victim_size);
            check_malloced_chunk(victim, nb);
            MALLOC_UNLOCK;
            return chunk2mem(victim);
        }

        /* Else place in bin */

        frontlink(victim, victim_size, remainder_index, bck, fwd);
    }

    /* If there are any possibly nonempty big-enough blocks, search for best
       fitting chunk by scanning bins in blockwidth units. */

    if ((block = idx2binblock(idx)) <= binblocks) {
        /* Get to the first marked block */

        if ((block & binblocks) == 0) {
            /* force to an even block boundary */
            idx = (idx & ~(BINBLOCKWIDTH - 1)) + BINBLOCKWIDTH;
            block <<= 1;
            while ((block & binblocks) == 0) {
                idx += BINBLOCKWIDTH;
                block <<= 1;
            }
        }

        /* For each possibly nonempty block ... */
        for (;;) {
            startidx = idx; /* (track incomplete blocks) */
            q = bin = bin_at(idx);

            /* For each bin in this block ... */
            do {
                /* Find and use first big enough chunk ... */

                for (victim = last(bin); victim != bin; victim = victim->bk) {
                    victim_size = chunksize(victim);
                    remainder_size = long_sub_size_t(victim_size, nb);

                    if (remainder_size >= (long) MINSIZE) { /* split */
                        remainder = chunk_at_offset(victim, nb);
                        set_head(victim, nb | PREV_INUSE);
                        unlink(victim, bck, fwd);
                        link_last_remainder(remainder);
                        set_head(remainder, remainder_size | PREV_INUSE);
                        set_foot(remainder, remainder_size);
                        check_malloced_chunk(victim, nb);
                        MALLOC_UNLOCK;
                        return chunk2mem(victim);
                    }

                    else if (remainder_size >= 0) { /* take */
                        set_inuse_bit_at_offset(victim, victim_size);
                        unlink(victim, bck, fwd);
                        check_malloced_chunk(victim, nb);
                        MALLOC_UNLOCK;
                        return chunk2mem(victim);
                    }
                }

                bin = next_bin(bin);

                if (idx < MAX_SMALLBIN) {
                    bin = next_bin(bin);
                    ++idx;
                }
            } while ((++idx & (BINBLOCKWIDTH - 1)) != 0);

            /* Clear out the block bit. */

            do { /* Possibly backtrack to try to clear a partial block */
                if ((startidx & (BINBLOCKWIDTH - 1)) == 0) {
                    binblocks &= ~block;
                    break;
                }
                --startidx;
                q = prev_bin(q);
            } while (first(q) == q);

            /* Get to the next possibly nonempty block */

            if ((block <<= 1) <= binblocks && (block != 0)) {
                while ((block & binblocks) == 0) {
                    idx += BINBLOCKWIDTH;
                    block <<= 1;
                }
            } else
                break;
        }
    }

    /* Try to use top chunk */

    /* Require that there be a remainder, ensuring top always exists  */
    remainder_size = long_sub_size_t(chunksize(top), nb);
    if (chunksize(top) < nb || remainder_size < (long) MINSIZE) {
        /* Try to extend */
        malloc_extend_top(RCALL nb);
        remainder_size = long_sub_size_t(chunksize(top), nb);
        if (chunksize(top) < nb || remainder_size < (long) MINSIZE) {
            MALLOC_UNLOCK;
            return 0; /* propagate failure */
        }
    }

    victim = top;
    set_head(victim, nb | PREV_INUSE);
    top = chunk_at_offset(victim, nb);
    set_head(top, remainder_size | PREV_INUSE);
    check_malloced_chunk(victim, nb);
    MALLOC_UNLOCK;
    return chunk2mem(victim);
}

void _free_r(RARG Void_t *mem) {
    mchunkptr p;            /* chunk corresponding to mem */
    INTERNAL_SIZE_T hd;     /* its head field */
    INTERNAL_SIZE_T sz;     /* its size */
    int idx;                /* its bin index */
    mchunkptr next;         /* next contiguous chunk */
    INTERNAL_SIZE_T nextsz; /* its size */
    INTERNAL_SIZE_T prevsz; /* size of previous contiguous chunk */
    mchunkptr bck;          /* misc temp for linking */
    mchunkptr fwd;          /* misc temp for linking */
    int islr;               /* track whether merging with last_remainder */

    if (mem == 0) /* free(0) has no effect */
        return;

    MALLOC_LOCK;

    p = mem2chunk(mem);
    hd = p->size;

    check_inuse_chunk(p);

    sz = hd & ~PREV_INUSE;
    next = chunk_at_offset(p, sz);
    nextsz = chunksize(next);

    if (next == top) { /* merge with top */
        sz += nextsz;

        if (!(hd & PREV_INUSE)) { /* consolidate backward */
            prevsz = p->prev_size;
            p = chunk_at_offset(p, -prevsz);
            sz += prevsz;
            unlink(p, bck, fwd);
        }

        set_head(p, sz | PREV_INUSE);
        top = p;
        if ((unsigned long) (sz) >= (unsigned long) trim_threshold)
            malloc_trim(top_pad);
        MALLOC_UNLOCK;
        return;
    }

    set_head(next, nextsz); /* clear inuse bit */

    islr = 0;

    if (!(hd & PREV_INUSE)) { /* consolidate backward */
        prevsz = p->prev_size;
        p = chunk_at_offset(p, -prevsz);
        sz += prevsz;

        if (p->fd == last_remainder) /* keep as last_remainder */
            islr = 1;
        else
            unlink(p, bck, fwd);
    }

    if (!(inuse_bit_at_offset(next, nextsz))) { /* consolidate forward */
        sz += nextsz;

        if (!islr && next->fd == last_remainder) { /* re-insert last_remainder */
            islr = 1;
            link_last_remainder(p);
        } else
            unlink(next, bck, fwd);
    }

    set_head(p, sz | PREV_INUSE);
    set_foot(p, sz);
    if (!islr)
        frontlink(p, sz, idx, bck, fwd);

    MALLOC_UNLOCK;
}

int _malloc_trim_r(RARG size_t pad) {
    long top_size;     /* Amount of top-most memory */
    long extra;        /* Amount to release */
    char *current_brk; /* address returned by pre-check sbrk call */
    char *new_brk;     /* address returned by negative sbrk call */

    unsigned long pagesz = malloc_getpagesize;

    MALLOC_LOCK;

    top_size = chunksize(top);
    extra = ((top_size - pad - MINSIZE + (pagesz - 1)) / pagesz - 1) * pagesz;

    if (extra < (long) pagesz) { /* Not enough memory to release */
        MALLOC_UNLOCK;
        return 0;
    }

    else {
        /* Test to make sure no one else called sbrk */
        current_brk = (char *) (MORECORE(0));
        if (current_brk != (char *) (top) + top_size) {
            MALLOC_UNLOCK;
            return 0; /* Apparently we don't own memory; must fail */
        }

        else {
            new_brk = (char *) (MORECORE(-extra));

            if (new_brk == (char *) (MORECORE_FAILURE)) { /* sbrk failed? */
                /* Try to figure out what we have */
                current_brk = (char *) (MORECORE(0));
                top_size = current_brk - (char *) top;
                if (top_size >= (long) MINSIZE) { /* if not, we are very very dead! */
                    sbrked_mem = current_brk - sbrk_base;
                    set_head(top, top_size | PREV_INUSE);
                }
                check_chunk(top);
                MALLOC_UNLOCK;
                return 0;
            }

            else {
                /* Success. Adjust top accordingly. */
                set_head(top, (top_size - extra) | PREV_INUSE);
                sbrked_mem -= extra;
                check_chunk(top);
                MALLOC_UNLOCK;
                return 1;
            }
        }
    }
}
