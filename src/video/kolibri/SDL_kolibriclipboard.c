
#include "../../SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KOLIBRI

#include <sys/ksys.h>

#define string_length(x) SDL_strlen(x) + 1

#include "../SDL_sysvideo.h"

char *KOLIBRI_GetClipboardText(_THIS)
{
    int clip_num = _ksys_clip_num();
    char *clip_buf, *result;

    if (clip_num > 0) {
        clip_buf = _ksys_clip_get(clip_num - 1);
        if ((int)*clip_buf > 0 && (int)*(clip_buf + 4) == KSYS_CLIP_TEXT && ((int)*(clip_buf + 8) == KSYS_CLIP_CP866)) {
            char *clip_text = clip_buf + 12;

            result = SDL_calloc((int)*clip_buf, sizeof(char));
            SDL_strlcpy(result, clip_text, (int)*clip_buf);
            _ksys_free(clip_buf);
        }
    }
    if (!result)
        result = SDL_strdup("");

    return result;
}

int KOLIBRI_SetClipboardText(_THIS, const char *text)
{
    char *temp_buffer = SDL_calloc(string_length(text) + 12, sizeof(char));

    *temp_buffer = string_length(text);
    *(temp_buffer + 4) = KSYS_CLIP_TEXT;
    *(temp_buffer + 8) = KSYS_CLIP_CP866;

    SDL_strlcpy(temp_buffer + 12, text, string_length(text));
    _ksys_clip_set(string_length(text) + 12, temp_buffer);
    SDL_free(temp_buffer);

    return 0;
}

SDL_bool KOLIBRI_HasClipboardText(_THIS)
{
    SDL_bool result = SDL_FALSE;
    char *text = KOLIBRI_GetClipboardText(_this);
    if (text) {
        result = text[0] != '\0' ? SDL_TRUE : SDL_FALSE;
        SDL_free(text);
    }

    return result;
}

#endif /* SDL_VIDEO_DRIVER_KOLIBRI */
