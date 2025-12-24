TARGET = psparpg
OBJS = src/main.o \
       src/core/platform.o \
       src/core/timing.o \
       src/core/logging.o \
       src/renderer/renderer.o \
       src/renderer/isometric.o \
       src/input/input.o \
       src/input/bindings.o \
       src/audio/audio_stub.o \
       src/ui/menu.o \
       src/ui/hud.o \
       src/game/world.o \
       src/game/entity.o \
       src/assets/dataroot.o \
       src/assets/archive.o \
       src/assets/filesystem.o

INCDIR = include
CFLAGS = -O2 -G0 -Wall -I$(INCDIR)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpspgum -lpspgu -lm -lpsprtc -lpspaudio -lpsppower

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSP ARPG Engine
PSP_EBOOT_ICON = ICON0.PNG

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak