import gdb
gdb.execute('set pagination off')
def uid(e):
    v=gdb.parse_and_eval(e)
    if int(v)==0: return 0
    return int(v['fld'][0]['rtint'])
class GA(gdb.Breakpoint):
    def stop(self): print('CJ_BEGIN'); return False
class DC(gdb.Breakpoint):
    def stop(self):
        print('CJ do insn=%d newjpos=%d newlpos=%d'%(uid('insn'),uid('newjpos'),uid('newlpos'))); return False
class FC(gdb.Breakpoint):
    def stop(self):
        print('CJ find e1=%d e2=%d'%(uid('e1'),uid('e2'))); return False
GA('rest_of_compilation'); DC('do_cross_jump')
import os
if os.environ.get('FIND'): FC('find_cross_jump')
gdb.execute('run')
