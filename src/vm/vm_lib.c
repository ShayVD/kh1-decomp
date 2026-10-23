/* Opcode 24 of the script VM: the library of script functions
 * (docs/modules.md "Session 32").
 *
 * func_001dcad0 is the handler D_0037A198[24]: it calls entry k of
 * D_003D9FE0 with the VM and returns its result (2 / 4 / 6, as the other
 * handlers).  The table has 763 entries, from 0x001c6d08 to 0x001ec678.
 * 547 of them lie in 0x001cd238-0x001dcad0, numbered mostly in address order
 * (an increasing run of 480), and the last-numbered entry (762,
 * func_001dca48) is the last one before func_001dcad0: the library functions
 * there and this dispatcher are probably one file, and this file is meant to
 * grow upward with them (src/vm/vm_lib.c from 0x001cd238; see "Next module
 * moves").  The other entries belong to other modules: the camera
 * (src/camera/, 32), the message windows (src/msgwin/, 30) and 154 functions
 * after 0x001dcad0 (0x001ddc78-0x001ec678). */
#include "common.h"
#include "data/types/vm_rec.h"

/* A library function: takes the VM, returns the handler result. */
typedef s32 (*VmLibFn)();

s32 func_001c6d08();
s32 func_001c71e8();
s32 func_001c7700();
s32 func_001c7c18();
s32 func_001c8168();
s32 func_001c8260();
s32 func_001c8308();
s32 func_001c83c8();
s32 func_001c8420();
s32 func_001c8478();
s32 func_001c84c8();
s32 func_001c8518();
s32 func_001c8568();
s32 func_001c85d8();
s32 func_001c8648();
s32 func_001c86b8();
s32 func_001c8708();
s32 func_001c8878();
s32 func_001c8a00();
s32 func_001c8c90();
s32 func_001c8d98();
s32 func_001c91e8();
s32 func_001c92e8();
s32 func_001c9db0();
s32 func_001c9e20();
s32 func_001ca0f8();
s32 func_001ca368();
s32 func_001ca5f8();
s32 func_001ca680();
s32 func_001ca708();
s32 func_001ca790();
s32 func_001ca7c8();
s32 func_001cac98();
s32 func_001cae00();
s32 func_001cae78();
s32 func_001cb120();
s32 func_001cb3c0();
s32 func_001cb440();
s32 func_001cb738();
s32 func_001cb7d0();
s32 func_001cb960();
s32 func_001cbbd0();
s32 func_001cbfc0();
s32 func_001cc170();
s32 func_001cc1c0();
s32 func_001cc210();
s32 func_001cc260();
s32 func_001cc2c8();
s32 func_001cc330();
s32 func_001cc380();
s32 func_001cc3d0();
s32 func_001cc420();
s32 func_001cc470();
s32 func_001cc508();
s32 func_001cc548();
s32 func_001cc628();
s32 func_001cc640();
s32 func_001ccbd8();
s32 func_001ccbf8();
s32 func_001cccf0();
s32 func_001ccda8();
s32 func_001ccdf0();
s32 func_001cd280();
s32 func_001cd2c0();
s32 func_001cd2d8();
s32 func_001cd600();
s32 func_001cd6b8();
s32 func_001cd740();
s32 func_001cd748();
s32 func_001cd778();
s32 func_001cd7e0();
s32 func_001cd7e8();
s32 func_001cd830();
s32 func_001cd8b0();
s32 func_001cd8e0();
s32 func_001cd910();
s32 func_001cd940();
s32 func_001cd9e8();
s32 func_001cda18();
s32 func_001cda60();
s32 func_001cdaa8();
s32 func_001cdaf0();
s32 func_001cdb38();
s32 func_001cdb80();
s32 func_001cdbc8();
s32 func_001cdc58();
s32 func_001cdcb8();
s32 func_001cdd18();
s32 func_001cdd60();
s32 func_001cdda8();
s32 func_001cddf0();
s32 func_001cde38();
s32 func_001cdea8();
s32 func_001cded0();
s32 func_001cdf00();
s32 func_001cdf98();
s32 func_001ce020();
s32 func_001ce0b8();
s32 func_001ce150();
s32 func_001ce1a8();
s32 func_001ce240();
s32 func_001ce298();
s32 func_001ce2e8();
s32 func_001ce320();
s32 func_001ce358();
s32 func_001ce390();
s32 func_001ce3c0();
s32 func_001ce400();
s32 func_001ce440();
s32 func_001ce5f0();
s32 func_001ce750();
s32 func_001ce880();
s32 func_001ce9b0();
s32 func_001cea38();
s32 func_001ceac0();
s32 func_001ceb08();
s32 func_001ceb78();
s32 func_001cec68();
s32 func_001ceda0();
s32 func_001cede8();
s32 func_001cee90();
s32 func_001ceee8();
s32 func_001cef20();
s32 func_001cef80();
s32 func_001cefb8();
s32 func_001cf018();
s32 func_001cf0c8();
s32 func_001cf110();
s32 func_001cf210();
s32 func_001cf300();
s32 func_001cf478();
s32 func_001cf5d0();
s32 func_001cf728();
s32 func_001cf7a0();
s32 func_001cf838();
s32 func_001cf890();
s32 func_001cf8e8();
s32 func_001cf940();
s32 func_001cf960();
s32 func_001cfa58();
s32 func_001cfa78();
s32 func_001cfad0();
s32 func_001cfb00();
s32 func_001cfb48();
s32 func_001cfb90();
s32 func_001cfc28();
s32 func_001cfd30();
s32 func_001cfdd8();
s32 func_001cfe98();
s32 func_001cfeb8();
s32 func_001cfed8();
s32 func_001cff08();
s32 func_001cff80();
s32 func_001d0070();
s32 func_001d0138();
s32 func_001d0170();
s32 func_001d01a8();
s32 func_001d01c8();
s32 func_001d01e8();
s32 func_001d02d0();
s32 func_001d0380();
s32 func_001d0440();
s32 func_001d0468();
s32 func_001d0490();
s32 func_001d04b8();
s32 func_001d0500();
s32 func_001d0548();
s32 func_001d05a0();
s32 func_001d0600();
s32 func_001d0660();
s32 func_001d0680();
s32 func_001d06b8();
s32 func_001d06f0();
s32 func_001d07a8();
s32 func_001d07e0();
s32 func_001d0818();
s32 func_001d0868();
s32 func_001d0908();
s32 func_001d0938();
s32 func_001d09d8();
s32 func_001d0a28();
s32 func_001d0a38();
s32 func_001d0a80();
s32 func_001d0ac8();
s32 func_001d0b10();
s32 func_001d0b68();
s32 func_001d0b90();
s32 func_001d0dd0();
s32 func_001d1010();
s32 func_001d1230();
s32 func_001d12b8();
s32 func_001d1348();
s32 func_001d1380();
s32 func_001d13c0();
s32 func_001d13e0();
s32 func_001d1400();
s32 func_001d1418();
s32 func_001d1428();
s32 func_001d1450();
s32 func_001d1478();
s32 func_001d14a0();
s32 func_001d14c8();
s32 func_001d14f0();
s32 func_001d1640();
s32 func_001d16a8();
s32 func_001d16c8();
s32 func_001d1728();
s32 func_001d1790();
s32 func_001d17d0();
s32 func_001d1890();
s32 func_001d1948();
s32 func_001d1a28();
s32 func_001d1b00();
s32 func_001d1bf8();
s32 func_001d1ce0();
s32 func_001d1df0();
s32 func_001d1ef0();
s32 func_001d1f48();
s32 func_001d1fb0();
s32 func_001d2018();
s32 func_001d2080();
s32 func_001d2088();
s32 func_001d2090();
s32 func_001d2270();
s32 func_001d2468();
s32 func_001d24b0();
s32 func_001d24f8();
s32 func_001d2540();
s32 func_001d2588();
s32 func_001d25d8();
s32 func_001d2628();
s32 func_001d2668();
s32 func_001d2708();
s32 func_001d2720();
s32 func_001d2768();
s32 func_001d2860();
s32 func_001d2958();
s32 func_001d2ab8();
s32 func_001d2b58();
s32 func_001d2c08();
s32 func_001d2c68();
s32 func_001d2fd8();
s32 func_001d3040();
s32 func_001d3078();
s32 func_001d30e0();
s32 func_001d3118();
s32 func_001d31d8();
s32 func_001d3228();
s32 func_001d3248();
s32 func_001d3268();
s32 func_001d32a8();
s32 func_001d32f0();
s32 func_001d3338();
s32 func_001d3380();
s32 func_001d33c8();
s32 func_001d3430();
s32 func_001d3468();
s32 func_001d3490();
s32 func_001d34b0();
s32 func_001d3558();
s32 func_001d35a0();
s32 func_001d3610();
s32 func_001d3710();
s32 func_001d3828();
s32 func_001d3858();
s32 func_001d38d0();
s32 func_001d3948();
s32 func_001d39b0();
s32 func_001d3a28();
s32 func_001d3a48();
s32 func_001d3a78();
s32 func_001d3aa8();
s32 func_001d3b20();
s32 func_001d3b80();
s32 func_001d3bb0();
s32 func_001d3be8();
s32 func_001d3c28();
s32 func_001d3c70();
s32 func_001d3cb8();
s32 func_001d3d08();
s32 func_001d3d58();
s32 func_001d3da8();
s32 func_001d3de8();
s32 func_001d3e08();
s32 func_001d3ff0();
s32 func_001d40b0();
s32 func_001d40f0();
s32 func_001d4168();
s32 func_001d41e0();
s32 func_001d4258();
s32 func_001d42f0();
s32 func_001d4358();
s32 func_001d43d8();
s32 func_001d4448();
s32 func_001d44b8();
s32 func_001d44f8();
s32 func_001d4538();
s32 func_001d4578();
s32 func_001d4610();
s32 func_001d4690();
s32 func_001d4710();
s32 func_001d4798();
s32 func_001d4ac8();
s32 func_001d4b38();
s32 func_001d4b60();
s32 func_001d4c08();
s32 func_001d4cb8();
s32 func_001d4d68();
s32 func_001d4de0();
s32 func_001d4e10();
s32 func_001d4e38();
s32 func_001d4e60();
s32 func_001d4f10();
s32 func_001d4fc0();
s32 func_001d5010();
s32 func_001d5090();
s32 func_001d5118();
s32 func_001d5168();
s32 func_001d5278();
s32 func_001d52c0();
s32 func_001d5308();
s32 func_001d5330();
s32 func_001d5350();
s32 func_001d5388();
s32 func_001d5408();
s32 func_001d5458();
s32 func_001d54a8();
s32 func_001d54d8();
s32 func_001d5500();
s32 func_001d5528();
s32 func_001d5550();
s32 func_001d5578();
s32 func_001d55a0();
s32 func_001d55c8();
s32 func_001d55f0();
s32 func_001d5618();
s32 func_001d56a8();
s32 func_001d56f0();
s32 func_001d5738();
s32 func_001d5780();
s32 func_001d57d0();
s32 func_001d5828();
s32 func_001d5850();
s32 func_001d5878();
s32 func_001d58a0();
s32 func_001d58c8();
s32 func_001d5978();
s32 func_001d59a0();
s32 func_001d5a50();
s32 func_001d5b00();
s32 func_001d5b58();
s32 func_001d5ed8();
s32 func_001d5f18();
s32 func_001d5f58();
s32 func_001d5f80();
s32 func_001d5fa8();
s32 func_001d5ff0();
s32 func_001d6038();
s32 func_001d6080();
s32 func_001d60c0();
s32 func_001d6100();
s32 func_001d6128();
s32 func_001d6180();
s32 func_001d61c8();
s32 func_001d6210();
s32 func_001d6230();
s32 func_001d6250();
s32 func_001d6348();
s32 func_001d63e8();
s32 func_001d64f8();
s32 func_001d6558();
s32 func_001d65b8();
s32 func_001d6600();
s32 func_001d6628();
s32 func_001d6658();
s32 func_001d66b8();
s32 func_001d66d8();
s32 func_001d66f8();
s32 func_001d6718();
s32 func_001d6760();
s32 func_001d6780();
s32 func_001d67c8();
s32 func_001d6810();
s32 func_001d6858();
s32 func_001d68a0();
s32 func_001d68e8();
s32 func_001d6930();
s32 func_001d6958();
s32 func_001d6978();
s32 func_001d69d0();
s32 func_001d6a20();
s32 func_001d6a40();
s32 func_001d6a60();
s32 func_001d6bf8();
s32 func_001d6c08();
s32 func_001d6c20();
s32 func_001d6c48();
s32 func_001d6c80();
s32 func_001d6cf0();
s32 func_001d6d60();
s32 func_001d6db0();
s32 func_001d6dd0();
s32 func_001d6df0();
s32 func_001d6e10();
s32 func_001d6e30();
s32 func_001d6e50();
s32 func_001d6e70();
s32 func_001d6ef0();
s32 func_001d6f38();
s32 func_001d6f60();
s32 func_001d6f70();
s32 func_001d6f90();
s32 func_001d6fb0();
s32 func_001d6ff8();
s32 func_001d7040();
s32 func_001d7118();
s32 func_001d7220();
s32 func_001d7238();
s32 func_001d7258();
s32 func_001d72e0();
s32 func_001d7320();
s32 func_001d7438();
s32 func_001d74b8();
s32 func_001d7520();
s32 func_001d7548();
s32 func_001d75d0();
s32 func_001d7678();
s32 func_001d76c8();
s32 func_001d76e8();
s32 func_001d7798();
s32 func_001d7820();
s32 func_001d7840();
s32 func_001d7b88();
s32 func_001d7ef8();
s32 func_001d8400();
s32 func_001d85a8();
s32 func_001d85f0();
s32 func_001d8638();
s32 func_001d8660();
s32 func_001d8680();
s32 func_001d86e0();
s32 func_001d8738();
s32 func_001d8760();
s32 func_001d87b8();
s32 func_001d87d8();
s32 func_001d8838();
s32 func_001d88c8();
s32 func_001d8910();
s32 func_001d8958();
s32 func_001d89a0();
s32 func_001d8a00();
s32 func_001d8a60();
s32 func_001d8ac0();
s32 func_001d8b08();
s32 func_001d8b28();
s32 func_001d8b48();
s32 func_001d8b68();
s32 func_001d8b98();
s32 func_001d8be0();
s32 func_001d8c00();
s32 func_001d8c30();
s32 func_001d8c80();
s32 func_001d8cc8();
s32 func_001d8d18();
s32 func_001d8d70();
s32 func_001d8db8();
s32 func_001d8e10();
s32 func_001d8e60();
s32 func_001d8eb0();
s32 func_001d8ef8();
s32 func_001d8f18();
s32 func_001d9100();
s32 func_001d9268();
s32 func_001d9480();
s32 func_001d95f0();
s32 func_001d9728();
s32 func_001d9750();
s32 func_001d9780();
s32 func_001d9830();
s32 func_001d9850();
s32 func_001d9880();
s32 func_001d98d0();
s32 func_001d9950();
s32 func_001d99d0();
s32 func_001d99f8();
s32 func_001d9a50();
s32 func_001d9aa0();
s32 func_001d9af8();
s32 func_001d9b58();
s32 func_001d9bb0();
s32 func_001d9c08();
s32 func_001d9c60();
s32 func_001d9cb0();
s32 func_001d9d30();
s32 func_001d9d90();
s32 func_001d9dd0();
s32 func_001d9df0();
s32 func_001d9e40();
s32 func_001d9e90();
s32 func_001d9eb8();
s32 func_001d9ee0();
s32 func_001d9f20();
s32 func_001d9f88();
s32 func_001d9fb0();
s32 func_001d9ff8();
s32 func_001da040();
s32 func_001da088();
s32 func_001da0e8();
s32 func_001da108();
s32 func_001da128();
s32 func_001da178();
s32 func_001da1a8();
s32 func_001da1d0();
s32 func_001da260();
s32 func_001da2c8();
s32 func_001da3b8();
s32 func_001da400();
s32 func_001da490();
s32 func_001da520();
s32 func_001da5b0();
s32 func_001da628();
s32 func_001da6d0();
s32 func_001da740();
s32 func_001da7b8();
s32 func_001da808();
s32 func_001da860();
s32 func_001da8b8();
s32 func_001da910();
s32 func_001da968();
s32 func_001da9f0();
s32 func_001daa00();
s32 func_001daa18();
s32 func_001daad8();
s32 func_001dab20();
s32 func_001dab48();
s32 func_001dab98();
s32 func_001dabc0();
s32 func_001dabe8();
s32 func_001dac40();
s32 func_001dacc8();
s32 func_001dad30();
s32 func_001dad58();
s32 func_001db018();
s32 func_001db060();
s32 func_001db080();
s32 func_001db0d0();
s32 func_001db140();
s32 func_001db198();
s32 func_001db208();
s32 func_001db278();
s32 func_001db2e0();
s32 func_001db348();
s32 func_001db3b8();
s32 func_001db408();
s32 func_001db458();
s32 func_001db4a8();
s32 func_001db500();
s32 func_001db550();
s32 func_001db5a0();
s32 func_001db5c0();
s32 func_001db5e0();
s32 func_001db600();
s32 func_001db658();
s32 func_001db718();
s32 func_001db888();
s32 func_001db8e0();
s32 func_001db950();
s32 func_001db9c0();
s32 func_001db9f8();
s32 func_001dba30();
s32 func_001dba88();
s32 func_001dbae0();
s32 func_001dbb00();
s32 func_001dbb20();
s32 func_001dbb40();
s32 func_001dbb60();
s32 func_001dbba0();
s32 func_001dbbf0();
s32 func_001dbc10();
s32 func_001dbc38();
s32 func_001dbc90();
s32 func_001dbcd8();
s32 func_001dbd20();
s32 func_001dbd68();
s32 func_001dbdc8();
s32 func_001dbe50();
s32 func_001dbe78();
s32 func_001dbec0();
s32 func_001dbf20();
s32 func_001dbf68();
s32 func_001dbfb8();
s32 func_001dc000();
s32 func_001dc100();
s32 func_001dc120();
s32 func_001dc140();
s32 func_001dc280();
s32 func_001dc2e0();
s32 func_001dc308();
s32 func_001dc358();
s32 func_001dc3c0();
s32 func_001dc470();
s32 func_001dc520();
s32 func_001dc7c0();
s32 func_001dc800();
s32 func_001dc868();
s32 func_001dc8c8();
s32 func_001dc9a0();
s32 func_001dca00();
s32 func_001dca48();
s32 func_001ddc78();
s32 func_001dde08();
s32 func_001ddf98();
s32 func_001ddfb8();
s32 func_001de030();
s32 func_001de0b0();
s32 func_001de130();
s32 func_001de1e0();
s32 func_001de290();
s32 func_001de328();
s32 func_001de420();
s32 func_001de4e8();
s32 func_001de558();
s32 func_001de5b0();
s32 func_001de6a8();
s32 func_001de778();
s32 func_001de848();
s32 func_001de910();
s32 func_001de9e0();
s32 func_001deaf8();
s32 func_001dec10();
s32 func_001ded08();
s32 func_001def20();
s32 func_001df130();
s32 func_001df170();
s32 func_001df1d8();
s32 func_001df268();
s32 func_001df2a8();
s32 func_001df310();
s32 func_001df3a8();
s32 func_001df4a0();
s32 func_001df568();
s32 func_001df5d8();
s32 func_001df630();
s32 func_001df708();
s32 func_001df7e0();
s32 func_001df890();
s32 func_001df940();
s32 func_001df9c0();
s32 func_001dfa38();
s32 func_001dfaa0();
s32 func_001dfb20();
s32 func_001dfbb8();
s32 func_001dfcb0();
s32 func_001dfd78();
s32 func_001dfde0();
s32 func_001dfe50();
s32 func_001dfea8();
s32 func_001dffa0();
s32 func_001e0010();
s32 func_001e0078();
s32 func_001e0220();
s32 func_001e0318();
s32 func_001e0338();
s32 func_001e0498();
s32 func_001e0528();
s32 func_001e16b0();
s32 func_001e1748();
s32 func_001e17e0();
s32 func_001e24c8();
s32 func_001e25c8();
s32 func_001e25e8();
s32 func_001e2628();
s32 func_001e2668();
s32 func_001e26b8();
s32 func_001e3770();
s32 func_001e38b0();
s32 func_001e3dd0();
s32 func_001e3ed0();
s32 func_001e4790();
s32 func_001e4868();
s32 func_001e5d78();
s32 func_001e7488();
s32 func_001e79a0();
s32 func_001e7ad8();
s32 func_001e7e00();
s32 func_001e7ea8();
s32 func_001e7f08();
s32 func_001e80d0();
s32 func_001e8238();
s32 func_001e82e0();
s32 func_001e83f8();
s32 func_001e8560();
s32 func_001e8608();
s32 func_001e8770();
s32 func_001e87b8();
s32 func_001e8800();
s32 func_001e88e0();
s32 func_001e89c0();
s32 func_001e89e0();
s32 func_001e8a10();
s32 func_001e8a30();
s32 func_001e8a50();
s32 func_001e8b08();
s32 func_001e8b50();
s32 func_001e8bc0();
s32 func_001e8bd8();
s32 func_001e8c88();
s32 func_001e8cf0();
s32 func_001e8d40();
s32 func_001e8da0();
s32 func_001e8de8();
s32 func_001e8f68();
s32 func_001e9028();
s32 func_001e9048();
s32 func_001e90c8();
s32 func_001e90d0();
s32 func_001e9108();
s32 func_001e9150();
s32 func_001e9170();
s32 func_001e9190();
s32 func_001e91c0();
s32 func_001e91f0();
s32 func_001e9238();
s32 func_001e9288();
s32 func_001e9310();
s32 func_001ea438();
s32 func_001ea470();
s32 func_001ea580();
s32 func_001ea5f8();
s32 func_001ea658();
s32 func_001ea6b8();
s32 func_001ea760();
s32 func_001ea808();
s32 func_001ea888();
s32 func_001ea908();
s32 func_001ea9c8();
s32 func_001eaa88();
s32 func_001eab78();
s32 func_001eb140();
s32 func_001eb1d8();
s32 func_001eb278();
s32 func_001eb380();
s32 func_001eb4b8();
s32 func_001eb558();
s32 func_001eb698();
s32 func_001eb7b0();
s32 func_001eb910();
s32 func_001eba80();
s32 func_001ebb10();
s32 func_001ebba0();
s32 func_001ebd48();
s32 func_001ebde0();
s32 func_001ebf18();
s32 func_001ebf48();
s32 func_001ebf98();
s32 func_001ebff0();
s32 func_001ec040();
s32 func_001ec0d8();
s32 func_001ec1a0();
s32 func_001ec3b0();
s32 func_001ec3f8();
s32 func_001ec468();
s32 func_001ec678();

VmLibFn D_003D9FE0[0x2fb] ALIGNED(32) = {
    func_001cbbd0, func_001cb960, func_001cae78, func_001cc260,
    func_001cc2c8, func_001cc330, func_001cc380, func_001cc420,
    func_001cd280, func_001cd2c0, func_001ea580, func_001cd2d8,
    func_001cd600, func_001cd6b8, func_001cd740, func_001cd7e0,
    func_001cd8b0, func_001cd8e0, func_001cd910, func_001cd940,
    func_001cd9e8, func_001cda18, func_001cda60, func_001cdaa8,
    func_001cdaf0, func_001cdb38, func_001cdb80, func_001cdd18,
    func_001cdd60, func_001cdda8, func_001cddf0, func_001cde38,
    func_001cded0, func_001cc470, func_001c6d08, func_001c8168,
    func_001c8260, func_001c8308, func_001c83c8, func_001c8420,
    func_001c8478, func_001c84c8, func_001c8518, func_001c8568,
    func_001c85d8, func_001c8648, func_001c86b8, func_001c8708,
    func_001ddfb8, func_001c8878, func_001c8a00, func_001c8c90,
    func_001c8d98, func_001cdbc8, func_001ea5f8, func_001ea658,
    func_001cdc58, func_001cdcb8, func_001cdf00, func_001cdf98,
    func_001ce150, func_001ce298, func_001ce2e8, func_001ce320,
    func_001ce358, func_001ce390, func_001ce3c0, func_001ce400,
    func_001ce440, func_001ce5f0, func_001ce750, func_001ce880,
    func_001ce9b0, func_001ceac0, func_001ceb08, func_001ceb78,
    func_001cec68, func_001ceda0, func_001cede8, func_001cee90,
    func_001cc170, func_001cc1c0, func_001cc210, func_001cc3d0,
    func_001ceee8, func_001cef80, func_001cf018, func_001cf0c8,
    func_001cac98, func_001cae00, func_001cf110, func_001cf300,
    func_001cf478, func_001cf728, func_001cf7a0, func_001cf838,
    func_001cf890, func_001cf8e8, func_001cf940, func_001cf960,
    func_001cfa58, func_001cfa78, func_001c91e8, func_001cfad0,
    func_001cfb00, func_001cfb48, func_001c92e8, func_001cc508,
    func_001cfb90, func_001cfc28, func_001cfd30, func_001cfdd8,
    func_001cfe98, func_001cfeb8, func_001cfed8, func_001cff08,
    func_001cff80, func_001d0070, func_001d0138, func_001d0170,
    func_001d01a8, func_001d01c8, func_001d01e8, func_001d02d0,
    func_001e0338, func_001e0498, func_001d0380, func_001d0440,
    func_001d0468, func_001d0490, func_001ce1a8, func_001ce240,
    func_001d04b8, func_001d0500, func_001d0548, func_001d05a0,
    func_001d0680, func_001d06b8, func_001d06f0, func_001d07a8,
    func_001d07e0, func_001d0818, func_001d0908, func_001d09d8,
    func_001d0a38, func_001d0a80, func_001d0ac8, func_001c71e8,
    func_001c7700, func_001d0b68, func_001d0b90, func_001d0dd0,
    func_001d1010, func_001cc548, func_001ca0f8, func_001cea38,
    func_001ca368, func_001d1230, func_001d1348, func_001d1380,
    func_001d13c0, func_001d13e0, func_001df130, func_001df1d8,
    func_001df268, func_001ddc78, func_001ddf98, func_001df310,
    func_001d1400, func_001d1418, func_001d1428, func_001d1450,
    func_001d1478, func_001d14c8, func_001c7c18, func_001d14f0,
    func_001cc628, func_001cbfc0, func_001def20, func_001cc640,
    func_001ccbd8, func_001d1640, func_001d16a8, func_001d16c8,
    func_001d1728, func_001d1790, func_001df170, func_001df2a8,
    func_001de290, func_001de5b0, func_001e8bd8, func_001e8cf0,
    func_001d17d0, func_001d1948, func_001d1b00, func_001d1ce0,
    func_001dec10, func_001d1ef0, func_001d1f48, func_001d1fb0,
    func_001d2080, func_001d2088, func_001d2090, func_001d2270,
    func_001d2468, func_001d24f8, func_001d2588, func_001d25d8,
    func_001d2628, func_001d2668, func_001d2708, func_001d2720,
    func_001d2768, func_001d2860, func_001cf5d0, func_001e16b0,
    func_001e1748, func_001e17e0, func_001d2958, func_001d2ab8,
    func_001d2b58, func_001d2c08, func_001e3770, func_001e3ed0,
    func_001d2c68, func_001d2fd8, func_001d3040, func_001d3078,
    func_001d30e0, func_001d3118, func_001d31d8, func_001d3228,
    func_001d3248, func_001d3268, func_001d32f0, func_001d3338,
    func_001d33c8, func_001d3430, func_001d3468, func_001d3490,
    func_001d34b0, func_001d3558, func_001d32a8, func_001d35a0,
    func_001e24c8, func_001e25c8, func_001e25e8, func_001e2668,
    func_001e26b8, func_001e83f8, func_001e8608, func_001e7ea8,
    func_001e8770, func_001d3610, func_001de4e8, func_001df568,
    func_001e0220, func_001e0318, func_001d3858, func_001d38d0,
    func_001d39b0, func_001d3a28, func_001d3a48, func_001d3a78,
    func_001d3aa8, func_001d3b20, func_001d3b80, func_001d3bb0,
    func_001e4790, func_001d3c28, func_001d3c70, func_001d3cb8,
    func_001d3d08, func_001d3d58, func_001d3da8, func_001e79a0,
    func_001e7ad8, func_001e7e00, func_001d3de8, func_001d3e08,
    func_001d3ff0, func_001d40b0, func_001e2628, func_001e9310,
    func_001d40f0, func_001d4168, func_001d41e0, func_001d4258,
    func_001d42f0, func_001d4358, func_001d44b8, func_001d44f8,
    func_001d4538, func_001d4578, func_001d4610, func_001d4690,
    func_001d24b0, func_001d2540, func_001d4710, func_001d4798,
    func_001ea438, func_001ea470, func_001d0600, func_001d0660,
    func_001d4ac8, func_001d4b38, func_001d4b60, func_001d4c08,
    func_001d4cb8, func_001d4d68, func_001d4de0, func_001ca5f8,
    func_001ca680, func_001ca708, func_001d4e10, func_001d4e60,
    func_001d4f10, func_001d4fc0, func_001d5010, func_001d5168,
    func_001d5278, func_001d52c0, func_001d5350, func_001d5408,
    func_001d5458, func_001d54a8, func_001d54d8, func_001d5500,
    func_001d5528, func_001d5550, func_001d5578, func_001d55a0,
    func_001d3380, func_001d5618, func_001d56a8, func_001ea808,
    func_001ea888, func_001d56f0, func_001d5738, func_001d5780,
    func_001d57d0, func_001d5828, func_001d5850, func_001d5878,
    func_001d58c8, func_001d5978, func_001d5a50, func_001d59a0,
    func_001df630, func_001df708, func_001d5b00, func_001d5b58,
    func_001d5ed8, func_001e8c88, func_001d5f18, func_001d5f58,
    func_001d5f80, func_001d5fa8, func_001cb738, func_001cb7d0,
    func_001d5ff0, func_001d6038, func_001d6080, func_001d60c0,
    func_001d6100, func_001ccbf8, func_001d6128, func_001d6180,
    func_001d61c8, func_001d6210, func_001d6230, func_001de328,
    func_001de420, func_001df3a8, func_001df4a0, func_001ea908,
    func_001ea9c8, func_001ea6b8, func_001ea760, func_001d3948,
    func_001de558, func_001df5d8, func_001d6250, func_001d6348,
    func_001e8f68, func_001e9028, func_001d63e8, func_001d64f8,
    func_001d6558, func_001d65b8, func_001e90d0, func_001e9108,
    func_001d6600, func_001d3be8, func_001ca790, func_001ca7c8,
    func_001d6658, func_001d66b8, func_001d66d8, func_001d66f8,
    func_001d6718, func_001d6760, func_001d6780, func_001d67c8,
    func_001d5388, func_001e80d0, func_001e82e0, func_001d6810,
    func_001d6858, func_001e9048, func_001e89c0, func_001d6978,
    func_001d69d0, func_001d6a20, func_001d6a40, func_001e89e0,
    func_001d6a60, func_001d6bf8, func_001d6c08, func_001d1890,
    func_001d1a28, func_001d1bf8, func_001d1df0, func_001d6c20,
    func_001d6c48, func_001e9190, func_001d6c80, func_001e8a50,
    func_001d6d60, func_001d6db0, func_001d6dd0, func_001d6df0,
    func_001d6e10, func_001d6e30, func_001d6e50, func_001e9150,
    func_001e9170, func_001d6e70, func_001d6ef0, func_001d6f38,
    func_001d6f60, func_001d6f70, func_001d6f90, func_001e0528,
    func_001d6fb0, func_001d6ff8, func_001de910, func_001ded08,
    func_001d7040, func_001d7118, func_001d7220, func_001d7238,
    func_001d7258, func_001d7320, func_001d7438, func_001d7520,
    func_001e5d78, func_001d7548, func_001d75d0, func_001d76c8,
    func_001d76e8, func_001d7798, func_001d7820, func_001d7840,
    func_001d7b88, func_001d7ef8, func_001d85a8, func_001d85f0,
    func_001d8638, func_001d8660, func_001d8680, func_001d86e0,
    func_001d4e38, func_001d8738, func_001d8760, func_001cccf0,
    func_001d87b8, func_001d87d8, func_001d8838, func_001d88c8,
    func_001d8910, func_001d8958, func_001d89a0, func_001d8a00,
    func_001d8a60, func_001d8ac0, func_001d8b08, func_001d8b28,
    func_001d8b48, func_001d8be0, func_001d8c00, func_001d8c30,
    func_001d8c80, func_001d8cc8, func_001d8d18, func_001d8d70,
    func_001ce020, func_001d6628, func_001d74b8, func_001d8db8,
    func_001d8e10, func_001d8e60, func_001d8eb0, func_001d7678,
    func_001e8b08, func_001e8b50, func_001e8bc0, func_001d8ef8,
    func_001d8f18, func_001d9100, func_001d9268, func_001cd748,
    func_001cd7e8, func_001cd778, func_001cd830, func_001d9480,
    func_001d95f0, func_001d0b10, func_001eb140, func_001eb278,
    func_001eb380, func_001eb4b8, func_001eb698, func_001eb910,
    func_001eba80, func_001ebba0, func_001ebd48, func_001ebde0,
    func_001d9728, func_001eb1d8, func_001ebb10, func_001eb7b0,
    func_001c9db0, func_001c9e20, func_001d9750, func_001df7e0,
    func_001df940, func_001df9c0, func_001dfa38, func_001d9780,
    func_001d9830, func_001d9850, func_001d9880, func_001d98d0,
    func_001d9950, func_001d99d0, func_001d99f8, func_001d9a50,
    func_001d9aa0, func_001d9af8, func_001d9b58, func_001d9bb0,
    func_001d9c08, func_001d9c60, func_001d9cb0, func_001d9d30,
    func_001d9d90, func_001d9dd0, func_001d9df0, func_001d9e40,
    func_001d9e90, func_001d9eb8, func_001d9ee0, func_001d9f88,
    func_001d55c8, func_001d55f0, func_001e8560, func_001e8238,
    func_001d9fb0, func_001d9ff8, func_001da040, func_001da088,
    func_001da0e8, func_001da108, func_001da128, func_001e8da0,
    func_001da178, func_001e90c8, func_001e91f0, func_001e9288,
    func_001e91c0, func_001de030, func_001da1a8, func_001da1d0,
    func_001d8b98, func_001d8b68, func_001ebf98, func_001ebf48,
    func_001d68a0, func_001d68e8, func_001d6930, func_001d6958,
    func_001eaa88, func_001eab78, func_001ec040, func_001ebff0,
    func_001da260, func_001dfaa0, func_001dfb20, func_001dfbb8,
    func_001dfcb0, func_001dfd78, func_001dfde0, func_001dfe50,
    func_001dfea8, func_001cb120, func_001da2c8, func_001e9238,
    func_001df890, func_001dffa0, func_001e0010, func_001e0078,
    func_001ce0b8, func_001da3b8, func_001da400, func_001da490,
    func_001da520, func_001da5b0, func_001da628, func_001de848,
    func_001d6cf0, func_001cdea8, func_001da740, func_001cef20,
    func_001cefb8, func_001d2018, func_001da7b8, func_001da808,
    func_001e38b0, func_001e4868, func_001da860, func_001da8b8,
    func_001da910, func_001ec0d8, func_001ec1a0, func_001d9f20,
    func_001da968, func_001de130, func_001eb558, func_001d5308,
    func_001d5330, func_001d12b8, func_001da9f0, func_001daa00,
    func_001daa18, func_001daad8, func_001dab20, func_001dab48,
    func_001ebf18, func_001dab98, func_001dabc0, func_001e8800,
    func_001e7f08, func_001dabe8, func_001de6a8, func_001de9e0,
    func_001dac40, func_001dacc8, func_001dad30, func_001e8d40,
    func_001dad58, func_001db060, func_001d0a28, func_001db080,
    func_001db0d0, func_001db140, func_001db198, func_001db208,
    func_001db278, func_001db2e0, func_001db348, func_001db3b8,
    func_001db408, func_001e3dd0, func_001db458, func_001db4a8,
    func_001db500, func_001db550, func_001db5a0, func_001db5c0,
    func_001db5e0, func_001ec3f8, func_001ec468, func_001db600,
    func_001db658, func_001db718, func_001db888, func_001db950,
    func_001db9c0, func_001db9f8, func_001dba30, func_001dba88,
    func_001e7488, func_001d8400, func_001db8e0, func_001cb440,
    func_001d43d8, func_001d4448, func_001de0b0, func_001de1e0,
    func_001dbae0, func_001dbb00, func_001dbb20, func_001dbb40,
    func_001d72e0, func_001da6d0, func_001de778, func_001deaf8,
    func_001dbb60, func_001dbba0, func_001dbbf0, func_001dbc10,
    func_001dbc38, func_001dbc90, func_001dbcd8, func_001dbd68,
    func_001dbdc8, func_001dbe50, func_001dbe78, func_001e8a10,
    func_001e8a30, func_001dbec0, func_001dbf20, func_001dbf68,
    func_001dbd20, func_001e87b8, func_001e88e0, func_001dbfb8,
    func_001ec3b0, func_001cf210, func_001e8de8, func_001dc000,
    func_001dc100, func_001dc120, func_001dde08, func_001dc140,
    func_001dc280, func_001d14a0, func_001d0868, func_001d0938,
    func_001ec678, func_001cb3c0, func_001dc2e0, func_001db018,
    func_001dc308, func_001dc358, func_001d58a0, func_001d3828,
    func_001dc3c0, func_001dc470, func_001dc520, func_001dc7c0,
    func_001d3710, func_001ccda8, func_001ccdf0, func_001dc800,
    func_001d5090, func_001d5118, func_001dc868, func_001dc8c8,
    func_001dc9a0, func_001dca00, func_001dca48,
};

s32 func_001dcad0(VmRec *vm, s32 k) {
    return D_003D9FE0[k](vm);
}
