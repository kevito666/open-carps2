CC ?= cc
CFLAGS ?= -std=c17 -O2 -Wall -Wextra -Wpedantic -Werror
CPPFLAGS ?= -Iinclude
LDFLAGS ?=
BUILD := build

.PHONY: all test clean asan
all: $(BUILD)/open-carps2-info

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/open-carps2-info: src/info.c src/model.c include/open_carps2/model.h | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/info.c src/model.c $(LDFLAGS) -o $@

$(BUILD)/test-model: tests/test_model.c src/model.c include/open_carps2/model.h | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) tests/test_model.c src/model.c $(LDFLAGS) -o $@

test: $(BUILD)/test-model $(BUILD)/open-carps2-info
	./$(BUILD)/test-model
	./$(BUILD)/open-carps2-info --version
	./$(BUILD)/open-carps2-info --list
	./$(BUILD)/open-carps2-info --match-usb 04a9:2795

asan:
	$(MAKE) clean
	$(MAKE) CFLAGS='-std=c17 -O1 -g -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer' LDFLAGS='-fsanitize=address,undefined' test

clean:
	rm -rf $(BUILD)
