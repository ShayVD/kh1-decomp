/* The clocks (vpk_clocks.h).  From kh1-decomp host/vita/main.c @ e1575e1a. */
#include <psp2/power.h>
#include "vpk_clocks.h"

void vpk_clocks_set(int arm, int bus, int gpu, int gpu_xbar, VpkClocks *got) {
    int arm0 = scePowerGetArmClockFrequency();
    scePowerSetArmClockFrequency(arm);
    scePowerSetBusClockFrequency(bus);
    scePowerSetGpuClockFrequency(gpu);
    scePowerSetGpuXbarClockFrequency(gpu_xbar);
    if (got) {
        got->arm_was = arm0;
        got->arm = scePowerGetArmClockFrequency();
        got->bus = scePowerGetBusClockFrequency();
        got->gpu = scePowerGetGpuClockFrequency();
        got->gpu_xbar = scePowerGetGpuXbarClockFrequency();
    }
}
