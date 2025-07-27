#include "tomload/parser.h"
#include "tomload/detail_number.h"
#include "tomload/detail_string.h"

namespace tomload {

bool wait_newline(view_t& view) {
    skip_space(view, " \t\r", false);
    if (view.empty()) {
        return true;
    } else if (starts_with(view, "\n")) {
        view.remove_prefix(1);
        return true;
    } else if (starts_with(view, "#")) {
        view_t::size_type lf_pos = view.find('\n');
        if (lf_pos == view_t::npos) {
            view = view_t{};
        } else {
            view.remove_prefix(lf_pos);
        }
        return true;
    } else {
        return false;
    }
}
/////////////////////////////////////////////////////////////////////////////

void skip_space(view_t& view, view_t spaces, bool skip_comment) {
    bool go_recurrsive = false;

    view_t::size_type pos = view.find_first_not_of(spaces);
    if (pos == view_t::npos) {
        view = view_t{};
    } else if (pos > 0) {
        view.remove_prefix(pos);
        go_recurrsive = true;
    }

    if (skip_comment) {
        if (starts_with(view, "#")) {
            view_t::size_type lf_pos = view.find('\n');
            if (lf_pos == view_t::npos) {
                view = view_t{};
            } else {
                view.remove_prefix(lf_pos);
                go_recurrsive = true;
            }
        }
    }

    if (go_recurrsive) {
        skip_space(view, spaces, skip_comment);
    }
}
/////////////////////////////////////////////////////////////////////////////

item_t parse_array(view_t& view) {
    std::shared_ptr<std::vector<item_t>> v = std::make_shared<std::vector<item_t>>();

    view.remove_prefix(1);

    enum {
        wait_item,
        wait_comma,
        closed,
    } status = wait_item;

    while (status != closed) {
        skip_space(view, " \t\r\n", false);

        if (view.empty()) {
            throw parse_error("missing \"]\" in array");
        } else if (starts_with(view, "]")) {
            view.remove_prefix(1);
            status = closed;
        } else if (status == wait_item) {
            v->push_back(parse_item(view));
            status = wait_comma;
        } else if (status == wait_comma) {
            skip_space(view, " \t\r\n", false);
            if (view.empty()) {
                throw parse_error("missing \",\" in array");
            } else if (starts_with(view, ",")) {
                view.remove_prefix(1);
                status = wait_item;
            } else {
                throw parse_error("missing \",\" in array");
            }
        } else {
            throw parse_error("unknown error");
        }
    }

    return item_t{v};
}
/////////////////////////////////////////////////////////////////////////////

item_t parse_item(view_t& view) {
    const std::pair<view_t, item_t> fixed_values[8] = {
        {"true", item_t{true}},
        {"false", item_t{false}},
        {"inf", item_t{std::numeric_limits<double>::infinity()}},
        {"+inf", item_t{std::numeric_limits<double>::infinity()}},
        {"-inf", item_t{-std::numeric_limits<double>::infinity()}},
        {"nan", item_t{std::numeric_limits<double>::quiet_NaN()}},
        {"+nan", item_t{std::numeric_limits<double>::quiet_NaN()}},
        {"-nan", item_t{-std::numeric_limits<double>::quiet_NaN()}},
    };

    for (const auto& pair : fixed_values) {
        if (starts_with(view, pair.first)) {
            view.remove_prefix(pair.first.size());
            return pair.second;
        }
    }

    if (starts_with(view, {"0x", "0o", "0b"})) {
        view_t::size_type length = get_radix_length(view);
        integer_t i = parse_radix_value(view, length);

        view.remove_prefix(length);
        return item_t{i};
    } else if (starts_with(view, "'''")) {
        view_t::size_type length = get_multi_literal_string_length(view);
        string_t str = parse_multi_literal_string(view, length);

        view.remove_prefix(length);
        return item_t{std::move(str)};
    } else if (starts_with(view, "'")) {
        view_t::size_type length = get_literal_string_length(view);
        string_t str = parse_literal_string(view, length);

        view.remove_prefix(length);
        return item_t{std::move(str)};
    } else if (starts_with(view, "\"\"\"")) {
        view_t::size_type length = get_multi_string_length(view);
        string_t str = parse_multi_string(view, length);

        view.remove_prefix(length);
        return item_t{std::move(str)};
    } else if (starts_with(view, "\"")) {
        view_t::size_type length = get_string_length(view);
        string_t str = parse_string(view, length);

        view.remove_prefix(length);
        return item_t{std::move(str)};
    } else if (starts_with(view, "[")) {
        return parse_array(view);
    }

    throw parse_error("not hit item");
}
/////////////////////////////////////////////////////////////////////////////

std::vector<key_t> parse_keys(view_t& view) {
    std::vector<std::string> keys;

    bool wait_dot = false;

    for (;;) {
        skip_space(view, " \t", false);

        if (not wait_dot) {
            if (view.empty()) {
                throw parse_error("unexpected end of input");
            } else if (view_t("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-").find(view[0]) != view_t::npos) {
                view_t::size_type length = get_bare_length(view);
                key_t s = parse_bare_value(view, length);

                view.remove_prefix(length);
                keys.push_back(std::move(s));
                wait_dot = true;
            } else if (starts_with(view, "'")) {
                view_t::size_type length = get_literal_string_length(view);
                key_t s = parse_literal_string(view, length);
 
                view.remove_prefix(length);
                keys.push_back(std::move(s));
                wait_dot = true;
            } else if (starts_with(view, "\"")) {
                view_t::size_type length = get_string_length(view);
                key_t s = parse_string(view, length);

                view.remove_prefix(length);
                keys.push_back(std::move(s));
                wait_dot = true;
            } else {
                throw parse_error("expected string");
            }
        } else {
            if (view.empty()) {
                break;
            } else if (starts_with(view, ".")) {
                view.remove_prefix(1);
                wait_dot = false;
            } else {
                break;
            }
        }
    }
    if (keys.empty()) {
        throw parse_error("no keys found");
    }
    return keys;
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload
