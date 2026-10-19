set pagination off
set confirm off
break emit_reload_insns
commands
silent
set $u = chain->insn->fld[0].rtint
if $u == 914 || $u == 1266 || $u == 916 || $u == 1269 || $u == 922 || $u == 1261
printf "uid %d last %d used %lx valid %lx atall %lx :", $u, last_spill_reg, reload_reg_used[0], reg_reloaded_valid[0], reload_reg_used_at_all[0]
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
