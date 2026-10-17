#include "common.h"
int WaitSema(int);
int WakeupThread(int);
int RotateThreadReadyQueue(int);
int SuspendThread(int);
int func_00259c88(const char *, ...);
int CreateSema(void *);
int DeleteSema(int);
int CreateThread(void *);
int StartThread(int, void *);
int GetThreadId(void);
int ChangeThreadPriority(int, int);
extern char D_00492388[];
extern int D_0066E1B0;
extern int D_0046BE88;
typedef struct { u8 a, b; } Ev;
typedef struct { u32 rd; u32 wr; Ev ev[512]; } EvQ;
extern EvQ D_0066E1B8;
extern u8 D_0066DDB0[];
extern u8 D_00494050[];
typedef struct { int count, max, init, wait, attr, opt; } SemaParam;
typedef struct { int status; void *func; void *stack; int size; void *gp; int prio; int x18, x1c, x20, x24, x28, x2c; } ThreadParam;
void func_0025fb60(EvQ *q);

void func_0025fb60(EvQ *q) {
    int n;
    for (;;) {
        WaitSema(D_0066E1B0);
        n = q->rd & 0x1ff;
        q->rd = n + 1;
        switch (q->ev[n].a) {
        case 0:
            WakeupThread(q->ev[n].b);
            break;
        case 1:
            RotateThreadReadyQueue(q->ev[n].b);
            break;
        case 2:
            SuspendThread(q->ev[n].b);
            break;
        default:
            func_00259c88(D_00492388);
            break;
        }
    }
}

