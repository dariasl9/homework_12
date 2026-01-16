#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <tuple>
#include <cmath>

struct VarianceStats {
    double sum = 0.0;
    double sum_squares = 0.0;
    int count = 0;
    
    void add(double price) {
        sum += price;
        sum_squares += price * price;
        count++;
    }
    
    double mean() const {
        return count > 0 ? sum / count : 0.0;
    }
    
    double variance() const {
        if (count <= 1) return 0.0;
        return (sum_squares - (sum * sum) / count) / (count - 1);
    }
    
    double stddev() const {
        return std::sqrt(variance());
    }
};

int main() {
    std::string line;
    std::map<std::string, VarianceStats> accumulators;
    
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string key;
        double price, price_squared;
        
        if (iss >> key >> price >> price_squared) {
            accumulators[key].add(price);
        }
    }
    
    // Выводим результаты
    std::cout << std::fixed << std::setprecision(2);
    
    for (const auto& [key, stats] : accumulators) {
        if (stats.count > 0) {
            std::cout << "Price Statistics:\n";
            std::cout << "  Mean: $" << stats.mean() << "\n";
            std::cout << "  Variance: " << stats.variance() << "\n";
            std::cout << "  Standard Deviation: " << stats.stddev() << "\n";
            std::cout << "  Count: " << stats.count << "\n";
            std::cout << "  Coefficient of Variation: " 
                     << (stats.mean() > 0 ? (stats.stddev() / stats.mean() * 100) : 0)
                     << "%\n";
        }
    }
    
    return 0;
}