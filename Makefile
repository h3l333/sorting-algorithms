# Make is an automation tool designed to re-run commands for files not up to date relative to
# their dependencies.

CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude

BIN_DIR := bin
APP := $(BIN_DIR)/main
TEST_APP := $(BIN_DIR)/test-utils
SORT_TEST_APP := $(BIN_DIR)/test-sorting
SOURCES := $(wildcard src/*.c)
TEST_SOURCES := tests/test-utils.c src/utils.c
SORT_TEST_SOURCES := tests/test-sorting.c src/burbujeo.c src/seleccion.c src/insercion.c src/shell.c src/quicksort.c src/utils.c

# Variable assignment: -"?=" only sets the variable if it is not already set
#                      - ":=" corresponds to simple/immediate assignment

.PHONY: all test clean # Specifies to Make that "all", "test" and "clean" are not files in the dir.

all: $(APP) # "$()" is used to indicate that "APP" does not refer to literal bare text.
# By executing "make all" a rebuild-if-needed is performed.

$(BIN_DIR): # Rule header; no prerequisites. BIN_DIR holds a path like "bin".
# Creates bin directory if it does not already exist.
	mkdir -p $(BIN_DIR)

# Useful to think of it as:
#                           target: prerequisites
#                              recipe
# A target is the thing Make is trying to produce or accomplish.
# A recipe is the commands that produce it.

$(APP): $(SOURCES) include/ordenamientos.h include/utils.h | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(APP)

$(TEST_APP): $(TEST_SOURCES) include/utils.h | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_APP)

$(SORT_TEST_APP): $(SORT_TEST_SOURCES) include/ordenamientos.h | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SORT_TEST_SOURCES) -o $(SORT_TEST_APP)

# Defined targets, dependencies and to the right of "|" specification to build bin dir if it
# does not already exist.
# Indented line represents the command to be run.

test: $(TEST_APP) $(SORT_TEST_APP)
	./$(TEST_APP)
	./$(SORT_TEST_APP)

# Automatically runs test binary files.

clean:
	rm -f $(APP) $(TEST_APP) $(SORT_TEST_APP)

# Deletes all compiled binaries, including main application binary.

FORMATTER ?= clang-format
FORMAT_SOURCES := $(wildcard src/*.c include/*.h tests/*.c)

.PHONY: format check-format

format:
	$(FORMATTER) -i $(FORMAT_SOURCES)

check-format:
	$(FORMATTER) --dry-run --Werror $(FORMAT_SOURCES)
