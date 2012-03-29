CC=g++

GTEST_LIB=$(HOME)/local-gcc-trunk/gtest/lib

CFLAGSX:=$(CFLAGS)
LDFLAGSX:=$(LDFLAGS)

CFLAGSX+=-Wall -O3 -s -fpic -std=c++11 -Wno-strict-aliasing -Wextra -Werror -pedantic -DNDEBUG
CFLAGSX+=-I include

LDFLAGSX+=-lstdc++ -lpthread -O3 -s


PYSRC = $(wildcard test/meta/gen*.py)

SRCS = $(wildcard test/*.cpp)

PROGS = $(patsubst %.cpp,%,$(SRCS))



all: $(PROGS)

%: %.cpp
	$(CC) $(LDFLAGSX) $(CFLAGSX) $(GTEST_LIB)/gtest_main.a -o $@ $<


autogen: $(PYSRC)
	@cd test/meta; \
	python $(notdir $<); \
	cd ../..; \

test: autogen all
	@for p in $(PROGS); do \
	  echo "running $$p"; \
	  ./$$p  --gtest_color=yes; \
	done;

clean:
	rm -f test/*.o $(PROGS)

.PHONY: clean test

