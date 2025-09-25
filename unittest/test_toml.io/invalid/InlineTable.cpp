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

TEST_CASE("invalid/InlineTable/InlineTable_2_invalid.toml") {
    std::string content = load_file("invalid/InlineTable/InlineTable_2_invalid.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/InlineTable/InlineTable_3_invalid.toml") {
    std::string content = load_file("invalid/InlineTable/InlineTable_3_invalid.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

