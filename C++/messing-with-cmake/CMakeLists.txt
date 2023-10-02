# versão minima do CMAKE pra rodar o projeto
cmake_minimum_required(VERSION 3.25.0)

# nome do projeto
project(exercise_1)

# arquivo fonte (main.c)
add_executable(main main.cpp)

# definindo C++ standard
# set(CXX_STANDARD 17)

# definindo C++ standard minimo
# set(CXX_STANDARD_REQUIRED True)

# adicionando biblioteca : nome_lib, arquivo_origem (onde ela ta sendo usada)
add_library(iostream main.cpp)

# linka o executável main com a target library declarada em libs/CMakeLists
target_link_libraries(main PUBLIC RaizQuadrada)

target_link_directories (main PUBLIC
                            "${PROJECT_SOURCE_DIR}/libs"
                        )

# adicionando um diretorio para as bibliotecas
add_subdirectory(libs)