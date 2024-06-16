CC=gcc
CFLAGS=-I$(IDIR) -I$(VDIR)
IDIR=include
SDIR=src
TDIR=tests
ODIR=obj
VDIR=vendor/Unity/src

# Header file dependencies

# sync_string.h --> /include/sync_string.h
_TEST_SYNC_DEPS = sync_string.h
TEST_SYNC_DEPS = $(patsubst %, $(IDIR)/%,$(_TEST_SYNC_DEPS))

# symbol_alphabet.h --> /include/symbol_alphabet.h
_TEST_SYM_DEPS = symbol_alphabet.h
TEST_SYM_DEPS = $(patsubst %, $(IDIR)/%,$(_TEST_SYM_DEPS))

# Object Files

# main.o --> /obj/main.o
_MAIN_OBJ = main.o
MAIN_OBJ = $(patsubst %, $(ODIR)/%,$(_MAIN_OBJ))

# sync_string.o --> /obj/sync_string.o
_SYNC_OBJ = sync_string.o
SYNC_OBJ = $(patsubst %, $(ODIR)/%,$(_SYNC_OBJ))

_SYMBOL_OBJ = symbol_alphabet.o
SYMBOL_OBJ = $(patsubst %, $(ODIR)/%,$(_SYMBOL_OBJ))

# test_sync_string.o --> /obj/test_sync_string.o
_TEST_SYNC_OBJ = test_sync_string.o
TEST_SYNC_OBJ = $(patsubst %, $(ODIR)/%,$(_TEST_SYNC_OBJ))

_TEST_SYM_OBJ = test_symbol_alphabet.o
TEST_SYM_OBJ = $(patsubst %, $(ODIR)/%,$(_TEST_SYM_OBJ))

UNITY_SRC = $(VDIR)/unity.c
UNITY_OBJ = $(ODIR)/unity.o

# Rule for creating object files
# Syntax - Target: Dependencies list

# Rule for creating Unity object file
$(ODIR)/unity.o: $(VDIR)/unity.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule for creating main.o
$(ODIR)/main.o: $(SDIR)/main.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule for creating sync_string.o
$(ODIR)/sync_string.o: $(SDIR)/sync_string.c $(TEST_SYNC_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule for creating test_sync_string.o
$(ODIR)/test_sync_string.o: $(TDIR)/test_sync_string.c $(TEST_SYNC_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/symbol_alphabet.o: $(SDIR)/symbol_alphabet.c $(TEST_SYM_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/test_symbol_alphabet.o: $(TDIR)/test_symbol_alphabet.c $(TEST_SYM_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Analogous to the following:
# main: main.o
# 	$(CC) -o main main.o $(CFLAGS)
main: $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test_sync: $(SYNC_OBJ) $(TEST_SYNC_OBJ) $(UNITY_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(TEST_SYNC_DEPS)

test_sym: $(SYMBOL_OBJ) $(TEST_SYM_OBJ) $(UNITY_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(TEST_SYM_DEPS)

.PHONY: clean

clean:
	del /Q $(ODIR)\*.o
