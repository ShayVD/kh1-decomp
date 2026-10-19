# tl73.py: true LCS (DP) between ours.n and orig.n; prints orig-words-unmatched, ours-unmatched, sum
# (session 11, s11w73) True DP LCS for big functions, where lchk's difflib count misaligns. W points at a work dir holding ours.<ext> and orig.<ext> word dumps; edit it.
import sys
W='/tmp/claude-0/s11/s11w73/'
EXT='raw' if len(sys.argv)<2 else sys.argv[1]
A=[l.rstrip('\n') if EXT=='raw' else l.split(' ',1)[1].rstrip('\n') for l in open(W+'ours.'+EXT)]
B=[l.rstrip('\n') if EXT=='raw' else l.split(' ',1)[1].rstrip('\n') for l in open(W+'orig.'+EXT)]
ids={}
a=[ids.setdefault(x,len(ids)) for x in A]; b=[ids.setdefault(x,len(ids)) for x in B]
prev=[0]*(len(b)+1)
for i in range(len(a)):
    cur=[0]*(len(b)+1); ai=a[i]
    for j in range(len(b)):
        cur[j+1]= prev[j]+1 if ai==b[j] else (prev[j+1] if prev[j+1]>cur[j] else cur[j])
    prev=cur
m=prev[-1]
print('TL', len(b)-m, len(a)-m, len(a)+len(b)-2*m)
