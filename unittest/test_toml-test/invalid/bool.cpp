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

TEST_CASE("invalid/bool/almost-false-with-extra.toml") {
    std::vector<char> content = load_file("invalid/bool/almost-false-with-extra.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/almost-false.toml") {
    std::vector<char> content = load_file("invalid/bool/almost-false.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/almost-true-with-extra.toml") {
    std::vector<char> content = load_file("invalid/bool/almost-true-with-extra.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/almost-true.toml") {
    std::vector<char> content = load_file("invalid/bool/almost-true.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/capitalized-false.toml") {
    std::vector<char> content = load_file("invalid/bool/capitalized-false.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/capitalized-true.toml") {
    std::vector<char> content = load_file("invalid/bool/capitalized-true.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/just-f.toml") {
    std::vector<char> content = load_file("invalid/bool/just-f.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/just-t.toml") {
    std::vector<char> content = load_file("invalid/bool/just-t.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/mixed-case-false.toml") {
    std::vector<char> content = load_file("invalid/bool/mixed-case-false.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/mixed-case-true.toml") {
    std::vector<char> content = load_file("invalid/bool/mixed-case-true.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/mixed-case.toml") {
    std::vector<char> content = load_file("invalid/bool/mixed-case.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/starting-same-false.toml") {
    std::vector<char> content = load_file("invalid/bool/starting-same-false.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/starting-same-true.toml") {
    std::vector<char> content = load_file("invalid/bool/starting-same-true.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/wrong-case-false.toml") {
    std::vector<char> content = load_file("invalid/bool/wrong-case-false.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/bool/wrong-case-true.toml") {
    std::vector<char> content = load_file("invalid/bool/wrong-case-true.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

