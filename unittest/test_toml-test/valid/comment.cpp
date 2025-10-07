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

TEST_CASE("valid/comment/after-literal-no-ws.toml") {
    std::string content = load_file("valid/comment/after-literal-no-ws.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["inf"].is_float() == true);
    CHECK(t["inf"].get_float() == std::numeric_limits<double>::infinity());
    CHECK(t["nan"].is_float() == true);
    CHECK(t["nan"].get_float() == rhs_nan{});
    CHECK(t["true"].is_boolean() == true);
    CHECK(t["true"].get_boolean() == true);
    CHECK(t["false"].is_boolean() == true);
    CHECK(t["false"].get_boolean() == false);
}

TEST_CASE("valid/comment/at-eof.toml") {
    std::string content = load_file("valid/comment/at-eof.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["key"].is_string() == true);
    CHECK(t["key"].get_string() == "value");
}

TEST_CASE("valid/comment/at-eof2.toml") {
    std::string content = load_file("valid/comment/at-eof2.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["key"].is_string() == true);
    CHECK(t["key"].get_string() == "value");
}

TEST_CASE("valid/comment/noeol.toml") {
    std::string content = load_file("valid/comment/noeol.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

TEST_CASE("valid/comment/nonascii.toml") {
    std::string content = load_file("valid/comment/nonascii.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

