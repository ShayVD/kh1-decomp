set pagination off
set confirm off
break emit_reload_insns
commands
silent
set $u = chain->insn->fld[0].rtint
printf "uid %d last %d :", $u, last_spill_reg
set $i = 0
while $i < n_reloads
  if rld[$i].reg_rtx
    printf " %d", rld[$i].reg_rtx->fld[0].rtuint
  end
  set $i = $i + 1
end
printf "\n"
cont
end
run
quit
