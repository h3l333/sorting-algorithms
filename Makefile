CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude

BIN_DIR := bin
APP := $(BIN_DIR)/main
TEST_APP := $(BIN_DIR)/test-utils
SORT_TEST_APP := $(BIN_DIR)/test-sorting
SOURCES := $(wildcard src/*.c)
TEST_SOURCES := tests/test-utils.c src/utils.c
SORT_TEST_SOURCES := tests/test-sorting.c src/burbujeo.c src/seleccion.c src/insercion.c src/shell.c src/quicksort.c src/utils.c

.PHONY: all test clean

all: $(APP)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(APP): $(SOURCES) include/ordenamientos.h include/utils.h | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(APP)

$(TEST_APP): $(TEST_SOURCES) include/utils.h | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_APP)

$(SORT_TEST_APP): $(SORT_TEST_SOURCES) include/ordenamientos.h | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SORT_TEST_SOURCES) -o $(SORT_TEST_APP)

test: $(TEST_APP) $(SORT_TEST_APP)
	./$(TEST_APP)
	./$(SORT_TEST_APP)

clean:
	rm -f $(APP) $(TEST_APP) $(SORT_TEST_APP)

FORMATTER ?= clang-format
FORMAT_SOURCES := $(wildcard src/*.c include/*.h tests/*.c)

.PHONY: format check-format

format:
	$(FORMATTER) -i $(FORMAT_SOURCES)

check-format:
	$(FORMATTER) --dry-run --Werror $(FORMAT_SOURCES)
