/* Round 47 wwm2: score 62 -> 54, hill3o statement order. Earlier header below. */
/* score 62 (1360 bytes, same size). Builds a 128-byte option flag block: clear with p = f + 127 counting down, fields from func_00f2ac38(func_00f2ab98(n)), three 2/3/4 switches (case 4 falls into case 2) and bit tests of options 34..38. Left: in the case 4 -> case 2 fallthrough ours keeps an extra li v0,5 and the switch trees differ slightly; f[a] = 5; f[b] = 5 inside case 4 is worse. Round 27 wwm2. */
s32 func_00f2ab98(s32);
s8 func_00f2ac38(s32);

void func_00f2ac98(u8 *f)
{
    s32 i;
    u8 *p;
    s32 v;

    p = f + 127;
    for (i = 127; i >= 0; i--) {
        *p-- = 0;
    }
    f[2] = 1;
    f[3] = func_00f2ac38(func_00f2ab98(0));
    f[5] = func_00f2ac38(func_00f2ab98(3));
    f[8] = func_00f2ac38(func_00f2ab98(4));
    f[9] = func_00f2ac38(func_00f2ab98(6));
    f[10] = func_00f2ac38(func_00f2ab98(5));
    f[11] = func_00f2ac38(func_00f2ab98(2));
    f[15] = func_00f2ac38(func_00f2ab98(8));
    f[16] = func_00f2ac38(func_00f2ab98(9));
    f[4] = func_00f2ac38(func_00f2ab98(1));
    v = func_00f2ab98(7);
    f[13] = 0;
    f[27] = 0;
    f[13] = func_00f2ac38(v);
    v = func_00f2ab98(10);
    f[17] = 0;
    f[18] = 0;
    switch (v) {
        break;
    case 2:
        f[17] = 5;
        break;
    case 3:
        f[18] = 5;
    }
    v = func_00f2ab98(11);
    f[19] = 0;
    f[20] = 0;
    switch (v) {
    case 2:
        f[19] = 5;
        break;
    case 3:
        f[20] = 5;
        break;
    }
    v = func_00f2ab98(12);
    f[21] = 0;
    f[22] = 0;
    switch (v) {
    case 3:
        f[22] = 5;
        break;
        break;
    case 4:
    case 2:
        f[21] = 5;
        f[22] = 5;
    }
    v = func_00f2ab98(13);
    f[23] = 0;
    f[24] = 0;
    switch (v) {
    case 3:
        f[24] = 5;
        break;
    case 4:
        f[24] = 5;
    case 2:
        f[23] = 5;
        break;
    }
    v = func_00f2ab98(14);
    f[25] = 0;
    f[26] = 0;
    switch (v) {
    case 3:
        f[26] = 5;
        break;
        break;
    case 4:
        f[26] = 5;
    case 2:
        f[25] = 5;
    }
    v = func_00f2ab98(34);
    if (v & 0x80) f[30] = 1;
    if (v & 0x40) f[31] = 1;
    if (v & 0x20) f[32] = 1;
    if (v & 0x10) f[33] = 1;
    if (v & 8) f[34] = 1;
    if (v & 4) f[35] = 1;
    if (v & 2) f[36] = 1;
    if (v & 1) f[37] = 1;
    v = func_00f2ab98(35);
    if (v & 0x80) f[38] = 1;
    if (v & 0x40) f[39] = 1;
    if (v & 0x20) f[40] = 1;
    if (v & 0x10) f[41] = 1;
    if (v & 8) f[42] = 1;
    if (v & 4) f[43] = 1;
    if (v & 2) f[44] = 1;
    if (v & 1) f[45] = 1;
    v = func_00f2ab98(36);
    if (v & 0x80) f[46] = 1;
    if (v & 0x40) f[47] = 1;
    if (v & 0x20) f[48] = 1;
    if (v & 0x10) f[49] = 1;
    if (v & 8) f[50] = 1;
    if (v & 4) f[51] = 1;
    if (v & 2) f[52] = 1;
    if (v & 1) f[53] = 1;
    v = func_00f2ab98(37);
    if (v & 0x80) f[54] = 1;
    if (v & 0x40) f[55] = 1;
    if (v & 0x20) f[56] = 1;
    if (v & 0x10) f[57] = 1;
    if (v & 8) f[58] = 1;
    if (v & 4) f[59] = 1;
    if (v & 1) f[61] = 1;
    if (v & 2) f[60] = 1;
    v = func_00f2ab98(38);
    if (v & 0x80) f[62] = 1;
    if (v & 0x40) f[63] = 1;
    if (v & 0x20) f[64] = 1;
}
