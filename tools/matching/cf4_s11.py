import sys, os, itertools, json
sys.path.insert(0, '/home/claude/kh1-decomp/tools/matching'); os.environ.setdefault('WDIR','/tmp/claude-0/s11/s11w6')
import lchk_s10 as L
s=open('/tmp/claude-0/s11/s11w6/f1.c').read()
a=s.index('        m.x = r->x4->x4;'); b=s.index('        func_001c4640(&m);')
cfg=json.loads(sys.argv[1])
S=cfg['S']; arm='{ %s }'%cfg['arm']; cond=cfg.get('cond','vm'); decl=cfg.get('decl','')
dst='/home/claude/kh1-decomp/src/hand/.s11w6_t.c'; res=[]
for rest in itertools.permutations(range(len(S))):
  for pos in range(len(S)+1):
    lines=['        '+S[i] for i in rest]; lines.insert(pos,'        if (%s) %s else %s'%(cond,arm,arm))
    t=s[:a]+'\n'.join(lines)+'\n'+s[b:]
    t=t.replace('    Msg m;\n','    Msg m;\n'+decl)
    open(dst,'w').write(t); r=L.check(dst,'001cfc28')
    if r: v=r['func_001cfc28']; res.append((v[0],v[1],rest,pos,t))
res.sort(key=lambda x:(x[0],x[1]))
for x in res[:3]: print(x[:4])
open('/tmp/claude-0/s11/s11w6/cf4_best.c','w').write(res[0][4])
