# deps.py dumpfile startuid_list : for given insn uids, list forward dependents in sched2 dump
import re,sys
t=open(sys.argv[1]).read()
ins={}
for m in re.finditer(r'\n\((insn|call_insn|jump_insn)(?::\w+)? (\d+) (\d+) (\d+) (.*?)(?=\n\((?:insn|call_insn|jump_insn|code_label|note|barrier))',t,re.S):
    uid=int(m.group(2)); body=' '.join(m.group(5).split())
    ins[uid]=body
fw={}
for u,b in ins.items():
    # LOG_LINKS: insn_list entries following the pattern; take all 'insn_list(:KIND)? N'
    for k,v in re.findall(r'insn_list(:REG_DEP_\w+)? (\d+)',b):
        fw.setdefault(int(v),[]).append((u,k or ':TRUE'))
for s in sys.argv[2].split(','):
    s=int(s); print(s, ins.get(s,'')[:60], len(fw.get(s,[])), fw.get(s))
