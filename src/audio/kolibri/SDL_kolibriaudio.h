
#ifndef SDL_kolibriaudio_h_
#define SDL_kolibriaudio_h_

#define _THIS   SDL_AudioDevice *this
#define private this->hidden

typedef struct SDL_PrivateAudioData
{
    SNDBUF hBuff;
    int audio_tid;
    uint32_t used_format;
    volatile int audio_response;
} SDL_PrivateAudioData;

#endif
