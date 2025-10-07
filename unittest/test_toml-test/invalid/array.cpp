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

TEST_CASE("invalid/array/double-comma-01.toml") {
    std::string content = load_file("invalid/array/double-comma-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/double-comma-02.toml") {
    std::string content = load_file("invalid/array/double-comma-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/double-comma-1.toml") {
    std::string content = load_file("invalid/array/double-comma-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/double-comma-2.toml") {
    std::string content = load_file("invalid/array/double-comma-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/extending-table.toml") {
    std::string content = load_file("invalid/array/extending-table.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/missing-separator-01.toml") {
    std::string content = load_file("invalid/array/missing-separator-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/missing-separator-02.toml") {
    std::string content = load_file("invalid/array/missing-separator-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-01.toml") {
    std::string content = load_file("invalid/array/no-close-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-02.toml") {
    std::string content = load_file("invalid/array/no-close-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-03.toml") {
    std::string content = load_file("invalid/array/no-close-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-04.toml") {
    std::string content = load_file("invalid/array/no-close-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-05.toml") {
    std::string content = load_file("invalid/array/no-close-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-06.toml") {
    std::string content = load_file("invalid/array/no-close-06.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-07.toml") {
    std::string content = load_file("invalid/array/no-close-07.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-08.toml") {
    std::string content = load_file("invalid/array/no-close-08.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-1.toml") {
    std::string content = load_file("invalid/array/no-close-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-2.toml") {
    std::string content = load_file("invalid/array/no-close-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-3.toml") {
    std::string content = load_file("invalid/array/no-close-3.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-4.toml") {
    std::string content = load_file("invalid/array/no-close-4.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-5.toml") {
    std::string content = load_file("invalid/array/no-close-5.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-6.toml") {
    std::string content = load_file("invalid/array/no-close-6.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-7.toml") {
    std::string content = load_file("invalid/array/no-close-7.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-8.toml") {
    std::string content = load_file("invalid/array/no-close-8.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-table-01.toml") {
    std::string content = load_file("invalid/array/no-close-table-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-close-table-02.toml") {
    std::string content = load_file("invalid/array/no-close-table-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-comma-01.toml") {
    std::string content = load_file("invalid/array/no-comma-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-comma-02.toml") {
    std::string content = load_file("invalid/array/no-comma-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-comma-03.toml") {
    std::string content = load_file("invalid/array/no-comma-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-comma-1.toml") {
    std::string content = load_file("invalid/array/no-comma-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-comma-2.toml") {
    std::string content = load_file("invalid/array/no-comma-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/no-comma-3.toml") {
    std::string content = load_file("invalid/array/no-comma-3.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/only-comma-01.toml") {
    std::string content = load_file("invalid/array/only-comma-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/only-comma-02.toml") {
    std::string content = load_file("invalid/array/only-comma-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/only-comma-1.toml") {
    std::string content = load_file("invalid/array/only-comma-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/only-comma-2.toml") {
    std::string content = load_file("invalid/array/only-comma-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/text-after-array-entries.toml") {
    std::string content = load_file("invalid/array/text-after-array-entries.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/text-before-array-separator.toml") {
    std::string content = load_file("invalid/array/text-before-array-separator.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/array/text-in-array.toml") {
    std::string content = load_file("invalid/array/text-in-array.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

