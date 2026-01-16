CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include
BIN_DIR = ./bin
SRC_DIR = ./src

TARGETS = $(BIN_DIR)/mapper_mean $(BIN_DIR)/reducer_mean \
          $(BIN_DIR)/mapper_variance $(BIN_DIR)/reducer_variance

all: $(TARGETS)

$(BIN_DIR)/mapper_mean: $(SRC_DIR)/mapper_mean.cpp include/csv_parser.hpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/reducer_mean: $(SRC_DIR)/reducer_mean.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/mapper_variance: $(SRC_DIR)/mapper_variance.cpp include/csv_parser.hpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/reducer_variance: $(SRC_DIR)/reducer_variance.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR) output/*

run: all
	./run_locally.sh

.PHONY: all clean run