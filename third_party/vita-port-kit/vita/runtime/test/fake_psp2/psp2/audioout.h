#ifndef FAKE_PSP2_AUDIOOUT_H
#define FAKE_PSP2_AUDIOOUT_H
typedef enum { SCE_AUDIO_OUT_PORT_TYPE_MAIN = 0, SCE_AUDIO_OUT_PORT_TYPE_BGM = 1 } SceAudioOutPortType;
typedef enum { SCE_AUDIO_OUT_MODE_MONO = 0, SCE_AUDIO_OUT_MODE_STEREO = 1 } SceAudioOutMode;
typedef enum { SCE_AUDIO_VOLUME_FLAG_L_CH = 1, SCE_AUDIO_VOLUME_FLAG_R_CH = 2 } SceAudioOutChannelFlag;
#define SCE_AUDIO_VOLUME_0DB 32768
int sceAudioOutOpenPort(SceAudioOutPortType type, int len, int freq, SceAudioOutMode mode);
int sceAudioOutReleasePort(int port);
int sceAudioOutOutput(int port, const void *buf);
int sceAudioOutSetVolume(int port, SceAudioOutChannelFlag ch, int *vol);
#endif
