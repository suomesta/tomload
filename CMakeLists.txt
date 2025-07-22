# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

# プロジェクト名と使用する言語を設定
project(test_toml_r CXX)

set(CMAKE_CXX_STANDARD 14) # C++17 if you want std::string_view

add_executable(a.out
    main.cpp test_functions.cpp test_samples.cpp
    tomload.h tomload.cpp
    parser.h parser.cpp
    detail_string.h detail_string.cpp
    detail_number.h detail_number.cpp
    view_t.hpp include/string_view14.hpp
)

target_include_directories(a.out PUBLIC ./include)

target_compile_definitions(a.out PRIVATE
    TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/samples/"
)
