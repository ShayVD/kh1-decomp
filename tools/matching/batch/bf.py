# bf.py MODE FNAME FILE... : score files (same prefix before /*UNIT*/) in one compile batch
import sys; sys.path.insert(0, __import__('os').path.dirname(__import__('os').path.abspath(__file__))); import batch
mode, fn = sys.argv[1:3]; fs = sys.argv[3:]
P=None; U=[]
for f in fs:
    s=open(f).read(); i=s.index('/*UNIT*/'); P = P or s[:i]; U.append(s[i+9:])
r=[]
for k in range(0,len(U),200): r += batch.score(P, fn, U[k:k+200], mode)
for f,x in sorted(zip(fs,r), key=lambda t:t[1])[:10]: print(x, f)
