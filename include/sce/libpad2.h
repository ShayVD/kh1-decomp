/* Declarations of SCE libpad2 / libdbc / libvib functions as linked into
 * the game ELF (KH1 reads the controller through libpad2, not libpad).
 * Hand-written from the public function signatures; no SDK headers are
 * copied into this repository. Addresses are in functions.tsv. */
#ifndef KH1_SCE_LIBPAD2_H
#define KH1_SCE_LIBPAD2_H

int sceDbcInit(void);
int scePad2Init(int mode);
int scePad2CreateSocket(void *param, void *addr);
int scePad2GetState(int socket);
int scePad2GetButtonProfile(int socket, void *profile);
int scePad2Read(int socket, unsigned char *data);
int sceVibSetActParam(int socket, int profile_size, unsigned char *profile, int data_size, void *data);

#endif /* KH1_SCE_LIBPAD2_H */
