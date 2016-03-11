CFLAGS=-Wall -g -std=c11
LDFLAGS=-lm

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
TMP_DIRS=$(OBJ_DIR) $(BIN_DIR)

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

PROGRAM=bin/main

$(PROGRAM): $(OBJS) $(BIN_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@

$(TMP_DIRS):
	mkdir $@

clean:
	rm -rf $(TMP_DIRS)

run: $(PROGRAM)
	$(PROGRAM)

# "clean" is not a file
.PHONY: clean run
