CC=gcc
CFLAGS=-I.
IDIR=include
DEPS = $(IDIR)/sync_string.h

# Source files
# Update these filepaths as project directory structure changes
MAIN_SRC = src/main.c
TEST_SYNC_SRC = tests/test_sync_string.c
SYNC_SRC = src/sync_string.c

# Object Files
# TODO: look into using patsubst in order to manage directories better
MAIN_OBJ = $(MAIN_SRC:.c=.o)
TEST_SYNC_OBJ = $(TEST_SYNC_SRC:.c=.o) $(SYNC_SRC:.c=.o)

# Rule for creating object files!!
# Syntax - Target: Dependencies list
# $@ means left side of ':', or %.o
# $< means first item in Dependencies list, or %.c
src/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Analogous to the following:
# main: main.o
# $(CC) -o main main.o $(CFLAGS)
main: $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(TEST_SYNC_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DEPS)