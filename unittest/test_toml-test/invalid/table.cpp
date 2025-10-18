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

using tomload::item_t;
using tomload::view_t;

TEST_CASE("invalid/table/append-with-dotted-keys-01.toml") {
    std::vector<char> content = load_file("invalid/table/append-with-dotted-keys-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-02.toml") {
    std::vector<char> content = load_file("invalid/table/append-with-dotted-keys-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-04.toml") {
    std::vector<char> content = load_file("invalid/table/append-with-dotted-keys-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-05.toml") {
    std::vector<char> content = load_file("invalid/table/append-with-dotted-keys-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-06.toml") {
    std::vector<char> content = load_file("invalid/table/append-with-dotted-keys-06.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/append-with-dotted-keys-07.toml") {
    std::vector<char> content = load_file("invalid/table/append-with-dotted-keys-07.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/bare-invalid-character-01.toml") {
    std::vector<char> content = load_file("invalid/table/bare-invalid-character-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/bare-invalid-character-02.toml") {
    std::vector<char> content = load_file("invalid/table/bare-invalid-character-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/dot.toml") {
    std::vector<char> content = load_file("invalid/table/dot.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/dotdot.toml") {
    std::vector<char> content = load_file("invalid/table/dotdot.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-01.toml") {
    std::vector<char> content = load_file("invalid/table/duplicate-key-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-02.toml") {
    std::vector<char> content = load_file("invalid/table/duplicate-key-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-04.toml") {
    std::vector<char> content = load_file("invalid/table/duplicate-key-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-05.toml") {
    std::vector<char> content = load_file("invalid/table/duplicate-key-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-08.toml") {
    std::vector<char> content = load_file("invalid/table/duplicate-key-08.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/duplicate-key-09.toml") {
    std::vector<char> content = load_file("invalid/table/duplicate-key-09.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/empty-implicit-table.toml") {
    std::vector<char> content = load_file("invalid/table/empty-implicit-table.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/empty.toml") {
    std::vector<char> content = load_file("invalid/table/empty.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/equals-sign.toml") {
    std::vector<char> content = load_file("invalid/table/equals-sign.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/llbrace.toml") {
    std::vector<char> content = load_file("invalid/table/llbrace.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/multiline-key-01.toml") {
    std::vector<char> content = load_file("invalid/table/multiline-key-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/multiline-key-02.toml") {
    std::vector<char> content = load_file("invalid/table/multiline-key-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/nested-brackets-close.toml") {
    std::vector<char> content = load_file("invalid/table/nested-brackets-close.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/nested-brackets-open.toml") {
    std::vector<char> content = load_file("invalid/table/nested-brackets-open.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/newline-01.toml") {
    std::vector<char> content = load_file("invalid/table/newline-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/newline-02.toml") {
    std::vector<char> content = load_file("invalid/table/newline-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/newline-03.toml") {
    std::vector<char> content = load_file("invalid/table/newline-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/newline-04.toml") {
    std::vector<char> content = load_file("invalid/table/newline-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/newline-05.toml") {
    std::vector<char> content = load_file("invalid/table/newline-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-01.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-02.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-03.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-04.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-05.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-06.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-06.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-07.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-07.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-08.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-08.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/no-close-09.toml") {
    std::vector<char> content = load_file("invalid/table/no-close-09.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/overwrite-with-deep-table.toml") {
    std::vector<char> content = load_file("invalid/table/overwrite-with-deep-table.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/redefine-01.toml") {
    std::vector<char> content = load_file("invalid/table/redefine-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/redefine-02.toml") {
    std::vector<char> content = load_file("invalid/table/redefine-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/redefine-03.toml") {
    std::vector<char> content = load_file("invalid/table/redefine-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/super-twice.toml") {
    std::vector<char> content = load_file("invalid/table/super-twice.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/text-after-table.toml") {
    std::vector<char> content = load_file("invalid/table/text-after-table.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/trailing-dot.toml") {
    std::vector<char> content = load_file("invalid/table/trailing-dot.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/whitespace.toml") {
    std::vector<char> content = load_file("invalid/table/whitespace.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

TEST_CASE("invalid/table/with-pound.toml") {
    std::vector<char> content = load_file("invalid/table/with-pound.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, tomload::parse_error&);
}

