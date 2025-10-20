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

TEST_CASE("valid/inline-table/array-01.toml") {
    std::vector<char> content = load_file("valid/inline-table/array-01.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"arr"].is_array() == true);
    CHECK(t[u8"arr"].size() == 2);
    CHECK(t[u8"arr"][0].is_table() == true);
    CHECK(t[u8"arr"][0].size() == 1);
    CHECK(t[u8"arr"][0][u8"a"].is_integer() == true);
    CHECK(t[u8"arr"][0][u8"a"].get_integer() == 1);
    CHECK(t[u8"arr"][1].is_table() == true);
    CHECK(t[u8"arr"][1].size() == 1);
    CHECK(t[u8"arr"][1][u8"a"].is_integer() == true);
    CHECK(t[u8"arr"][1][u8"a"].get_integer() == 2);
    CHECK(t[u8"people"].is_array() == true);
    CHECK(t[u8"people"].size() == 3);
    CHECK(t[u8"people"][0].is_table() == true);
    CHECK(t[u8"people"][0].size() == 2);
    CHECK(t[u8"people"][0][u8"first_name"].is_string() == true);
    CHECK(t[u8"people"][0][u8"first_name"].get_string() == u8"Bruce");
    CHECK(t[u8"people"][0][u8"last_name"].is_string() == true);
    CHECK(t[u8"people"][0][u8"last_name"].get_string() == u8"Springsteen");
    CHECK(t[u8"people"][1].is_table() == true);
    CHECK(t[u8"people"][1].size() == 2);
    CHECK(t[u8"people"][1][u8"first_name"].is_string() == true);
    CHECK(t[u8"people"][1][u8"first_name"].get_string() == u8"Eric");
    CHECK(t[u8"people"][1][u8"last_name"].is_string() == true);
    CHECK(t[u8"people"][1][u8"last_name"].get_string() == u8"Clapton");
    CHECK(t[u8"people"][2].is_table() == true);
    CHECK(t[u8"people"][2].size() == 2);
    CHECK(t[u8"people"][2][u8"first_name"].is_string() == true);
    CHECK(t[u8"people"][2][u8"first_name"].get_string() == u8"Bob");
    CHECK(t[u8"people"][2][u8"last_name"].is_string() == true);
    CHECK(t[u8"people"][2][u8"last_name"].get_string() == u8"Seger");
}

TEST_CASE("valid/inline-table/array-02.toml") {
    std::vector<char> content = load_file("valid/inline-table/array-02.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8"a"].is_array() == true);
    CHECK(t[u8"a"][u8"a"].size() == 0);
}

TEST_CASE("valid/inline-table/array-03.toml") {
    std::vector<char> content = load_file("valid/inline-table/array-03.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"b"].is_table() == true);
    CHECK(t[u8"b"].size() == 2);
    CHECK(t[u8"b"][u8"a"].is_array() == true);
    CHECK(t[u8"b"][u8"a"].size() == 2);
    CHECK(t[u8"b"][u8"a"][0].is_integer() == true);
    CHECK(t[u8"b"][u8"a"][0].get_integer() == 1);
    CHECK(t[u8"b"][u8"a"][1].is_integer() == true);
    CHECK(t[u8"b"][u8"a"][1].get_integer() == 2);
    CHECK(t[u8"b"][u8"b"].is_array() == true);
    CHECK(t[u8"b"][u8"b"].size() == 2);
    CHECK(t[u8"b"][u8"b"][0].is_integer() == true);
    CHECK(t[u8"b"][u8"b"][0].get_integer() == 3);
    CHECK(t[u8"b"][u8"b"][1].is_integer() == true);
    CHECK(t[u8"b"][u8"b"][1].get_integer() == 4);
}

TEST_CASE("valid/inline-table/bool.toml") {
    std::vector<char> content = load_file("valid/inline-table/bool.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 2);
    CHECK(t[u8"a"][u8"a"].is_boolean() == true);
    CHECK(t[u8"a"][u8"a"].get_boolean() == true);
    CHECK(t[u8"a"][u8"b"].is_boolean() == true);
    CHECK(t[u8"a"][u8"b"].get_boolean() == false);
}

TEST_CASE("valid/inline-table/empty.toml") {
    std::vector<char> content = load_file("valid/inline-table/empty.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t[u8"empty1"].is_table() == true);
    CHECK(t[u8"empty1"].size() == 0);
    CHECK(t[u8"empty2"].is_table() == true);
    CHECK(t[u8"empty2"].size() == 0);
    CHECK(t[u8"empty_in_array"].is_array() == true);
    CHECK(t[u8"empty_in_array"].size() == 2);
    CHECK(t[u8"empty_in_array"][0].is_table() == true);
    CHECK(t[u8"empty_in_array"][0].size() == 1);
    CHECK(t[u8"empty_in_array"][0][u8"not_empty"].is_integer() == true);
    CHECK(t[u8"empty_in_array"][0][u8"not_empty"].get_integer() == 1);
    CHECK(t[u8"empty_in_array"][1].is_table() == true);
    CHECK(t[u8"empty_in_array"][1].size() == 0);
    CHECK(t[u8"empty_in_array2"].is_array() == true);
    CHECK(t[u8"empty_in_array2"].size() == 2);
    CHECK(t[u8"empty_in_array2"][0].is_table() == true);
    CHECK(t[u8"empty_in_array2"][0].size() == 0);
    CHECK(t[u8"empty_in_array2"][1].is_table() == true);
    CHECK(t[u8"empty_in_array2"][1].size() == 1);
    CHECK(t[u8"empty_in_array2"][1][u8"not_empty"].is_integer() == true);
    CHECK(t[u8"empty_in_array2"][1][u8"not_empty"].get_integer() == 1);
    CHECK(t[u8"many_empty"].is_array() == true);
    CHECK(t[u8"many_empty"].size() == 3);
    CHECK(t[u8"many_empty"][0].is_table() == true);
    CHECK(t[u8"many_empty"][0].size() == 0);
    CHECK(t[u8"many_empty"][1].is_table() == true);
    CHECK(t[u8"many_empty"][1].size() == 0);
    CHECK(t[u8"many_empty"][2].is_table() == true);
    CHECK(t[u8"many_empty"][2].size() == 0);
    CHECK(t[u8"nested_empty"].is_table() == true);
    CHECK(t[u8"nested_empty"].size() == 1);
    CHECK(t[u8"nested_empty"][u8"empty"].is_table() == true);
    CHECK(t[u8"nested_empty"][u8"empty"].size() == 0);
    CHECK(t[u8"with_cmt"].is_table() == true);
    CHECK(t[u8"with_cmt"].size() == 0);
}

TEST_CASE("valid/inline-table/end-in-bool.toml") {
    std::vector<char> content = load_file("valid/inline-table/end-in-bool.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"black"].is_table() == true);
    CHECK(t[u8"black"].size() == 3);
    CHECK(t[u8"black"][u8"python"].is_string() == true);
    CHECK(t[u8"black"][u8"python"].get_string() == u8">3.6");
    CHECK(t[u8"black"][u8"version"].is_string() == true);
    CHECK(t[u8"black"][u8"version"].get_string() == u8">=18.9b0");
    CHECK(t[u8"black"][u8"allow_prereleases"].is_boolean() == true);
    CHECK(t[u8"black"][u8"allow_prereleases"].get_boolean() == true);
}

TEST_CASE("valid/inline-table/inline-table.toml") {
    std::vector<char> content = load_file("valid/inline-table/inline-table.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"name"].is_table() == true);
    CHECK(t[u8"name"].size() == 2);
    CHECK(t[u8"name"][u8"first"].is_string() == true);
    CHECK(t[u8"name"][u8"first"].get_string() == u8"Tom");
    CHECK(t[u8"name"][u8"last"].is_string() == true);
    CHECK(t[u8"name"][u8"last"].get_string() == u8"Preston-Werner");
    CHECK(t[u8"point"].is_table() == true);
    CHECK(t[u8"point"].size() == 2);
    CHECK(t[u8"point"][u8"x"].is_integer() == true);
    CHECK(t[u8"point"][u8"x"].get_integer() == 1);
    CHECK(t[u8"point"][u8"y"].is_integer() == true);
    CHECK(t[u8"point"][u8"y"].get_integer() == 2);
    CHECK(t[u8"simple"].is_table() == true);
    CHECK(t[u8"simple"].size() == 1);
    CHECK(t[u8"simple"][u8"a"].is_integer() == true);
    CHECK(t[u8"simple"][u8"a"].get_integer() == 1);
    CHECK(t[u8"str-key"].is_table() == true);
    CHECK(t[u8"str-key"].size() == 1);
    CHECK(t[u8"str-key"][u8"a"].is_integer() == true);
    CHECK(t[u8"str-key"][u8"a"].get_integer() == 1);
    CHECK(t[u8"table-array"].is_array() == true);
    CHECK(t[u8"table-array"].size() == 2);
    CHECK(t[u8"table-array"][0].is_table() == true);
    CHECK(t[u8"table-array"][0].size() == 1);
    CHECK(t[u8"table-array"][0][u8"a"].is_integer() == true);
    CHECK(t[u8"table-array"][0][u8"a"].get_integer() == 1);
    CHECK(t[u8"table-array"][1].is_table() == true);
    CHECK(t[u8"table-array"][1].size() == 1);
    CHECK(t[u8"table-array"][1][u8"b"].is_integer() == true);
    CHECK(t[u8"table-array"][1][u8"b"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/key-dotted-1.toml") {
    std::vector<char> content = load_file("valid/inline-table/key-dotted-1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8"a"].is_table() == true);
    CHECK(t[u8"a"][u8"a"].size() == 1);
    CHECK(t[u8"a"][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"a"][u8"a"][u8"b"].get_integer() == 1);
    CHECK(t[u8"b"].is_table() == true);
    CHECK(t[u8"b"].size() == 1);
    CHECK(t[u8"b"][u8"a"].is_table() == true);
    CHECK(t[u8"b"][u8"a"].size() == 1);
    CHECK(t[u8"b"][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"b"][u8"a"][u8"b"].get_integer() == 1);
    CHECK(t[u8"c"].is_table() == true);
    CHECK(t[u8"c"].size() == 1);
    CHECK(t[u8"c"][u8"a"].is_table() == true);
    CHECK(t[u8"c"][u8"a"].size() == 1);
    CHECK(t[u8"c"][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"c"][u8"a"][u8"b"].get_integer() == 1);
    CHECK(t[u8"d"].is_table() == true);
    CHECK(t[u8"d"].size() == 1);
    CHECK(t[u8"d"][u8"a"].is_table() == true);
    CHECK(t[u8"d"][u8"a"].size() == 1);
    CHECK(t[u8"d"][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"d"][u8"a"][u8"b"].get_integer() == 1);
    CHECK(t[u8"e"].is_table() == true);
    CHECK(t[u8"e"].size() == 1);
    CHECK(t[u8"e"][u8"a"].is_table() == true);
    CHECK(t[u8"e"][u8"a"].size() == 1);
    CHECK(t[u8"e"][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"e"][u8"a"][u8"b"].get_integer() == 1);
}

TEST_CASE("valid/inline-table/key-dotted-2.toml") {
    std::vector<char> content = load_file("valid/inline-table/key-dotted-2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"many"].is_table() == true);
    CHECK(t[u8"many"].size() == 1);
    CHECK(t[u8"many"][u8"dots"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"here"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"][u8"here"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"][u8"a"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"][u8"a"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"][u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"][u8"a"][u8"b"].size() == 2);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"][u8"a"][u8"b"][u8"c"].is_integer() == true);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"][u8"a"][u8"b"][u8"c"].get_integer() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"][u8"a"][u8"b"][u8"d"].is_integer() == true);
    CHECK(t[u8"many"][u8"dots"][u8"here"][u8"dot"][u8"dot"][u8"dot"][u8"a"][u8"b"][u8"d"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/key-dotted-3.toml") {
    std::vector<char> content = load_file("valid/inline-table/key-dotted-3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"tbl"].is_table() == true);
    CHECK(t[u8"tbl"].size() == 2);
    CHECK(t[u8"tbl"][u8"a"].is_table() == true);
    CHECK(t[u8"tbl"][u8"a"].size() == 1);
    CHECK(t[u8"tbl"][u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"tbl"][u8"a"][u8"b"].size() == 1);
    CHECK(t[u8"tbl"][u8"a"][u8"b"][u8"c"].is_table() == true);
    CHECK(t[u8"tbl"][u8"a"][u8"b"][u8"c"].size() == 1);
    CHECK(t[u8"tbl"][u8"a"][u8"b"][u8"c"][u8"d"].is_table() == true);
    CHECK(t[u8"tbl"][u8"a"][u8"b"][u8"c"][u8"d"].size() == 1);
    CHECK(t[u8"tbl"][u8"a"][u8"b"][u8"c"][u8"d"][u8"e"].is_integer() == true);
    CHECK(t[u8"tbl"][u8"a"][u8"b"][u8"c"][u8"d"][u8"e"].get_integer() == 1);
    CHECK(t[u8"tbl"][u8"x"].is_table() == true);
    CHECK(t[u8"tbl"][u8"x"].size() == 1);
    CHECK(t[u8"tbl"][u8"x"][u8"a"].is_table() == true);
    CHECK(t[u8"tbl"][u8"x"][u8"a"].size() == 1);
    CHECK(t[u8"tbl"][u8"x"][u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"tbl"][u8"x"][u8"a"][u8"b"].size() == 1);
    CHECK(t[u8"tbl"][u8"x"][u8"a"][u8"b"][u8"c"].is_table() == true);
    CHECK(t[u8"tbl"][u8"x"][u8"a"][u8"b"][u8"c"].size() == 1);
    CHECK(t[u8"tbl"][u8"x"][u8"a"][u8"b"][u8"c"][u8"d"].is_table() == true);
    CHECK(t[u8"tbl"][u8"x"][u8"a"][u8"b"][u8"c"][u8"d"].size() == 1);
    CHECK(t[u8"tbl"][u8"x"][u8"a"][u8"b"][u8"c"][u8"d"][u8"e"].is_integer() == true);
    CHECK(t[u8"tbl"][u8"x"][u8"a"][u8"b"][u8"c"][u8"d"][u8"e"].get_integer() == 1);
}

TEST_CASE("valid/inline-table/key-dotted-5.toml") {
    std::vector<char> content = load_file("valid/inline-table/key-dotted-5.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"arr-1"].is_array() == true);
    CHECK(t[u8"arr-1"].size() == 1);
    CHECK(t[u8"arr-1"][0].is_table() == true);
    CHECK(t[u8"arr-1"][0].size() == 1);
    CHECK(t[u8"arr-1"][0][u8"a"].is_table() == true);
    CHECK(t[u8"arr-1"][0][u8"a"].size() == 1);
    CHECK(t[u8"arr-1"][0][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"arr-1"][0][u8"a"][u8"b"].get_integer() == 1);
    CHECK(t[u8"arr-2"].is_array() == true);
    CHECK(t[u8"arr-2"].size() == 2);
    CHECK(t[u8"arr-2"][0].is_string() == true);
    CHECK(t[u8"arr-2"][0].get_string() == u8"str");
    CHECK(t[u8"arr-2"][1].is_table() == true);
    CHECK(t[u8"arr-2"][1].size() == 1);
    CHECK(t[u8"arr-2"][1][u8"a"].is_table() == true);
    CHECK(t[u8"arr-2"][1][u8"a"].size() == 1);
    CHECK(t[u8"arr-2"][1][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"arr-2"][1][u8"a"][u8"b"].get_integer() == 1);
    CHECK(t[u8"arr-3"].is_array() == true);
    CHECK(t[u8"arr-3"].size() == 2);
    CHECK(t[u8"arr-3"][0].is_table() == true);
    CHECK(t[u8"arr-3"][0].size() == 1);
    CHECK(t[u8"arr-3"][0][u8"a"].is_table() == true);
    CHECK(t[u8"arr-3"][0][u8"a"].size() == 1);
    CHECK(t[u8"arr-3"][0][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"arr-3"][0][u8"a"][u8"b"].get_integer() == 1);
    CHECK(t[u8"arr-3"][1].is_table() == true);
    CHECK(t[u8"arr-3"][1].size() == 1);
    CHECK(t[u8"arr-3"][1][u8"a"].is_table() == true);
    CHECK(t[u8"arr-3"][1][u8"a"].size() == 1);
    CHECK(t[u8"arr-3"][1][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"arr-3"][1][u8"a"][u8"b"].get_integer() == 2);
    CHECK(t[u8"arr-4"].is_array() == true);
    CHECK(t[u8"arr-4"].size() == 3);
    CHECK(t[u8"arr-4"][0].is_string() == true);
    CHECK(t[u8"arr-4"][0].get_string() == u8"str");
    CHECK(t[u8"arr-4"][1].is_table() == true);
    CHECK(t[u8"arr-4"][1].size() == 1);
    CHECK(t[u8"arr-4"][1][u8"a"].is_table() == true);
    CHECK(t[u8"arr-4"][1][u8"a"].size() == 1);
    CHECK(t[u8"arr-4"][1][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"arr-4"][1][u8"a"][u8"b"].get_integer() == 1);
    CHECK(t[u8"arr-4"][2].is_table() == true);
    CHECK(t[u8"arr-4"][2].size() == 1);
    CHECK(t[u8"arr-4"][2][u8"a"].is_table() == true);
    CHECK(t[u8"arr-4"][2][u8"a"].size() == 1);
    CHECK(t[u8"arr-4"][2][u8"a"][u8"b"].is_integer() == true);
    CHECK(t[u8"arr-4"][2][u8"a"][u8"b"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/key-dotted-6.toml") {
    std::vector<char> content = load_file("valid/inline-table/key-dotted-6.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"top"].is_table() == true);
    CHECK(t[u8"top"].size() == 1);
    CHECK(t[u8"top"][u8"dot"].is_table() == true);
    CHECK(t[u8"top"][u8"dot"].size() == 1);
    CHECK(t[u8"top"][u8"dot"][u8"dot"].is_array() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"].size() == 2);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][0].is_table() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][0].size() == 1);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][0][u8"dot"].is_table() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][0][u8"dot"].size() == 1);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][0][u8"dot"][u8"dot"].is_table() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][0][u8"dot"][u8"dot"].size() == 1);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][0][u8"dot"][u8"dot"][u8"dot"].is_integer() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][0][u8"dot"][u8"dot"][u8"dot"].get_integer() == 1);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][1].is_table() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][1].size() == 1);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][1][u8"dot"].is_table() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][1][u8"dot"].size() == 1);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][1][u8"dot"][u8"dot"].is_table() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][1][u8"dot"][u8"dot"].size() == 1);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][1][u8"dot"][u8"dot"][u8"dot"].is_integer() == true);
    CHECK(t[u8"top"][u8"dot"][u8"dot"][1][u8"dot"][u8"dot"][u8"dot"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/key-dotted-7.toml") {
    std::vector<char> content = load_file("valid/inline-table/key-dotted-7.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"arr"].is_array() == true);
    CHECK(t[u8"arr"].size() == 1);
    CHECK(t[u8"arr"][0].is_table() == true);
    CHECK(t[u8"arr"][0].size() == 1);
    CHECK(t[u8"arr"][0][u8"a"].is_table() == true);
    CHECK(t[u8"arr"][0][u8"a"].size() == 1);
    CHECK(t[u8"arr"][0][u8"a"][u8"b"].is_array() == true);
    CHECK(t[u8"arr"][0][u8"a"][u8"b"].size() == 1);
    CHECK(t[u8"arr"][0][u8"a"][u8"b"][0].is_table() == true);
    CHECK(t[u8"arr"][0][u8"a"][u8"b"][0].size() == 1);
    CHECK(t[u8"arr"][0][u8"a"][u8"b"][0][u8"c"].is_table() == true);
    CHECK(t[u8"arr"][0][u8"a"][u8"b"][0][u8"c"].size() == 1);
    CHECK(t[u8"arr"][0][u8"a"][u8"b"][0][u8"c"][u8"d"].is_integer() == true);
    CHECK(t[u8"arr"][0][u8"a"][u8"b"][0][u8"c"][u8"d"].get_integer() == 1);
}

TEST_CASE("valid/inline-table/multiline.toml") {
    std::vector<char> content = load_file("valid/inline-table/multiline.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"tbl_multiline"].is_table() == true);
    CHECK(t[u8"tbl_multiline"].size() == 4);
    CHECK(t[u8"tbl_multiline"][u8"a"].is_integer() == true);
    CHECK(t[u8"tbl_multiline"][u8"a"].get_integer() == 1);
    CHECK(t[u8"tbl_multiline"][u8"b"].is_string() == true);
    CHECK(t[u8"tbl_multiline"][u8"b"].get_string() == u8"multiline\n");
    CHECK(t[u8"tbl_multiline"][u8"c"].is_string() == true);
    CHECK(t[u8"tbl_multiline"][u8"c"].get_string() == u8"and yet\nanother line");
    CHECK(t[u8"tbl_multiline"][u8"d"].is_integer() == true);
    CHECK(t[u8"tbl_multiline"][u8"d"].get_integer() == 4);
}

TEST_CASE("valid/inline-table/nest.toml") {
    std::vector<char> content = load_file("valid/inline-table/nest.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t[u8"tbl_tbl_empty"].is_table() == true);
    CHECK(t[u8"tbl_tbl_empty"].size() == 1);
    CHECK(t[u8"tbl_tbl_empty"][u8"tbl_0"].is_table() == true);
    CHECK(t[u8"tbl_tbl_empty"][u8"tbl_0"].size() == 0);
    CHECK(t[u8"tbl_tbl_val"].is_table() == true);
    CHECK(t[u8"tbl_tbl_val"].size() == 1);
    CHECK(t[u8"tbl_tbl_val"][u8"tbl_1"].is_table() == true);
    CHECK(t[u8"tbl_tbl_val"][u8"tbl_1"].size() == 1);
    CHECK(t[u8"tbl_tbl_val"][u8"tbl_1"][u8"one"].is_integer() == true);
    CHECK(t[u8"tbl_tbl_val"][u8"tbl_1"][u8"one"].get_integer() == 1);
    CHECK(t[u8"tbl_arr_tbl"].is_table() == true);
    CHECK(t[u8"tbl_arr_tbl"].size() == 1);
    CHECK(t[u8"tbl_arr_tbl"][u8"arr_tbl"].is_array() == true);
    CHECK(t[u8"tbl_arr_tbl"][u8"arr_tbl"].size() == 1);
    CHECK(t[u8"tbl_arr_tbl"][u8"arr_tbl"][0].is_table() == true);
    CHECK(t[u8"tbl_arr_tbl"][u8"arr_tbl"][0].size() == 1);
    CHECK(t[u8"tbl_arr_tbl"][u8"arr_tbl"][0][u8"one"].is_integer() == true);
    CHECK(t[u8"tbl_arr_tbl"][u8"arr_tbl"][0][u8"one"].get_integer() == 1);
    CHECK(t[u8"arr_tbl_tbl"].is_array() == true);
    CHECK(t[u8"arr_tbl_tbl"].size() == 1);
    CHECK(t[u8"arr_tbl_tbl"][0].is_table() == true);
    CHECK(t[u8"arr_tbl_tbl"][0].size() == 1);
    CHECK(t[u8"arr_tbl_tbl"][0][u8"tbl"].is_table() == true);
    CHECK(t[u8"arr_tbl_tbl"][0][u8"tbl"].size() == 1);
    CHECK(t[u8"arr_tbl_tbl"][0][u8"tbl"][u8"one"].is_integer() == true);
    CHECK(t[u8"arr_tbl_tbl"][0][u8"tbl"][u8"one"].get_integer() == 1);
    CHECK(t[u8"arr_arr_tbl_empty"].is_array() == true);
    CHECK(t[u8"arr_arr_tbl_empty"].size() == 1);
    CHECK(t[u8"arr_arr_tbl_empty"][0].is_array() == true);
    CHECK(t[u8"arr_arr_tbl_empty"][0].size() == 1);
    CHECK(t[u8"arr_arr_tbl_empty"][0][0].is_table() == true);
    CHECK(t[u8"arr_arr_tbl_empty"][0][0].size() == 0);
    CHECK(t[u8"arr_arr_tbl_val"].is_array() == true);
    CHECK(t[u8"arr_arr_tbl_val"].size() == 1);
    CHECK(t[u8"arr_arr_tbl_val"][0].is_array() == true);
    CHECK(t[u8"arr_arr_tbl_val"][0].size() == 1);
    CHECK(t[u8"arr_arr_tbl_val"][0][0].is_table() == true);
    CHECK(t[u8"arr_arr_tbl_val"][0][0].size() == 1);
    CHECK(t[u8"arr_arr_tbl_val"][0][0][u8"one"].is_integer() == true);
    CHECK(t[u8"arr_arr_tbl_val"][0][0][u8"one"].get_integer() == 1);
    CHECK(t[u8"arr_arr_tbls"].is_array() == true);
    CHECK(t[u8"arr_arr_tbls"].size() == 1);
    CHECK(t[u8"arr_arr_tbls"][0].is_array() == true);
    CHECK(t[u8"arr_arr_tbls"][0].size() == 2);
    CHECK(t[u8"arr_arr_tbls"][0][0].is_table() == true);
    CHECK(t[u8"arr_arr_tbls"][0][0].size() == 1);
    CHECK(t[u8"arr_arr_tbls"][0][0][u8"one"].is_integer() == true);
    CHECK(t[u8"arr_arr_tbls"][0][0][u8"one"].get_integer() == 1);
    CHECK(t[u8"arr_arr_tbls"][0][1].is_table() == true);
    CHECK(t[u8"arr_arr_tbls"][0][1].size() == 1);
    CHECK(t[u8"arr_arr_tbls"][0][1][u8"two"].is_integer() == true);
    CHECK(t[u8"arr_arr_tbls"][0][1][u8"two"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/spaces.toml") {
    std::vector<char> content = load_file("valid/inline-table/spaces.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"clap-1"].is_table() == true);
    CHECK(t[u8"clap-1"].size() == 2);
    CHECK(t[u8"clap-1"][u8"version"].is_string() == true);
    CHECK(t[u8"clap-1"][u8"version"].get_string() == u8"4");
    CHECK(t[u8"clap-1"][u8"features"].is_array() == true);
    CHECK(t[u8"clap-1"][u8"features"].size() == 2);
    CHECK(t[u8"clap-1"][u8"features"][0].is_string() == true);
    CHECK(t[u8"clap-1"][u8"features"][0].get_string() == u8"derive");
    CHECK(t[u8"clap-1"][u8"features"][1].is_string() == true);
    CHECK(t[u8"clap-1"][u8"features"][1].get_string() == u8"cargo");
    CHECK(t[u8"clap-2"].is_table() == true);
    CHECK(t[u8"clap-2"].size() == 3);
    CHECK(t[u8"clap-2"][u8"version"].is_string() == true);
    CHECK(t[u8"clap-2"][u8"version"].get_string() == u8"4");
    CHECK(t[u8"clap-2"][u8"features"].is_array() == true);
    CHECK(t[u8"clap-2"][u8"features"].size() == 2);
    CHECK(t[u8"clap-2"][u8"features"][0].is_string() == true);
    CHECK(t[u8"clap-2"][u8"features"][0].get_string() == u8"derive");
    CHECK(t[u8"clap-2"][u8"features"][1].is_string() == true);
    CHECK(t[u8"clap-2"][u8"features"][1].get_string() == u8"cargo");
    CHECK(t[u8"clap-2"][u8"nest"].is_table() == true);
    CHECK(t[u8"clap-2"][u8"nest"].size() == 2);
    CHECK(t[u8"clap-2"][u8"nest"][u8"a"].is_string() == true);
    CHECK(t[u8"clap-2"][u8"nest"][u8"a"].get_string() == u8"x");
    CHECK(t[u8"clap-2"][u8"nest"][u8"b"].is_array() == true);
    CHECK(t[u8"clap-2"][u8"nest"][u8"b"].size() == 2);
    CHECK(t[u8"clap-2"][u8"nest"][u8"b"][0].is_float() == true);
    CHECK(t[u8"clap-2"][u8"nest"][u8"b"][0].get_float() == 1.5);
    CHECK(t[u8"clap-2"][u8"nest"][u8"b"][1].is_float() == true);
    CHECK(t[u8"clap-2"][u8"nest"][u8"b"][1].get_float() == 9.0);
}

