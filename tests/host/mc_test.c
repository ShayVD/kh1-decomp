/* host/port/mc_dir.c, the port's memory card, driven the way src/memcard/mcstep.c drives libmc
 * (each call, then PlatMcSync for its result) over a directory tests/host/ps2mc_test.py copies out
 * of a made-up card (argv[1]: BISLPS-25198-07/ with a 3,000-byte data file and a 60-byte system.bin).
 *
 *   nocard   port 2 (the game's 1) has no directory: GetInfo type 0 and "no card" (-10), as the
 *            null platform answered.
 *   info     port 1: a formatted PS2 card, -1 (new card) once, then 0.
 *   dir      the load screen's "BISLPS-25198-??" lists the save (name bytes 13 / 14 its number, the
 *            card's modified time), "*" at the root no "." / ".."; inside the save "*" lists "." and
 *            "..", then the two files with their sizes.
 *   read     the 60-byte head and the whole image read back; a missing file is -4.
 *   save     the save screen's sequence: Mkdir a new save (an existing one -4), create + write,
 *            write over (no truncate), Rename in its directory, Delete a file and the directory
 *            (not empty -6, then 0); Chdir to it and a relative open. */
#include <stdio.h>
#include <string.h>
#include "platform/mc.h"

extern const char *kh1_mc_root[2];

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("mc_test: %s\n", name); fails++; } } while (0)

static int sync(void) {
    int r = 12345;
    PlatMcSync(1, 0, &r);
    return r;
}

int main(int argc, char **argv) {
    unsigned char tbl[8][64], buf[4096];
    char cur[256];
    int type, freec, format, fd, i, n;
    kh1_mc_root[0] = argv[1];

    PlatMcGetInfo(1, 0, &type, &freec, &format);
    CHECK("nocard", sync() == -10 && type == 0 && format == 0);
    PlatMcGetInfo(0, 0, &type, &freec, &format);
    CHECK("info: new card", sync() == -1 && type == 2 && format == 1 && freec >= 132);
    PlatMcGetInfo(0, 0, &type, &freec, &format);
    CHECK("info: same card", sync() == 0);

    PlatMcGetDir(0, 0, "BISLPS-25198-??", 0, 8, tbl);
    n = sync();
    CHECK("dir: one save", n == 1 && strcmp((char *)tbl[0] + 0x20, "BISLPS-25198-07") == 0 &&
          tbl[0][0x20 + 13] == '0' && tbl[0][0x20 + 14] == '7');
    CHECK("dir: the card's time", tbl[0][8 + 7] * 256 + tbl[0][8 + 6] == 2004 && tbl[0][8 + 5] == 5 &&
          tbl[0][8 + 4] == 6 && tbl[0][8 + 3] == 7 && tbl[0][8 + 2] == 8 && tbl[0][8 + 1] == 9);
    PlatMcGetDir(0, 0, "*", 0, 8, tbl);
    CHECK("dir: root", sync() == 1);
    PlatMcGetDir(0, 0, "/BISLPS-25198-07/*", 0, 8, tbl);
    n = sync();
    CHECK("dir: a save's entries", n == 4 && strcmp((char *)tbl[0] + 0x20, ".") == 0 &&
          strcmp((char *)tbl[1] + 0x20, "..") == 0);
    for (i = 2; i < n; i++) {
        unsigned int size;
        memcpy(&size, tbl[i] + 0x10, 4);
        CHECK("dir: sizes", (strcmp((char *)tbl[i] + 0x20, "system.bin") == 0 && size == 60) ||
              (strcmp((char *)tbl[i] + 0x20, "BISLPS-25198-07") == 0 && size == 3000));
    }

    PlatMcOpen(0, 0, "/BISLPS-25198-07/system.bin", 1);
    fd = sync();
    CHECK("read: open", fd >= 0);
    PlatMcRead(fd, buf, 60);
    CHECK("read: head", sync() == 60 && buf[0] == 0x4B && buf[3] == 0x51 && buf[59] == 0x11);
    PlatMcClose(fd);
    CHECK("read: close", sync() == 0);
    PlatMcOpen(0, 0, "/BISLPS-25198-07/BISLPS-25198-07", 1);
    fd = sync();
    PlatMcRead(fd, buf, 3000);
    n = sync();
    for (i = 0; i < 3000 && buf[i] == ((i * 7) & 0xFF); i++);
    CHECK("read: image", n == 3000 && i == 3000);
    PlatMcClose(fd);
    sync();
    PlatMcOpen(0, 0, "/BISLPS-25198-08/system.bin", 1);
    CHECK("read: missing", sync() == -4);

    PlatMcMkdir(0, 0, "/BISLPS-25198-07");
    CHECK("save: mkdir over a save", sync() == -4);
    PlatMcMkdir(0, 0, "/BISLPS-25198-08");
    CHECK("save: mkdir", sync() == 0);
    PlatMcOpen(0, 0, "/BISLPS-25198-08/system.bin", 515);
    fd = sync();
    memset(buf, 0x22, 60);
    PlatMcWrite(fd, buf, 60);
    CHECK("save: write", fd >= 0 && sync() == 60);
    PlatMcClose(fd);
    sync();
    PlatMcOpen(0, 0, "/BISLPS-25198-08/system.bin", 2);
    fd = sync();
    memset(buf, 0x33, 4);
    PlatMcWrite(fd, buf, 4);
    sync();
    PlatMcClose(fd);
    sync();
    PlatMcChdir(0, 0, "/BISLPS-25198-08", cur);
    CHECK("save: chdir", sync() == 0 && strcmp(cur, "/") == 0);
    PlatMcOpen(0, 0, "system.bin", 1);
    fd = sync();
    memset(buf, 0, 64);
    PlatMcRead(fd, buf, 64);
    CHECK("save: over, not truncated", sync() == 60 && buf[3] == 0x33 && buf[4] == 0x22 && buf[59] == 0x22);
    PlatMcClose(fd);
    sync();
    PlatMcRename(0, 0, "system.bin", "system.old");
    CHECK("save: rename", sync() == 0);
    PlatMcChdir(0, 0, "..", cur);
    CHECK("save: chdir back", sync() == 0 && strcmp(cur, "/BISLPS-25198-08") == 0);
    PlatMcDelete(0, 0, "/BISLPS-25198-08");
    CHECK("save: delete not empty", sync() == -6);
    PlatMcDelete(0, 0, "/BISLPS-25198-08/system.bin");
    CHECK("save: delete renamed away", sync() == -4);
    PlatMcDelete(0, 0, "/BISLPS-25198-08/system.old");
    CHECK("save: delete file", sync() == 0);
    PlatMcDelete(0, 0, "/BISLPS-25198-08");
    CHECK("save: delete dir", sync() == 0);
    PlatMcGetDir(0, 0, "BISLPS-25198-??", 0, 8, tbl);
    CHECK("save: one save left", sync() == 1);

    printf("mc_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
