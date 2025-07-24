#include "parser.h"
#include "detail_number.h"
#include "detail_string.h"

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

    if (starts_with(view, "0x")) {
        view_t::size_type length = get_radix_length(view, "0123456789ABCDEFabcdef_");
        integer_t i = parse_radix_value(view, length, 16);

        view.remove_prefix(length);
        return item_t{i};
    } else if (starts_with(view, "0o")) {
        view_t::size_type length = get_radix_length(view, "01234567_");
        integer_t i = parse_radix_value(view, length, 8);

        view.remove_prefix(length);
        return item_t{i};
    } else if (starts_with(view, "0b")) {
        view_t::size_type length = get_radix_length(view, "01_");
        integer_t i = parse_radix_value(view, length, 2);

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

}  // namespace tomload
