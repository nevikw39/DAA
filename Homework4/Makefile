MAKEFLAGS += -j$(shell nproc 2> /dev/null || sysctl -n hw.ncpu)

CXX = g++
CXXFLAGS = -std=c++17 -Ofast -mtune=native -march=native

SRC = $(wildcard hw4_bnb*.c*)
BIN = hw4_bnb

TESTS = $(sort $(wildcard data/*.txt))

.PHONY: debug nevikw39 test all clean

debug: CXXFLAGS = -DDEBUG -g -fsanitize=address -fsanitize=undefined
debug: nevikw39

nevikw39: CXX = g++-12
nevikw39: CXXFLAGS += -Dnevikw39 -Wall -Wextra
nevikw39: all

test: $(TESTS)

data/%.txt: all
	./$(BIN) < $@

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)

clean:
	-rm -f $(BIN)