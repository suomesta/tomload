#include "doctest/doctest.h"
#include "tomload/tomload.h"

using namespace tomload;

TEST_CASE("testing boolean item accessors") {
    item_t item(true);

    CHECK(item.is_boolean() == true);
    CHECK(item.is_integer() == false);
    CHECK(item.is_float() == false);
    CHECK(item.is_string() == false);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == false);

    CHECK(item.get_boolean() == true);
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

    CHECK_THROWS_AS(item.size(), type_error&);
    CHECK_THROWS_AS(item.empty(), type_error&);
    CHECK_THROWS_AS(item[0], type_error&);
    CHECK_THROWS_AS(item[""], type_error&);
    CHECK_THROWS_AS(item.contains(""), type_error&);
    CHECK_THROWS_AS(item.array_begin(), type_error&);
    CHECK_THROWS_AS(item.array_end(), type_error&);
    CHECK_THROWS_AS(item.table_begin(), type_error&);
    CHECK_THROWS_AS(item.table_end(), type_error&);
    CHECK_THROWS_AS(item.array_range(), type_error&);
    CHECK_THROWS_AS(item.table_range(), type_error&);
}

TEST_CASE("testing integer item accessors") {
    item_t item(static_cast<integer_t>(123));

    CHECK(item.is_boolean() == false);
    CHECK(item.is_integer() == true);
    CHECK(item.is_float() == false);
    CHECK(item.is_string() == false);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == false);

    CHECK_THROWS_AS(item.get_boolean(), type_error&);
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

    CHECK_THROWS_AS(item.size(), type_error&);
    CHECK_THROWS_AS(item.empty(), type_error&);
    CHECK_THROWS_AS(item[0], type_error&);
    CHECK_THROWS_AS(item[""], type_error&);
    CHECK_THROWS_AS(item.contains(""), type_error&);
    CHECK_THROWS_AS(item.array_begin(), type_error&);
    CHECK_THROWS_AS(item.array_end(), type_error&);
    CHECK_THROWS_AS(item.table_begin(), type_error&);
    CHECK_THROWS_AS(item.table_end(), type_error&);
    CHECK_THROWS_AS(item.array_range(), type_error&);
    CHECK_THROWS_AS(item.table_range(), type_error&);
}

TEST_CASE("testing float item accessors") {
    item_t item(static_cast<float_t>(1.5));

    CHECK(item.is_boolean() == false);
    CHECK(item.is_integer() == false);
    CHECK(item.is_float() == true);
    CHECK(item.is_string() == false);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == false);

    CHECK_THROWS_AS(item.get_boolean(), type_error&);
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

    CHECK_THROWS_AS(item.size(), type_error&);
    CHECK_THROWS_AS(item.empty(), type_error&);
    CHECK_THROWS_AS(item[0], type_error&);
    CHECK_THROWS_AS(item[""], type_error&);
    CHECK_THROWS_AS(item.contains(""), type_error&);
    CHECK_THROWS_AS(item.array_begin(), type_error&);
    CHECK_THROWS_AS(item.array_end(), type_error&);
    CHECK_THROWS_AS(item.table_begin(), type_error&);
    CHECK_THROWS_AS(item.table_end(), type_error&);
    CHECK_THROWS_AS(item.array_range(), type_error&);
    CHECK_THROWS_AS(item.table_range(), type_error&);
}

TEST_CASE("testing string item accessors") {
    item_t item(string_t{"abc"});

    CHECK(item.is_boolean() == false);
    CHECK(item.is_integer() == false);
    CHECK(item.is_float() == false);
    CHECK(item.is_string() == true);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == false);

    CHECK_THROWS_AS(item.get_boolean(), type_error&);
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

    CHECK_THROWS_AS(item.size(), type_error&);
    CHECK_THROWS_AS(item.empty(), type_error&);
    CHECK_THROWS_AS(item[0], type_error&);
    CHECK_THROWS_AS(item[""], type_error&);
    CHECK_THROWS_AS(item.contains(""), type_error&);
    CHECK_THROWS_AS(item.array_begin(), type_error&);
    CHECK_THROWS_AS(item.array_end(), type_error&);
    CHECK_THROWS_AS(item.table_begin(), type_error&);
    CHECK_THROWS_AS(item.table_end(), type_error&);
    CHECK_THROWS_AS(item.array_range(), type_error&);
    CHECK_THROWS_AS(item.table_range(), type_error&);
}

TEST_CASE("testing array item accessors") {
    auto ptr = std::make_shared<std::vector<item_t>>();
    ptr->push_back(item_t(true));
    ptr->push_back(item_t(static_cast<integer_t>(1)));
    ptr->push_back(item_t(1.5));
    ptr->push_back(item_t(string_t("abc")));
    item_t item(ptr);

    CHECK(item.is_boolean() == false);
    CHECK(item.is_integer() == false);
    CHECK(item.is_float() == false);
    CHECK(item.is_string() == false);
    CHECK(item.is_array() == true);
    CHECK(item.is_table() == false);

    CHECK_THROWS_AS(item.get_boolean(), type_error&);
    CHECK_THROWS_AS(item.get_integer(), type_error&);
    CHECK_THROWS_AS(item.get_float(), type_error&);
    CHECK_THROWS_AS(item.get_string(), type_error&);

    boolean_t b;
    CHECK(item.get(b) == false);
    integer_t i;
    CHECK(item.get(i) == false);
    float_t d;
    CHECK(item.get(d) == false);
    string_t s;
    CHECK(item.get(s) == false);

    CHECK(item.size() == 4);
    CHECK(item.empty() == false);
    CHECK(item[0].get_boolean() == true);
    CHECK(item[1].get_integer() == 1);
    CHECK(item[2].get_float() == 1.5);
    CHECK(item[3].get_string() == "abc");

    auto it = item.array_begin();
    auto end = item.array_end();
    CHECK(it != end);
    CHECK(it->get_boolean() == true);
    ++it;
    CHECK(it != end);
    CHECK(it->get_integer() == 1);
    ++it;
    CHECK(it != end);
    CHECK(it->get_float() == 1.5);
    ++it;
    CHECK(it != end);
    CHECK(it->get_string() == "abc");
    ++it;
    CHECK(it == end);

    int index = 0;
    for (auto it : item.array_range()) {
        if (index == 0) {
            CHECK(it.get_boolean() == true);
        } else if (index == 1) {
            CHECK(it.get_integer() == 1);
        } else if (index == 2) {
            CHECK(it.get_float() == 1.5);
        } else if (index == 3) {
            CHECK(it.get_string() == "abc");
        } else {
            CHECK(false);
        }

        index++;
    }

    CHECK_THROWS_AS(item[""], type_error&);
    CHECK_THROWS_AS(item.contains(""), type_error&);
    CHECK_THROWS_AS(item.table_begin(), type_error&);
    CHECK_THROWS_AS(item.table_end(), type_error&);
    CHECK_THROWS_AS(item.table_range(), type_error&);
}

TEST_CASE("testing table item accessors") {
    auto ptr = std::make_shared<std::map<tomload::key_t, item_t>>();
    ptr->insert({"1st", item_t(true)});
    ptr->insert({"2nd", item_t(static_cast<integer_t>(1))});
    ptr->insert({"3rd", item_t(1.5)});
    ptr->insert({"4th", item_t(string_t("abc"))});
    item_t item(ptr);

    CHECK(item.is_boolean() == false);
    CHECK(item.is_integer() == false);
    CHECK(item.is_float() == false);
    CHECK(item.is_string() == false);
    CHECK(item.is_array() == false);
    CHECK(item.is_table() == true);

    CHECK_THROWS_AS(item.get_boolean(), type_error&);
    CHECK_THROWS_AS(item.get_integer(), type_error&);
    CHECK_THROWS_AS(item.get_float(), type_error&);
    CHECK_THROWS_AS(item.get_string(), type_error&);

    boolean_t b;
    CHECK(item.get(b) == false);
    integer_t i;
    CHECK(item.get(i) == false);
    float_t d;
    CHECK(item.get(d) == false);
    string_t s;
    CHECK(item.get(s) == false);

    CHECK(item.size() == 4);
    CHECK(item.empty() == false);
    CHECK(item["1st"].get_boolean() == true);
    CHECK(item["2nd"].get_integer() == 1);
    CHECK(item["3rd"].get_float() == 1.5);
    CHECK(item["4th"].get_string() == "abc");

    auto it = item.table_begin();
    auto end = item.table_end();
    CHECK(it != end);
    CHECK(it->first == "1st");
    CHECK(it->second.get_boolean() == true);
    ++it;
    CHECK(it != end);
    CHECK(it->first == "2nd");
    CHECK(it->second.get_integer() == 1);
    ++it;
    CHECK(it != end);
    CHECK(it->first == "3rd");
    CHECK(it->second.get_float() == 1.5);
    ++it;
    CHECK(it != end);
    CHECK(it->first == "4th");
    CHECK(it->second.get_string() == "abc");
    ++it;
    CHECK(it == end);

    int index = 0;
    for (auto it : item.table_range()) {
        if (index == 0) {
            CHECK(it.first == "1st");
            CHECK(it.second.get_boolean() == true);
        } else if (index == 1) {
            CHECK(it.first == "2nd");
            CHECK(it.second.get_integer() == 1);
        } else if (index == 2) {
            CHECK(it.first == "3rd");
            CHECK(it.second.get_float() == 1.5);
        } else if (index == 3) {
            CHECK(it.first == "4th");
            CHECK(it.second.get_string() == "abc");
        } else {
            CHECK(false);
        }

        index++;
    }

    CHECK_THROWS_AS(item[0], type_error&);
    CHECK_THROWS_AS(item.array_begin(), type_error&);
    CHECK_THROWS_AS(item.array_end(), type_error&);
    CHECK_THROWS_AS(item.array_range(), type_error&);
}
