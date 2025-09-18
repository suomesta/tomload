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

TEST_CASE("invalid/float/double-dot-01.toml") {
    std::string content = load_file("invalid/float/double-dot-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/double-dot-02.toml") {
    std::string content = load_file("invalid/float/double-dot-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/double-point-1.toml") {
    std::string content = load_file("invalid/float/double-point-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/double-point-2.toml") {
    std::string content = load_file("invalid/float/double-point-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-dot-01.toml") {
    std::string content = load_file("invalid/float/exp-dot-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-dot-02.toml") {
    std::string content = load_file("invalid/float/exp-dot-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-dot-03.toml") {
    std::string content = load_file("invalid/float/exp-dot-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-e-01.toml") {
    std::string content = load_file("invalid/float/exp-double-e-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-e-02.toml") {
    std::string content = load_file("invalid/float/exp-double-e-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-e-1.toml") {
    std::string content = load_file("invalid/float/exp-double-e-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-e-2.toml") {
    std::string content = load_file("invalid/float/exp-double-e-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-us.toml") {
    std::string content = load_file("invalid/float/exp-double-us.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-leading-us.toml") {
    std::string content = load_file("invalid/float/exp-leading-us.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-point-1.toml") {
    std::string content = load_file("invalid/float/exp-point-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-point-2.toml") {
    std::string content = load_file("invalid/float/exp-point-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-point-3.toml") {
    std::string content = load_file("invalid/float/exp-point-3.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us-01.toml") {
    std::string content = load_file("invalid/float/exp-trailing-us-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us-02.toml") {
    std::string content = load_file("invalid/float/exp-trailing-us-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us-1.toml") {
    std::string content = load_file("invalid/float/exp-trailing-us-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us-2.toml") {
    std::string content = load_file("invalid/float/exp-trailing-us-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us.toml") {
    std::string content = load_file("invalid/float/exp-trailing-us.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/inf-capital.toml") {
    std::string content = load_file("invalid/float/inf-capital.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-01.toml") {
    std::string content = load_file("invalid/float/inf-incomplete-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-02.toml") {
    std::string content = load_file("invalid/float/inf-incomplete-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-03.toml") {
    std::string content = load_file("invalid/float/inf-incomplete-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-1.toml") {
    std::string content = load_file("invalid/float/inf-incomplete-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-2.toml") {
    std::string content = load_file("invalid/float/inf-incomplete-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-3.toml") {
    std::string content = load_file("invalid/float/inf-incomplete-3.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/inf_underscore.toml") {
    std::string content = load_file("invalid/float/inf_underscore.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-dot-neg.toml") {
    std::string content = load_file("invalid/float/leading-dot-neg.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-dot-plus.toml") {
    std::string content = load_file("invalid/float/leading-dot-plus.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-dot.toml") {
    std::string content = load_file("invalid/float/leading-dot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-point-neg.toml") {
    std::string content = load_file("invalid/float/leading-point-neg.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-point-plus.toml") {
    std::string content = load_file("invalid/float/leading-point-plus.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-point.toml") {
    std::string content = load_file("invalid/float/leading-point.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-us.toml") {
    std::string content = load_file("invalid/float/leading-us.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-zero-neg.toml") {
    std::string content = load_file("invalid/float/leading-zero-neg.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-zero-plus.toml") {
    std::string content = load_file("invalid/float/leading-zero-plus.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/leading-zero.toml") {
    std::string content = load_file("invalid/float/leading-zero.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/nan-capital.toml") {
    std::string content = load_file("invalid/float/nan-capital.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-01.toml") {
    std::string content = load_file("invalid/float/nan-incomplete-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-02.toml") {
    std::string content = load_file("invalid/float/nan-incomplete-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-03.toml") {
    std::string content = load_file("invalid/float/nan-incomplete-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-1.toml") {
    std::string content = load_file("invalid/float/nan-incomplete-1.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-2.toml") {
    std::string content = load_file("invalid/float/nan-incomplete-2.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-3.toml") {
    std::string content = load_file("invalid/float/nan-incomplete-3.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/nan_underscore.toml") {
    std::string content = load_file("invalid/float/nan_underscore.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-dot-01.toml") {
    std::string content = load_file("invalid/float/trailing-dot-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-dot-02.toml") {
    std::string content = load_file("invalid/float/trailing-dot-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-dot-min.toml") {
    std::string content = load_file("invalid/float/trailing-dot-min.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-dot-plus.toml") {
    std::string content = load_file("invalid/float/trailing-dot-plus.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-exp-minus.toml") {
    std::string content = load_file("invalid/float/trailing-exp-minus.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-exp-plus.toml") {
    std::string content = load_file("invalid/float/trailing-exp-plus.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-exp-point.toml") {
    std::string content = load_file("invalid/float/trailing-exp-point.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-exp.toml") {
    std::string content = load_file("invalid/float/trailing-exp.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-point-min.toml") {
    std::string content = load_file("invalid/float/trailing-point-min.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-point-plus.toml") {
    std::string content = load_file("invalid/float/trailing-point-plus.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-point.toml") {
    std::string content = load_file("invalid/float/trailing-point.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-us-exp-01.toml") {
    std::string content = load_file("invalid/float/trailing-us-exp-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-us-exp-02.toml") {
    std::string content = load_file("invalid/float/trailing-us-exp-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/trailing-us.toml") {
    std::string content = load_file("invalid/float/trailing-us.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/us-after-dot.toml") {
    std::string content = load_file("invalid/float/us-after-dot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/us-after-point.toml") {
    std::string content = load_file("invalid/float/us-after-point.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/us-before-dot.toml") {
    std::string content = load_file("invalid/float/us-before-dot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/float/us-before-point.toml") {
    std::string content = load_file("invalid/float/us-before-point.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

