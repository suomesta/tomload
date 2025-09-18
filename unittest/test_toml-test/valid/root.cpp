#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "tomload/tomload.h"

namespace {

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(TOML_TEST_DIR) + filename);
    if (not file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

struct rhs_nan {};
bool operator==(tomload::float_t f, rhs_nan) {
    return std::isnan(f);
}

}  // namespace

using namespace tomload;

TEST_CASE("valid/empty-crlf.toml") {
    std::string content = load_file("valid/empty-crlf.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

TEST_CASE("valid/empty-lf.toml") {
    std::string content = load_file("valid/empty-lf.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

TEST_CASE("valid/empty-nothing.toml") {
    std::string content = load_file("valid/empty-nothing.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

TEST_CASE("valid/empty-space.toml") {
    std::string content = load_file("valid/empty-space.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

TEST_CASE("valid/empty-tab.toml") {
    std::string content = load_file("valid/empty-tab.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 0);
}

TEST_CASE("valid/implicit-and-explicit-after.toml") {
    std::string content = load_file("valid/implicit-and-explicit-after.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 2);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 1);
    CHECK(t["a"]["b"]["c"].is_table() == true);
    CHECK(t["a"]["b"]["c"].size() == 1);
    CHECK(t["a"]["b"]["c"]["answer"].is_integer() == true);
    CHECK(t["a"]["b"]["c"]["answer"].get_integer() == 42);
    CHECK(t["a"]["better"].is_integer() == true);
    CHECK(t["a"]["better"].get_integer() == 43);
}

TEST_CASE("valid/implicit-and-explicit-before.toml") {
    std::string content = load_file("valid/implicit-and-explicit-before.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 2);
    CHECK(t["a"]["better"].is_integer() == true);
    CHECK(t["a"]["better"].get_integer() == 43);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 1);
    CHECK(t["a"]["b"]["c"].is_table() == true);
    CHECK(t["a"]["b"]["c"].size() == 1);
    CHECK(t["a"]["b"]["c"]["answer"].is_integer() == true);
    CHECK(t["a"]["b"]["c"]["answer"].get_integer() == 42);
}

TEST_CASE("valid/implicit-groups.toml") {
    std::string content = load_file("valid/implicit-groups.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["a"].is_table() == true);
    CHECK(t["a"].size() == 1);
    CHECK(t["a"]["b"].is_table() == true);
    CHECK(t["a"]["b"].size() == 1);
    CHECK(t["a"]["b"]["c"].is_table() == true);
    CHECK(t["a"]["b"]["c"].size() == 1);
    CHECK(t["a"]["b"]["c"]["answer"].is_integer() == true);
    CHECK(t["a"]["b"]["c"]["answer"].get_integer() == 42);
}

TEST_CASE("valid/multibyte.toml") {
    std::string content = load_file("valid/multibyte.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 1);
    CHECK(t["𝐭𝐛𝐥"].is_table() == true);
    CHECK(t["𝐭𝐛𝐥"].size() == 2);
    CHECK(t["𝐭𝐛𝐥"]["string"].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["string"].get_string() == "𝓼𝓽𝓻𝓲𝓷𝓰 - #");
    CHECK(t["𝐭𝐛𝐥"]["sub"].is_table() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"].size() == 5);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪"].is_array() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪"].size() == 2);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪"][0].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪"][0].get_string() == "] ");
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪"][1].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪"][1].get_string() == " # ");
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪𝟚"].is_array() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪𝟚"].size() == 2);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪𝟚"][0].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪𝟚"][0].get_string() == "Tèƨƭ #11 ]ƥřôƲèδ ƭλáƭ");
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪𝟚"][1].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["𝕒𝕣𝕣𝕒𝕪𝟚"][1].get_string() == "Éжƥèřï₥èñƭ #9 ωáƨ á ƨúççèƨƨ");
    CHECK(t["𝐭𝐛𝐥"]["sub"]["another_test_string"].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["another_test_string"].get_string() == "§á₥è ƭλïñϱ, βúƭ ωïƭλ á ƨƭřïñϱ #");
    CHECK(t["𝐭𝐛𝐥"]["sub"]["escapes"].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["escapes"].get_string() == " Âñδ ωλèñ \"'ƨ ářè ïñ ƭλè ƨƭřïñϱ, áℓôñϱ ωïƭλ # \"");
    CHECK(t["𝐭𝐛𝐥"]["sub"]["βïƭ#"].is_table() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["βïƭ#"].size() == 2);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["βïƭ#"]["ωλáƭ?"].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["βïƭ#"]["ωλáƭ?"].get_string() == "Ýôú δôñ'ƭ ƭλïñƙ ƨô₥è úƨèř ωôñ'ƭ δô ƭλáƭ?");
    CHECK(t["𝐭𝐛𝐥"]["sub"]["βïƭ#"]["multi_line_array"].is_array() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["βïƭ#"]["multi_line_array"].size() == 1);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["βïƭ#"]["multi_line_array"][0].is_string() == true);
    CHECK(t["𝐭𝐛𝐥"]["sub"]["βïƭ#"]["multi_line_array"][0].get_string() == "]");
}

TEST_CASE("valid/newline-crlf.toml") {
    std::string content = load_file("valid/newline-crlf.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["os"].is_string() == true);
    CHECK(t["os"].get_string() == "DOS");
    CHECK(t["newline"].is_string() == true);
    CHECK(t["newline"].get_string() == "crlf");
}

TEST_CASE("valid/newline-lf.toml") {
    std::string content = load_file("valid/newline-lf.toml");
    item_t t{content.c_str()};

    CHECK(t.is_table() == true);
    CHECK(t.size() == 2);
    CHECK(t["os"].is_string() == true);
    CHECK(t["os"].get_string() == "unix");
    CHECK(t["newline"].is_string() == true);
    CHECK(t["newline"].get_string() == "lf");
}

