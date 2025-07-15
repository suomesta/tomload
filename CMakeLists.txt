# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

# プロジェクト名と使用する言語を設定
project(test_toml_r CXX)

set(CMAKE_CXX_STANDARD 17) # C++17 for std::string_view

# a.outという実行ファイルをmain.cppとtoml_r.hppから作成
add_executable(a.out main.cpp toml_r.hpp)

target_include_directories(a.out PUBLIC ./include)

target_compile_definitions(a.out PRIVATE
    TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/samples/"
)
