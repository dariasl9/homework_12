#include <iostream>
#include <string>
#include <optional>
#include "csv_parser.hpp"

int main() {
    std::string line;
    
    if (std::getline(std::cin, line)) {
    }
    
    while (std::getline(std::cin, line)) {
        auto price = CSVParser::parse_price(line);
        
        if (price) {
            std::cout << "mean\t" << *price << "\n";
        }
    }
    
    return 0;
}