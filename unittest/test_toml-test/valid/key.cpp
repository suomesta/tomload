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
    CHECK(t[u8"alpha"].is_string() == true);
    CHECK(t[u8"alpha"].get_string() == u8"a");
    CHECK(t[u8"123"].is_string() == true);
    CHECK(t[u8"123"].get_string() == u8"num");
    CHECK(t[u8"000111"].is_string() == true);
    CHECK(t[u8"000111"].get_string() == u8"leading");
    CHECK(t[u8"10e3"].is_string() == true);
    CHECK(t[u8"10e3"].get_string() == u8"false float");
    CHECK(t[u8"one1two2"].is_string() == true);
    CHECK(t[u8"one1two2"].get_string() == u8"mixed");
    CHECK(t[u8"with-dash"].is_string() == true);
    CHECK(t[u8"with-dash"].get_string() == u8"dashed");
    CHECK(t[u8"under_score"].is_string() == true);
    CHECK(t[u8"under_score"].get_string() == u8"___");
    CHECK(t[u8"34-11"].is_integer() == true);
    CHECK(t[u8"34-11"].get_integer() == 23);
    CHECK(t[u8"2018_10"].is_table() == true);
    CHECK(t[u8"2018_10"].size() == 1);
    CHECK(t[u8"2018_10"][u8"001"].is_integer() == true);
    CHECK(t[u8"2018_10"][u8"001"].get_integer() == 1);
    CHECK(t[u8"a-a-a"].is_table() == true);
    CHECK(t[u8"a-a-a"].size() == 1);
    CHECK(t[u8"a-a-a"][u8"_"].is_boolean() == true);
    CHECK(t[u8"a-a-a"][u8"_"].get_boolean() == false);
}

TEST_CASE("valid/key/case-sensitive.toml") {
    std::vector<char> content = load_file("valid/key/case-sensitive.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t[u8"sectioN"].is_string() == true);
    CHECK(t[u8"sectioN"].get_string() == u8"NN");
    CHECK(t[u8"section"].is_table() == true);
    CHECK(t[u8"section"].size() == 3);
    CHECK(t[u8"section"][u8"name"].is_string() == true);
    CHECK(t[u8"section"][u8"name"].get_string() == u8"lower");
    CHECK(t[u8"section"][u8"NAME"].is_string() == true);
    CHECK(t[u8"section"][u8"NAME"].get_string() == u8"upper");
    CHECK(t[u8"section"][u8"Name"].is_string() == true);
    CHECK(t[u8"section"][u8"Name"].get_string() == u8"capitalized");
    CHECK(t[u8"Section"].is_table() == true);
    CHECK(t[u8"Section"].size() == 4);
    CHECK(t[u8"Section"][u8"name"].is_string() == true);
    CHECK(t[u8"Section"][u8"name"].get_string() == u8"different section!!");
    CHECK(t[u8"Section"][u8"μ"].is_string() == true);
    CHECK(t[u8"Section"][u8"μ"].get_string() == u8"greek small letter mu");
    CHECK(t[u8"Section"][u8"Μ"].is_string() == true);
    CHECK(t[u8"Section"][u8"Μ"].get_string() == u8"greek capital letter MU");
    CHECK(t[u8"Section"][u8"M"].is_string() == true);
    CHECK(t[u8"Section"][u8"M"].get_string() == u8"latin letter M");
}

TEST_CASE("valid/key/dotted-1.toml") {
    std::vector<char> content = load_file("valid/key/dotted-1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"name"].is_table() == true);
    CHECK(t[u8"name"].size() == 2);
    CHECK(t[u8"name"][u8"first"].is_string() == true);
    CHECK(t[u8"name"][u8"first"].get_string() == u8"Arthur");
    CHECK(t[u8"name"][u8"last"].is_string() == true);
    CHECK(t[u8"name"][u8"last"].get_string() == u8"Dent");
    CHECK(t[u8"many"].is_table() == true);
    CHECK(t[u8"many"].size() == 1);
    CHECK(t[u8"many"][u8"dots"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"dot"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"][u8"dot"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"dot"][u8"dot"].is_table() == true);
    CHECK(t[u8"many"][u8"dots"][u8"dot"][u8"dot"].size() == 1);
    CHECK(t[u8"many"][u8"dots"][u8"dot"][u8"dot"][u8"dot"].is_integer() == true);
    CHECK(t[u8"many"][u8"dots"][u8"dot"][u8"dot"][u8"dot"].get_integer() == 42);
}

TEST_CASE("valid/key/dotted-2.toml") {
    std::vector<char> content = load_file("valid/key/dotted-2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"count"].is_table() == true);
    CHECK(t[u8"count"].size() == 12);
    CHECK(t[u8"count"][u8"a"].is_integer() == true);
    CHECK(t[u8"count"][u8"a"].get_integer() == 1);
    CHECK(t[u8"count"][u8"b"].is_integer() == true);
    CHECK(t[u8"count"][u8"b"].get_integer() == 2);
    CHECK(t[u8"count"][u8"c"].is_integer() == true);
    CHECK(t[u8"count"][u8"c"].get_integer() == 3);
    CHECK(t[u8"count"][u8"d"].is_integer() == true);
    CHECK(t[u8"count"][u8"d"].get_integer() == 4);
    CHECK(t[u8"count"][u8"e"].is_integer() == true);
    CHECK(t[u8"count"][u8"e"].get_integer() == 5);
    CHECK(t[u8"count"][u8"f"].is_integer() == true);
    CHECK(t[u8"count"][u8"f"].get_integer() == 6);
    CHECK(t[u8"count"][u8"g"].is_integer() == true);
    CHECK(t[u8"count"][u8"g"].get_integer() == 7);
    CHECK(t[u8"count"][u8"h"].is_integer() == true);
    CHECK(t[u8"count"][u8"h"].get_integer() == 8);
    CHECK(t[u8"count"][u8"i"].is_integer() == true);
    CHECK(t[u8"count"][u8"i"].get_integer() == 9);
    CHECK(t[u8"count"][u8"j"].is_integer() == true);
    CHECK(t[u8"count"][u8"j"].get_integer() == 10);
    CHECK(t[u8"count"][u8"k"].is_integer() == true);
    CHECK(t[u8"count"][u8"k"].get_integer() == 11);
    CHECK(t[u8"count"][u8"l"].is_integer() == true);
    CHECK(t[u8"count"][u8"l"].get_integer() == 12);
}

TEST_CASE("valid/key/dotted-3.toml") {
    std::vector<char> content = load_file("valid/key/dotted-3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t[u8"top"].is_table() == true);
    CHECK(t[u8"top"].size() == 1);
    CHECK(t[u8"top"][u8"key"].is_integer() == true);
    CHECK(t[u8"top"][u8"key"].get_integer() == 1);
    CHECK(t[u8"tbl"].is_table() == true);
    CHECK(t[u8"tbl"].size() == 1);
    CHECK(t[u8"tbl"][u8"a"].is_table() == true);
    CHECK(t[u8"tbl"][u8"a"].size() == 1);
    CHECK(t[u8"tbl"][u8"a"][u8"b"].is_table() == true);
    CHECK(t[u8"tbl"][u8"a"][u8"b"].size() == 1);
    CHECK(t[u8"tbl"][u8"a"][u8"b"][u8"c"].is_float() == true);
    CHECK(t[u8"tbl"][u8"a"][u8"b"][u8"c"].get_float() == 42.666);
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8"few"].is_table() == true);
    CHECK(t[u8"a"][u8"few"].size() == 1);
    CHECK(t[u8"a"][u8"few"][u8"dots"].is_table() == true);
    CHECK(t[u8"a"][u8"few"][u8"dots"].size() == 1);
    CHECK(t[u8"a"][u8"few"][u8"dots"][u8"polka"].is_table() == true);
    CHECK(t[u8"a"][u8"few"][u8"dots"][u8"polka"].size() == 2);
    CHECK(t[u8"a"][u8"few"][u8"dots"][u8"polka"][u8"dot"].is_string() == true);
    CHECK(t[u8"a"][u8"few"][u8"dots"][u8"polka"][u8"dot"].get_string() == u8"again?");
    CHECK(t[u8"a"][u8"few"][u8"dots"][u8"polka"][u8"dance-with"].is_string() == true);
    CHECK(t[u8"a"][u8"few"][u8"dots"][u8"polka"][u8"dance-with"].get_string() == u8"Dot");
}

TEST_CASE("valid/key/dotted-empty.toml") {
    std::vector<char> content = load_file("valid/key/dotted-empty.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 3);
    CHECK(t[u8""].is_table() == true);
    CHECK(t[u8""].size() == 1);
    CHECK(t[u8""][u8"x"].is_string() == true);
    CHECK(t[u8""][u8"x"].get_string() == u8"empty.x");
    CHECK(t[u8"x"].is_table() == true);
    CHECK(t[u8"x"].size() == 1);
    CHECK(t[u8"x"][u8""].is_string() == true);
    CHECK(t[u8"x"][u8""].get_string() == u8"x.empty");
    CHECK(t[u8"a"].is_table() == true);
    CHECK(t[u8"a"].size() == 1);
    CHECK(t[u8"a"][u8""].is_table() == true);
    CHECK(t[u8"a"][u8""].size() == 1);
    CHECK(t[u8"a"][u8""][u8""].is_string() == true);
    CHECK(t[u8"a"][u8""][u8""].get_string() == u8"empty.empty");
}

TEST_CASE("valid/key/empty-1.toml") {
    std::vector<char> content = load_file("valid/key/empty-1.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8""].is_string() == true);
    CHECK(t[u8""].get_string() == u8"blank");
}

TEST_CASE("valid/key/empty-2.toml") {
    std::vector<char> content = load_file("valid/key/empty-2.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8""].is_string() == true);
    CHECK(t[u8""].get_string() == u8"blank");
}

TEST_CASE("valid/key/empty-3.toml") {
    std::vector<char> content = load_file("valid/key/empty-3.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8""].is_integer() == true);
    CHECK(t[u8""].get_integer() == 0);
}

TEST_CASE("valid/key/equals-nospace.toml") {
    std::vector<char> content = load_file("valid/key/equals-nospace.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"answer"].is_integer() == true);
    CHECK(t[u8"answer"].get_integer() == 42);
}

TEST_CASE("valid/key/escapes.toml") {
    std::vector<char> content = load_file("valid/key/escapes.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 7);
    CHECK(t[u8"\n"].is_string() == true);
    CHECK(t[u8"\n"].get_string() == u8"newline");
    CHECK(t[u8"\b"].is_string() == true);
    CHECK(t[u8"\b"].get_string() == u8"bell");
    CHECK(t[u8"À"].is_string() == true);
    CHECK(t[u8"À"].get_string() == u8"latin capital letter A with grave");
    CHECK(t[u8"\""].is_string() == true);
    CHECK(t[u8"\""].get_string() == u8"just a quote");
    CHECK(t[u8"backsp\b\b"].is_table() == true);
    CHECK(t[u8"backsp\b\b"].size() == 0);
    CHECK(t[u8"\"quoted\""].is_table() == true);
    CHECK(t[u8"\"quoted\""].size() == 1);
    CHECK(t[u8"\"quoted\""][u8"quote"].is_boolean() == true);
    CHECK(t[u8"\"quoted\""][u8"quote"].get_boolean() == true);
    CHECK(t[u8"a.b"].is_table() == true);
    CHECK(t[u8"a.b"].size() == 1);
    CHECK(t[u8"a.b"][u8"À"].is_table() == true);
    CHECK(t[u8"a.b"][u8"À"].size() == 0);
}

TEST_CASE("valid/key/numeric-01.toml") {
    std::vector<char> content = load_file("valid/key/numeric-01.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"1"].is_boolean() == true);
    CHECK(t[u8"1"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-02.toml") {
    std::vector<char> content = load_file("valid/key/numeric-02.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"1"].is_table() == true);
    CHECK(t[u8"1"].size() == 1);
    CHECK(t[u8"1"][u8"2"].is_boolean() == true);
    CHECK(t[u8"1"][u8"2"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-03.toml") {
    std::vector<char> content = load_file("valid/key/numeric-03.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"0123"].is_boolean() == true);
    CHECK(t[u8"0123"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-04.toml") {
    std::vector<char> content = load_file("valid/key/numeric-04.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"01"].is_table() == true);
    CHECK(t[u8"01"].size() == 1);
    CHECK(t[u8"01"][u8"23"].is_boolean() == true);
    CHECK(t[u8"01"][u8"23"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-05.toml") {
    std::vector<char> content = load_file("valid/key/numeric-05.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"23"].is_table() == true);
    CHECK(t[u8"23"].size() == 1);
    CHECK(t[u8"23"][u8"01"].is_boolean() == true);
    CHECK(t[u8"23"][u8"01"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-06.toml") {
    std::vector<char> content = load_file("valid/key/numeric-06.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"-1"].is_boolean() == true);
    CHECK(t[u8"-1"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-07.toml") {
    std::vector<char> content = load_file("valid/key/numeric-07.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"-01"].is_boolean() == true);
    CHECK(t[u8"-01"].get_boolean() == true);
}

TEST_CASE("valid/key/numeric-08.toml") {
    std::vector<char> content = load_file("valid/key/numeric-08.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t[u8"1"].is_string() == true);
    CHECK(t[u8"1"].get_string() == u8"one");
    CHECK(t[u8"01"].is_string() == true);
    CHECK(t[u8"01"].get_string() == u8"zero one");
}

TEST_CASE("valid/key/quoted-dots.toml") {
    std::vector<char> content = load_file("valid/key/quoted-dots.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"plain"].is_integer() == true);
    CHECK(t[u8"plain"].get_integer() == 1);
    CHECK(t[u8"with.dot"].is_integer() == true);
    CHECK(t[u8"with.dot"].get_integer() == 2);
    CHECK(t[u8"plain_table"].is_table() == true);
    CHECK(t[u8"plain_table"].size() == 2);
    CHECK(t[u8"plain_table"][u8"plain"].is_integer() == true);
    CHECK(t[u8"plain_table"][u8"plain"].get_integer() == 3);
    CHECK(t[u8"plain_table"][u8"with.dot"].is_integer() == true);
    CHECK(t[u8"plain_table"][u8"with.dot"].get_integer() == 4);
    CHECK(t[u8"table"].is_table() == true);
    CHECK(t[u8"table"].size() == 1);
    CHECK(t[u8"table"][u8"withdot"].is_table() == true);
    CHECK(t[u8"table"][u8"withdot"].size() == 3);
    CHECK(t[u8"table"][u8"withdot"][u8"plain"].is_integer() == true);
    CHECK(t[u8"table"][u8"withdot"][u8"plain"].get_integer() == 5);
    CHECK(t[u8"table"][u8"withdot"][u8"key.with.dots"].is_integer() == true);
    CHECK(t[u8"table"][u8"withdot"][u8"key.with.dots"].get_integer() == 6);
    CHECK(t[u8"table"][u8"withdot"][u8"escaped.dot"].is_integer() == true);
    CHECK(t[u8"table"][u8"withdot"][u8"escaped.dot"].get_integer() == 7);
}

TEST_CASE("valid/key/quoted-unicode.toml") {
    std::vector<char> content = load_file("valid/key/quoted-unicode.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 5);
    CHECK(t[u8"" + std::string(1, '\0') + u8""].is_string() == true);
    CHECK(t[u8"" + std::string(1, '\0') + u8""].get_string() == u8"null");
    CHECK(t[u8"\\u0000"].is_string() == true);
    CHECK(t[u8"\\u0000"].get_string() == u8"different key");
    CHECK(t[u8"\b  A   ÿ ퟿  ￿ 𐀀 􏿿"].is_string() == true);
    CHECK(t[u8"\b  A   ÿ ퟿  ￿ 𐀀 􏿿"].get_string() == u8"escaped key");
    CHECK(t[u8"~  ÿ ퟿  ￿ 𐀀 􏿿"].is_string() == true);
    CHECK(t[u8"~  ÿ ퟿  ￿ 𐀀 􏿿"].get_string() == u8"basic key");
    CHECK(t[u8"l ~  ÿ ퟿  ￿ 𐀀 􏿿"].is_string() == true);
    CHECK(t[u8"l ~  ÿ ퟿  ￿ 𐀀 􏿿"].get_string() == u8"literal key");
}

TEST_CASE("valid/key/space.toml") {
    std::vector<char> content = load_file("valid/key/space.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"a b"].is_integer() == true);
    CHECK(t[u8"a b"].get_integer() == 1);
    CHECK(t[u8" c d "].is_integer() == true);
    CHECK(t[u8" c d "].get_integer() == 2);
    CHECK(t[u8"  much \t\t  whitespace  \t\n  \r\n  "].is_integer() == true);
    CHECK(t[u8"  much \t\t  whitespace  \t\n  \r\n  "].get_integer() == 3);
    CHECK(t[u8" tbl "].is_table() == true);
    CHECK(t[u8" tbl "].size() == 1);
    CHECK(t[u8" tbl "][u8"\ttab\ttab\t"].is_string() == true);
    CHECK(t[u8" tbl "][u8"\ttab\ttab\t"].get_string() == u8"tab");
}

TEST_CASE("valid/key/special-chars.toml") {
    std::vector<char> content = load_file("valid/key/special-chars.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"=~!@$^&*()_+-`1234567890[]|/?><.,;:'="].is_integer() == true);
    CHECK(t[u8"=~!@$^&*()_+-`1234567890[]|/?><.,;:'="].get_integer() == 1);
}

TEST_CASE("valid/key/special-word.toml") {
    std::vector<char> content = load_file("valid/key/special-word.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 4);
    CHECK(t[u8"false"].is_boolean() == true);
    CHECK(t[u8"false"].get_boolean() == false);
    CHECK(t[u8"true"].is_integer() == true);
    CHECK(t[u8"true"].get_integer() == 1);
    CHECK(t[u8"inf"].is_integer() == true);
    CHECK(t[u8"inf"].get_integer() == 100000000);
    CHECK(t[u8"nan"].is_string() == true);
    CHECK(t[u8"nan"].get_string() == u8"ceci n'est pas un nombre");
}

TEST_CASE("valid/key/start.toml") {
    std::vector<char> content = load_file("valid/key/start.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 10);
    CHECK(t[u8"-key"].is_table() == true);
    CHECK(t[u8"-key"].size() == 1);
    CHECK(t[u8"-key"][u8"-key"].is_integer() == true);
    CHECK(t[u8"-key"][u8"-key"].get_integer() == 1);
    CHECK(t[u8"_key"].is_table() == true);
    CHECK(t[u8"_key"].size() == 1);
    CHECK(t[u8"_key"][u8"_key"].is_integer() == true);
    CHECK(t[u8"_key"][u8"_key"].get_integer() == 2);
    CHECK(t[u8"1key"].is_table() == true);
    CHECK(t[u8"1key"].size() == 1);
    CHECK(t[u8"1key"][u8"1key"].is_integer() == true);
    CHECK(t[u8"1key"][u8"1key"].get_integer() == 3);
    CHECK(t[u8"-"].is_table() == true);
    CHECK(t[u8"-"].size() == 1);
    CHECK(t[u8"-"][u8"-"].is_integer() == true);
    CHECK(t[u8"-"][u8"-"].get_integer() == 4);
    CHECK(t[u8"_"].is_table() == true);
    CHECK(t[u8"_"].size() == 1);
    CHECK(t[u8"_"][u8"_"].is_integer() == true);
    CHECK(t[u8"_"][u8"_"].get_integer() == 5);
    CHECK(t[u8"1"].is_table() == true);
    CHECK(t[u8"1"].size() == 1);
    CHECK(t[u8"1"][u8"1"].is_integer() == true);
    CHECK(t[u8"1"][u8"1"].get_integer() == 6);
    CHECK(t[u8"---"].is_table() == true);
    CHECK(t[u8"---"].size() == 1);
    CHECK(t[u8"---"][u8"---"].is_integer() == true);
    CHECK(t[u8"---"][u8"---"].get_integer() == 7);
    CHECK(t[u8"___"].is_table() == true);
    CHECK(t[u8"___"].size() == 1);
    CHECK(t[u8"___"][u8"___"].is_integer() == true);
    CHECK(t[u8"___"][u8"___"].get_integer() == 8);
    CHECK(t[u8"111"].is_table() == true);
    CHECK(t[u8"111"].size() == 1);
    CHECK(t[u8"111"][u8"111"].is_integer() == true);
    CHECK(t[u8"111"][u8"111"].get_integer() == 9);
    CHECK(t[u8"inline"].is_table() == true);
    CHECK(t[u8"inline"].size() == 1);
    CHECK(t[u8"inline"][u8"---"].is_table() == true);
    CHECK(t[u8"inline"][u8"---"].size() == 3);
    CHECK(t[u8"inline"][u8"---"][u8"---"].is_integer() == true);
    CHECK(t[u8"inline"][u8"---"][u8"---"].get_integer() == 10);
    CHECK(t[u8"inline"][u8"---"][u8"___"].is_integer() == true);
    CHECK(t[u8"inline"][u8"---"][u8"___"].get_integer() == 11);
    CHECK(t[u8"inline"][u8"---"][u8"111"].is_integer() == true);
    CHECK(t[u8"inline"][u8"---"][u8"111"].get_integer() == 12);
}

TEST_CASE("valid/key/zero.toml") {
    std::vector<char> content = load_file("valid/key/zero.toml");
    view_t view{content.data(), content.size()};
    item_t t{view};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t[u8"0"].is_integer() == true);
    CHECK(t[u8"0"].get_integer() == 0);
}

