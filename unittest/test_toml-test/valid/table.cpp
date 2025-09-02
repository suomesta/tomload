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

TEST_CASE("valid/table/empty-name.toml") {
    std::string content = load_file("valid/table/empty-name.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[""].is_table() == true);
    CHECK(t[""].size() == 2);
    CHECK(t[""]["x"].is_integer() == true);
    CHECK(t[""]["x"].get_integer() == 1);
    CHECK(t[""]["a"].is_table() == true);
    CHECK(t[""]["a"].size() == 1);
    CHECK(t[""]["a"]["x"].is_integer() == true);
    CHECK(t[""]["a"]["x"].get_integer() == 2);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"][""].is_table() == true);
    CHECK(t["a"][""].size() == 1);
    CHECK(t["a"][""]["x"].is_integer() == true);
    CHECK(t["a"][""]["x"].get_integer() == 3);
}

TEST_CASE("valid/table/empty.toml") {
    std::string content = load_file("valid/table/empty.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 0);
}

TEST_CASE("valid/table/keyword-with-values.toml") {
    std::string content = load_file("valid/table/keyword-with-values.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["true"].is_table() == true);
    CHECK(t["true"].size() == 1);
    CHECK(t["true"]["k"].is_integer() == true);
    CHECK(t["true"]["k"].get_integer() == 1);
    CHECK(t["false"].is_table() == true);
    CHECK(t["false"].size() == 1);
    CHECK(t["false"]["k"].is_integer() == true);
    CHECK(t["false"]["k"].get_integer() == 2);
    CHECK(t["inf"].is_table() == true);
    CHECK(t["inf"].size() == 1);
    CHECK(t["inf"]["k"].is_integer() == true);
    CHECK(t["inf"]["k"].get_integer() == 3);
    CHECK(t["nan"].is_table() == true);
    CHECK(t["nan"].size() == 1);
    CHECK(t["nan"]["k"].is_integer() == true);
    CHECK(t["nan"]["k"].get_integer() == 4);
}

TEST_CASE("valid/table/keyword.toml") {
    std::string content = load_file("valid/table/keyword.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["true"].is_table() == true);
    CHECK(t["true"].size() == 0);
    CHECK(t["false"].is_table() == true);
    CHECK(t["false"].size() == 0);
    CHECK(t["inf"].is_table() == true);
    CHECK(t["inf"].size() == 0);
    CHECK(t["nan"].is_table() == true);
    CHECK(t["nan"].size() == 0);
}

TEST_CASE("valid/table/names-with-values.toml") {
    std::string content = load_file("valid/table/names-with-values.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 4);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 1);
    CHECK(t["a"]["b"]["c"].is_table() == true);
    CHECK(t["a"]["b"]["c"].size() == 1);
    CHECK(t["a"]["b"]["c"]["key"].is_integer() == true);
    CHECK(t["a"]["b"]["c"]["key"].get_integer() == 1);
    CHECK(t["a"]["b.c"].is_table() == true);
    CHECK(t["a"]["b.c"].size() == 1);
    CHECK(t["a"]["b.c"]["key"].is_integer() == true);
    CHECK(t["a"]["b.c"]["key"].get_integer() == 2);
    CHECK(t["a"]["d.e"].is_table() == true);
    CHECK(t["a"]["d.e"].size() == 1);
    CHECK(t["a"]["d.e"]["key"].is_integer() == true);
    CHECK(t["a"]["d.e"]["key"].get_integer() == 3);
    CHECK(t["a"][" x "].is_table() == true);
    CHECK(t["a"][" x "].size() == 1);
    CHECK(t["a"][" x "]["key"].is_integer() == true);
    CHECK(t["a"][" x "]["key"].get_integer() == 4);
    CHECK(t["d"].is_table() == true);
    CHECK(t["d"].size() == 1);
    CHECK(t["d"]["e"].is_table() == true);
    CHECK(t["d"]["e"].size() == 1);
    CHECK(t["d"]["e"]["f"].is_table() == true);
    CHECK(t["d"]["e"]["f"].size() == 1);
    CHECK(t["d"]["e"]["f"]["key"].is_integer() == true);
    CHECK(t["d"]["e"]["f"]["key"].get_integer() == 5);
    CHECK(t["g"].is_table() == true);
    CHECK(t["g"].size() == 1);
    CHECK(t["g"]["h"].is_table() == true);
    CHECK(t["g"]["h"].size() == 1);
    CHECK(t["g"]["h"]["i"].is_table() == true);
    CHECK(t["g"]["h"]["i"].size() == 1);
    CHECK(t["g"]["h"]["i"]["key"].is_integer() == true);
    CHECK(t["g"]["h"]["i"]["key"].get_integer() == 6);
    CHECK(t["j"].is_table() == true);
    CHECK(t["j"].size() == 1);
    CHECK(t["j"]["ʞ"].is_table() == true);
    CHECK(t["j"]["ʞ"].size() == 1);
    CHECK(t["j"]["ʞ"]["l"].is_table() == true);
    CHECK(t["j"]["ʞ"]["l"].size() == 1);
    CHECK(t["j"]["ʞ"]["l"]["key"].is_integer() == true);
    CHECK(t["j"]["ʞ"]["l"]["key"].get_integer() == 7);
    CHECK(t["x"].is_table() == true);
    CHECK(t["x"].size() == 1);
    CHECK(t["x"]["1"].is_table() == true);
    CHECK(t["x"]["1"].size() == 1);
    CHECK(t["x"]["1"]["2"].is_table() == true);
    CHECK(t["x"]["1"]["2"].size() == 1);
    CHECK(t["x"]["1"]["2"]["key"].is_integer() == true);
    CHECK(t["x"]["1"]["2"]["key"].get_integer() == 8);
}

TEST_CASE("valid/table/names.toml") {
    std::string content = load_file("valid/table/names.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 4);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 1);
    CHECK(t["a"]["b"]["c"].is_table() == true);
    CHECK(t["a"]["b"]["c"].size() == 0);
    CHECK(t["a"]["b.c"].is_table() == true);
    CHECK(t["a"]["b.c"].size() == 0);
    CHECK(t["a"]["d.e"].is_table() == true);
    CHECK(t["a"]["d.e"].size() == 0);
    CHECK(t["a"][" x "].is_table() == true);
    CHECK(t["a"][" x "].size() == 0);
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
    CHECK(t["x"].is_table() == true);
    CHECK(t["x"].size() == 1);
    CHECK(t["x"]["1"].is_table() == true);
    CHECK(t["x"]["1"].size() == 1);
    CHECK(t["x"]["1"]["2"].is_table() == true);
    CHECK(t["x"]["1"]["2"].size() == 0);
}

TEST_CASE("valid/table/no-eol.toml") {
    std::string content = load_file("valid/table/no-eol.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["table"].is_table() == true);
    CHECK(t["table"].size() == 0);
}

TEST_CASE("valid/table/sub-empty.toml") {
    std::string content = load_file("valid/table/sub-empty.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 0);
}

TEST_CASE("valid/table/sub.toml") {
    std::string content = load_file("valid/table/sub.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 2);
    CHECK(t["a"]["key"].is_integer() == true);
    CHECK(t["a"]["key"].get_integer() == 1);
    CHECK(t["a"]["extend"].is_table() == true);
    CHECK(t["a"]["extend"].size() == 2);
    CHECK(t["a"]["extend"]["key"].is_integer() == true);
    CHECK(t["a"]["extend"]["key"].get_integer() == 2);
    CHECK(t["a"]["extend"]["more"].is_table() == true);
    CHECK(t["a"]["extend"]["more"].size() == 1);
    CHECK(t["a"]["extend"]["more"]["key"].is_integer() == true);
    CHECK(t["a"]["extend"]["more"]["key"].get_integer() == 3);
}

TEST_CASE("valid/table/whitespace.toml") {
    std::string content = load_file("valid/table/whitespace.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["valid key"].is_table() == true);
    CHECK(t["valid key"].size() == 0);
}

TEST_CASE("valid/table/with-literal-string.toml") {
    std::string content = load_file("valid/table/with-literal-string.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["\"b\""].is_table() == true);
    CHECK(t["a"]["\"b\""].size() == 1);
    CHECK(t["a"]["\"b\""]["c"].is_table() == true);
    CHECK(t["a"]["\"b\""]["c"].size() == 1);
    CHECK(t["a"]["\"b\""]["c"]["answer"].is_integer() == true);
    CHECK(t["a"]["\"b\""]["c"]["answer"].get_integer() == 42);
}

TEST_CASE("valid/table/with-pound.toml") {
    std::string content = load_file("valid/table/with-pound.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["key#group"].is_table() == true);
    CHECK(t["key#group"].size() == 1);
    CHECK(t["key#group"]["answer"].is_integer() == true);
    CHECK(t["key#group"]["answer"].get_integer() == 42);
}

TEST_CASE("valid/table/with-single-quotes.toml") {
    std::string content = load_file("valid/table/with-single-quotes.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 1);
    CHECK(t["a"]["b"]["c"].is_table() == true);
    CHECK(t["a"]["b"]["c"].size() == 1);
    CHECK(t["a"]["b"]["c"]["answer"].is_integer() == true);
    CHECK(t["a"]["b"]["c"]["answer"].get_integer() == 42);
}

TEST_CASE("valid/table/without-super-with-values.toml") {
    std::string content = load_file("valid/table/without-super-with-values.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["x"].is_table() == true);
    CHECK(t["x"].size() == 3);
    CHECK(t["x"]["y"].is_table() == true);
    CHECK(t["x"]["y"].size() == 1);
    CHECK(t["x"]["y"]["z"].is_table() == true);
    CHECK(t["x"]["y"]["z"].size() == 1);
    CHECK(t["x"]["y"]["z"]["w"].is_table() == true);
    CHECK(t["x"]["y"]["z"]["w"].size() == 2);
    CHECK(t["x"]["y"]["z"]["w"]["a"].is_integer() == true);
    CHECK(t["x"]["y"]["z"]["w"]["a"].get_integer() == 1);
    CHECK(t["x"]["y"]["z"]["w"]["b"].is_integer() == true);
    CHECK(t["x"]["y"]["z"]["w"]["b"].get_integer() == 2);
    CHECK(t["x"]["c"].is_integer() == true);
    CHECK(t["x"]["c"].get_integer() == 3);
    CHECK(t["x"]["d"].is_integer() == true);
    CHECK(t["x"]["d"].get_integer() == 4);
}

TEST_CASE("valid/table/without-super.toml") {
    std::string content = load_file("valid/table/without-super.toml");
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

