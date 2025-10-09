// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

// This file is generated automatically. Do not modify.

#include <cmath>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <doctest/doctest.h>
#include "tomload/tomload.h"

namespace {

std::vector<char> load_file(const std::string& filename) {
    std::ifstream file(std::string(TOML_TEST_DIR) + filename, std::ios::binary | std::ios::ate);
    if (not file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::streamsize size = file.tellg();
    std::vector<char> buffer(size);

    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), size); 

    return buffer;
}

struct rhs_nan {};
bool operator==(tomload::float_t f, rhs_nan) {
    return std::isnan(f);
}

}  // namespace

using namespace tomload;

TEST_CASE("invalid/float/double-dot-01.toml") {
    std::vector<char> content = load_file("invalid/float/double-dot-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/double-dot-02.toml") {
    std::vector<char> content = load_file("invalid/float/double-dot-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/double-point-1.toml") {
    std::vector<char> content = load_file("invalid/float/double-point-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/double-point-2.toml") {
    std::vector<char> content = load_file("invalid/float/double-point-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-dot-01.toml") {
    std::vector<char> content = load_file("invalid/float/exp-dot-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-dot-02.toml") {
    std::vector<char> content = load_file("invalid/float/exp-dot-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-dot-03.toml") {
    std::vector<char> content = load_file("invalid/float/exp-dot-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-e-01.toml") {
    std::vector<char> content = load_file("invalid/float/exp-double-e-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-e-02.toml") {
    std::vector<char> content = load_file("invalid/float/exp-double-e-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-e-1.toml") {
    std::vector<char> content = load_file("invalid/float/exp-double-e-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-e-2.toml") {
    std::vector<char> content = load_file("invalid/float/exp-double-e-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-double-us.toml") {
    std::vector<char> content = load_file("invalid/float/exp-double-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-leading-us.toml") {
    std::vector<char> content = load_file("invalid/float/exp-leading-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-point-1.toml") {
    std::vector<char> content = load_file("invalid/float/exp-point-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-point-2.toml") {
    std::vector<char> content = load_file("invalid/float/exp-point-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-point-3.toml") {
    std::vector<char> content = load_file("invalid/float/exp-point-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us-01.toml") {
    std::vector<char> content = load_file("invalid/float/exp-trailing-us-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us-02.toml") {
    std::vector<char> content = load_file("invalid/float/exp-trailing-us-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us-1.toml") {
    std::vector<char> content = load_file("invalid/float/exp-trailing-us-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us-2.toml") {
    std::vector<char> content = load_file("invalid/float/exp-trailing-us-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/exp-trailing-us.toml") {
    std::vector<char> content = load_file("invalid/float/exp-trailing-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/inf-capital.toml") {
    std::vector<char> content = load_file("invalid/float/inf-capital.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-01.toml") {
    std::vector<char> content = load_file("invalid/float/inf-incomplete-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-02.toml") {
    std::vector<char> content = load_file("invalid/float/inf-incomplete-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-03.toml") {
    std::vector<char> content = load_file("invalid/float/inf-incomplete-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-1.toml") {
    std::vector<char> content = load_file("invalid/float/inf-incomplete-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-2.toml") {
    std::vector<char> content = load_file("invalid/float/inf-incomplete-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/inf-incomplete-3.toml") {
    std::vector<char> content = load_file("invalid/float/inf-incomplete-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/inf_underscore.toml") {
    std::vector<char> content = load_file("invalid/float/inf_underscore.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-dot-neg.toml") {
    std::vector<char> content = load_file("invalid/float/leading-dot-neg.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-dot-plus.toml") {
    std::vector<char> content = load_file("invalid/float/leading-dot-plus.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-dot.toml") {
    std::vector<char> content = load_file("invalid/float/leading-dot.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-point-neg.toml") {
    std::vector<char> content = load_file("invalid/float/leading-point-neg.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-point-plus.toml") {
    std::vector<char> content = load_file("invalid/float/leading-point-plus.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-point.toml") {
    std::vector<char> content = load_file("invalid/float/leading-point.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-us.toml") {
    std::vector<char> content = load_file("invalid/float/leading-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-zero-neg.toml") {
    std::vector<char> content = load_file("invalid/float/leading-zero-neg.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-zero-plus.toml") {
    std::vector<char> content = load_file("invalid/float/leading-zero-plus.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/leading-zero.toml") {
    std::vector<char> content = load_file("invalid/float/leading-zero.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/nan-capital.toml") {
    std::vector<char> content = load_file("invalid/float/nan-capital.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-01.toml") {
    std::vector<char> content = load_file("invalid/float/nan-incomplete-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-02.toml") {
    std::vector<char> content = load_file("invalid/float/nan-incomplete-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-03.toml") {
    std::vector<char> content = load_file("invalid/float/nan-incomplete-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-1.toml") {
    std::vector<char> content = load_file("invalid/float/nan-incomplete-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-2.toml") {
    std::vector<char> content = load_file("invalid/float/nan-incomplete-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/nan-incomplete-3.toml") {
    std::vector<char> content = load_file("invalid/float/nan-incomplete-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/nan_underscore.toml") {
    std::vector<char> content = load_file("invalid/float/nan_underscore.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-dot-01.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-dot-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-dot-02.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-dot-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-dot-min.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-dot-min.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-dot-plus.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-dot-plus.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-exp-minus.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-exp-minus.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-exp-plus.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-exp-plus.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-exp-point.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-exp-point.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-exp.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-exp.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-point-min.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-point-min.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-point-plus.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-point-plus.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-point.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-point.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-us-exp-01.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-us-exp-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-us-exp-02.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-us-exp-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/trailing-us.toml") {
    std::vector<char> content = load_file("invalid/float/trailing-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/us-after-dot.toml") {
    std::vector<char> content = load_file("invalid/float/us-after-dot.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/us-after-point.toml") {
    std::vector<char> content = load_file("invalid/float/us-after-point.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/us-before-dot.toml") {
    std::vector<char> content = load_file("invalid/float/us-before-dot.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/float/us-before-point.toml") {
    std::vector<char> content = load_file("invalid/float/us-before-point.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

