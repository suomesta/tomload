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

TEST_CASE("invalid/inline-table/bad-key-syntax.toml") {
    std::string content = load_file("invalid/inline-table/bad-key-syntax.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/double-comma.toml") {
    std::string content = load_file("invalid/inline-table/double-comma.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/duplicate-key-01.toml") {
    std::string content = load_file("invalid/inline-table/duplicate-key-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/duplicate-key-02.toml") {
    std::string content = load_file("invalid/inline-table/duplicate-key-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/duplicate-key-03.toml") {
    std::string content = load_file("invalid/inline-table/duplicate-key-03.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/duplicate-key-04.toml") {
    std::string content = load_file("invalid/inline-table/duplicate-key-04.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/empty-01.toml") {
    std::string content = load_file("invalid/inline-table/empty-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/empty-02.toml") {
    std::string content = load_file("invalid/inline-table/empty-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/empty-03.toml") {
    std::string content = load_file("invalid/inline-table/empty-03.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/linebreak-01.toml") {
    std::string content = load_file("invalid/inline-table/linebreak-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/linebreak-02.toml") {
    std::string content = load_file("invalid/inline-table/linebreak-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/linebreak-03.toml") {
    std::string content = load_file("invalid/inline-table/linebreak-03.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/linebreak-04.toml") {
    std::string content = load_file("invalid/inline-table/linebreak-04.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/no-close-01.toml") {
    std::string content = load_file("invalid/inline-table/no-close-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/no-close-02.toml") {
    std::string content = load_file("invalid/inline-table/no-close-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/no-comma-01.toml") {
    std::string content = load_file("invalid/inline-table/no-comma-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/no-comma-02.toml") {
    std::string content = load_file("invalid/inline-table/no-comma-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-01.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-01.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-02.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-02.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-03.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-03.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-05.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-05.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-06.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-06.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-07.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-07.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-08.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-08.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-09.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-09.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/overwrite-10.toml") {
    std::string content = load_file("invalid/inline-table/overwrite-10.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

TEST_CASE("invalid/inline-table/trailing-comma.toml") {
    std::string content = load_file("invalid/inline-table/trailing-comma.toml");

    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);
}

