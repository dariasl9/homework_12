#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <optional>
#include <string_view>
#include <charconv>
#include <system_error>

class CSVParser {
public:
    static std::optional<double> parse_price(const std::string& line) {
        // id,name,host_id,host_name,neighbourhood_group,neighbourhood,latitude,longitude,room_type,price,...
        
        size_t field_count = 0;
        bool in_quotes = false;
        std::string_view field;
        size_t start = 0;
        
        for (size_t i = 0; i <= line.size(); ++i) {
            if (i == line.size() || (!in_quotes && line[i] == ',')) {
                field = std::string_view(line.data() + start, i - start);
                
                if (field_count == 9) { // price field
                    // Убираем кавычки если есть
                    if (!field.empty() && field.front() == '"' && field.back() == '"') {
                        field = field.substr(1, field.size() - 2);
                    }
                    
                    double price;
                    auto [ptr, ec] = std::from_chars(field.data(), 
                                                    field.data() + field.size(), 
                                                    price);
                    
                    if (ec == std::errc() && price > 0) {
                        return price;
                    }
                    return std::nullopt;
                }
                
                field_count++;
                start = i + 1;
            }
            else if (line[i] == '"') {
                in_quotes = !in_quotes;
            }
        }
        
        return std::nullopt;
    }
};