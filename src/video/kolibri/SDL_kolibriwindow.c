
#include "../../SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KOLIBRI

#include <sys/ksys.h>

#include "../../events/SDL_keyboard_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../SDL_sysvideo.h"

#include "SDL_kolibrivideo.h"
#include "SDL_kolibriwindow.h"

#define WINDOW_BORDER_H 4
#define WINDOW_BORDER_W 9

void KOLIBRI_RepaintWnd(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->driverdata;
    SDL_Window *window = SDL_GetWindowFromID(data->window_id);
    SDL_WindowData *wdata = (SDL_WindowData *)window->driverdata;
    int win_pos_x, win_pos_y;
    int win_size_w, win_size_h;

    win_size_w = window->w + WINDOW_BORDER_W;
    win_size_h = window->h + _ksys_get_skin_height() + WINDOW_BORDER_H;
    win_pos_x = data->screen_size.x / 2 - win_size_w / 2;
    win_pos_y = data->screen_size.y / 2 - win_size_h / 2;

    _ksys_start_draw();
    _ksys_create_window(win_pos_x, win_pos_y, win_size_w, win_size_h, window->title, 0, 0x34);
    if (wdata->surface->pixels)
        _ksys_draw_bitmap(wdata->surface->pixels, 0, 0, wdata->surface->w, wdata->surface->h);
    _ksys_end_draw();
}

int KOLIBRI_CreateWindow(_THIS, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->driverdata;
    SDL_WindowData *wdata;

    /* Allocate window internal data */
    wdata = (SDL_WindowData *)SDL_calloc(1, sizeof(SDL_WindowData));
    if (!wdata)
        return SDL_OutOfMemory();

    /* Setup driver data for this window */
    window->driverdata = wdata;
    data->window_id = SDL_GetWindowID(window);

    _ksys_set_event_mask(0x27);
    KOLIBRI_RepaintWnd(_this);

    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);

    return 0;
}

void KOLIBRI_SetWindowTitle(_THIS, SDL_Window *window)
{
    _ksys_set_window_title(window->title);
}

void KOLIBRI_DestroyWindow(_THIS, SDL_Window *window)
{
    if (!window)
        return;
    SDL_free(window->driverdata);
}

#endif
