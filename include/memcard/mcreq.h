/* The memory card requests (src/memcard/, docs/modules.md "Session 44").
 *
 * Game code never calls libmc directly: it queues a request
 * (func_00234018 ... func_002347e0, each returns the request's id), and
 * func_002365e0 runs the queue once a frame (the step table D_00425BD0:
 * 0 takes the next request, 1-13 run one).  func_00233d08(id) is 1 while
 * the request (0: any) is queued or running, func_00233db0(id) waits for it.
 * The answer of the last request of each kind is a small code (0 = done)
 * in D_00647FEC ... D_0064801C, read by func_00234840 ... func_00234900.
 *
 * On the Vita build the libmc calls of src/memcard/mcstep.c are the ones
 * to replace (include/platform/mc.h); the queue and the codes stay. */
#ifndef KH1_MEMCARD_MCREQ_H
#define KH1_MEMCARD_MCREQ_H

#include "common.h"

/* One queued request (D_006477B0[64], a ring: D_00647FBC the next to run,
 * D_00647FB8 the next free).  type: 1 card info, 2 the directory "*",
 * 3 the directory of a name, 4 format, 5 unformat, 6 change directory,
 * 7 make a directory, 8 write a new file, 9 delete, 10 read a file, 11
 * write a file that exists, 12 set a file's info, 13 only call the hook.
 * a[]: port, slot, then the request's own arguments; the last is a hook
 * called with the id when the request ends. */
typedef struct {
    s32 type;
    s32 id;
    s32 a[6];
} McCmd;

#endif /* KH1_MEMCARD_MCREQ_H */
