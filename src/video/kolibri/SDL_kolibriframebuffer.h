
#include "../../SDL_internal.h"

#ifndef SDL_kolibriframebuffer_h_
#define SDL_kolibriframebuffer_h_

extern int KOLIBRI_CreateWindowFramebuffer(_THIS, SDL_Window *window, Uint32 *format, void **pixels, int *pitch);
extern int KOLIBRI_UpdateWindowFramebuffer(_THIS, SDL_Window *window, const SDL_Rect *rects, int numrects);
extern void KOLIBRI_DestroyWindowFramebuffer(_THIS, SDL_Window *window);

#endif
