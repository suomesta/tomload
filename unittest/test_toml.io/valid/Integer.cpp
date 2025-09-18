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

TEST_CASE("valid/Integer/Integer_1.toml") {
    std::string content = load_file("valid/Integer/Integer_1.toml");
    item_t t{content.c_str()};

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

TEST_CASE("valid/Integer/Integer_2.toml") {
    std::string content = load_file("valid/Integer/Integer_2.toml");
    item_t t{content.c_str()};

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

TEST_CASE("valid/Integer/Integer_3.toml") {
    std::string content = load_file("valid/Integer/Integer_3.toml");
    item_t t{content.c_str()};

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

