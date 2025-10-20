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

TEST_CASE("valid/Float/Float_1.toml") {
    std::vector<char> content = load_file("valid/Float/Float_1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t[u8"flt1"].is_float() == true);
    CHECK(t[u8"flt1"].get_float() == 1.0);
    CHECK(t[u8"flt2"].is_float() == true);
    CHECK(t[u8"flt2"].get_float() == 3.1415);
    CHECK(t[u8"flt3"].is_float() == true);
    CHECK(t[u8"flt3"].get_float() == -0.01);
    CHECK(t[u8"flt4"].is_float() == true);
    CHECK(t[u8"flt4"].get_float() == 5e+22);
    CHECK(t[u8"flt5"].is_float() == true);
    CHECK(t[u8"flt5"].get_float() == 1000000.0);
    CHECK(t[u8"flt6"].is_float() == true);
    CHECK(t[u8"flt6"].get_float() == -0.02);
    CHECK(t[u8"flt7"].is_float() == true);
    CHECK(t[u8"flt7"].get_float() == 6.626e-34);
}

TEST_CASE("valid/Float/Float_3.toml") {
    std::vector<char> content = load_file("valid/Float/Float_3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"flt8"].is_float() == true);
    CHECK(t[u8"flt8"].get_float() == 224617.445991228);
}

TEST_CASE("valid/Float/Float_4.toml") {
    std::vector<char> content = load_file("valid/Float/Float_4.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"flt8"].is_float() == true);
    CHECK(t[u8"flt8"].get_float() == 224617.445991228);
}

TEST_CASE("valid/Float/Float_5.toml") {
    std::vector<char> content = load_file("valid/Float/Float_5.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 6);
    CHECK(t[u8"sf1"].is_float() == true);
    CHECK(t[u8"sf1"].get_float() == std::numeric_limits<double>::infinity());
    CHECK(t[u8"sf2"].is_float() == true);
    CHECK(t[u8"sf2"].get_float() == std::numeric_limits<double>::infinity());
    CHECK(t[u8"sf3"].is_float() == true);
    CHECK(t[u8"sf3"].get_float() == -std::numeric_limits<double>::infinity());
    CHECK(t[u8"sf4"].is_float() == true);
    CHECK(t[u8"sf4"].get_float() == rhs_nan{});
    CHECK(t[u8"sf5"].is_float() == true);
    CHECK(t[u8"sf5"].get_float() == rhs_nan{});
    CHECK(t[u8"sf6"].is_float() == true);
    CHECK(t[u8"sf6"].get_float() == rhs_nan{});
}

