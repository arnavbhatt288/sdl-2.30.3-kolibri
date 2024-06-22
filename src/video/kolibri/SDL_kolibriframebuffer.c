
#include "../../SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KOLIBRI

#include <sys/ksys.h>

#include "SDL.h"

#include "../SDL_sysvideo.h"

#include "SDL_kolibriframebuffer.h"
#include "SDL_kolibrivideo.h"
#include "SDL_kolibriwindow.h"

void FreeOldFramebuffer(SDL_Window *window)
{
    SDL_WindowData *data = (SDL_WindowData *)window->driverdata;
    SDL_FreeSurface(data->surface);
}

int KOLIBRI_CreateWindowFramebuffer(_THIS, SDL_Window *window, Uint32 *format, void **pixels, int *pitch)
{
    SDL_WindowData *data = (SDL_WindowData *)window->driverdata;
    SDL_Surface *surface;
    const Uint32 surface_format = SDL_PIXELFORMAT_RGB24;
    int w, h;

    /* Free the old framebuffer surface */
    FreeOldFramebuffer(window);

    /* Create a new one */
    SDL_GetWindowSizeInPixels(window, &w, &h);
    surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 0, surface_format);
    if (!surface)
        return -1;

    /* Save the info and return! */
    data->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;

#ifdef DEBUG_VIDEO
    char *info;

    SDL_asprintf(&info, "width = %d, height = %d, pitch = %d, bpp = %d\n", window->w,
                 window->h, surface->pitch, surface_format);
    _ksys_debug_puts(info);
    SDL_free(info);
#endif
    return 0;
}

int KOLIBRI_UpdateWindowFramebuffer(_THIS, SDL_Window *window, const SDL_Rect *rects, int numrects)
{
    SDL_WindowData *data = (SDL_WindowData *)window->driverdata;
    SDL_Surface *surface;

    static int frame_number;

    surface = data->surface;
    if (!surface)
        return SDL_SetError("Couldn't find surface for window");

    /* Send the data to the display */
    _ksys_draw_bitmap(surface->pixels, 0, 0, surface->w, surface->h);
}

void KOLIBRI_DestroyWindowFramebuffer(_THIS, SDL_Window *window)
{
    SDL_WindowData *data = (SDL_WindowData *)window->driverdata;
    SDL_Surface *surface;

    SDL_FreeSurface(data->surface);
    data->surface = NULL;
}

#endif /* SDL_VIDEO_DRIVER_KOLIBRI */
