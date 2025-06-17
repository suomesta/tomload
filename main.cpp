#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "toml_r.hpp"


TEST_CASE("testing parse_item(bool)") {
    {
        view_t src = "true";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_BOOL);
        CHECK(result.b == true);
        CHECK(src.empty());
    }
    {
        view_t src = "false";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_BOOL);
        CHECK(result.b == false);
        CHECK(src.empty());
    }
}

TEST_CASE("testing parse_item(uint)") {
    {
        view_t src = "0xF_f";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_UINT);
        CHECK(result.u == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "0xF_FFFF_FFFF_FFFF_FFFF";

        CHECK_THROWS_AS(parse_item(src), parse_error&);
    }
    {
        view_t src = "0o77_7";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_UINT);
        CHECK(result.u == 511UL);
        CHECK(src.empty());
    }
    {
        view_t src = "0b11110000";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_UINT);
        CHECK(result.u == 240UL);
        CHECK(src.empty());
    }
}

TEST_CASE("testing parse_item(vector)") {
    {
        view_t src = "[]";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_VECTOR);
        CHECK(result.v->size() == 0);
        CHECK(src.empty());
    }
    {
        view_t src = "[ \t \n ]";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_VECTOR);
        CHECK(result.v->size() == 0);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff]";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_VECTOR);
        CHECK(result.v->size() == 1);
        CHECK(result.v->at(0).type == item_t::TYPE_UINT);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff,]";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_VECTOR);
        CHECK(result.v->size() == 1);
        CHECK(result.v->at(0).type == item_t::TYPE_UINT);
        CHECK(result.v->at(0).u == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff , ]";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_VECTOR);
        CHECK(result.v->size() == 1);
        CHECK(result.v->at(0).type == item_t::TYPE_UINT);
        CHECK(result.v->at(0).u == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff,true]";
        item_t result = parse_item(src);

        CHECK(result.type == item_t::TYPE_VECTOR);
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

        CHECK(result.type == item_t::TYPE_VECTOR);
        CHECK(result.v->size() == 2);
        CHECK(result.v->at(0).type == item_t::TYPE_UINT);
        CHECK(result.v->at(0).u == 255UL);
        CHECK(result.v->at(1).type == item_t::TYPE_BOOL);
        CHECK(result.v->at(1).b == true);
        CHECK(src.empty());
    }
}