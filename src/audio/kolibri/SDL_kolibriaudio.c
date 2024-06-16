#include "../../SDL_internal.h"

#ifdef SDL_AUDIO_DRIVER_KOLIBRI

#include <sound.h>
#include <sys/ksys.h>

#include "SDL_audio.h"

#include "../SDL_audio_c.h"
#include "../SDL_audiodev_c.h"

#include "SDL_kolibriaudio.h"

/* The tag name used by Kolibri audio */
#define AUDIO_THREAD_STACK_SIZE  40960
#define KOLIBRIAUDIO_DRIVER_NAME "kolibri"

/* Variables required for spawning a thread for audio */
static ksys_thread_t thread_info;
static int main_slot;
static uint32_t main_tid;
static uint32_t thread_stack[AUDIO_THREAD_STACK_SIZE];
static SDL_AudioDevice *global_device;

static void kolibri_audio_callback(void)
{
    ksys_signal_info_t snd_signal;
    SDL_AudioDevice *this;
    SDL_AudioCallback callback;

    int bPaused;
    char str[100];

    // initialize
    this = global_device;
    callback = this->spec.callback;

    if (CreateBuffer(private->used_format | PCM_RING, 0, &private->hBuff)) {
        private->audio_response = 1;
        exit(0);
    }

    GetBufferSize(private->hBuff, &this->spec.size);
    sprintf(str, "buffer created, size is %d\n", this->spec.size);
    _ksys_debug_puts(str);

    this->spec.size >>= 1;
    this->work_buffer = SDL_calloc(1, this->spec.size);
    private->audio_response = 1;
    if (!this->work_buffer) {
        DestroyBuffer(private->hBuff);
        exit(0);
    }

    // wait for resume
    while (SDL_AtomicGet(&this->paused))
        _ksys_thread_yield();
    _ksys_debug_puts("audio_thread created\n");

    bPaused = 0;
    private->audio_response = 1;
    PlayBuffer(private->hBuff, 0);

    // main loop
    while (1) {
        if (!SDL_AtomicGet(&this->paused)) {
            PlayBuffer(private->hBuff, 0);
            bPaused = 0;
            private->audio_response = 1;
        } else if (SDL_AtomicGet(&this->paused)) {
            StopBuffer(private->hBuff);
            bPaused = 1;
            private->audio_response = 1;
        } else if (SDL_AtomicGet(&this->shutdown)) {
            private->audio_response = 1;
            StopBuffer(private->hBuff);
            DestroyBuffer(private->hBuff);
            exit(0);
        } else {
            _ksys_thread_info(&thread_info, main_slot);
            if (thread_info.slot_state == KSYS_SLOT_STATE_FREE || thread_info.pid != main_tid) {
                SDL_AtomicSet(&this->shutdown, 1);
                continue;
            }
        }
        if (bPaused) {
            _ksys_delay(5);
        } else {
            _ksys_wait_signal(&snd_signal);
            if (snd_signal.id != 0xFF000001)
                continue;
            callback(this->spec.userdata, this->work_buffer, this->spec.size);
            SetBuffer(private->hBuff, this->work_buffer, ((int *)snd_signal.data)[2], this->spec.size);
        }
    }
}

static void KOLIBRIAUDIO_CloseDevice(SDL_AudioDevice *device)
{
    if (device->hidden->audio_tid)
        return;

    device->hidden->audio_response = 0;
    while (!device->hidden->audio_response)
        _ksys_thread_yield();

    SDL_free(device->work_buffer);
    SDL_free(device->hidden);
}

static int KOLIBRIAUDIO_OpenDevice(_THIS, const char *devname)
{
    int ver;
    char buff[100];

    if (InitSound(&ver)) {
        _ksys_debug_puts("Error: cannot load drivers!\n");
        return -1;
    }

    private = (SDL_PrivateAudioData *)SDL_calloc(1, sizeof(*private));
    if (!private) {
        return SDL_OutOfMemory();
    }

    switch (this->spec.freq) {

#define HANDLE_FREQ(freq, symb)                  \
    case freq:                                   \
        switch (this->spec.channels) {           \
        case 1:                                  \
            switch (this->spec.format) {         \
            case AUDIO_U8:                       \
            case AUDIO_S8:                       \
                private->used_format = PCM_1_8_##symb;  \
                break;                           \
            case AUDIO_U16SYS:                   \
            case AUDIO_S16SYS:                   \
                private->used_format = PCM_1_16_##symb; \
                break;                           \
            }                                    \
            break;                               \
        case 2:                                  \
            switch (this->spec.format) {         \
            case AUDIO_U8:                       \
            case AUDIO_S8:                       \
                private->used_format = PCM_2_8_##symb;  \
                break;                           \
            case AUDIO_U16SYS:                   \
            case AUDIO_S16SYS:                   \
                private->used_format = PCM_2_16_##symb; \
                break;                           \
            }                                    \
            break;                               \
        }                                        \
        break;

        HANDLE_FREQ(48000, 48);
        HANDLE_FREQ(44100, 44);
        HANDLE_FREQ(32000, 32);
        HANDLE_FREQ(24000, 24);
        HANDLE_FREQ(22050, 22);
        HANDLE_FREQ(16000, 16);
        HANDLE_FREQ(12000, 12);
        HANDLE_FREQ(11025, 11);
        HANDLE_FREQ(8000, 8);
    }

    if (!private->used_format) {
        _ksys_debug_puts("Unknown audio format");
        return -1;
    }

    _ksys_thread_info(&thread_info, KSYS_THIS_SLOT);
    main_tid = thread_info.pid;
    for (main_slot = 0;; main_slot++) {
        _ksys_thread_info(&thread_info, main_slot);
        if (thread_info.slot_state != KSYS_SLOT_STATE_FREE && thread_info.pid == main_tid)
            break;
    }

    global_device = this;
    private->audio_tid = _ksys_create_thread(kolibri_audio_callback, thread_stack + AUDIO_THREAD_STACK_SIZE);
    if (private->audio_tid < 0) {
        _ksys_debug_puts("Cannot create audio thread");
        return -1;
    }

    _ksys_focus_window(main_slot);
    while (!private->audio_response)
        _ksys_thread_yield();

    if (!private->hBuff) {
        _ksys_debug_puts("Cannot create audio buffer");
        return -1;
    }
    if (!this->work_buffer) {
        _ksys_debug_puts("Cannot allocate audio buffer");
        return -1;
    }

    this->spec.silence = (this->spec.format == AUDIO_U8 ? 0x80 : 0);
    this->spec.samples = this->spec.size / this->spec.channels;
    if (this->spec.format == AUDIO_U16SYS || this->spec.format == AUDIO_S16SYS)
        this->spec.samples /= 2;

    sprintf(buff, "obtained size is %d, samples %d\n", this->spec.size, this->spec.samples);
    _ksys_debug_puts(buff);

    return 0;
}

static SDL_bool KOLIBRIAUDIO_Init(SDL_AudioDriverImpl *impl)
{
    impl->CloseDevice = KOLIBRIAUDIO_CloseDevice;
    impl->OpenDevice = KOLIBRIAUDIO_OpenDevice;
    impl->OnlyHasDefaultOutputDevice = SDL_TRUE;
    impl->ProvidesOwnCallbackThread = SDL_TRUE;

    return SDL_TRUE;
}

AudioBootStrap KOLIBRIAUDIO_bootstrap = {
    KOLIBRIAUDIO_DRIVER_NAME, "Kolibri Audio Driver",
    KOLIBRIAUDIO_Init, SDL_FALSE
};

#endif
