MAKEFLAGS += -j$(shell nproc 2> /dev/null || sysctl -n hw.ncpu)

CXX = g++
CXXFLAGS = -std=c++17 -Ofast -mtune=native -march=native

SRC = $(wildcard hw5_pns*.c*)
BIN = hw5_pns

TEST ?= 10000000 1000000 30000000
TESTS = $(foreach i, $(shell seq $(TEST)), data/$(i).txt)

.PHONY: debug nevikw39 test all clean

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)

test: $(TESTS)

data/%.txt: all
	mkdir -p data
	./gen.sh $(basename $(notdir $@))
	./$(BIN) < $@

debug: CXXFLAGS = -DDEBUG -g -fsanitize=address -fsanitize=undefined
debug: nevikw39

nevikw39: CXX = g++-13
nevikw39: CXXFLAGS += -Dnevikw39 -Wall -Wextra
nevikw39: all

clean:
	-rm -f $(BIN) $(TESTS)
