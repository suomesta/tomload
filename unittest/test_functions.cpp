#include "doctest/doctest.h"
#include <cmath>
#include <iterator>
#include "tomload/tomload.h"
#include "tomload/parser.h"

using namespace tomload;

TEST_CASE("testing skip_space()") {
    {
        view_t src = "true";
        skip_space(src, " \t\r\n", false);

        CHECK(src == "true");
    }
    {
        view_t src = "\n\r\t true";
        skip_space(src, " \t\r\n", false);

        CHECK(src == "true");
    }
    {
        view_t src = "  # comment \r\n true";
        skip_space(src, " \t\r\n", true);

        CHECK(src == "true");
    }
    {
        view_t src = "  \n \t";
        skip_space(src, " \t\r\n", true);

        CHECK(src == "");
    }
    {
        view_t src = "  # \t";
        skip_space(src, " \t\r\n", true);

        CHECK(src == "");
    }
}

TEST_CASE("testing parse_item(invalid)") {
    {
        view_t src = "";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "True";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
}

TEST_CASE("testing parse_item(bool)") {
    {
        view_t src = "true";
        item_t result = parse_item(src);

        CHECK(result.is_boolean() == true);
        CHECK(result.get_bool() == true);
        CHECK(src.empty());
    }
    {
        view_t src = "false";
        item_t result = parse_item(src);

        CHECK(result.is_boolean() == true);
        CHECK(result.get_bool() == false);
        CHECK(src.empty());
    }
}

TEST_CASE("testing parse_item(special_float)") {
    {
        view_t src = "inf";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK(result.get_float() == std::numeric_limits<double>::infinity());
        CHECK(src.empty());
    }
    {
        view_t src = "+inf";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK(result.get_float() == std::numeric_limits<double>::infinity());
        CHECK(src.empty());
    }
    {
        view_t src = "-inf";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK(result.get_float() == -std::numeric_limits<double>::infinity());
        CHECK(src.empty());
    }
    {
        view_t src = "nan";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK((std::isnan(result.get_float()) && not std::signbit(result.get_float())));
        CHECK(src.empty());
    }
    {
        view_t src = "+nan";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK((std::isnan(result.get_float()) && not std::signbit(result.get_float())));
        CHECK(src.empty());
    }
    {
        view_t src = "-nan";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK((std::isnan(result.get_float()) && std::signbit(result.get_float())));
        CHECK(src.empty());
    }
}

TEST_CASE("testing parse_item(radix)") {
    {
        view_t src = "0xF_f";
        item_t result = parse_item(src);

        CHECK(result.is_integer() == true);
        CHECK(result.get_integer() == 255LL);
        CHECK(src.empty());
    }
    {
        view_t src = "0o77_7";
        item_t result = parse_item(src);

        CHECK(result.is_integer() == true);
        CHECK(result.get_integer() == 511LL);
        CHECK(src.empty());
    }
    {
        view_t src = "0b11110000";
        item_t result = parse_item(src);

        CHECK(result.is_integer() == true);
        CHECK(result.get_integer() == 240LL);
        CHECK(src.empty());
    }
    {
        view_t src = "0xFFFF_FFFF_FFFF_FFFF";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "0x_F_F";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "0x_F_F";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "0xz";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "0o99";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "0b24";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "0x";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
}

TEST_CASE("testing parse_item(''')") {
    {
        view_t src = "''''''";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "");
        CHECK(src.empty());
    }
    {
        view_t src = "'''A\r\na'''";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "A\r\na");
        CHECK(src.empty());
    }
    {
        view_t src = "''''A\r\na''''";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "'A\r\na'");
        CHECK(src.empty());
    }
    {
        view_t src = "'''''A\r\na'''''";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "''A\r\na''");
        CHECK(src.empty());
    }
    {
        view_t src = "''''''A\r\na''''''";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "");
        CHECK(src.compare("A\r\na''''''") == 0);
    }
    {
        view_t src = "'''\r\nA\r\na'''";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "A\r\na");
        CHECK(src.compare("") == 0);
    }
    {
        view_t src = "'''\nA\na'''";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "A\na");
        CHECK(src.compare("") == 0);
    }
    {
        view_t src = "'''\nA\na''";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
}

TEST_CASE("testing parse_item(')") {
    {
        view_t src = "''";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "");
        CHECK(src.empty());
    }
    {
        view_t src = "'a\"b'";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "a\"b");
        CHECK(src.empty());
    }
    {
        view_t src = "'a\r\nb'";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "'a\"b";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
}

TEST_CASE("testing parse_item(\"\"\")") {
    {
        view_t src = "\"\"\"\"\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\"\"abc\"\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "abc");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\"\"\nabc\"\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "abc");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\"\"\n\nabc\"\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "\nabc");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\"\"\r\nabc\"\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "abc");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\"\"\r\n\r\nabc\"\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "\r\nabc");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\"\"\nabc\\\nedf\"\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "abcedf");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\"\"\nabc\\\n \n\t\nedf\"\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "abcedf");
        CHECK(src.empty());
    }
}

TEST_CASE("testing parse_item(\")") {
    {
        view_t src = "\"\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "");
        CHECK(src.empty());
    }
    {
        view_t src = "\"abc\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "abc");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\\\\\\\"\\r\\n\\t\\b \t\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "\\\"\r\n\t\b \t");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\\u3042\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "あ");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\\U00003044\"";
        item_t result = parse_item(src);

        CHECK(result.is_string() == true);
        CHECK(result.get_string() == "い");
        CHECK(src.empty());
    }
    {
        view_t src = "\"\\u0000\"";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "\"\\u123\"";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "\"\\U0000001F\"";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "\"\\U1234567\"";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "\"\\\"";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "\"abc\r\ndef\"";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "\"abc";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
}

TEST_CASE("testing parse_item(array)") {
    {
        view_t src = "[]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 0);
        CHECK(src.empty());
    }
    {
        view_t src = "[ \t \n ]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 0);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 1);
        CHECK(result[0].is_integer() == true);
        CHECK(result[0].get_integer() == 255LL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff,]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 1);
        CHECK(result[0].is_integer() == true);
        CHECK(result[0].get_integer() == 255LL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff , ]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 1);
        CHECK(result[0].is_integer() == true);
        CHECK(result[0].get_integer() == 255LL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff,true]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 2);
        CHECK(result[0].is_integer() == true);
        CHECK(result[0].get_integer() == 255LL);
        CHECK(result[1].is_boolean() == true);
        CHECK(result[1].get_bool() == true);
        CHECK(src.empty());
        for (array_iterator i = result.array_begin(); i != result.array_end(); ++i) {
            if (std::distance(result.array_begin(), i) == 0) {
                CHECK(i->is_integer() == true);
                CHECK(i->get_integer() == 255LL);
            } else if (std::distance(result.array_begin(), i) == 1) {
                CHECK(i->is_boolean() == true);
                CHECK(i->get_bool() == true);
            }
        }
        int i = 0;
        for (auto r : result.array_range()) {
            if (i == 0) {
                CHECK(r.is_integer() == true);
                CHECK(r.get_integer() == 255LL);
            } else if (i == 1) {
                CHECK(r.is_boolean() == true);
                CHECK(r.get_bool() == true);
            }
            i++;
        }
    }
    {
        view_t src = "[0xff , true , ]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 2);
        CHECK(result[0].is_integer() == true);
        CHECK(result[0].get_integer() == 255LL);
        CHECK(result[1].is_boolean() == true);
        CHECK(result[1].get_bool() == true);
        CHECK(src.empty());
    }
}

TEST_CASE("testing parse()") {
    {
        view_t src = "[aa]  #comm\n";
        item_t result(src);

        CHECK(result.is_table() == true);
        CHECK(result.size() == 0);
    }
    {
        view_t src = "[aa]  #comm\nbb = false\n";
        item_t result(src);

        CHECK(result.is_table() == true);
        CHECK(result.size() == 1);
        CHECK(result.contains("aa") == true);
        CHECK(result["aa"]["bb"].is_boolean() == true);
        CHECK(result["aa"]["bb"].get_bool() == false);
    }
}
