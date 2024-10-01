
TARGET = main

# Source files
SRC = src/*.c

# Included directories
INCLUDE_DIR = include

# Compiler and linker flags
# Considerar: -Werror -Wfatal-errors -Wall -Wextra
# considerar optimizaciones: -Os
CFLAGS = -I${INCLUDE_DIR} -Werror -Wfatal-errors -Wall -Wextra

# Output directory
BUILD_DIR = bin
BUILD_TARGET = $(BUILD_DIR)/main.o

# Default target
all: $(BUILD_DIR) $(BUILD_TARGET)

$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Build .o from source
$(BUILD_TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up build directory
clean:
	if exist $(BUILD_DIR) del /Q $(BUILD_DIR)\*
