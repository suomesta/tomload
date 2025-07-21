#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "tomload.hpp"

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

TEST_CASE("String_6.toml") {
    std::string content = load_file("String_6.toml");
    view_t src{content.c_str()};
    item_t t = parse(src);

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
    view_t src{content.c_str()};
    item_t t = parse(src);

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["regex2"].is_string() == true);
    CHECK(t["regex2"].get_string() == "I [dw]on't need \\d{2} apples");
    CHECK(t["lines"].is_string() == true);
    CHECK(t["lines"].get_string() == "The first newline is\ntrimmed in raw strings.\n   All other whitespace\n   is preserved.\n");
}

TEST_CASE("String_8.toml") {
    std::string content = load_file("String_8.toml");
    view_t src{content.c_str()};
    item_t t = parse(src);

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
    view_t src{content.c_str()};
    item_t t = parse(src);

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["bool1"].is_boolean() == true);
    CHECK(t["bool1"].get_bool() == true);
    CHECK(t["bool2"].is_boolean() == true);
    CHECK(t["bool2"].get_bool() == false);
}
