# mktpl_s17.py (s17m1): build a tog_s17 template from a 001c62a0 draft (site list hard-coded).
import sys
src, out = sys.argv[1:3]
s = open(src).read()
if s.startswith('/*'): s = s.split('*/', 1)[1]
A, B, C = '\x01', '\x03', '\x02'
def alt(*xs): return A + B.join(xs) + C
def rep(o, n, need=True):
    global s
    if o not in s:
        if need: raise SystemExit('missing: ' + o)
        return
    s = s.replace(o, n, 1)
D = 'D_0037A380.'
rep("        e->c0 = *(C4 *)p; p++;", "        " + alt("e->", "D_0037A380.ent[i].") + "c0 = *(C4 *)p; p++;")
rep("        *(C4 *)((u8 *)&D_0037A380.ent[i].v[2] - 44) = *(C4 *)p; p++;", "        " + alt("*(C4 *)((u8 *)&D_0037A380.ent[i].v[2] - 44)", "e->c4", "D_0037A380.ent[i].c4") + " = *(C4 *)p; p++;")
rep("        e->n = *p; p++;", "        " + alt("e->", "D_0037A380.ent[i].") + "n = *p; p++;")
for k in range(10):
    rep("        cpm(&D_0037A380.ent[i].v[%d], p); p += 4;" % k, "        cpm(&" + alt("D_0037A380.ent[i].", "e->") + "v[%d], p); p += 4;" % k)
rep("        cpm(&e->v[10], p); p += 4;", "        cpm(&" + alt("e->", "D_0037A380.ent[i].") + "v[10], p); p += 4;")
rep("{ f32 *d = &D_0037A380.e.x; f32 *v = (f32 *)(b + 336);", "{ " + alt("f32 *d = &D_0037A380.e.x; f32 *v = (f32 *)(b + 336);", "f32 *v = (f32 *)(b + 336); f32 *d = &D_0037A380.e.x;", "f32 *d = &D_0037A380.e.x; f32 *v = (f32 *)b + 84;", "f32 *d = (f32 *)((u8 *)&D_0037A380 + 80); f32 *v = (f32 *)(b + 336);"))
rep("    u8 *b = (u8 *)&D_0037A380;\n", alt("    u8 *b = (u8 *)&D_0037A380;\n", "    u8 *b;\n", "    u8 *b;\n", "    u8 *b;\n", "    u8 *b = (u8 *)&D_0037A380;\n    s32 d3_;\n", "    u8 *b;\n    s32 d3_;\n"))
rep("    D_0037A380.n = *p++;\n    for (i = 0; ", alt("    D_0037A380.n = *p++;\n    for (i = 0; ", "    D_0037A380.n = *p++;\n    b = (u8 *)&D_0037A380;\n    for (i = 0; ", "    b = (u8 *)&D_0037A380;\n    D_0037A380.n = *p++;\n    for (i = 0; ", "    D_0037A380.n = *p++;\n    for (b = (u8 *)&D_0037A380, i = 0; ", "    D_0037A380.n = *p++;\n    for (i = 0, b = (u8 *)&D_0037A380; "))
rep("    if (add[0] < 0.0f) i = 0; else j = 0;\n", alt("    if (add[0] < 0.0f) i = 0; else j = 0;\n", "", "    if (set[0] < 0.0f) i = 0; else j = 0;\n"))
rep("    s32 i, j;\n", alt("    s32 i, j;\n", "    s32 j, i;\n", "    s32 i;\n    s32 j;\n    s32 d0_;\n", "    s32 d0_;\n    s32 i, j;\n"))
rep("        Ent *e = &D_0037A380.ent[i];\n", alt("        Ent *e = &D_0037A380.ent[i];\n", "        Ent *e;\n        s32 d1_;\n        e = &D_0037A380.ent[i];\n"))
rep("        struct Lk *l;\n", alt("        struct Lk *l;\n", "        struct Lk *l;\n        s32 d2_;\n"))
rep("            lk_init(&D_0037A380.ent[i].lk);", "            lk_init(" + alt("&D_0037A380.ent[i].lk", "l", "&D_0037A380.ent[0].lk") + ");")
open(out, 'w').write(s)
