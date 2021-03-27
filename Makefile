CC=gcc
CC_FLAGS=-g -Wall
CC_LIBS=-lncurses -lcurl

SRC_DIR=src
OBJ_DIR=obj

SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
BIN_FILE=prog

all: $(BIN_FILE)

$(BIN_FILE): $(OBJ_FILES)
	$(CC) $(CC_FLAGS) $^ -o $@ $(CC_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $^

clean:
	rm -f $(OBJ_FILES) $(BIN_FILE)
