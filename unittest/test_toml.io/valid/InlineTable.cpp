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
    std::ifstream file(std::string(TOML_IO_DIR) + filename);
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

TEST_CASE("valid/InlineTable/InlineTable_1.toml") {
    std::string content = load_file("valid/InlineTable/InlineTable_1.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["name"].is_table() == true);
    CHECK(t["name"].size() == 2);
    CHECK(t["name"]["first"].is_string() == true);
    CHECK(t["name"]["first"].get_string() == "Tom");
    CHECK(t["name"]["last"].is_string() == true);
    CHECK(t["name"]["last"].get_string() == "Preston-Werner");
    CHECK(t["point"].is_table() == true);
    CHECK(t["point"].size() == 2);
    CHECK(t["point"]["x"].is_integer() == true);
    CHECK(t["point"]["x"].get_integer() == 1);
    CHECK(t["point"]["y"].is_integer() == true);
    CHECK(t["point"]["y"].get_integer() == 2);
    CHECK(t["animal"].is_table() == true);
    CHECK(t["animal"].size() == 1);
    CHECK(t["animal"]["type"].is_table() == true);
    CHECK(t["animal"]["type"].size() == 1);
    CHECK(t["animal"]["type"]["name"].is_string() == true);
    CHECK(t["animal"]["type"]["name"].get_string() == "pug");
}

TEST_CASE("valid/InlineTable/InlineTable_2.toml") {
    std::string content = load_file("valid/InlineTable/InlineTable_2.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["product"].is_table() == true);
    CHECK(t["product"].size() == 1);
    CHECK(t["product"]["type"].is_table() == true);
    CHECK(t["product"]["type"].size() == 1);
    CHECK(t["product"]["type"]["name"].is_string() == true);
    CHECK(t["product"]["type"]["name"].get_string() == "Nail");
}

TEST_CASE("valid/InlineTable/InlineTable_3.toml") {
    std::string content = load_file("valid/InlineTable/InlineTable_3.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["product"].is_table() == true);
    CHECK(t["product"].size() == 1);
    CHECK(t["product"]["type"].is_table() == true);
    CHECK(t["product"]["type"].size() == 1);
    CHECK(t["product"]["type"]["name"].is_string() == true);
    CHECK(t["product"]["type"]["name"].get_string() == "Nail");
}

