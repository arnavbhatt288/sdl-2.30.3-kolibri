CC = kos32-gcc
LD = kos32-ld
OBJCOPY = kos32-objcopy

SDK_DIR = ../../..
LDFLAGS = -nostdlib -static --image-base 0 -T $(SDK_DIR)/sources/newlib/app.lds --subsystem native
CFLAGS = -c -fno-ident -O2 -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -D_KOLIBRI -DNO_ZIP -DPERFORMANCE 
LIBS = -lSDL2test -lSDL2 -lgcc -lc.dll -lc -lsound

INCLUDES = -I $(SDK_DIR)/sources/newlib/libc/include -I ../include/
LIBPATH = -L $(SDK_DIR)/lib -L /home/autobuild/tools/win32/mingw32/lib

all: checkkeys loopwave testatomic testaudioinfo testbounds testcustomcursor testdisplayinfo testdraw2 testdrawchessboard testfile \
	   testfilesystem testgeometry testiconv testime testintersections testkeys testmouse testmultiaudio testoverlay2 \
		 testplatform testqsort testrelative testrendercopyex testrendertarget testresample testscale testshape testsprite2 \
		 testspriteminimal teststreaming testver testviewport testwm2 testyuv

checkkeys: checkkeys.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

loopwave: loopwave.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

loopwavequeue: loopwavequeue.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testatomic: testatomic.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testaudioinfo: testaudioinfo.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testbounds: testbounds.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testcustomcursor: testcustomcursor.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testdisplayinfo: testdisplayinfo.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testdraw2: testdraw2.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testdrawchessboard: testdrawchessboard.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testfile: testfile.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testfilesystem: testfilesystem.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testgeometry: testgeometry.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testiconv: testiconv.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testime: testime.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testintersections: testintersections.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testkeys: testkeys.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testmouse: testmouse.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testmultiaudio: testmultiaudio.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testoverlay2: testoverlay2.o testyuv_cvt.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testplatform: testplatform.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testqsort: testqsort.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testrelative: testrelative.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testrendercopyex: testrendercopyex.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testrendertarget: testrendertarget.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testresample: testresample.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testscale: testscale.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testshape: testshape.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testsprite2: testsprite2.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testspriteminimal: testspriteminimal.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

teststreaming: teststreaming.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testver: testver.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testviewport: testviewport.o testutils.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testwm2: testwm2.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

testyuv: testyuv.o testyuv_cvt.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)
	$(OBJCOPY) $@ -O binary

%.o : %.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
 
clean:
	rm -f *.o
	rm -f checkkeys loopwave testatomic testaudioinfo testbounds testcustomcursor testdisplayinfo testdraw2 testdrawchessboard testfile \
	testfilesystem testgeometry testiconv testime testintersections testkeys testmouse testmultiaudio testoverlay2 \
	testplatform testqsort testrelative testrendercopyex testrendertarget testresample testscale testshape testsprite2 \
	testspriteminimal teststreaming testver testviewport testwm2 testyuv
