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

TEST_CASE("invalid/array/double-comma-01.toml") {
    std::vector<char> content = load_file("invalid/array/double-comma-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/double-comma-02.toml") {
    std::vector<char> content = load_file("invalid/array/double-comma-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/double-comma-1.toml") {
    std::vector<char> content = load_file("invalid/array/double-comma-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/double-comma-2.toml") {
    std::vector<char> content = load_file("invalid/array/double-comma-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/extending-table.toml") {
    std::vector<char> content = load_file("invalid/array/extending-table.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/missing-separator-01.toml") {
    std::vector<char> content = load_file("invalid/array/missing-separator-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/missing-separator-02.toml") {
    std::vector<char> content = load_file("invalid/array/missing-separator-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-01.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-02.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-03.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-04.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-05.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-06.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-06.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-07.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-07.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-08.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-08.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-1.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-2.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-3.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-4.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-4.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-5.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-5.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-6.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-6.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-7.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-7.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-8.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-8.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-table-01.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-table-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-close-table-02.toml") {
    std::vector<char> content = load_file("invalid/array/no-close-table-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-comma-01.toml") {
    std::vector<char> content = load_file("invalid/array/no-comma-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-comma-02.toml") {
    std::vector<char> content = load_file("invalid/array/no-comma-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-comma-03.toml") {
    std::vector<char> content = load_file("invalid/array/no-comma-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-comma-1.toml") {
    std::vector<char> content = load_file("invalid/array/no-comma-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-comma-2.toml") {
    std::vector<char> content = load_file("invalid/array/no-comma-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/no-comma-3.toml") {
    std::vector<char> content = load_file("invalid/array/no-comma-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/only-comma-01.toml") {
    std::vector<char> content = load_file("invalid/array/only-comma-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/only-comma-02.toml") {
    std::vector<char> content = load_file("invalid/array/only-comma-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/only-comma-1.toml") {
    std::vector<char> content = load_file("invalid/array/only-comma-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/only-comma-2.toml") {
    std::vector<char> content = load_file("invalid/array/only-comma-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/text-after-array-entries.toml") {
    std::vector<char> content = load_file("invalid/array/text-after-array-entries.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/text-before-array-separator.toml") {
    std::vector<char> content = load_file("invalid/array/text-before-array-separator.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/array/text-in-array.toml") {
    std::vector<char> content = load_file("invalid/array/text-in-array.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

