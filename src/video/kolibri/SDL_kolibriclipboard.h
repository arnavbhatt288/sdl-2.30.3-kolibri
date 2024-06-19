
#include "../../SDL_internal.h"

#ifndef SDL_kolibriclipboard_h_
#define SDL_kolibriclipboard_h_

extern char *KOLIBRI_GetClipboardText(_THIS);
extern int KOLIBRI_SetClipboardText(_THIS, const char *text);
extern SDL_bool KOLIBRI_HasClipboardText(_THIS);

#endif
