
#include "../../SDL_internal.h"

#ifndef SDL_kolibrimouse_h_
#define SDL_kolibrimouse_h_

typedef struct _KOLIBRI_CursorData
{
    int has_null_cursor;
    void *cursor;
    void *null_cursor;
} KOLIBRI_CursorData;

extern void KOLIBRI_InitMouse(void);

#endif
