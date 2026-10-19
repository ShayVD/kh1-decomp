import gdb
gdb.execute("set pagination off")
class FB(gdb.FinishBreakpoint):
    def __init__(self, info):
        super().__init__(gdb.newest_frame(), internal=True); self.info = info
    def stop(self):
        print(self.info, "->", int(self.return_value)); return False
class B(gdb.Breakpoint):
    def stop(self):
        f = gdb.newest_frame()
        q = int(f.read_var('qtyno')); Q = gdb.parse_and_eval('qty')[q]
        info = "q%d b%d d%d sugg%d acc%d reg%d refs%d size%d" % (q, int(f.read_var('born_index')), int(f.read_var('dead_index')), int(f.read_var('just_try_suggested')), int(f.read_var('accept_call_clobbered')), int(Q['first_reg']), int(Q['n_refs']), int(Q['size'])) + " bd%d-%d" % (int(Q['birth']), int(Q['death']))
        FB(info); return False
B("find_free_reg")
gdb.execute("run")
