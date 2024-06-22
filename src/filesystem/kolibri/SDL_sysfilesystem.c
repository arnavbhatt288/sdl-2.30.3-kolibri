
#include "../../SDL_internal.h"

#ifdef SDL_FILESYSTEM_KOLIBRI

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* System dependent filesystem routines                                */

#include <sys/ksys.h>

#include "SDL_error.h"
#include "SDL_filesystem.h"

char *SDL_GetBasePath(void)
{
    char *retval = NULL;
    size_t len;
    char cwd[FILENAME_MAX];

    _ksys_getcwd(cwd, sizeof(cwd));
    len = SDL_strlen(cwd) + 2;
    retval = (char *)SDL_malloc(len);
    SDL_snprintf(retval, len, "%s/", cwd);

    return retval;
}

char *SDL_GetPrefPath(const char *org, const char *app)
{
    char *retval = NULL;
    size_t len;
    char *base = SDL_GetBasePath();
    if (!app) {
        SDL_InvalidParamError("app");
        return NULL;
    }
    if (!org) {
        org = "";
    }

    len = SDL_strlen(base) + SDL_strlen(org) + SDL_strlen(app) + 4;
    retval = (char *)SDL_malloc(len);

    if (*org) {
        SDL_snprintf(retval, len, "%s%s/%s/", base, org, app);
    } else {
        SDL_snprintf(retval, len, "%s%s/", base, app);
    }
    free(base);

    _ksys_mkdir(retval);
    return retval;
}

#endif /* SDL_FILESYSTEM_KOLIBRI */
