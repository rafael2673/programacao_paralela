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
        file_name = os.path.basename(file_path)
        name_without_ext = os.path.splitext(file_name)[0]

        # Check if Makefile exists, if not create a simple one
        if not os.path.exists(os.path.join(dir_path, "Makefile")):
            is_cpp = file_path.endswith('.cpp')
            compiler = "g++" if is_cpp else "gcc"
            flags = "-fopenmp" if is_cpp else "-pthread"

            makefile_content = f"""
{name_without_ext}: {file_name}
\t{compiler} {flags} -o {name_without_ext} {file_name}

.PHONY: clean
clean:
\trm -f {name_without_ext}
"""
            with open(os.path.join(dir_path, "Makefile"), 'w') as f:
                f.write(makefile_content)

        # Run make
        process = subprocess.run(['make'], 
                              cwd=dir_path,
                              capture_output=True, 
                              text=True)

        if process.returncode != 0:
            return False, f"Erro na compilação:\n{process.stderr}"

        # Run the executable
        process = subprocess.run([f'./{name_without_ext}'], 
                              cwd=dir_path,
                              capture_output=True, 
                              text=True)

        return True, process.stdout
    except Exception as e:
        return False, f"Erro na execução: {str(e)}"

def list_files_in_directory(directory):
    files = []
    try:
        for root, _, filenames in os.walk(directory):
            for filename in filenames:
                if filename.endswith(('.c', '.cpp')):
                    files.append(os.path.join(root, filename))
    except Exception as e:
        st.error(f"Erro ao listar arquivos: {str(e)}")
    return files

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

    # Lista todos os arquivos .c e .cpp na pasta U1
    files = list_files_in_directory("U1")

    if files:
        selected_file = st.selectbox(
            "Selecione o arquivo para executar:",
            files,
            format_func=lambda x: os.path.basename(x)
        )

        # Mostra o editor de código
        code_content = read_file_content(selected_file)
        edited_code = st.text_area("Código (você pode editar):", value=code_content, height=400)

        col1, col2 = st.columns(2)
        with col1:
            if st.button("Salvar Alterações"):
                if save_file_content(selected_file, edited_code):
                    st.success("Código salvo com sucesso!")

        with col2:
            if st.button("Compilar e Executar"):
                success, output = compile_and_run(selected_file)
                if success:
                    st.success("Programa executado com sucesso!")
                    st.code(output)
                else:
                    st.error(output)
    else:
        st.info("Nenhum arquivo .c ou .cpp encontrado na pasta U1. Adicione seus arquivos à pasta para vê-los aqui.")

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
    Para executar seu código:
    1. Adicione seu arquivo .c ou .cpp na pasta da unidade (U1, U2, U3)
    2. Selecione o arquivo na interface
    3. Clique em "Compilar e Executar"

    Se necessário, você pode editar o código diretamente na interface e 
    salvar suas alterações antes de executar.
    """)