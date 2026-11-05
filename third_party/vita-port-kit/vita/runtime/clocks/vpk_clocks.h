/* The CPU, bus and GPU clocks.  An application starts at ARM 333 MHz; VPK_CLOCKS_MAX is what Vita ports set
 * (ARM 444, bus 222, GPU 222, GPU crossbar 166).  Vita3K takes the calls and runs as fast either way.
 * From kh1-decomp host/vita/main.c @ e1575e1a. */
#ifndef VPK_CLOCKS_H
#define VPK_CLOCKS_H

typedef struct {
    int arm_was; /* the ARM clock before */
    int arm, bus, gpu, gpu_xbar; /* what the Vita accepted (MHz) */
} VpkClocks;

#define VPK_CLOCKS_MAX 444, 222, 222, 166

/* sets the four clocks (MHz) and reads back what the Vita accepted into got (may be 0) */
void vpk_clocks_set(int arm, int bus, int gpu, int gpu_xbar, VpkClocks *got);

#endif /* VPK_CLOCKS_H */
