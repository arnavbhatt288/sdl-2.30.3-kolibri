/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL_config_kolibri_h_
#define SDL_config_kolibri_h_
#define SDL_config_h_

#include "SDL_platform.h"

#define HAVE_STDARG_H    1
#define HAVE_STDDEF_H    1
#define HAVE_STDIO_H     1
#define HAVE_STDLIB_H    1
#define HAVE_INTTYPES_H  1
#define HAVE_STDINT_H    1
#define HAVE_MATH_H      1
#define HAVE_CEIL        1
#define HAVE_COPYSIGN    1
#define HAVE_COS         1
#define HAVE_EXP         1
#define HAVE_FABS        1
#define HAVE_FLOOR       1
#define HAVE_LOG         1
#define HAVE_LOG10       1
#define HAVE_SCALBN      1
#define HAVE_SIN         1
#define HAVE_SQRT        1
#define HAVE_TAN         1
#define HAVE_MALLOC      1
#define LACKS_SYS_MMAN_H 1
#define HAVE_MALLOC      1
#define HAVE_CALLOC      1
#define HAVE_REALLOC     1
#define HAVE_FREE        1
#define HAVE_ALLOCA      1
#define HAVE_QSORT       1
#define HAVE_BSEARCH     1
#define HAVE_ABS         1
#define HAVE_BCOPY       1
#define HAVE_MEMCPY      1
#define HAVE_STRTOL      1
#define HAVE_STRTOUL     1
#define HAVE_STRTOLL     1
#define HAVE_STRTOULL    1
#define HAVE_ATOI        1
#define HAVE_ATOF        1
#define HAVE_VSSCANF     1
#define HAVE_VSNPRINTF   1
#define HAVE_M_PI        1
#define HAVE_CEIL        1
#define HAVE_COPYSIGN    1
#define HAVE_COS         1
#define HAVE_COSF        1
#define HAVE_EXP         1
#define HAVE_FABS        1
#define HAVE_FLOOR       1
#define HAVE_LOG         1
#define HAVE_LOG10       1
#define HAVE_LROUND      1
#define HAVE_LROUNDF     1
#define HAVE_ROUND       1
#define HAVE_ROUNDF      1
#define HAVE_SCALBN      1
#define HAVE_SIN         1
#define HAVE_SINF        1
#define HAVE_SQRT        1
#define HAVE_SQRTF       1
#define HAVE_TAN         1
#define HAVE_TANF        1
#define HAVE_TRUNC       1
#define HAVE_TRUNCF      1
#define HAVE_SETJMP      1

/* Enable the dummy thread support (src/thread/dummy/\*.c) */
#define SDL_THREADS_DISABLED 1

/* Enable the dummy timer support (src/timer/dummy/\*.c) */
#define SDL_TIMER_DUMMY 1

/* Enable the Kolibri video driver (src/video/kolibri/\*.c) */
#define SDL_VIDEO_DRIVER_KOLIBRI 1

/* Enable the Kolibri audio driver (src/audio/kolibri/\*.c) */
#define SDL_AUDIO_DRIVER_KOLIBRI 1

/* Enable the stub joystick driver (src/joystick/dummy/\*.c) */
#define SDL_JOYSTICK_DISABLED 1

/* Enable the stub haptic driver (src/haptic/dummy/\*.c) */
#define SDL_HAPTIC_DISABLED 1

/* Enable the stub HIDAPI */
#define SDL_HIDAPI_DISABLED 1

/* Enable the stub sensor driver (src/sensor/dummy/\*.c) */
#define SDL_SENSOR_DISABLED 1

/* Enable the stub shared object loader (src/loadso/dummy/\*.c) */
#define SDL_LOADSO_DISABLED 1

/* Enable the dummy filesystem driver (src/filesystem/dummy/\*.c) */
#define SDL_FILESYSTEM_DUMMY 1

#endif /* SDL_config_kolibri_h_ */
