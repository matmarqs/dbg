.PHONY: all clean

LIBDBG_A := build/libdbg.a
TARGETS := $(LIBDBG_A)

MAKEFLAGS += -j$(shell nproc)

SRC_DIRS := ./src
BUILD_DIR := ./build

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:./%.c=$(BUILD_DIR)/%.o)

AR := ar
CC := gcc

CFLAGS := -Wall -Wextra -std=c99 -ggdb
CPPFLAGS := -MMD -MP -Iinclude
LDFLAGS :=

all: $(TARGETS)

$(LIBDBG_A): $(OBJS)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
