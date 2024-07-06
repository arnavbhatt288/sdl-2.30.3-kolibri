
#include "../../SDL_internal.h"

#ifndef SDL_kolibriclipboard_h_
#define SDL_kolibriclipboard_h_

char *KOLIBRI_GetClipboardText(_THIS);
int KOLIBRI_SetClipboardText(_THIS, const char *text);
SDL_bool KOLIBRI_HasClipboardText(_THIS);

#endif /* SDL_kolibriclipboard_h_ */
