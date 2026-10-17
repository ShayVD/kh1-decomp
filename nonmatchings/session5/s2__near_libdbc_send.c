#include "common.h"
s32 sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
void func_00268a78(const char *, ...);
s32 func_0025a750(void *);
extern u8 D_0066FB08[];
extern u8 D_0066FB30[];
extern s32 D_0066FB80[];
extern char D_00493078[];
extern char D_00493058[];
extern char D_00493098[];
typedef struct { s32 valid, type, idx, shift; } BtnEnt;
typedef struct { u8 pad[124]; s32 cnt; } PadBuf;
typedef struct { s32 x0, x4, x8; PadBuf *buf; BtnEnt btn[(0x330 - 16) / 16]; } Pad2Slot;
extern Pad2Slot D_00670040[];

s32 sceDbcSendData2(s32 sock, u32 cmd, s32 *len, u8 *data) {
    s32 *p = D_0066FB80;
    s32 i;
    D_0066FB80[0] = sock;
    p[1] = cmd;
    p[2] = *len;
    for (i = 0; i < *len; i++) ((u8 *)&p[3])[i] = data[i];
    if (func_0025a750(D_0066FB30) == 1) return 0;
    if (sceSifCallRpc(D_0066FB30, 0x8000091b, 1, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00493078);
        return 0;
    }
    return 1;
}
s32 sceDbcSendData(s32 sock, u32 cmd, s32 *len, u8 *data) {
    s32 *p = D_0066FB80;
    s32 i;
    D_0066FB80[0] = sock;
    p[1] = cmd;
    p[2] = *len;
    for (i = 0; i < *len; i++) ((u8 *)&p[3])[i] = data[i];
    if (sceSifCallRpc(D_0066FB08, 0x80000919, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00493058);
        return 0;
    }
    if (p[35] >= 0) *len = p[2];
    return p[35];
}
s32 sceDbcReceiveData(s32 sock, u32 cmd, s32 *len, u8 *data) {
    s32 *p = D_0066FB80;
    s32 i;
    D_0066FB80[0] = sock;
    p[1] = cmd;
    p[2] = *len;
    if (sceSifCallRpc(D_0066FB08, 0x8000091a, 0, p, 1024, p, 1024, 0, 0) < 0) {
        func_00268a78(D_00493098);
        return 0;
    }
    if (p[35] >= 0) {
        *len = p[2];
        for (i = 0; i < p[2]; i++) data[i] = ((u8 *)&p[3])[i];
    }
    return p[35];
}
s32 func_00268ff0(s32 s, u8 *data, s32 btn) {
    BtnEnt e = D_00670040[s].btn[btn];
    u8 v;
    if (!e.valid) return -1;
    switch (e.type) {
    case 1:
        return (data[e.idx] >> e.shift) & 1 ? 0 : 1;
    case 8:
        v = data[e.idx] >> e.shift;
        if (e.shift) {
            e.idx++;
            v |= data[e.idx] << (8 - e.shift);
        }
        return v;
    }
    return -1;
}
