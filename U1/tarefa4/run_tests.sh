#!/bin/bash

THREADS=(1 2 4 8 16)
VALUES=(1000000 5000000 10000000 20000000 30000000 40000000 50000000 60000000 80000000 100000000)
echo "Iniciando testes..." > resultados.txt

for VALUE in "${VALUES[@]}"; do
    echo -e "\nUsando tamanho/iterações: $VALUE\n" | tee -a resultados.txt

    echo "Memory-bound:" | tee -a resultados.txt
    for t in "${THREADS[@]}"; do
        output=$(./memoryBound $t $VALUE)
        time=$(echo "$output" | grep "segundos" | grep -oP '[0-9]+\.[0-9]+')
        echo "$t threads: tempo = $time segundos" | tee -a resultados.txt
    done

    echo -e "\nCPU-bound:" | tee -a resultados.txt
    for t in "${THREADS[@]}"; do
        output=$(./cpuBound $t $VALUE)
        time=$(echo "$output" | grep "segundos" | grep -oP '[0-9]+\.[0-9]+')
        echo "$t threads: tempo = $time segundos" | tee -a resultados.txt
    done
done
