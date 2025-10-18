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

TEST_CASE("valid/key/alphanum.toml") {
    std::vector<char> content = load_file("valid/key/alphanum.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 10);
    CHECK(t["alpha"].is_string() == true);
    CHECK(t["alpha"].get_string() == "a");
    CHECK(t["123"].is_string() == true);
    CHECK(t["123"].get_string() == "num");
    CHECK(t["000111"].is_string() == true);
    CHECK(t["000111"].get_string() == "leading");
    CHECK(t["10e3"].is_string() == true);
    CHECK(t["10e3"].get_string() == "false float");
    CHECK(t["one1two2"].is_string() == true);
    CHECK(t["one1two2"].get_string() == "mixed");
    CHECK(t["with-dash"].is_string() == true);
    CHECK(t["with-dash"].get_string() == "dashed");
    CHECK(t["under_score"].is_string() == true);
    CHECK(t["under_score"].get_string() == "___");
    CHECK(t["34-11"].is_integer() == true);
    CHECK(t["34-11"].get_integer() == 23);
    CHECK(t["2018_10"].is_table() == true);
    CHECK(t["2018_10"].size() == 1);
    CHECK(t["2018_10"]["001"].is_integer() == true);
    CHECK(t["2018_10"]["001"].get_integer() == 1);
    CHECK(t["a-a-a"].is_table() == true);
    CHECK(t["a-a-a"].size() == 1);
    CHECK(t["a-a-a"]["_"].is_boolean() == true);
    CHECK(t["a-a-a"]["_"].get_boolean() == false);
}

TEST_CASE("valid/key/case-sensitive.toml") {
    std::vector<char> content = load_file("valid/key/case-sensitive.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["sectioN"].is_string() == true);
    CHECK(t["sectioN"].get_string() == "NN");
    CHECK(t["section"].is_table() == true);
    CHECK(t["section"].size() == 3);
    CHECK(t["section"]["name"].is_string() == true);
    CHECK(t["section"]["name"].get_string() == "lower");
    CHECK(t["section"]["NAME"].is_string() == true);
    CHECK(t["section"]["NAME"].get_string() == "upper");
    CHECK(t["section"]["Name"].is_string() == true);
    CHECK(t["section"]["Name"].get_string() == "capitalized");
    CHECK(t["Section"].is_table() == true);
    CHECK(t["Section"].size() == 4);
    CHECK(t["Section"]["name"].is_string() == true);
    CHECK(t["Section"]["name"].get_string() == "different section!!");
    CHECK(t["Section"][u8"μ"].is_string() == true);
    CHECK(t["Section"][u8"μ"].get_string() == "greek small letter mu");
    CHECK(t["Section"][u8"Μ"].is_string() == true);
    CHECK(t["Section"][u8"Μ"].get_string() == "greek capital letter MU");
    CHECK(t["Section"]["M"].is_string() == true);
    CHECK(t["Section"]["M"].get_string() == "latin letter M");
}

TEST_CASE("valid/key/dotted-1.toml") {
    std::vector<char> content = load_file("valid/key/dotted-1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["name"].is_table() == true);
    CHECK(t["name"].size() == 2);
    CHECK(t["name"]["first"].is_string() == true);
    CHECK(t["name"]["first"].get_string() == "Arthur");
    CHECK(t["name"]["last"].is_string() == true);
    CHECK(t["name"]["last"].get_string() == "Dent");
    CHECK(t["many"].is_table() == true);
    CHECK(t["many"].size() == 1);
    CHECK(t["many"]["dots"].is_table() == true);
    CHECK(t["many"]["dots"].size() == 1);
    CHECK(t["many"]["dots"]["dot"].is_table() == true);
    CHECK(t["many"]["dots"]["dot"].size() == 1);
    CHECK(t["many"]["dots"]["dot"]["dot"].is_table() == true);
    CHECK(t["many"]["dots"]["dot"]["dot"].size() == 1);
    CHECK(t["many"]["dots"]["dot"]["dot"]["dot"].is_integer() == true);
    CHECK(t["many"]["dots"]["dot"]["dot"]["dot"].get_integer() == 42);
}

TEST_CASE("valid/key/dotted-2.toml") {
    std::vector<char> content = load_file("valid/key/dotted-2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["count"].is_table() == true);
    CHECK(t["count"].size() == 12);
    CHECK(t["count"]["a"].is_integer() == true);
    CHECK(t["count"]["a"].get_integer() == 1);
    CHECK(t["count"]["b"].is_integer() == true);
    CHECK(t["count"]["b"].get_integer() == 2);
    CHECK(t["count"]["c"].is_integer() == true);
    CHECK(t["count"]["c"].get_integer() == 3);
    CHECK(t["count"]["d"].is_integer() == true);
    CHECK(t["count"]["d"].get_integer() == 4);
    CHECK(t["count"]["e"].is_integer() == true);
    CHECK(t["count"]["e"].get_integer() == 5);
    CHECK(t["count"]["f"].is_integer() == true);
    CHECK(t["count"]["f"].get_integer() == 6);
    CHECK(t["count"]["g"].is_integer() == true);
    CHECK(t["count"]["g"].get_integer() == 7);
    CHECK(t["count"]["h"].is_integer() == true);
    CHECK(t["count"]["h"].get_integer() == 8);
    CHECK(t["count"]["i"].is_integer() == true);
    CHECK(t["count"]["i"].get_integer() == 9);
    CHECK(t["count"]["j"].is_integer() == true);
    CHECK(t["count"]["j"].get_integer() == 10);
    CHECK(t["count"]["k"].is_integer() == true);
    CHECK(t["count"]["k"].get_integer() == 11);
    CHECK(t["count"]["l"].is_integer() == true);
    CHECK(t["count"]["l"].get_integer() == 12);
}

TEST_CASE("valid/key/dotted-3.toml") {
    std::vector<char> content = load_file("valid/key/dotted-3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t["top"].is_table() == true);
    CHECK(t["top"].size() == 1);
    CHECK(t["top"]["key"].is_integer() == true);
    CHECK(t["top"]["key"].get_integer() == 1);
    CHECK(t["tbl"].is_table() == true);
    CHECK(t["tbl"].size() == 1);
    CHECK(t["tbl"]["a"].is_table() == true);
    CHECK(t["tbl"]["a"].size() == 1);
    CHECK(t["tbl"]["a"]["b"].is_table() == true);
    CHECK(t["tbl"]["a"]["b"].size() == 1);
    CHECK(t["tbl"]["a"]["b"]["c"].is_float() == true);
    CHECK(t["tbl"]["a"]["b"]["c"].get_float() == 42.666);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["few"].is_table() == true);
    CHECK(t["a"]["few"].size() == 1);
    CHECK(t["a"]["few"]["dots"].is_table() == true);
    CHECK(t["a"]["few"]["dots"].size() == 1);
    CHECK(t["a"]["few"]["dots"]["polka"].is_table() == true);
    CHECK(t["a"]["few"]["dots"]["polka"].size() == 2);
    CHECK(t["a"]["few"]["dots"]["polka"]["dot"].is_string() == true);
    CHECK(t["a"]["few"]["dots"]["polka"]["dot"].get_string() == "again?");
    CHECK(t["a"]["few"]["dots"]["polka"]["dance-with"].is_string() == true);
    CHECK(t["a"]["few"]["dots"]["polka"]["dance-with"].get_string() == "Dot");
}

TEST_CASE("valid/key/dotted-empty.toml") {
    std::vector<char> content = load_file("valid/key/dotted-empty.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t[""].is_table() == true);
    CHECK(t[""].size() == 1);
    CHECK(t[""]["x"].is_string() == true);
    CHECK(t[""]["x"].get_string() == "empty.x");
    CHECK(t["x"].is_table() == true);
    CHECK(t["x"].size() == 1);
    CHECK(t["x"][""].is_string() == true);
    CHECK(t["x"][""].get_string() == "x.empty");
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"][""].is_table() == true);
    CHECK(t["a"][""].size() == 1);
    CHECK(t["a"][""][""].is_string() == true);
    CHECK(t["a"][""][""].get_string() == "empty.empty");
}

TEST_CASE("valid/key/empty-1.toml") {
    std::vector<char> content = load_file("valid/key/empty-1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[""].is_string() == true);
    CHECK(t[""].get_string() == "blank");
}

TEST_CASE("valid/key/empty-2.toml") {
    std::vector<char> content = load_file("valid/key/empty-2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[""].is_string() == true);
    CHECK(t[""].get_string() == "blank");
}

TEST_CASE("valid/key/empty-3.toml") {
    std::vector<char> content = load_file("valid/key/empty-3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[""].is_integer() == true);
    CHECK(t[""].get_integer() == 0);
}

TEST_CASE("valid/key/equals-nospace.toml") {
    std::vector<char> content = load_file("valid/key/equals-nospace.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["answer"].is_integer() == true);
    CHECK(t["answer"].get_integer() == 42);
}

TEST_CASE("valid/key/escapes.toml") {
    std::vector<char> content = load_file("valid/key/escapes.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t["\n"].is_string() == true);
    CHECK(t["\n"].get_string() == "newline");
    CHECK(t["\b"].is_string() == true);
    CHECK(t["\b"].get_string() == "bell");
    CHECK(t[u8"À"].is_string() == true);
    CHECK(t[u8"À"].get_string() == "latin capital letter A with grave");
    CHECK(t["\""].is_string() == true);
    CHECK(t["\""].get_string() == "just a quote");
    CHECK(t["backsp\b\b"].is_table() == true);
    CHECK(t["backsp\b\b"].size() == 0);
    CHECK(t["\"quoted\""].is_table() == true);
    CHECK(t["\"quoted\""].size() == 1);
    CHECK(t["\"quoted\""]["quote"].is_boolean() == true);
    CHECK(t["\"quoted\""]["quote"].get_boolean() == true);
    CHECK(t["a.b"].is_table() == true);
    CHECK(t["a.b"].size() == 1);
    CHECK(t["a.b"][u8"À"].is_table() == true);
    CHECK(t["a.b"][u8"À"].size() == 0);
}

TEST_CASE("valid/key/numeric-01.toml") {
    std::vector<char> content = load_file("valid/key/numeric-01.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["1"].is_boolean() == true);
    CHECK(t["1"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-02.toml") {
    std::vector<char> content = load_file("valid/key/numeric-02.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["1"].is_table() == true);
    CHECK(t["1"].size() == 1);
    CHECK(t["1"]["2"].is_boolean() == true);
    CHECK(t["1"]["2"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-03.toml") {
    std::vector<char> content = load_file("valid/key/numeric-03.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["0123"].is_boolean() == true);
    CHECK(t["0123"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-04.toml") {
    std::vector<char> content = load_file("valid/key/numeric-04.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["01"].is_table() == true);
    CHECK(t["01"].size() == 1);
    CHECK(t["01"]["23"].is_boolean() == true);
    CHECK(t["01"]["23"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-05.toml") {
    std::vector<char> content = load_file("valid/key/numeric-05.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["23"].is_table() == true);
    CHECK(t["23"].size() == 1);
    CHECK(t["23"]["01"].is_boolean() == true);
    CHECK(t["23"]["01"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-06.toml") {
    std::vector<char> content = load_file("valid/key/numeric-06.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["-1"].is_boolean() == true);
    CHECK(t["-1"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-07.toml") {
    std::vector<char> content = load_file("valid/key/numeric-07.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["-01"].is_boolean() == true);
    CHECK(t["-01"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-08.toml") {
    std::vector<char> content = load_file("valid/key/numeric-08.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["1"].is_string() == true);
    CHECK(t["1"].get_string() == "one");
    CHECK(t["01"].is_string() == true);
    CHECK(t["01"].get_string() == "zero one");
}

TEST_CASE("valid/key/quoted-dots.toml") {
    std::vector<char> content = load_file("valid/key/quoted-dots.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["plain"].is_integer() == true);
    CHECK(t["plain"].get_integer() == 1);
    CHECK(t["with.dot"].is_integer() == true);
    CHECK(t["with.dot"].get_integer() == 2);
    CHECK(t["plain_table"].is_table() == true);
    CHECK(t["plain_table"].size() == 2);
    CHECK(t["plain_table"]["plain"].is_integer() == true);
    CHECK(t["plain_table"]["plain"].get_integer() == 3);
    CHECK(t["plain_table"]["with.dot"].is_integer() == true);
    CHECK(t["plain_table"]["with.dot"].get_integer() == 4);
    CHECK(t["table"].is_table() == true);
    CHECK(t["table"].size() == 1);
    CHECK(t["table"]["withdot"].is_table() == true);
    CHECK(t["table"]["withdot"].size() == 3);
    CHECK(t["table"]["withdot"]["plain"].is_integer() == true);
    CHECK(t["table"]["withdot"]["plain"].get_integer() == 5);
    CHECK(t["table"]["withdot"]["key.with.dots"].is_integer() == true);
    CHECK(t["table"]["withdot"]["key.with.dots"].get_integer() == 6);
    CHECK(t["table"]["withdot"]["escaped.dot"].is_integer() == true);
    CHECK(t["table"]["withdot"]["escaped.dot"].get_integer() == 7);
}

TEST_CASE("valid/key/quoted-unicode.toml") {
    std::vector<char> content = load_file("valid/key/quoted-unicode.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t["" + std::string(1, '\0') + ""].is_string() == true);
    CHECK(t["" + std::string(1, '\0') + ""].get_string() == "null");
    CHECK(t["\\u0000"].is_string() == true);
    CHECK(t["\\u0000"].get_string() == "different key");
    CHECK(t[u8"\b  A   ÿ ퟿  ￿ 𐀀 􏿿"].is_string() == true);
    CHECK(t[u8"\b  A   ÿ ퟿  ￿ 𐀀 􏿿"].get_string() == "escaped key");
    CHECK(t[u8"~  ÿ ퟿  ￿ 𐀀 􏿿"].is_string() == true);
    CHECK(t[u8"~  ÿ ퟿  ￿ 𐀀 􏿿"].get_string() == "basic key");
    CHECK(t[u8"l ~  ÿ ퟿  ￿ 𐀀 􏿿"].is_string() == true);
    CHECK(t[u8"l ~  ÿ ퟿  ￿ 𐀀 􏿿"].get_string() == "literal key");
}

TEST_CASE("valid/key/space.toml") {
    std::vector<char> content = load_file("valid/key/space.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["a b"].is_integer() == true);
    CHECK(t["a b"].get_integer() == 1);
    CHECK(t[" c d "].is_integer() == true);
    CHECK(t[" c d "].get_integer() == 2);
    CHECK(t["  much \t\t  whitespace  \t\n  \r\n  "].is_integer() == true);
    CHECK(t["  much \t\t  whitespace  \t\n  \r\n  "].get_integer() == 3);
    CHECK(t[" tbl "].is_table() == true);
    CHECK(t[" tbl "].size() == 1);
    CHECK(t[" tbl "]["\ttab\ttab\t"].is_string() == true);
    CHECK(t[" tbl "]["\ttab\ttab\t"].get_string() == "tab");
}

TEST_CASE("valid/key/special-chars.toml") {
    std::vector<char> content = load_file("valid/key/special-chars.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["=~!@$^&*()_+-`1234567890[]|/?><.,;:'="].is_integer() == true);
    CHECK(t["=~!@$^&*()_+-`1234567890[]|/?><.,;:'="].get_integer() == 1);
}

TEST_CASE("valid/key/special-word.toml") {
    std::vector<char> content = load_file("valid/key/special-word.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t["false"].is_boolean() == true);
    CHECK(t["false"].get_boolean() == false);
    CHECK(t["true"].is_integer() == true);
    CHECK(t["true"].get_integer() == 1);
    CHECK(t["inf"].is_integer() == true);
    CHECK(t["inf"].get_integer() == 100000000);
    CHECK(t["nan"].is_string() == true);
    CHECK(t["nan"].get_string() == "ceci n'est pas un nombre");
}

TEST_CASE("valid/key/start.toml") {
    std::vector<char> content = load_file("valid/key/start.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 10);
    CHECK(t["-key"].is_table() == true);
    CHECK(t["-key"].size() == 1);
    CHECK(t["-key"]["-key"].is_integer() == true);
    CHECK(t["-key"]["-key"].get_integer() == 1);
    CHECK(t["_key"].is_table() == true);
    CHECK(t["_key"].size() == 1);
    CHECK(t["_key"]["_key"].is_integer() == true);
    CHECK(t["_key"]["_key"].get_integer() == 2);
    CHECK(t["1key"].is_table() == true);
    CHECK(t["1key"].size() == 1);
    CHECK(t["1key"]["1key"].is_integer() == true);
    CHECK(t["1key"]["1key"].get_integer() == 3);
    CHECK(t["-"].is_table() == true);
    CHECK(t["-"].size() == 1);
    CHECK(t["-"]["-"].is_integer() == true);
    CHECK(t["-"]["-"].get_integer() == 4);
    CHECK(t["_"].is_table() == true);
    CHECK(t["_"].size() == 1);
    CHECK(t["_"]["_"].is_integer() == true);
    CHECK(t["_"]["_"].get_integer() == 5);
    CHECK(t["1"].is_table() == true);
    CHECK(t["1"].size() == 1);
    CHECK(t["1"]["1"].is_integer() == true);
    CHECK(t["1"]["1"].get_integer() == 6);
    CHECK(t["---"].is_table() == true);
    CHECK(t["---"].size() == 1);
    CHECK(t["---"]["---"].is_integer() == true);
    CHECK(t["---"]["---"].get_integer() == 7);
    CHECK(t["___"].is_table() == true);
    CHECK(t["___"].size() == 1);
    CHECK(t["___"]["___"].is_integer() == true);
    CHECK(t["___"]["___"].get_integer() == 8);
    CHECK(t["111"].is_table() == true);
    CHECK(t["111"].size() == 1);
    CHECK(t["111"]["111"].is_integer() == true);
    CHECK(t["111"]["111"].get_integer() == 9);
    CHECK(t["inline"].is_table() == true);
    CHECK(t["inline"].size() == 1);
    CHECK(t["inline"]["---"].is_table() == true);
    CHECK(t["inline"]["---"].size() == 3);
    CHECK(t["inline"]["---"]["---"].is_integer() == true);
    CHECK(t["inline"]["---"]["---"].get_integer() == 10);
    CHECK(t["inline"]["---"]["___"].is_integer() == true);
    CHECK(t["inline"]["---"]["___"].get_integer() == 11);
    CHECK(t["inline"]["---"]["111"].is_integer() == true);
    CHECK(t["inline"]["---"]["111"].get_integer() == 12);
}

TEST_CASE("valid/key/zero.toml") {
    std::vector<char> content = load_file("valid/key/zero.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["0"].is_integer() == true);
    CHECK(t["0"].get_integer() == 0);
}

