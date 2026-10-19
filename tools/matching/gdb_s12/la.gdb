set pagination off
set confirm off
break block_alloc if b == 42
run
finish
p next_qty
p qty[0]
p qty[1]
p qty[2]
p qty[3]
p qty[4]
quit
