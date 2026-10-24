/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"
M2C_UNK func_001a5ca0(void *);
M2C_UNK func_001a62a8(s32);
M2C_UNK func_001a6538(s32);
M2C_UNK func_001a67a0(s32);

void pppKeShpTailPhtFrame(void) {

}

void pppKeShpTailPhtDraw(void) {

}

void pppKeShpTailPhtCon(void) {

}

void pppKeShpTailPhtReset(void) {

}

void pppKeShpTailLcFrame(void) {

}

void pppKeShpTailLcDraw(void) {

}

void pppKeShpDttFrame(void) {

}

void pppKeLnsLpCon(s32 arg0, PppEntry *arg1) {
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    func_001a5ca0(temp_s0);
    M2C_FIELD(temp_s0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0xA8) = 0;
}

void pppKeLnsArndCon(s32 arg0, PppEntry *arg1) {
    func_001a62a8(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsCrnCon(s32 arg0, PppEntry *arg1) {
    func_001a6538(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsFlsCon(s32 arg0, PppEntry *arg1) {
    func_001a67a0(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsLpTDes(void) {

}

void pppKeLnsClmTDes(void) {

}
#include "data/bss_0061_mixed.h"
