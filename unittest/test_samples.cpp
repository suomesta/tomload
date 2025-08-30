#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "tomload/tomload.h"

namespace {

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(SAMPLES_DIR) + filename);
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
    CHECK(t["site"]["google.com"].get_boolean() == true);
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
    std::string content = load_file("Keys_8.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 2);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 1);
    CHECK(t["fruit"]["apple"]["smooth"].is_boolean() == true);
    CHECK(t["fruit"]["apple"]["smooth"].get_boolean() == true);
    CHECK(t["fruit"]["orange"].is_integer() == true);
    CHECK(t["fruit"]["orange"].get_integer() == 2);
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
    std::string content = load_file("String_2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["str1"].is_string() == true);
    CHECK(t["str1"].get_string() == "Roses are red\nViolets are blue");
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
}

TEST_CASE("String_5.toml") {
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

TEST_CASE("Integer_1.toml") {
    std::string content = load_file("Integer_1.toml");
    item_t t(view_t{content.c_str()});

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

TEST_CASE("Integer_2.toml") {
    std::string content = load_file("Integer_2.toml");
    item_t t(view_t{content.c_str()});

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

TEST_CASE("Integer_3.toml") {
    std::string content = load_file("Integer_3.toml");
    item_t t(view_t{content.c_str()});

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

TEST_CASE("Float_1.toml") {
    std::string content = load_file("Float_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t["flt1"].is_float() == true);
    CHECK(t["flt1"].get_float() == 1.0);
    CHECK(t["flt2"].is_float() == true);
    CHECK(t["flt2"].get_float() == 3.1415);
    CHECK(t["flt3"].is_float() == true);
    CHECK(t["flt3"].get_float() == -0.01);
    CHECK(t["flt4"].is_float() == true);
    CHECK(t["flt4"].get_float() == 5e+22);
    CHECK(t["flt5"].is_float() == true);
    CHECK(t["flt5"].get_float() == 1000000.0);
    CHECK(t["flt6"].is_float() == true);
    CHECK(t["flt6"].get_float() == -0.02);
    CHECK(t["flt7"].is_float() == true);
    CHECK(t["flt7"].get_float() == 6.626e-34);
}

TEST_CASE("Float_2.toml") {
    std::string content = load_file("Float_2.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Float_2_1.toml") {
    std::string content = load_file("Float_2_1.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Float_2_2.toml") {
    std::string content = load_file("Float_2_2.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Float_2_3.toml") {
    std::string content = load_file("Float_2_3.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Float_3.toml") {
    std::string content = load_file("Float_3.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["flt8"].is_float() == true);
    CHECK(t["flt8"].get_float() == 224617.445991228);
}

TEST_CASE("Float_4.toml") {
    std::string content = load_file("Float_4.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["flt8"].is_float() == true);
    CHECK(t["flt8"].get_float() == 224617.445991228);
}

TEST_CASE("Float_5.toml") {
    std::string content = load_file("Float_5.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 6);
    CHECK(t["sf1"].is_float() == true);
    CHECK(t["sf1"].get_float() == std::numeric_limits<double>::infinity());
    CHECK(t["sf2"].is_float() == true);
    CHECK(t["sf2"].get_float() == std::numeric_limits<double>::infinity());
    CHECK(t["sf3"].is_float() == true);
    CHECK(t["sf3"].get_float() == -std::numeric_limits<double>::infinity());
    CHECK(t["sf4"].is_float() == true);
    CHECK(t["sf4"].get_float() == rhs_nan{});
    CHECK(t["sf5"].is_float() == true);
    CHECK(t["sf5"].get_float() == rhs_nan{});
    CHECK(t["sf6"].is_float() == true);
    CHECK(t["sf6"].get_float() == rhs_nan{});
}

TEST_CASE("Boolean_1.toml") {
    std::string content = load_file("Boolean_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["bool1"].is_boolean() == true);
    CHECK(t["bool1"].get_boolean() == true);
    CHECK(t["bool2"].is_boolean() == true);
    CHECK(t["bool2"].get_boolean() == false);
}

TEST_CASE("Array_1.toml") {
    std::string content = load_file("Array_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t["integers"].is_array() == true);
    CHECK(t["integers"].size() == 3);
    CHECK(t["integers"][0].is_integer() == true);
    CHECK(t["integers"][0].get_integer() == 1);
    CHECK(t["integers"][1].is_integer() == true);
    CHECK(t["integers"][1].get_integer() == 2);
    CHECK(t["integers"][2].is_integer() == true);
    CHECK(t["integers"][2].get_integer() == 3);
    CHECK(t["colors"].is_array() == true);
    CHECK(t["colors"].size() == 3);
    CHECK(t["colors"][0].is_string() == true);
    CHECK(t["colors"][0].get_string() == "red");
    CHECK(t["colors"][1].is_string() == true);
    CHECK(t["colors"][1].get_string() == "yellow");
    CHECK(t["colors"][2].is_string() == true);
    CHECK(t["colors"][2].get_string() == "green");
    CHECK(t["nested_arrays_of_ints"].is_array() == true);
    CHECK(t["nested_arrays_of_ints"].size() == 2);
    CHECK(t["nested_arrays_of_ints"][0].is_array() == true);
    CHECK(t["nested_arrays_of_ints"][0].size() == 2);
    CHECK(t["nested_arrays_of_ints"][0][0].is_integer() == true);
    CHECK(t["nested_arrays_of_ints"][0][0].get_integer() == 1);
    CHECK(t["nested_arrays_of_ints"][0][1].is_integer() == true);
    CHECK(t["nested_arrays_of_ints"][0][1].get_integer() == 2);
    CHECK(t["nested_arrays_of_ints"][1].is_array() == true);
    CHECK(t["nested_arrays_of_ints"][1].size() == 3);
    CHECK(t["nested_arrays_of_ints"][1][0].is_integer() == true);
    CHECK(t["nested_arrays_of_ints"][1][0].get_integer() == 3);
    CHECK(t["nested_arrays_of_ints"][1][1].is_integer() == true);
    CHECK(t["nested_arrays_of_ints"][1][1].get_integer() == 4);
    CHECK(t["nested_arrays_of_ints"][1][2].is_integer() == true);
    CHECK(t["nested_arrays_of_ints"][1][2].get_integer() == 5);
    CHECK(t["nested_mixed_array"].is_array() == true);
    CHECK(t["nested_mixed_array"].size() == 2);
    CHECK(t["nested_mixed_array"][0].is_array() == true);
    CHECK(t["nested_mixed_array"][0].size() == 2);
    CHECK(t["nested_mixed_array"][0][0].is_integer() == true);
    CHECK(t["nested_mixed_array"][0][0].get_integer() == 1);
    CHECK(t["nested_mixed_array"][0][1].is_integer() == true);
    CHECK(t["nested_mixed_array"][0][1].get_integer() == 2);
    CHECK(t["nested_mixed_array"][1].is_array() == true);
    CHECK(t["nested_mixed_array"][1].size() == 3);
    CHECK(t["nested_mixed_array"][1][0].is_string() == true);
    CHECK(t["nested_mixed_array"][1][0].get_string() == "a");
    CHECK(t["nested_mixed_array"][1][1].is_string() == true);
    CHECK(t["nested_mixed_array"][1][1].get_string() == "b");
    CHECK(t["nested_mixed_array"][1][2].is_string() == true);
    CHECK(t["nested_mixed_array"][1][2].get_string() == "c");
    CHECK(t["string_array"].is_array() == true);
    CHECK(t["string_array"].size() == 4);
    CHECK(t["string_array"][0].is_string() == true);
    CHECK(t["string_array"][0].get_string() == "all");
    CHECK(t["string_array"][1].is_string() == true);
    CHECK(t["string_array"][1].get_string() == "strings");
    CHECK(t["string_array"][2].is_string() == true);
    CHECK(t["string_array"][2].get_string() == "are the same");
    CHECK(t["string_array"][3].is_string() == true);
    CHECK(t["string_array"][3].get_string() == "type");
    CHECK(t["numbers"].is_array() == true);
    CHECK(t["numbers"].size() == 6);
    CHECK(t["numbers"][0].is_float() == true);
    CHECK(t["numbers"][0].get_float() == 0.1);
    CHECK(t["numbers"][1].is_float() == true);
    CHECK(t["numbers"][1].get_float() == 0.2);
    CHECK(t["numbers"][2].is_float() == true);
    CHECK(t["numbers"][2].get_float() == 0.5);
    CHECK(t["numbers"][3].is_integer() == true);
    CHECK(t["numbers"][3].get_integer() == 1);
    CHECK(t["numbers"][4].is_integer() == true);
    CHECK(t["numbers"][4].get_integer() == 2);
    CHECK(t["numbers"][5].is_integer() == true);
    CHECK(t["numbers"][5].get_integer() == 5);
    CHECK(t["contributors"].is_array() == true);
    CHECK(t["contributors"].size() == 2);
    CHECK(t["contributors"][0].is_string() == true);
    CHECK(t["contributors"][0].get_string() == "Foo Bar <foo@example.com>");
    CHECK(t["contributors"][1].is_table() == true);
    CHECK(t["contributors"][1].size() == 3);
    CHECK(t["contributors"][1]["name"].is_string() == true);
    CHECK(t["contributors"][1]["name"].get_string() == "Baz Qux");
    CHECK(t["contributors"][1]["email"].is_string() == true);
    CHECK(t["contributors"][1]["email"].get_string() == "bazqux@example.com");
    CHECK(t["contributors"][1]["url"].is_string() == true);
    CHECK(t["contributors"][1]["url"].get_string() == "https://example.com/bazqux");
}

TEST_CASE("Array_2.toml") {
    std::string content = load_file("Array_2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["integers2"].is_array() == true);
    CHECK(t["integers2"].size() == 3);
    CHECK(t["integers2"][0].is_integer() == true);
    CHECK(t["integers2"][0].get_integer() == 1);
    CHECK(t["integers2"][1].is_integer() == true);
    CHECK(t["integers2"][1].get_integer() == 2);
    CHECK(t["integers2"][2].is_integer() == true);
    CHECK(t["integers2"][2].get_integer() == 3);
    CHECK(t["integers3"].is_array() == true);
    CHECK(t["integers3"].size() == 2);
    CHECK(t["integers3"][0].is_integer() == true);
    CHECK(t["integers3"][0].get_integer() == 1);
    CHECK(t["integers3"][1].is_integer() == true);
    CHECK(t["integers3"][1].get_integer() == 2);
}

TEST_CASE("Table_1.toml") {
    std::string content = load_file("Table_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["table"].is_table() == true);
    CHECK(t["table"].size() == 0);
}

TEST_CASE("Table_2.toml") {
    std::string content = load_file("Table_2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["table-1"].is_table() == true);
    CHECK(t["table-1"].size() == 2);
    CHECK(t["table-1"]["key1"].is_string() == true);
    CHECK(t["table-1"]["key1"].get_string() == "some string");
    CHECK(t["table-1"]["key2"].is_integer() == true);
    CHECK(t["table-1"]["key2"].get_integer() == 123);
    CHECK(t["table-2"].is_table() == true);
    CHECK(t["table-2"].size() == 2);
    CHECK(t["table-2"]["key1"].is_string() == true);
    CHECK(t["table-2"]["key1"].get_string() == "another string");
    CHECK(t["table-2"]["key2"].is_integer() == true);
    CHECK(t["table-2"]["key2"].get_integer() == 456);
}

TEST_CASE("Table_3.toml") {
    std::string content = load_file("Table_3.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["dog"].is_table() == true);
    CHECK(t["dog"].size() == 1);
    CHECK(t["dog"]["tater.man"].is_table() == true);
    CHECK(t["dog"]["tater.man"].size() == 1);
    CHECK(t["dog"]["tater.man"]["type"].is_table() == true);
    CHECK(t["dog"]["tater.man"]["type"].size() == 1);
    CHECK(t["dog"]["tater.man"]["type"]["name"].is_string() == true);
    CHECK(t["dog"]["tater.man"]["type"]["name"].get_string() == "pug");
}

TEST_CASE("Table_4.toml") {
    std::string content = load_file("Table_4.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 1);
    CHECK(t["a"]["b"]["c"].is_table() == true);
    CHECK(t["a"]["b"]["c"].size() == 0);
    CHECK(t["d"].is_table() == true);
    CHECK(t["d"].size() == 1);
    CHECK(t["d"]["e"].is_table() == true);
    CHECK(t["d"]["e"].size() == 1);
    CHECK(t["d"]["e"]["f"].is_table() == true);
    CHECK(t["d"]["e"]["f"].size() == 0);
    CHECK(t["g"].is_table() == true);
    CHECK(t["g"].size() == 1);
    CHECK(t["g"]["h"].is_table() == true);
    CHECK(t["g"]["h"].size() == 1);
    CHECK(t["g"]["h"]["i"].is_table() == true);
    CHECK(t["g"]["h"]["i"].size() == 0);
    CHECK(t["j"].is_table() == true);
    CHECK(t["j"].size() == 1);
    CHECK(t["j"]["ʞ"].is_table() == true);
    CHECK(t["j"]["ʞ"].size() == 1);
    CHECK(t["j"]["ʞ"]["l"].is_table() == true);
    CHECK(t["j"]["ʞ"]["l"].size() == 0);
}

TEST_CASE("Table_5.toml") {
    std::string content = load_file("Table_5.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["x"].is_table() == true);
    CHECK(t["x"].size() == 1);
    CHECK(t["x"]["y"].is_table() == true);
    CHECK(t["x"]["y"].size() == 1);
    CHECK(t["x"]["y"]["z"].is_table() == true);
    CHECK(t["x"]["y"]["z"].size() == 1);
    CHECK(t["x"]["y"]["z"]["w"].is_table() == true);
    CHECK(t["x"]["y"]["z"]["w"].size() == 0);
}

TEST_CASE("Table_6.toml") {
    std::string content = load_file("Table_6.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Table_7.toml") {
    std::string content = load_file("Table_7.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("Table_8.toml") {
    std::string content = load_file("Table_8.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 2);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 0);
    CHECK(t["fruit"]["orange"].is_table() == true);
    CHECK(t["fruit"]["orange"].size() == 0);
    CHECK(t["animal"].is_table() == true);
    CHECK(t["animal"].size() == 0);
}

TEST_CASE("Table_9.toml") {
    std::string content = load_file("Table_9.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 2);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 0);
    CHECK(t["fruit"]["orange"].is_table() == true);
    CHECK(t["fruit"]["orange"].size() == 0);
    CHECK(t["animal"].is_table() == true);
    CHECK(t["animal"].size() == 0);
}

TEST_CASE("Table_10.toml") {
/*
    std::string content = load_file("Table_10.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["name"].is_string() == true);
    CHECK(t["name"].get_string() == "Fido");
    CHECK(t["breed"].is_string() == true);
    CHECK(t["breed"].get_string() == "pug");
    CHECK(t["owner"].is_table() == true);
    CHECK(t["owner"].size() == 2);
    CHECK(t["owner"]["name"].is_string() == true);
    CHECK(t["owner"]["name"].get_string() == "Regina Dogman");
*/
}

TEST_CASE("Table_11.toml") {
    std::string content = load_file("Table_11.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 1);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 2);
    CHECK(t["fruit"]["apple"]["color"].is_string() == true);
    CHECK(t["fruit"]["apple"]["color"].get_string() == "red");
    CHECK(t["fruit"]["apple"]["taste"].is_table() == true);
    CHECK(t["fruit"]["apple"]["taste"].size() == 1);
    CHECK(t["fruit"]["apple"]["taste"]["sweet"].is_boolean() == true);
    CHECK(t["fruit"]["apple"]["taste"]["sweet"].get_boolean() == true);
}

TEST_CASE("Table_12.toml") {
    std::string content = load_file("Table_12.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["fruit"].is_table() == true);
    CHECK(t["fruit"].size() == 1);
    CHECK(t["fruit"]["apple"].is_table() == true);
    CHECK(t["fruit"]["apple"].size() == 3);
    CHECK(t["fruit"]["apple"]["color"].is_string() == true);
    CHECK(t["fruit"]["apple"]["color"].get_string() == "red");
    CHECK(t["fruit"]["apple"]["taste"].is_table() == true);
    CHECK(t["fruit"]["apple"]["taste"].size() == 1);
    CHECK(t["fruit"]["apple"]["taste"]["sweet"].is_boolean() == true);
    CHECK(t["fruit"]["apple"]["taste"]["sweet"].get_boolean() == true);
    CHECK(t["fruit"]["apple"]["texture"].is_table() == true);
    CHECK(t["fruit"]["apple"]["texture"].size() == 1);
    CHECK(t["fruit"]["apple"]["texture"]["smooth"].is_boolean() == true);
    CHECK(t["fruit"]["apple"]["texture"]["smooth"].get_boolean() == true);
}

TEST_CASE("InlineTable_1.toml") {
    std::string content = load_file("InlineTable_1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["name"].is_table() == true);
    CHECK(t["name"].size() == 2);
    CHECK(t["name"]["first"].is_string() == true);
    CHECK(t["name"]["first"].get_string() == "Tom");
    CHECK(t["name"]["last"].is_string() == true);
    CHECK(t["name"]["last"].get_string() == "Preston-Werner");
    CHECK(t["point"].is_table() == true);
    CHECK(t["point"].size() == 2);
    CHECK(t["point"]["x"].is_integer() == true);
    CHECK(t["point"]["x"].get_integer() == 1);
    CHECK(t["point"]["y"].is_integer() == true);
    CHECK(t["point"]["y"].get_integer() == 2);
    CHECK(t["animal"].is_table() == true);
    CHECK(t["animal"].size() == 1);
    CHECK(t["animal"]["type"].is_table() == true);
    CHECK(t["animal"]["type"].size() == 1);
    CHECK(t["animal"]["type"]["name"].is_string() == true);
    CHECK(t["animal"]["type"]["name"].get_string() == "pug");
}

TEST_CASE("InlineTable_2.toml") {
    std::string content = load_file("InlineTable_2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["product"].is_table() == true);
    CHECK(t["product"].size() == 1);
    CHECK(t["product"]["type"].is_table() == true);
    CHECK(t["product"]["type"].size() == 1);
    CHECK(t["product"]["type"]["name"].is_string() == true);
    CHECK(t["product"]["type"]["name"].get_string() == "Nail");
}

TEST_CASE("InlineTable_2_invalid.toml") {
    std::string content = load_file("InlineTable_2_invalid.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("InlineTable_3.toml") {
    std::string content = load_file("InlineTable_3.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["product"].is_table() == true);
    CHECK(t["product"].size() == 1);
    CHECK(t["product"]["type"].is_table() == true);
    CHECK(t["product"]["type"].size() == 1);
    CHECK(t["product"]["type"]["name"].is_string() == true);
    CHECK(t["product"]["type"]["name"].get_string() == "Nail");
}

TEST_CASE("InlineTable_3_invalid.toml") {
    std::string content = load_file("InlineTable_3_invalid.toml");

    CHECK_THROWS_AS(item_t t(view_t{content.c_str()}), parse_error&);
}
