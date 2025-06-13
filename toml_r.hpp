#include <iostream>

#ifndef TOML_R_HPP
#define TOML_R_HPP

#include <memory>
#include <string>
#include <vector>
#include "integers.hpp"
#include "view_t.hpp"

struct item_t {
    enum type_t {
        TYPE_VOID = 0,
        TYPE_BOOL,
        TYPE_UINT,
        TYPE_VECTOR,
    } type = TYPE_VOID;

    bool b;
    u64 u;
    std::unique_ptr<std::vector<item_t>> v;
};

view_t::size_type get_radix_length(view_t view, view_t allowed) {
    view_t::size_type pos = view.find_first_not_of(allowed, 2);
    if (pos == view_t::npos) {
        pos = view.size() - 2;
    }
    return pos + 2;
}

u64 parse_radix_value(view_t view, view_t::size_type length, int base) {
    view_t sub(view.data() + 2, length - 2);
    if ((starts_with(sub, "_")) ||
        (ends_with(sub, "_")) ||
        (sub.find("__") != view_t::npos)) {
        return 0;
    }

    std::string str;
    for (char c : sub) {
        if (c != '_') {
            str.push_back(c);
        }
    }

    return std::stoull(str.c_str(), nullptr, base);
}

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
    } else if (starts_with(view, "0x")) {
        view_t::size_type length = get_radix_length(view, "0123456789ABCDEFabcdef_");
        u64 u = parse_radix_value(view, length, 16);

        ret.type = item_t::TYPE_UINT;
        ret.u = u;
        view.remove_prefix(length);
    } else if (starts_with(view, "0o")) {
        view_t::size_type length = get_radix_length(view, "01234567_");
        u64 u = parse_radix_value(view, length, 8);

        ret.type = item_t::TYPE_UINT;
        ret.u = u;
        view.remove_prefix(length);
    } else if (starts_with(view, "0b")) {
        view_t::size_type length = get_radix_length(view, "01_");
        u64 u = parse_radix_value(view, length, 2);

        ret.type = item_t::TYPE_UINT;
        ret.u = u;
        view.remove_prefix(length);
    }

    return ret;
}

#endif  // TOML_R_HPP
