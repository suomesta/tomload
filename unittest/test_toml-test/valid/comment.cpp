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

TEST_CASE("valid/comment/after-literal-no-ws.toml") {
    std::vector<char> content = load_file("valid/comment/after-literal-no-ws.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"inf"].is_float() == true);
    CHECK(t[u8"inf"].get_float() == std::numeric_limits<double>::infinity());
    CHECK(t[u8"nan"].is_float() == true);
    CHECK(t[u8"nan"].get_float() == rhs_nan{});
    CHECK(t[u8"true"].is_boolean() == true);
    CHECK(t[u8"true"].get_boolean() == true);
    CHECK(t[u8"false"].is_boolean() == true);
    CHECK(t[u8"false"].get_boolean() == false);
}

TEST_CASE("valid/comment/at-eof.toml") {
    std::vector<char> content = load_file("valid/comment/at-eof.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"key"].is_string() == true);
    CHECK(t[u8"key"].get_string() == u8"value");
}

TEST_CASE("valid/comment/at-eof2.toml") {
    std::vector<char> content = load_file("valid/comment/at-eof2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"key"].is_string() == true);
    CHECK(t[u8"key"].get_string() == u8"value");
}

TEST_CASE("valid/comment/noeol.toml") {
    std::vector<char> content = load_file("valid/comment/noeol.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

TEST_CASE("valid/comment/nonascii.toml") {
    std::vector<char> content = load_file("valid/comment/nonascii.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

