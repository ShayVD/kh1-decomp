#!/usr/bin/env python3
"""Drop view casts of pieces whose declaration now has the users' type (session 29).

  python3 -I tools/shift/s29types/s29_uncast.py --types T1,T2 --pieces D_X,D_Y FILE.c ...

`((T *)&D_X)` and `(T *)&D_X` become `D_X` (D_X must be an array of T's type),
`&D_X` given to a T pointer (`= &D_X;`) becomes `D_X`.  Edits in place; run
s27_check.py afterwards.
"""
import re, sys


def uncast(t, types, pieces):
    for D in pieces:
        for T in types:
            t = re.sub(r"\(\s*\(\s*" + T + r"\s*\*\s*\)\s*&\s*" + D + r"\s*\)", D, t)
            t = re.sub(r"\(\s*" + T + r"\s*\*\s*\)\s*&\s*" + D + r"\b", D, t)
        t = re.sub(r"&\(" + D + r"\)\[", "&" + D + "[", t)
    return t


def main(argv):
    types = pieces = None
    files = []
    it = iter(argv)
    for a in it:
        if a == "--types":
            types = next(it).split(",")
        elif a == "--pieces":
            pieces = next(it).split(",")
        else:
            files.append(a)
    for f in files:
        s = open(f).read()
        s2 = uncast(s, types, pieces)
        if s2 != s:
            open(f, "w").write(s2)
            print("changed", f)


if __name__ == "__main__":
    main(sys.argv[1:])
