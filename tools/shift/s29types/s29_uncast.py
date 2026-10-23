#!/usr/bin/env python3
"""Drop view casts of pieces whose declaration now has the users' type (session 29).

  python3 -I tools/shift/s29types/s29_uncast.py [--scalar] --types T1,T2 --pieces D_X,D_Y FILE.c ...

`((T *)&D_X)` and `(T *)&D_X` become `D_X` (D_X must be an array of T's type),
`&D_X` given to a T pointer (`= &D_X;`) becomes `D_X`.  Edits in place; run
s27_check.py afterwards.  --scalar: the pieces are single T objects (uncast_scalar).
"""
import re, sys


def uncast_scalar(t, types, pieces):
    """the same for a piece that is one T object: `(*(T *)&D_X)` -> `D_X`,
    `((T *)&D_X)` / `(T *)&D_X` -> `&D_X`, `&((T *)&D_X)[k]` -> `(&D_X + k)`"""
    for D in pieces:
        for T in types:
            c = r"\(\s*" + T + r"\s*\*\s*\)\s*&\s*" + D
            t = re.sub(r"\(\s*\*\s*" + c + r"\s*\)", D, t)
            t = re.sub(r"&\s*\(\s*" + c + r"\s*\)\s*\[\s*0\s*\]", "&" + D, t)
            t = re.sub(r"&\s*\(\s*" + c + r"\s*\)\s*\[\s*(\w+)\s*\]", r"(&" + D + r" + \1)", t)
            t = re.sub(r"\(\s*" + c + r"\s*\)", "&" + D, t)
            t = re.sub(c + r"\b", "&" + D, t)
    return t


def uncast(t, types, pieces):
    for D in pieces:
        for T in types:
            t = re.sub(r"\(\s*\(\s*" + T + r"\s*\*\s*\)\s*&\s*" + D + r"\s*\)", D, t)
            t = re.sub(r"\(\s*" + T + r"\s*\*\s*\)\s*&\s*" + D + r"\b", D, t)
        t = re.sub(r"&\(" + D + r"\)\[", "&" + D + "[", t)
    return t


def main(argv):
    types = pieces = None
    scalar = False
    files = []
    it = iter(argv)
    for a in it:
        if a == "--types":
            types = next(it).split(",")
        elif a == "--scalar":
            scalar = True
        elif a == "--pieces":
            pieces = next(it).split(",")
        else:
            files.append(a)
    for f in files:
        s = open(f).read()
        s2 = (uncast_scalar if scalar else uncast)(s, types, pieces)
        if s2 != s:
            open(f, "w").write(s2)
            print("changed", f)


if __name__ == "__main__":
    main(sys.argv[1:])
