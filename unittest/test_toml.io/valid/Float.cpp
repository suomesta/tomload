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

TEST_CASE("valid/Float/Float_1.toml") {
    std::string content = load_file("valid/Float/Float_1.toml");
    item_t t{content.c_str()};

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

TEST_CASE("valid/Float/Float_3.toml") {
    std::string content = load_file("valid/Float/Float_3.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["flt8"].is_float() == true);
    CHECK(t["flt8"].get_float() == 224617.445991228);
}

TEST_CASE("valid/Float/Float_4.toml") {
    std::string content = load_file("valid/Float/Float_4.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["flt8"].is_float() == true);
    CHECK(t["flt8"].get_float() == 224617.445991228);
}

TEST_CASE("valid/Float/Float_5.toml") {
    std::string content = load_file("valid/Float/Float_5.toml");
    item_t t{content.c_str()};

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

