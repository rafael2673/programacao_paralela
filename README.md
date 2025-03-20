# Programação Paralela - UFRN

Este repositório contém exemplos práticos de programação paralela em C/C++ para a disciplina de Programação Paralela da UFRN.

## Estrutura do Repositório

- `pthreads/`: Exemplos utilizando a biblioteca POSIX Threads
- `openmp/`: Exemplos utilizando OpenMP

## Requisitos

- Compilador GCC/G++ com suporte a C11/C++11
- Biblioteca POSIX Threads (pthread)
- OpenMP

## Como Compilar e Executar

Cada diretório contém seu próprio Makefile. Para compilar um exemplo:

1. Navegue até o diretório do exemplo
2. Execute o comando make
```bash
cd pthreads/01_hello_threads
make
./hello_threads
