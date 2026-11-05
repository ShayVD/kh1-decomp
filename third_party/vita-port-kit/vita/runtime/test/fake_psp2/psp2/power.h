#ifndef FAKE_PSP2_POWER_H
#define FAKE_PSP2_POWER_H
int scePowerGetArmClockFrequency(void);
int scePowerGetBusClockFrequency(void);
int scePowerGetGpuClockFrequency(void);
int scePowerGetGpuXbarClockFrequency(void);
int scePowerSetArmClockFrequency(int);
int scePowerSetBusClockFrequency(int);
int scePowerSetGpuClockFrequency(int);
int scePowerSetGpuXbarClockFrequency(int);
#endif
