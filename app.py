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

def save_file_content(file_path, content):
    try:
        os.makedirs(os.path.dirname(file_path), exist_ok=True)
        with open(file_path, 'w') as file:
            file.write(content)
        return True
    except Exception as e:
        st.error(f"Erro ao salvar arquivo: {str(e)}")
        return False

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
        # Editor de código
        code_content = read_file_content("U1/pthreads/01_hello_threads/hello_threads.c")
        edited_code = st.text_area("Código (você pode editar):", value=code_content, height=400, key="hello_threads")

        col1, col2 = st.columns(2)
        with col1:
            if st.button("Salvar Alterações", key="save_hello"):
                if save_file_content("U1/pthreads/01_hello_threads/hello_threads.c", edited_code):
                    st.success("Código salvo com sucesso!")

        with col2:
            if st.button("Executar Hello Threads"):
                success, output = compile_and_run("U1/pthreads/01_hello_threads/hello_threads.c")
                if success:
                    st.success("Programa executado com sucesso!")
                    st.code(output)
                else:
                    st.error(output)

    with st.expander("Mutex Example"):
        # Editor de código
        code_content = read_file_content("U1/pthreads/02_mutex/mutex_example.c")
        edited_code = st.text_area("Código (você pode editar):", value=code_content, height=400, key="mutex_example")

        col1, col2 = st.columns(2)
        with col1:
            if st.button("Salvar Alterações", key="save_mutex"):
                if save_file_content("U1/pthreads/02_mutex/mutex_example.c", edited_code):
                    st.success("Código salvo com sucesso!")

        with col2:
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
        # Editor de código
        code_content = read_file_content("U1/openmp/01_parallel_for/parallel_for.cpp")
        edited_code = st.text_area("Código (você pode editar):", value=code_content, height=400, key="parallel_for")

        col1, col2 = st.columns(2)
        with col1:
            if st.button("Salvar Alterações", key="save_parallel"):
                if save_file_content("U1/openmp/01_parallel_for/parallel_for.cpp", edited_code):
                    st.success("Código salvo com sucesso!")

        with col2:
            if st.button("Executar Parallel For"):
                success, output = compile_and_run("U1/openmp/01_parallel_for/parallel_for.cpp")
                if success:
                    st.success("Programa executado com sucesso!")
                    st.code(output)
                else:
                    st.error(output)

    with st.expander("Sections"):
        # Editor de código
        code_content = read_file_content("U1/openmp/02_sections/sections.cpp")
        edited_code = st.text_area("Código (você pode editar):", value=code_content, height=400, key="sections")

        col1, col2 = st.columns(2)
        with col1:
            if st.button("Salvar Alterações", key="save_sections"):
                if save_file_content("U1/openmp/02_sections/sections.cpp", edited_code):
                    st.success("Código salvo com sucesso!")

        with col2:
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

    Você também pode editar o código diretamente na interface e 
    salvar suas alterações antes de executar.
    """)