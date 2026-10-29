/* dkmovie.x func_00f23ae8: draft (session 141, round 28), structurally complete, not polished, 2652 vs 2776 bytes, 592 words differ, score 675 (m2c output unusable). The decode task: waits for ready slots, lays out the IPU buffers after f3DF08 (a guard word 0x12345678 at f3DD14), then walks each ready slot's packets: type 4 audio goes to func_00f21910 / func_00f21a20, type 3 pictures are fed through the IPU (BDEC/IDEC commands on 0x10002000, output via func_00f23aa8 in chunks of up to 0x3FF macroblocks) and shown (func_00f22df8). Stops on flag 8 or after f3DF1C frames, then idles setting 0x40000. Labels follow the m2c control flow. Round 19 (wwm1): score 675 -> 629 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
#include "../nonmatchings/session141/dkmovie/movie_work.h"

void FlushCache(s32);
void sceGsSyncPath(s32, s32);
void sceIpuInit(void);
void sceIpuSync(s32, s32);
void func_001eda90(s32, s32);
void func_0024b1e8(void *, void *, s32);
void func_0024e468(s32);
void func_0024e6e8(s32, s32);
void func_00f207a0(MovieWork *);
void func_00f208b8(MovieWork *);
void func_00f216d0(MovieWork *);
void func_00f21910(u8 *, MovieWork *);
void func_00f21a20(u8 *, MovieWork *);
void func_00f22df8(s32);
void func_00f22e28(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f230c0(s32, s32, s32);
void func_00f23480(void);
void func_00f23a78(s32);
void func_00f23aa8(s32, s32);
void func_00f23ae0(void); CONTEXT_ONLY void func_00f23ae0() {}
extern s32 D_00F283C8;
extern u8 D_00F28568[];
extern u8 D_00F28580[];

void func_00f23ae8(void) {
    s32 len, dst;
    s32 i, cnt, f;
    u8 *p;
    s32 w, ht, mbw, sz, buf0, buf1, buf2;
    s32 frame, slot, shown;
    u32 nmb, c;
    MovieWork *m;
    s32 cw, ch;

    func_00f207a0(D_00F28460);
    for (;;) {
        cnt = 0;
        for (i = 0; i < D_00F28460->f3DF50; i++) {
            if (D_00F28460->f3DD74[i] == 2) {
                cnt++;
            }
        }
        if ((cnt > 0 && D_00F28460->f3DD48 < 0) || cnt >= D_00F28460->f3DF50 || (D_00F28460->f3DDD0 & 8)) {
            break;
        }
        func_00f23480();
    }
    f = D_00F28460->f3DDD0 | 0x200;
    D_00F28460->f3DDD0 = f;
    if (f & 0x100) {
        while (!(D_00F28460->f3DDD0 & 8)) {
            func_00f23480();
            if (!(D_00F28460->f3DDD0 & 0x100)) {
                break;
            }
        }
    }
    m = D_00F28460;
    m->f3DD98 = (s32)m->pic[1];
    m->f3DD94 = (s32)m->pic[0];
    m->f3DD9C = (s32)m->f1E900;
    m->f3DF68 = 0;
    m->f3DDA0 = (s32)m->f24D00;
    D_00F28460->f3DF69 = 0;
    D_00F28460->f3DF6A = 0;
    D_00F28460->f3DF6B = 0;
    m = D_00F28460;
    w = m->f3DD20;
    ht = m->f3DD24;
    m->f3DDA4 = 0;
    buf0 = (m->f3DF08 + 0x3F) & ~0x3F;
    m->f3DDAC = (s32)m->aux[0];
    mbw = w / 16;
    cw = w;
    ch = ht;
    sz = mbw * (ht / 16) * 24 + 0x28;
    buf1 = (buf0 + (sz + 0x3F) / 64 * 256 + 0x3F) & ~0x3F;
    buf2 = (buf1 + mbw * ((ht + 15) / 16) * 1024 + 0x3F) & ~0x3F;
    m->f3DDA8 = 0;
    *(s32 *)(buf2 + 0x40) = 0x12345678;
    m->f3DD14 = buf2 + 0x40;
    if ((u32)(D_00F28460->f3DD14 + 4) >= (u32)((s32)D_00F28460 + D_00F28460->f3DF48)) {
        __asm__ volatile("break");
    }
    sceGsSyncPath(0, 0);
    shown = 0;
    sceIpuInit();
    func_00f22e28(buf0, buf1, 0x400, w, ht, 0x1180, 0, D_00F28460->f3DF61, D_00F28460->f3DEF0);
    frame = 0;
    slot = 0;
next_slot:
    D_00F283C8 = 0;
    if (D_00F28460->f3DD74[slot] != 2) {
        D_00F283C8 = 1;
        func_00f208b8(D_00F28460);
        D_00F28460->f3DF34 = 0;
        D_00F28460->f3DF40 = 0;
        for (;;) {
            cnt = 0;
            for (i = 0; i < D_00F28460->f3DF50; i++) {
                if (D_00F28460->f3DD74[i] == 2) {
                    cnt++;
                }
            }
            if (cnt > 0) {
                break;
            }
            if (shown) {
                func_00f23ae0();
                func_00f22df8(buf0);
            }
            if (D_00F28460->f3DDD0 & 8) {
                goto end;
            }
            func_00f23480();
        }
    }
    if (D_00F28460->f3DDD0 & 8) {
        goto end;
    }
    p = (u8 *)D_00F28460->f3DD84[slot];
    D_00F283C8 = 0;
next_packet:
    while (p[0] != 3) {
        if (p[0] == 4) {
            switch (p[8]) {
            case 1:
                break;
            default:
                func_00f21910(p + 0x10, D_00F28460);
                break;
            case 2:
                func_00f21a20(p + 0x10, D_00F28460);
                break;
            }
            p = p + 0x10 + *(s16 *)(p + 4);
        }
    }
    if (*(s16 *)(p + 4) != cw || *(s16 *)(p + 6) != ch) {
        ch = *(s16 *)(p + 6);
        cw = *(s16 *)(p + 4);
        func_00f22e28(buf0, buf1, 0x400, cw, ch, 0x1180, 0, D_00F28460->f3DF61, D_00F28460->f3DEF0);
    }
    len = *(s32 *)(p + 8);
    sceGsSyncPath(0, 0);
    func_00f230c0(buf2, (s32)(p + 0x10), len + 0x10);
    FlushCache(0);
    IPU_CTRL = 0x40000000;
    sceIpuSync(0, 0);
    IPU_CMD = 0;
    sceIpuSync(0, 0);
    dst = buf1;
    IPU_CTRL = *(s32 *)(p + 0xC);
    func_00f23a78(buf2);
    sceIpuSync(0, 0);
    IPU_CMD = 0x40000000;
    sceIpuSync(0, 0);
    IPU_CTRL = *(s32 *)(p + 0xC);
    nmb = mbw * (ht / 16);
    IPU_CMD = (p[2] << 24) | 0x10010000;
    while (nmb != 0) {
        c = nmb < 0x400 ? nmb : 0x3FF;
        func_00f23aa8(dst, c);
        while ((D3_CHCR >> 8) & 1) {
        }
        nmb -= c;
        dst += c << 10;
    }
    sceIpuSync(0, 0);
    FlushCache(0);
    if (D_00F28460->f3DF61 == 0) {
        FlushCache(0);
        func_0024e6e8(buf1, w * ht);
    }
    p = p + 0x10 + len;
    FlushCache(0);
    shown = 1;
    func_00f23ae0();
    func_00f22df8(buf0);
    sceGsSyncPath(0, 0);
    func_00f216d0(D_00F28460);
    m = D_00F28460;
    m->f3DD2C = frame;
    if (m->f3DF67 == 0 && frame == m->f3DF1C - 30) {
        func_001eda90(0, 0xEF);
        D_00F28460->f3DF67 = 1;
    }
    frame++;
    D_00F28460->f3DDD0 |= 4;
    func_00f23480();
    m = D_00F28460;
    if (m->f3DD50[slot] < frame) {
        m->f3DD74[slot] = 0;
    } else {
        if (m->f3DDD0 & 0x40) {
            func_00f208b8(m);
            D_00F28460->f3DF34 = 0;
            D_00F28460->f3DF40 = 0;
            f = D_00F28460->f3DDD0;
            while (!(f & 8) && (f & 0x40)) {
                func_00f23ae0();
                func_00f22df8(buf0);
                func_00f23480();
                f = D_00F28460->f3DDD0;
            }
            if (f & 8) {
                goto done_slot;
            }
        }
        if (!(m->f3DDD0 & 8)) {
            goto next_packet;
        }
    }
done_slot:
    slot = (slot + 1) % D_00F28460->f3DF50;
    if (!(D_00F28460->f3DDD0 & 8) && frame < D_00F28460->f3DF1C) {
        goto next_slot;
    }
end:
    IPU_CTRL = 0x40000000;
    sceIpuSync(0, 0);
    func_00f208b8(D_00F28460);
    if (*(s32 *)D_00F28460->f3DD14 != 0x12345678) {
        func_0024b1e8(D_00F28568, D_00F28580, 0x36B);
    }
    D_00F28460->f3DDD0 |= 0x8000;
    for (;;) {
        func_0024e468(1);
        D_00F28460->f3DDD0 |= 0x40000;
    }
}
