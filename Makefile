CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include
BIN_DIR = ./bin
SRC_DIR = ./src
OUTPUT_DIR = ./output

TARGETS = $(BIN_DIR)/mapper_mean $(BIN_DIR)/mapper_variance \
          $(BIN_DIR)/reducer_mean $(BIN_DIR)/reducer_variance

all: $(TARGETS)

# Сборка mapper  для среднего
$(BIN_DIR)/mapper_mean: $(SRC_DIR)/mapper_mean.cpp include/csv_better_parser.hpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Сборка mapper  для дисперсии
$(BIN_DIR)/mapper_variance: $(SRC_DIR)/mapper_variance.cpp include/csv_better_parser.hpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Сборка reducer для среднего
$(BIN_DIR)/reducer_mean: $(SRC_DIR)/reducer_mean.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Сборка reducer для дисперсии
$(BIN_DIR)/reducer_variance: $(SRC_DIR)/reducer_variance.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Очистка
clean:
	rm -rf $(BIN_DIR) $(OUTPUT_DIR)/*

# Запуск всего пайплайна
run: all
	@echo "=== Расчет средней цены ==="
	@cat input/AB_NYC_2019.csv | ./bin/mapper_mean 2>/dev/null | sort -k1 | ./bin/reducer_mean
	
	@echo ""
	@echo "=== Расчет дисперсии цены ==="
	@cat input/AB_NYC_2019.csv | ./bin/mapper_variance 2>/dev/null | sort -k1 | ./bin/reducer_variance
	
	@echo ""
	@echo "=== Проверка с помощью Python ==="
	@python3 check_simple.py

.PHONY: all clean run