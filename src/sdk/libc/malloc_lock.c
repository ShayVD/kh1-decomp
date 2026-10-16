/* SCE's newlib __malloc_lock: a recursive lock on one semaphore, keyed by
 * thread id (__malloc_unlock matched automatically, src/sdk/auto). sdk
 * segment. */
#include "reent.h"

int GetThreadId(void);
int WaitSema(int);

extern int D_0046AE28; /* owner thread, -1 when free */
extern int D_0046AE2C; /* recursion count */
extern int D_0046AF10; /* semaphore id */

void __malloc_lock(struct _reent *ptr) {
    int tid = GetThreadId();

    if (D_0046AE28 == tid) {
        D_0046AE2C++;
        return;
    }
    WaitSema(D_0046AF10);
    D_0046AE28 = tid;
    D_0046AE2C++;
}
