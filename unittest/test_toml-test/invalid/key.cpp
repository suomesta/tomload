// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

// This file is generated automatically. Do not modify.

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <doctest/doctest.h>
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

TEST_CASE("invalid/key/after-table.toml") {
    std::string content = load_file("invalid/key/after-table.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/after-value.toml") {
    std::string content = load_file("invalid/key/after-value.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/bare-invalid-character-01.toml") {
    std::string content = load_file("invalid/key/bare-invalid-character-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/bare-invalid-character-02.toml") {
    std::string content = load_file("invalid/key/bare-invalid-character-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/dot.toml") {
    std::string content = load_file("invalid/key/dot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/dotdot.toml") {
    std::string content = load_file("invalid/key/dotdot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/dotted-redefine-table-01.toml") {
    std::string content = load_file("invalid/key/dotted-redefine-table-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/dotted-redefine-table-02.toml") {
    std::string content = load_file("invalid/key/dotted-redefine-table-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/duplicate-keys-01.toml") {
    std::string content = load_file("invalid/key/duplicate-keys-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/duplicate-keys-02.toml") {
    std::string content = load_file("invalid/key/duplicate-keys-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/duplicate-keys-03.toml") {
    std::string content = load_file("invalid/key/duplicate-keys-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/duplicate-keys-04.toml") {
    std::string content = load_file("invalid/key/duplicate-keys-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/duplicate-keys-05.toml") {
    std::string content = load_file("invalid/key/duplicate-keys-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/duplicate-keys-06.toml") {
    std::string content = load_file("invalid/key/duplicate-keys-06.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/duplicate-keys-07.toml") {
    std::string content = load_file("invalid/key/duplicate-keys-07.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/empty.toml") {
    std::string content = load_file("invalid/key/empty.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/end-in-escape.toml") {
    std::string content = load_file("invalid/key/end-in-escape.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/escape.toml") {
    std::string content = load_file("invalid/key/escape.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/hash.toml") {
    std::string content = load_file("invalid/key/hash.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/multiline-key-01.toml") {
    std::string content = load_file("invalid/key/multiline-key-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/multiline-key-02.toml") {
    std::string content = load_file("invalid/key/multiline-key-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/multiline-key-03.toml") {
    std::string content = load_file("invalid/key/multiline-key-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/multiline-key-04.toml") {
    std::string content = load_file("invalid/key/multiline-key-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/newline-01.toml") {
    std::string content = load_file("invalid/key/newline-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/newline-02.toml") {
    std::string content = load_file("invalid/key/newline-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/newline-03.toml") {
    std::string content = load_file("invalid/key/newline-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/newline-04.toml") {
    std::string content = load_file("invalid/key/newline-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/newline-05.toml") {
    std::string content = load_file("invalid/key/newline-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/newline-06.toml") {
    std::string content = load_file("invalid/key/newline-06.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/no-eol-01.toml") {
    std::string content = load_file("invalid/key/no-eol-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/no-eol-02.toml") {
    std::string content = load_file("invalid/key/no-eol-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/no-eol-03.toml") {
    std::string content = load_file("invalid/key/no-eol-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/no-eol-05.toml") {
    std::string content = load_file("invalid/key/no-eol-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/no-eol-06.toml") {
    std::string content = load_file("invalid/key/no-eol-06.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/no-eol-07.toml") {
    std::string content = load_file("invalid/key/no-eol-07.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/only-float.toml") {
    std::string content = load_file("invalid/key/only-float.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/only-int.toml") {
    std::string content = load_file("invalid/key/only-int.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/only-str.toml") {
    std::string content = load_file("invalid/key/only-str.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/open-bracket.toml") {
    std::string content = load_file("invalid/key/open-bracket.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/partial-quoted.toml") {
    std::string content = load_file("invalid/key/partial-quoted.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/quoted-unclosed-01.toml") {
    std::string content = load_file("invalid/key/quoted-unclosed-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/quoted-unclosed-02.toml") {
    std::string content = load_file("invalid/key/quoted-unclosed-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/single-open-bracket.toml") {
    std::string content = load_file("invalid/key/single-open-bracket.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/space.toml") {
    std::string content = load_file("invalid/key/space.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/special-character.toml") {
    std::string content = load_file("invalid/key/special-character.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/start-bracket.toml") {
    std::string content = load_file("invalid/key/start-bracket.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/start-dot.toml") {
    std::string content = load_file("invalid/key/start-dot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/two-equals-01.toml") {
    std::string content = load_file("invalid/key/two-equals-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/two-equals-02.toml") {
    std::string content = load_file("invalid/key/two-equals-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/two-equals-03.toml") {
    std::string content = load_file("invalid/key/two-equals-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/without-value-01.toml") {
    std::string content = load_file("invalid/key/without-value-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/without-value-02.toml") {
    std::string content = load_file("invalid/key/without-value-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/without-value-03.toml") {
    std::string content = load_file("invalid/key/without-value-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/without-value-04.toml") {
    std::string content = load_file("invalid/key/without-value-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/without-value-05.toml") {
    std::string content = load_file("invalid/key/without-value-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/without-value-06.toml") {
    std::string content = load_file("invalid/key/without-value-06.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/key/without-value-07.toml") {
    std::string content = load_file("invalid/key/without-value-07.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

