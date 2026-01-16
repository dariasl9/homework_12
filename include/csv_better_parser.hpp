#pragma once

#include <string>
#include <optional>
#include <cctype>
#include <iostream>

class BetterCSVParser {
public:
    static std::optional<double> extract_price(const std::string& line, bool debug = false) {
        // Считаем запятые до 10-го поля
        int comma_count = 0;
        size_t start = 0;
        size_t end = 0;
        bool in_quotes = false;
        
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            
            if (c == '"') {
                in_quotes = !in_quotes;
            } else if (c == ',' && !in_quotes) {
                comma_count++;
                if (comma_count == 9) {
                    start = i + 1;
                } else if (comma_count == 10) {
                    end = i;
                    break;
                }
            }
        }
        
        // Если не нашли 10-ю запятую, но нашли 9-ю, берем до конца строки
        if (comma_count == 9 && start > 0 && end == 0) {
            end = line.size();
        }
        
        if (debug) {
            std::cerr << "Запятых: " << comma_count << ", start: " << start << ", end: " << end << std::endl;
        }
        
        if (comma_count < 9 || start >= end || end > line.size()) {
            if (debug) std::cerr << "Не удалось найти 10-е поле" << std::endl;
            return std::nullopt;
        }
        
        // Извлекаем цену
        std::string price_str = line.substr(start, end - start);
        
        if (debug) {
            std::cerr << "Строка с ценой: \"" << price_str << "\"" << std::endl;
        }
        
        // Очищаем строку
        price_str = clean_price_string(price_str);
        
        if (debug) {
            std::cerr << "Очищенная строка: \"" << price_str << "\"" << std::endl;
        }
        
        if (price_str.empty()) {
            if (debug) std::cerr << "Пустая строка после очистки" << std::endl;
            return std::nullopt;
        }
        
        // Пробуем преобразовать
        try {
            double price = std::stod(price_str);
            if (debug) std::cerr << "Преобразованная цена: " << price << std::endl;
            
            // Базовая проверка
            if (price < 0) {
                if (debug) std::cerr << "Отрицательная цена" << std::endl;
                return std::nullopt;
            }
            
            return price;
        } catch (const std::exception& e) {
            if (debug) std::cerr << "Ошибка преобразования: " << e.what() << std::endl;
            return std::nullopt;
        }
    }
    
private:
    static std::string clean_price_string(const std::string& str) {
        std::string result;
        bool has_decimal = false;
        bool has_digit = false;
        
        for (char c : str) {
            // Если цифра
            if (c >= '0' && c <= '9') {
                result += c;
                has_digit = true;
            }
            // Десятичная точка (только одна)
            else if (c == '.' && !has_decimal) {
                result += c;
                has_decimal = true;
            }
            // Минус (только в начале)
            else if (c == '-' && result.empty()) {
                result += c;
            }
            // Игнорируем все остальное, включая кавычки, пробелы и т.д.
        }
        
        // Если не было цифр, возвращаем пустую строку
        if (!has_digit) {
            return "";
        }
        
        return result;
    }
};