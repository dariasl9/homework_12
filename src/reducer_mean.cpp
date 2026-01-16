#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>

int main() {
    std::string line;
    std::map<std::string, std::pair<double, int>> accumulators;
    
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string key;
        double value;
        
        if (iss >> key >> value) {
            auto& [sum, count] = accumulators[key];
            sum += value;
            count++;
        }
    }
    
    // Выводим результаты
    for (const auto& [key, stats] : accumulators) {
        const auto& [sum, count] = stats;
        if (count > 0) {
            double mean = sum / count;
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Average price: $" << mean << std::endl;
            std::cout << "Total listings: " << count << std::endl;
        }
    }
    
    return 0;
}