CFLAGS=-Wall

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
TMP_DIRS=$(OBJ_DIR) $(BIN_DIR)

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

PROGRAM=main

$(BIN_DIR)/$(PROGRAM): $(OBJS) $(BIN_DIR)
	$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@

$(TMP_DIRS):
	mkdir $@

clean:
	rm -rf $(TMP_DIRS)

run: $(PROGRAM)
	bin/main

# "clean" is not a file
.PHONY: clean
