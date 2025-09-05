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

TEST_CASE("invalid/bool/almost-false-with-extra.toml") {
    std::string content = load_file("invalid/bool/almost-false-with-extra.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/almost-false.toml") {
    std::string content = load_file("invalid/bool/almost-false.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/almost-true-with-extra.toml") {
    std::string content = load_file("invalid/bool/almost-true-with-extra.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/almost-true.toml") {
    std::string content = load_file("invalid/bool/almost-true.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/capitalized-false.toml") {
    std::string content = load_file("invalid/bool/capitalized-false.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/capitalized-true.toml") {
    std::string content = load_file("invalid/bool/capitalized-true.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/just-f.toml") {
    std::string content = load_file("invalid/bool/just-f.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/just-t.toml") {
    std::string content = load_file("invalid/bool/just-t.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/mixed-case-false.toml") {
    std::string content = load_file("invalid/bool/mixed-case-false.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/mixed-case-true.toml") {
    std::string content = load_file("invalid/bool/mixed-case-true.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/mixed-case.toml") {
    std::string content = load_file("invalid/bool/mixed-case.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/starting-same-false.toml") {
    std::string content = load_file("invalid/bool/starting-same-false.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/starting-same-true.toml") {
    std::string content = load_file("invalid/bool/starting-same-true.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/wrong-case-false.toml") {
    std::string content = load_file("invalid/bool/wrong-case-false.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/bool/wrong-case-true.toml") {
    std::string content = load_file("invalid/bool/wrong-case-true.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

