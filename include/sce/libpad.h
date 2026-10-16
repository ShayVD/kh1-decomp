/* Declarations of SCE libpad functions as linked into the game ELF.
 * Hand-written from the public function signatures; no SDK headers are
 * copied into this repository. Addresses go in functions.tsv once found. */
#ifndef KH1_SCE_LIBPAD_H
#define KH1_SCE_LIBPAD_H

int scePadRead(int port, int slot, unsigned char *rdata);

#endif /* KH1_SCE_LIBPAD_H */
