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
    std::ifstream file(std::string(TOML_TEST_DIR) + filename, std::ios::binary | std::ios::ate);
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

TEST_CASE("valid/array/bool.toml") {
    std::vector<char> content = load_file("valid/array/bool.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_array() == true);
    CHECK(t[u8"a"].size() == 2);
    CHECK(t[u8"a"][0].is_boolean() == true);
    CHECK(t[u8"a"][0].get_boolean() == true);
    CHECK(t[u8"a"][1].is_boolean() == true);
    CHECK(t[u8"a"][1].get_boolean() == false);
}

TEST_CASE("valid/array/mixed-int-array.toml") {
    std::vector<char> content = load_file("valid/array/mixed-int-array.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"arrays-and-ints"].is_array() == true);
    CHECK(t[u8"arrays-and-ints"].size() == 2);
    CHECK(t[u8"arrays-and-ints"][0].is_integer() == true);
    CHECK(t[u8"arrays-and-ints"][0].get_integer() == 1);
    CHECK(t[u8"arrays-and-ints"][1].is_array() == true);
    CHECK(t[u8"arrays-and-ints"][1].size() == 1);
    CHECK(t[u8"arrays-and-ints"][1][0].is_string() == true);
    CHECK(t[u8"arrays-and-ints"][1][0].get_string() == u8"Arrays are not integers.");
}

TEST_CASE("valid/array/mixed-int-float.toml") {
    std::vector<char> content = load_file("valid/array/mixed-int-float.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"ints-and-floats"].is_array() == true);
    CHECK(t[u8"ints-and-floats"].size() == 2);
    CHECK(t[u8"ints-and-floats"][0].is_integer() == true);
    CHECK(t[u8"ints-and-floats"][0].get_integer() == 1);
    CHECK(t[u8"ints-and-floats"][1].is_float() == true);
    CHECK(t[u8"ints-and-floats"][1].get_float() == 1.1);
}

TEST_CASE("valid/array/mixed-int-string.toml") {
    std::vector<char> content = load_file("valid/array/mixed-int-string.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"strings-and-ints"].is_array() == true);
    CHECK(t[u8"strings-and-ints"].size() == 2);
    CHECK(t[u8"strings-and-ints"][0].is_string() == true);
    CHECK(t[u8"strings-and-ints"][0].get_string() == u8"hi");
    CHECK(t[u8"strings-and-ints"][1].is_integer() == true);
    CHECK(t[u8"strings-and-ints"][1].get_integer() == 42);
}

TEST_CASE("valid/array/mixed-string-table.toml") {
    std::vector<char> content = load_file("valid/array/mixed-string-table.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
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
    CHECK(t[u8"mixed"].is_array() == true);
    CHECK(t[u8"mixed"].size() == 3);
    CHECK(t[u8"mixed"][0].is_table() == true);
    CHECK(t[u8"mixed"][0].size() == 1);
    CHECK(t[u8"mixed"][0][u8"k"].is_string() == true);
    CHECK(t[u8"mixed"][0][u8"k"].get_string() == u8"a");
    CHECK(t[u8"mixed"][1].is_string() == true);
    CHECK(t[u8"mixed"][1].get_string() == u8"b");
    CHECK(t[u8"mixed"][2].is_integer() == true);
    CHECK(t[u8"mixed"][2].get_integer() == 1);
}

TEST_CASE("valid/array/nested-double.toml") {
    std::vector<char> content = load_file("valid/array/nested-double.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"nest"].is_array() == true);
    CHECK(t[u8"nest"].size() == 1);
    CHECK(t[u8"nest"][0].is_array() == true);
    CHECK(t[u8"nest"][0].size() == 2);
    CHECK(t[u8"nest"][0][0].is_array() == true);
    CHECK(t[u8"nest"][0][0].size() == 1);
    CHECK(t[u8"nest"][0][0][0].is_string() == true);
    CHECK(t[u8"nest"][0][0][0].get_string() == u8"a");
    CHECK(t[u8"nest"][0][1].is_array() == true);
    CHECK(t[u8"nest"][0][1].size() == 3);
    CHECK(t[u8"nest"][0][1][0].is_integer() == true);
    CHECK(t[u8"nest"][0][1][0].get_integer() == 1);
    CHECK(t[u8"nest"][0][1][1].is_integer() == true);
    CHECK(t[u8"nest"][0][1][1].get_integer() == 2);
    CHECK(t[u8"nest"][0][1][2].is_array() == true);
    CHECK(t[u8"nest"][0][1][2].size() == 1);
    CHECK(t[u8"nest"][0][1][2][0].is_integer() == true);
    CHECK(t[u8"nest"][0][1][2][0].get_integer() == 3);
}

TEST_CASE("valid/array/nested-inline-table.toml") {
    std::vector<char> content = load_file("valid/array/nested-inline-table.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_array() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][0].is_table() == true);
    CHECK(t[u8"a"][0].size() == 1);
    CHECK(t[u8"a"][0][u8"b"].is_table() == true);
    CHECK(t[u8"a"][0][u8"b"].size() == 0);
}

TEST_CASE("valid/array/nospaces.toml") {
    std::vector<char> content = load_file("valid/array/nospaces.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"ints"].is_array() == true);
    CHECK(t[u8"ints"].size() == 3);
    CHECK(t[u8"ints"][0].is_integer() == true);
    CHECK(t[u8"ints"][0].get_integer() == 1);
    CHECK(t[u8"ints"][1].is_integer() == true);
    CHECK(t[u8"ints"][1].get_integer() == 2);
    CHECK(t[u8"ints"][2].is_integer() == true);
    CHECK(t[u8"ints"][2].get_integer() == 3);
}

TEST_CASE("valid/array/string-quote-comma-2.toml") {
    std::vector<char> content = load_file("valid/array/string-quote-comma-2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"title"].is_array() == true);
    CHECK(t[u8"title"].size() == 1);
    CHECK(t[u8"title"][0].is_string() == true);
    CHECK(t[u8"title"][0].get_string() == u8" \", ");
}

TEST_CASE("valid/array/string-quote-comma.toml") {
    std::vector<char> content = load_file("valid/array/string-quote-comma.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"title"].is_array() == true);
    CHECK(t[u8"title"].size() == 2);
    CHECK(t[u8"title"][0].is_string() == true);
    CHECK(t[u8"title"][0].get_string() == u8"Client: \"XXXX\", Job: XXXX");
    CHECK(t[u8"title"][1].is_string() == true);
    CHECK(t[u8"title"][1].get_string() == u8"Code: XXXX");
}

TEST_CASE("valid/array/string-with-comma-2.toml") {
    std::vector<char> content = load_file("valid/array/string-with-comma-2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"title"].is_array() == true);
    CHECK(t[u8"title"].size() == 2);
    CHECK(t[u8"title"][0].is_string() == true);
    CHECK(t[u8"title"][0].get_string() == u8"Client: XXXX,\nJob: XXXX");
    CHECK(t[u8"title"][1].is_string() == true);
    CHECK(t[u8"title"][1].get_string() == u8"Code: XXXX");
}

TEST_CASE("valid/array/string-with-comma.toml") {
    std::vector<char> content = load_file("valid/array/string-with-comma.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"title"].is_array() == true);
    CHECK(t[u8"title"].size() == 2);
    CHECK(t[u8"title"][0].is_string() == true);
    CHECK(t[u8"title"][0].get_string() == u8"Client: XXXX, Job: XXXX");
    CHECK(t[u8"title"][1].is_string() == true);
    CHECK(t[u8"title"][1].get_string() == u8"Code: XXXX");
}

TEST_CASE("valid/array/strings.toml") {
    std::vector<char> content = load_file("valid/array/strings.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
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
}

TEST_CASE("valid/array/table-array-string-backslash.toml") {
    std::vector<char> content = load_file("valid/array/table-array-string-backslash.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"foo"].is_array() == true);
    CHECK(t[u8"foo"].size() == 1);
    CHECK(t[u8"foo"][0].is_table() == true);
    CHECK(t[u8"foo"][0].size() == 1);
    CHECK(t[u8"foo"][0][u8"bar"].is_string() == true);
    CHECK(t[u8"foo"][0][u8"bar"].get_string() == u8"\"{{baz}}\"");
}

TEST_CASE("valid/array/trailing-comma.toml") {
    std::vector<char> content = load_file("valid/array/trailing-comma.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"arr-1"].is_array() == true);
    CHECK(t[u8"arr-1"].size() == 1);
    CHECK(t[u8"arr-1"][0].is_integer() == true);
    CHECK(t[u8"arr-1"][0].get_integer() == 1);
    CHECK(t[u8"arr-2"].is_array() == true);
    CHECK(t[u8"arr-2"].size() == 2);
    CHECK(t[u8"arr-2"][0].is_integer() == true);
    CHECK(t[u8"arr-2"][0].get_integer() == 2);
    CHECK(t[u8"arr-2"][1].is_integer() == true);
    CHECK(t[u8"arr-2"][1].get_integer() == 3);
    CHECK(t[u8"arr-3"].is_array() == true);
    CHECK(t[u8"arr-3"].size() == 1);
    CHECK(t[u8"arr-3"][0].is_integer() == true);
    CHECK(t[u8"arr-3"][0].get_integer() == 4);
    CHECK(t[u8"arr-4"].is_array() == true);
    CHECK(t[u8"arr-4"].size() == 2);
    CHECK(t[u8"arr-4"][0].is_integer() == true);
    CHECK(t[u8"arr-4"][0].get_integer() == 5);
    CHECK(t[u8"arr-4"][1].is_integer() == true);
    CHECK(t[u8"arr-4"][1].get_integer() == 6);
}

