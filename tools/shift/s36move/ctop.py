"""Split a C file into top-level items (text, kind, name), losslessly:
''.join(texts) is the file.  Kinds: pp, comment, decl, func, tail
(session 36, tools/shift/s36move/mod.py)."""
import re
def items(src):
    out=[]; i=0; n=len(src); cur_start=0
    depth=0; j=0
    res=[]
    start=0
    while j<n:
        c=src[j]
        if src.startswith('/*',j):
            k=src.index('*/',j+2)+2
            if depth==0 and src[start:j].strip()=='' :
                # standalone comment: own item
                e=k
                while e<n and src[e] in ' \t': e+=1
                if e<n and src[e]=='\n': e+=1
                res.append((src[start:e],'comment',None)); start=e; j=e; continue
            j=k; continue
        if src.startswith('//',j):
            k=src.find('\n',j); k=n if k<0 else k+1
            if depth==0 and src[start:j].strip()=='':
                res.append((src[start:k],'comment',None)); start=k; j=k; continue
            j=k; continue
        if c=='#' and depth==0 and src[start:j].strip()=='':
            k=j
            while True:
                e=src.find('\n',k); e=n if e<0 else e
                if src[e-1:e]=='\\': k=e+1; continue
                break
            e=min(e+1,n)
            res.append((src[start:e],'pp',None)); start=e; j=e; continue
        if c in '"\'':
            k=j+1
            while src[k]!=c:
                k+= 2 if src[k]=='\\' else 1
            j=k+1; continue
        if c=='{': depth+=1
        elif c=='}':
            depth-=1
            if depth==0:
                rest=src[j+1:]
                m=re.match(r'[^;{}]*?;',rest)
                text_so_far=src[start:j+1]
                if m and not re.search(r'\)\s*\{',text_so_far.split('{')[0]+'{') :
                    pass
                else:
                    e=j+1
                    while e<n and src[e] in ' \t': e+=1
                    if e<n and src[e]=='\n': e+=1
                    t=src[start:e]
                    hd=t.split('{')[0]
                    name=None
                    if re.search(r'\)\s*$',hd.strip()) or re.search(r'\)\s*$',re.sub(r'/\*.*?\*/','',hd,flags=re.S).strip()):
                        mm=re.findall(r'(\w+)\s*\(',hd)
                        name=mm[0] if mm else None
                        # skip return-type words like "(*" cases
                        res.append((t,'func',name)); start=e; j=e; continue
        elif c==';' and depth==0:
            e=j+1
            while e<n and src[e] in ' \t': e+=1
            if src.startswith('/*',e) and '\n' not in src[e:src.index('*/',e)]:
                e=src.index('*/',e)+2
                while e<n and src[e] in ' \t': e+=1
            elif src.startswith('//',e):
                e=src.find('\n',e)
            if e<n and src[e]=='\n': e+=1
            res.append((src[start:e],'decl',None)); start=e; j=e; continue
        j+=1
    if start<n: res.append((src[start:],'tail',None))
    return res
if __name__=='__main__':
    import sys
    for t,k,nm in items(open(sys.argv[1]).read()):
        print(k,nm,repr(t[:70]))
