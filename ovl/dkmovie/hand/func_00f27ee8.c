/* dkmovie.x func_00f27ee8: matched by hand. */
#include "ovl.h"

typedef struct MovieWork {
    u8 pad[0x3DD00];
    s32 f3DD00;
    s32 f3DD04;
    s32 f3DD08;
    s32 f3DD0C;
    s32 f3DD10;
    s32 f3DD14;
    s32 f3DD18;
    s32 f3DD1C;
    s32 f3DD20;
    s32 f3DD24;
    s32 f3DD28;
    s32 f3DD2C;
    s32 f3DD30;
    s32 f3DD34;
    s32 f3DD38;
    s32 f3DD3C;
    s32 f3DD40;
    s32 f3DD44;
    s32 f3DD48;
    s32 f3DD4C;
    s32 f3DD50;
    s32 f3DD54;
    s32 f3DD58;
    s32 f3DD5C;
    s32 f3DD60;
    s32 f3DD64;
    s32 f3DD68;
    s32 f3DD6C;
    s32 f3DD70;
    s32 f3DD74;
    s32 f3DD78;
    s32 f3DD7C;
    s32 f3DD80;
    s32 f3DD84;
    s32 f3DD88;
    s32 f3DD8C;
    s32 f3DD90;
    s32 f3DD94;
    s32 f3DD98;
    s32 f3DD9C;
    s32 f3DDA0;
    s32 f3DDA4;
    s32 f3DDA8;
    s32 f3DDAC;
    s32 f3DDB0;
    s8 f3DDB4; u8 p3DDB4[3];
    s32 f3DDB8;
    s8 f3DDBC; u8 p3DDBC[3];
    s32 f3DDC0;
    s32 f3DDC4;
    s32 f3DDC8;
    s32 f3DDCC;
    s32 f3DDD0;
    s8 f3DDD4[0x80];
    s8 f3DE54[0x80];
    s32 f3DED4;
    s32 f3DED8;
    s32 f3DEDC;
    s32 f3DEE0;
    s32 f3DEE4;
    s32 f3DEE8;
    s32 f3DEEC;
    s32 f3DEF0;
    s32 f3DEF4;
    s32 f3DEF8;
    s32 f3DEFC;
    s32 f3DF00;
    s32 f3DF04;
    s32 f3DF08;
    s32 f3DF0C;
    s32 f3DF10;
    s32 f3DF14;
    s32 f3DF18;
    s32 f3DF1C;
    s32 f3DF20;
    s32 f3DF24;
    s32 f3DF28;
    s32 f3DF2C;
    s32 f3DF30;
    s32 f3DF34;
    s32 f3DF38;
    s32 f3DF3C;
    s32 f3DF40;
    s32 f3DF44;
    s32 f3DF48;
    s32 f3DF4C;
    s8 f3DF50;
    s8 f3DF51;
    s8 f3DF52;
    s8 f3DF53;
    s8 f3DF54;
    s8 f3DF55;
    s8 f3DF56;
    s8 f3DF57;
    s8 f3DF58;
    s8 f3DF59;
    s8 f3DF5A;
    s8 f3DF5B;
    s8 f3DF5C;
    s8 f3DF5D;
    s8 f3DF5E;
    s8 f3DF5F;
    s8 f3DF60;
    s8 f3DF61;
    s8 f3DF62;
    s8 f3DF63;
    s8 f3DF64;
    s8 f3DF65;
    s8 f3DF66;
    s8 f3DF67;
    s8 f3DF68;
    s8 f3DF69;
    s8 f3DF6A;
    s8 f3DF6B;
} MovieWork;
s32 sceIoctl(s32, s32, void *);
void func_00f23480(void);
void func_00f208b8(MovieWork *);
void func_00f255f0(void);
void func_00f27678(void);
extern s32 D_00F283C8;
s32 func_00f27ee8(s32 arg0, MovieWork *w) {
    s32 st[4];
    s32 fd;
    s32 shown = 0;
    s32 started = 0;
    fd = w->f3DD48;
    D_00F283C8 = 0;
    if (fd < 0) {
        return 0;
    }
    while (sceIoctl(fd, 1, st), st[0] != 0) {
        if (shown == 0) {
            shown = 1;
            D_00F283C8 = 1;
        }
        func_00f23480();
        if (arg0 != 0) {
            if (started == 0) {
                started = 1;
                func_00f208b8(w);
            }
            func_00f255f0();
            func_00f27678();
        }
    }
    D_00F283C8 = 0;
    return 0;
}
