CC=gcc
LD=ld
LIBS=common.c config.c clipmsg.c
OBJS=$(patsubst %.c,%.o,$(LIBS))
PREFIX=""
CFLAGS=-Wall -g -I../include -DPREFIX=$(PREFIX) -DDEBUG

all: libs daemon_bin client_bin

debug:
	@echo "LIBS: \"$(LIBS)\", OBJS: \"$(OBJS)\""

libs:
	@for thing in $(LIBS); do\
		gcc $(CFLAGS) -c $$thing; \
	done

daemon_bin:
	gcc $(CFLAGS) -o ../bin/daemon daemon.c $(OBJS)

client_bin:
	gcc $(CFLAGS) -o ../bin/client client.c $(OBJS)

clean:
	-rm *.o
	-rm `find -executable -type f`
	-rm `find -type s`

install:
	cp daemon $(PREFIX)/usr/bin
	cp daemon.conf $(PREFIX)/etc

.PHONY: all
