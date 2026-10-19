# ga3.py: global-alloc trace, one FR line per find_reg call with the hard reg it chose (gdb.FinishBreakpoint on find_reg reads reg_renumber). Run with gt.sh.
import gdb
gdb.execute('set pagination off'); gdb.execute('set confirm off')
names=['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','s8','ra']
def nm(i): return 'mem' if i<0 else (names[i] if i<32 else 'f%d'%(i-32))
def rs(v):
    x=int(v[0])&0xffffffffffffffff
    return ','.join(nm(i) for i in range(64) if (x>>i)&1)
class GA(gdb.Breakpoint):
    def stop(self):
        print('GA_BEGIN'); return False
class FRF(gdb.FinishBreakpoint):
    def __init__(s, fr, num, reg, txt):
        super().__init__(fr, internal=True); s.num=num; s.reg=reg; s.txt=txt
    def stop(s):
        r=int(gdb.parse_and_eval('reg_renumber[%d]'%s.reg))
        print('FR %s -> %s'%(s.txt, nm(r))); return False
    def out_of_scope(s): pass
class FR(gdb.Breakpoint):
    def stop(self):
        f=gdb.selected_frame()
        num=int(f.read_var('num')); a=gdb.parse_and_eval('allocno[%d]'%num)
        reg=int(a['reg'])
        txt='num=%d reg=%d refs=%d len=%d calls=%d retry=%d pref=[%s] copy=[%s] someone=[%s]'%(num,reg,int(a['n_refs']),int(a['live_length']),int(a['calls_crossed']),int(f.read_var('retrying')),rs(a['hard_reg_preferences']),rs(a['hard_reg_copy_preferences']),rs(a['regs_someone_prefers']))
        FRF(gdb.newest_frame(), num, reg, txt)
        return False
GA('global_alloc'); FR('find_reg')
gdb.execute('run')
