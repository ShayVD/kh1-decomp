import os, re, sys
from pathlib import Path
ROOT = Path(sys.argv[1])
out = open(os.environ.get("S25_DIR", "/tmp/s25types") + "/drive2.out").read()
reasons = {}
for blk in re.split(r"\n(?=D_)", out):
    lines = blk.split("\n")
    m = re.match(r"(D_[0-9A-F]{8})\tNO", lines[0])
    if not m:
        continue
    N = m.group(1)
    if len(lines) < 2 or "no candidate" in lines[1]:
        reasons[N] = "session 25: no user declares a basic or header-reachable type to share"
        continue
    first = lines[1].strip()
    decl, _, rest = first.partition(": ")
    fails = re.findall(r"(src/\S+) (does not compile|code changes|new warning|no file-scope extern|not understood)", rest)
    kinds = {}
    for f, k in fails:
        kinds.setdefault(k, []).append(Path(f).name)
    parts = [f"{k} in {', '.join(v[:2])}{' +' + str(len(v) - 2) if len(v) > 2 else ''}" for k, v in kinds.items()]
    if "address of an array user" in rest:
        parts.append("an auto user takes the address of its array")
    reasons[N] = f"session 25: as {decl}: " + "; ".join(parts) if parts else f"session 25: as {decl}: {rest[:80]}"
n = 0
for mod in sorted((ROOT / "src/data").glob("data_*.s")):
    st = mod.read_text()
    def rep(m):
        global n
        N = m.group(2)
        if N not in reasons or "session 25" in m.group(3):
            return m.group(0)
        n += 1
        return f"{m.group(1)}{m.group(3)}; {reasons[N].replace('*/', '* /')} */"
    st2 = re.sub(r"(PIECE(?:_BEGIN)?\s+(D_[0-9A-F]{8}),[^/\n]*/\* )(untyped: users disagree[^\n]*?) \*/", rep, st)
    if st2 != st:
        mod.write_text(st2)
print("annotated", n, "of", len(reasons))
