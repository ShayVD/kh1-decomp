import gdb
gdb.execute('set pagination off')
gdb.execute('set confirm off')
names=['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','s8','ra']
def rs(v):
    x=int(v[0])&0xffffffffffffffff
    return ','.join(names[i] for i in range(32) if (x>>i)&1)
class GA(gdb.Breakpoint):
    def stop(self):
        print('GA_BEGIN'); return False
class FR(gdb.Breakpoint):
    def stop(self):
        f=gdb.selected_frame()
        num=int(f.read_var('num')); a=gdb.parse_and_eval('allocno[%d]'%num)
        print('FR num=%d reg=%d refs=%d len=%d calls=%d retry=%d conf=[%s] pref=[%s] copy=[%s] full=[%s] someone=[%s]'%(num,int(a['reg']),int(a['n_refs']),int(a['live_length']),int(a['calls_crossed']),int(f.read_var('retrying')),rs(a['hard_reg_conflicts']),rs(a['hard_reg_preferences']),rs(a['hard_reg_copy_preferences']),rs(a['hard_reg_full_preferences']),rs(a['regs_someone_prefers'])))
        import os
        w=os.environ.get('CONF','')
        if w and int(a['reg']) in [int(x) for x in w.split(',')]:
            rw=int(gdb.parse_and_eval('allocno_row_words')); mx=int(gdb.parse_and_eval('max_allocno'))
            base=int(gdb.parse_and_eval('(long)*(long long**)&conflicts'))
            inf=gdb.selected_inferior(); out=[]
            for b in range(mx):
                word=int.from_bytes(inf.read_memory(base+8*(rw*num+b//64),8),'little')
                if (word>>(b%64))&1: out.append('%d'%int(gdb.parse_and_eval('allocno[%d].reg'%b)))
            print('CONF reg=%d: %s'%(int(a['reg']),' '.join(out)))
        return False
GA('global_alloc'); FR('global.c:1368')
class FE(gdb.Breakpoint):
    def stop(self):
        print('GA_END'); return False
gdb.execute('run')
