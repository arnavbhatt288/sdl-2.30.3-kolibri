

#include "../../SDL_internal.h"

#ifndef SDL_kolibriwindow_h_
#define SDL_kolibriwindow_h_

typedef struct SDL_WindowData
{
    SDL_Surface *surface;
} SDL_WindowData;

extern int KOLIBRI_CreateWindow(_THIS, SDL_Window *window);
extern void KOLIBRI_RepaintWnd(_THIS);
extern void KOLIBRI_SetWindowTitle(_THIS, SDL_Window *window);
extern void KOLIBRI_DestroyWindow(_THIS, SDL_Window *window);

#endif
