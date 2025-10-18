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

TEST_CASE("invalid/integer/capital-bin.toml") {
    std::vector<char> content = load_file("invalid/integer/capital-bin.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/capital-hex.toml") {
    std::vector<char> content = load_file("invalid/integer/capital-hex.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/capital-oct.toml") {
    std::vector<char> content = load_file("invalid/integer/capital-oct.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/double-sign-nex.toml") {
    std::vector<char> content = load_file("invalid/integer/double-sign-nex.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/double-sign-plus.toml") {
    std::vector<char> content = load_file("invalid/integer/double-sign-plus.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/double-us.toml") {
    std::vector<char> content = load_file("invalid/integer/double-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/incomplete-bin.toml") {
    std::vector<char> content = load_file("invalid/integer/incomplete-bin.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/incomplete-hex.toml") {
    std::vector<char> content = load_file("invalid/integer/incomplete-hex.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/incomplete-oct.toml") {
    std::vector<char> content = load_file("invalid/integer/incomplete-oct.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/invalid-bin.toml") {
    std::vector<char> content = load_file("invalid/integer/invalid-bin.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-01.toml") {
    std::vector<char> content = load_file("invalid/integer/invalid-hex-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-02.toml") {
    std::vector<char> content = load_file("invalid/integer/invalid-hex-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-03.toml") {
    std::vector<char> content = load_file("invalid/integer/invalid-hex-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-1.toml") {
    std::vector<char> content = load_file("invalid/integer/invalid-hex-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-2.toml") {
    std::vector<char> content = load_file("invalid/integer/invalid-hex-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/invalid-oct.toml") {
    std::vector<char> content = load_file("invalid/integer/invalid-oct.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-us-bin.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-us-bin.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-us-hex.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-us-hex.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-us-oct.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-us-oct.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-us.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-01.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-02.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-03.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-1.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-2.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-3.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-01.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-sign-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-02.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-sign-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-03.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-sign-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-1.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-sign-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-2.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-sign-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-3.toml") {
    std::vector<char> content = load_file("invalid/integer/leading-zero-sign-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/negative-bin.toml") {
    std::vector<char> content = load_file("invalid/integer/negative-bin.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/negative-hex.toml") {
    std::vector<char> content = load_file("invalid/integer/negative-hex.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/negative-oct.toml") {
    std::vector<char> content = load_file("invalid/integer/negative-oct.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/positive-bin.toml") {
    std::vector<char> content = load_file("invalid/integer/positive-bin.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/positive-hex.toml") {
    std::vector<char> content = load_file("invalid/integer/positive-hex.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/positive-oct.toml") {
    std::vector<char> content = load_file("invalid/integer/positive-oct.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/text-after-integer.toml") {
    std::vector<char> content = load_file("invalid/integer/text-after-integer.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/trailing-us-bin.toml") {
    std::vector<char> content = load_file("invalid/integer/trailing-us-bin.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/trailing-us-hex.toml") {
    std::vector<char> content = load_file("invalid/integer/trailing-us-hex.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/trailing-us-oct.toml") {
    std::vector<char> content = load_file("invalid/integer/trailing-us-oct.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/trailing-us.toml") {
    std::vector<char> content = load_file("invalid/integer/trailing-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/us-after-bin.toml") {
    std::vector<char> content = load_file("invalid/integer/us-after-bin.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/us-after-hex.toml") {
    std::vector<char> content = load_file("invalid/integer/us-after-hex.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/integer/us-after-oct.toml") {
    std::vector<char> content = load_file("invalid/integer/us-after-oct.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

