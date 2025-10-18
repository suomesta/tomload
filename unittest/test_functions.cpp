// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

/*
 * @file unittest/test_functions.cpp
 * @brief testing some functions regarding item_t using doctest.
 * @note target version of C++ is C++14. 
 */

#include <cmath>
#include <iterator>
#include <doctest/doctest.h>
#include "tomload/tomload.h"
#include "tomload/parser.h"
#include "tomload/view_t.h"

using tomload::item_t;
using tomload::view_t;

TEST_CASE("testing tomload::skip_space()") {
    {
        view_t src = "true";
        tomload::skip_space(src, " \t\r\n", false);

        CHECK(src == "true");
    }
    {
        view_t src = "\n\r\t true";
        tomload::skip_space(src, " \t\r\n", false);

        CHECK(src == "true");
    }
    {
        view_t src = "  # comment \r\n true";
        tomload::skip_space(src, " \t\r\n", true);

        CHECK(src == "true");
    }
    {
        view_t src = "  \n \t";
        tomload::skip_space(src, " \t\r\n", true);

        CHECK(src == "");
    }
    {
        view_t src = "  # \t";
        tomload::skip_space(src, " \t\r\n", true);

        CHECK(src == "");
    }
}

TEST_CASE("testing tomload::item_t::item_t()") {
    {
        item_t result("[aa]  #comm\n");

        CHECK(result.is_table() == true);
        CHECK(result.size() == 1);
        CHECK(result.contains("aa") == true);
        CHECK(result["aa"].is_table() == true);
        CHECK(result["aa"].size() == 0);
    }
    {
        item_t result("[aa]  #comm\nbb = false\n");

        CHECK(result.is_table() == true);
        CHECK(result.size() == 1);
        CHECK(result.contains("aa") == true);
        CHECK(result["aa"]["bb"].is_boolean() == true);
        CHECK(result["aa"]["bb"].get_boolean() == false);
    }
    {
        const char src[] = "[a.b.c.d]\n  z = 9\n\n[a]\n  b.c.d.k.t = \"Using dotted keys to add to [a.b.c.d] after explicitly defining it above is not allowed\"\n";

        CHECK_THROWS_AS((item_t(src)), tomload::parse_error&);
    }
}

