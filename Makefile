CC=gcc
CC_FLAGS=-g -Wall
CC_LIBS=-lncurses -lcurl

SRC_DIR=src
OBJ_DIR=obj
TST_DIR=test
TBN_DIR=test/bin

TST_LIB=test/minunit.h

# source and object files
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# test files and their binaries
TST_FILES=$(wildcard $(TST_DIR)/*_test.c)
TBN_FILES=$(patsubst $(TST_DIR)/%_test.c, $(TBN_DIR)/%, $(TST_FILES))

BIN_FILE=dictcc

all: $(OBJ_DIR) $(BIN_FILE) 

$(BIN_FILE): $(OBJ_FILES)
	$(CC) $(CC_FLAGS) $^ -o $@ $(CC_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

$(OBJ_DIR):
	mkdir $@

test: $(TBN_DIR) $(OBJ_DIR) $(TBN_FILES)
	for test in $(TBN_FILES); do ./$$test; done

$(TBN_DIR)/%: $(OBJ_DIR)/%.o $(TST_DIR)/%_test.c
	$(CC) $(CC_FLAGS) $^ $(TST_LIB) -o $@

$(TBN_DIR):
	mkdir $@

clean:
	rm -rf $(BIN_FILE) $(OBJ_DIR) $(TBN_DIR)
