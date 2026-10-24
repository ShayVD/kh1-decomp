/* The disc read queue under src/io/discfile.c: the request slots D_004F3230
 * (func_0011ffd0 takes one), func_0011fd60 a synchronous read (sceCdRead),
 * func_0011fd40 a wait (a guess), func_0011fe20 loads the file table at
 * boot, func_0011fec0 compares the disc's name (strncmp). Flag mode:
 * nostrict (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00110000_s6_04.h"

/* func_0011fe20 (from hand/nostrict/text_00110000_s6_04.c). */
extern FileEnt D_004E4A00[];
extern s32 D_002C5C30;
extern s32 D_004F3208;
void func_00120580(char *, FileEnt *);
FileEnt *func_00120190(char *);
void func_0011fe20(void) {
    FileEnt *p;
    func_00120580("\\KINGDOM.IDX;1", D_004E4A00);
    D_002C5C30 = 0;
    p = D_004E4A00;
    while (p->lsn != 0 || p->size != 0) {
        p->lsn += D_004F3208;
        D_002C5C30++;
        p++;
        if (D_002C5C30 >= 3584) goto done;
    }
done:
    {FileEnt *e = func_00120190("kingdom.img"); D_004F3200 = e->lsn;}
}

