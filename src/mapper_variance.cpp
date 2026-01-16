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
            double price_squared = (*price) * (*price);
            
            std::cout << "variance\t" << *price << "\t" << price_squared << "\n";
        }
    }
    
    return 0;
}