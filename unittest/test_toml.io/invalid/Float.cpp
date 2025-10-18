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
    std::ifstream file(std::string(TOML_IO_DIR) + filename, std::ios::binary | std::ios::ate);
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

TEST_CASE("invalid/Float/Float_2.toml") {
    std::vector<char> content = load_file("invalid/Float/Float_2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/Float/Float_2_1.toml") {
    std::vector<char> content = load_file("invalid/Float/Float_2_1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/Float/Float_2_2.toml") {
    std::vector<char> content = load_file("invalid/Float/Float_2_2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/Float/Float_2_3.toml") {
    std::vector<char> content = load_file("invalid/Float/Float_2_3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

