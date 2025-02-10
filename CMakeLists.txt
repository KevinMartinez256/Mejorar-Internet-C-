cmake_minimum_required(VERSION 3.10)
project(InternetService)

enable_testing()

# Incluir directorios de código fuente y bibliotecas
include_directories(src)
include_directories(libs)

# Compilar el código principal
add_executable(main src/Integradora.cpp)

# Compilar las pruebas unitarias
add_executable(test_main test/test_main.cpp)
target_link_libraries(test_main libs/libgtest.a libs/libgtest_main.a pthread)
add_test(NAME TestMain COMMAND test_main)
