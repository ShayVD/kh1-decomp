#!/bin/bash
# pref.sh file : compile, print user-var regs, their prefs, dispositions
D=/tmp/claude-0/s12/s12w2/dp; mkdir -p $D
/tmp/claude-0/s12/s12w2/cc.sh $1 $D
for r in $(grep "user var" $D/x.c.19.lreg | grep GR_REGS | awk '{print $2}'); do
  echo "$(grep "^Register $r " $D/x.c.19.lreg | cut -c1-60) | pref: $(grep "^;; $r preferences" $D/x.c.20.greg | cut -d: -f2) | in $(sed -n '/Register dispositions/,$p' $D/x.c.20.greg | grep -o "\b$r in [0-9]*" | head -1)"
done
