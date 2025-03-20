import streamlit as st
import os

# Set page config
st.set_page_config(
    page_title="Programação Paralela - UFRN",
    page_icon="🔄",
    layout="wide"
)

def read_file_content(file_path):
    try:
        with open(file_path, 'r') as file:
            return file.read()
    except Exception as e:
        return f"Error reading file: {str(e)}"

# Title and Introduction
st.title("Programação Paralela - UFRN")
st.markdown("""
Este é um repositório educacional contendo exemplos práticos de programação paralela
em C/C++ para a disciplina de Programação Paralela da UFRN.
""")

# Main sections
st.header("Exemplos Disponíveis")

# POSIX Threads Section
st.subheader("1. POSIX Threads (pthreads)")
with st.expander("Ver exemplos de pthreads"):
    st.markdown("### Hello Threads")
    st.code(read_file_content("pthreads/01_hello_threads/hello_threads.c"), language="c")
    
    st.markdown("### Mutex Example")
    st.code(read_file_content("pthreads/02_mutex/mutex_example.c"), language="c")

# OpenMP Section
st.subheader("2. OpenMP")
with st.expander("Ver exemplos de OpenMP"):
    st.markdown("### Parallel For")
    st.code(read_file_content("openmp/01_parallel_for/parallel_for.cpp"), language="cpp")
    
    st.markdown("### Sections")
    st.code(read_file_content("openmp/02_sections/sections.cpp"), language="cpp")

# Compilation Instructions
st.header("Como Compilar e Executar")
st.markdown("""
Cada exemplo possui seu próprio Makefile para facilitar a compilação. Para compilar um exemplo:

1. Navegue até o diretório do exemplo desejado
2. Execute o comando `make`
3. Execute o programa gerado

Por exemplo:
```bash
cd pthreads/01_hello_threads
make
./hello_threads
```
""")

# Requirements
st.header("Requisitos")
st.markdown("""
- Compilador GCC/G++ com suporte a C11/C++11
- Biblioteca POSIX Threads (pthread)
- OpenMP
""")
