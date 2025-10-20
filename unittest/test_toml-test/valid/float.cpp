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

TEST_CASE("valid/float/exponent.toml") {
    std::vector<char> content = load_file("valid/float/exponent.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 8);
    CHECK(t[u8"lower"].is_float() == true);
    CHECK(t[u8"lower"].get_float() == 300.0);
    CHECK(t[u8"upper"].is_float() == true);
    CHECK(t[u8"upper"].get_float() == 300.0);
    CHECK(t[u8"neg"].is_float() == true);
    CHECK(t[u8"neg"].get_float() == 0.03);
    CHECK(t[u8"pos"].is_float() == true);
    CHECK(t[u8"pos"].get_float() == 300.0);
    CHECK(t[u8"zero"].is_float() == true);
    CHECK(t[u8"zero"].get_float() == 3.0);
    CHECK(t[u8"pointlower"].is_float() == true);
    CHECK(t[u8"pointlower"].get_float() == 310.0);
    CHECK(t[u8"pointupper"].is_float() == true);
    CHECK(t[u8"pointupper"].get_float() == 310.0);
    CHECK(t[u8"minustenth"].is_float() == true);
    CHECK(t[u8"minustenth"].get_float() == -0.1);
}

TEST_CASE("valid/float/float.toml") {
    std::vector<char> content = load_file("valid/float/float.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"pi"].is_float() == true);
    CHECK(t[u8"pi"].get_float() == 3.14);
    CHECK(t[u8"pospi"].is_float() == true);
    CHECK(t[u8"pospi"].get_float() == 3.14);
    CHECK(t[u8"negpi"].is_float() == true);
    CHECK(t[u8"negpi"].get_float() == -3.14);
    CHECK(t[u8"zero-intpart"].is_float() == true);
    CHECK(t[u8"zero-intpart"].get_float() == 0.123);
    CHECK(t[u8"leading-zero-fractional"].is_float() == true);
    CHECK(t[u8"leading-zero-fractional"].get_float() == 0.0123);
}

TEST_CASE("valid/float/inf-and-nan.toml") {
    std::vector<char> content = load_file("valid/float/inf-and-nan.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 6);
    CHECK(t[u8"nan"].is_float() == true);
    CHECK(t[u8"nan"].get_float() == rhs_nan{});
    CHECK(t[u8"nan_neg"].is_float() == true);
    CHECK(t[u8"nan_neg"].get_float() == rhs_nan{});
    CHECK(t[u8"nan_plus"].is_float() == true);
    CHECK(t[u8"nan_plus"].get_float() == rhs_nan{});
    CHECK(t[u8"infinity"].is_float() == true);
    CHECK(t[u8"infinity"].get_float() == std::numeric_limits<double>::infinity());
    CHECK(t[u8"infinity_neg"].is_float() == true);
    CHECK(t[u8"infinity_neg"].get_float() == -std::numeric_limits<double>::infinity());
    CHECK(t[u8"infinity_plus"].is_float() == true);
    CHECK(t[u8"infinity_plus"].get_float() == std::numeric_limits<double>::infinity());
}

TEST_CASE("valid/float/long.toml") {
    std::vector<char> content = load_file("valid/float/long.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"longpi"].is_float() == true);
    CHECK(t[u8"longpi"].get_float() == 3.141592653589793);
    CHECK(t[u8"neglongpi"].is_float() == true);
    CHECK(t[u8"neglongpi"].get_float() == -3.141592653589793);
}

TEST_CASE("valid/float/max-int.toml") {
    std::vector<char> content = load_file("valid/float/max-int.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"max_float"].is_float() == true);
    CHECK(t[u8"max_float"].get_float() == 9007199254740991.0);
    CHECK(t[u8"min_float"].is_float() == true);
    CHECK(t[u8"min_float"].get_float() == -9007199254740991.0);
}

TEST_CASE("valid/float/underscore.toml") {
    std::vector<char> content = load_file("valid/float/underscore.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t[u8"before"].is_float() == true);
    CHECK(t[u8"before"].get_float() == 3141.5927);
    CHECK(t[u8"after"].is_float() == true);
    CHECK(t[u8"after"].get_float() == 3141.5927);
    CHECK(t[u8"exponent"].is_float() == true);
    CHECK(t[u8"exponent"].get_float() == 300000000000000.0);
}

TEST_CASE("valid/float/zero.toml") {
    std::vector<char> content = load_file("valid/float/zero.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t[u8"zero"].is_float() == true);
    CHECK(t[u8"zero"].get_float() == 0.0);
    CHECK(t[u8"signed-pos"].is_float() == true);
    CHECK(t[u8"signed-pos"].get_float() == 0.0);
    CHECK(t[u8"signed-neg"].is_float() == true);
    CHECK(t[u8"signed-neg"].get_float() == -0.0);
    CHECK(t[u8"exponent"].is_float() == true);
    CHECK(t[u8"exponent"].get_float() == 0.0);
    CHECK(t[u8"exponent-two-0"].is_float() == true);
    CHECK(t[u8"exponent-two-0"].get_float() == 0.0);
    CHECK(t[u8"exponent-signed-pos"].is_float() == true);
    CHECK(t[u8"exponent-signed-pos"].get_float() == 0.0);
    CHECK(t[u8"exponent-signed-neg"].is_float() == true);
    CHECK(t[u8"exponent-signed-neg"].get_float() == -0.0);
}

