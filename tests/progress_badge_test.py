#!/usr/bin/env python3
"""Self-test for tools/progress_badge.py on synthetic source and on the tree (no game data).

  python3 -I tests/progress_badge_test.py
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import progress_badge as P  # noqa: E402

SOURCE = """
/* func_00000001(void) { in a comment } */
void func_00000002(void);
void func_00000003(void); CONTEXT_ONLY void func_00000003() {}
const char *s = "func_00000004(void) {";
#if 0
void func_00000005(void) {}
#else
void func_00000006(void) { func_00000002(); }
#endif
#ifdef KH1_THING
s32 func_00000007(s32 a) {
    return func_00000008(a);
}
#endif
void (*tbl[])(void) = { func_00000002 };
s32 D_00000009 = func_0000000a(1) ? 1 : 2; struct S { s32 (*func_0000000b)(void); };
"""


def main() -> int:
    got = P.c_definitions(SOURCE)
    want = {"func_00000006", "func_00000007"}
    assert got == want, sorted(got)
    assert P.percent(99999, 100000) == 99.99  # never rounded up to 100.00
    assert P.percent(0, 7) == 0.0

    # The tree: each layout parses, and the numbers are possible.
    elf, ovl = P.main_elf(), P.overlays()
    for t in (elf, ovl):
        assert 0 < t["matched"] <= t["funcs"] and 0 < t["matched_bytes"] <= t["bytes"], t
    svg = P.render([("Main ELF", elf), ("Overlays", ovl)])
    assert svg.startswith("<svg") and "Work in progress" in svg
    print("progress badge self-test: PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())
