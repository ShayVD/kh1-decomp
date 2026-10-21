"""Shared helpers of the session 27 Phase 4 tools (compile one file with its objects.mk recipe)."""
import hashlib, json, os, re, subprocess, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
SCR = Path(os.environ.get("S27_DIR", "/tmp/s27types"))
SCR.mkdir(parents=True, exist_ok=True)
TOOLCHAIN = (ROOT / "tools/toolchain").resolve()

_recipes = None


def recipes():
    global _recipes
    if _recipes is None:
        _recipes = {}
        cur = None
        for ln in (ROOT / "out/gen/objects.mk").read_text().splitlines():
            m = re.match(r"out/build/(src/\S+\.c)\.o:", ln)
            if m:
                cur = m.group(1)
            elif cur and "-S -x c" in ln:
                _recipes[cur] = ln.strip().lstrip("@").split(" && ")[0]
                cur = None
    return _recipes


def compile_s(rel, text=None, root=ROOT):
    """(asm or None, [(line, message)]) of src file `rel` (text: its content, default the file)
    compiled with its recipe in tree `root`."""
    cmd = recipes().get(rel)
    if cmd is None and rel.endswith(".h"):  # a header compiled as C: any C file's recipe
        k, c = next(iter(sorted(recipes().items())))
        cmd = c.replace(" " + k, " " + rel)
    src = Path(root) / rel
    with tempfile.TemporaryDirectory(dir=SCR) as td:
        if text is not None:
            tmp = src.with_name(".s27tmp_" + src.name)
            tmp.write_text(text)
            name = str(tmp.relative_to(root))
        else:
            tmp, name = None, rel
        try:
            c = cmd.replace("$(TOOLCHAIN)", str(TOOLCHAIN)).replace("$(INCLUDES)", "-Iinclude -Isrc")
            c = c.replace("$(@:.o=.s)", f"{td}/o.s").replace(" " + rel, " " + name)
            r = subprocess.run(c, shell=True, cwd=root, capture_output=True, text=True)
            asm = Path(td, "o.s").read_text() if r.returncode == 0 else None
            if asm is not None and tmp is not None:
                asm = asm.replace(tmp.name, src.name)
        finally:
            if tmp is not None:
                tmp.unlink()
    diags = []
    for ln in r.stderr.replace(".s27tmp_", "").splitlines():
        m = re.match(r"^([^:]+):(\d+): (.*)$", ln)
        if m:
            diags.append((int(m.group(2)) if m.group(1).endswith(src.name) else 0, m.group(3)))
        elif ln.strip() and not ln.startswith("In file included") and not ln.strip().startswith("from "):
            diags.append((0, ln.strip()))
    return asm, diags


def canon_labels(asm):
    seen = {}

    def rep(m):
        k = m.group(0)
        if k not in seen:
            seen[k] = f"{m.group(1)}#{len([x for x in seen if x.startswith(m.group(1))])}"
        return seen[k]
    return re.sub(r"(\$LC?|\$LF)\d+", rep, asm)


def same_asm(a, b):
    if a == b:
        return True
    if a is None or b is None or os.environ.get("S27_STRICT") == "1":
        return False
    return canon_labels(a) == canon_labels(b)


def warnings(diags):
    """the diagnostics as a set of messages without line numbers"""
    return set(m for _, m in diags)


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True).stdout


_head_lock = __import__("threading").Lock()


def head_tree():
    """an export of HEAD's src/ and include/ (refreshed when HEAD moves)"""
    with _head_lock:
        return _head_tree()


def _head_tree():
    sha = git("rev-parse", "HEAD").strip()
    d = SCR / "head"
    stamp = d / ".sha"
    if not stamp.exists() or stamp.read_text() != sha:
        subprocess.run(["rm", "-rf", str(d)])
        d.mkdir(parents=True)
        (SCR / "cache").mkdir(exist_ok=True)
        p = subprocess.Popen(["git", "archive", "HEAD", "src", "include", "kh1.toml"], cwd=ROOT,
                             stdout=subprocess.PIPE)
        subprocess.run(["tar", "-x", "-C", str(d)], stdin=p.stdout, check=True)
        p.wait()
        stamp.write_text(sha)
    return d, sha


def head_compile(rel):
    d, sha = head_tree()
    key = SCR / "cache" / (hashlib.sha1((sha + rel + recipes()[rel]).encode()).hexdigest() + ".json")
    key.parent.mkdir(exist_ok=True)
    if key.exists():
        j = json.loads(key.read_text())
        return j["asm"], [tuple(x) for x in j["diags"]]
    asm, diags = compile_s(rel, None, root=d)
    key.write_text(json.dumps(dict(asm=asm, diags=diags)))
    return asm, diags
