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

TEST_CASE("valid/InlineTable/InlineTable_1.toml") {
    std::vector<char> content = load_file("valid/InlineTable/InlineTable_1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
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
    CHECK(t[u8"animal"].is_table() == true);
    CHECK(t[u8"animal"].size() == 1);
    CHECK(t[u8"animal"][u8"type"].is_table() == true);
    CHECK(t[u8"animal"][u8"type"].size() == 1);
    CHECK(t[u8"animal"][u8"type"][u8"name"].is_string() == true);
    CHECK(t[u8"animal"][u8"type"][u8"name"].get_string() == u8"pug");
}

TEST_CASE("valid/InlineTable/InlineTable_2.toml") {
    std::vector<char> content = load_file("valid/InlineTable/InlineTable_2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"product"].is_table() == true);
    CHECK(t[u8"product"].size() == 1);
    CHECK(t[u8"product"][u8"type"].is_table() == true);
    CHECK(t[u8"product"][u8"type"].size() == 1);
    CHECK(t[u8"product"][u8"type"][u8"name"].is_string() == true);
    CHECK(t[u8"product"][u8"type"][u8"name"].get_string() == u8"Nail");
}

TEST_CASE("valid/InlineTable/InlineTable_3.toml") {
    std::vector<char> content = load_file("valid/InlineTable/InlineTable_3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"product"].is_table() == true);
    CHECK(t[u8"product"].size() == 1);
    CHECK(t[u8"product"][u8"type"].is_table() == true);
    CHECK(t[u8"product"][u8"type"].size() == 1);
    CHECK(t[u8"product"][u8"type"][u8"name"].is_string() == true);
    CHECK(t[u8"product"][u8"type"][u8"name"].get_string() == u8"Nail");
}

