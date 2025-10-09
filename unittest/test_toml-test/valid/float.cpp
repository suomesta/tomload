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

using namespace tomload;

TEST_CASE("valid/float/exponent.toml") {
    std::vector<char> content = load_file("valid/float/exponent.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 8);
    CHECK(t["lower"].is_float() == true);
    CHECK(t["lower"].get_float() == 300.0);
    CHECK(t["upper"].is_float() == true);
    CHECK(t["upper"].get_float() == 300.0);
    CHECK(t["neg"].is_float() == true);
    CHECK(t["neg"].get_float() == 0.03);
    CHECK(t["pos"].is_float() == true);
    CHECK(t["pos"].get_float() == 300.0);
    CHECK(t["zero"].is_float() == true);
    CHECK(t["zero"].get_float() == 3.0);
    CHECK(t["pointlower"].is_float() == true);
    CHECK(t["pointlower"].get_float() == 310.0);
    CHECK(t["pointupper"].is_float() == true);
    CHECK(t["pointupper"].get_float() == 310.0);
    CHECK(t["minustenth"].is_float() == true);
    CHECK(t["minustenth"].get_float() == -0.1);
}

TEST_CASE("valid/float/float.toml") {
    std::vector<char> content = load_file("valid/float/float.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t["pi"].is_float() == true);
    CHECK(t["pi"].get_float() == 3.14);
    CHECK(t["pospi"].is_float() == true);
    CHECK(t["pospi"].get_float() == 3.14);
    CHECK(t["negpi"].is_float() == true);
    CHECK(t["negpi"].get_float() == -3.14);
    CHECK(t["zero-intpart"].is_float() == true);
    CHECK(t["zero-intpart"].get_float() == 0.123);
    CHECK(t["leading-zero-fractional"].is_float() == true);
    CHECK(t["leading-zero-fractional"].get_float() == 0.0123);
}

TEST_CASE("valid/float/inf-and-nan.toml") {
    std::vector<char> content = load_file("valid/float/inf-and-nan.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 6);
    CHECK(t["nan"].is_float() == true);
    CHECK(t["nan"].get_float() == rhs_nan{});
    CHECK(t["nan_neg"].is_float() == true);
    CHECK(t["nan_neg"].get_float() == rhs_nan{});
    CHECK(t["nan_plus"].is_float() == true);
    CHECK(t["nan_plus"].get_float() == rhs_nan{});
    CHECK(t["infinity"].is_float() == true);
    CHECK(t["infinity"].get_float() == std::numeric_limits<double>::infinity());
    CHECK(t["infinity_neg"].is_float() == true);
    CHECK(t["infinity_neg"].get_float() == -std::numeric_limits<double>::infinity());
    CHECK(t["infinity_plus"].is_float() == true);
    CHECK(t["infinity_plus"].get_float() == std::numeric_limits<double>::infinity());
}

TEST_CASE("valid/float/long.toml") {
    std::vector<char> content = load_file("valid/float/long.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["longpi"].is_float() == true);
    CHECK(t["longpi"].get_float() == 3.141592653589793);
    CHECK(t["neglongpi"].is_float() == true);
    CHECK(t["neglongpi"].get_float() == -3.141592653589793);
}

TEST_CASE("valid/float/max-int.toml") {
    std::vector<char> content = load_file("valid/float/max-int.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["max_float"].is_float() == true);
    CHECK(t["max_float"].get_float() == 9007199254740991.0);
    CHECK(t["min_float"].is_float() == true);
    CHECK(t["min_float"].get_float() == -9007199254740991.0);
}

TEST_CASE("valid/float/underscore.toml") {
    std::vector<char> content = load_file("valid/float/underscore.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["before"].is_float() == true);
    CHECK(t["before"].get_float() == 3141.5927);
    CHECK(t["after"].is_float() == true);
    CHECK(t["after"].get_float() == 3141.5927);
    CHECK(t["exponent"].is_float() == true);
    CHECK(t["exponent"].get_float() == 300000000000000.0);
}

TEST_CASE("valid/float/zero.toml") {
    std::vector<char> content = load_file("valid/float/zero.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t["zero"].is_float() == true);
    CHECK(t["zero"].get_float() == 0.0);
    CHECK(t["signed-pos"].is_float() == true);
    CHECK(t["signed-pos"].get_float() == 0.0);
    CHECK(t["signed-neg"].is_float() == true);
    CHECK(t["signed-neg"].get_float() == -0.0);
    CHECK(t["exponent"].is_float() == true);
    CHECK(t["exponent"].get_float() == 0.0);
    CHECK(t["exponent-two-0"].is_float() == true);
    CHECK(t["exponent-two-0"].get_float() == 0.0);
    CHECK(t["exponent-signed-pos"].is_float() == true);
    CHECK(t["exponent-signed-pos"].get_float() == 0.0);
    CHECK(t["exponent-signed-neg"].is_float() == true);
    CHECK(t["exponent-signed-neg"].get_float() == -0.0);
}

