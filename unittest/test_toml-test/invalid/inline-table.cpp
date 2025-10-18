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

TEST_CASE("invalid/inline-table/bad-key-syntax.toml") {
    std::vector<char> content = load_file("invalid/inline-table/bad-key-syntax.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/double-comma.toml") {
    std::vector<char> content = load_file("invalid/inline-table/double-comma.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/duplicate-key-01.toml") {
    std::vector<char> content = load_file("invalid/inline-table/duplicate-key-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/duplicate-key-02.toml") {
    std::vector<char> content = load_file("invalid/inline-table/duplicate-key-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/duplicate-key-03.toml") {
    std::vector<char> content = load_file("invalid/inline-table/duplicate-key-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/duplicate-key-04.toml") {
    std::vector<char> content = load_file("invalid/inline-table/duplicate-key-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/empty-01.toml") {
    std::vector<char> content = load_file("invalid/inline-table/empty-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/empty-02.toml") {
    std::vector<char> content = load_file("invalid/inline-table/empty-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/empty-03.toml") {
    std::vector<char> content = load_file("invalid/inline-table/empty-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/linebreak-01.toml") {
    std::vector<char> content = load_file("invalid/inline-table/linebreak-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/linebreak-02.toml") {
    std::vector<char> content = load_file("invalid/inline-table/linebreak-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/linebreak-03.toml") {
    std::vector<char> content = load_file("invalid/inline-table/linebreak-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/linebreak-04.toml") {
    std::vector<char> content = load_file("invalid/inline-table/linebreak-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/no-close-01.toml") {
    std::vector<char> content = load_file("invalid/inline-table/no-close-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/no-close-02.toml") {
    std::vector<char> content = load_file("invalid/inline-table/no-close-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/no-comma-01.toml") {
    std::vector<char> content = load_file("invalid/inline-table/no-comma-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/no-comma-02.toml") {
    std::vector<char> content = load_file("invalid/inline-table/no-comma-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-01.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-02.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-03.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-05.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-06.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-06.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-07.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-07.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-08.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-08.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-09.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-09.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-10.toml") {
    std::vector<char> content = load_file("invalid/inline-table/overwrite-10.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/inline-table/trailing-comma.toml") {
    std::vector<char> content = load_file("invalid/inline-table/trailing-comma.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

