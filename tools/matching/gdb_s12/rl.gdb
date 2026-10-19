set pagination off
set confirm off
break emit_reload_insns
commands
silent
printf "uid %d last %d n %d :", chain->insn->fld[0].rtint, last_spill_reg, n_reloads
set $i = 0
while $i < n_reloads
  if rld[$i].reg_rtx
    printf " %d", rld[$i].reg_rtx->fld[0].rtuint
  else
    printf " -"
  end
  set $i = $i + 1
end
printf "\n"
cont
end
run
quit
