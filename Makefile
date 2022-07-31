ATARI:=$(HOME)/src/atari
LIBCMINI:=$(ATARI)/libcmini
GCC:=$(ATARI)/m68k-atari-mint-gcc
PATH:=$(PATH):$(ATARI)/m68k-atari-mint-gcc/bin
LD_LIBRARY_PATH:=$(ATARI)/m68k-atari-mint-gcc/lib64
export PATH LD_LIBRARY_PATH

CFLAGS:=-O2 -s

BIN:=libjoy_test

all: $(BIN).tos libjoy.inl

$(BIN).tos: $(BIN).c libjoy.o
	m68k-atari-mint-gcc -I$(LIBCMINI)/include -nostdlib $(LIBCMINI)/build/crt0.o $^ -o $@ $(CFLAGS) -L$(LIBCMINI)/build -lcmini -lgcc

libjoy.o: libjoy.c
	m68k-atari-mint-gcc -I$(LIBCMINI)/include -pie $< -c -o $@ $(CFLAGS)

libjoy.inl: libjoy.o
	m68k-atari-mint-objcopy -O binary $< $@
	ls -l $@
	m68k-atari-mint-objdump -t $<

run: $(BIN).tos
	hatari $<

clean:
	$(RM) $(BIN).tos *.o *.inl
