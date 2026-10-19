import gdb
gdb.execute("set pagination off")
def pri(Q):
    r=int(Q['n_refs']); s=int(Q['size']); l=int(Q['death'])-int(Q['birth'])
    f = 0 if r<=1 else (1 if r<4 else (2 if r<8 else 3))
    return f*r*s*10000//max(l,1)
class FB(gdb.FinishBreakpoint):
    def __init__(self, b):
        super().__init__(gdb.newest_frame(), internal=True); self.b=b
    def stop(self):
        n=int(gdb.parse_and_eval('next_qty')); qty=gdb.parse_and_eval('qty')
        try: fn=gdb.parse_and_eval('current_function_decl->decl.name->identifier.pointer').string()
        except Exception as e: fn='?'
        s=[]
        for i in range(n):
            Q=qty[i]; s.append("q%d:r%d:p%d:ph%d:bd%d-%d" % (i,int(Q['first_reg']),pri(Q),int(Q['phys_reg']),int(Q['birth']),int(Q['death'])))
        print("BLK %s b%d n%d %s" % (fn, self.b, n, ' '.join(s)))
        return False
class B(gdb.Breakpoint):
    def stop(self):
        FB(int(gdb.newest_frame().read_var('b'))); return False
B("block_alloc")
gdb.execute("run")
