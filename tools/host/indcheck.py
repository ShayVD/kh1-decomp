#!/usr/bin/env python3
"""Checks of the game's C that need its syntax tree (phase 5, docs/vita-port-plan.md
5.1e; portability.md rules 10 and 11). Asks clang for the tree of every game file
(and every draft of shift/drafts.tsv) with the host census's flags.

Calls through pointers (rule 10). argcheck.py reads direct calls in the text; a
call through a pointer (a table, a struct field, a local loaded from either) has
no name to look up, and on the EE `fn()` still hands the target the caller's
a0-a3 (func_0013e558's class handler call, session 64). For each call whose
callee is not a function name after casts this lists the arguments it passes
and what its callee expression reads, and finds the targets in:

- data tables: the `.word` entries of src/data/*.s pieces, C initializers, and
  for `.incbin` pieces the user's ELF (an indexed array: its words from the
  start while they are functions or 0);
- functions assigned to data or to a struct field (`Record.field`), and
  functions passed as arguments, followed through setters and parameters to a
  fixpoint (`@func#i` is function func's parameter i);
- a local, through what the same function assigns to it (a function, a local
  table's initializer, or a field it was loaded from);
- tables of records a setter fills (RECORD_SETTERS: the actor class table of
  func_0014f830, the party's timed callbacks) and static record tables in the ELF
  (RECORD_TABLES: ppp's classes), by the offset of the field the call reads, from
  the records' real layout (Layout: gcc's -m32 -malign-double rules);
- a field under another typedef's name: by offset when the field's name spells it
  (O15.f408 and O16.x408 meet at ~@0x408, from 0x40 up), or as listed in FIELD_SAME.

Verdicts: SHORT (a known target takes more than the call passes), SHORT? (the
same, found only through a struct field), OK, ?def (targets known, none defined
in C or read into ASM_TAKES, the assembly / SDK functions' parameters), ? (none found; its note may give a lead: the functions the ELF's code
stores at the same offset of any struct), and from the table below (read by
hand): READ, OVERLAY, DATA (a pointer from a file loaded at run time: look in a
host run on the real disc) and OPEN (read, not traced to the end). A note never
hides a SHORT.

    python3 -I tools/host/indcheck.py --takes NAME...

prints, for reading by hand, how many parameters each function takes, and the
functions a data name, a field (Record.field) or a parameter (@func#i) holds.

Argument classes (rule 11): every declaration a file sees (headers, struct
typedefs, `()` declarations, block-scope externs) and every m2c cast at a call,
against the definition (ABI rows), and every f32 an unprototyped call promotes
to double where the definition takes f32 (PROMO rows). CLANG rows are clang's
errors: a builtin called with fewer arguments than it takes, or a file clang
cannot parse (gcc nested functions), whose calls are not listed; such a file
whose host object (gcc) has no `call *` is CLANG-READ (session 69).

    python3 -I tools/host/indcheck.py [--all] [--tsv out/host/indcheck.tsv]

prints the rows to act on (SHORT, SHORT?, ABI, PROMO, CLANG), with --all every
row. A heuristic: a call through a table can reach any entry (the index is not
read); check each hit by hand. Needs clang (the census builds with gcc; the
syntax is the same).
"""
import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import argcheck  # noqa: E402

ROOT = argcheck.ROOT
CFLAGS = ["-m32", "-malign-double", "-std=gnu89", "-w", "-fno-strict-aliasing", "-DKH1_HOST",
          "-Iinclude", "-Isrc", "-Wno-error=implicit-function-declaration", "-Wno-error=int-conversion",
          "-Wno-error=incompatible-pointer-types", "-Wno-error=implicit-int", "-Wno-return-type", "-fsyntax-only",
          "-Xclang", "-ast-dump=json"]

# Indirect calls read by hand (file, caller): what they reach. READ means the targets
# take no more than the call passes (or the call was fixed); OVERLAY means only an
# overlay can set the pointer (no writer, or a setter with no caller, in the main ELF):
# check it against the overlay inventories (docs/vita-port-plan.md 5.2).
READ = {
    ("src/gfx/objwin.c", "func_0010ba98"):
        "READ: Win.cb at the close (state 5) passed nothing and a0 = a1 = the window on the EE; the "
        "close callbacks (func_0010bd90's, msgwin.c's func_001cae20(id, win)) read the window: the "
        "host passes (w, w) (session 65); the open call passes Fade's (cnt, arg)",
    ("src/game/summon.nostrict.c", "func_0013be00"):
        "READ: the steps come from D_00304B48 (func_0013bde8 copies it): func_0013b050, func_0013b3d0, "
        "func_0013b740, func_0013b8f0, all (void)",
    ("src/game/memberfile.c", "func_001330e8"):
        "READ: W32Chan.x18 is func_001331d8's cb (func_001d75a0, void)",
    ("src/game/objreq.nostrict.c", "func_00146998"):
        "READ: LdTask.cb / arg are func_00146a68's cb / arg; its cb targets take one argument",
    ("src/text/fldtext.c", "func_0010e430"):
        "READ: Fade.cb is func_0010ef70's third argument: msgwin.c's (id, win) callbacks and void ones",
    ("src/util/task.c", "func_001bffa0"):
        "OVERLAY: the task's fn is set only by func_001c06c0, which nothing in the main ELF calls",
    ("src/game/objreq.c", "func_001468b0"):
        "OVERLAY: x38 is set only by func_001468f8, which nothing in the main ELF calls",
    ("src/game/cmdmenu.nostrict.c", "func_0012d930"):
        "OVERLAY: D_00524F74 is set only by func_0012cab8, which nothing in the main ELF calls",
    ("src/game/summon.c", "func_0013ab08"):
        "OVERLAY: D_00304B6C is 0 in the ELF and src/ only clears it",
    ("src/gummi/gumisave.c", "func_001b9c10"):
        "OVERLAY: the gummi overlay's entry, called with nothing: on the EE a0 is still FlushCache's 2 "
        "(if the kernel keeps it) and a1 what func_001207f8 left; check what the entry reads",
    ("src/gummi/gumisave.c", "func_001b9c60"):
        "OVERLAY: the gummi overlay's entry, called with nothing: on the EE a0 is still FlushCache's 2 "
        "(if the kernel keeps it) and a1 = D_00F20000 (s0); check what the entry reads",
    ("src/sound/objse.c", "func_001570d0"):
        "READ (session 64): the +0x10 callback gets whatever func_001ecfd8 left in a0; no handler can rely on it",
    # session 66 (a key may name a field the call reads, or "*" for every caller in the file)
    ("src/ai/partyctl.nostrict.c", "*"):
        "READ: C03Act.cb comes from the action tables the eight setups store at w+0x1C (partyai.c: "
        "D_0035BD50 D_0035BE50 D_0035BFC0 D_0035C090 D_0035C140 D_0035C1F0 D_0035C2C0 D_0035C360) and "
        "D_0035BCB8: every handler takes 4 (--takes)",
    ("src/ai/partyctl.nostrict.c", "*", "C03AW.cb44"):
        "OVERLAY: w->cb44 (+0x44) is only cleared in src/ and no code of the main ELF stores a function there",
    ("src/ai/partyctl.nostrict.c", "*", "C03AW_6a3f8.cb44"):
        "OVERLAY: w->cb44 (+0x44) is only cleared in src/ and no code of the main ELF stores a function there",
    ("src/memcard/mcstep.c", "*"):
        "OVERLAY: the hook D_00648034 is the request's own (D_006477B0[].a[k], mcqueue.c's queue functions); "
        "every queue call in the main ELF passes 0",
    ("src/model/mdldraw.nostrict.c", "func_001606d0"):
        "READ: Prm25.x30 / x34 run only when x4 is set: objdraw.nostrict.c's S14 (fn1 func_00122770 3, fn2 "
        "func_001229c0 2); shadow.nostrict.c, partymdl.c and journalmdl.c leave x4 0",
    ("src/model/mdlgs.nostrict.c", "func_0015ff78"):
        "READ: B4Src2.x40 / x44 are the draw prm's x20 / x24 (func_001606d0): objdraw.nostrict.c's S14.fn "
        "(func_00135ed0 2, func_00175600 1) and its p; shadow.nostrict.c's 0",
    ("src/obj/atkhit.c", "func_0014aab0"):
        "READ: the attack record's xb4 is set by partyctl.nostrict.c (p->cb = func_00171f38, 2, the record "
        "l->p40 that class1c.nostrict.c passes here)",
    ("src/obj/objbone.c", "func_00131b50"):
        "READ: +0x17c is the actor's first motion entry (objmotion.c W6Ent, func_001302d0), its +0xC the "
        "callback func_00130578's callers store: func_00138948 func_00140fa8 func_001447a0 func_001580e8 "
        "func_0015ac30 func_0015d248 func_0015dac0 func_001731f8 func_001740e8 func_00174ad8, all 1",
    ("src/obj/plact.c", "func_001271b0"):
        "OVERLAY: D_002E27D4 is 0 in the ELF and the main ELF only clears it (func_00138400)",
    ("src/ppp/kethdraw.nostrict.c", "func_001a7718"):
        "READ: gcc nested functions (func_001a7600 ... func_001a72c8) that share their parent's frame; "
        "no arguments by design (clang cannot parse them)",
    ("src/ppp/pppcomp.c", "pppDrawHookDraw"):
        "OVERLAY: the hook table D_00616220 is 0 in the ELF and the main ELF only clears it (func_00182058)",
    ("src/ppp/pppsys.c", "func_001822f8"):
        "READ: PppSys.mods are &D_00370200[id] (func_00182c10 takes the words pppRelocProgram relocated) "
        "and fn10 (+0x10) is 0 in all 236 classes: the loop never calls",
    ("src/sound/objse.nostrict.c", "func_001571a8"):
        "READ: cb is always 0 (the only caller, func_00157400, passes 0)",
    ("src/sound/objse.c", "func_001573d8"):
        "READ: the task's +0x48 is func_00157400's cb (roomobj.nostrict.c's func_00132a78, 1); the +0x48 "
        "targets of other structs (the party AI's p48) do not reach it",
    ("src/game/memberfile.c", "func_00133550"):
        "READ: the task's +0x48 is func_00133578's cb (roomobj.nostrict.c's func_00132a78, 1); the +0x48 "
        "targets of other structs (the party AI's p48) do not reach it",
    ("src/gfx/light.c", "func_00122430"):
        "READ: the task's +0x48 is func_001224c8's third argument (partyctl.nostrict.c's func_00122768, 1; "
        "partyai.c's 0); the +0x48 targets of other structs (the party AI's p48) do not reach it",
    ("src/text/textwin.c", "func_001f8170"):
        "READ: TextWin.x8 is the descriptor's x4 (func_001f31a8 copies x0 to +4, x4 to +8): the descriptors "
        "of the 141 calls that pass a constant hold x4s that take 0 or 1 (37 calls pass a computed one)",
    ("src/text/textwin.c", "func_001f82b0", "TextWin.x4"):
        "READ: TextWin.x4 is the descriptor's x0 (func_001f31a8): the 137 functions the constant "
        "descriptors hold all take 1 (37 calls pass a computed descriptor)",
    ("src/text/textwin.c", "func_001f82b0", "TextWin.x0"):
        "OVERLAY: only func_001f4670 sets TextWin.x0 and nothing in the main ELF calls it",
    ("src/util/proc.c", "func_0011f228"):
        "OVERLAY: func_0011f228 has no caller in the main ELF",
    ("src/util/vmath.c", "func_001be7d8"):
        "OVERLAY: the stack's push (func_001be758, which sets cur) and func_001be7d8 have no caller in the "
        "main ELF",
    ("src/vm/stackvm.nostrict.c", "func_0013cfe8"):
        "READ: cb is always 0 (objscript.c's func_0012ba48 passes 0)",
    ("src/vm/stackvm.nostrict.c", "func_0013cfe8", "SVmNat.fn"):
        "READ: vm->nat is D_002E2F20 (objscript.c, n->f18): the native tables D_002E2810 (226) and "
        "D_00362340 (25) of {fn, n, fl}; every native takes `args` or nothing",
}
# Fields that are one field under other names (two typedefs of one struct read by hand),
# or a setter's parameter stored there: each gets the targets of all.
FIELD_SAME = [
    # the task pools of src/util/proc.c: func_0011f090(pool, prio, fn) stores fn at +0xC
    ("TNode.fn", "GsTask.cb", "Nea98.xc", "@func_0011f090#2"),
    ("T15.f14", "T16.f14"),          # objtask.nostrict.c: func_00138400's task, func_00137ea8's
    ("T155ef8.x18", "W9Task.x18"),   # objslot: func_001560f8's task, func_00155ef8's
    ("W34E32.x1c", "Ent9c.x1c"),     # memberitem: func_00149c80's cb, func_00149a88's
    # the choice list records: func_0010f558(range, win, start) stores range at the window's
    # +0xA8 (its text object's +0x28), which func_0010cd40 hands func_0010f368 as a Range52
    ("Range52.fn", "MsgCb.fn", "ListCb.fn", "ShopCb.fn", "Cb20.fn"),
]
# Tables of records a setter fills from its parameters: the setter, the table's start,
# record size and count, {field offset: the setter's parameter stored there}, and the
# data that point into the table (list heads). A call through a field of the table
# (D_X[i].field, a piece inside the table at offset 0, or p->field with p loaded from
# a list head) reaches what the setter's callers pass for that field.
RECORD_SETTERS = {
    # the actor class table (src/obj/actcore.c, func_0014f830(class, f0, ..., f1c)):
    # 0x3A + 1 records of {flags, enter, leave, ..., MvFn, StFn, ...}
    "func_0014f830": (0x00350D88, 0x20, 59, {4 * i: i + 1 for i in range(8)}, ()),
    # the party's timed callbacks (src/ai/partyai.c, func_00170f50(o, w, cb, mask, arg)):
    # 30 nodes {id, mask, cb, arg, next}, the active list D_00575780, free list D_00575784
    "func_00170f50": (0x00575528, 0x14, 30, {8: 2, 4: 3, 0xC: 4}, ("D_00575780", "D_00575784")),
}
# Static tables of records in the ELF that a call reaches through a struct field: the
# record type names the code gives them, the table's start, record size and count. The
# field's offset picks the word of every record.
RECORD_TABLES = {
    # ppp's class table (include/ppp.h): programs name &D_00370200[id] (pppRelocProgram)
    ("PppClass", "Cls"): (0x00370200, 0x28, 236),
}
VM_HOOKS = "OVERLAY: src/vm/vm_lib.c's hooks D_0037733C ... D_003773E8 are 0 in the ELF and nothing in src/ sets them"

# Parameters of call targets defined only in assembly or the SDK (no C definition to count),
# read by hand from the code: the argument registers each reads before it writes them
# (session 68). They count like a C definition's.
ASM_TAKES = {
    # FlushCache / iFlushCache (src/sdk/libkernl/syscall.s): `li v1,100 / 102; syscall`, the
    # kernel reads the mode in a0. PlatFlushCache / PlatIFlushCache are the host's (void (int)).
    "func_002583e0": 1,
    "iFlushCache": 1,
    "func_00258410": 1,
    "PlatFlushCache": 1,
    "PlatIFlushCache": 1,
    # sceVu0RotMatrixZ / X / Y (src/sdk/libvu0/vu0.s): out a0, in a1 (lqc2 0($a1)), the angle
    # in f12 (c.lt.s $f12 ...); a2 / a3 are written before they are read.
    "func_002676c0": 3,
    "func_00267768": 3,
    "func_00267810": 3,
    # SyncDCache(start, end) (src/sdk/libkernl/cache.c)
    "func_00258a58": 2,
}


def strip(n):
    """Skip casts and parentheses around an expression node."""
    while n.get("kind") in ("ImplicitCastExpr", "CStyleCastExpr", "ParenExpr") and n.get("inner"):
        n = n["inner"][0]
    return n


def m2c_off(e):
    """OFF of M2C_FIELD(p, T, OFF), *(T)((s8 *)p + OFF), else None."""
    e = strip(e)
    if e.get("kind") != "UnaryOperator" or e.get("opcode") != "*":
        return None
    e = strip(e["inner"][0])
    if e.get("kind") == "BinaryOperator" and e.get("opcode") == "+" \
            and strip(e["inner"][1]).get("kind") == "IntegerLiteral":
        return int(strip(e["inner"][1])["value"], 0)
    return None


def dname(name):
    """D_00525368_001330e8 (a file's own extern of D_00525368) -> D_00525368."""
    m = re.match(r"(D_[0-9A-Fa-f]{8})_\w+$", name)
    return m.group(1) if m else name


def member(n):
    """A MemberExpr as RecordType.field (the type its base points at), so that two
    structs' fields of one name stay apart."""
    t = ""
    if n.get("inner"):
        t = n["inner"][0].get("type", {}).get("qualType", "")
    t = re.sub(r"\b(struct|union|const|volatile)\b|\*|\[.*?\]", " ", t).split()
    return "%s.%s" % (t[0] if t else "?", n.get("name", "?"))


def tclass(t):
    """The argument class of a clang type node: i32, i64, f32, f64, q128, rec, void."""
    q = t.get("qualType", "")
    d = t.get("desugaredQualType", q)
    if "*" in d or "[" in d or "(" in d or "*" in q:
        return "i32"
    if "128" in q or "128" in d:
        return "q128"
    d = re.sub(r"\b(const|volatile|signed|unsigned)\b", " ", d).split()
    d = " ".join(d)
    d = {"f32": "float", "f64": "double", "s64": "long long", "u64": "long long"}.get(d, d)
    if d == "float":
        return "f32"
    if d in ("double", "long double"):
        return "f64"
    if d in ("long long", "long long int"):
        return "i64"
    if d.startswith(("struct ", "union ")):
        return "rec"
    if d == "void":
        return "void"
    return "i32"


def fsig(fd):
    """(return class, [parameter classes] or None when unprototyped, variadic) of a FunctionDecl."""
    t = fd.get("type", {})
    q = t.get("desugaredQualType", t.get("qualType", ""))
    m = re.match(r"(.*?)\s*\((.*)\)$", q)
    ret = tclass({"qualType": m.group(1)}) if m else "?"
    ps = [tclass(c.get("type", {})) for c in fd.get("inner", ()) if c.get("kind") == "ParmVarDecl"]
    proto = not (m and m.group(2).strip() == "" and not ps)
    return ret, (ps if proto else None), "..." in q


def split_top(s):
    out, depth, cur = [], 0, ""
    for c in s:
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        if c == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += c
    if cur.strip():
        out.append(cur.strip())
    return out


def castsig(t):
    """fsig of a cast to a function pointer type (m2c's `#define f ((T (*)(...)) f)`)."""
    q = t.get("desugaredQualType", t.get("qualType", ""))
    m = re.match(r"(.*?)\s*\(\*\)\s*\((.*)\)$", q)
    if not m:
        return None
    ps = split_top(m.group(2))
    var = "..." in ps
    ps = [x for x in ps if x != "..."]
    if ps == ["void"]:
        ps = []
    return tclass({"qualType": m.group(1)}), ([tclass({"qualType": x}) for x in ps] if ps or "void" in m.group(2) else None), var


BASIC = {"char": 1, "s8": 1, "u8": 1, "signed char": 1, "unsigned char": 1, "short": 2, "s16": 2, "u16": 2,
         "unsigned short": 2, "int": 4, "s32": 4, "u32": 4, "unsigned int": 4, "long": 4, "unsigned long": 4,
         "f32": 4, "float": 4, "M2C_UNK": 4, "s64": 8, "u64": 8, "f64": 8, "double": 8, "long long": 8,
         "unsigned long long": 8}


class Layout:
    """Field offsets of the records a file declares, laid out the way gcc lays out the
    -m32 -malign-double host (natural alignment; bit fields packed into units of their
    type). A field whose type this cannot size ends its record's offsets."""

    def __init__(self, tu):
        self.recs, self.tdefs, self.tnames, self.rnames = {}, {}, {}, {}
        self.offs, self.sizes = {}, {}
        self.scan(tu)

    def scan(self, n):
        k = n.get("kind")
        if k == "RecordDecl" and n.get("completeDefinition", True) and any(
                c.get("kind") == "FieldDecl" for c in n.get("inner", ())):
            self.recs[n["id"]] = n
            if n.get("name"):
                self.rnames["%s %s" % (n.get("tagUsed", "struct"), n["name"])] = n["id"]
        elif k == "TypedefDecl":
            tgt = []
            walk(n, lambda m: tgt.append(m["ownedTagDecl"]["id"]) if m.get("ownedTagDecl") else
                 tgt.append(m["decl"]["id"]) if m.get("kind") == "RecordType" and m.get("decl") else None)
            self.tdefs[n["id"]] = ("rec", tgt[0]) if tgt else ("type", n.get("type", {}))
            self.tnames[n["name"]] = n["id"]
        for c in n.get("inner", ()):
            if isinstance(c, dict):
                self.scan(c)

    def tsize(self, t, prev=None, depth=0):
        """(size, alignment) of a clang type node, or None."""
        if depth > 20:
            return None
        q = re.sub(r"\b(const|volatile)\b", " ", t.get("qualType", "")).strip()
        q = " ".join(q.split())
        m = re.match(r"(.*?)\s*\[(\d+)\]$", q)
        if m:
            e = self.tsize({"qualType": m.group(1)}, prev, depth + 1)
            return (e[0] * int(m.group(2)), e[1]) if e else None
        if "*" in q or "(" in q and "unnamed" not in q:
            return 4, 4
        if q in BASIC:
            return BASIC[q], BASIC[q]
        if "unnamed" in q:
            return self.rsize(prev["id"], depth + 1) if prev is not None and prev.get("kind") == "RecordDecl" else None
        tid = t.get("typeAliasDeclId") or self.tnames.get(q)
        if tid in self.tdefs:
            kind, v = self.tdefs[tid]
            return self.rsize(v, depth + 1) if kind == "rec" else self.tsize(v, None, depth + 1)
        if q in self.rnames:
            return self.rsize(self.rnames[q], depth + 1)
        return None

    def rsize(self, rid, depth=0):
        if rid in self.sizes:
            return self.sizes[rid]
        n = self.recs.get(rid)
        if n is None or depth > 20:
            return None
        self.sizes[rid] = None  # a record that contains itself (through no pointer) has no size
        union = n.get("tagUsed") == "union"
        bit, size, align, prev = 0, 0, 1, None
        for c in n.get("inner", ()):
            if c.get("kind") != "FieldDecl":
                prev = c
                continue
            z = self.tsize(c.get("type", {}), prev, depth)
            prev = c
            if z is None:
                return None
            align = max(align, z[1])
            if union:
                self.offs[c["id"]] = 0
                size = max(size, z[0])
                continue
            if c.get("isBitfield"):
                w = None
                for v in c.get("inner", ()):
                    w = v.get("value") or (v.get("inner") or [{}])[0].get("value")
                w = int(w) if w is not None else z[0] * 8
                unit = z[0] * 8
                if w == 0 or (bit % unit) + w > unit:
                    bit = (bit + unit - 1) // unit * unit
                self.offs[c["id"]] = bit // 8 // z[1] * z[1]
                bit += w
                continue
            bit = (bit + z[1] * 8 - 1) // (z[1] * 8) * (z[1] * 8)
            self.offs[c["id"]] = bit // 8
            bit += z[0] * 8
        size = max(size, (bit + 7) // 8)
        size = (size + align - 1) // align * align
        self.sizes[rid] = (size, align)
        return self.sizes[rid]


def offsets(tu):
    """FieldDecl id -> its byte offset, for every record this can lay out."""
    lay = Layout(tu)
    for rid in list(lay.recs):
        lay.rsize(rid)
    return lay.offs


def walk(n, fn):
    fn(n)
    for c in n.get("inner", ()):
        if isinstance(c, dict):
            walk(c, fn)


class FileScan:
    def __init__(self, path):
        self.path = path
        self.defs = {}      # name -> (nparams, variadic)
        self.calls = []     # (caller, line, nargs, bases, fields, locals, type, field offset, Record.field called)
        self.inits = {}     # data name -> [function names] (C initializers, assignments)
        self.fields = {}    # struct field -> [function names] assigned to it
        self.param_sets = []  # (data name or field, function, parameter index) set from a parameter
        self.fnargs = {}    # (callee, argument index) -> [function names] passed
        self.fwd = []       # (callee, argument index, caller, caller's parameter index) passed on
        self.line = 0
        self.file = None
        self.in_main = True
        self.errors = []
        self.defsig = {}    # name -> fsig of the definition
        self.decls = []     # (name, file, line, fsig) of each declaration (not a definition)
        self.promos = []    # (callee, argument index, line, caller): an f32 promoted to double

    def loc(self, n):
        for key in ("loc", "range"):
            l = n.get(key)
            if not l:
                continue
            if key == "range":
                l = l.get("begin", {})
            l = l.get("expansionLoc", l)
            if "file" in l:
                self.file = l["file"]
                self.in_main = os.path.normpath(l["file"]) == os.path.normpath(self.path)
            if "line" in l:
                self.line = l["line"]

    def offkey(self, n):
        """~@0x408 for a field whose name spells its offset (f408, x408, p1C, cb44) at
        0x40 or more: views of one struct under different typedef and field names (O15.f408,
        O16.x408) meet there. Weak, like a field name."""
        off = self.offs.get(n.get("referencedMemberDecl"))
        m = re.match(r"[a-zA-Z]+_?([0-9a-fA-F]+)$", n.get("name", ""))
        if off is None or off < 0x40 or not m or int(m.group(1), 16) != off:
            return None
        return "~@0x%x" % off

    def run(self):
        p = subprocess.run(["clang"] + CFLAGS + [self.path], cwd=ROOT, capture_output=True, text=True)
        # clang refuses what gcc only warns about: a call with fewer arguments than a
        # prototype (or a K&R definition) names is the same passthrough, so report it
        self.errors = [l for l in p.stderr.splitlines() if ": error: " in l]
        if not p.stdout.strip():
            return self
        tu = json.loads(p.stdout)
        self.offs = offsets(tu)
        for d in tu.get("inner", ()):
            self.loc(d)
            if d.get("kind") == "FunctionDecl":
                if any(c.get("kind") == "CompoundStmt" for c in d.get("inner", ())):
                    self.defsig[d["name"]] = fsig(d)
                elif self.file and not os.path.isabs(self.file) and not d.get("isImplicit"):
                    self.decls.append((d["name"], self.file, self.line, fsig(d)))
            if d.get("kind") == "FunctionDecl" and any(c.get("kind") == "CompoundStmt" for c in d.get("inner", ())):
                ps = [c for c in d.get("inner", ()) if c.get("kind") == "ParmVarDecl"]
                var = d.get("variadic", False) or "..." in d.get("type", {}).get("qualType", "")
                self.defs[d["name"]] = (len(ps), var)
                if self.in_main:
                    self.func(d)
            elif d.get("kind") == "VarDecl" and d.get("inner") and self.in_main:
                names = []
                walk(d, lambda n: names.append(n["referencedDecl"]["name"]) if n.get("kind") == "DeclRefExpr"
                     and n.get("referencedDecl", {}).get("kind") == "FunctionDecl" else None)
                if names:
                    self.inits.setdefault(dname(d["name"]), []).extend(names)
            # keep the file / line state of the dump's order (it names a file only when it changes)
            walk(d, self.loc)
        return self

    def func(self, fd):
        assigns = {}  # local id -> [rhs nodes]

        params = [c["id"] for c in fd.get("inner", ()) if c.get("kind") == "ParmVarDecl"]
        local_ids = set()
        walk(fd, lambda n: local_ids.add(n["id"]) if n.get("kind") == "VarDecl" else None)

        def fnref(e):
            e = strip(e)
            if e.get("kind") == "UnaryOperator" and e.get("opcode") == "&":
                e = strip(e["inner"][0])
            if e.get("kind") == "DeclRefExpr" and e["referencedDecl"].get("kind") == "FunctionDecl":
                return e["referencedDecl"]["name"]
            return None

        def store(lhs, rhs):
            """lhs = rhs outside the locals: remember a function (or a parameter) stored in data or a field."""
            f = fnref(rhs)
            fs = [f] if f else []
            r = strip(rhs)
            pidx = None
            if r.get("kind") == "DeclRefExpr" and r["referencedDecl"].get("id") in params:
                pidx = params.index(r["referencedDecl"]["id"])
            elif r.get("kind") == "DeclRefExpr" and r["referencedDecl"].get("id") in assigns:
                # t->f14 = fn, the local assigned functions before (a switch's cases)
                fs = [fnref(x) for x in assigns[r["referencedDecl"]["id"]] if fnref(x)]
            if not fs and pidx is None:
                return
            keys, alt = [], {}

            def g(n):
                k = n.get("kind")
                if k == "DeclRefExpr" and n["referencedDecl"].get("kind") == "VarDecl" \
                        and n["referencedDecl"]["id"] not in local_ids:
                    keys.append(dname(n["referencedDecl"]["name"]))
                elif k == "MemberExpr":
                    keys.append("." + member(n))
                    if self.offkey(n):
                        alt["." + member(n)] = "." + self.offkey(n)
            walk(lhs, g)
            keys = keys[:1] + [k for k in keys[1:] if k.startswith(".")][-1:]
            if m2c_off(lhs) is not None and m2c_off(lhs) >= 0x40:
                keys.append(".~@0x%x" % m2c_off(lhs))  # M2C_FIELD(p, T, 0x4A0) = func_X
            for key in keys + [alt[k] for k in keys if k in alt]:
                if fs:
                    (self.fields.setdefault(key[1:], []) if key.startswith(".") else
                     self.inits.setdefault(key, [])).extend(fs)
                else:
                    self.param_sets.append((key, fd["name"], pidx))

        def collect(n):
            self.loc(n)
            k = n.get("kind")
            if k == "VarDecl" and n.get("inner"):
                assigns.setdefault(n["id"], []).append(n["inner"][0])
            elif k == "BinaryOperator" and n.get("opcode") == "=":
                lhs = strip(n["inner"][0])
                if lhs.get("kind") == "DeclRefExpr" and lhs["referencedDecl"].get("id") in local_ids:
                    assigns.setdefault(lhs["referencedDecl"]["id"], []).append(n["inner"][1])
                else:
                    store(n["inner"][0], n["inner"][1])
            elif k == "CallExpr":
                c = strip(n["inner"][0])
                if c.get("kind") == "DeclRefExpr":
                    for i, arg in enumerate(n["inner"][1:]):
                        f = fnref(arg)
                        if f:
                            self.fnargs.setdefault((c["referencedDecl"]["name"], i), []).append(f)
                        r = strip(arg)
                        if r.get("kind") == "DeclRefExpr" and r["referencedDecl"].get("id") in params:
                            self.fwd.append((c["referencedDecl"]["name"], i, fd["name"],
                                             params.index(r["referencedDecl"]["id"])))
        walk(fd, collect)

        def reads(e, seen):
            bases, fields, locs = set(), set(), set()

            def f(n):
                k = n.get("kind")
                if k == "DeclRefExpr":
                    r = n["referencedDecl"]
                    if r.get("kind") == "VarDecl":
                        if r["id"] in assigns and r["id"] not in seen:
                            locs.add(r["name"])
                            seen.add(r["id"])
                            for rhs in assigns[r["id"]]:
                                if fnref(rhs):
                                    bases.add("&" + fnref(rhs))  # fn = func_X; fn()
                                    continue
                                if strip(rhs).get("kind") == "InitListExpr":  # Tbl t = { { func_X, ... } }
                                    walk(rhs, lambda m: bases.add("&" + fnref(m)) if m.get("kind") == "DeclRefExpr"
                                         and fnref(m) else None)
                                    continue
                                b2, f2, l2 = reads(rhs, seen)
                                bases.update(b2)
                                fields.update(f2)
                                locs.update(l2)
                        elif r["id"] not in assigns:
                            bases.add(dname(r["name"]))
                    elif r.get("kind") == "ParmVarDecl":
                        locs.add(r["name"] + "(param)")
                        # the parameter itself is the pointer called (not a struct it points at)
                        if r["id"] in params and strip(e) is n:
                            bases.add("@%s#%d" % (fd["name"], params.index(r["id"])))
                elif k == "MemberExpr":
                    fields.add(member(n))
                    if self.offkey(n):
                        fields.add(self.offkey(n))
                elif k == "ArraySubscriptExpr":
                    b = strip(n["inner"][0])
                    if b.get("kind") == "DeclRefExpr" and b["referencedDecl"].get("kind") == "VarDecl" \
                            and "[" in b["referencedDecl"].get("type", {}).get("qualType", ""):
                        bases.add(dname(b["referencedDecl"]["name"]) + "[]")
            walk(e, f)
            return bases, fields, locs

        def visit(n):
            self.loc(n)
            if n.get("kind") == "FunctionDecl" and n is not fd and self.file and not os.path.isabs(self.file):
                self.decls.append((n["name"], self.file, self.line, fsig(n)))  # a block-scope extern
            if n.get("kind") == "CallExpr":
                callee = strip(n["inner"][0])
                c2 = callee
                if c2.get("kind") == "UnaryOperator" and c2.get("opcode") in ("*", "&"):
                    c2 = strip(c2["inner"][0])
                direct = c2.get("kind") == "DeclRefExpr" and c2["referencedDecl"].get("kind") == "FunctionDecl"
                cast = n["inner"][0]
                while cast.get("kind") in ("ImplicitCastExpr", "ParenExpr") and cast.get("inner"):
                    cast = cast["inner"][0]
                if direct and cast.get("kind") == "CStyleCastExpr":
                    sig = castsig(cast.get("type", {}))
                    if sig:
                        self.decls.append((c2["referencedDecl"]["name"], self.path, self.line, sig))
                for i, arg in enumerate(n["inner"][1:]):
                    # an unprototyped call (or a `()` cast) promotes an f32 to double
                    if arg.get("kind") == "ImplicitCastExpr" and arg.get("castKind") == "FloatingCast" \
                            and arg.get("type", {}).get("qualType") == "double" and arg.get("inner") \
                            and tclass(arg["inner"][0].get("type", {})) == "f32":
                        self.promos.append((c2["referencedDecl"]["name"] if direct else None, i, self.line,
                                            fd["name"]))
                if not (c2.get("kind") == "DeclRefExpr" and c2["referencedDecl"].get("kind") == "FunctionDecl"):
                    b, fl, lc = reads(callee, set())
                    # the offset of the field the pointer is loaded from (D_X[i].f, p->f; 0 for
                    # *(T *)(&D_X + i)), when this can size the record
                    top, hops = strip(callee), 0
                    while top.get("kind") == "DeclRefExpr" and top["referencedDecl"].get("id") in assigns \
                            and hops < 4:
                        top, hops = strip(assigns[top["referencedDecl"]["id"]][0]), hops + 1  # fn = p->f; fn()
                    off = 0
                    if m2c_off(top) is not None:
                        off = m2c_off(top)
                        if off >= 0x40:
                            fl.add("~@0x%x" % off)
                    elif top.get("kind") == "MemberExpr":
                        off = self.offs.get(top.get("referencedMemberDecl"))
                    self.calls.append((fd["name"], self.line, len(n["inner"]) - 1, sorted(b), sorted(fl),
                                       sorted(lc), n["inner"][0].get("type", {}).get("qualType", ""), off,
                                       member(top) if top.get("kind") == "MemberExpr" else None))
            for c in n.get("inner", ()):
                if isinstance(c, dict):
                    visit(c)
        self.line = 0
        self.loc(fd)
        visit(fd)


def data_tables():
    """PIECE name -> function names in its .word entries, from the src .s files, and
    every piece's (start, size)."""
    tabs, pieces, first = {}, [], {}
    for d, _, fs in os.walk(os.path.join(ROOT, "src")):
        for f in fs:
            if not f.endswith(".s"):
                continue
            cur = None
            for l in open(os.path.join(d, f), errors="replace"):
                m = re.match(r"\s*PIECE(?:_BEGIN)?\s+(D_([0-9A-Fa-f]{8})),\s*(0x[0-9a-fA-F]+|\d+)", l)
                if m:
                    pieces.append((int(m.group(2), 16), int(m.group(3), 0), m.group(1)))
                m = re.match(r"\s*PIECE(?:_BEGIN)?\s+(\w+)", l) or re.match(r"(\w+):", l)
                if m:
                    cur = m.group(1)
                    at0 = True
                    continue
                m = re.match(r"\s*\.word\s+([A-Za-z_]\w*)\s*$", l)
                if m and cur and not m.group(1).startswith(("D_", "jtbl", ".L")):
                    tabs.setdefault(cur, []).append(m.group(1))
                    if at0:
                        first[cur] = m.group(1)
                if cur and l.strip() and not l.lstrip().startswith(("/*", "#")):
                    at0 = False
    return tabs, sorted(pieces), first


def elf_words(pieces):
    """A function that gives the functions an address range of the user's ELF points at
    (the bytes a PIECE copies from it: pointers that were not written as .word)."""
    elf_path = os.path.join(ROOT, "SLPS_251.98")
    starts = set()
    for l in open(os.path.join(ROOT, "layout.tsv")):
        f = l.split("\t")
        if f and re.match(r"[0-9a-fA-F]{8}$", f[0]):
            starts.add(int(f[0], 16))
    if not os.path.exists(elf_path):
        print("indcheck: no SLPS_251.98, data pieces are read from their .word entries only", file=sys.stderr)
        return lambda name: [], lambda addr, stride, count: []
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    from elf32 import Elf  # noqa: E402
    from pathlib import Path
    elf = Elf.load(Path(elf_path))
    import bisect
    keys = [p[0] for p in pieces]

    def look(name):
        m = re.match(r"D_([0-9A-Fa-f]{8})(\[\])?$", name)
        if not m:
            return []
        addr = int(m.group(1), 16)
        if m.group(2):
            # an indexed table: the words from its start while they are functions or 0
            out = []
            for j in range(256):
                b = elf.read(addr + 4 * j, 4)
                w = int.from_bytes(b, "little") if b else -1
                if w in starts:
                    out.append("func_%08x" % w)
                elif w != 0:
                    break
            return out
        i = bisect.bisect_right(keys, addr) - 1
        if i >= 0 and pieces[i][0] <= addr < pieces[i][0] + pieces[i][1]:
            lo, size = pieces[i][0], pieces[i][1]
        else:
            lo, size = addr, 4
        b = elf.read(lo, size) or b""
        out = []
        for j in range(0, len(b) - 3, 4):
            w = int.from_bytes(b[j:j + 4], "little")
            if w in starts:
                out.append("func_%08x" % w)
        return out

    def look_at(addr, stride, count):
        """The functions at addr, addr + stride, ... (one field of a table's records)."""
        out = []
        for j in range(count):
            b = elf.read(addr + stride * j, 4)
            w = int.from_bytes(b, "little") if b else 0
            if w in starts:
                out.append("func_%08x" % w)
        return out
    return look, look_at


def elf_stores():
    """field offset -> the functions the main ELF's code stores at that offset of a
    register (lui / addiu of a function's start, then sw REG, OFF(BASE) before REG is
    written again; the stack's stores left out). Weak: any struct's field at OFF counts."""
    elf_path = os.path.join(ROOT, "SLPS_251.98")
    if not os.path.exists(elf_path):
        return {}
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    from elf32 import Elf  # noqa: E402
    from pathlib import Path
    starts = set()
    for l in open(os.path.join(ROOT, "layout.tsv")):
        f = l.split("\t")
        if f and re.match(r"[0-9a-fA-F]{8}$", f[0]):
            starts.add(int(f[0], 16))
    elf = Elf.load(Path(elf_path))
    lo, hi = min(starts), max(starts)
    b = elf.read(lo, hi - lo) or b""
    w = [int.from_bytes(b[i:i + 4], "little") for i in range(0, len(b) - 3, 4)]
    out, lui = {}, {}
    for i, x in enumerate(w):
        op, rs, rt, imm = x >> 26, (x >> 21) & 31, (x >> 16) & 31, x & 0xFFFF
        if op == 0x0F:
            lui[rt] = (imm << 16, i)
        elif op == 0x09 and rs in lui and i - lui[rs][1] < 8:
            v = (lui[rs][0] + (imm - 0x10000 if imm & 0x8000 else imm)) & 0xFFFFFFFF
            if v not in starts:
                continue
            for x2 in w[i + 1:i + 10]:
                if x2 >> 26 == 0x2B and (x2 >> 16) & 31 == rt:
                    if (x2 >> 21) & 31 != 29:
                        out.setdefault(x2 & 0xFFFF, set()).add("func_%08x" % v)
                    break
                if (x2 >> 16) & 31 == rt and x2 >> 26 not in (0x2B, 0x28, 0x29, 0x3F):
                    break
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tsv")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--takes", nargs="+", metavar="NAME",
                    help="for reading by hand: the parameters each function takes, and for a data name "
                         "(or @func#i, a parameter) the functions it holds with theirs")
    a = ap.parse_args()
    alias = {}
    for l in open(os.path.join(ROOT, "functions.tsv")):
        f = l.split("\t")
        if len(f) >= 2 and not l.startswith("#") and f[1].split():
            alias[f[0]] = "func_" + f[1].split()[0].lower()[-8:]
    norm = lambda s: alias.get(s, s)  # noqa: E731
    with ThreadPoolExecutor(a.j) as ex:
        scans = list(ex.map(lambda p: FileScan(p).run(), argcheck.files()))
    defs = {}
    for s in scans:
        for k, v in s.defs.items():
            defs.setdefault(norm(k), v)
    for k, v in ASM_TAKES.items():
        defs.setdefault(k, (v, False))
    tabs, pieces, first = data_tables()
    tabs = {k: [norm(x) for x in v] for k, v in tabs.items()}
    # a piece called as one pointer (no index, no field) reaches its first word only: the
    # .word entries after it are other data (D_00351BC8's +4, SyncDCache)
    later = {k: set(v) - {norm(first[k])} for k, v in tabs.items() if k in first}
    look, look_at = elf_words(pieces)
    stores = elf_stores()
    fnargs, fields = {}, {}
    for s in scans:
        for k, v in s.inits.items():
            tabs.setdefault(k, []).extend(norm(x) for x in v)
        for k, v in s.fnargs.items():
            fnargs.setdefault((norm(k[0]), k[1]), []).extend(norm(x) for x in v)
        for k, v in s.fields.items():
            fields.setdefault(k, []).extend(norm(x) for x in v)
    # Functions passed as arguments flow into the callee's parameter (@func#i), on through
    # the parameters it passes to other calls, and into the data or fields a parameter is
    # stored in: follow the edges to a fixpoint.
    edges = []
    for (fn, i), v in fnargs.items():
        tabs.setdefault("@%s#%d" % (fn, i), []).extend(v)
    for s in scans:
        for callee, i, caller, j in s.fwd:
            edges.append(("@%s#%d" % (norm(caller), j), "@%s#%d" % (norm(callee), i)))
        for key, fn, i in s.param_sets:
            edges.append(("@%s#%d" % (norm(fn), i), key))
    sets = {k: set(v) for k, v in tabs.items()}
    changed = True
    while changed:
        changed = False
        for a_, b_ in edges:
            add = sets.get(a_, set()) - sets.get(b_, set())
            if add:
                sets.setdefault(b_, set()).update(add)
                changed = True
    for k, v in sets.items():
        if k.startswith("."):
            fields.setdefault(k[1:], []).extend(v)
        else:
            tabs[k] = sorted(v)
    for group in FIELD_SAME:
        u = {t for k in group for t in (tabs.get(k, ()) if k.startswith("@") else fields.get(k, ()))}
        for k in group:
            if not k.startswith("@"):
                fields[k] = sorted(u)
    if a.takes:
        def takes(f):
            d = defs.get(norm(f))
            return "%s %s" % (f, "?" if d is None else "%d%s" % (d[0], "..." if d[1] else ""))
        for name in a.takes:
            if name in defs or norm(name) in defs:
                print(takes(name))
            else:
                fs = sorted(set(tabs.get(name) or look(name)) | set(fields.get(name, ())))
                print("%s: %s" % (name, ", ".join(takes(f) for f in fs) or "no functions"))
        return 0
    rows = []
    for s in scans:
        for caller, line, nargs, bases, flds, locs, ty, off, topf in s.calls:
            bases = [b.replace("@%s#" % caller, "@%s#" % norm(caller)) for b in bases]
            # a table defined in C or as .word entries is read from there, else from the ELF
            targets = {t for b in bases for t in (tabs.get(b.rstrip("[]")) or look(b))}
            targets |= {norm(b[1:]) for b in bases if b.startswith("&")}
            if not flds and not off:
                for b in bases:
                    targets -= later.get(b, set())
            for names, (lo, size, count) in RECORD_TABLES.items():
                if off is not None and topf and topf.split(".")[0] in names:
                    targets |= set(look_at(lo + off, size, count))
            for b in bases:
                m = re.match(r"D_([0-9A-Fa-f]{8})$", b)
                for setter, (lo, size, count, params, heads) in RECORD_SETTERS.items():
                    if off is None or not m:
                        continue
                    if b in heads:
                        at = off
                    elif lo <= int(m.group(1), 16) < lo + size * count:
                        at = (int(m.group(1), 16) - lo + off) % size
                    else:
                        continue
                    if at in params:
                        targets |= sets.get("@%s#%d" % (setter, params[at]), set())
            weak = {t for f in flds for t in fields.get(f, ())} - targets
            # a field name is only a name: its targets count when the data names none
            src_targets = targets or weak
            targets = sorted(src_targets)
            known = [defs[t][0] for t in targets if t in defs and not defs[t][1]]
            most = max(known) if known else None
            if most is not None and most > nargs:
                verdict = "SHORT?" if src_targets is weak else "SHORT"
            elif most is not None:
                verdict = "OK"
            elif targets:
                verdict = "?def"  # targets known, none defined in C (assembly, the SDK)
            else:
                verdict = "?"
            note = next((READ[k] for k in [(s.path, c, f) for c in (caller, "*") for f in flds]
                         + [(s.path, caller), (s.path, "*")] if k in READ), None)
            if note is None and s.path == "src/vm/vm_lib.c" and any(re.match(r"D_003773[0-9A-F]{2}$", b) for b in bases):
                note = VM_HOOKS
            if note is None and verdict == "?" and off and stores.get(off):
                # a lead for reading by hand: what the code stores at the field's offset of
                # any struct (any record's +OFF counts, so this decides nothing)
                st = sorted(stores[off])
                note = "lead: the ELF stores at +0x%X: %s" % (off, ", ".join(
                    "%s(%s)" % (f, defs[f][0] if f in defs else "?") for f in st[:8]) + (" ..." if len(st) > 8 else ""))
            # a note read by hand never hides a SHORT the targets prove (only a weak SHORT?)
            if note and verdict not in ("OK", "SHORT") and not note.startswith("lead:"):
                verdict = note.split()[0].rstrip(":")
            short = [t for t in targets if t in defs and defs[t][0] > nargs]
            rows.append((verdict, s.path, line, caller, nargs, most if most is not None else "?",
                         ",".join(b for b in bases if not b.endswith("[]") and not b.startswith("&")) or "-", ",".join(flds) or "-", ",".join(locs) or "-",
                         "%d/%d" % (len(short), len(targets)), ",".join(short[:6]) or "-", ty,
                         ",".join(targets[:6]) or "-", note or ""))
    # Argument and return classes (portability rule 11) from the syntax trees: every
    # declaration a file sees (headers, struct typedefs, `()` declarations, block-scope
    # externs) against the definition, and every f32 an unprototyped call promotes.
    defsig = {}
    for s in scans:
        for k, v in s.defsig.items():
            defsig.setdefault(norm(k), v)
    wide = ("f32", "f64", "i64", "q128", "rec")
    seen = set()
    for s in scans:
        for name, f, line, (ret, ps, var) in s.decls:
            d = defsig.get(norm(name))
            if not d or (f, line, name) in seen:
                continue
            seen.add((f, line, name))
            why = []
            # a 64-bit return read as 32 bits (or dropped) is its low word on x86 and ARM alike
            if ret != d[0] and (ret in wide or d[0] in wide) and "?" not in (ret, d[0]) \
                    and not ({ret, d[0]} <= {"i64", "i32", "void"}):
                why.append("returns %s, defined %s" % (ret, d[0]))
            if ps is not None and d[1] is not None and not d[2] and not var:
                for i, (a_, b_) in enumerate(zip(ps, d[1])):
                    if a_ != b_ and (a_ in wide or b_ in wide):
                        why.append("parameter %d %s, defined %s" % (i + 1, a_, b_))
            if why:
                rows.append(("ABI", f, line, "-", "-", "-", "-", "-", "-", "-", "-", name + ": " + "; ".join(why),
                             "-", ""))
        for callee, i, line, caller in s.promos:
            d = defsig.get(norm(callee)) if callee else None
            if d and d[1] is not None and i < len(d[1]) and d[1][i] == "f32":
                rows.append(("PROMO", s.path, line, caller, "-", "-", "-", "-", "-", "-", "-",
                             "%s: argument %d is an f32 passed as double (no prototype), defined f32"
                             % (callee, i + 1), "-", ""))
    # Session 69: a file clang cannot parse because of gcc nested functions is read from its host object
    # instead (the census compiles it with gcc): no `call *` there means no call through a pointer to miss.
    nested = ("function definition is not allowed here", "illegal storage class on function")
    for s in scans:
        verdict, note = "CLANG", ""
        if s.errors and all(e.split(": error: ", 1)[1].startswith(nested) for e in s.errors):
            obj = os.path.join(ROOT, "out", "host", s.path + ".o")
            if os.path.exists(obj):
                p = subprocess.run(["objdump", "-d", obj], capture_output=True, text=True)
                if p.returncode == 0 and not re.search(r"\bcall\s+\*", p.stdout):
                    verdict = "CLANG-READ"
                    note = ("READ: gcc nested functions clang cannot parse; the host object (gcc) has no call "
                            "through a pointer, and abicheck reads the file's declarations")
        for e in s.errors:
            rows.append((verdict, s.path, e.split(":")[1], "-", "-", "-", "-", "-", "-", "-", "-",
                         e.split(": error: ", 1)[1], "-", note))
    shown = [r for r in rows if a.all or r[0] in ("SHORT", "SHORT?", "CLANG", "ABI", "PROMO")]
    for r in shown:
        print("\t".join(str(x) for x in r))
    n = {}
    for r in rows:
        n[r[0]] = n.get(r[0], 0) + 1
    print("%d rows (indirect calls, ABI and PROMO declarations, CLANG errors): %s"
          % (len(rows), ", ".join("%s %d" % kv for kv in sorted(n.items()))), file=sys.stderr)
    if a.tsv:
        os.makedirs(os.path.dirname(a.tsv), exist_ok=True)
        with open(a.tsv, "w") as fh:
            fh.write("verdict\tfile\tline\tcaller\tpassed\ttakes\tdata\tfields\tlocals\tshort/targets\tshort\ttype\ttargets\tnote\n")
            for r in rows:
                fh.write("\t".join(str(x) for x in r) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
