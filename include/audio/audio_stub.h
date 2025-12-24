#ifndef AUDIO_AUDIO_STUB_H
#define AUDIO_AUDIO_STUB_H

void audioInit(void);
void audioShutdown(void);
void audioPlayMusic(const char* filename);
void audioPlaySound(const char* filename);
void audioSetMusicVolume(float volume);
void audioSetSoundVolume(float volume);

#endif
