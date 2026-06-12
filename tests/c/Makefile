# ==========================================
# Compiler and Flags Configuration
# ==========================================
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -g -Iinclude
LIBS    := -lldap -llber

# ==========================================
# Directory Path Definitions
# ==========================================
SRC_DIR   := src
BUILD_DIR := build
OUT_DIR   := out

# ==========================================
# Target Binary Definition
# ==========================================
TARGET := $(BUILD_DIR)/test

# ==========================================
# Source and Object File Mapping
# ==========================================
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# ==========================================
# Master Build Rules
# ==========================================

# The absolute first target is the default. 
# It now strictly demands that the config check passes BEFORE building the binary.
all: check_config $(TARGET)

# Safety check rule to ensure setup.h exists locally
.PHONY: check_config
check_config:
	@if [ ! -f include/setup.h ]; then \
		echo "❌ Error: include/setup.h not found!"; \
		echo "👉 Run: cp include/setup.h.example include/setup.h and populate your real credentials."; \
		exit 1; \
	fi

# Rule to link the final executable from object files
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	@echo "🎉 Successfully built target: $@"

# Rule to compile individual source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ==========================================
# Utility Rules
# ==========================================

# Helper to automatically run your bash script test runner
.PHONY: test
test: all
	@echo "🚀 Starting test automation script..."
	@bash scripts/run_bind_test.sh

# Complete cleanup rule (removes build files and generated test artifacts)
.PHONY: clean
clean:
	@echo "🧹 Cleaning up workspace..."
	rm -rf $(BUILD_DIR) $(OUT_DIR)
	@echo "✨ Workspace is clean."
