CC = kos32-gcc
AR = kos32-ar
LD = kos32-ld
STRIP = kos32-strip

LIBNAME = libSDL2

LIBS:= -lgcc -lc.dll -ldll -lsound

LDFLAGS+= -shared -s -T dll.lds --entry _DllStartup --image-base=0 --out-implib $(LIBNAME).dll.a 
LDFLAGS+= -L/home/autobuild/tools/win32/mingw32/lib

atomic_OBJS = src/atomic/SDL_atomic.o src/atomic/SDL_spinlock.o

audio_OBJS = src/audio/SDL_audio.o src/audio/SDL_audiocvt.o \
        src/audio/SDL_audiodev.o src/audio/SDL_audiotypecvt.o \
		src/audio/SDL_mixer.o src/audio/SDL_wave.o \
		src/audio/kolibri/SDL_kolibriaudio.o

cpuinfo_OBJS = src/cpuinfo/SDL_cpuinfo.o

events_OBJS = src/events/imKStoUCS.o src/events/SDL_clipboardevents.o \
        src/events/SDL_displayevents.o src/events/SDL_dropevents.o \
		src/events/SDL_events.o src/events/SDL_gesture.o \
		src/events/SDL_keyboard.o src/events/SDL_keysym_to_scancode.o \
		src/events/SDL_mouse.o src/events/SDL_quit.o \
		src/events/SDL_scancode_tables.o src/events/SDL_touch.o \
		src/events/SDL_windowevents.o

file_OBJS = src/file/SDL_rwops.o

haptic_OBJS = src/haptic/SDL_haptic.o src/haptic/dummy/SDL_syshaptic.o

hidapi_OBJS = src/hidapi/SDL_hidapi.o

joystick_OBJS = src/joystick/controller_type.o src/joystick/SDL_gamecontroller.o \
        src/joystick/SDL_joystick.o src/joystick/SDL_steam_virtual_gamepad.o \
		src/joystick/dummy/SDL_sysjoystick.o

loadso_OBJS = src/loadso/dummy/SDL_sysloadso.o

power_OBJS = src/power/SDL_power.o

filesystem_OBJS = src/filesystem/kolibri/SDL_sysfilesystem.o

locale_OBJS = src/locale/SDL_locale.o src/locale/dummy/SDL_syslocale.o

misc_OBJS = src/misc/SDL_url.o src/misc/dummy/SDL_sysurl.o

render_OBJS = src/render/SDL_render.o src/render/SDL_yuv_sw.o \
        src/render/software/SDL_blendfillrect.o src/render/software/SDL_blendline.o \
		src/render/software/SDL_blendpoint.o src/render/software/SDL_drawline.o \
		src/render/software/SDL_drawpoint.o src/render/software/SDL_render_sw.o \
		src/render/software/SDL_rotate.o src/render/software/SDL_triangle.o

sensor_OBJS = src/sensor/SDL_sensor.o src/sensor/dummy/SDL_dummysensor.o

stdlib_OBJS = src/stdlib/SDL_crc16.o src/stdlib/SDL_crc32.o src/stdlib/SDL_getenv.o \
        src/stdlib/SDL_iconv.o src/stdlib/SDL_malloc.o src/stdlib/SDL_mslibc.o \
		src/stdlib/SDL_qsort.o src/stdlib/SDL_stdlib.o src/stdlib/SDL_string.o \
		src/stdlib/SDL_strtokr.o

libm_OBJS = src/libm/e_atan2.o src/libm/e_exp.o src/libm/e_fmod.o src/libm/e_log.o \
        src/libm/e_log10.o src/libm/e_pow.o src/libm/e_rem_pio2.o src/libm/e_sqrt.o \
		src/libm/k_cos.o src/libm/k_rem_pio2.o src/libm/k_sin.o src/libm/k_tan.o \
		src/libm/s_atan.o src/libm/s_copysign.o src/libm/s_cos.o src/libm/s_fabs.o \
		src/libm/s_floor.o src/libm/s_scalbn.o src/libm/s_sin.o src/libm/s_tan.o

thread_OBJS = src/thread/SDL_thread.o src/thread/generic/SDL_syscond.o \
        src/thread/generic/SDL_sysmutex.o src/thread/generic/SDL_syssem.o \
		src/thread/generic/SDL_systhread.o src/thread/generic/SDL_systls.o

timer_OBJS = src/timer/SDL_timer.o src/timer/kolibri/SDL_systimer.o

video_OBJS = src/video/SDL_blit_0.o src/video/SDL_blit_1.o src/video/SDL_blit_A.o \
        src/video/SDL_blit_auto.o src/video/SDL_blit_copy.o src/video/SDL_blit_N.o \
		src/video/SDL_blit_slow.o src/video/SDL_blit.o src/video/SDL_bmp.o \
		src/video/SDL_clipboard.o src/video/SDL_egl.o src/video/SDL_fillrect.o \
		src/video/SDL_pixels.o src/video/SDL_rect.o src/video/SDL_RLEaccel.o \
		src/video/SDL_shape.o src/video/SDL_stretch.o src/video/SDL_surface.o \
		src/video/SDL_video.o src/video/SDL_yuv.o src/video/yuv2rgb/yuv_rgb_lsx.o \
		src/video/yuv2rgb/yuv_rgb_sse.o src/video/yuv2rgb/yuv_rgb_std.o \
		src/video/kolibri/SDL_kolibrievents.o src/video/kolibri/SDL_kolibriframebuffer.o \
		src/video/kolibri/SDL_kolibrivideo.o src/video/kolibri/SDL_kolibriwindow.o \
		src/video/kolibri/SDL_kolibrimouse.o src/video/kolibri/SDL_kolibriclipboard.o

curr_OBJS = src/SDL_assert.o src/SDL_dataqueue.o src/SDL_error.o src/SDL_guid.o \
        src/SDL_hints.o src/SDL_list.o src/SDL_log.o src/SDL_utils.o src/SDL.o

OBJS = $(atomic_OBJS) $(audio_OBJS) $(cpuinfo_OBJS) $(events_OBJS) $(file_OBJS) $(haptic_OBJS) \
		$(hidapi_OBJS) $(joystick_OBJS) $(loadso_OBJS) $(power_OBJS) $(filesystem_OBJS) \
		$(locale_OBJS) $(misc_OBJS) $(render_OBJS) $(sensor_OBJS) $(stdlib_OBJS) $(libm_OBJS) \
		$(thread_OBJS) $(timer_OBJS) $(video_OBJS) $(curr_OBJS)

CFLAGS = -c -O2 -mpreferred-stack-boundary=2 -fno-ident -fomit-frame-pointer -fno-stack-check \
        -fno-stack-protector -mno-stack-arg-probe -fno-exceptions -fno-asynchronous-unwind-tables \
        -ffast-math -mno-ms-bitfields  -fexpensive-optimizations \
        -D__KOLIBRI__ -D_KOLIBRI -DKOLIBRI -D_KOS_ -D_KOS -DKOS -DDEBUG_AUDIO -DDEBUG_VIDEO \
        -DPACKAGE=\"SDL\" -DVERSION=\"2.30.3\" -U_Win32 -UWIN32 -U_WIN32 -U__MINGW32__ -U__WIN32__ \
        -I../newlib/libc/include/ -Iinclude/ -Iatomic/ -Iaudio/ -Icpuinfo/ -Ievents/ -Ifile/ -Ihaptic/ \
		-Ihidapi/ -Ijoystick/ -Iloadso/ -Ipower/ -Ifilesystem/ -Ilocale/ -Imisc/ -Irender/ -Isensor/ \
		-Istdlib/ -Ilibm/ -Ithread/ -Itimer/ -Ivideo/ -I.

all:  $(LIBNAME).a $(LIBNAME).dll
 
$(LIBNAME).a: $(OBJS)
	$(AR) -crs  ../../lib/$(LIBNAME).a $(OBJS) 

$(LIBNAME).dll: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
	$(STRIP) -S $@
 
%.o : %.c Makefile
	$(CC) $(CFLAGS) -o $@ $<
 
clean:
	rm -f $(OBJS)
