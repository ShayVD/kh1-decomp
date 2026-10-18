import re
def pp(text):
    L=text.split('\n'); out=[]; i=0
    while i < len(L):
        m=re.match(r'\tla\t(\$\d+),([A-Za-z_]\w*)$', L[i])
        if m and i+1 < len(L) and re.match(r'\tjal\t', L[i+1]):
            r,sym=m.groups()
            out += [f'\tlui\t{r},%hi({sym})', '\t.set\tnoreorder', '\t.set\tnomacro', L[i+1], f'\taddiu\t{r},{r},%lo({sym})', '\t.set\tmacro', '\t.set\treorder']
            i += 2; continue
        out.append(L[i]); i+=1
    return '\n'.join(out)
