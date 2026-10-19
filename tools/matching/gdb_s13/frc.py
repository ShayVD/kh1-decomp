import gdb, os
gdb.execute('set pagination off')
UID=int(os.environ['UID_'])
def uid(v): return 0 if int(v)==0 else int(v['fld'][0]['rtint'])
st={'on':False}
class FS(gdb.Breakpoint):
    def stop(self):
        f=gdb.selected_frame(); st['on']= uid(f.read_var('insn'))==UID
        return False
class TS(gdb.Breakpoint):
    def stop(self):
        if not st['on']: return False
        st['on']=False
        gdb.execute('set var opposite_needed.regs[0] |= 4')
        print('RG forced')
        return False
FS('fill_slots_from_thread')
TS('reorg.c:2540')
gdb.execute('run')
