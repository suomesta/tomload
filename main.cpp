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
