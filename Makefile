MAKEFLAGS += -j$(shell nproc)

BUILD_DIR := build
EXECUTABLE := $(BUILD_DIR)/dbg
LIBDBG := $(BUILD_DIR)/libdbg.a
TESTS := $(BUILD_DIR)/tests

SRCS := $(shell find ./src -name '*.c')
SRCS_OBJ := $(SRCS:./%.c=$(BUILD_DIR)/%.o)
EXEC_OBJ := $(BUILD_DIR)/tools/dbg.o
TESTS_OBJ := $(BUILD_DIR)/test/tests.o

AR := ar
CC := gcc

CFLAGS := -Wall -Wextra -std=c99 -ggdb
CPPFLAGS := -MMD -MP -Iinclude -Isrc/include
LDFLAGS := -ledit

.PHONY: all clean test

all: $(EXECUTABLE) $(LIBDBG) test

$(EXECUTABLE): $(EXEC_OBJ) $(LIBDBG)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TESTS): $(TESTS_OBJ) $(LIBDBG)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(LIBDBG): $(SRCS_OBJ)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

test: $(TESTS) $(EXECUTABLE)
	$(TESTS)

clean:
	rm -rf $(BUILD_DIR)
