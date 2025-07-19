# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

# プロジェクト名と使用する言語を設定
project(test_toml_r CXX)

set(CMAKE_CXX_STANDARD 17) # C++17 for std::string_view

add_executable(a.out main.cpp samples.cpp tomload.hpp view_t.hpp integers.hpp)

target_include_directories(a.out PUBLIC ./include)

target_compile_definitions(a.out PRIVATE
    TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/samples/"
)
