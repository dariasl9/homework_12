#include <iostream>
#include <string>
#include <optional>
#include "csv_better_parser.hpp"

int main() {
    std::string line;
    int total_lines = 0;
    int parsed_lines = 0;
    int error_lines = 0;
    
    while (std::getline(std::cin, line)) {
        total_lines++;
        
        auto price = BetterCSVParser::extract_price(line, false);
        
        if (price) {
            parsed_lines++;
            double price_squared = (*price) * (*price);
            std::cout << "variance\t" << *price << "\t" << price_squared << "\n";
        } else {
            error_lines++;
        }
    }
    
    std::cerr << "Variance mapper: обработано " << parsed_lines << "/" << total_lines 
              << " строк (" << (total_lines > 0 ? 100.0 * parsed_lines / total_lines : 0) << "%)" << std::endl;
    
    return 0;
}