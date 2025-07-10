#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <cmath>
#include "toml_r.hpp"

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

        CHECK(result.is_bool() == true);
        CHECK(result.b == true);
        CHECK(src.empty());
    }
    {
        view_t src = "false";
        item_t result = parse_item(src);

        CHECK(result.is_bool() == true);
        CHECK(result.b == false);
        CHECK(src.empty());
    }
}

TEST_CASE("testing parse_item(special_float)") {
    {
        view_t src = "inf";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK(result.d == std::numeric_limits<double>::infinity());
        CHECK(src.empty());
    }
    {
        view_t src = "+inf";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK(result.d == std::numeric_limits<double>::infinity());
        CHECK(src.empty());
    }
    {
        view_t src = "-inf";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK(result.d == -std::numeric_limits<double>::infinity());
        CHECK(src.empty());
    }
    {
        view_t src = "nan";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK((std::isnan(result.d) && not std::signbit(result.d)));
        CHECK(src.empty());
    }
    {
        view_t src = "+nan";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK((std::isnan(result.d) && not std::signbit(result.d)));
        CHECK(src.empty());
    }
    {
        view_t src = "-nan";
        item_t result = parse_item(src);

        CHECK(result.is_float() == true);
        CHECK((std::isnan(result.d) && std::signbit(result.d)));
        CHECK(src.empty());
    }
}

TEST_CASE("testing parse_item(uint)") {
    {
        view_t src = "0xF_f";
        item_t result = parse_item(src);

        CHECK(result.is_uint() == true);
        CHECK(result.u == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "0o77_7";
        item_t result = parse_item(src);

        CHECK(result.is_uint() == true);
        CHECK(result.u == 511UL);
        CHECK(src.empty());
    }
    {
        view_t src = "0b11110000";
        item_t result = parse_item(src);

        CHECK(result.is_uint() == true);
        CHECK(result.u == 240UL);
        CHECK(src.empty());
    }
    {
        view_t src = "0xF_FFFF_FFFF_FFFF_FFFF";

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
        view_t src = "0x";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
}

TEST_CASE("testing parse_item(array)") {
    {
        view_t src = "[]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.v->size() == 0);
        CHECK(src.empty());
    }
    {
        view_t src = "[ \t \n ]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.v->size() == 0);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.v->size() == 1);
        CHECK(result.v->at(0).type == item_t::TYPE_UINT);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff,]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.v->size() == 1);
        CHECK(result.v->at(0).type == item_t::TYPE_UINT);
        CHECK(result.v->at(0).u == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff , ]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.v->size() == 1);
        CHECK(result.v->at(0).type == item_t::TYPE_UINT);
        CHECK(result.v->at(0).u == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff,true]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.v->size() == 2);
        CHECK(result.v->at(0).type == item_t::TYPE_UINT);
        CHECK(result.v->at(0).u == 255UL);
        CHECK(result.v->at(1).type == item_t::TYPE_BOOL);
        CHECK(result.v->at(1).b == true);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff , true , ]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 2);
        CHECK(result[0].type == item_t::TYPE_UINT);
        CHECK(result[0].u == 255UL);
        CHECK(result[1].type == item_t::TYPE_BOOL);
        CHECK(result[1].b == true);
        CHECK(src.empty());
    }

    {
        view_t src = "[aa]  #comm\n";
        parse(src);
    }
    {
        view_t src = "[aa]  #comm\nbb = true\n";
        parse(src);
    }
}