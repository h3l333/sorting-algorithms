CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude

BIN_DIR := bin
APP := $(BIN_DIR)/main
TEST_APP := $(BIN_DIR)/test-utils
SOURCES := $(wildcard src/*.c)
TEST_SOURCES := tests/test-utils.c src/utils.c

.PHONY: all test clean

all: $(APP)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(APP): $(SOURCES) include/ordenamientos.h include/utils.h | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(APP)

$(TEST_APP): $(TEST_SOURCES) include/utils.h | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_APP)

test: $(TEST_APP)
	./$(TEST_APP)

clean:
	rm -f $(APP) $(TEST_APP)

FORMATTER ?= clang-format
FORMAT_SOURCES := $(wildcard src/*.c include/*.h tests/*.c)

.PHONY: format check-format

format:
	$(FORMATTER) -i $(FORMAT_SOURCES)

check-format:
	$(FORMATTER) --dry-run --Werror $(FORMAT_SOURCES)
