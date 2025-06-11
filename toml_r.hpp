
#ifndef TOML_R_HPP
#define TOML_R_HPP

#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using view_t = std::string_view;

bool starts_with(view_t view, view_t x) {
    return view.find(x) == 0;
}

static_assert(sizeof(long long) == sizeof(i64), "sizeof(long long) must be 8");
static_assert(sizeof(unsigned long long) == sizeof(u64), "sizeof(unsigned long long) must be 8");

struct item_t {
    enum type_t {
        TYPE_VOID = 0,
        TYPE_BOOL,
        TYPE_UINT,
        TYPE_VECTOR,
    } type;

    bool b;
    u64 u;
    std::unique_ptr<std::vector<item_t>> v;
};

item_t parse_item(view_t& view) {
    item_t ret = {item_t::TYPE_VOID};

    while (starts_with(view, " ") ||
           starts_with(view, "\t") ||
           starts_with(view, "\r") ||
           starts_with(view, "\n")) {
        view.remove_prefix(1);
    }

    if (starts_with(view, "true")) {
        ret.type = item_t::TYPE_BOOL;
        ret.b = true;
        view.remove_prefix(4);
    } else if (starts_with(view, "false")) {
        ret.type = item_t::TYPE_BOOL;
        ret.b = false;
        view.remove_prefix(5);
    }

    return ret;
}

#endif  // TOML_R_HPP
