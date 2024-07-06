

#include "../../SDL_internal.h"

#ifndef SDL_kolibriwindow_h_
#define SDL_kolibriwindow_h_

#define WINDOW_BORDER_H 4
#define WINDOW_BORDER_W 9

#define TRUE_WIN_HEIGHT _ksys_get_skin_height() + WINDOW_BORDER_H
#define TRUE_WIN_WIDTH  WINDOW_BORDER_W

typedef struct SDL_WindowData
{
    SDL_Surface *surface;
    unsigned char skin;
} SDL_WindowData;

void KOLIBRI_RepaintWnd(_THIS);
int KOLIBRI_CreateWindow(_THIS, SDL_Window *window);
void KOLIBRI_MaximizeWindow(_THIS, SDL_Window *window);
void KOLIBRI_MinimizeWindow(_THIS, SDL_Window *window);
void KOLIBRI_RestoreWindow(_THIS, SDL_Window *window);
void KOLIBRI_SetWindowFullscreen(_THIS, SDL_Window *window, SDL_VideoDisplay *_display, SDL_bool fullscreen);
void KOLIBRI_SetWindowPosition(_THIS, SDL_Window *window);
void KOLIBRI_SetWindowResizable(_THIS, SDL_Window *window, SDL_bool resizable);
void KOLIBRI_SetWindowSize(_THIS, SDL_Window *window);
void KOLIBRI_SetWindowTitle(_THIS, SDL_Window *window);
void KOLIBRI_DestroyWindow(_THIS, SDL_Window *window);
SDL_bool KOLIBRI_GetWindowWMInfo(_THIS, SDL_Window *window, struct SDL_SysWMinfo *info);

#endif /* SDL_kolibriwindow_h_ */
