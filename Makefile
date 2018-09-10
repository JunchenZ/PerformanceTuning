# Student's Makefile for the CS:APP Performance Lab
TEAM = bovik
VERSION = 1
HANDINDIR =

CC = clang
CFLAGS = -Wall -O2 -fno-vectorize
# CFLAGS = -Wall -O2 -fno-vectorize -fsanitize=address,undefined
LIBS = -lm

OBJS = driver.o kernels.o fcyc.o clock.o

all: driver

driver: $(OBJS) fcyc.h clock.h defs.h config.h
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o driver

handin:
	cp kernels.c $(HANDINDIR)/$(TEAM)-$(VERSION)-kernels.c

clean: 
	-rm -f $(OBJS) driver core *~ *.o


