
SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)

CFLAGS += -std=c99

LIB_NAME = bacon
VERSION_MAJOR = 0
VERSION_MINOR = 1

TARGET_NAME = lib$(LIB_NAME)
TARGET_STATIC = $(TARGET_NAME).a
TARGET_DSOLIB = $(TARGET_NAME).so.$(VERSION_MAJOR).$(VERSION_MINOR)
TARGET_DSO = $(TARGET_NAME).so

CFLAGS += -Iinclude -std=c99 -Wall -O2 -fvisibility=hidden -fPIC -pedantic

LDFLAGS += -shared -soname $(TARGET_DSO).$(VERSION_MAJOR)

bacon: $(OBJS)

$(TARGET_STATIC):
	ar crus $(TARGET_STATIC) $(OBJS)

$(OBJS):
	cc $(CFLAGS) -c -o $@ $(@:.o=.c)

test:
	@:

clean:
	rm -f $(OBJS)

.PHONY: test
