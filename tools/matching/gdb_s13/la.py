import gdb
gdb.execute('set pagination off'); gdb.execute('set confirm off')
class FB(gdb.FinishBreakpoint):
    def stop(self):
        n=int(gdb.parse_and_eval('next_qty'))
        print('LA_BEGIN')
        for q in range(n):
            e=gdb.parse_and_eval('qty[%d]'%q)
            print('LQ q=%d reg=%d refs=%d birth=%d death=%d calls=%d phys=%d sugg=%d copysugg=%d'%(q,int(e['first_reg']),int(e['n_refs']),int(e['birth']),int(e['death']),int(e['n_calls_crossed']),int(e['phys_reg']),int(gdb.parse_and_eval('qty_phys_num_sugg[%d]'%q)),int(gdb.parse_and_eval('qty_phys_num_copy_sugg[%d]'%q))))
        return False
class BA(gdb.Breakpoint):
    def stop(self):
        FB(gdb.newest_frame(), internal=True); return False
BA('block_alloc')
gdb.execute('run')
