cmake_minimum_required(VERSION 3.13)

project(tomload CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(unittest
    unittest/main.cpp
    unittest/test_accessor.cpp
    unittest/test_functions.cpp
    unittest/test_parse_item.cpp
    unittest/test_toml.io/valid/Array.cpp
    unittest/test_toml.io/valid/Boolean.cpp
    unittest/test_toml.io/valid/Comment.cpp
    unittest/test_toml.io/valid/Float.cpp unittest/test_toml.io/invalid/Float.cpp
    unittest/test_toml.io/valid/InlineTable.cpp unittest/test_toml.io/invalid/InlineTable.cpp
    unittest/test_toml.io/valid/Integer.cpp
    unittest/test_toml.io/valid/Key_Value_Pair.cpp unittest/test_toml.io/invalid/Key_Value_Pair.cpp
    unittest/test_toml.io/valid/Keys.cpp unittest/test_toml.io/invalid/Keys.cpp
    unittest/test_toml.io/valid/String.cpp
    unittest/test_toml.io/valid/Table.cpp unittest/test_toml.io/invalid/Table.cpp
    unittest/test_toml-test/valid/array.cpp unittest/test_toml-test/invalid/array.cpp
    unittest/test_toml-test/valid/bool.cpp unittest/test_toml-test/invalid/bool.cpp
    unittest/test_toml-test/valid/comment.cpp
    unittest/test_toml-test/invalid/control.cpp
    unittest/test_toml-test/valid/float.cpp unittest/test_toml-test/invalid/float.cpp
 #   unittest/test_toml-test/invalid/encoding.cpp
    unittest/test_toml-test/valid/inline-table.cpp unittest/test_toml-test/invalid/inline-table.cpp
    unittest/test_toml-test/valid/integer.cpp unittest/test_toml-test/invalid/integer.cpp
    unittest/test_toml-test/valid/key.cpp unittest/test_toml-test/invalid/key.cpp
    unittest/test_toml-test/valid/root.cpp
    unittest/test_toml-test/valid/string.cpp unittest/test_toml-test/invalid/string.cpp
    unittest/test_toml-test/valid/table.cpp unittest/test_toml-test/invalid/table.cpp
    tomload/tomload.h tomload/tomload.cpp
    tomload/parser.h tomload/parser.cpp
    tomload/detail_string.h tomload/detail_string.cpp
    tomload/detail_number.h tomload/detail_number.cpp
    tomload/view_t.h tomload/view_t.cpp tomload/string_view14.hpp
)

target_include_directories(unittest PUBLIC
    ./include 
    ${CMAKE_SOURCE_DIR}
)

target_compile_definitions(unittest PRIVATE
    TOML_IO_DIR="${CMAKE_SOURCE_DIR}/unittest/toml.io/"
    TOML_TEST_DIR="${CMAKE_SOURCE_DIR}/unittest/toml-test/tests/"
)
