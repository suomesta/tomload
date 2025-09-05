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

TEST_CASE("invalid/integer/capital-bin.toml") {
    std::string content = load_file("invalid/integer/capital-bin.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/capital-hex.toml") {
    std::string content = load_file("invalid/integer/capital-hex.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/capital-oct.toml") {
    std::string content = load_file("invalid/integer/capital-oct.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/double-sign-nex.toml") {
    std::string content = load_file("invalid/integer/double-sign-nex.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/double-sign-plus.toml") {
    std::string content = load_file("invalid/integer/double-sign-plus.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/double-us.toml") {
    std::string content = load_file("invalid/integer/double-us.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/incomplete-bin.toml") {
    std::string content = load_file("invalid/integer/incomplete-bin.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/incomplete-hex.toml") {
    std::string content = load_file("invalid/integer/incomplete-hex.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/incomplete-oct.toml") {
    std::string content = load_file("invalid/integer/incomplete-oct.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/invalid-bin.toml") {
    std::string content = load_file("invalid/integer/invalid-bin.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-01.toml") {
    std::string content = load_file("invalid/integer/invalid-hex-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-02.toml") {
    std::string content = load_file("invalid/integer/invalid-hex-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-03.toml") {
    std::string content = load_file("invalid/integer/invalid-hex-03.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-1.toml") {
    std::string content = load_file("invalid/integer/invalid-hex-1.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/invalid-hex-2.toml") {
    std::string content = load_file("invalid/integer/invalid-hex-2.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/invalid-oct.toml") {
    std::string content = load_file("invalid/integer/invalid-oct.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-us-bin.toml") {
    std::string content = load_file("invalid/integer/leading-us-bin.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-us-hex.toml") {
    std::string content = load_file("invalid/integer/leading-us-hex.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-us-oct.toml") {
    std::string content = load_file("invalid/integer/leading-us-oct.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-us.toml") {
    std::string content = load_file("invalid/integer/leading-us.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-01.toml") {
    std::string content = load_file("invalid/integer/leading-zero-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-02.toml") {
    std::string content = load_file("invalid/integer/leading-zero-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-03.toml") {
    std::string content = load_file("invalid/integer/leading-zero-03.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-1.toml") {
    std::string content = load_file("invalid/integer/leading-zero-1.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-2.toml") {
    std::string content = load_file("invalid/integer/leading-zero-2.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-3.toml") {
    std::string content = load_file("invalid/integer/leading-zero-3.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-01.toml") {
    std::string content = load_file("invalid/integer/leading-zero-sign-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-02.toml") {
    std::string content = load_file("invalid/integer/leading-zero-sign-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-03.toml") {
    std::string content = load_file("invalid/integer/leading-zero-sign-03.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-1.toml") {
    std::string content = load_file("invalid/integer/leading-zero-sign-1.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-2.toml") {
    std::string content = load_file("invalid/integer/leading-zero-sign-2.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/leading-zero-sign-3.toml") {
    std::string content = load_file("invalid/integer/leading-zero-sign-3.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/negative-bin.toml") {
    std::string content = load_file("invalid/integer/negative-bin.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/negative-hex.toml") {
    std::string content = load_file("invalid/integer/negative-hex.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/negative-oct.toml") {
    std::string content = load_file("invalid/integer/negative-oct.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/positive-bin.toml") {
    std::string content = load_file("invalid/integer/positive-bin.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/positive-hex.toml") {
    std::string content = load_file("invalid/integer/positive-hex.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/positive-oct.toml") {
    std::string content = load_file("invalid/integer/positive-oct.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/text-after-integer.toml") {
    std::string content = load_file("invalid/integer/text-after-integer.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/trailing-us-bin.toml") {
    std::string content = load_file("invalid/integer/trailing-us-bin.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/trailing-us-hex.toml") {
    std::string content = load_file("invalid/integer/trailing-us-hex.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/trailing-us-oct.toml") {
    std::string content = load_file("invalid/integer/trailing-us-oct.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/trailing-us.toml") {
    std::string content = load_file("invalid/integer/trailing-us.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/us-after-bin.toml") {
    std::string content = load_file("invalid/integer/us-after-bin.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/us-after-hex.toml") {
    std::string content = load_file("invalid/integer/us-after-hex.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/integer/us-after-oct.toml") {
    std::string content = load_file("invalid/integer/us-after-oct.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

