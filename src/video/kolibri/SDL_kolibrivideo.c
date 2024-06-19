
#include "../../SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KOLIBRI

#include <sys/ksys.h>

#include "../../events/SDL_events_c.h"
#include "../SDL_pixels_c.h"
#include "../SDL_sysvideo.h"
#include "SDL_video.h"

#include "SDL_kolibriclipboard.h"
#include "SDL_kolibrievents.h"
#include "SDL_kolibriframebuffer.h"
#include "SDL_kolibrimouse.h"
#include "SDL_kolibrivideo.h"
#include "SDL_kolibriwindow.h"

#define KOLIBRIVID_DRIVER_NAME "kolibri"

static void KOLIBRI_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->driverdata);
    SDL_free(device);
}

int KOLIBRI_VideoInit(_THIS)
{
    SDL_DisplayMode mode;
    SDL_VideoData *data = _this->driverdata;
    data->screen_size = _ksys_screen_size();

    /* Use 24-bpp desktop mode */
    mode.format = SDL_PIXELFORMAT_RGB24;
    mode.w = data->screen_size.x;
    mode.h = data->screen_size.y;
    mode.refresh_rate = 0;
    mode.driverdata = NULL;
    if (SDL_AddBasicVideoDisplay(&mode) < 0)
        return -1;

    SDL_zero(mode);
    SDL_AddDisplayMode(&_this->displays[0], &mode);

    KOLIBRI_InitMouse();
    KOLIBRI_InitOSKeymap();

    /* We're done! */
    return 0;
}

static int KOLIBRI_SetDisplayMode(_THIS, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    return 0;
}

void KOLIBRI_VideoQuit(_THIS)
{
}

static SDL_VideoDevice *KOLIBRI_CreateDevice(void)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *)SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        return 0;
    }

    /* Initialize internal Kolibri specific data */
    data = (SDL_VideoData *)SDL_calloc(1, sizeof(SDL_VideoData));
    if (!data) {
        SDL_OutOfMemory();
        SDL_free(device);
        return 0;
    }

    /* General video */
    device->VideoInit = KOLIBRI_VideoInit;
    device->VideoQuit = KOLIBRI_VideoQuit;
    device->SetDisplayMode = KOLIBRI_SetDisplayMode;
    device->PumpEvents = KOLIBRI_PumpEvents;
    device->free = KOLIBRI_DeleteDevice;

    /* Framebuffer */
    device->CreateWindowFramebuffer = KOLIBRI_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = KOLIBRI_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = KOLIBRI_DestroyWindowFramebuffer;

    /* "Window" */
    device->CreateSDLWindow = KOLIBRI_CreateWindow;
    device->SetWindowTitle = KOLIBRI_SetWindowTitle;
    device->DestroyWindow = KOLIBRI_DestroyWindow;

    /* Clipboard */
    device->HasClipboardText = KOLIBRI_HasClipboardText;
    device->GetClipboardText = KOLIBRI_GetClipboardText;
    device->SetClipboardText = KOLIBRI_SetClipboardText;

    /* KolibriOS specific data */
    device->driverdata = data;

    return device;
}

VideoBootStrap KOLIBRI_bootstrap = {
    KOLIBRIVID_DRIVER_NAME, "SDL kolibri video driver",
    KOLIBRI_CreateDevice,
    NULL /* no ShowMessageBox implementation */
};

#endif
