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

TEST_CASE("valid/string/basic-escape-01.toml") {
    std::vector<char> content = load_file("valid/string/basic-escape-01.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"test"].is_string() == true);
    CHECK(t[u8"test"].get_string() == u8"\"one\"");
}

TEST_CASE("valid/string/basic-escape-02.toml") {
    std::vector<char> content = load_file("valid/string/basic-escape-02.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"test"].is_string() == true);
    CHECK(t[u8"test"].get_string() == u8"\\\"one");
}

TEST_CASE("valid/string/basic-escape-03.toml") {
    std::vector<char> content = load_file("valid/string/basic-escape-03.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"test"].is_string() == true);
    CHECK(t[u8"test"].get_string() == u8"\\\\\\\\\"one");
}

TEST_CASE("valid/string/empty.toml") {
    std::vector<char> content = load_file("valid/string/empty.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"answer"].is_string() == true);
    CHECK(t[u8"answer"].get_string() == u8"");
}

TEST_CASE("valid/string/ends-in-whitespace-escape.toml") {
    std::vector<char> content = load_file("valid/string/ends-in-whitespace-escape.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"beee"].is_string() == true);
    CHECK(t[u8"beee"].get_string() == u8"heeee\ngeeee");
}

TEST_CASE("valid/string/escape-tricky.toml") {
    std::vector<char> content = load_file("valid/string/escape-tricky.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t[u8"end_esc"].is_string() == true);
    CHECK(t[u8"end_esc"].get_string() == u8"String does not end here\" but ends here\\");
    CHECK(t[u8"lit_end_esc"].is_string() == true);
    CHECK(t[u8"lit_end_esc"].get_string() == u8"String ends here\\");
    CHECK(t[u8"multiline_unicode"].is_string() == true);
    CHECK(t[u8"multiline_unicode"].get_string() == u8" ");
    CHECK(t[u8"multiline_not_unicode"].is_string() == true);
    CHECK(t[u8"multiline_not_unicode"].get_string() == u8"\\u0041");
    CHECK(t[u8"multiline_end_esc"].is_string() == true);
    CHECK(t[u8"multiline_end_esc"].get_string() == u8"When will it end? \"\"\"...\"\"\" should be here\"");
    CHECK(t[u8"lit_multiline_not_unicode"].is_string() == true);
    CHECK(t[u8"lit_multiline_not_unicode"].get_string() == u8"\\u007f");
    CHECK(t[u8"lit_multiline_end"].is_string() == true);
    CHECK(t[u8"lit_multiline_end"].get_string() == u8"There is no escape\\");
}

TEST_CASE("valid/string/escaped-escape.toml") {
    std::vector<char> content = load_file("valid/string/escaped-escape.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"answer"].is_string() == true);
    CHECK(t[u8"answer"].get_string() == u8"\\x64");
}

TEST_CASE("valid/string/escapes.toml") {
    std::vector<char> content = load_file("valid/string/escapes.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 13);
    CHECK(t[u8"backspace"].is_string() == true);
    CHECK(t[u8"backspace"].get_string() == u8"|\b.");
    CHECK(t[u8"tab"].is_string() == true);
    CHECK(t[u8"tab"].get_string() == u8"|\t.");
    CHECK(t[u8"newline"].is_string() == true);
    CHECK(t[u8"newline"].get_string() == u8"|\n.");
    CHECK(t[u8"formfeed"].is_string() == true);
    CHECK(t[u8"formfeed"].get_string() == u8"|.");
    CHECK(t[u8"carriage"].is_string() == true);
    CHECK(t[u8"carriage"].get_string() == u8"|\r.");
    CHECK(t[u8"quote"].is_string() == true);
    CHECK(t[u8"quote"].get_string() == u8"|\".");
    CHECK(t[u8"backslash"].is_string() == true);
    CHECK(t[u8"backslash"].get_string() == u8"|\\.");
    CHECK(t[u8"delete"].is_string() == true);
    CHECK(t[u8"delete"].get_string() == u8"|.");
    CHECK(t[u8"unitseparator"].is_string() == true);
    CHECK(t[u8"unitseparator"].get_string() == u8"|.");
    CHECK(t[u8"notunicode1"].is_string() == true);
    CHECK(t[u8"notunicode1"].get_string() == u8"|\\u.");
    CHECK(t[u8"notunicode2"].is_string() == true);
    CHECK(t[u8"notunicode2"].get_string() == u8"|\\u.");
    CHECK(t[u8"notunicode3"].is_string() == true);
    CHECK(t[u8"notunicode3"].get_string() == u8"|\\u0075.");
    CHECK(t[u8"notunicode4"].is_string() == true);
    CHECK(t[u8"notunicode4"].get_string() == u8"|\\u.");
}

TEST_CASE("valid/string/multibyte-escape.toml") {
    std::vector<char> content = load_file("valid/string/multibyte-escape.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"basic-1"].is_string() == true);
    CHECK(t[u8"basic-1"].get_string() == u8"ɑ € 𐫱 ɑ€𐫱");
    CHECK(t[u8"ml-basic-1"].is_string() == true);
    CHECK(t[u8"ml-basic-1"].get_string() == u8"ɑ € 𐫱 ɑ€𐫱");
    CHECK(t[u8"basic-2"].is_string() == true);
    CHECK(t[u8"basic-2"].get_string() == u8"ɑ € 𐫱 ɑ€𐫱");
    CHECK(t[u8"ml-basic-2"].is_string() == true);
    CHECK(t[u8"ml-basic-2"].get_string() == u8"ɑ € 𐫱 ɑ€𐫱");
}

TEST_CASE("valid/string/multibyte.toml") {
    std::vector<char> content = load_file("valid/string/multibyte.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"basic"].is_string() == true);
    CHECK(t[u8"basic"].get_string() == u8"ɑ € 𐫱 ɑ€𐫱");
    CHECK(t[u8"raw"].is_string() == true);
    CHECK(t[u8"raw"].get_string() == u8"ɑ € 𐫱 ɑ€𐫱");
    CHECK(t[u8"ml-basic"].is_string() == true);
    CHECK(t[u8"ml-basic"].get_string() == u8"ɑ € 𐫱 ɑ€𐫱");
    CHECK(t[u8"ml-raw"].is_string() == true);
    CHECK(t[u8"ml-raw"].get_string() == u8"ɑ € 𐫱 ɑ€𐫱");
}

TEST_CASE("valid/string/multiline-empty.toml") {
    std::vector<char> content = load_file("valid/string/multiline-empty.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"empty-1"].is_string() == true);
    CHECK(t[u8"empty-1"].get_string() == u8"");
    CHECK(t[u8"empty-2"].is_string() == true);
    CHECK(t[u8"empty-2"].get_string() == u8"");
    CHECK(t[u8"empty-3"].is_string() == true);
    CHECK(t[u8"empty-3"].get_string() == u8"");
    CHECK(t[u8"empty-4"].is_string() == true);
    CHECK(t[u8"empty-4"].get_string() == u8"");
}

TEST_CASE("valid/string/multiline-escaped-crlf.toml") {
    std::vector<char> content = load_file("valid/string/multiline-escaped-crlf.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"0"].is_string() == true);
    CHECK(t[u8"0"].get_string() == u8"");
}

TEST_CASE("valid/string/multiline-quotes.toml") {
    std::vector<char> content = load_file("valid/string/multiline-quotes.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 13);
    CHECK(t[u8"lit_one"].is_string() == true);
    CHECK(t[u8"lit_one"].get_string() == u8"'one quote'");
    CHECK(t[u8"lit_two"].is_string() == true);
    CHECK(t[u8"lit_two"].get_string() == u8"''two quotes''");
    CHECK(t[u8"lit_one_space"].is_string() == true);
    CHECK(t[u8"lit_one_space"].get_string() == u8" 'one quote' ");
    CHECK(t[u8"lit_two_space"].is_string() == true);
    CHECK(t[u8"lit_two_space"].get_string() == u8" ''two quotes'' ");
    CHECK(t[u8"one"].is_string() == true);
    CHECK(t[u8"one"].get_string() == u8"\"one quote\"");
    CHECK(t[u8"two"].is_string() == true);
    CHECK(t[u8"two"].get_string() == u8"\"\"two quotes\"\"");
    CHECK(t[u8"one_space"].is_string() == true);
    CHECK(t[u8"one_space"].get_string() == u8" \"one quote\" ");
    CHECK(t[u8"two_space"].is_string() == true);
    CHECK(t[u8"two_space"].get_string() == u8" \"\"two quotes\"\" ");
    CHECK(t[u8"mismatch1"].is_string() == true);
    CHECK(t[u8"mismatch1"].get_string() == u8"aaa'''bbb");
    CHECK(t[u8"mismatch2"].is_string() == true);
    CHECK(t[u8"mismatch2"].get_string() == u8"aaa\"\"\"bbb");
    CHECK(t[u8"escaped"].is_string() == true);
    CHECK(t[u8"escaped"].get_string() == u8"lol\"\"\"");
    CHECK(t[u8"five-quotes"].is_string() == true);
    CHECK(t[u8"five-quotes"].get_string() == u8"Closing with five quotes\n\"\"");
    CHECK(t[u8"four-quotes"].is_string() == true);
    CHECK(t[u8"four-quotes"].get_string() == u8"Closing with four quotes\n\"");
}

TEST_CASE("valid/string/multiline.toml") {
    std::vector<char> content = load_file("valid/string/multiline.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 9);
    CHECK(t[u8"equivalent_one"].is_string() == true);
    CHECK(t[u8"equivalent_one"].get_string() == u8"The quick brown fox jumps over the lazy dog.");
    CHECK(t[u8"equivalent_two"].is_string() == true);
    CHECK(t[u8"equivalent_two"].get_string() == u8"The quick brown fox jumps over the lazy dog.");
    CHECK(t[u8"equivalent_three"].is_string() == true);
    CHECK(t[u8"equivalent_three"].get_string() == u8"The quick brown fox jumps over the lazy dog.");
    CHECK(t[u8"whitespace-after-bs"].is_string() == true);
    CHECK(t[u8"whitespace-after-bs"].get_string() == u8"The quick brown fox jumps over the lazy dog.");
    CHECK(t[u8"no-space"].is_string() == true);
    CHECK(t[u8"no-space"].get_string() == u8"ab");
    CHECK(t[u8"keep-ws-before"].is_string() == true);
    CHECK(t[u8"keep-ws-before"].get_string() == u8"a   \tb");
    CHECK(t[u8"escape-bs-1"].is_string() == true);
    CHECK(t[u8"escape-bs-1"].get_string() == u8"a \\\nb");
    CHECK(t[u8"escape-bs-2"].is_string() == true);
    CHECK(t[u8"escape-bs-2"].get_string() == u8"a \\b");
    CHECK(t[u8"escape-bs-3"].is_string() == true);
    CHECK(t[u8"escape-bs-3"].get_string() == u8"a \\\\\n  b");
}

TEST_CASE("valid/string/nl.toml") {
    std::vector<char> content = load_file("valid/string/nl.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"nl_mid"].is_string() == true);
    CHECK(t[u8"nl_mid"].get_string() == u8"val\nue");
    CHECK(t[u8"nl_end"].is_string() == true);
    CHECK(t[u8"nl_end"].get_string() == u8"value\n");
    CHECK(t[u8"lit_nl_end"].is_string() == true);
    CHECK(t[u8"lit_nl_end"].get_string() == u8"value\\n");
    CHECK(t[u8"lit_nl_mid"].is_string() == true);
    CHECK(t[u8"lit_nl_mid"].get_string() == u8"val\\nue");
    CHECK(t[u8"lit_nl_uni"].is_string() == true);
    CHECK(t[u8"lit_nl_uni"].get_string() == u8"val\\ue");
}

TEST_CASE("valid/string/quoted-unicode.toml") {
    std::vector<char> content = load_file("valid/string/quoted-unicode.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"escaped_string"].is_string() == true);
    CHECK(t[u8"escaped_string"].get_string() == u8"" + std::string(1, '\0') + u8" \b  A   ÿ ퟿  ￿ 𐀀 􏿿");
    CHECK(t[u8"not_escaped_string"].is_string() == true);
    CHECK(t[u8"not_escaped_string"].get_string() == u8"\\u0000 \\u0008 \\u000c \\U00000041 \\u007f \\u0080 \\u00ff \\ud7ff \\ue000 \\uffff \\U00010000 \\U0010ffff");
    CHECK(t[u8"basic_string"].is_string() == true);
    CHECK(t[u8"basic_string"].get_string() == u8"~  ÿ ퟿  ￿ 𐀀 􏿿");
    CHECK(t[u8"literal_string"].is_string() == true);
    CHECK(t[u8"literal_string"].get_string() == u8"~  ÿ ퟿  ￿ 𐀀 􏿿");
}

TEST_CASE("valid/string/raw-empty.toml") {
    std::vector<char> content = load_file("valid/string/raw-empty.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"empty"].is_string() == true);
    CHECK(t[u8"empty"].get_string() == u8"");
}

TEST_CASE("valid/string/raw-multiline.toml") {
    std::vector<char> content = load_file("valid/string/raw-multiline.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"oneline"].is_string() == true);
    CHECK(t[u8"oneline"].get_string() == u8"This string has a ' quote character.");
    CHECK(t[u8"firstnl"].is_string() == true);
    CHECK(t[u8"firstnl"].get_string() == u8"This string has a ' quote character.");
    CHECK(t[u8"multiline"].is_string() == true);
    CHECK(t[u8"multiline"].get_string() == u8"This string\nhas ' a quote character\nand more than\none newline\nin it.");
    CHECK(t[u8"multiline_with_tab"].is_string() == true);
    CHECK(t[u8"multiline_with_tab"].get_string() == u8"First line\n\t Followed by a tab");
    CHECK(t[u8"this-str-has-apostrophes"].is_string() == true);
    CHECK(t[u8"this-str-has-apostrophes"].get_string() == u8"' there's one already\n'' two more\n''");
}

TEST_CASE("valid/string/raw.toml") {
    std::vector<char> content = load_file("valid/string/raw.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 8);
    CHECK(t[u8"backspace"].is_string() == true);
    CHECK(t[u8"backspace"].get_string() == u8"This string has a \\b backspace character.");
    CHECK(t[u8"tab"].is_string() == true);
    CHECK(t[u8"tab"].get_string() == u8"This string has a \\t tab character.");
    CHECK(t[u8"unescaped_tab"].is_string() == true);
    CHECK(t[u8"unescaped_tab"].get_string() == u8"This string has an \t unescaped tab character.");
    CHECK(t[u8"newline"].is_string() == true);
    CHECK(t[u8"newline"].get_string() == u8"This string has a \\n new line character.");
    CHECK(t[u8"formfeed"].is_string() == true);
    CHECK(t[u8"formfeed"].get_string() == u8"This string has a \\f form feed character.");
    CHECK(t[u8"carriage"].is_string() == true);
    CHECK(t[u8"carriage"].get_string() == u8"This string has a \\r carriage return character.");
    CHECK(t[u8"slash"].is_string() == true);
    CHECK(t[u8"slash"].get_string() == u8"This string has a \\/ slash character.");
    CHECK(t[u8"backslash"].is_string() == true);
    CHECK(t[u8"backslash"].get_string() == u8"This string has a \\\\ backslash character.");
}

TEST_CASE("valid/string/simple.toml") {
    std::vector<char> content = load_file("valid/string/simple.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"answer"].is_string() == true);
    CHECK(t[u8"answer"].get_string() == u8"You are not drinking enough whisky.");
}

TEST_CASE("valid/string/start-mb.toml") {
    std::vector<char> content = load_file("valid/string/start-mb.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t[u8"s1"].is_string() == true);
    CHECK(t[u8"s1"].get_string() == u8"§");
    CHECK(t[u8"s2"].is_string() == true);
    CHECK(t[u8"s2"].get_string() == u8"§");
    CHECK(t[u8"s3"].is_string() == true);
    CHECK(t[u8"s3"].get_string() == u8"§");
    CHECK(t[u8"s4"].is_string() == true);
    CHECK(t[u8"s4"].get_string() == u8"§");
    CHECK(t[u8"s5"].is_string() == true);
    CHECK(t[u8"s5"].get_string() == u8"§");
    CHECK(t[u8"s6"].is_string() == true);
    CHECK(t[u8"s6"].get_string() == u8"§");
    CHECK(t[u8"s7"].is_string() == true);
    CHECK(t[u8"s7"].get_string() == u8"§");
}

TEST_CASE("valid/string/unicode-escape.toml") {
    std::vector<char> content = load_file("valid/string/unicode-escape.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 14);
    CHECK(t[u8"delta-1"].is_string() == true);
    CHECK(t[u8"delta-1"].get_string() == u8"δ");
    CHECK(t[u8"delta-2"].is_string() == true);
    CHECK(t[u8"delta-2"].get_string() == u8"δ");
    CHECK(t[u8"a"].is_string() == true);
    CHECK(t[u8"a"].get_string() == u8"a");
    CHECK(t[u8"b"].is_string() == true);
    CHECK(t[u8"b"].get_string() == u8"b");
    CHECK(t[u8"c"].is_string() == true);
    CHECK(t[u8"c"].get_string() == u8"c");
    CHECK(t[u8"null-1"].is_string() == true);
    CHECK(t[u8"null-1"].get_string() == u8"" + std::string(1, '\0') + u8"");
    CHECK(t[u8"null-2"].is_string() == true);
    CHECK(t[u8"null-2"].get_string() == u8"" + std::string(1, '\0') + u8"");
    CHECK(t[u8"ml-delta-1"].is_string() == true);
    CHECK(t[u8"ml-delta-1"].get_string() == u8"δ");
    CHECK(t[u8"ml-delta-2"].is_string() == true);
    CHECK(t[u8"ml-delta-2"].get_string() == u8"δ");
    CHECK(t[u8"ml-a"].is_string() == true);
    CHECK(t[u8"ml-a"].get_string() == u8"a");
    CHECK(t[u8"ml-b"].is_string() == true);
    CHECK(t[u8"ml-b"].get_string() == u8"b");
    CHECK(t[u8"ml-c"].is_string() == true);
    CHECK(t[u8"ml-c"].get_string() == u8"c");
    CHECK(t[u8"ml-null-1"].is_string() == true);
    CHECK(t[u8"ml-null-1"].get_string() == u8"" + std::string(1, '\0') + u8"");
    CHECK(t[u8"ml-null-2"].is_string() == true);
    CHECK(t[u8"ml-null-2"].get_string() == u8"" + std::string(1, '\0') + u8"");
}

TEST_CASE("valid/string/with-pound.toml") {
    std::vector<char> content = load_file("valid/string/with-pound.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"pound"].is_string() == true);
    CHECK(t[u8"pound"].get_string() == u8"We see no # comments here.");
    CHECK(t[u8"poundcomment"].is_string() == true);
    CHECK(t[u8"poundcomment"].get_string() == u8"But there are # some comments here.");
}

