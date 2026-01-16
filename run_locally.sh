#!/bin/sh

mkdir -p bin
mkdir -p output

INPUT_FILE="./input/AB_NYC_2019.csv"

echo "=== Расчет средней цены ==="
cat ${INPUT_FILE} | ./bin/mapper_mean | sort -k1 | ./bin/reducer_mean > output/mean_output.txt
cat output/mean_output.txt

printf "\n=== Расчет дисперсии цены ===\n"
cat ${INPUT_FILE} | ./bin/mapper_variance | sort -k1 | ./bin/reducer_variance > output/variance_output.txt
cat output/variance_output.txt

printf "\n=== Сводная статистика ===\n"
echo "--------------------------------------------"
printf "%-25s %12s\n" "Статистика" "Значение"
echo "--------------------------------------------"

MEAN=$(grep "Mean:" output/variance_output.txt | grep -oE '[0-9]+\.[0-9]+')
VAR=$(grep "Variance:" output/variance_output.txt | grep -oE '[0-9]+\.[0-9]+')
STDDEV=$(grep "Standard Deviation:" output/variance_output.txt | grep -oE '[0-9]+\.[0-9]+')
COUNT=$(grep "Count:" output/variance_output.txt | awk '{print $2}')

printf "%-25s $%12.2f\n" "Средняя цена" "$MEAN"
printf "%-25s %12.2f\n" "Дисперсия" "$VAR"
printf "%-25s %12.2f\n" "Стандартное отклонение" "$STDDEV"
printf "%-25s %12d\n" "Количество записей" "$COUNT"
printf "%-25s %11.1f%%\n" "Коэффициент вариации" "$(grep 'Coefficient of Variation:' output/variance_output.txt | grep -oE '[0-9]+\.[0-9]+')"
echo "--------------------------------------------"