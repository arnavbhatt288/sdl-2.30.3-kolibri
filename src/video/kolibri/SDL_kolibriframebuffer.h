
#include "../../SDL_internal.h"

#ifndef SDL_kolibriframebuffer_h_
#define SDL_kolibriframebuffer_h_

extern int SDL_KOLIBRI_CreateWindowFramebuffer(_THIS, SDL_Window *window, Uint32 *format, void **pixels, int *pitch);
extern int SDL_KOLIBRI_UpdateWindowFramebuffer(_THIS, SDL_Window *window, const SDL_Rect *rects, int numrects);
extern void SDL_KOLIBRI_DestroyWindowFramebuffer(_THIS, SDL_Window *window);

#endif
