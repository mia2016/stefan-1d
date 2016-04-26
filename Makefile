CFLAGS=-Wall -g -std=c11
LDFLAGS=-lm

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
TEST_DIR=tests
DEP_DIR=.deps
TMP_DIRS=$(OBJ_DIR) $(BIN_DIR) $(DEP_DIR)

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
T_SRCS=$(wildcard $(TEST_DIR)/*.c)
T_BINS=$(T_SRCS:$(TEST_DIR)/%.c=$(BIN_DIR)/test_%)

PROGRAM=bin/main

# Main program
$(PROGRAM): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

# Objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(DEP_DIR)
	$(CC) -MM -MP -MT $@ $< > $(DEP_DIR)/$*.d
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@

# Tests
$(BIN_DIR)/test_%: $(TEST_DIR)/%.c
	$(CC) $(CPPFLAGS) -Iinclude $(CFLAGS) $^ -o $@

# Temporary folders
$(TMP_DIRS):
	mkdir $@

clean:
	rm -rf $(TMP_DIRS)

run: $(PROGRAM)
	$(PROGRAM)


# Dependencies are made during compilation
$(DEP_DIR)/%.d:;

# Run all tests
test: $(T_BINS)
	@echo "Running tests..."
	@for p in $^; do $$p; done;

# "clean" is not a file
.PHONY: clean run test


-include $(DEP_DIR)/*.d
