import gdb, os
gdb.execute('set pagination off')
names=['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','s8','ra']
UID=int(os.environ['UID_'])
def uid(v):
    return 0 if int(v)==0 else int(v['fld'][0]['rtint'])
state={'opp':None,'depth':0}
class FS(gdb.Breakpoint):
    def stop(self):
        f=gdb.selected_frame()
        if uid(f.read_var('insn'))==UID:
            print('RG fill insn=%d thread=%d opp=%d likely=%d tif=%d own=%d'%(UID,uid(f.read_var('thread')),uid(f.read_var('opposite_thread')),int(f.read_var('likely')),int(f.read_var('thread_if_true')),int(f.read_var('own_thread'))))
            state['opp']=uid(f.read_var('opposite_thread')); state['on']=True
        else: state['on']=False
        return False
class Fin(gdb.FinishBreakpoint):
    def __init__(self,frame,res,tgt):
        super().__init__(frame,internal=True); self.res=res; self.tgt=tgt
    def stop(self):
        r=gdb.parse_and_eval('*(struct resources*)%d'%self.res)
        x=int(r['regs'][0])&0xffffffff
        print('RG mtlr target=%d -> live=[%s]'%(self.tgt,','.join(names[i] for i in range(32) if (x>>i)&1)))
        return False
class MT(gdb.Breakpoint):
    def stop(self):
        if not state.get('on'): return False
        f=gdb.selected_frame()
        t=uid(f.read_var('target')) if int(f.read_var('target')) else 0
        Fin(f,int(f.read_var('res')),t)
        return False
class FB(gdb.Breakpoint):
    def stop(self):
        if not state.get('on'): return False
        f=gdb.selected_frame()
        print('RG findbb insn=%d'%uid(f.read_var('insn')))
        return False
FS('fill_slots_from_thread'); MT('mark_target_live_regs'); FB('find_basic_block')
gdb.execute('run')
