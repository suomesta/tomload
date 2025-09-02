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

}  // namespace

using namespace tomload;

TEST_CASE("valid/integer/float64-max.toml") {
    std::string content = load_file("valid/integer/float64-max.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["max_int"].is_integer() == true);
    CHECK(t["max_int"].get_integer() == 9007199254740991);
    CHECK(t["min_int"].is_integer() == true);
    CHECK(t["min_int"].get_integer() == -9007199254740991);
}

TEST_CASE("valid/integer/integer.toml") {
    std::string content = load_file("valid/integer/integer.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["answer"].is_integer() == true);
    CHECK(t["answer"].get_integer() == 42);
    CHECK(t["posanswer"].is_integer() == true);
    CHECK(t["posanswer"].get_integer() == 42);
    CHECK(t["neganswer"].is_integer() == true);
    CHECK(t["neganswer"].get_integer() == -42);
    CHECK(t["zero"].is_integer() == true);
    CHECK(t["zero"].get_integer() == 0);
}

TEST_CASE("valid/integer/literals.toml") {
    std::string content = load_file("valid/integer/literals.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 9);
    CHECK(t["bin1"].is_integer() == true);
    CHECK(t["bin1"].get_integer() == 214);
    CHECK(t["bin2"].is_integer() == true);
    CHECK(t["bin2"].get_integer() == 5);
    CHECK(t["oct1"].is_integer() == true);
    CHECK(t["oct1"].get_integer() == 342391);
    CHECK(t["oct2"].is_integer() == true);
    CHECK(t["oct2"].get_integer() == 493);
    CHECK(t["oct3"].is_integer() == true);
    CHECK(t["oct3"].get_integer() == 501);
    CHECK(t["hex1"].is_integer() == true);
    CHECK(t["hex1"].get_integer() == 3735928559);
    CHECK(t["hex2"].is_integer() == true);
    CHECK(t["hex2"].get_integer() == 3735928559);
    CHECK(t["hex3"].is_integer() == true);
    CHECK(t["hex3"].get_integer() == 3735928559);
    CHECK(t["hex4"].is_integer() == true);
    CHECK(t["hex4"].get_integer() == 2439);
}

TEST_CASE("valid/integer/long.toml") {
    std::string content = load_file("valid/integer/long.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["int64-max"].is_integer() == true);
    CHECK(t["int64-max"].get_integer() == 9223372036854775807);
    CHECK(t["int64-max-neg"].is_integer() == true);
    CHECK(t["int64-max-neg"].get_integer() == -9223372036854775808);
}

TEST_CASE("valid/integer/underscore.toml") {
    std::string content = load_file("valid/integer/underscore.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["kilo"].is_integer() == true);
    CHECK(t["kilo"].get_integer() == 1000);
    CHECK(t["x"].is_integer() == true);
    CHECK(t["x"].get_integer() == 1111);
}

TEST_CASE("valid/integer/zero.toml") {
    std::string content = load_file("valid/integer/zero.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 12);
    CHECK(t["d1"].is_integer() == true);
    CHECK(t["d1"].get_integer() == 0);
    CHECK(t["d2"].is_integer() == true);
    CHECK(t["d2"].get_integer() == 0);
    CHECK(t["d3"].is_integer() == true);
    CHECK(t["d3"].get_integer() == 0);
    CHECK(t["h1"].is_integer() == true);
    CHECK(t["h1"].get_integer() == 0);
    CHECK(t["h2"].is_integer() == true);
    CHECK(t["h2"].get_integer() == 0);
    CHECK(t["h3"].is_integer() == true);
    CHECK(t["h3"].get_integer() == 0);
    CHECK(t["o1"].is_integer() == true);
    CHECK(t["o1"].get_integer() == 0);
    CHECK(t["a2"].is_integer() == true);
    CHECK(t["a2"].get_integer() == 0);
    CHECK(t["a3"].is_integer() == true);
    CHECK(t["a3"].get_integer() == 0);
    CHECK(t["b1"].is_integer() == true);
    CHECK(t["b1"].get_integer() == 0);
    CHECK(t["b2"].is_integer() == true);
    CHECK(t["b2"].get_integer() == 0);
    CHECK(t["b3"].is_integer() == true);
    CHECK(t["b3"].get_integer() == 0);
}

