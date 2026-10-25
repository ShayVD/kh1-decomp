/* host/port/canvas.c, the 2D canvas map and the full-screen rules (include/platform/canvas.h,
 * docs/renderer-spec.md 5.3 step 1 and 5.4 "Session 93"), on made-up values: tests/selftest.sh builds
 * it with gcc -m32 when that works. */
#include "common.h"
#include "platform/canvas.h"

int printf(const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("canvas_test: %s\n", name); fails++; } } while (0)

static int near(f32 a, f32 b) { return a - b < 0.01f && b - a < 0.01f; }

int main(void) {
    KH1Canvas c;
    f32 x, y;
    s32 x0, x1, k, prev;

    /* the Vita: 4:3 canvas at 725.3 x 544, pillarboxed by 117.3; the view -1325 .. 9517 sixteenths */
    kh1_canvas_fit(&c, 960.0f, 544.0f);
    CHECK("vita: scale", near(c.s, 544.0f / 384.0f));
    CHECK("vita: offset", near(c.ox, (960.0f - 512.0f * 544.0f / 384.0f) / 2.0f) && near(c.oy, 0.0f));
    CHECK("vita: view", c.vx0 == -1325 && c.vw == 10842);
    kh1_canvas_map(&c, 0x7000, 0x7400, &x, &y);
    CHECK("vita: canvas top left", near(x, c.ox) && near(y, 0.0f));
    kh1_canvas_map(&c, 0x9000, 0x8C00, &x, &y);
    CHECK("vita: canvas bottom right", near(x, 960.0f - c.ox) && near(y, 544.0f));
    kh1_canvas_map(&c, 0x7000 + 256 * 16, 0x7400 + 192 * 16, &x, &y);
    CHECK("vita: centre", near(x, 480.0f) && near(y, 272.0f));
    /* the view's edges are the screen's (to a sixteenth's rounding) */
    kh1_canvas_map(&c, 0x7000 + c.vx0, 0x7400, &x, &y);
    CHECK("vita: view left = screen 0", x > -0.1f && x < 0.1f);
    kh1_canvas_map(&c, 0x7000 + c.vx0 + c.vw, 0x7400, &x, &y);
    CHECK("vita: view right = screen 960", x > 959.9f && x < 960.1f);

    /* a 4:3 screen: no bars, the view the canvas */
    kh1_canvas_fit(&c, 640.0f, 480.0f);
    CHECK("4:3: scale, no bars, view", near(c.s, 1.25f) && near(c.ox, 0.0f) && near(c.oy, 0.0f) && c.vx0 == 0 &&
          c.vw == 8192);
    /* narrower than 4:3: scaled to the width, letterboxed */
    kh1_canvas_fit(&c, 512.0f, 512.0f);
    CHECK("square: letterbox", near(c.s, 1.0f) && near(c.ox, 0.0f) && near(c.oy, 64.0f) && c.vw == 8192);

    /* the stretch: identity at 4:3; the canvas's edges to the view's; a point left of 0 rounds down */
    CHECK("stretch: 4:3 identity", kh1_canvas_stretch_x(0x7000, 0, 8192) == 0x7000 &&
          kh1_canvas_stretch_x(0x8234, 0, 8192) == 0x8234 && kh1_canvas_stretch_u(0x2008, 8192) == 0x2008);
    CHECK("stretch: left edge", kh1_canvas_stretch_x(0x7000, -1325, 10842) == 0x7000 - 1325);
    CHECK("stretch: right edge", kh1_canvas_stretch_x(0x9000, -1325, 10842) == 0x7000 + 9517);
    CHECK("stretch: centre stays", kh1_canvas_stretch_x(0x8000, -1325, 10842) == 0x8000);
    /* 1790.5 (the copy into the Z area): -1.5 px x 1.3235 = -1.985 px = -31.76 sixteenths -> -32 */
    CHECK("stretch: left of the canvas", kh1_canvas_stretch_x(0x7000 - 24, -1325, 10842) == 0x7000 - 1325 - 32);
    CHECK("stretch: u", kh1_canvas_stretch_u(0x2000, 10842) == 10842 && kh1_canvas_stretch_u(0, 10842) == 0 &&
          kh1_canvas_stretch_u(8, 10842) == 11);

    /* the scissor rule: the full canvas is the view, a column the view's column; others their own */
    CHECK("scissor: full", kh1_canvas_scissor(0x01FF0000, 0x017F0000, -1325, 10842, &x0, &x1) == 1 &&
          x0 == -1325 && x1 == 9517);
    CHECK("scissor: full at 4:3", kh1_canvas_scissor(0x01FF0000, 0x017F0000, 0, 8192, &x0, &x1) == 1 &&
          x0 == 0 && x1 == 8192);
    CHECK("scissor: the display's full", kh1_canvas_scissor(0x01FF0000, 0x01BF0000, -1325, 10842, &x0, &x1) == 1 &&
          x0 == -1325 && x1 == 9517);
    CHECK("scissor: no column on the display", kh1_canvas_scissor(0x003F0020, 0x01BF0000, -1325, 10842, &x0, &x1) == 0);
    prev = -1325;
    for (k = 0; k < 16; k++) { /* the 16 columns tile the view without gaps */
        u32 lo = (u32)(k * 32) | (u32)(k * 32 + 31) << 16;
        if (kh1_canvas_scissor(lo, 0x017F0000, -1325, 10842, &x0, &x1) != 1 || x0 != prev || x1 <= x0) break;
        prev = x1;
    }
    CHECK("scissor: columns tile the view", k == 16 && prev == 9517);
    CHECK("scissor: column 1", kh1_canvas_scissor(0x003F0020, 0x017F0000, -1325, 10842, &x0, &x1) == 1 &&
          x0 == -1325 + 678 && x1 == -1325 + 1355);
    CHECK("scissor: a window", kh1_canvas_scissor(0x00FF0010, 0x017F0000, -1325, 10842, &x0, &x1) == 0 &&
          x0 == 16 * 16 && x1 == 256 * 16);
    CHECK("scissor: not the full height", kh1_canvas_scissor(0x01FF0000, 0x00BF0000, -1325, 10842, &x0, &x1) == 0 &&
          x0 == 0 && x1 == 8192);
    CHECK("scissor: an odd column", kh1_canvas_scissor(0x003F0010, 0x017F0000, -1325, 10842, &x0, &x1) == 0);

    if (fails) { printf("canvas_test: %d of %d failed\n", fails, checks); return 1; }
    printf("canvas_test: PASS (%d checks)\n", checks);
    return 0;
}
