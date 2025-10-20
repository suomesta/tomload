// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

// This file is generated automatically. Do not modify.

#include <cmath>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <doctest/doctest.h>
#include "tomload/tomload.h"

namespace {

std::vector<char> load_file(const std::string& filename) {
    std::ifstream file(std::string(TOML_IO_DIR) + filename, std::ios::binary | std::ios::ate);
    if (not file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::streamsize size = file.tellg();
    std::vector<char> buffer(size);

    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), size); 

    return buffer;
}

struct rhs_nan {};
bool operator==(tomload::float_t f, rhs_nan) {
    return std::isnan(f);
}

}  // namespace

using tomload::item_t;
using tomload::view_t;

TEST_CASE("valid/Array/Array_1.toml") {
    std::vector<char> content = load_file("valid/Array/Array_1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t[u8"integers"].is_array() == true);
    CHECK(t[u8"integers"].size() == 3);
    CHECK(t[u8"integers"][0].is_integer() == true);
    CHECK(t[u8"integers"][0].get_integer() == 1);
    CHECK(t[u8"integers"][1].is_integer() == true);
    CHECK(t[u8"integers"][1].get_integer() == 2);
    CHECK(t[u8"integers"][2].is_integer() == true);
    CHECK(t[u8"integers"][2].get_integer() == 3);
    CHECK(t[u8"colors"].is_array() == true);
    CHECK(t[u8"colors"].size() == 3);
    CHECK(t[u8"colors"][0].is_string() == true);
    CHECK(t[u8"colors"][0].get_string() == u8"red");
    CHECK(t[u8"colors"][1].is_string() == true);
    CHECK(t[u8"colors"][1].get_string() == u8"yellow");
    CHECK(t[u8"colors"][2].is_string() == true);
    CHECK(t[u8"colors"][2].get_string() == u8"green");
    CHECK(t[u8"nested_arrays_of_ints"].is_array() == true);
    CHECK(t[u8"nested_arrays_of_ints"].size() == 2);
    CHECK(t[u8"nested_arrays_of_ints"][0].is_array() == true);
    CHECK(t[u8"nested_arrays_of_ints"][0].size() == 2);
    CHECK(t[u8"nested_arrays_of_ints"][0][0].is_integer() == true);
    CHECK(t[u8"nested_arrays_of_ints"][0][0].get_integer() == 1);
    CHECK(t[u8"nested_arrays_of_ints"][0][1].is_integer() == true);
    CHECK(t[u8"nested_arrays_of_ints"][0][1].get_integer() == 2);
    CHECK(t[u8"nested_arrays_of_ints"][1].is_array() == true);
    CHECK(t[u8"nested_arrays_of_ints"][1].size() == 3);
    CHECK(t[u8"nested_arrays_of_ints"][1][0].is_integer() == true);
    CHECK(t[u8"nested_arrays_of_ints"][1][0].get_integer() == 3);
    CHECK(t[u8"nested_arrays_of_ints"][1][1].is_integer() == true);
    CHECK(t[u8"nested_arrays_of_ints"][1][1].get_integer() == 4);
    CHECK(t[u8"nested_arrays_of_ints"][1][2].is_integer() == true);
    CHECK(t[u8"nested_arrays_of_ints"][1][2].get_integer() == 5);
    CHECK(t[u8"nested_mixed_array"].is_array() == true);
    CHECK(t[u8"nested_mixed_array"].size() == 2);
    CHECK(t[u8"nested_mixed_array"][0].is_array() == true);
    CHECK(t[u8"nested_mixed_array"][0].size() == 2);
    CHECK(t[u8"nested_mixed_array"][0][0].is_integer() == true);
    CHECK(t[u8"nested_mixed_array"][0][0].get_integer() == 1);
    CHECK(t[u8"nested_mixed_array"][0][1].is_integer() == true);
    CHECK(t[u8"nested_mixed_array"][0][1].get_integer() == 2);
    CHECK(t[u8"nested_mixed_array"][1].is_array() == true);
    CHECK(t[u8"nested_mixed_array"][1].size() == 3);
    CHECK(t[u8"nested_mixed_array"][1][0].is_string() == true);
    CHECK(t[u8"nested_mixed_array"][1][0].get_string() == u8"a");
    CHECK(t[u8"nested_mixed_array"][1][1].is_string() == true);
    CHECK(t[u8"nested_mixed_array"][1][1].get_string() == u8"b");
    CHECK(t[u8"nested_mixed_array"][1][2].is_string() == true);
    CHECK(t[u8"nested_mixed_array"][1][2].get_string() == u8"c");
    CHECK(t[u8"string_array"].is_array() == true);
    CHECK(t[u8"string_array"].size() == 4);
    CHECK(t[u8"string_array"][0].is_string() == true);
    CHECK(t[u8"string_array"][0].get_string() == u8"all");
    CHECK(t[u8"string_array"][1].is_string() == true);
    CHECK(t[u8"string_array"][1].get_string() == u8"strings");
    CHECK(t[u8"string_array"][2].is_string() == true);
    CHECK(t[u8"string_array"][2].get_string() == u8"are the same");
    CHECK(t[u8"string_array"][3].is_string() == true);
    CHECK(t[u8"string_array"][3].get_string() == u8"type");
    CHECK(t[u8"numbers"].is_array() == true);
    CHECK(t[u8"numbers"].size() == 6);
    CHECK(t[u8"numbers"][0].is_float() == true);
    CHECK(t[u8"numbers"][0].get_float() == 0.1);
    CHECK(t[u8"numbers"][1].is_float() == true);
    CHECK(t[u8"numbers"][1].get_float() == 0.2);
    CHECK(t[u8"numbers"][2].is_float() == true);
    CHECK(t[u8"numbers"][2].get_float() == 0.5);
    CHECK(t[u8"numbers"][3].is_integer() == true);
    CHECK(t[u8"numbers"][3].get_integer() == 1);
    CHECK(t[u8"numbers"][4].is_integer() == true);
    CHECK(t[u8"numbers"][4].get_integer() == 2);
    CHECK(t[u8"numbers"][5].is_integer() == true);
    CHECK(t[u8"numbers"][5].get_integer() == 5);
    CHECK(t[u8"contributors"].is_array() == true);
    CHECK(t[u8"contributors"].size() == 2);
    CHECK(t[u8"contributors"][0].is_string() == true);
    CHECK(t[u8"contributors"][0].get_string() == u8"Foo Bar <foo@example.com>");
    CHECK(t[u8"contributors"][1].is_table() == true);
    CHECK(t[u8"contributors"][1].size() == 3);
    CHECK(t[u8"contributors"][1][u8"name"].is_string() == true);
    CHECK(t[u8"contributors"][1][u8"name"].get_string() == u8"Baz Qux");
    CHECK(t[u8"contributors"][1][u8"email"].is_string() == true);
    CHECK(t[u8"contributors"][1][u8"email"].get_string() == u8"bazqux@example.com");
    CHECK(t[u8"contributors"][1][u8"url"].is_string() == true);
    CHECK(t[u8"contributors"][1][u8"url"].get_string() == u8"https://example.com/bazqux");
}

TEST_CASE("valid/Array/Array_2.toml") {
    std::vector<char> content = load_file("valid/Array/Array_2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"integers2"].is_array() == true);
    CHECK(t[u8"integers2"].size() == 3);
    CHECK(t[u8"integers2"][0].is_integer() == true);
    CHECK(t[u8"integers2"][0].get_integer() == 1);
    CHECK(t[u8"integers2"][1].is_integer() == true);
    CHECK(t[u8"integers2"][1].get_integer() == 2);
    CHECK(t[u8"integers2"][2].is_integer() == true);
    CHECK(t[u8"integers2"][2].get_integer() == 3);
    CHECK(t[u8"integers3"].is_array() == true);
    CHECK(t[u8"integers3"].size() == 2);
    CHECK(t[u8"integers3"][0].is_integer() == true);
    CHECK(t[u8"integers3"][0].get_integer() == 1);
    CHECK(t[u8"integers3"][1].is_integer() == true);
    CHECK(t[u8"integers3"][1].get_integer() == 2);
}

