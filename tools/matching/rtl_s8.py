# rtl.py FILE [start_line end_line]: compact list of insns: uid, set dest <- src (one line)
import sys, re
L = open(sys.argv[1]).read().split('\n')
a = int(sys.argv[2]) if len(sys.argv) > 2 else 0; b = int(sys.argv[3]) if len(sys.argv) > 3 else len(L)
txt = '\n'.join(L[a:b])
for m in re.finditer(r'^\((insn|call_insn|jump_insn|code_label|note)(?:/\w)? (\d+) .*?(?=^\(|\Z)', txt, re.S | re.M):
    k, uid, body = m.group(1), m.group(2), m.group(0)
    if k == 'note': continue
    s = re.sub(r'\s+', ' ', body)
    s = re.sub(r'\(expr_list.*', '', s) if k != 'call_insn' else s[:200]
    s = re.sub(r'^\(\w+(/\w)? \d+ \d+ \d+ ', '', s)
    print(k[0], uid, s[:170])
