import streamlit as st
import os
import subprocess
import sys

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

def compile_and_run(file_path):
    try:
        # Get directory and filename
        dir_path = os.path.dirname(file_path)

        # Run make
        process = subprocess.run(['make'], 
                              cwd=dir_path,
                              capture_output=True, 
                              text=True)

        if process.returncode != 0:
            return False, f"Erro na compilação:\n{process.stderr}"

        # Get the executable name (same as directory name)
        executable = os.path.basename(dir_path)

        # Run the executable
        process = subprocess.run([f'./{executable}'], 
                              cwd=dir_path,
                              capture_output=True, 
                              text=True)

        return True, process.stdout
    except Exception as e:
        return False, f"Erro na execução: {str(e)}"

# Title and Introduction
st.title("Programação Paralela - UFRN")
st.markdown("""
Este é um repositório educacional contendo exemplos práticos de programação paralela
em C/C++ para a disciplina de Programação Paralela da UFRN.
""")

# Unidades
st.header("Unidades")

# Seletor de Unidade
unidade = st.selectbox(
    "Selecione a Unidade",
    ["U1", "U2", "U3"]
)

if unidade == "U1":
    st.subheader("Unidade 1 - Introdução à Programação Paralela")

    # POSIX Threads Section
    st.markdown("### POSIX Threads (pthreads)")
    with st.expander("Hello Threads"):
        st.code(read_file_content("U1/pthreads/01_hello_threads/hello_threads.c"), language="c")
        if st.button("Executar Hello Threads"):
            success, output = compile_and_run("U1/pthreads/01_hello_threads/hello_threads.c")
            if success:
                st.success("Programa executado com sucesso!")
                st.code(output)
            else:
                st.error(output)

    with st.expander("Mutex Example"):
        st.code(read_file_content("U1/pthreads/02_mutex/mutex_example.c"), language="c")
        if st.button("Executar Mutex Example"):
            success, output = compile_and_run("U1/pthreads/02_mutex/mutex_example.c")
            if success:
                st.success("Programa executado com sucesso!")
                st.code(output)
            else:
                st.error(output)

    # OpenMP Section
    st.markdown("### OpenMP")
    with st.expander("Parallel For"):
        st.code(read_file_content("U1/openmp/01_parallel_for/parallel_for.cpp"), language="cpp")
        if st.button("Executar Parallel For"):
            success, output = compile_and_run("U1/openmp/01_parallel_for/parallel_for.cpp")
            if success:
                st.success("Programa executado com sucesso!")
                st.code(output)
            else:
                st.error(output)

    with st.expander("Sections"):
        st.code(read_file_content("U1/openmp/02_sections/sections.cpp"), language="cpp")
        if st.button("Executar Sections"):
            success, output = compile_and_run("U1/openmp/02_sections/sections.cpp")
            if success:
                st.success("Programa executado com sucesso!")
                st.code(output)
            else:
                st.error(output)

elif unidade == "U2":
    st.info("Conteúdo da Unidade 2 será adicionado em breve.")

elif unidade == "U3":
    st.info("Conteúdo da Unidade 3 será adicionado em breve.")

# Requisitos
with st.sidebar:
    st.header("Requisitos")
    st.markdown("""
    - Compilador GCC/G++ com suporte a C11/C++11
    - Biblioteca POSIX Threads (pthread)
    - OpenMP
    """)

    st.header("Como Compilar")
    st.markdown("""
    Cada exemplo possui seu próprio Makefile. O botão "Executar" 
    automaticamente compila e executa o programa selecionado.
    """)