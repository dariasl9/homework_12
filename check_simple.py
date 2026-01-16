#!/usr/bin/env python3
import csv
import math
import os

def main():
    filename = 'input/AB_NYC_2019.csv'
    
    if not os.path.exists(filename):
        print(f"Файл {filename} не найден!")
        return
    
    prices = []
    
    with open(filename, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for row in reader:
            if len(row) >= 10:
                try:
                    price = float(row[9])
                    if price >= 0:
                        prices.append(price)
                except ValueError:
                    pass
    
    if not prices:
        print("Не удалось получить данные")
        return
    
    n = len(prices)
    mean = sum(prices) / n
    variance = sum((x - mean) ** 2 for x in prices) / (n - 1)
    stddev = math.sqrt(variance)
    
    print('Python результаты:')
    print(f'  Количество: {n}')
    print(f'  Среднее: ${mean:.2f}')
    print(f'  Дисперсия: {variance:.2f}')
    print(f'  Стандартное отклонение: ${stddev:.2f}')
    print(f'  Коэффициент вариации: {stddev/mean*100:.2f}%')

if __name__ == "__main__":
    main()