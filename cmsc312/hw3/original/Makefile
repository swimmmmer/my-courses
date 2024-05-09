#
#
# Make environment

CC=gcc
CFLAGS= -c -g -Wall $(INCLUDES)

# Files
OBJECT_FILES= main.o support.o

# Production
all : Assign3

Assign3 : $(OBJECT_FILES)
	$(CC)  $(OBJECT_FILES) -o $@

main.o : main.c memory.h
	$(CC) $(CFLAGS) $< -o $@

support.o : support.c memory.h
	$(CC) $(CFLAGS) $< -o $@

clean : 
	rm -v Assign3 $(OBJECT_FILES)
