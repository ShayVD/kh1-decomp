#!/usr/bin/env python3
# symbolic register simulator over a straight-line asm range; prints stores base+off = expr
import sys,re
lines=[l.strip() for l in open(sys.argv[1])]
i=0
while i<len(lines)-1:
    if re.match(r'(jal|j|jr|b|beq|bne|beqz|bnez|beqzl|bnezl|beql|bnel|blez|bgez)\s',lines[i]) and not lines[i+1].startswith('.'):
        lines[i],lines[i+1]=lines[i+1],lines[i]; i+=2
    else: i+=1
start=int(sys.argv[2]) if len(sys.argv)>2 else 0
end=int(sys.argv[3]) if len(sys.argv)>3 else len(lines)
R={}
CN=[0]
def g(r):
    r=r.replace('$','')
    if r=='zero': return '0'
    return R.get(r,r)
def ev(e):
    try: return str(eval(e))
    except Exception: return e
for l in lines[start:end]:
    m=re.match(r'(\S+)\s*(.*)',l)
    if not m: continue
    op,args=m.group(1),[a.strip() for a in m.group(2).split(',')] if m.group(2) else []
    a=[x.replace('$','') for x in args]
    def num(x): return int(x,0)
    if op=='li': R[a[0]]=str(num(a[1]))
    elif op=='lui': R[a[0]]=str(num(a[1])<<16) if a[1].startswith(('0','1','2','3','4','5','6','7','8','9')) else 'hi('+a[1]+')'
    elif op=='ori': R[a[0]]=ev('(%s|%d)'%(g(a[1]),num(a[2])))
    elif op=='addiu': R[a[0]]=ev('(%s+%d)'%(g(a[1]),num(a[2]))) if not a[2].startswith('%') else g(a[1])+'+lo'
    elif op in('addu','daddu'): R[a[0]]=ev('(%s+%s)'%(g(a[1]),g(a[2])))
    elif op=='subu': R[a[0]]=ev('(%s-%s)'%(g(a[1]),g(a[2])))
    elif op=='sll': R[a[0]]=ev('(%s<<%d)'%(g(a[1]),num(a[2])))
    elif op=='dsll': R[a[0]]=ev('(%s<<%d)'%(g(a[1]),num(a[2])))
    elif op=='dsll32': R[a[0]]=ev('(%s<<%d)'%(g(a[1]),32+num(a[2])))
    elif op=='dsrl32': R[a[0]]='zx(%s)'%g(a[1]) if 'zx' not in g(a[1]) else g(a[1])
    elif op in('move',): R[a[0]]=g(a[1])
    elif op in('and','or'): R[a[0]]='(%s %s %s)'%(g(a[1]),'&' if op=='and' else '|',g(a[2]))
    elif op in('lw','lhu','lh','lbu','lb','ld','lwc1'):
        mm=re.match(r'(.*)\((\w+)\)',a[1]); R[a[0]]='%s[%s+%s]'%(op,g(mm.group(2)),mm.group(1))
    elif op in('sw','sd','sh','sb','swc1'):
        mm=re.match(r'(.*)\((\w+)\)',a[1]); print('%s %s+%s = %s'%(op,g(mm.group(2)),mm.group(1),g(a[0])))
    elif op=='jal': print('CALL',args[0], 'a0=',g('a0'),'a1=',g('a1')); CN[0]+=1; R['v0']='ret%d_'%CN[0]+args[0][5:]
    elif op in('slti',): R[a[0]]='(%s<%s)'%(g(a[1]),a[2])
    elif op=='movn': R[a[0]]='(%s?%s:%s)'%(g(a[2]),g(a[1]),g(a[0]))
    elif op=='mtc1' or op.startswith('cvt') or op.endswith('.s'): pass
    else: R[a[0]] = op+'(...)' if a else None
