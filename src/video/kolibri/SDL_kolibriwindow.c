
#include "../../SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KOLIBRI

#include <sys/ksys.h>

#include "../../events/SDL_keyboard_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../SDL_sysvideo.h"
#include "SDL_syswm.h"

#include "SDL_kolibrivideo.h"
#include "SDL_kolibriwindow.h"

static int pid = 0;

void KOLIBRI_RepaintWnd(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->driverdata;
    SDL_Window *window = SDL_GetWindowFromID(data->window_id);
    SDL_WindowData *wdata = (SDL_WindowData *)window->driverdata;
    int win_pos_x, win_pos_y;
    int win_size_w, win_size_h;

    win_size_w = window->w;
    win_size_h = window->h;
    if (wdata->skin == 0x33 || wdata->skin == 0x34) {
        win_size_w += TRUE_WIN_WIDTH;
        win_size_h += TRUE_WIN_HEIGHT;
    }

    _ksys_start_draw();
    _ksys_create_window(window->x, window->y, win_size_w, win_size_h, window->title, 0, wdata->skin);
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

    wdata->skin = 0x34;
    _ksys_set_event_mask(0x27);
    KOLIBRI_RepaintWnd(_this);

    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);

    return 0;
}

void KOLIBRI_MaximizeWindow(_THIS, SDL_Window *window)
{
    // TODO
}

void KOLIBRI_MinimizeWindow(_THIS, SDL_Window *window)
{
    ksys_thread_t thread_info;

    _ksys_thread_info(&thread_info, KSYS_THIS_SLOT);
    pid = thread_info.pid;
    asm_inline("int $0x40" ::"a"(18), "b"(22), "c"(1), "d"(pid));
}

void KOLIBRI_RestoreWindow(_THIS, SDL_Window *window)
{
    asm_inline("int $0x40" ::"a"(18), "b"(22), "c"(3), "d"(pid));
}

void KOLIBRI_SetWindowFullscreen(_THIS, SDL_Window *window, SDL_VideoDisplay *_display, SDL_bool fullscreen)
{
    SDL_WindowData *wdata = (SDL_WindowData *)window->driverdata;
    static int old_w, old_h, old_x, old_y;
    static unsigned char old_skin;
    if (fullscreen) {
        old_w = window->w + (TRUE_WIN_WIDTH - 1);
        old_h = window->h + (TRUE_WIN_HEIGHT - 1);
        old_x = window->x;
        old_y = window->y;
        old_skin = wdata->skin;

        wdata->skin = 0x01;
        _ksys_change_window(0, 0, _ksys_screen_size().x + 1, _ksys_screen_size().y + 1);
    } else {
        wdata->skin = old_skin;
        _ksys_change_window(old_x, old_y, old_w, old_h);
    }
}

void KOLIBRI_SetWindowPosition(_THIS, SDL_Window *window)
{
    _ksys_change_window(window->x, window->y, window->w + (TRUE_WIN_WIDTH - 1), window->h + (TRUE_WIN_HEIGHT - 1));
}

void KOLIBRI_SetWindowResizable(_THIS, SDL_Window *window, SDL_bool resizable)
{
    SDL_WindowData *wdata = (SDL_WindowData *)window->driverdata;

    if (resizable)
        wdata->skin = 0x33;
    else
        wdata->skin = 0x34;
    KOLIBRI_RepaintWnd(_this);
}

void KOLIBRI_SetWindowSize(_THIS, SDL_Window *window)
{
    _ksys_change_window(window->x, window->y, window->w + (TRUE_WIN_WIDTH - 1), window->h + (TRUE_WIN_HEIGHT - 1));
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

SDL_bool KOLIBRI_GetWindowWMInfo(_THIS, SDL_Window *window, struct SDL_SysWMinfo *info)
{
    /* What is the point of this? What information should be included? */
    if (info->version.major == SDL_MAJOR_VERSION) {
        info->subsystem = SDL_SYSWM_KOLIBRI;
        return SDL_TRUE;
    } else {
        SDL_SetError("Application not compiled with SDL %d", SDL_MAJOR_VERSION);
        return SDL_FALSE;
    }
}

#endif /* SDL_VIDEO_DRIVER_KOLIBRI */
