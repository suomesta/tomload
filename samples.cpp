#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "toml_r.hpp"

namespace {

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(TEST_DATA_DIR) + filename);
    if (not file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

}  // namespace

TEST_CASE("Boolean_1.toml") {
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
