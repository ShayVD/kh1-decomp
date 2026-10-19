import gdb
gdb.execute("set pagination off")
def I(a): return int(gdb.parse_and_eval("*(int*)%d"%a))
def arr(base,i,sz=4):
    p=I(base)
    t='int' if sz==4 else 'short'
    return int(gdb.parse_and_eval("((%s*)%d)[%d]"%(t,p,i)))
FUNC=[None]
CUR=[0]; RETS=set()
class FB(gdb.Breakpoint):
    def __init__(self,ret):
        super().__init__("*%d"%ret,internal=True)
    def stop(self):
        n=I(0x082233f8)
        s=[]
        for i in range(n):
            br=arr(0x08223418,i); de=arr(0x0822341c,i); r=arr(0x08223410,i); sz=arr(0x08223420,i)
            fr=arr(0x08223434,i); ph=arr(0x082233fc,i,2)
            import math; fl=(r.bit_length()-1) if r>0 else 0; s.append("q%d:r%d:n%d:s%d:p%d:ph%d:bd%d-%d"%(i,fr,r,sz,int(fl*r*sz*10000//max(de-br,1)),ph,br,de))
        print("BLK b%d n%d %s"%(CUR[0],n,' '.join(s)))
        return False
class B(gdb.Breakpoint):
    def stop(self):
        esp=int(gdb.parse_and_eval("$esp"))
        ret=I(esp); b=I(esp+4)
        CUR[0]=b
        if ret not in RETS: RETS.add(ret); FB(ret)
        return False
B("*0x08111ef0")
gdb.execute("run")
