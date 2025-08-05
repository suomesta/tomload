#include "doctest/doctest.h"
#include "tomload/tomload.h"

using namespace tomload;

TEST_CASE("testing bool constructor, is_***() and get_***()") {
    item_t item(true);

    CHECK(item.is_boolean() == true);
    CHECK(item.is_integer() == false);
    CHECK(item.is_float() == false);
    CHECK(item.is_string() == false);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == false);

    CHECK(item.get_bool() == true);
    CHECK_THROWS_AS(item.get_integer(), type_error&);
    CHECK_THROWS_AS(item.get_float(), type_error&);
    CHECK_THROWS_AS(item.get_string(), type_error&);

    boolean_t b;
    CHECK(item.get(b) == true);
    CHECK(b == true);
    integer_t i;
    CHECK(item.get(i) == false);
    float_t d;
    CHECK(item.get(d) == false);
    string_t s;
    CHECK(item.get(s) == false);
}

TEST_CASE("testing integer constructor, is_***() and get_***()") {
    item_t item(static_cast<integer_t>(123));

    CHECK(item.is_boolean() == false);
    CHECK(item.is_integer() == true);
    CHECK(item.is_float() == false);
    CHECK(item.is_string() == false);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == false);

    CHECK_THROWS_AS(item.get_bool(), type_error&);
    CHECK(item.get_integer() == 123);
    CHECK_THROWS_AS(item.get_float(), type_error&);
    CHECK_THROWS_AS(item.get_string(), type_error&);

    boolean_t b;
    CHECK(item.get(b) == false);
    integer_t i;
    CHECK(item.get(i) == true);
    CHECK(i == 123);
    float_t d;
    CHECK(item.get(d) == true);
    CHECK(d == 123.0);
    string_t s;
    CHECK(item.get(s) == false);
}

TEST_CASE("testing float constructor, is_***() and get_***()") {
    item_t item(static_cast<float_t>(1.5));

    CHECK(item.is_boolean() == false);
    CHECK(item.is_integer() == false);
    CHECK(item.is_float() == true);
    CHECK(item.is_string() == false);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == false);

    CHECK_THROWS_AS(item.get_bool(), type_error&);
    CHECK_THROWS_AS(item.get_integer(), type_error&);
    CHECK(item.get_float() == 1.5);
    CHECK_THROWS_AS(item.get_string(), type_error&);

    boolean_t b;
    CHECK(item.get(b) == false);
    integer_t i;
    CHECK(item.get(i) == true);
    CHECK(i == 1);
    float_t d;
    CHECK(item.get(d) == true);
    CHECK(d == 1.5);
    string_t s;
    CHECK(item.get(s) == false);
}

TEST_CASE("testing string constructor, is_***() and get_***()") {
    item_t item(string_t{"abc"});

    CHECK(item.is_boolean() == false);
    CHECK(item.is_integer() == false);
    CHECK(item.is_float() == false);
    CHECK(item.is_string() == true);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == false);

    CHECK_THROWS_AS(item.get_bool(), type_error&);
    CHECK_THROWS_AS(item.get_integer(), type_error&);
    CHECK_THROWS_AS(item.get_float(), type_error&);
    CHECK(item.get_string() == "abc");

    boolean_t b;
    CHECK(item.get(b) == false);
    integer_t i;
    CHECK(item.get(i) == false);
    float_t d;
    CHECK(item.get(d) == false);
    string_t s;
    CHECK(item.get(s) == true);
    CHECK(s == "abc");
}
