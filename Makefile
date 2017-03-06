
NAME=$(notdir $(CURDIR))

INCLUDE=-I`pwd`/include

C_STRICT=-Werror -Wextra
C_FLAGS=-std=c11 -Wall $(INCLUDE)
BUILD_DIR=build
EXEC=$(BUILD_DIR)/_start

TESTS=tests/*.c
VERSION_FILE=VERSION


.PHONY: build test version


all: clean build

build: mkdir_build main.c utils.c cli.c linking

mkdir_build:
	@ mkdir -p $(BUILD_DIR)

main.c: src/main.c
	@ $(eval name=$(basename $(notdir $<)))
	@ $(CC) $(C_FLAGS) -E $? > $(BUILD_DIR)/$(name).i
	@ $(CC) $(C_FLAGS) -S $(BUILD_DIR)/$(name).i -o $(BUILD_DIR)/$(name).s
	@ $(AS) $(BUILD_DIR)/$(name).s -o $(BUILD_DIR)/$(name).o

utils.c: src/utils.c
	@ $(eval name=$(basename $(notdir $<)))
	@ $(CC) $(C_FLAGS) -E $? > $(BUILD_DIR)/$(name).i
	@ $(CC) $(C_FLAGS) -S $(BUILD_DIR)/$(name).i -o $(BUILD_DIR)/$(name).s
	@ $(AS) $(BUILD_DIR)/$(name).s -o $(BUILD_DIR)/$(name).o

cli.c: src/cli.c
	@ $(eval name=$(basename $(notdir $<)))
	@ $(CC) $(C_FLAGS) -E $? > $(BUILD_DIR)/$(name).i
	@ $(CC) $(C_FLAGS) -S $(BUILD_DIR)/$(name).i -o $(BUILD_DIR)/$(name).s
	@ $(AS) $(BUILD_DIR)/$(name).s -o $(BUILD_DIR)/$(name).o

linking: $(BUILD_DIR)/*.o
	@ $(CC) -o $(EXEC) $?
	@ if [ -f ./$(NAME) ]; then rm ./$(NAME); fi;
	@ ln -s -n $(EXEC) ./$(NAME)
	@ ./$(NAME)

test:

docs:

clean:
	@ rm -rf $(BUILD_DIR)/

version: $(VERSION_FILE)
	@ cat $(VERSION_FILE)
