#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "tomload/tomload.h"

namespace {

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(TEST_DATA_DIR) + filename);
    if (not file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

}  // namespace

using namespace tomload;

TEST_CASE("Comment_1.toml") {
    std::string content = load_file("Comment_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["key"].is_string() == true);
    CHECK(t["key"].get_string() == "value");
    CHECK(t["another"].is_string() == true);
    CHECK(t["another"].get_string() == "# This is not a comment");
}

TEST_CASE("Key_Value_Pair_1.toml") {
    std::string content = load_file("Key_Value_Pair_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["key"].is_string() == true);
    CHECK(t["key"].get_string() == "value");
}

TEST_CASE("Key_Value_Pair_2.toml") {
    std::string content = load_file("Key_Value_Pair_2.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Key_Value_Pair_3.toml") {
    std::string content = load_file("Key_Value_Pair_3.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Keys_1.toml") {
    std::string content = load_file("Keys_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["key"].is_string() == true);
    CHECK(t["key"].get_string() == "value");
    CHECK(t["bare_key"].is_string() == true);
    CHECK(t["bare_key"].get_string() == "value");
    CHECK(t["bare-key"].is_string() == true);
    CHECK(t["bare-key"].get_string() == "value");
    CHECK(t["1234"].is_string() == true);
    CHECK(t["1234"].get_string() == "value");
}

TEST_CASE("Keys_2.toml") {
    std::string content = load_file("Keys_2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t["127.0.0.1"].is_string() == true);
    CHECK(t["127.0.0.1"].get_string() == "value");
    CHECK(t["character encoding"].is_string() == true);
    CHECK(t["character encoding"].get_string() == "value");
    CHECK(t["ʎǝʞ"].is_string() == true);
    CHECK(t["ʎǝʞ"].get_string() == "value");
    CHECK(t["key2"].is_string() == true);
    CHECK(t["key2"].get_string() == "value");
    CHECK(t["quoted \"value\""].is_string() == true);
    CHECK(t["quoted \"value\""].get_string() == "value");
}

TEST_CASE("Keys_3_fix1.toml") {
    std::string content = load_file("Keys_3_fix1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[""].is_string() == true);
    CHECK(t[""].get_string() == "blank");
}

TEST_CASE("Keys_3_fix2.toml") {
    std::string content = load_file("Keys_3_fix2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[""].is_string() == true);
    CHECK(t[""].get_string() == "blank");
}
TEST_CASE("Keys_4.toml") {
    std::string content = load_file("Keys_4.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["name"].is_string() == true);
    CHECK(t["name"].get_string() == "Orange");
    CHECK(t["physical"].is_table() == true);
    CHECK(t["physical"].size() == 2);
    CHECK(t["physical"]["color"].is_string() == true);
    CHECK(t["physical"]["color"].get_string() == "orange");
    CHECK(t["physical"]["shape"].is_string() == true);
    CHECK(t["physical"]["shape"].get_string() == "round");
    CHECK(t["site"].is_table() == true);
    CHECK(t["site"].size() == 1);
    CHECK(t["site"]["google.com"].is_boolean() == true);
    CHECK(t["site"]["google.com"].get_bool() == true);
}

TEST_CASE("Keys_5.toml") {
    std::string content = load_file("Keys_5.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 3);
    CHECK(t["fruit"]["name"].is_string() == true);
    CHECK(t["fruit"]["name"].get_string() == "banana");
    CHECK(t["fruit"]["color"].is_string() == true);
    CHECK(t["fruit"]["color"].get_string() == "yellow");
    CHECK(t["fruit"]["flavor"].is_string() == true);
    CHECK(t["fruit"]["flavor"].get_string() == "banana");
}

TEST_CASE("Keys_6.toml") {
    std::string content = load_file("Keys_6.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Keys_7.toml") {
    std::string content = load_file("Keys_7.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Keys_8.toml") {
/*
    std::string content = load_file("Keys_8.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 2);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 1);
    CHECK(t["fruit"]["apple"]["smooth"].is_boolean() == true);
    CHECK(t["fruit"]["apple"]["smooth"].get_bool() == true);
    CHECK(t["fruit"]["orange"].is_integer() == true);
    CHECK(t["fruit"]["orange"].get_integer() == 2);
*/
}

TEST_CASE("Keys_9.toml") {
    std::string content = load_file("Keys_9.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Keys_10.toml") {
    std::string content = load_file("Keys_10.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["apple"].is_table() == true);
    CHECK(t["apple"].size() == 3);
    CHECK(t["apple"]["type"].is_string() == true);
    CHECK(t["apple"]["type"].get_string() == "fruit");
    CHECK(t["apple"]["skin"].is_string() == true);
    CHECK(t["apple"]["skin"].get_string() == "thin");
    CHECK(t["apple"]["color"].is_string() == true);
    CHECK(t["apple"]["color"].get_string() == "red");
    CHECK(t["orange"].is_table() == true);
    CHECK(t["orange"].size() == 3);
    CHECK(t["orange"]["type"].is_string() == true);
    CHECK(t["orange"]["type"].get_string() == "fruit");
    CHECK(t["orange"]["skin"].is_string() == true);
    CHECK(t["orange"]["skin"].get_string() == "thick");
    CHECK(t["orange"]["color"].is_string() == true);
    CHECK(t["orange"]["color"].get_string() == "orange");
}

TEST_CASE("Keys_11.toml") {
    std::string content = load_file("Keys_11.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["apple"].is_table() == true);
    CHECK(t["apple"].size() == 3);
    CHECK(t["apple"]["type"].is_string() == true);
    CHECK(t["apple"]["type"].get_string() == "fruit");
    CHECK(t["apple"]["skin"].is_string() == true);
    CHECK(t["apple"]["skin"].get_string() == "thin");
    CHECK(t["apple"]["color"].is_string() == true);
    CHECK(t["apple"]["color"].get_string() == "red");
    CHECK(t["orange"].is_table() == true);
    CHECK(t["orange"].size() == 3);
    CHECK(t["orange"]["type"].is_string() == true);
    CHECK(t["orange"]["type"].get_string() == "fruit");
    CHECK(t["orange"]["skin"].is_string() == true);
    CHECK(t["orange"]["skin"].get_string() == "thick");
    CHECK(t["orange"]["color"].is_string() == true);
    CHECK(t["orange"]["color"].get_string() == "orange");
}

TEST_CASE("Keys_12.toml") {
    std::string content = load_file("Keys_12.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["3"].is_table() == true);
    CHECK(t["3"].size() == 1);
    CHECK(t["3"]["14159"].is_string() == true);
    CHECK(t["3"]["14159"].get_string() == "pi");
}

TEST_CASE("String_1.toml") {
    std::string content = load_file("String_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["str"].is_string() == true);
    CHECK(t["str"].get_string() == "I'm a string. \"You can quote me\". Name\tJosé\nLocation\tSF.");
}

TEST_CASE("String_2.toml") {
/*
    std::string content = load_file("String_2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["str1"].is_string() == true);
    CHECK(t["str1"].get_string() == "Roses are red\nViolets are blue");
*/
}

TEST_CASE("String_3.toml") {
    std::string content = load_file("String_3.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["str2"].is_string() == true);
    CHECK(t["str2"].get_string() == "Roses are red\nViolets are blue");
    CHECK(t["str3"].is_string() == true);
    CHECK(t["str3"].get_string() == "Roses are red\r\nViolets are blue");
}

TEST_CASE("String_4.toml") {
/*
    std::string content = load_file("String_4.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["str1"].is_string() == true);
    CHECK(t["str1"].get_string() == "The quick brown fox jumps over the lazy dog.");
    CHECK(t["str2"].is_string() == true);
    CHECK(t["str2"].get_string() == "The quick brown fox jumps over the lazy dog.");
    CHECK(t["str3"].is_string() == true);
    CHECK(t["str3"].get_string() == "The quick brown fox jumps over the lazy dog.");
*/
}

TEST_CASE("String_5.toml") {
/*
    std::string content = load_file("String_5.toml");
    item_t t(view_t{content.c_str()});

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
*/
}

TEST_CASE("String_6.toml") {
    std::string content = load_file("String_6.toml");
    item_t t(view_t{content.c_str()});

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

TEST_CASE("String_7.toml") {
    std::string content = load_file("String_7.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["regex2"].is_string() == true);
    CHECK(t["regex2"].get_string() == "I [dw]on't need \\d{2} apples");
    CHECK(t["lines"].is_string() == true);
    CHECK(t["lines"].get_string() == "The first newline is\ntrimmed in raw strings.\n   All other whitespace\n   is preserved.\n");
}

TEST_CASE("String_8.toml") {
    std::string content = load_file("String_8.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["quot15"].is_string() == true);
    CHECK(t["quot15"].get_string() == "Here are fifteen quotation marks: \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");
    CHECK(t["apos15"].is_string() == true);
    CHECK(t["apos15"].get_string() == "Here are fifteen apostrophes: '''''''''''''''");
    CHECK(t["str"].is_string() == true);
    CHECK(t["str"].get_string() == "'That,' she said, 'is still pointless.'");
}

TEST_CASE("Boolean_1.toml") {
    std::string content = load_file("Boolean_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["bool1"].is_boolean() == true);
    CHECK(t["bool1"].get_bool() == true);
    CHECK(t["bool2"].is_boolean() == true);
    CHECK(t["bool2"].get_bool() == false);
}
