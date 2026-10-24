/* Declarations of SCE libdma functions as linked into the game ELF.
 * Hand-written from the public function signatures; no SDK headers are
 * copied into this repository. Addresses are in functions.tsv (named in
 * session 56 from their code, docs/sdk.md "Session 56"). */
#ifndef KH1_SCE_LIBDMA_H
#define KH1_SCE_LIBDMA_H

/* A channel's registers (CHCR at +0x00, MADR +0x10, QWC +0x20, TADR +0x30,
 * ASR0 +0x40, ASR1 +0x50, SADR +0x80); the game only passes it back. */
typedef struct sceDmaChan sceDmaChan;

sceDmaChan *sceDmaGetChan(int id);
void sceDmaSend(sceDmaChan *d, void *tag);

#endif /* KH1_SCE_LIBDMA_H */
