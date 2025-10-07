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

TEST_CASE("invalid/table/append-with-dotted-keys-01.toml") {
    std::string content = load_file("invalid/table/append-with-dotted-keys-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-02.toml") {
    std::string content = load_file("invalid/table/append-with-dotted-keys-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-04.toml") {
    std::string content = load_file("invalid/table/append-with-dotted-keys-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-05.toml") {
    std::string content = load_file("invalid/table/append-with-dotted-keys-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-06.toml") {
    std::string content = load_file("invalid/table/append-with-dotted-keys-06.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-07.toml") {
    std::string content = load_file("invalid/table/append-with-dotted-keys-07.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/bare-invalid-character-01.toml") {
    std::string content = load_file("invalid/table/bare-invalid-character-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/bare-invalid-character-02.toml") {
    std::string content = load_file("invalid/table/bare-invalid-character-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/dot.toml") {
    std::string content = load_file("invalid/table/dot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/dotdot.toml") {
    std::string content = load_file("invalid/table/dotdot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-01.toml") {
    std::string content = load_file("invalid/table/duplicate-key-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-02.toml") {
    std::string content = load_file("invalid/table/duplicate-key-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-04.toml") {
    std::string content = load_file("invalid/table/duplicate-key-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-05.toml") {
    std::string content = load_file("invalid/table/duplicate-key-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-08.toml") {
    std::string content = load_file("invalid/table/duplicate-key-08.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-09.toml") {
    std::string content = load_file("invalid/table/duplicate-key-09.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/empty-implicit-table.toml") {
    std::string content = load_file("invalid/table/empty-implicit-table.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/empty.toml") {
    std::string content = load_file("invalid/table/empty.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/equals-sign.toml") {
    std::string content = load_file("invalid/table/equals-sign.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/llbrace.toml") {
    std::string content = load_file("invalid/table/llbrace.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/multiline-key-01.toml") {
    std::string content = load_file("invalid/table/multiline-key-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/multiline-key-02.toml") {
    std::string content = load_file("invalid/table/multiline-key-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/nested-brackets-close.toml") {
    std::string content = load_file("invalid/table/nested-brackets-close.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/nested-brackets-open.toml") {
    std::string content = load_file("invalid/table/nested-brackets-open.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/newline-01.toml") {
    std::string content = load_file("invalid/table/newline-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/newline-02.toml") {
    std::string content = load_file("invalid/table/newline-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/newline-03.toml") {
    std::string content = load_file("invalid/table/newline-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/newline-04.toml") {
    std::string content = load_file("invalid/table/newline-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/newline-05.toml") {
    std::string content = load_file("invalid/table/newline-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-01.toml") {
    std::string content = load_file("invalid/table/no-close-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-02.toml") {
    std::string content = load_file("invalid/table/no-close-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-03.toml") {
    std::string content = load_file("invalid/table/no-close-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-04.toml") {
    std::string content = load_file("invalid/table/no-close-04.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-05.toml") {
    std::string content = load_file("invalid/table/no-close-05.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-06.toml") {
    std::string content = load_file("invalid/table/no-close-06.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-07.toml") {
    std::string content = load_file("invalid/table/no-close-07.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-08.toml") {
    std::string content = load_file("invalid/table/no-close-08.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/no-close-09.toml") {
    std::string content = load_file("invalid/table/no-close-09.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/overwrite-with-deep-table.toml") {
    std::string content = load_file("invalid/table/overwrite-with-deep-table.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/redefine-01.toml") {
    std::string content = load_file("invalid/table/redefine-01.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/redefine-02.toml") {
    std::string content = load_file("invalid/table/redefine-02.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/redefine-03.toml") {
    std::string content = load_file("invalid/table/redefine-03.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/super-twice.toml") {
    std::string content = load_file("invalid/table/super-twice.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/text-after-table.toml") {
    std::string content = load_file("invalid/table/text-after-table.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/trailing-dot.toml") {
    std::string content = load_file("invalid/table/trailing-dot.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/whitespace.toml") {
    std::string content = load_file("invalid/table/whitespace.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

TEST_CASE("invalid/table/with-pound.toml") {
    std::string content = load_file("invalid/table/with-pound.toml");

    CHECK_THROWS_AS(item_t{content.c_str()}, parse_error&);
}

