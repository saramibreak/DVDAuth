TARGET := DVDAuth.out
ifeq ($(shell uname),Linux)
  INCFLAGS := -I. -Ilibdvdcpxm/src -I_linux
else ifeq ($(shell uname),Darwin)
  INCFLAGS := -I. -Ilibdvdcpxm/src -I_linux -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks
  LIBS := -framework CoreFoundation -framework IOKit
endif
CFLAGS := -include _linux/defineForLinux.h
CXXFLAGS := $(CFLAGS) -std=c++11

ifneq ($(SANITIZER),)
   CFLAGS   := -fsanitize=$(SANITIZER) $(CFLAGS)
   CXXFLAGS := -fsanitize=$(SANITIZER) $(CXXFLAGS)
   LDFLAGS  := -fsanitize=$(SANITIZER) $(LDFLAGS)
endif

ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g
	CXXFLAGS += -O0 -g
else
	CFLAGS += -O2 -Wall -Wextra -Wno-unknown-pragmas
	CXXFLAGS += -O2 -Wall -Wextra -Wno-unknown-pragmas
endif

SOURCES_CXX := \
  DVDAuth.o \
  execScsiCmdforFileSystem.o \
  libdvdcpxm/src/dvd_css.o \
  libdvdcpxm/src/dvd_command.o \
  libdvdcpxm/src/dvd_device.o \
  libdvdcpxm/src/libdvdcpxm.o \
  _linux/defineForLinux.o

OBJECTS := $(SOURCES_C:.c=.o) $(SOURCES_CXX:.cpp=.o)

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCFLAGS)

clean-objs:
	rm -f $(OBJECTS)

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

install:
	install -m 0755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

.PHONY: clean clean-objs
