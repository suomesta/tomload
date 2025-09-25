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

TEST_CASE("valid/Array/Array_1.toml") {
    std::string content = load_file("valid/Array/Array_1.toml");
    item_t t{content.c_str()};

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

TEST_CASE("valid/Array/Array_2.toml") {
    std::string content = load_file("valid/Array/Array_2.toml");
    item_t t{content.c_str()};

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

