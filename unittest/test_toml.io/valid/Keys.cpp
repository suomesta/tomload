#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
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

TEST_CASE("valid/Keys/Keys_1.toml") {
    std::string content = load_file("valid/Keys/Keys_1.toml");
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

TEST_CASE("valid/Keys/Keys_10.toml") {
    std::string content = load_file("valid/Keys/Keys_10.toml");
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

TEST_CASE("valid/Keys/Keys_11.toml") {
    std::string content = load_file("valid/Keys/Keys_11.toml");
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

TEST_CASE("valid/Keys/Keys_12.toml") {
    std::string content = load_file("valid/Keys/Keys_12.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["3"].is_table() == true);
    CHECK(t["3"].size() == 1);
    CHECK(t["3"]["14159"].is_string() == true);
    CHECK(t["3"]["14159"].get_string() == "pi");
}

TEST_CASE("valid/Keys/Keys_2.toml") {
    std::string content = load_file("valid/Keys/Keys_2.toml");
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

TEST_CASE("valid/Keys/Keys_3_fix1.toml") {
    std::string content = load_file("valid/Keys/Keys_3_fix1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[""].is_string() == true);
    CHECK(t[""].get_string() == "blank");
}

TEST_CASE("valid/Keys/Keys_3_fix2.toml") {
    std::string content = load_file("valid/Keys/Keys_3_fix2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[""].is_string() == true);
    CHECK(t[""].get_string() == "blank");
}

TEST_CASE("valid/Keys/Keys_4.toml") {
    std::string content = load_file("valid/Keys/Keys_4.toml");
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

TEST_CASE("valid/Keys/Keys_5.toml") {
    std::string content = load_file("valid/Keys/Keys_5.toml");
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

TEST_CASE("valid/Keys/Keys_8.toml") {
    std::string content = load_file("valid/Keys/Keys_8.toml");
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

