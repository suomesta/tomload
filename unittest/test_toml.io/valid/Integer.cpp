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

using namespace tomload;

TEST_CASE("valid/Integer/Integer_1.toml") {
    std::vector<char> content = load_file("valid/Integer/Integer_1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["int1"].is_integer() == true);
    CHECK(t["int1"].get_integer() == 99);
    CHECK(t["int2"].is_integer() == true);
    CHECK(t["int2"].get_integer() == 42);
    CHECK(t["int3"].is_integer() == true);
    CHECK(t["int3"].get_integer() == 0);
    CHECK(t["int4"].is_integer() == true);
    CHECK(t["int4"].get_integer() == -17);
}

TEST_CASE("valid/Integer/Integer_2.toml") {
    std::vector<char> content = load_file("valid/Integer/Integer_2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["int5"].is_integer() == true);
    CHECK(t["int5"].get_integer() == 1000);
    CHECK(t["int6"].is_integer() == true);
    CHECK(t["int6"].get_integer() == 5349221);
    CHECK(t["int7"].is_integer() == true);
    CHECK(t["int7"].get_integer() == 5349221);
    CHECK(t["int8"].is_integer() == true);
    CHECK(t["int8"].get_integer() == 12345);
}

TEST_CASE("valid/Integer/Integer_3.toml") {
    std::vector<char> content = load_file("valid/Integer/Integer_3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 6);
    CHECK(t["hex1"].is_integer() == true);
    CHECK(t["hex1"].get_integer() == 3735928559);
    CHECK(t["hex2"].is_integer() == true);
    CHECK(t["hex2"].get_integer() == 3735928559);
    CHECK(t["hex3"].is_integer() == true);
    CHECK(t["hex3"].get_integer() == 3735928559);
    CHECK(t["oct1"].is_integer() == true);
    CHECK(t["oct1"].get_integer() == 342391);
    CHECK(t["oct2"].is_integer() == true);
    CHECK(t["oct2"].get_integer() == 493);
    CHECK(t["bin1"].is_integer() == true);
    CHECK(t["bin1"].get_integer() == 214);
}

