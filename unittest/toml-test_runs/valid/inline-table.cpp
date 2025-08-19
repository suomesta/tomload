#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "tomload/tomload.h"

namespace {

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(TOML_TEST_DIR) + filename);
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

TEST_CASE("valid/inline-table/array-01.toml") {
    std::string content = load_file("valid/inline-table/array-01.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["arr"].is_array() == true);
    CHECK(t["arr"].size() == 2);
    CHECK(t["arr"][0].is_table() == true);
    CHECK(t["arr"][0].size() == 1);
    CHECK(t["arr"][0]["a"].is_integer() == true);
    CHECK(t["arr"][0]["a"].get_integer() == 1);
    CHECK(t["arr"][1].is_table() == true);
    CHECK(t["arr"][1].size() == 1);
    CHECK(t["arr"][1]["a"].is_integer() == true);
    CHECK(t["arr"][1]["a"].get_integer() == 2);
    CHECK(t["people"].is_array() == true);
    CHECK(t["people"].size() == 3);
    CHECK(t["people"][0].is_table() == true);
    CHECK(t["people"][0].size() == 2);
    CHECK(t["people"][0]["first_name"].is_string() == true);
    CHECK(t["people"][0]["first_name"].get_string() == "Bruce");
    CHECK(t["people"][0]["last_name"].is_string() == true);
    CHECK(t["people"][0]["last_name"].get_string() == "Springsteen");
    CHECK(t["people"][1].is_table() == true);
    CHECK(t["people"][1].size() == 2);
    CHECK(t["people"][1]["first_name"].is_string() == true);
    CHECK(t["people"][1]["first_name"].get_string() == "Eric");
    CHECK(t["people"][1]["last_name"].is_string() == true);
    CHECK(t["people"][1]["last_name"].get_string() == "Clapton");
    CHECK(t["people"][2].is_table() == true);
    CHECK(t["people"][2].size() == 2);
    CHECK(t["people"][2]["first_name"].is_string() == true);
    CHECK(t["people"][2]["first_name"].get_string() == "Bob");
    CHECK(t["people"][2]["last_name"].is_string() == true);
    CHECK(t["people"][2]["last_name"].get_string() == "Seger");
}

TEST_CASE("valid/inline-table/array-02.toml") {
    std::string content = load_file("valid/inline-table/array-02.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["a"].is_array() == true);
    CHECK(t["a"]["a"].size() == 0);
}

TEST_CASE("valid/inline-table/array-03.toml") {
    std::string content = load_file("valid/inline-table/array-03.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["b"].is_table() == true);
    CHECK(t["b"].size() == 2);
    CHECK(t["b"]["a"].is_array() == true);
    CHECK(t["b"]["a"].size() == 2);
    CHECK(t["b"]["a"][0].is_integer() == true);
    CHECK(t["b"]["a"][0].get_integer() == 1);
    CHECK(t["b"]["a"][1].is_integer() == true);
    CHECK(t["b"]["a"][1].get_integer() == 2);
    CHECK(t["b"]["b"].is_array() == true);
    CHECK(t["b"]["b"].size() == 2);
    CHECK(t["b"]["b"][0].is_integer() == true);
    CHECK(t["b"]["b"][0].get_integer() == 3);
    CHECK(t["b"]["b"][1].is_integer() == true);
    CHECK(t["b"]["b"][1].get_integer() == 4);
}

TEST_CASE("valid/inline-table/bool.toml") {
    std::string content = load_file("valid/inline-table/bool.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 2);
    CHECK(t["a"]["a"].is_boolean() == true);
    CHECK(t["a"]["a"].get_boolean() == true);
    CHECK(t["a"]["b"].is_boolean() == true);
    CHECK(t["a"]["b"].get_boolean() == false);
}

TEST_CASE("valid/inline-table/empty.toml") {
    std::string content = load_file("valid/inline-table/empty.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t["empty1"].is_table() == true);
    CHECK(t["empty1"].size() == 0);
    CHECK(t["empty2"].is_table() == true);
    CHECK(t["empty2"].size() == 0);
    CHECK(t["empty_in_array"].is_array() == true);
    CHECK(t["empty_in_array"].size() == 2);
    CHECK(t["empty_in_array"][0].is_table() == true);
    CHECK(t["empty_in_array"][0].size() == 1);
    CHECK(t["empty_in_array"][0]["not_empty"].is_integer() == true);
    CHECK(t["empty_in_array"][0]["not_empty"].get_integer() == 1);
    CHECK(t["empty_in_array"][1].is_table() == true);
    CHECK(t["empty_in_array"][1].size() == 0);
    CHECK(t["empty_in_array2"].is_array() == true);
    CHECK(t["empty_in_array2"].size() == 2);
    CHECK(t["empty_in_array2"][0].is_table() == true);
    CHECK(t["empty_in_array2"][0].size() == 0);
    CHECK(t["empty_in_array2"][1].is_table() == true);
    CHECK(t["empty_in_array2"][1].size() == 1);
    CHECK(t["empty_in_array2"][1]["not_empty"].is_integer() == true);
    CHECK(t["empty_in_array2"][1]["not_empty"].get_integer() == 1);
    CHECK(t["many_empty"].is_array() == true);
    CHECK(t["many_empty"].size() == 3);
    CHECK(t["many_empty"][0].is_table() == true);
    CHECK(t["many_empty"][0].size() == 0);
    CHECK(t["many_empty"][1].is_table() == true);
    CHECK(t["many_empty"][1].size() == 0);
    CHECK(t["many_empty"][2].is_table() == true);
    CHECK(t["many_empty"][2].size() == 0);
    CHECK(t["nested_empty"].is_table() == true);
    CHECK(t["nested_empty"].size() == 1);
    CHECK(t["nested_empty"]["empty"].is_table() == true);
    CHECK(t["nested_empty"]["empty"].size() == 0);
    CHECK(t["with_cmt"].is_table() == true);
    CHECK(t["with_cmt"].size() == 0);
}

TEST_CASE("valid/inline-table/end-in-bool.toml") {
    std::string content = load_file("valid/inline-table/end-in-bool.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["black"].is_table() == true);
    CHECK(t["black"].size() == 3);
    CHECK(t["black"]["python"].is_string() == true);
    CHECK(t["black"]["python"].get_string() == ">3.6");
    CHECK(t["black"]["version"].is_string() == true);
    CHECK(t["black"]["version"].get_string() == ">=18.9b0");
    CHECK(t["black"]["allow_prereleases"].is_boolean() == true);
    CHECK(t["black"]["allow_prereleases"].get_boolean() == true);
}

TEST_CASE("valid/inline-table/inline-table.toml") {
    std::string content = load_file("valid/inline-table/inline-table.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
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
    CHECK(t["simple"].is_table() == true);
    CHECK(t["simple"].size() == 1);
    CHECK(t["simple"]["a"].is_integer() == true);
    CHECK(t["simple"]["a"].get_integer() == 1);
    CHECK(t["str-key"].is_table() == true);
    CHECK(t["str-key"].size() == 1);
    CHECK(t["str-key"]["a"].is_integer() == true);
    CHECK(t["str-key"]["a"].get_integer() == 1);
    CHECK(t["table-array"].is_array() == true);
    CHECK(t["table-array"].size() == 2);
    CHECK(t["table-array"][0].is_table() == true);
    CHECK(t["table-array"][0].size() == 1);
    CHECK(t["table-array"][0]["a"].is_integer() == true);
    CHECK(t["table-array"][0]["a"].get_integer() == 1);
    CHECK(t["table-array"][1].is_table() == true);
    CHECK(t["table-array"][1].size() == 1);
    CHECK(t["table-array"][1]["b"].is_integer() == true);
    CHECK(t["table-array"][1]["b"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/key-dotted-1.toml") {
    std::string content = load_file("valid/inline-table/key-dotted-1.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["a"].is_table() == true);
    CHECK(t["a"]["a"].size() == 1);
    CHECK(t["a"]["a"]["b"].is_integer() == true);
    CHECK(t["a"]["a"]["b"].get_integer() == 1);
    CHECK(t["b"].is_table() == true);
    CHECK(t["b"].size() == 1);
    CHECK(t["b"]["a"].is_table() == true);
    CHECK(t["b"]["a"].size() == 1);
    CHECK(t["b"]["a"]["b"].is_integer() == true);
    CHECK(t["b"]["a"]["b"].get_integer() == 1);
    CHECK(t["c"].is_table() == true);
    CHECK(t["c"].size() == 1);
    CHECK(t["c"]["a"].is_table() == true);
    CHECK(t["c"]["a"].size() == 1);
    CHECK(t["c"]["a"]["b"].is_integer() == true);
    CHECK(t["c"]["a"]["b"].get_integer() == 1);
    CHECK(t["d"].is_table() == true);
    CHECK(t["d"].size() == 1);
    CHECK(t["d"]["a"].is_table() == true);
    CHECK(t["d"]["a"].size() == 1);
    CHECK(t["d"]["a"]["b"].is_integer() == true);
    CHECK(t["d"]["a"]["b"].get_integer() == 1);
    CHECK(t["e"].is_table() == true);
    CHECK(t["e"].size() == 1);
    CHECK(t["e"]["a"].is_table() == true);
    CHECK(t["e"]["a"].size() == 1);
    CHECK(t["e"]["a"]["b"].is_integer() == true);
    CHECK(t["e"]["a"]["b"].get_integer() == 1);
}

TEST_CASE("valid/inline-table/key-dotted-2.toml") {
    std::string content = load_file("valid/inline-table/key-dotted-2.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["many"].is_table() == true);
    CHECK(t["many"].size() == 1);
    CHECK(t["many"]["dots"].is_table() == true);
    CHECK(t["many"]["dots"].size() == 1);
    CHECK(t["many"]["dots"]["here"].is_table() == true);
    CHECK(t["many"]["dots"]["here"].size() == 1);
    CHECK(t["many"]["dots"]["here"]["dot"].is_table() == true);
    CHECK(t["many"]["dots"]["here"]["dot"].size() == 1);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"].is_table() == true);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"].size() == 1);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"].is_table() == true);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"].size() == 1);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"]["a"].is_table() == true);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"]["a"].size() == 1);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"]["a"]["b"].is_table() == true);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"]["a"]["b"].size() == 2);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"]["a"]["b"]["c"].is_integer() == true);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"]["a"]["b"]["c"].get_integer() == 1);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"]["a"]["b"]["d"].is_integer() == true);
    CHECK(t["many"]["dots"]["here"]["dot"]["dot"]["dot"]["a"]["b"]["d"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/key-dotted-3.toml") {
    std::string content = load_file("valid/inline-table/key-dotted-3.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["tbl"].is_table() == true);
    CHECK(t["tbl"].size() == 2);
    CHECK(t["tbl"]["a"].is_table() == true);
    CHECK(t["tbl"]["a"].size() == 1);
    CHECK(t["tbl"]["a"]["b"].is_table() == true);
    CHECK(t["tbl"]["a"]["b"].size() == 1);
    CHECK(t["tbl"]["a"]["b"]["c"].is_table() == true);
    CHECK(t["tbl"]["a"]["b"]["c"].size() == 1);
    CHECK(t["tbl"]["a"]["b"]["c"]["d"].is_table() == true);
    CHECK(t["tbl"]["a"]["b"]["c"]["d"].size() == 1);
    CHECK(t["tbl"]["a"]["b"]["c"]["d"]["e"].is_integer() == true);
    CHECK(t["tbl"]["a"]["b"]["c"]["d"]["e"].get_integer() == 1);
    CHECK(t["tbl"]["x"].is_table() == true);
    CHECK(t["tbl"]["x"].size() == 1);
    CHECK(t["tbl"]["x"]["a"].is_table() == true);
    CHECK(t["tbl"]["x"]["a"].size() == 1);
    CHECK(t["tbl"]["x"]["a"]["b"].is_table() == true);
    CHECK(t["tbl"]["x"]["a"]["b"].size() == 1);
    CHECK(t["tbl"]["x"]["a"]["b"]["c"].is_table() == true);
    CHECK(t["tbl"]["x"]["a"]["b"]["c"].size() == 1);
    CHECK(t["tbl"]["x"]["a"]["b"]["c"]["d"].is_table() == true);
    CHECK(t["tbl"]["x"]["a"]["b"]["c"]["d"].size() == 1);
    CHECK(t["tbl"]["x"]["a"]["b"]["c"]["d"]["e"].is_integer() == true);
    CHECK(t["tbl"]["x"]["a"]["b"]["c"]["d"]["e"].get_integer() == 1);
}

TEST_CASE("valid/inline-table/key-dotted-4.toml") {
/*
    std::string content = load_file("valid/inline-table/key-dotted-4.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["arr"].is_array() == true);
    CHECK(t["arr"].size() == 2);
    CHECK(t["arr"][0].is_table() == true);
    CHECK(t["arr"][0].size() == 2);
    CHECK(t["arr"][0]["t"].is_table() == true);
    CHECK(t["arr"][0]["t"].size() == 1);
    CHECK(t["arr"][0]["t"]["a"].is_table() == true);
    CHECK(t["arr"][0]["t"]["a"].size() == 1);
    CHECK(t["arr"][0]["t"]["a"]["b"].is_integer() == true);
    CHECK(t["arr"][0]["t"]["a"]["b"].get_integer() == 1);
    CHECK(t["arr"][0]["T"].is_table() == true);
    CHECK(t["arr"][0]["T"].size() == 1);
    CHECK(t["arr"][0]["T"]["a"].is_table() == true);
    CHECK(t["arr"][0]["T"]["a"].size() == 1);
    CHECK(t["arr"][0]["T"]["a"]["b"].is_integer() == true);
    CHECK(t["arr"][0]["T"]["a"]["b"].get_integer() == 1);
    CHECK(t["arr"][1].is_table() == true);
    CHECK(t["arr"][1].size() == 2);
    CHECK(t["arr"][1]["t"].is_table() == true);
    CHECK(t["arr"][1]["t"].size() == 1);
    CHECK(t["arr"][1]["t"]["a"].is_table() == true);
    CHECK(t["arr"][1]["t"]["a"].size() == 1);
    CHECK(t["arr"][1]["t"]["a"]["b"].is_integer() == true);
    CHECK(t["arr"][1]["t"]["a"]["b"].get_integer() == 2);
    CHECK(t["arr"][1]["T"].is_table() == true);
    CHECK(t["arr"][1]["T"].size() == 1);
    CHECK(t["arr"][1]["T"]["a"].is_table() == true);
    CHECK(t["arr"][1]["T"]["a"].size() == 1);
    CHECK(t["arr"][1]["T"]["a"]["b"].is_integer() == true);
    CHECK(t["arr"][1]["T"]["a"]["b"].get_integer() == 2);
*/
}

TEST_CASE("valid/inline-table/key-dotted-5.toml") {
    std::string content = load_file("valid/inline-table/key-dotted-5.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["arr-1"].is_array() == true);
    CHECK(t["arr-1"].size() == 1);
    CHECK(t["arr-1"][0].is_table() == true);
    CHECK(t["arr-1"][0].size() == 1);
    CHECK(t["arr-1"][0]["a"].is_table() == true);
    CHECK(t["arr-1"][0]["a"].size() == 1);
    CHECK(t["arr-1"][0]["a"]["b"].is_integer() == true);
    CHECK(t["arr-1"][0]["a"]["b"].get_integer() == 1);
    CHECK(t["arr-2"].is_array() == true);
    CHECK(t["arr-2"].size() == 2);
    CHECK(t["arr-2"][0].is_string() == true);
    CHECK(t["arr-2"][0].get_string() == "str");
    CHECK(t["arr-2"][1].is_table() == true);
    CHECK(t["arr-2"][1].size() == 1);
    CHECK(t["arr-2"][1]["a"].is_table() == true);
    CHECK(t["arr-2"][1]["a"].size() == 1);
    CHECK(t["arr-2"][1]["a"]["b"].is_integer() == true);
    CHECK(t["arr-2"][1]["a"]["b"].get_integer() == 1);
    CHECK(t["arr-3"].is_array() == true);
    CHECK(t["arr-3"].size() == 2);
    CHECK(t["arr-3"][0].is_table() == true);
    CHECK(t["arr-3"][0].size() == 1);
    CHECK(t["arr-3"][0]["a"].is_table() == true);
    CHECK(t["arr-3"][0]["a"].size() == 1);
    CHECK(t["arr-3"][0]["a"]["b"].is_integer() == true);
    CHECK(t["arr-3"][0]["a"]["b"].get_integer() == 1);
    CHECK(t["arr-3"][1].is_table() == true);
    CHECK(t["arr-3"][1].size() == 1);
    CHECK(t["arr-3"][1]["a"].is_table() == true);
    CHECK(t["arr-3"][1]["a"].size() == 1);
    CHECK(t["arr-3"][1]["a"]["b"].is_integer() == true);
    CHECK(t["arr-3"][1]["a"]["b"].get_integer() == 2);
    CHECK(t["arr-4"].is_array() == true);
    CHECK(t["arr-4"].size() == 3);
    CHECK(t["arr-4"][0].is_string() == true);
    CHECK(t["arr-4"][0].get_string() == "str");
    CHECK(t["arr-4"][1].is_table() == true);
    CHECK(t["arr-4"][1].size() == 1);
    CHECK(t["arr-4"][1]["a"].is_table() == true);
    CHECK(t["arr-4"][1]["a"].size() == 1);
    CHECK(t["arr-4"][1]["a"]["b"].is_integer() == true);
    CHECK(t["arr-4"][1]["a"]["b"].get_integer() == 1);
    CHECK(t["arr-4"][2].is_table() == true);
    CHECK(t["arr-4"][2].size() == 1);
    CHECK(t["arr-4"][2]["a"].is_table() == true);
    CHECK(t["arr-4"][2]["a"].size() == 1);
    CHECK(t["arr-4"][2]["a"]["b"].is_integer() == true);
    CHECK(t["arr-4"][2]["a"]["b"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/key-dotted-6.toml") {
    std::string content = load_file("valid/inline-table/key-dotted-6.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["top"].is_table() == true);
    CHECK(t["top"].size() == 1);
    CHECK(t["top"]["dot"].is_table() == true);
    CHECK(t["top"]["dot"].size() == 1);
    CHECK(t["top"]["dot"]["dot"].is_array() == true);
    CHECK(t["top"]["dot"]["dot"].size() == 2);
    CHECK(t["top"]["dot"]["dot"][0].is_table() == true);
    CHECK(t["top"]["dot"]["dot"][0].size() == 1);
    CHECK(t["top"]["dot"]["dot"][0]["dot"].is_table() == true);
    CHECK(t["top"]["dot"]["dot"][0]["dot"].size() == 1);
    CHECK(t["top"]["dot"]["dot"][0]["dot"]["dot"].is_table() == true);
    CHECK(t["top"]["dot"]["dot"][0]["dot"]["dot"].size() == 1);
    CHECK(t["top"]["dot"]["dot"][0]["dot"]["dot"]["dot"].is_integer() == true);
    CHECK(t["top"]["dot"]["dot"][0]["dot"]["dot"]["dot"].get_integer() == 1);
    CHECK(t["top"]["dot"]["dot"][1].is_table() == true);
    CHECK(t["top"]["dot"]["dot"][1].size() == 1);
    CHECK(t["top"]["dot"]["dot"][1]["dot"].is_table() == true);
    CHECK(t["top"]["dot"]["dot"][1]["dot"].size() == 1);
    CHECK(t["top"]["dot"]["dot"][1]["dot"]["dot"].is_table() == true);
    CHECK(t["top"]["dot"]["dot"][1]["dot"]["dot"].size() == 1);
    CHECK(t["top"]["dot"]["dot"][1]["dot"]["dot"]["dot"].is_integer() == true);
    CHECK(t["top"]["dot"]["dot"][1]["dot"]["dot"]["dot"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/key-dotted-7.toml") {
    std::string content = load_file("valid/inline-table/key-dotted-7.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["arr"].is_array() == true);
    CHECK(t["arr"].size() == 1);
    CHECK(t["arr"][0].is_table() == true);
    CHECK(t["arr"][0].size() == 1);
    CHECK(t["arr"][0]["a"].is_table() == true);
    CHECK(t["arr"][0]["a"].size() == 1);
    CHECK(t["arr"][0]["a"]["b"].is_array() == true);
    CHECK(t["arr"][0]["a"]["b"].size() == 1);
    CHECK(t["arr"][0]["a"]["b"][0].is_table() == true);
    CHECK(t["arr"][0]["a"]["b"][0].size() == 1);
    CHECK(t["arr"][0]["a"]["b"][0]["c"].is_table() == true);
    CHECK(t["arr"][0]["a"]["b"][0]["c"].size() == 1);
    CHECK(t["arr"][0]["a"]["b"][0]["c"]["d"].is_integer() == true);
    CHECK(t["arr"][0]["a"]["b"][0]["c"]["d"].get_integer() == 1);
}

TEST_CASE("valid/inline-table/multiline.toml") {
    std::string content = load_file("valid/inline-table/multiline.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["tbl_multiline"].is_table() == true);
    CHECK(t["tbl_multiline"].size() == 4);
    CHECK(t["tbl_multiline"]["a"].is_integer() == true);
    CHECK(t["tbl_multiline"]["a"].get_integer() == 1);
    CHECK(t["tbl_multiline"]["b"].is_string() == true);
    CHECK(t["tbl_multiline"]["b"].get_string() == "multiline\n");
    CHECK(t["tbl_multiline"]["c"].is_string() == true);
    CHECK(t["tbl_multiline"]["c"].get_string() == "and yet\nanother line");
    CHECK(t["tbl_multiline"]["d"].is_integer() == true);
    CHECK(t["tbl_multiline"]["d"].get_integer() == 4);
}

TEST_CASE("valid/inline-table/nest.toml") {
    std::string content = load_file("valid/inline-table/nest.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t["tbl_tbl_empty"].is_table() == true);
    CHECK(t["tbl_tbl_empty"].size() == 1);
    CHECK(t["tbl_tbl_empty"]["tbl_0"].is_table() == true);
    CHECK(t["tbl_tbl_empty"]["tbl_0"].size() == 0);
    CHECK(t["tbl_tbl_val"].is_table() == true);
    CHECK(t["tbl_tbl_val"].size() == 1);
    CHECK(t["tbl_tbl_val"]["tbl_1"].is_table() == true);
    CHECK(t["tbl_tbl_val"]["tbl_1"].size() == 1);
    CHECK(t["tbl_tbl_val"]["tbl_1"]["one"].is_integer() == true);
    CHECK(t["tbl_tbl_val"]["tbl_1"]["one"].get_integer() == 1);
    CHECK(t["tbl_arr_tbl"].is_table() == true);
    CHECK(t["tbl_arr_tbl"].size() == 1);
    CHECK(t["tbl_arr_tbl"]["arr_tbl"].is_array() == true);
    CHECK(t["tbl_arr_tbl"]["arr_tbl"].size() == 1);
    CHECK(t["tbl_arr_tbl"]["arr_tbl"][0].is_table() == true);
    CHECK(t["tbl_arr_tbl"]["arr_tbl"][0].size() == 1);
    CHECK(t["tbl_arr_tbl"]["arr_tbl"][0]["one"].is_integer() == true);
    CHECK(t["tbl_arr_tbl"]["arr_tbl"][0]["one"].get_integer() == 1);
    CHECK(t["arr_tbl_tbl"].is_array() == true);
    CHECK(t["arr_tbl_tbl"].size() == 1);
    CHECK(t["arr_tbl_tbl"][0].is_table() == true);
    CHECK(t["arr_tbl_tbl"][0].size() == 1);
    CHECK(t["arr_tbl_tbl"][0]["tbl"].is_table() == true);
    CHECK(t["arr_tbl_tbl"][0]["tbl"].size() == 1);
    CHECK(t["arr_tbl_tbl"][0]["tbl"]["one"].is_integer() == true);
    CHECK(t["arr_tbl_tbl"][0]["tbl"]["one"].get_integer() == 1);
    CHECK(t["arr_arr_tbl_empty"].is_array() == true);
    CHECK(t["arr_arr_tbl_empty"].size() == 1);
    CHECK(t["arr_arr_tbl_empty"][0].is_array() == true);
    CHECK(t["arr_arr_tbl_empty"][0].size() == 1);
    CHECK(t["arr_arr_tbl_empty"][0][0].is_table() == true);
    CHECK(t["arr_arr_tbl_empty"][0][0].size() == 0);
    CHECK(t["arr_arr_tbl_val"].is_array() == true);
    CHECK(t["arr_arr_tbl_val"].size() == 1);
    CHECK(t["arr_arr_tbl_val"][0].is_array() == true);
    CHECK(t["arr_arr_tbl_val"][0].size() == 1);
    CHECK(t["arr_arr_tbl_val"][0][0].is_table() == true);
    CHECK(t["arr_arr_tbl_val"][0][0].size() == 1);
    CHECK(t["arr_arr_tbl_val"][0][0]["one"].is_integer() == true);
    CHECK(t["arr_arr_tbl_val"][0][0]["one"].get_integer() == 1);
    CHECK(t["arr_arr_tbls"].is_array() == true);
    CHECK(t["arr_arr_tbls"].size() == 1);
    CHECK(t["arr_arr_tbls"][0].is_array() == true);
    CHECK(t["arr_arr_tbls"][0].size() == 2);
    CHECK(t["arr_arr_tbls"][0][0].is_table() == true);
    CHECK(t["arr_arr_tbls"][0][0].size() == 1);
    CHECK(t["arr_arr_tbls"][0][0]["one"].is_integer() == true);
    CHECK(t["arr_arr_tbls"][0][0]["one"].get_integer() == 1);
    CHECK(t["arr_arr_tbls"][0][1].is_table() == true);
    CHECK(t["arr_arr_tbls"][0][1].size() == 1);
    CHECK(t["arr_arr_tbls"][0][1]["two"].is_integer() == true);
    CHECK(t["arr_arr_tbls"][0][1]["two"].get_integer() == 2);
}

TEST_CASE("valid/inline-table/spaces.toml") {
    std::string content = load_file("valid/inline-table/spaces.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["clap-1"].is_table() == true);
    CHECK(t["clap-1"].size() == 2);
    CHECK(t["clap-1"]["version"].is_string() == true);
    CHECK(t["clap-1"]["version"].get_string() == "4");
    CHECK(t["clap-1"]["features"].is_array() == true);
    CHECK(t["clap-1"]["features"].size() == 2);
    CHECK(t["clap-1"]["features"][0].is_string() == true);
    CHECK(t["clap-1"]["features"][0].get_string() == "derive");
    CHECK(t["clap-1"]["features"][1].is_string() == true);
    CHECK(t["clap-1"]["features"][1].get_string() == "cargo");
    CHECK(t["clap-2"].is_table() == true);
    CHECK(t["clap-2"].size() == 3);
    CHECK(t["clap-2"]["version"].is_string() == true);
    CHECK(t["clap-2"]["version"].get_string() == "4");
    CHECK(t["clap-2"]["features"].is_array() == true);
    CHECK(t["clap-2"]["features"].size() == 2);
    CHECK(t["clap-2"]["features"][0].is_string() == true);
    CHECK(t["clap-2"]["features"][0].get_string() == "derive");
    CHECK(t["clap-2"]["features"][1].is_string() == true);
    CHECK(t["clap-2"]["features"][1].get_string() == "cargo");
    CHECK(t["clap-2"]["nest"].is_table() == true);
    CHECK(t["clap-2"]["nest"].size() == 2);
    CHECK(t["clap-2"]["nest"]["a"].is_string() == true);
    CHECK(t["clap-2"]["nest"]["a"].get_string() == "x");
    CHECK(t["clap-2"]["nest"]["b"].is_array() == true);
    CHECK(t["clap-2"]["nest"]["b"].size() == 2);
    CHECK(t["clap-2"]["nest"]["b"][0].is_float() == true);
    CHECK(t["clap-2"]["nest"]["b"][0].get_float() == 1.5);
    CHECK(t["clap-2"]["nest"]["b"][1].is_float() == true);
    CHECK(t["clap-2"]["nest"]["b"][1].get_float() == 9.0);
}

