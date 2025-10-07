// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

// This file is generated automatically. Do not modify.

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <doctest/doctest.h>
#include "tomload/tomload.h"

namespace {

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(TOML_TEST_DIR) + filename);
    if (not file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

struct rhs_nan {};
bool operator==(tomload::float_t f, rhs_nan) {
    return std::isnan(f);
}

}  // namespace

using namespace tomload;

TEST_CASE("valid/array/bool.toml") {
    std::string content = load_file("valid/array/bool.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_array() == true);
    CHECK(t["a"].size() == 2);
    CHECK(t["a"][0].is_boolean() == true);
    CHECK(t["a"][0].get_boolean() == true);
    CHECK(t["a"][1].is_boolean() == true);
    CHECK(t["a"][1].get_boolean() == false);
}

TEST_CASE("valid/array/mixed-int-array.toml") {
    std::string content = load_file("valid/array/mixed-int-array.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["arrays-and-ints"].is_array() == true);
    CHECK(t["arrays-and-ints"].size() == 2);
    CHECK(t["arrays-and-ints"][0].is_integer() == true);
    CHECK(t["arrays-and-ints"][0].get_integer() == 1);
    CHECK(t["arrays-and-ints"][1].is_array() == true);
    CHECK(t["arrays-and-ints"][1].size() == 1);
    CHECK(t["arrays-and-ints"][1][0].is_string() == true);
    CHECK(t["arrays-and-ints"][1][0].get_string() == "Arrays are not integers.");
}

TEST_CASE("valid/array/mixed-int-float.toml") {
    std::string content = load_file("valid/array/mixed-int-float.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["ints-and-floats"].is_array() == true);
    CHECK(t["ints-and-floats"].size() == 2);
    CHECK(t["ints-and-floats"][0].is_integer() == true);
    CHECK(t["ints-and-floats"][0].get_integer() == 1);
    CHECK(t["ints-and-floats"][1].is_float() == true);
    CHECK(t["ints-and-floats"][1].get_float() == 1.1);
}

TEST_CASE("valid/array/mixed-int-string.toml") {
    std::string content = load_file("valid/array/mixed-int-string.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["strings-and-ints"].is_array() == true);
    CHECK(t["strings-and-ints"].size() == 2);
    CHECK(t["strings-and-ints"][0].is_string() == true);
    CHECK(t["strings-and-ints"][0].get_string() == "hi");
    CHECK(t["strings-and-ints"][1].is_integer() == true);
    CHECK(t["strings-and-ints"][1].get_integer() == 42);
}

TEST_CASE("valid/array/mixed-string-table.toml") {
    std::string content = load_file("valid/array/mixed-string-table.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["contributors"].is_array() == true);
    CHECK(t["contributors"].size() == 2);
    CHECK(t["contributors"][0].is_string() == true);
    CHECK(t["contributors"][0].get_string() == "Foo Bar <foo@example.com>");
    CHECK(t["contributors"][1].is_table() == true);
    CHECK(t["contributors"][1].size() == 3);
    CHECK(t["contributors"][1]["name"].is_string() == true);
    CHECK(t["contributors"][1]["name"].get_string() == "Baz Qux");
    CHECK(t["contributors"][1]["email"].is_string() == true);
    CHECK(t["contributors"][1]["email"].get_string() == "bazqux@example.com");
    CHECK(t["contributors"][1]["url"].is_string() == true);
    CHECK(t["contributors"][1]["url"].get_string() == "https://example.com/bazqux");
    CHECK(t["mixed"].is_array() == true);
    CHECK(t["mixed"].size() == 3);
    CHECK(t["mixed"][0].is_table() == true);
    CHECK(t["mixed"][0].size() == 1);
    CHECK(t["mixed"][0]["k"].is_string() == true);
    CHECK(t["mixed"][0]["k"].get_string() == "a");
    CHECK(t["mixed"][1].is_string() == true);
    CHECK(t["mixed"][1].get_string() == "b");
    CHECK(t["mixed"][2].is_integer() == true);
    CHECK(t["mixed"][2].get_integer() == 1);
}

TEST_CASE("valid/array/nested-double.toml") {
    std::string content = load_file("valid/array/nested-double.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["nest"].is_array() == true);
    CHECK(t["nest"].size() == 1);
    CHECK(t["nest"][0].is_array() == true);
    CHECK(t["nest"][0].size() == 2);
    CHECK(t["nest"][0][0].is_array() == true);
    CHECK(t["nest"][0][0].size() == 1);
    CHECK(t["nest"][0][0][0].is_string() == true);
    CHECK(t["nest"][0][0][0].get_string() == "a");
    CHECK(t["nest"][0][1].is_array() == true);
    CHECK(t["nest"][0][1].size() == 3);
    CHECK(t["nest"][0][1][0].is_integer() == true);
    CHECK(t["nest"][0][1][0].get_integer() == 1);
    CHECK(t["nest"][0][1][1].is_integer() == true);
    CHECK(t["nest"][0][1][1].get_integer() == 2);
    CHECK(t["nest"][0][1][2].is_array() == true);
    CHECK(t["nest"][0][1][2].size() == 1);
    CHECK(t["nest"][0][1][2][0].is_integer() == true);
    CHECK(t["nest"][0][1][2][0].get_integer() == 3);
}

TEST_CASE("valid/array/nested-inline-table.toml") {
    std::string content = load_file("valid/array/nested-inline-table.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_array() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"][0].is_table() == true);
    CHECK(t["a"][0].size() == 1);
    CHECK(t["a"][0]["b"].is_table() == true);
    CHECK(t["a"][0]["b"].size() == 0);
}

TEST_CASE("valid/array/nospaces.toml") {
    std::string content = load_file("valid/array/nospaces.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["ints"].is_array() == true);
    CHECK(t["ints"].size() == 3);
    CHECK(t["ints"][0].is_integer() == true);
    CHECK(t["ints"][0].get_integer() == 1);
    CHECK(t["ints"][1].is_integer() == true);
    CHECK(t["ints"][1].get_integer() == 2);
    CHECK(t["ints"][2].is_integer() == true);
    CHECK(t["ints"][2].get_integer() == 3);
}

TEST_CASE("valid/array/string-quote-comma-2.toml") {
    std::string content = load_file("valid/array/string-quote-comma-2.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["title"].is_array() == true);
    CHECK(t["title"].size() == 1);
    CHECK(t["title"][0].is_string() == true);
    CHECK(t["title"][0].get_string() == " \", ");
}

TEST_CASE("valid/array/string-quote-comma.toml") {
    std::string content = load_file("valid/array/string-quote-comma.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["title"].is_array() == true);
    CHECK(t["title"].size() == 2);
    CHECK(t["title"][0].is_string() == true);
    CHECK(t["title"][0].get_string() == "Client: \"XXXX\", Job: XXXX");
    CHECK(t["title"][1].is_string() == true);
    CHECK(t["title"][1].get_string() == "Code: XXXX");
}

TEST_CASE("valid/array/string-with-comma-2.toml") {
    std::string content = load_file("valid/array/string-with-comma-2.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["title"].is_array() == true);
    CHECK(t["title"].size() == 2);
    CHECK(t["title"][0].is_string() == true);
    CHECK(t["title"][0].get_string() == "Client: XXXX,\nJob: XXXX");
    CHECK(t["title"][1].is_string() == true);
    CHECK(t["title"][1].get_string() == "Code: XXXX");
}

TEST_CASE("valid/array/string-with-comma.toml") {
    std::string content = load_file("valid/array/string-with-comma.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["title"].is_array() == true);
    CHECK(t["title"].size() == 2);
    CHECK(t["title"][0].is_string() == true);
    CHECK(t["title"][0].get_string() == "Client: XXXX, Job: XXXX");
    CHECK(t["title"][1].is_string() == true);
    CHECK(t["title"][1].get_string() == "Code: XXXX");
}

TEST_CASE("valid/array/strings.toml") {
    std::string content = load_file("valid/array/strings.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["string_array"].is_array() == true);
    CHECK(t["string_array"].size() == 4);
    CHECK(t["string_array"][0].is_string() == true);
    CHECK(t["string_array"][0].get_string() == "all");
    CHECK(t["string_array"][1].is_string() == true);
    CHECK(t["string_array"][1].get_string() == "strings");
    CHECK(t["string_array"][2].is_string() == true);
    CHECK(t["string_array"][2].get_string() == "are the same");
    CHECK(t["string_array"][3].is_string() == true);
    CHECK(t["string_array"][3].get_string() == "type");
}

TEST_CASE("valid/array/table-array-string-backslash.toml") {
    std::string content = load_file("valid/array/table-array-string-backslash.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["foo"].is_array() == true);
    CHECK(t["foo"].size() == 1);
    CHECK(t["foo"][0].is_table() == true);
    CHECK(t["foo"][0].size() == 1);
    CHECK(t["foo"][0]["bar"].is_string() == true);
    CHECK(t["foo"][0]["bar"].get_string() == "\"{{baz}}\"");
}

TEST_CASE("valid/array/trailing-comma.toml") {
    std::string content = load_file("valid/array/trailing-comma.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["arr-1"].is_array() == true);
    CHECK(t["arr-1"].size() == 1);
    CHECK(t["arr-1"][0].is_integer() == true);
    CHECK(t["arr-1"][0].get_integer() == 1);
    CHECK(t["arr-2"].is_array() == true);
    CHECK(t["arr-2"].size() == 2);
    CHECK(t["arr-2"][0].is_integer() == true);
    CHECK(t["arr-2"][0].get_integer() == 2);
    CHECK(t["arr-2"][1].is_integer() == true);
    CHECK(t["arr-2"][1].get_integer() == 3);
    CHECK(t["arr-3"].is_array() == true);
    CHECK(t["arr-3"].size() == 1);
    CHECK(t["arr-3"][0].is_integer() == true);
    CHECK(t["arr-3"][0].get_integer() == 4);
    CHECK(t["arr-4"].is_array() == true);
    CHECK(t["arr-4"].size() == 2);
    CHECK(t["arr-4"][0].is_integer() == true);
    CHECK(t["arr-4"][0].get_integer() == 5);
    CHECK(t["arr-4"][1].is_integer() == true);
    CHECK(t["arr-4"][1].get_integer() == 6);
}

