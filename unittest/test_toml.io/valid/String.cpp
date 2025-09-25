#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <doctest/doctest.h>
#include "tomload/tomload.h"

namespace {

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(TOML_IO_DIR) + filename);
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

TEST_CASE("valid/String/String_1.toml") {
    std::string content = load_file("valid/String/String_1.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["str"].is_string() == true);
    CHECK(t["str"].get_string() == "I'm a string. \"You can quote me\". Name\tJosé\nLocation\tSF.");
}

TEST_CASE("valid/String/String_2.toml") {
    std::string content = load_file("valid/String/String_2.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["str1"].is_string() == true);
    CHECK(t["str1"].get_string() == "Roses are red\nViolets are blue");
}

TEST_CASE("valid/String/String_3.toml") {
    std::string content = load_file("valid/String/String_3.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["str2"].is_string() == true);
    CHECK(t["str2"].get_string() == "Roses are red\nViolets are blue");
    CHECK(t["str3"].is_string() == true);
    CHECK(t["str3"].get_string() == "Roses are red\r\nViolets are blue");
}

TEST_CASE("valid/String/String_4.toml") {
    std::string content = load_file("valid/String/String_4.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["str1"].is_string() == true);
    CHECK(t["str1"].get_string() == "The quick brown fox jumps over the lazy dog.");
    CHECK(t["str2"].is_string() == true);
    CHECK(t["str2"].get_string() == "The quick brown fox jumps over the lazy dog.");
    CHECK(t["str3"].is_string() == true);
    CHECK(t["str3"].get_string() == "The quick brown fox jumps over the lazy dog.");
}

TEST_CASE("valid/String/String_5.toml") {
    std::string content = load_file("valid/String/String_5.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["str4"].is_string() == true);
    CHECK(t["str4"].get_string() == "Here are two quotation marks: \"\". Simple enough.");
    CHECK(t["str5"].is_string() == true);
    CHECK(t["str5"].get_string() == "Here are three quotation marks: \"\"\".");
    CHECK(t["str6"].is_string() == true);
    CHECK(t["str6"].get_string() == "Here are fifteen quotation marks: \"\"\"\"\"\"\"\"\"\"\"\"\"\"\".");
    CHECK(t["str7"].is_string() == true);
    CHECK(t["str7"].get_string() == "\"This,\" she said, \"is just a pointless statement.\"");
}

TEST_CASE("valid/String/String_6.toml") {
    std::string content = load_file("valid/String/String_6.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["winpath"].is_string() == true);
    CHECK(t["winpath"].get_string() == "C:\\Users\\nodejs\\templates");
    CHECK(t["winpath2"].is_string() == true);
    CHECK(t["winpath2"].get_string() == "\\\\ServerX\\admin$\\system32\\");
    CHECK(t["quoted"].is_string() == true);
    CHECK(t["quoted"].get_string() == "Tom \"Dubs\" Preston-Werner");
    CHECK(t["regex"].is_string() == true);
    CHECK(t["regex"].get_string() == "<\\i\\c*\\s*>");
}

TEST_CASE("valid/String/String_7.toml") {
    std::string content = load_file("valid/String/String_7.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["regex2"].is_string() == true);
    CHECK(t["regex2"].get_string() == "I [dw]on't need \\d{2} apples");
    CHECK(t["lines"].is_string() == true);
    CHECK(t["lines"].get_string() == "The first newline is\ntrimmed in raw strings.\n   All other whitespace\n   is preserved.\n");
}

TEST_CASE("valid/String/String_8.toml") {
    std::string content = load_file("valid/String/String_8.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["quot15"].is_string() == true);
    CHECK(t["quot15"].get_string() == "Here are fifteen quotation marks: \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");
    CHECK(t["apos15"].is_string() == true);
    CHECK(t["apos15"].get_string() == "Here are fifteen apostrophes: '''''''''''''''");
    CHECK(t["str"].is_string() == true);
    CHECK(t["str"].get_string() == "'That,' she said, 'is still pointless.'");
}

