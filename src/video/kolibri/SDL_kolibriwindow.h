

#include "../../SDL_internal.h"

#ifndef SDL_kolibriwindow_h_
#define SDL_kolibriwindow_h_

#define WINDOW_BORDER_H 4
#define WINDOW_BORDER_W 9

#define TRUE_WIN_HEIGHT _ksys_get_skin_height() + WINDOW_BORDER_H;
#define TRUE_WIN_WIDTH  WINDOW_BORDER_W

typedef struct SDL_WindowData
{
    SDL_Surface *surface;
    unsigned char skin;
} SDL_WindowData;

extern void KOLIBRI_RepaintWnd(_THIS);
extern int KOLIBRI_CreateWindow(_THIS, SDL_Window *window);
extern void KOLIBRI_SetWindowTitle(_THIS, SDL_Window *window);
extern void KOLIBRI_DestroyWindow(_THIS, SDL_Window *window);

#endif /* SDL_kolibriwindow_h_ */
