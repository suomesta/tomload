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

TEST_CASE("valid/Keys/Keys_1.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"key"].is_string() == true);
    CHECK(t[u8"key"].get_string() == u8"value");
    CHECK(t[u8"bare_key"].is_string() == true);
    CHECK(t[u8"bare_key"].get_string() == u8"value");
    CHECK(t[u8"bare-key"].is_string() == true);
    CHECK(t[u8"bare-key"].get_string() == u8"value");
    CHECK(t[u8"1234"].is_string() == true);
    CHECK(t[u8"1234"].get_string() == u8"value");
}

TEST_CASE("valid/Keys/Keys_10.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_10.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"apple"].is_table() == true);
    CHECK(t[u8"apple"].size() == 3);
    CHECK(t[u8"apple"][u8"type"].is_string() == true);
    CHECK(t[u8"apple"][u8"type"].get_string() == u8"fruit");
    CHECK(t[u8"apple"][u8"skin"].is_string() == true);
    CHECK(t[u8"apple"][u8"skin"].get_string() == u8"thin");
    CHECK(t[u8"apple"][u8"color"].is_string() == true);
    CHECK(t[u8"apple"][u8"color"].get_string() == u8"red");
    CHECK(t[u8"orange"].is_table() == true);
    CHECK(t[u8"orange"].size() == 3);
    CHECK(t[u8"orange"][u8"type"].is_string() == true);
    CHECK(t[u8"orange"][u8"type"].get_string() == u8"fruit");
    CHECK(t[u8"orange"][u8"skin"].is_string() == true);
    CHECK(t[u8"orange"][u8"skin"].get_string() == u8"thick");
    CHECK(t[u8"orange"][u8"color"].is_string() == true);
    CHECK(t[u8"orange"][u8"color"].get_string() == u8"orange");
}

TEST_CASE("valid/Keys/Keys_11.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_11.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"apple"].is_table() == true);
    CHECK(t[u8"apple"].size() == 3);
    CHECK(t[u8"apple"][u8"type"].is_string() == true);
    CHECK(t[u8"apple"][u8"type"].get_string() == u8"fruit");
    CHECK(t[u8"apple"][u8"skin"].is_string() == true);
    CHECK(t[u8"apple"][u8"skin"].get_string() == u8"thin");
    CHECK(t[u8"apple"][u8"color"].is_string() == true);
    CHECK(t[u8"apple"][u8"color"].get_string() == u8"red");
    CHECK(t[u8"orange"].is_table() == true);
    CHECK(t[u8"orange"].size() == 3);
    CHECK(t[u8"orange"][u8"type"].is_string() == true);
    CHECK(t[u8"orange"][u8"type"].get_string() == u8"fruit");
    CHECK(t[u8"orange"][u8"skin"].is_string() == true);
    CHECK(t[u8"orange"][u8"skin"].get_string() == u8"thick");
    CHECK(t[u8"orange"][u8"color"].is_string() == true);
    CHECK(t[u8"orange"][u8"color"].get_string() == u8"orange");
}

TEST_CASE("valid/Keys/Keys_12.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_12.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"3"].is_table() == true);
    CHECK(t[u8"3"].size() == 1);
    CHECK(t[u8"3"][u8"14159"].is_string() == true);
    CHECK(t[u8"3"][u8"14159"].get_string() == u8"pi");
}

TEST_CASE("valid/Keys/Keys_2.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"127.0.0.1"].is_string() == true);
    CHECK(t[u8"127.0.0.1"].get_string() == u8"value");
    CHECK(t[u8"character encoding"].is_string() == true);
    CHECK(t[u8"character encoding"].get_string() == u8"value");
    CHECK(t[u8"ʎǝʞ"].is_string() == true);
    CHECK(t[u8"ʎǝʞ"].get_string() == u8"value");
    CHECK(t[u8"key2"].is_string() == true);
    CHECK(t[u8"key2"].get_string() == u8"value");
    CHECK(t[u8"quoted \"value\""].is_string() == true);
    CHECK(t[u8"quoted \"value\""].get_string() == u8"value");
}

TEST_CASE("valid/Keys/Keys_3_fix1.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_3_fix1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8""].is_string() == true);
    CHECK(t[u8""].get_string() == u8"blank");
}

TEST_CASE("valid/Keys/Keys_3_fix2.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_3_fix2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8""].is_string() == true);
    CHECK(t[u8""].get_string() == u8"blank");
}

TEST_CASE("valid/Keys/Keys_4.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_4.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t[u8"name"].is_string() == true);
    CHECK(t[u8"name"].get_string() == u8"Orange");
    CHECK(t[u8"physical"].is_table() == true);
    CHECK(t[u8"physical"].size() == 2);
    CHECK(t[u8"physical"][u8"color"].is_string() == true);
    CHECK(t[u8"physical"][u8"color"].get_string() == u8"orange");
    CHECK(t[u8"physical"][u8"shape"].is_string() == true);
    CHECK(t[u8"physical"][u8"shape"].get_string() == u8"round");
    CHECK(t[u8"site"].is_table() == true);
    CHECK(t[u8"site"].size() == 1);
    CHECK(t[u8"site"][u8"google.com"].is_boolean() == true);
    CHECK(t[u8"site"][u8"google.com"].get_boolean() == true);
}

TEST_CASE("valid/Keys/Keys_5.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_5.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"fruit"].is_table() == true);
    CHECK(t[u8"fruit"].size() == 3);
    CHECK(t[u8"fruit"][u8"name"].is_string() == true);
    CHECK(t[u8"fruit"][u8"name"].get_string() == u8"banana");
    CHECK(t[u8"fruit"][u8"color"].is_string() == true);
    CHECK(t[u8"fruit"][u8"color"].get_string() == u8"yellow");
    CHECK(t[u8"fruit"][u8"flavor"].is_string() == true);
    CHECK(t[u8"fruit"][u8"flavor"].get_string() == u8"banana");
}

TEST_CASE("valid/Keys/Keys_8.toml") {
    std::vector<char> content = load_file("valid/Keys/Keys_8.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"fruit"].is_table() == true);
    CHECK(t[u8"fruit"].size() == 2);
    CHECK(t[u8"fruit"][u8"apple"].is_table() == true);
    CHECK(t[u8"fruit"][u8"apple"].size() == 1);
    CHECK(t[u8"fruit"][u8"apple"][u8"smooth"].is_boolean() == true);
    CHECK(t[u8"fruit"][u8"apple"][u8"smooth"].get_boolean() == true);
    CHECK(t[u8"fruit"][u8"orange"].is_integer() == true);
    CHECK(t[u8"fruit"][u8"orange"].get_integer() == 2);
}

