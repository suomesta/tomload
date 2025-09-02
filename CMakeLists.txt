cmake_minimum_required(VERSION 3.13)

project(tomload CXX)

set(CMAKE_CXX_STANDARD 14)  # set 17 if you want std::string_view

add_executable(unittest
    unittest/main.cpp unittest/test_accessor.cpp unittest/test_functions.cpp unittest/test_samples.cpp
    unittest/test_toml-test/valid/bool.cpp unittest/test_toml-test/invalid/bool.cpp
    unittest/test_toml-test/valid/integer.cpp unittest/test_toml-test/invalid/integer.cpp
    unittest/test_toml-test/valid/float.cpp unittest/test_toml-test/invalid/float.cpp
    unittest/test_toml-test/valid/string.cpp unittest/test_toml-test/invalid/string.cpp
    unittest/test_toml-test/valid/inline-table.cpp unittest/test_toml-test/invalid/inline-table.cpp
    unittest/test_toml-test/valid/table.cpp unittest/test_toml-test/invalid/table.cpp
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
    SAMPLES_DIR="${CMAKE_SOURCE_DIR}/unittest/toml.io/"
    TOML_TEST_DIR="${CMAKE_SOURCE_DIR}/unittest/toml-test/tests/"
)
