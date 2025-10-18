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
    CHECK(t["table"].is_table() == true);
    CHECK(t["table"].size() == 0);
}

TEST_CASE("valid/Table/Table_11.toml") {
    std::vector<char> content = load_file("valid/Table/Table_11.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 1);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 2);
    CHECK(t["fruit"]["apple"]["color"].is_string() == true);
    CHECK(t["fruit"]["apple"]["color"].get_string() == "red");
    CHECK(t["fruit"]["apple"]["taste"].is_table() == true);
    CHECK(t["fruit"]["apple"]["taste"].size() == 1);
    CHECK(t["fruit"]["apple"]["taste"]["sweet"].is_boolean() == true);
    CHECK(t["fruit"]["apple"]["taste"]["sweet"].get_boolean() == true);
}

TEST_CASE("valid/Table/Table_12.toml") {
    std::vector<char> content = load_file("valid/Table/Table_12.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 1);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 3);
    CHECK(t["fruit"]["apple"]["color"].is_string() == true);
    CHECK(t["fruit"]["apple"]["color"].get_string() == "red");
    CHECK(t["fruit"]["apple"]["taste"].is_table() == true);
    CHECK(t["fruit"]["apple"]["taste"].size() == 1);
    CHECK(t["fruit"]["apple"]["taste"]["sweet"].is_boolean() == true);
    CHECK(t["fruit"]["apple"]["taste"]["sweet"].get_boolean() == true);
    CHECK(t["fruit"]["apple"]["texture"].is_table() == true);
    CHECK(t["fruit"]["apple"]["texture"].size() == 1);
    CHECK(t["fruit"]["apple"]["texture"]["smooth"].is_boolean() == true);
    CHECK(t["fruit"]["apple"]["texture"]["smooth"].get_boolean() == true);
}

TEST_CASE("valid/Table/Table_2.toml") {
    std::vector<char> content = load_file("valid/Table/Table_2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["table-1"].is_table() == true);
    CHECK(t["table-1"].size() == 2);
    CHECK(t["table-1"]["key1"].is_string() == true);
    CHECK(t["table-1"]["key1"].get_string() == "some string");
    CHECK(t["table-1"]["key2"].is_integer() == true);
    CHECK(t["table-1"]["key2"].get_integer() == 123);
    CHECK(t["table-2"].is_table() == true);
    CHECK(t["table-2"].size() == 2);
    CHECK(t["table-2"]["key1"].is_string() == true);
    CHECK(t["table-2"]["key1"].get_string() == "another string");
    CHECK(t["table-2"]["key2"].is_integer() == true);
    CHECK(t["table-2"]["key2"].get_integer() == 456);
}

TEST_CASE("valid/Table/Table_3.toml") {
    std::vector<char> content = load_file("valid/Table/Table_3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["dog"].is_table() == true);
    CHECK(t["dog"].size() == 1);
    CHECK(t["dog"]["tater.man"].is_table() == true);
    CHECK(t["dog"]["tater.man"].size() == 1);
    CHECK(t["dog"]["tater.man"]["type"].is_table() == true);
    CHECK(t["dog"]["tater.man"]["type"].size() == 1);
    CHECK(t["dog"]["tater.man"]["type"]["name"].is_string() == true);
    CHECK(t["dog"]["tater.man"]["type"]["name"].get_string() == "pug");
}

TEST_CASE("valid/Table/Table_4.toml") {
    std::vector<char> content = load_file("valid/Table/Table_4.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 1);
    CHECK(t["a"]["b"]["c"].is_table() == true);
    CHECK(t["a"]["b"]["c"].size() == 0);
    CHECK(t["d"].is_table() == true);
    CHECK(t["d"].size() == 1);
    CHECK(t["d"]["e"].is_table() == true);
    CHECK(t["d"]["e"].size() == 1);
    CHECK(t["d"]["e"]["f"].is_table() == true);
    CHECK(t["d"]["e"]["f"].size() == 0);
    CHECK(t["g"].is_table() == true);
    CHECK(t["g"].size() == 1);
    CHECK(t["g"]["h"].is_table() == true);
    CHECK(t["g"]["h"].size() == 1);
    CHECK(t["g"]["h"]["i"].is_table() == true);
    CHECK(t["g"]["h"]["i"].size() == 0);
    CHECK(t["j"].is_table() == true);
    CHECK(t["j"].size() == 1);
    CHECK(t["j"][u8"ʞ"].is_table() == true);
    CHECK(t["j"][u8"ʞ"].size() == 1);
    CHECK(t["j"][u8"ʞ"]["l"].is_table() == true);
    CHECK(t["j"][u8"ʞ"]["l"].size() == 0);
}

TEST_CASE("valid/Table/Table_5.toml") {
    std::vector<char> content = load_file("valid/Table/Table_5.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["x"].is_table() == true);
    CHECK(t["x"].size() == 1);
    CHECK(t["x"]["y"].is_table() == true);
    CHECK(t["x"]["y"].size() == 1);
    CHECK(t["x"]["y"]["z"].is_table() == true);
    CHECK(t["x"]["y"]["z"].size() == 1);
    CHECK(t["x"]["y"]["z"]["w"].is_table() == true);
    CHECK(t["x"]["y"]["z"]["w"].size() == 0);
}

TEST_CASE("valid/Table/Table_8.toml") {
    std::vector<char> content = load_file("valid/Table/Table_8.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 2);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 0);
    CHECK(t["fruit"]["orange"].is_table() == true);
    CHECK(t["fruit"]["orange"].size() == 0);
    CHECK(t["animal"].is_table() == true);
    CHECK(t["animal"].size() == 0);
}

TEST_CASE("valid/Table/Table_9.toml") {
    std::vector<char> content = load_file("valid/Table/Table_9.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 2);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 0);
    CHECK(t["fruit"]["orange"].is_table() == true);
    CHECK(t["fruit"]["orange"].size() == 0);
    CHECK(t["animal"].is_table() == true);
    CHECK(t["animal"].size() == 0);
}

