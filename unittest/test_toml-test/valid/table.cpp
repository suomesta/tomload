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

TEST_CASE("valid/table/empty-name.toml") {
    std::vector<char> content = load_file("valid/table/empty-name.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8""].is_table() == true);
    CHECK(t[u8""].size() == 2);
    CHECK(t[u8""][u8"x"].is_integer() == true);
    CHECK(t[u8""][u8"x"].get_integer() == 1);
    CHECK(t[u8""][u8"a"].is_table() == true);
    CHECK(t[u8""][u8"a"].size() == 1);
    CHECK(t[u8""][u8"a"][u8"x"].is_integer() == true);
    CHECK(t[u8""][u8"a"][u8"x"].get_integer() == 2);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8""].is_table() == true);
    CHECK(t[u8"a"][u8""].size() == 1);
    CHECK(t[u8"a"][u8""][u8"x"].is_integer() == true);
    CHECK(t[u8"a"][u8""][u8"x"].get_integer() == 3);
}

TEST_CASE("valid/table/empty.toml") {
    std::vector<char> content = load_file("valid/table/empty.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 0);
}

TEST_CASE("valid/table/keyword-with-values.toml") {
    std::vector<char> content = load_file("valid/table/keyword-with-values.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"true"].is_table() == true);
    CHECK(t[u8"true"].size() == 1);
    CHECK(t[u8"true"][u8"k"].is_integer() == true);
    CHECK(t[u8"true"][u8"k"].get_integer() == 1);
    CHECK(t[u8"false"].is_table() == true);
    CHECK(t[u8"false"].size() == 1);
    CHECK(t[u8"false"][u8"k"].is_integer() == true);
    CHECK(t[u8"false"][u8"k"].get_integer() == 2);
    CHECK(t[u8"inf"].is_table() == true);
    CHECK(t[u8"inf"].size() == 1);
    CHECK(t[u8"inf"][u8"k"].is_integer() == true);
    CHECK(t[u8"inf"][u8"k"].get_integer() == 3);
    CHECK(t[u8"nan"].is_table() == true);
    CHECK(t[u8"nan"].size() == 1);
    CHECK(t[u8"nan"][u8"k"].is_integer() == true);
    CHECK(t[u8"nan"][u8"k"].get_integer() == 4);
}

TEST_CASE("valid/table/keyword.toml") {
    std::vector<char> content = load_file("valid/table/keyword.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"true"].is_table() == true);
    CHECK(t[u8"true"].size() == 0);
    CHECK(t[u8"false"].is_table() == true);
    CHECK(t[u8"false"].size() == 0);
    CHECK(t[u8"inf"].is_table() == true);
    CHECK(t[u8"inf"].size() == 0);
    CHECK(t[u8"nan"].is_table() == true);
    CHECK(t[u8"nan"].size() == 0);
}

TEST_CASE("valid/table/names-with-values.toml") {
    std::vector<char> content = load_file("valid/table/names-with-values.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 4);
    CHECK(t[u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"a"][u8"b"].size() == 1);
    CHECK(t[u8"a"][u8"b"][u8"c"].is_table() == true);
    CHECK(t[u8"a"][u8"b"][u8"c"].size() == 1);
    CHECK(t[u8"a"][u8"b"][u8"c"][u8"key"].is_integer() == true);
    CHECK(t[u8"a"][u8"b"][u8"c"][u8"key"].get_integer() == 1);
    CHECK(t[u8"a"][u8"b.c"].is_table() == true);
    CHECK(t[u8"a"][u8"b.c"].size() == 1);
    CHECK(t[u8"a"][u8"b.c"][u8"key"].is_integer() == true);
    CHECK(t[u8"a"][u8"b.c"][u8"key"].get_integer() == 2);
    CHECK(t[u8"a"][u8"d.e"].is_table() == true);
    CHECK(t[u8"a"][u8"d.e"].size() == 1);
    CHECK(t[u8"a"][u8"d.e"][u8"key"].is_integer() == true);
    CHECK(t[u8"a"][u8"d.e"][u8"key"].get_integer() == 3);
    CHECK(t[u8"a"][u8" x "].is_table() == true);
    CHECK(t[u8"a"][u8" x "].size() == 1);
    CHECK(t[u8"a"][u8" x "][u8"key"].is_integer() == true);
    CHECK(t[u8"a"][u8" x "][u8"key"].get_integer() == 4);
    CHECK(t[u8"d"].is_table() == true);
    CHECK(t[u8"d"].size() == 1);
    CHECK(t[u8"d"][u8"e"].is_table() == true);
    CHECK(t[u8"d"][u8"e"].size() == 1);
    CHECK(t[u8"d"][u8"e"][u8"f"].is_table() == true);
    CHECK(t[u8"d"][u8"e"][u8"f"].size() == 1);
    CHECK(t[u8"d"][u8"e"][u8"f"][u8"key"].is_integer() == true);
    CHECK(t[u8"d"][u8"e"][u8"f"][u8"key"].get_integer() == 5);
    CHECK(t[u8"g"].is_table() == true);
    CHECK(t[u8"g"].size() == 1);
    CHECK(t[u8"g"][u8"h"].is_table() == true);
    CHECK(t[u8"g"][u8"h"].size() == 1);
    CHECK(t[u8"g"][u8"h"][u8"i"].is_table() == true);
    CHECK(t[u8"g"][u8"h"][u8"i"].size() == 1);
    CHECK(t[u8"g"][u8"h"][u8"i"][u8"key"].is_integer() == true);
    CHECK(t[u8"g"][u8"h"][u8"i"][u8"key"].get_integer() == 6);
    CHECK(t[u8"j"].is_table() == true);
    CHECK(t[u8"j"].size() == 1);
    CHECK(t[u8"j"][u8"ʞ"].is_table() == true);
    CHECK(t[u8"j"][u8"ʞ"].size() == 1);
    CHECK(t[u8"j"][u8"ʞ"][u8"l"].is_table() == true);
    CHECK(t[u8"j"][u8"ʞ"][u8"l"].size() == 1);
    CHECK(t[u8"j"][u8"ʞ"][u8"l"][u8"key"].is_integer() == true);
    CHECK(t[u8"j"][u8"ʞ"][u8"l"][u8"key"].get_integer() == 7);
    CHECK(t[u8"x"].is_table() == true);
    CHECK(t[u8"x"].size() == 1);
    CHECK(t[u8"x"][u8"1"].is_table() == true);
    CHECK(t[u8"x"][u8"1"].size() == 1);
    CHECK(t[u8"x"][u8"1"][u8"2"].is_table() == true);
    CHECK(t[u8"x"][u8"1"][u8"2"].size() == 1);
    CHECK(t[u8"x"][u8"1"][u8"2"][u8"key"].is_integer() == true);
    CHECK(t[u8"x"][u8"1"][u8"2"][u8"key"].get_integer() == 8);
}

TEST_CASE("valid/table/names.toml") {
    std::vector<char> content = load_file("valid/table/names.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 4);
    CHECK(t[u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"a"][u8"b"].size() == 1);
    CHECK(t[u8"a"][u8"b"][u8"c"].is_table() == true);
    CHECK(t[u8"a"][u8"b"][u8"c"].size() == 0);
    CHECK(t[u8"a"][u8"b.c"].is_table() == true);
    CHECK(t[u8"a"][u8"b.c"].size() == 0);
    CHECK(t[u8"a"][u8"d.e"].is_table() == true);
    CHECK(t[u8"a"][u8"d.e"].size() == 0);
    CHECK(t[u8"a"][u8" x "].is_table() == true);
    CHECK(t[u8"a"][u8" x "].size() == 0);
    CHECK(t[u8"d"].is_table() == true);
    CHECK(t[u8"d"].size() == 1);
    CHECK(t[u8"d"][u8"e"].is_table() == true);
    CHECK(t[u8"d"][u8"e"].size() == 1);
    CHECK(t[u8"d"][u8"e"][u8"f"].is_table() == true);
    CHECK(t[u8"d"][u8"e"][u8"f"].size() == 0);
    CHECK(t[u8"g"].is_table() == true);
    CHECK(t[u8"g"].size() == 1);
    CHECK(t[u8"g"][u8"h"].is_table() == true);
    CHECK(t[u8"g"][u8"h"].size() == 1);
    CHECK(t[u8"g"][u8"h"][u8"i"].is_table() == true);
    CHECK(t[u8"g"][u8"h"][u8"i"].size() == 0);
    CHECK(t[u8"j"].is_table() == true);
    CHECK(t[u8"j"].size() == 1);
    CHECK(t[u8"j"][u8"ʞ"].is_table() == true);
    CHECK(t[u8"j"][u8"ʞ"].size() == 1);
    CHECK(t[u8"j"][u8"ʞ"][u8"l"].is_table() == true);
    CHECK(t[u8"j"][u8"ʞ"][u8"l"].size() == 0);
    CHECK(t[u8"x"].is_table() == true);
    CHECK(t[u8"x"].size() == 1);
    CHECK(t[u8"x"][u8"1"].is_table() == true);
    CHECK(t[u8"x"][u8"1"].size() == 1);
    CHECK(t[u8"x"][u8"1"][u8"2"].is_table() == true);
    CHECK(t[u8"x"][u8"1"][u8"2"].size() == 0);
}

TEST_CASE("valid/table/no-eol.toml") {
    std::vector<char> content = load_file("valid/table/no-eol.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"table"].is_table() == true);
    CHECK(t[u8"table"].size() == 0);
}

TEST_CASE("valid/table/sub-empty.toml") {
    std::vector<char> content = load_file("valid/table/sub-empty.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"a"][u8"b"].size() == 0);
}

TEST_CASE("valid/table/sub.toml") {
    std::vector<char> content = load_file("valid/table/sub.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 2);
    CHECK(t[u8"a"][u8"key"].is_integer() == true);
    CHECK(t[u8"a"][u8"key"].get_integer() == 1);
    CHECK(t[u8"a"][u8"extend"].is_table() == true);
    CHECK(t[u8"a"][u8"extend"].size() == 2);
    CHECK(t[u8"a"][u8"extend"][u8"key"].is_integer() == true);
    CHECK(t[u8"a"][u8"extend"][u8"key"].get_integer() == 2);
    CHECK(t[u8"a"][u8"extend"][u8"more"].is_table() == true);
    CHECK(t[u8"a"][u8"extend"][u8"more"].size() == 1);
    CHECK(t[u8"a"][u8"extend"][u8"more"][u8"key"].is_integer() == true);
    CHECK(t[u8"a"][u8"extend"][u8"more"][u8"key"].get_integer() == 3);
}

TEST_CASE("valid/table/whitespace.toml") {
    std::vector<char> content = load_file("valid/table/whitespace.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"valid key"].is_table() == true);
    CHECK(t[u8"valid key"].size() == 0);
}

TEST_CASE("valid/table/with-literal-string.toml") {
    std::vector<char> content = load_file("valid/table/with-literal-string.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8"\"b\""].is_table() == true);
    CHECK(t[u8"a"][u8"\"b\""].size() == 1);
    CHECK(t[u8"a"][u8"\"b\""][u8"c"].is_table() == true);
    CHECK(t[u8"a"][u8"\"b\""][u8"c"].size() == 1);
    CHECK(t[u8"a"][u8"\"b\""][u8"c"][u8"answer"].is_integer() == true);
    CHECK(t[u8"a"][u8"\"b\""][u8"c"][u8"answer"].get_integer() == 42);
}

TEST_CASE("valid/table/with-pound.toml") {
    std::vector<char> content = load_file("valid/table/with-pound.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"key#group"].is_table() == true);
    CHECK(t[u8"key#group"].size() == 1);
    CHECK(t[u8"key#group"][u8"answer"].is_integer() == true);
    CHECK(t[u8"key#group"][u8"answer"].get_integer() == 42);
}

TEST_CASE("valid/table/with-single-quotes.toml") {
    std::vector<char> content = load_file("valid/table/with-single-quotes.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"a"][u8"b"].size() == 1);
    CHECK(t[u8"a"][u8"b"][u8"c"].is_table() == true);
    CHECK(t[u8"a"][u8"b"][u8"c"].size() == 1);
    CHECK(t[u8"a"][u8"b"][u8"c"][u8"answer"].is_integer() == true);
    CHECK(t[u8"a"][u8"b"][u8"c"][u8"answer"].get_integer() == 42);
}

TEST_CASE("valid/table/without-super-with-values.toml") {
    std::vector<char> content = load_file("valid/table/without-super-with-values.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"x"].is_table() == true);
    CHECK(t[u8"x"].size() == 3);
    CHECK(t[u8"x"][u8"y"].is_table() == true);
    CHECK(t[u8"x"][u8"y"].size() == 1);
    CHECK(t[u8"x"][u8"y"][u8"z"].is_table() == true);
    CHECK(t[u8"x"][u8"y"][u8"z"].size() == 1);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"].is_table() == true);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"].size() == 2);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"][u8"a"].is_integer() == true);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"][u8"a"].get_integer() == 1);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"][u8"b"].is_integer() == true);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"][u8"b"].get_integer() == 2);
    CHECK(t[u8"x"][u8"c"].is_integer() == true);
    CHECK(t[u8"x"][u8"c"].get_integer() == 3);
    CHECK(t[u8"x"][u8"d"].is_integer() == true);
    CHECK(t[u8"x"][u8"d"].get_integer() == 4);
}

TEST_CASE("valid/table/without-super.toml") {
    std::vector<char> content = load_file("valid/table/without-super.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"x"].is_table() == true);
    CHECK(t[u8"x"].size() == 1);
    CHECK(t[u8"x"][u8"y"].is_table() == true);
    CHECK(t[u8"x"][u8"y"].size() == 1);
    CHECK(t[u8"x"][u8"y"][u8"z"].is_table() == true);
    CHECK(t[u8"x"][u8"y"][u8"z"].size() == 1);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"].is_table() == true);
    CHECK(t[u8"x"][u8"y"][u8"z"][u8"w"].size() == 0);
}

