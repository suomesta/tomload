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

TEST_CASE("valid/integer/float64-max.toml") {
    std::vector<char> content = load_file("valid/integer/float64-max.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"max_int"].is_integer() == true);
    CHECK(t[u8"max_int"].get_integer() == 9007199254740991);
    CHECK(t[u8"min_int"].is_integer() == true);
    CHECK(t[u8"min_int"].get_integer() == -9007199254740991);
}

TEST_CASE("valid/integer/integer.toml") {
    std::vector<char> content = load_file("valid/integer/integer.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"answer"].is_integer() == true);
    CHECK(t[u8"answer"].get_integer() == 42);
    CHECK(t[u8"posanswer"].is_integer() == true);
    CHECK(t[u8"posanswer"].get_integer() == 42);
    CHECK(t[u8"neganswer"].is_integer() == true);
    CHECK(t[u8"neganswer"].get_integer() == -42);
    CHECK(t[u8"zero"].is_integer() == true);
    CHECK(t[u8"zero"].get_integer() == 0);
}

TEST_CASE("valid/integer/literals.toml") {
    std::vector<char> content = load_file("valid/integer/literals.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 9);
    CHECK(t[u8"bin1"].is_integer() == true);
    CHECK(t[u8"bin1"].get_integer() == 214);
    CHECK(t[u8"bin2"].is_integer() == true);
    CHECK(t[u8"bin2"].get_integer() == 5);
    CHECK(t[u8"oct1"].is_integer() == true);
    CHECK(t[u8"oct1"].get_integer() == 342391);
    CHECK(t[u8"oct2"].is_integer() == true);
    CHECK(t[u8"oct2"].get_integer() == 493);
    CHECK(t[u8"oct3"].is_integer() == true);
    CHECK(t[u8"oct3"].get_integer() == 501);
    CHECK(t[u8"hex1"].is_integer() == true);
    CHECK(t[u8"hex1"].get_integer() == 3735928559);
    CHECK(t[u8"hex2"].is_integer() == true);
    CHECK(t[u8"hex2"].get_integer() == 3735928559);
    CHECK(t[u8"hex3"].is_integer() == true);
    CHECK(t[u8"hex3"].get_integer() == 3735928559);
    CHECK(t[u8"hex4"].is_integer() == true);
    CHECK(t[u8"hex4"].get_integer() == 2439);
}

TEST_CASE("valid/integer/long.toml") {
    std::vector<char> content = load_file("valid/integer/long.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"int64-max"].is_integer() == true);
    CHECK(t[u8"int64-max"].get_integer() == 9223372036854775807);
    CHECK(t[u8"int64-max-neg"].is_integer() == true);
    CHECK(t[u8"int64-max-neg"].get_integer() == -9223372036854775808);
}

TEST_CASE("valid/integer/underscore.toml") {
    std::vector<char> content = load_file("valid/integer/underscore.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"kilo"].is_integer() == true);
    CHECK(t[u8"kilo"].get_integer() == 1000);
    CHECK(t[u8"x"].is_integer() == true);
    CHECK(t[u8"x"].get_integer() == 1111);
}

TEST_CASE("valid/integer/zero.toml") {
    std::vector<char> content = load_file("valid/integer/zero.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 12);
    CHECK(t[u8"d1"].is_integer() == true);
    CHECK(t[u8"d1"].get_integer() == 0);
    CHECK(t[u8"d2"].is_integer() == true);
    CHECK(t[u8"d2"].get_integer() == 0);
    CHECK(t[u8"d3"].is_integer() == true);
    CHECK(t[u8"d3"].get_integer() == 0);
    CHECK(t[u8"h1"].is_integer() == true);
    CHECK(t[u8"h1"].get_integer() == 0);
    CHECK(t[u8"h2"].is_integer() == true);
    CHECK(t[u8"h2"].get_integer() == 0);
    CHECK(t[u8"h3"].is_integer() == true);
    CHECK(t[u8"h3"].get_integer() == 0);
    CHECK(t[u8"o1"].is_integer() == true);
    CHECK(t[u8"o1"].get_integer() == 0);
    CHECK(t[u8"a2"].is_integer() == true);
    CHECK(t[u8"a2"].get_integer() == 0);
    CHECK(t[u8"a3"].is_integer() == true);
    CHECK(t[u8"a3"].get_integer() == 0);
    CHECK(t[u8"b1"].is_integer() == true);
    CHECK(t[u8"b1"].get_integer() == 0);
    CHECK(t[u8"b2"].is_integer() == true);
    CHECK(t[u8"b2"].get_integer() == 0);
    CHECK(t[u8"b3"].is_integer() == true);
    CHECK(t[u8"b3"].get_integer() == 0);
}

