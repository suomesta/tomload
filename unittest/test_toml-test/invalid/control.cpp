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

TEST_CASE("invalid/control/bare-cr.toml") {
    std::vector<char> content = load_file("invalid/control/bare-cr.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/bare-formfeed.toml") {
    std::vector<char> content = load_file("invalid/control/bare-formfeed.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/bare-null.toml") {
    std::vector<char> content = load_file("invalid/control/bare-null.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/bare-vertical-tab.toml") {
    std::vector<char> content = load_file("invalid/control/bare-vertical-tab.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/comment-cr.toml") {
    std::vector<char> content = load_file("invalid/control/comment-cr.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/comment-del.toml") {
    std::vector<char> content = load_file("invalid/control/comment-del.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/comment-ff.toml") {
    std::vector<char> content = load_file("invalid/control/comment-ff.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/comment-lf.toml") {
    std::vector<char> content = load_file("invalid/control/comment-lf.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/comment-null.toml") {
    std::vector<char> content = load_file("invalid/control/comment-null.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/comment-us.toml") {
    std::vector<char> content = load_file("invalid/control/comment-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/multi-cr.toml") {
    std::vector<char> content = load_file("invalid/control/multi-cr.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/multi-del.toml") {
    std::vector<char> content = load_file("invalid/control/multi-del.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/multi-lf.toml") {
    std::vector<char> content = load_file("invalid/control/multi-lf.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/multi-null.toml") {
    std::vector<char> content = load_file("invalid/control/multi-null.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/multi-us.toml") {
    std::vector<char> content = load_file("invalid/control/multi-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/only-ff.toml") {
    std::vector<char> content = load_file("invalid/control/only-ff.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/only-null.toml") {
    std::vector<char> content = load_file("invalid/control/only-null.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/only-vt.toml") {
    std::vector<char> content = load_file("invalid/control/only-vt.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawmulti-cr.toml") {
    std::vector<char> content = load_file("invalid/control/rawmulti-cr.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawmulti-del.toml") {
    std::vector<char> content = load_file("invalid/control/rawmulti-del.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawmulti-lf.toml") {
    std::vector<char> content = load_file("invalid/control/rawmulti-lf.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawmulti-null.toml") {
    std::vector<char> content = load_file("invalid/control/rawmulti-null.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawmulti-us.toml") {
    std::vector<char> content = load_file("invalid/control/rawmulti-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawstring-cr.toml") {
    std::vector<char> content = load_file("invalid/control/rawstring-cr.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawstring-del.toml") {
    std::vector<char> content = load_file("invalid/control/rawstring-del.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawstring-lf.toml") {
    std::vector<char> content = load_file("invalid/control/rawstring-lf.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawstring-null.toml") {
    std::vector<char> content = load_file("invalid/control/rawstring-null.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/rawstring-us.toml") {
    std::vector<char> content = load_file("invalid/control/rawstring-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/string-bs.toml") {
    std::vector<char> content = load_file("invalid/control/string-bs.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/string-cr.toml") {
    std::vector<char> content = load_file("invalid/control/string-cr.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/string-del.toml") {
    std::vector<char> content = load_file("invalid/control/string-del.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/string-lf.toml") {
    std::vector<char> content = load_file("invalid/control/string-lf.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/string-null.toml") {
    std::vector<char> content = load_file("invalid/control/string-null.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/control/string-us.toml") {
    std::vector<char> content = load_file("invalid/control/string-us.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

