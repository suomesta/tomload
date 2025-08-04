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

}  // namespace

using namespace tomload;

TEST_CASE("valid/string/basic-escape-01.toml") {
    std::string content = load_file("valid/string/basic-escape-01.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["test"].is_string() == true);
    CHECK(t["test"].get_string() == "\"one\"");
}

TEST_CASE("valid/string/basic-escape-02.toml") {
    std::string content = load_file("valid/string/basic-escape-02.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["test"].is_string() == true);
    CHECK(t["test"].get_string() == "\\\"one");
}

TEST_CASE("valid/string/basic-escape-03.toml") {
    std::string content = load_file("valid/string/basic-escape-03.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["test"].is_string() == true);
    CHECK(t["test"].get_string() == "\\\\\\\\\"one");
}

TEST_CASE("valid/string/empty.toml") {
    std::string content = load_file("valid/string/empty.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["answer"].is_string() == true);
    CHECK(t["answer"].get_string() == "");
}

TEST_CASE("valid/string/ends-in-whitespace-escape.toml") {
    std::string content = load_file("valid/string/ends-in-whitespace-escape.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["beee"].is_string() == true);
    CHECK(t["beee"].get_string() == "heeee\ngeeee");
}

TEST_CASE("valid/string/escape-tricky.toml") {
    std::string content = load_file("valid/string/escape-tricky.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t["end_esc"].is_string() == true);
    CHECK(t["end_esc"].get_string() == "String does not end here\" but ends here\\");
    CHECK(t["lit_end_esc"].is_string() == true);
    CHECK(t["lit_end_esc"].get_string() == "String ends here\\");
    CHECK(t["multiline_unicode"].is_string() == true);
    CHECK(t["multiline_unicode"].get_string() == " ");
    CHECK(t["multiline_not_unicode"].is_string() == true);
    CHECK(t["multiline_not_unicode"].get_string() == "\\u0041");
    CHECK(t["multiline_end_esc"].is_string() == true);
    CHECK(t["multiline_end_esc"].get_string() == "When will it end? \"\"\"...\"\"\" should be here\"");
    CHECK(t["lit_multiline_not_unicode"].is_string() == true);
    CHECK(t["lit_multiline_not_unicode"].get_string() == "\\u007f");
    CHECK(t["lit_multiline_end"].is_string() == true);
    CHECK(t["lit_multiline_end"].get_string() == "There is no escape\\");
}

TEST_CASE("valid/string/escaped-escape.toml") {
    std::string content = load_file("valid/string/escaped-escape.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["answer"].is_string() == true);
    CHECK(t["answer"].get_string() == "\\x64");
}

TEST_CASE("valid/string/escapes.toml") {
    std::string content = load_file("valid/string/escapes.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 13);
    CHECK(t["backspace"].is_string() == true);
    CHECK(t["backspace"].get_string() == "|\b.");
    CHECK(t["tab"].is_string() == true);
    CHECK(t["tab"].get_string() == "|\t.");
    CHECK(t["newline"].is_string() == true);
    CHECK(t["newline"].get_string() == "|\n.");
    CHECK(t["formfeed"].is_string() == true);
    CHECK(t["formfeed"].get_string() == "|.");
    CHECK(t["carriage"].is_string() == true);
    CHECK(t["carriage"].get_string() == "|\r.");
    CHECK(t["quote"].is_string() == true);
    CHECK(t["quote"].get_string() == "|\".");
    CHECK(t["backslash"].is_string() == true);
    CHECK(t["backslash"].get_string() == "|\\.");
    CHECK(t["delete"].is_string() == true);
    CHECK(t["delete"].get_string() == "|.");
    CHECK(t["unitseparator"].is_string() == true);
    CHECK(t["unitseparator"].get_string() == "|.");
    CHECK(t["notunicode1"].is_string() == true);
    CHECK(t["notunicode1"].get_string() == "|\\u.");
    CHECK(t["notunicode2"].is_string() == true);
    CHECK(t["notunicode2"].get_string() == "|\\u.");
    CHECK(t["notunicode3"].is_string() == true);
    CHECK(t["notunicode3"].get_string() == "|\\u0075.");
    CHECK(t["notunicode4"].is_string() == true);
    CHECK(t["notunicode4"].get_string() == "|\\u.");
}

TEST_CASE("valid/string/multibyte-escape.toml") {
    std::string content = load_file("valid/string/multibyte-escape.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["basic-1"].is_string() == true);
    CHECK(t["basic-1"].get_string() == "ɑ € 𐫱 ɑ€𐫱");
    CHECK(t["ml-basic-1"].is_string() == true);
    CHECK(t["ml-basic-1"].get_string() == "ɑ € 𐫱 ɑ€𐫱");
    CHECK(t["basic-2"].is_string() == true);
    CHECK(t["basic-2"].get_string() == "ɑ € 𐫱 ɑ€𐫱");
    CHECK(t["ml-basic-2"].is_string() == true);
    CHECK(t["ml-basic-2"].get_string() == "ɑ € 𐫱 ɑ€𐫱");
}

TEST_CASE("valid/string/multibyte.toml") {
    std::string content = load_file("valid/string/multibyte.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["basic"].is_string() == true);
    CHECK(t["basic"].get_string() == "ɑ € 𐫱 ɑ€𐫱");
    CHECK(t["raw"].is_string() == true);
    CHECK(t["raw"].get_string() == "ɑ € 𐫱 ɑ€𐫱");
    CHECK(t["ml-basic"].is_string() == true);
    CHECK(t["ml-basic"].get_string() == "ɑ € 𐫱 ɑ€𐫱");
    CHECK(t["ml-raw"].is_string() == true);
    CHECK(t["ml-raw"].get_string() == "ɑ € 𐫱 ɑ€𐫱");
}

TEST_CASE("valid/string/multiline-empty.toml") {
    std::string content = load_file("valid/string/multiline-empty.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["empty-1"].is_string() == true);
    CHECK(t["empty-1"].get_string() == "");
    CHECK(t["empty-2"].is_string() == true);
    CHECK(t["empty-2"].get_string() == "");
    CHECK(t["empty-3"].is_string() == true);
    CHECK(t["empty-3"].get_string() == "");
    CHECK(t["empty-4"].is_string() == true);
    CHECK(t["empty-4"].get_string() == "");
}

TEST_CASE("valid/string/multiline-escaped-crlf.toml") {
    std::string content = load_file("valid/string/multiline-escaped-crlf.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["0"].is_string() == true);
    CHECK(t["0"].get_string() == "");
}

TEST_CASE("valid/string/multiline-quotes.toml") {
    std::string content = load_file("valid/string/multiline-quotes.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 13);
    CHECK(t["lit_one"].is_string() == true);
    CHECK(t["lit_one"].get_string() == "'one quote'");
    CHECK(t["lit_two"].is_string() == true);
    CHECK(t["lit_two"].get_string() == "''two quotes''");
    CHECK(t["lit_one_space"].is_string() == true);
    CHECK(t["lit_one_space"].get_string() == " 'one quote' ");
    CHECK(t["lit_two_space"].is_string() == true);
    CHECK(t["lit_two_space"].get_string() == " ''two quotes'' ");
    CHECK(t["one"].is_string() == true);
    CHECK(t["one"].get_string() == "\"one quote\"");
    CHECK(t["two"].is_string() == true);
    CHECK(t["two"].get_string() == "\"\"two quotes\"\"");
    CHECK(t["one_space"].is_string() == true);
    CHECK(t["one_space"].get_string() == " \"one quote\" ");
    CHECK(t["two_space"].is_string() == true);
    CHECK(t["two_space"].get_string() == " \"\"two quotes\"\" ");
    CHECK(t["mismatch1"].is_string() == true);
    CHECK(t["mismatch1"].get_string() == "aaa'''bbb");
    CHECK(t["mismatch2"].is_string() == true);
    CHECK(t["mismatch2"].get_string() == "aaa\"\"\"bbb");
    CHECK(t["escaped"].is_string() == true);
    CHECK(t["escaped"].get_string() == "lol\"\"\"");
    CHECK(t["five-quotes"].is_string() == true);
    CHECK(t["five-quotes"].get_string() == "Closing with five quotes\n\"\"");
    CHECK(t["four-quotes"].is_string() == true);
    CHECK(t["four-quotes"].get_string() == "Closing with four quotes\n\"");
}

TEST_CASE("valid/string/multiline.toml") {
    std::string content = load_file("valid/string/multiline.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 9);
    CHECK(t["equivalent_one"].is_string() == true);
    CHECK(t["equivalent_one"].get_string() == "The quick brown fox jumps over the lazy dog.");
    CHECK(t["equivalent_two"].is_string() == true);
    CHECK(t["equivalent_two"].get_string() == "The quick brown fox jumps over the lazy dog.");
    CHECK(t["equivalent_three"].is_string() == true);
    CHECK(t["equivalent_three"].get_string() == "The quick brown fox jumps over the lazy dog.");
    CHECK(t["whitespace-after-bs"].is_string() == true);
    CHECK(t["whitespace-after-bs"].get_string() == "The quick brown fox jumps over the lazy dog.");
    CHECK(t["no-space"].is_string() == true);
    CHECK(t["no-space"].get_string() == "ab");
    CHECK(t["keep-ws-before"].is_string() == true);
    CHECK(t["keep-ws-before"].get_string() == "a   \tb");
    CHECK(t["escape-bs-1"].is_string() == true);
    CHECK(t["escape-bs-1"].get_string() == "a \\\nb");
    CHECK(t["escape-bs-2"].is_string() == true);
    CHECK(t["escape-bs-2"].get_string() == "a \\b");
    CHECK(t["escape-bs-3"].is_string() == true);
    CHECK(t["escape-bs-3"].get_string() == "a \\\\\n  b");
}

TEST_CASE("valid/string/nl.toml") {
    std::string content = load_file("valid/string/nl.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t["nl_mid"].is_string() == true);
    CHECK(t["nl_mid"].get_string() == "val\nue");
    CHECK(t["nl_end"].is_string() == true);
    CHECK(t["nl_end"].get_string() == "value\n");
    CHECK(t["lit_nl_end"].is_string() == true);
    CHECK(t["lit_nl_end"].get_string() == "value\\n");
    CHECK(t["lit_nl_mid"].is_string() == true);
    CHECK(t["lit_nl_mid"].get_string() == "val\\nue");
    CHECK(t["lit_nl_uni"].is_string() == true);
    CHECK(t["lit_nl_uni"].get_string() == "val\\ue");
}

TEST_CASE("valid/string/quoted-unicode.toml") {
    std::string content = load_file("valid/string/quoted-unicode.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["escaped_string"].is_string() == true);
    CHECK(t["escaped_string"].get_string() == "" + std::string(1, '\0') + " \b  A   ÿ ퟿  ￿ 𐀀 􏿿");
    CHECK(t["not_escaped_string"].is_string() == true);
    CHECK(t["not_escaped_string"].get_string() == "\\u0000 \\u0008 \\u000c \\U00000041 \\u007f \\u0080 \\u00ff \\ud7ff \\ue000 \\uffff \\U00010000 \\U0010ffff");
    CHECK(t["basic_string"].is_string() == true);
    CHECK(t["basic_string"].get_string() == "~  ÿ ퟿  ￿ 𐀀 􏿿");
    CHECK(t["literal_string"].is_string() == true);
    CHECK(t["literal_string"].get_string() == "~  ÿ ퟿  ￿ 𐀀 􏿿");
}

TEST_CASE("valid/string/raw-empty.toml") {
    std::string content = load_file("valid/string/raw-empty.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["empty"].is_string() == true);
    CHECK(t["empty"].get_string() == "");
}

TEST_CASE("valid/string/raw-multiline.toml") {
    std::string content = load_file("valid/string/raw-multiline.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t["oneline"].is_string() == true);
    CHECK(t["oneline"].get_string() == "This string has a ' quote character.");
    CHECK(t["firstnl"].is_string() == true);
    CHECK(t["firstnl"].get_string() == "This string has a ' quote character.");
    CHECK(t["multiline"].is_string() == true);
    CHECK(t["multiline"].get_string() == "This string\nhas ' a quote character\nand more than\none newline\nin it.");
    CHECK(t["multiline_with_tab"].is_string() == true);
    CHECK(t["multiline_with_tab"].get_string() == "First line\n\t Followed by a tab");
    CHECK(t["this-str-has-apostrophes"].is_string() == true);
    CHECK(t["this-str-has-apostrophes"].get_string() == "' there's one already\n'' two more\n''");
}

TEST_CASE("valid/string/raw.toml") {
    std::string content = load_file("valid/string/raw.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 8);
    CHECK(t["backspace"].is_string() == true);
    CHECK(t["backspace"].get_string() == "This string has a \\b backspace character.");
    CHECK(t["tab"].is_string() == true);
    CHECK(t["tab"].get_string() == "This string has a \\t tab character.");
    CHECK(t["unescaped_tab"].is_string() == true);
    CHECK(t["unescaped_tab"].get_string() == "This string has an \t unescaped tab character.");
    CHECK(t["newline"].is_string() == true);
    CHECK(t["newline"].get_string() == "This string has a \\n new line character.");
    CHECK(t["formfeed"].is_string() == true);
    CHECK(t["formfeed"].get_string() == "This string has a \\f form feed character.");
    CHECK(t["carriage"].is_string() == true);
    CHECK(t["carriage"].get_string() == "This string has a \\r carriage return character.");
    CHECK(t["slash"].is_string() == true);
    CHECK(t["slash"].get_string() == "This string has a \\/ slash character.");
    CHECK(t["backslash"].is_string() == true);
    CHECK(t["backslash"].get_string() == "This string has a \\\\ backslash character.");
}

TEST_CASE("valid/string/simple.toml") {
    std::string content = load_file("valid/string/simple.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["answer"].is_string() == true);
    CHECK(t["answer"].get_string() == "You are not drinking enough whisky.");
}

TEST_CASE("valid/string/start-mb.toml") {
    std::string content = load_file("valid/string/start-mb.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t["s1"].is_string() == true);
    CHECK(t["s1"].get_string() == "§");
    CHECK(t["s2"].is_string() == true);
    CHECK(t["s2"].get_string() == "§");
    CHECK(t["s3"].is_string() == true);
    CHECK(t["s3"].get_string() == "§");
    CHECK(t["s4"].is_string() == true);
    CHECK(t["s4"].get_string() == "§");
    CHECK(t["s5"].is_string() == true);
    CHECK(t["s5"].get_string() == "§");
    CHECK(t["s6"].is_string() == true);
    CHECK(t["s6"].get_string() == "§");
    CHECK(t["s7"].is_string() == true);
    CHECK(t["s7"].get_string() == "§");
}

TEST_CASE("valid/string/unicode-escape.toml") {
    std::string content = load_file("valid/string/unicode-escape.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 14);
    CHECK(t["delta-1"].is_string() == true);
    CHECK(t["delta-1"].get_string() == "δ");
    CHECK(t["delta-2"].is_string() == true);
    CHECK(t["delta-2"].get_string() == "δ");
    CHECK(t["a"].is_string() == true);
    CHECK(t["a"].get_string() == "a");
    CHECK(t["b"].is_string() == true);
    CHECK(t["b"].get_string() == "b");
    CHECK(t["c"].is_string() == true);
    CHECK(t["c"].get_string() == "c");
    CHECK(t["null-1"].is_string() == true);
    CHECK(t["null-1"].get_string() == "" + std::string(1, '\0') + "");
    CHECK(t["null-2"].is_string() == true);
    CHECK(t["null-2"].get_string() == "" + std::string(1, '\0') + "");
    CHECK(t["ml-delta-1"].is_string() == true);
    CHECK(t["ml-delta-1"].get_string() == "δ");
    CHECK(t["ml-delta-2"].is_string() == true);
    CHECK(t["ml-delta-2"].get_string() == "δ");
    CHECK(t["ml-a"].is_string() == true);
    CHECK(t["ml-a"].get_string() == "a");
    CHECK(t["ml-b"].is_string() == true);
    CHECK(t["ml-b"].get_string() == "b");
    CHECK(t["ml-c"].is_string() == true);
    CHECK(t["ml-c"].get_string() == "c");
    CHECK(t["ml-null-1"].is_string() == true);
    CHECK(t["ml-null-1"].get_string() == "" + std::string(1, '\0') + "");
    CHECK(t["ml-null-2"].is_string() == true);
    CHECK(t["ml-null-2"].get_string() == "" + std::string(1, '\0') + "");
}

TEST_CASE("valid/string/with-pound.toml") {
    std::string content = load_file("valid/string/with-pound.toml");
    item_t t(view_t{content.c_str()});

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["pound"].is_string() == true);
    CHECK(t["pound"].get_string() == "We see no # comments here.");
    CHECK(t["poundcomment"].is_string() == true);
    CHECK(t["poundcomment"].get_string() == "But there are # some comments here.");
}

