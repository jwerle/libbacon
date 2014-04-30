
SRC = $(filter-out src/main.c, $(wildcard src/*.c))
OBJS = $(SRC:.c=.o)

CFLAGS += -std=c99

BIN_NAME ?= bacon
LIB_NAME ?= bacon

VERSION_MAJOR = 0
VERSION_MINOR = 1

TARGET_NAME = lib$(LIB_NAME)
TARGET_STATIC = $(TARGET_NAME).a
TARGET_DSOLIB = $(TARGET_NAME).so.$(VERSION_MAJOR).$(VERSION_MINOR)
TARGET_DSO = $(TARGET_NAME).so

CFLAGS += -Iinclude -std=c99 -Wall -O2 -fvisibility=hidden -fPIC -pedantic
LDFLAGS += -shared -soname $(TARGET_DSO).$(VERSION_MAJOR)

CFLAGS += -DBACON_VERSION='"$(VERSION_MAJOR).$(VERSION_MINOR)"'

bacon:
	cc $(CFLAGS) $(SRC) src/main.c -o $(BIN_NAME)

$(TARGET_STATIC):
	ar crus $(TARGET_STATIC) $(OBJS)

$(OBJS):
	cc $(CFLAGS) -c -o $@ $(@:.o=.c)

test: $(OBJS) $(TARGET_STATIC) deps
	cc deps/ok/libok.a $(CFLAGS) $(TARGET_STATIC) test.c -o test-$(BIN_NAME)
	./test-$(BIN_NAME)

deps:
	make -C deps/ok

clean:
	rm -f $(OBJS) $(BIN_NAME) $(TARGET_STATIC) test-$(BIN_NAME)
	make clean -C deps/ok

.PHONY: test deps
