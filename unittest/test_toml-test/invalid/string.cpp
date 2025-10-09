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

TEST_CASE("invalid/string/bad-byte-escape.toml") {
    std::vector<char> content = load_file("invalid/string/bad-byte-escape.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-concat.toml") {
    std::vector<char> content = load_file("invalid/string/bad-concat.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-escape-01.toml") {
    std::vector<char> content = load_file("invalid/string/bad-escape-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-escape-02.toml") {
    std::vector<char> content = load_file("invalid/string/bad-escape-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-escape-03.toml") {
    std::vector<char> content = load_file("invalid/string/bad-escape-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-escape-04.toml") {
    std::vector<char> content = load_file("invalid/string/bad-escape-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-escape-05.toml") {
    std::vector<char> content = load_file("invalid/string/bad-escape-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-01.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-02.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-03.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-04.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-05.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-1.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-2.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-3.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-hex-esc-4.toml") {
    std::vector<char> content = load_file("invalid/string/bad-hex-esc-4.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-multiline.toml") {
    std::vector<char> content = load_file("invalid/string/bad-multiline.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-slash-escape.toml") {
    std::vector<char> content = load_file("invalid/string/bad-slash-escape.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-01.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-02.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-03.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-04.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-05.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-06.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-06.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-07.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-07.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-1.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-2.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-3.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-4.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-4.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-5.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-5.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-6.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-6.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-7.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-7.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-ml-1.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-ml-1.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-ml-2.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-ml-2.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-ml-3.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-ml-3.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-ml-4.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-ml-4.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-ml-5.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-ml-5.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-ml-6.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-ml-6.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/bad-uni-esc-ml-7.toml") {
    std::vector<char> content = load_file("invalid/string/bad-uni-esc-ml-7.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/basic-byte-escapes.toml") {
    std::vector<char> content = load_file("invalid/string/basic-byte-escapes.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/basic-multiline-out-of-range-unicode-escape-01.toml") {
    std::vector<char> content = load_file("invalid/string/basic-multiline-out-of-range-unicode-escape-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/basic-multiline-out-of-range-unicode-escape-02.toml") {
    std::vector<char> content = load_file("invalid/string/basic-multiline-out-of-range-unicode-escape-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/basic-multiline-quotes.toml") {
    std::vector<char> content = load_file("invalid/string/basic-multiline-quotes.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/basic-multiline-unknown-escape.toml") {
    std::vector<char> content = load_file("invalid/string/basic-multiline-unknown-escape.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/basic-out-of-range-unicode-escape-01.toml") {
    std::vector<char> content = load_file("invalid/string/basic-out-of-range-unicode-escape-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/basic-out-of-range-unicode-escape-02.toml") {
    std::vector<char> content = load_file("invalid/string/basic-out-of-range-unicode-escape-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/basic-unknown-escape.toml") {
    std::vector<char> content = load_file("invalid/string/basic-unknown-escape.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/literal-multiline-quotes-01.toml") {
    std::vector<char> content = load_file("invalid/string/literal-multiline-quotes-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/literal-multiline-quotes-02.toml") {
    std::vector<char> content = load_file("invalid/string/literal-multiline-quotes-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/missing-quotes-array.toml") {
    std::vector<char> content = load_file("invalid/string/missing-quotes-array.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/missing-quotes-inline-table.toml") {
    std::vector<char> content = load_file("invalid/string/missing-quotes-inline-table.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/missing-quotes.toml") {
    std::vector<char> content = load_file("invalid/string/missing-quotes.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-bad-escape-01.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-bad-escape-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-bad-escape-02.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-bad-escape-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-bad-escape-03.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-bad-escape-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-bad-escape-04.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-bad-escape-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-escape-space-01.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-escape-space-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-escape-space-02.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-escape-space-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-lit-no-close-01.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-lit-no-close-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-lit-no-close-02.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-lit-no-close-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-lit-no-close-03.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-lit-no-close-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-lit-no-close-04.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-lit-no-close-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-no-close-01.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-no-close-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-no-close-02.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-no-close-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-no-close-03.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-no-close-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-no-close-04.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-no-close-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-no-close-05.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-no-close-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/multiline-quotes-01.toml") {
    std::vector<char> content = load_file("invalid/string/multiline-quotes-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-01.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-02.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-03.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-04.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-05.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-06.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-06.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-07.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-07.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-08.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-08.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-09.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-09.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-close-10.toml") {
    std::vector<char> content = load_file("invalid/string/no-close-10.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-open-01.toml") {
    std::vector<char> content = load_file("invalid/string/no-open-01.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-open-02.toml") {
    std::vector<char> content = load_file("invalid/string/no-open-02.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-open-03.toml") {
    std::vector<char> content = load_file("invalid/string/no-open-03.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-open-04.toml") {
    std::vector<char> content = load_file("invalid/string/no-open-04.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-open-05.toml") {
    std::vector<char> content = load_file("invalid/string/no-open-05.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-open-06.toml") {
    std::vector<char> content = load_file("invalid/string/no-open-06.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-open-07.toml") {
    std::vector<char> content = load_file("invalid/string/no-open-07.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/no-open-08.toml") {
    std::vector<char> content = load_file("invalid/string/no-open-08.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/text-after-string.toml") {
    std::vector<char> content = load_file("invalid/string/text-after-string.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

TEST_CASE("invalid/string/wrong-close.toml") {
    std::vector<char> content = load_file("invalid/string/wrong-close.toml");
    view_t view{content.data(), content.size()};

    CHECK_THROWS_AS(item_t{view}, parse_error&);
}

