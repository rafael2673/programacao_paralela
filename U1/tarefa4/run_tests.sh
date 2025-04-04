#!/bin/bash

VALUE=${1:-100}  # tamanho padrão

echo "Usando tamanho/iterações: $VALUE"

echo ""
echo "Memory-bound:"
for t in 1 2 4 8 16; do
  echo -n "$t threads: "
  ./memoryBound $t $VALUE
done

echo ""
echo "CPU-bound:"
for t in 1 2 4 8 16; do
  echo -n "$t threads: "
  ./cpuBound $t $VALUE
done
