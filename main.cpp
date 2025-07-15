#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
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
        CHECK(result.get_bool() == true);
        CHECK(src.empty());
    }
    {
        view_t src = "false";
        item_t result = parse_item(src);

        CHECK(result.is_bool() == true);
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

TEST_CASE("testing parse_item(uint)") {
    {
        view_t src = "0xF_f";
        item_t result = parse_item(src);

        CHECK(result.is_uint() == true);
        CHECK(result.get_uint() == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "0o77_7";
        item_t result = parse_item(src);

        CHECK(result.is_uint() == true);
        CHECK(result.get_uint() == 511UL);
        CHECK(src.empty());
    }
    {
        view_t src = "0b11110000";
        item_t result = parse_item(src);

        CHECK(result.is_uint() == true);
        CHECK(result.get_uint() == 240UL);
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
        CHECK(result[0].is_uint() == true);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff,]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 1);
        CHECK(result[0].is_uint() == true);
        CHECK(result[0].get_uint() == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff , ]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 1);
        CHECK(result[0].is_uint() == true);
        CHECK(result[0].get_uint() == 255UL);
        CHECK(src.empty());
    }
    {
        view_t src = "[0xff,true]";
        item_t result = parse_item(src);

        CHECK(result.is_array() == true);
        CHECK(result.size() == 2);
        CHECK(result[0].is_uint() == true);
        CHECK(result[0].get_uint() == 255UL);
        CHECK(result[1].is_bool() == true);
        CHECK(result[1].get_bool() == true);
        CHECK(src.empty());
        for (item_t::array_iterator i = result.array_begin(); i != result.array_end(); ++i) {
            if (std::distance(result.array_begin(), i) == 0) {
                CHECK(i->is_uint() == true);
                CHECK(i->get_uint() == 255UL);
            } else if (std::distance(result.array_begin(), i) == 1) {
                CHECK(i->is_bool() == true);
                CHECK(i->get_bool() == true);
            }
        }
        int i = 0;
        for (auto r : result.array_range()) {
            if (i == 0) {
                CHECK(r.is_uint() == true);
                CHECK(r.get_uint() == 255UL);
            } else if (i == 1) {
                CHECK(r.is_bool() == true);
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
        CHECK(result[0].is_uint() == true);
        CHECK(result[0].get_uint() == 255UL);
        CHECK(result[1].is_bool() == true);
        CHECK(result[1].get_bool() == true);
        CHECK(src.empty());
    }
}

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(TEST_DATA_DIR) + filename);
    if (not file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

TEST_CASE("testing parse()") {
    {
        view_t src = "[aa]  #comm\n";
        item_t result = parse(src);

        CHECK(result.is_table() == true);
        CHECK(result.size() == 0);
        CHECK(src.empty());
    }
    {
        view_t src = "[aa]  #comm\nbb = false\n";
        item_t result = parse(src);

        CHECK(result.is_table() == true);
        CHECK(result.size() == 1);
        CHECK(result.contains("aa") == true);
        CHECK(result["aa"]["bb"].is_bool() == true);
        CHECK(result["aa"]["bb"].get_bool() == false);
        CHECK(src.empty());
    }
    {
        std::string content = load_file("Boolean_1.toml");
        view_t src{content.c_str()};
        item_t t = parse(src);

        CHECK(t.is_table() == true);
        CHECK(t.size() == 2);
        CHECK(t["bool1"].is_bool() == true);
        CHECK(t["bool1"].get_bool() == true);
        CHECK(t["bool2"].is_bool() == true);
        CHECK(t["bool2"].get_bool() == false);
    }
}
