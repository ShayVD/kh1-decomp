set pagination off
set confirm off
break block_alloc if b == BLK
run
finish
p next_qty
set $i = 0
while $i < next_qty
  printf "q%d r%d refs %d birth %d death %d size %d phys %d pri %d\n", $i, qty[$i].first_reg, qty[$i].n_refs, qty[$i].birth, qty[$i].death, qty[$i].size, qty[$i].phys_reg, (qty[$i].n_refs > 1 ? (qty[$i].n_refs >= 4 ? (qty[$i].n_refs >= 8 ? 3 : 2) : 1) : 0) * qty[$i].n_refs * qty[$i].size * 10000 / (qty[$i].death - qty[$i].birth)
  set $i = $i + 1
end
quit
