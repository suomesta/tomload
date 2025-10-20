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

TEST_CASE("valid/String/String_1.toml") {
    std::vector<char> content = load_file("valid/String/String_1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"str"].is_string() == true);
    CHECK(t[u8"str"].get_string() == u8"I'm a string. \"You can quote me\". Name\tJosé\nLocation\tSF.");
}

TEST_CASE("valid/String/String_2.toml") {
    std::vector<char> content = load_file("valid/String/String_2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"str1"].is_string() == true);
    CHECK(t[u8"str1"].get_string() == u8"Roses are red\nViolets are blue");
}

TEST_CASE("valid/String/String_3.toml") {
    std::vector<char> content = load_file("valid/String/String_3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"str2"].is_string() == true);
    CHECK(t[u8"str2"].get_string() == u8"Roses are red\nViolets are blue");
    CHECK(t[u8"str3"].is_string() == true);
    CHECK(t[u8"str3"].get_string() == u8"Roses are red\r\nViolets are blue");
}

TEST_CASE("valid/String/String_4.toml") {
    std::vector<char> content = load_file("valid/String/String_4.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t[u8"str1"].is_string() == true);
    CHECK(t[u8"str1"].get_string() == u8"The quick brown fox jumps over the lazy dog.");
    CHECK(t[u8"str2"].is_string() == true);
    CHECK(t[u8"str2"].get_string() == u8"The quick brown fox jumps over the lazy dog.");
    CHECK(t[u8"str3"].is_string() == true);
    CHECK(t[u8"str3"].get_string() == u8"The quick brown fox jumps over the lazy dog.");
}

TEST_CASE("valid/String/String_5.toml") {
    std::vector<char> content = load_file("valid/String/String_5.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"str4"].is_string() == true);
    CHECK(t[u8"str4"].get_string() == u8"Here are two quotation marks: \"\". Simple enough.");
    CHECK(t[u8"str5"].is_string() == true);
    CHECK(t[u8"str5"].get_string() == u8"Here are three quotation marks: \"\"\".");
    CHECK(t[u8"str6"].is_string() == true);
    CHECK(t[u8"str6"].get_string() == u8"Here are fifteen quotation marks: \"\"\"\"\"\"\"\"\"\"\"\"\"\"\".");
    CHECK(t[u8"str7"].is_string() == true);
    CHECK(t[u8"str7"].get_string() == u8"\"This,\" she said, \"is just a pointless statement.\"");
}

TEST_CASE("valid/String/String_6.toml") {
    std::vector<char> content = load_file("valid/String/String_6.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"winpath"].is_string() == true);
    CHECK(t[u8"winpath"].get_string() == u8"C:\\Users\\nodejs\\templates");
    CHECK(t[u8"winpath2"].is_string() == true);
    CHECK(t[u8"winpath2"].get_string() == u8"\\\\ServerX\\admin$\\system32\\");
    CHECK(t[u8"quoted"].is_string() == true);
    CHECK(t[u8"quoted"].get_string() == u8"Tom \"Dubs\" Preston-Werner");
    CHECK(t[u8"regex"].is_string() == true);
    CHECK(t[u8"regex"].get_string() == u8"<\\i\\c*\\s*>");
}

TEST_CASE("valid/String/String_7.toml") {
    std::vector<char> content = load_file("valid/String/String_7.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"regex2"].is_string() == true);
    CHECK(t[u8"regex2"].get_string() == u8"I [dw]on't need \\d{2} apples");
    CHECK(t[u8"lines"].is_string() == true);
    CHECK(t[u8"lines"].get_string() == u8"The first newline is\ntrimmed in raw strings.\n   All other whitespace\n   is preserved.\n");
}

TEST_CASE("valid/String/String_8.toml") {
    std::vector<char> content = load_file("valid/String/String_8.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t[u8"quot15"].is_string() == true);
    CHECK(t[u8"quot15"].get_string() == u8"Here are fifteen quotation marks: \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");
    CHECK(t[u8"apos15"].is_string() == true);
    CHECK(t[u8"apos15"].get_string() == u8"Here are fifteen apostrophes: '''''''''''''''");
    CHECK(t[u8"str"].is_string() == true);
    CHECK(t[u8"str"].get_string() == u8"'That,' she said, 'is still pointless.'");
}

