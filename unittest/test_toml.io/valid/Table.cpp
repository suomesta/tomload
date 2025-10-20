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

TEST_CASE("valid/Table/Table_1.toml") {
    std::vector<char> content = load_file("valid/Table/Table_1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"table"].is_table() == true);
    CHECK(t[u8"table"].size() == 0);
}

TEST_CASE("valid/Table/Table_11.toml") {
    std::vector<char> content = load_file("valid/Table/Table_11.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"fruit"].is_table() == true);
    CHECK(t[u8"fruit"].size() == 1);
    CHECK(t[u8"fruit"][u8"apple"].is_table() == true);
    CHECK(t[u8"fruit"][u8"apple"].size() == 2);
    CHECK(t[u8"fruit"][u8"apple"][u8"color"].is_string() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"color"].get_string() == u8"red");
    CHECK(t[u8"fruit"][u8"apple"][u8"taste"].is_table() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"taste"].size() == 1);
    CHECK(t[u8"fruit"][u8"apple"][u8"taste"][u8"sweet"].is_boolean() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"taste"][u8"sweet"].get_boolean() == true);
}

TEST_CASE("valid/Table/Table_12.toml") {
    std::vector<char> content = load_file("valid/Table/Table_12.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"fruit"].is_table() == true);
    CHECK(t[u8"fruit"].size() == 1);
    CHECK(t[u8"fruit"][u8"apple"].is_table() == true);
    CHECK(t[u8"fruit"][u8"apple"].size() == 3);
    CHECK(t[u8"fruit"][u8"apple"][u8"color"].is_string() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"color"].get_string() == u8"red");
    CHECK(t[u8"fruit"][u8"apple"][u8"taste"].is_table() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"taste"].size() == 1);
    CHECK(t[u8"fruit"][u8"apple"][u8"taste"][u8"sweet"].is_boolean() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"taste"][u8"sweet"].get_boolean() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"texture"].is_table() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"texture"].size() == 1);
    CHECK(t[u8"fruit"][u8"apple"][u8"texture"][u8"smooth"].is_boolean() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"texture"][u8"smooth"].get_boolean() == true);
}

TEST_CASE("valid/Table/Table_2.toml") {
    std::vector<char> content = load_file("valid/Table/Table_2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"table-1"].is_table() == true);
    CHECK(t[u8"table-1"].size() == 2);
    CHECK(t[u8"table-1"][u8"key1"].is_string() == true);
    CHECK(t[u8"table-1"][u8"key1"].get_string() == u8"some string");
    CHECK(t[u8"table-1"][u8"key2"].is_integer() == true);
    CHECK(t[u8"table-1"][u8"key2"].get_integer() == 123);
    CHECK(t[u8"table-2"].is_table() == true);
    CHECK(t[u8"table-2"].size() == 2);
    CHECK(t[u8"table-2"][u8"key1"].is_string() == true);
    CHECK(t[u8"table-2"][u8"key1"].get_string() == u8"another string");
    CHECK(t[u8"table-2"][u8"key2"].is_integer() == true);
    CHECK(t[u8"table-2"][u8"key2"].get_integer() == 456);
}

TEST_CASE("valid/Table/Table_3.toml") {
    std::vector<char> content = load_file("valid/Table/Table_3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"dog"].is_table() == true);
    CHECK(t[u8"dog"].size() == 1);
    CHECK(t[u8"dog"][u8"tater.man"].is_table() == true);
    CHECK(t[u8"dog"][u8"tater.man"].size() == 1);
    CHECK(t[u8"dog"][u8"tater.man"][u8"type"].is_table() == true);
    CHECK(t[u8"dog"][u8"tater.man"][u8"type"].size() == 1);
    CHECK(t[u8"dog"][u8"tater.man"][u8"type"][u8"name"].is_string() == true);
    CHECK(t[u8"dog"][u8"tater.man"][u8"type"][u8"name"].get_string() == u8"pug");
}

TEST_CASE("valid/Table/Table_4.toml") {
    std::vector<char> content = load_file("valid/Table/Table_4.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"a"][u8"b"].size() == 1);
    CHECK(t[u8"a"][u8"b"][u8"c"].is_table() == true);
    CHECK(t[u8"a"][u8"b"][u8"c"].size() == 0);
    CHECK(t[u8"d"].is_table() == true);
    CHECK(t[u8"d"].size() == 1);
    CHECK(t[u8"d"][u8"e"].is_table() == true);
    CHECK(t[u8"d"][u8"e"].size() == 1);
    CHECK(t[u8"d"][u8"e"][u8"f"].is_table() == true);
    CHECK(t[u8"d"][u8"e"][u8"f"].size() == 0);
    CHECK(t[u8"g"].is_table() == true);
    CHECK(t[u8"g"].size() == 1);
    CHECK(t[u8"g"][u8"h"].is_table() == true);
    CHECK(t[u8"g"][u8"h"].size() == 1);
    CHECK(t[u8"g"][u8"h"][u8"i"].is_table() == true);
    CHECK(t[u8"g"][u8"h"][u8"i"].size() == 0);
    CHECK(t[u8"j"].is_table() == true);
    CHECK(t[u8"j"].size() == 1);
    CHECK(t[u8"j"][u8"ʞ"].is_table() == true);
    CHECK(t[u8"j"][u8"ʞ"].size() == 1);
    CHECK(t[u8"j"][u8"ʞ"][u8"l"].is_table() == true);
    CHECK(t[u8"j"][u8"ʞ"][u8"l"].size() == 0);
}

TEST_CASE("valid/Table/Table_5.toml") {
    std::vector<char> content = load_file("valid/Table/Table_5.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"x"].is_table() == true);
    CHECK(t[u8"x"].size() == 1);
    CHECK(t[u8"x"][u8"y"].is_table() == true);
    CHECK(t[u8"x"][u8"y"].size() == 1);
    CHECK(t[u8"x"][u8"y"][u8"z"].is_table() == true);
    CHECK(t[u8"x"][u8"y"][u8"z"].size() == 1);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"].is_table() == true);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"].size() == 0);
}

TEST_CASE("valid/Table/Table_8.toml") {
    std::vector<char> content = load_file("valid/Table/Table_8.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"fruit"].is_table() == true);
    CHECK(t[u8"fruit"].size() == 2);
    CHECK(t[u8"fruit"][u8"apple"].is_table() == true);
    CHECK(t[u8"fruit"][u8"apple"].size() == 0);
    CHECK(t[u8"fruit"][u8"orange"].is_table() == true);
    CHECK(t[u8"fruit"][u8"orange"].size() == 0);
    CHECK(t[u8"animal"].is_table() == true);
    CHECK(t[u8"animal"].size() == 0);
}

TEST_CASE("valid/Table/Table_9.toml") {
    std::vector<char> content = load_file("valid/Table/Table_9.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"fruit"].is_table() == true);
    CHECK(t[u8"fruit"].size() == 2);
    CHECK(t[u8"fruit"][u8"apple"].is_table() == true);
    CHECK(t[u8"fruit"][u8"apple"].size() == 0);
    CHECK(t[u8"fruit"][u8"orange"].is_table() == true);
    CHECK(t[u8"fruit"][u8"orange"].size() == 0);
    CHECK(t[u8"animal"].is_table() == true);
    CHECK(t[u8"animal"].size() == 0);
}

