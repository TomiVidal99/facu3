
TARGET = main

# Source files
SRC_CLIENT = src/client.c
SRC_SERVER = src/server.c

# Included directories
INCLUDE_DIR = include

# Compiler and linker flags
# Considerar: -Werror -Wfatal-errors -Wall -Wextra
# considerar optimizaciones: -Os
CFLAGS = -I${INCLUDE_DIR} -Werror -Wfatal-errors -Wall -Wextra

# Output directory
BUILD_DIR = bin
BUILD_TARGET_CLIENT = $(BUILD_DIR)/client.o
BUILD_TARGET_SERVER = $(BUILD_DIR)/server.o

# Default target
all: client

server: $(BUILD_DIR) $(BUILD_TARGET_SERVER)

$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Build .o from source
$(BUILD_TARGET_SERVER): $(SRC_SERVER)
	$(CC) $(CFLAGS) $^ -o $@

client: $(BUILD_DIR) $(BUILD_TARGET_CLIENT)

$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Build .o from source
$(BUILD_TARGET_CLIENT): $(SRC_CLIENT)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up build directory
clean:
	rm ./$(BUILD_TARGET_CLIENT)
	rm ./$(BUILD_TARGET_SERVER)