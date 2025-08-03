# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

# プロジェクト名と使用する言語を設定
project(tomload CXX)

set(CMAKE_CXX_STANDARD 14) # C++17 if you want std::string_view

add_executable(unittest
    unittest/main.cpp unittest/test_functions.cpp unittest/test_samples.cpp
    unittest/toml-test_runs/valid/bool.cpp unittest/toml-test_runs/invalid/bool.cpp
    tomload/tomload.h tomload/tomload.cpp
    tomload/parser.h tomload/parser.cpp
    tomload/detail_string.h tomload/detail_string.cpp
    tomload/detail_number.h tomload/detail_number.cpp
    tomload/view_t.hpp include/string_view14.hpp
)

target_include_directories(unittest PUBLIC
    ./include 
    ${CMAKE_SOURCE_DIR}
)

target_compile_definitions(unittest PRIVATE
    SAMPLES_DIR="${CMAKE_SOURCE_DIR}/unittest/samples/"
    TOML_TEST_DIR="${CMAKE_SOURCE_DIR}/unittest/toml-test/tests/"
)
