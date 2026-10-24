/* Declarations of the SCE SIF RPC calls (libkernl's sifrpc) as linked into
 * the game ELF.  Hand-written from the public function signatures; no SDK
 * headers are copied into this repository. Addresses are in functions.tsv. */
#ifndef KH1_SCE_SIFRPC_H
#define KH1_SCE_SIFRPC_H

typedef struct sceSifClientData sceSifClientData;  /* 0x28 bytes, owned by the caller */

void sceSifInitRpc(unsigned int mode);
int sceSifBindRpc(sceSifClientData *client, unsigned int rpc_number, unsigned int mode);
int sceSifCallRpc(sceSifClientData *client, unsigned int rpc_number, unsigned int mode, void *send, int ssize,
                  void *receive, int rsize, void (*end_func)(void *), void *end_param);

#endif /* KH1_SCE_SIFRPC_H */
