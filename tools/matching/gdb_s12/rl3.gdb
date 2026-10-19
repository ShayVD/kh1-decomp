set pagination off
set confirm off
break choose_reload_regs if chain->insn->fld[0].rtint == 914
commands
silent
printf "at 914 last %d -> set 0\n", last_spill_reg
set last_spill_reg = 0
cont
end
break emit_reload_insns
commands
silent
set $u = chain->insn->fld[0].rtint
if $u == 914 || $u == 1266 || $u == 916 || $u == 1269
printf "uid %d last %d :", $u, last_spill_reg
set $i = 0
while $i < n_reloads
  if rld[$i].reg_rtx
    printf " %d", rld[$i].reg_rtx->fld[0].rtuint
  end
  set $i = $i + 1
end
printf "\n"
end
cont
end
run
quit
