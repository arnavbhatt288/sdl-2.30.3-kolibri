
#include "../../SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KOLIBRI

#include <sys/ksys.h>

#include "SDL_hints.h"
#include "SDL_surface.h"

#include "../../events/SDL_mouse_c.h"
#include "../../events/default_cursor.h"
#include "../SDL_sysvideo.h"

#include "SDL_kolibrimouse.h"
#include "SDL_kolibrivideo.h"

static SDL_Cursor *KOLIBRI_CreateDefaultCursor(void)
{
    KOLIBRI_CursorData *curdata;
    SDL_Cursor *cursor;
    Uint32 *temp;

    cursor = (SDL_Cursor *)SDL_calloc(1, sizeof(*cursor));
    if (!cursor) {
        SDL_OutOfMemory();
        return NULL;
    }
    curdata = (KOLIBRI_CursorData *)SDL_calloc(1, sizeof(*curdata));
    if (!curdata) {
        SDL_OutOfMemory();
        SDL_free(cursor);
        return NULL;
    }

    /* Convert default SDL cursor to 32x32 */
    temp = (Uint32 *)SDL_malloc(32 * 32 * 4);
    if (!temp)
        return NULL;
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            if (i >= 16 || j >= 16) {
                temp[i * 32 + j] = 0x00000000;
                continue;
            }
            if (default_cmask[i * 16 / 8 + j / 8] & (0x80 >> (j & 7)))
                temp[i * 32 + j] = (default_cdata[i * 16 / 8 + j / 8] & (0x80 >> (j & 7)))
                                       ? 0xFF000000
                                       : 0xFFFFFFFF;
            else
                temp[i * 32 + j] = 0x00000000;
        }
    }

    curdata->cursor = _ksys_load_cursor(temp, (DEFAULT_CHOTX << 24) + (DEFAULT_CHOTY << 16) + KSYS_CURSOR_INDIRECT);
    cursor->driverdata = curdata;
    SDL_free(temp);

    return cursor;
}

/* Create a cursor from a surface */
static SDL_Cursor *KOLIBRI_CreateCursor(SDL_Surface *surface, int hot_x, int hot_y)
{
    KOLIBRI_CursorData *curdata;
    SDL_Cursor *cursor;
    int i, j;

    /* Size of cursor must be 32x32 */
    if (surface->w == 32 || surface->h == 32) {
        SDL_SetError("Size of the cursor must be 32x32");
        return NULL;
    }

    cursor = (SDL_Cursor *)SDL_calloc(1, sizeof(*cursor));
    if (!cursor) {
        SDL_OutOfMemory();
        return NULL;
    }
    curdata = (KOLIBRI_CursorData *)SDL_calloc(1, sizeof(*curdata));
    if (!curdata) {
        SDL_OutOfMemory();
        SDL_free(cursor);
        return NULL;
    }

    curdata->cursor = _ksys_load_cursor(surface->pixels, (hot_x << 24) + (hot_y << 16) + KSYS_CURSOR_INDIRECT);
    cursor->driverdata = curdata;

    return cursor;
}

static int KOLIBRI_ShowCursor(SDL_Cursor *cursor)
{
    KOLIBRI_CursorData *curdata;
    if (cursor) {
        curdata = (KOLIBRI_CursorData *)cursor->driverdata;
        if (!curdata->cursor) {
            if (!curdata->has_null_cursor) {
                unsigned *u = SDL_malloc(32 * 32 * 4);
                if (!u)
                    return 0;
                SDL_memset(u, 0, 32 * 32 * 4);
                curdata->null_cursor = _ksys_load_cursor(u, KSYS_CURSOR_INDIRECT);
                free(u);
                curdata->has_null_cursor = 1;
            }
            curdata->cursor = curdata->null_cursor;
        }
        _ksys_set_cursor(curdata->cursor);
    }

    return 0;
}

static void KOLIBRI_FreeCursor(SDL_Cursor *cursor)
{
    KOLIBRI_CursorData *curdata;

    if (cursor) {
        curdata = (KOLIBRI_CursorData *)cursor->driverdata;
        if (curdata) {
            SDL_free(curdata->cursor);
            SDL_free(curdata);
        }
        SDL_free(cursor);
    }
}

void KOLIBRI_InitMouse(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = KOLIBRI_CreateCursor;
    mouse->ShowCursor = KOLIBRI_ShowCursor;
    mouse->FreeCursor = KOLIBRI_FreeCursor;

    SDL_SetDefaultCursor(KOLIBRI_CreateDefaultCursor());
}

#endif
