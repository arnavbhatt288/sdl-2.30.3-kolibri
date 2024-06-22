
#include "../../SDL_internal.h"

#ifdef SDL_TIMER_KOLIBRI

#include <sys/ksys.h>

#include "SDL_timer.h"

static uint64_t start_tick;
static SDL_bool ticks_started = SDL_FALSE;

void SDL_TicksInit(void)
{
    if (ticks_started)
        return;

    ticks_started = SDL_TRUE;

    /* Set first ticks value */
    start_tick = _ksys_get_ns_count();
}

void SDL_TicksQuit(void)
{
    ticks_started = SDL_FALSE;
}

Uint64 SDL_GetTicks64(void)
{
    uint64_t elapsed;
    if (!ticks_started) {
        SDL_TicksInit();
    }

    return (Uint64)((_ksys_get_ns_count() - start_tick) / 1000000);
}

Uint64 SDL_GetPerformanceCounter(void)
{
    return _ksys_get_ns_count();
}

Uint64 SDL_GetPerformanceFrequency(void)
{
    return 1000000000;
}

void SDL_Delay(Uint32 ms)
{
    _ksys_delay((uint32_t)(ms / 10 + (ms % 10 > 0)));
}

#endif /* SDL_TIMER_KOLIBRI */
