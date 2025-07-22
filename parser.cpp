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
    view_t backup(view);

    view.remove_prefix(1);

    item_t tmp_vector{make_array};

    enum {
        wait_item,
        wait_comma,
        closed,
    } status = wait_item;

    while (status != closed) {
        skip_space(view, " \t\r\n", false);

        if (starts_with(view, "]")) {
            view.remove_prefix(1);
            status = closed;
        } else if (status == wait_item) {
            tmp_vector.v->push_back(parse_item(view));
            status = wait_comma;
        } else {
            if (starts_with(view, ",")) {
                view.remove_prefix(1);
                status = wait_item;
            } else {
                view = backup;
                return {};
            }
        }
    }

    return tmp_vector;
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

void insert_table(item_t& root, item_t& item, const std::vector<key_t>& brackets, const std::vector<key_t>& keys) {
    std::map<key_t, item_t>* mptr = root.m.get();
    for (const key_t& key : brackets) {
        mptr->insert({key, item_t{make_table}});
        mptr = mptr->find(key)->second.m.get();
    }
    for (const key_t& key : keys) {
        if (&key != &keys.back()) {
            mptr->insert({key, item_t{make_table}});
            mptr = mptr->find(key)->second.m.get();
        } else {
            mptr->insert({key, item_t{}});
            mptr->find(key)->second = std::move(item);
        }
        
    }
}

void parse_main(item_t& root, view_t& view) {
    std::vector<key_t> brackets;
    std::vector<key_t> keys;

    enum {
        start,
        bracket_wait_string,
        bracket_wait_dot,
        bracket_wait_newline,
        pair_wait_dot,
        pair_wait_value,
        pair_wait_newline,
        completed,
    } status = start;

    while (status != completed) {
        if (status == start) {
            skip_space(view, " \t\r\n", true);
            if (view.empty()) {
                status = completed;
            } else if (starts_with(view, "[")) {
                brackets.clear();
                status = bracket_wait_string;
                view.remove_prefix(1);
            } else if (view_t("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-").find(view_t(view.data(), 1)) != view_t::npos) {
                keys.clear();
                view_t::size_type length = get_bare_length(view);
                key_t s = parse_bare_value(view, length);

                status = pair_wait_dot;
                keys.push_back(std::move(s));
                view.remove_prefix(length);
            } else {
                ;
            }
        } else if (status == bracket_wait_string) {
            skip_space(view, " \t", false);
            if (view.empty()) {
                ;
            } else if (starts_with(view, "]")) {
                status = bracket_wait_newline;
                view.remove_prefix(1);
            } else if (view_t("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-").find(view_t(view.data(), 1)) != view_t::npos) {
                view_t::size_type length = get_bare_length(view);
                key_t s = parse_bare_value(view, length);

                brackets.push_back(std::move(s));
                view.remove_prefix(length);
            } else {
                ;
            }
        } else if (status == bracket_wait_newline) {
            if (wait_newline(view)) {
                status = start;
            }
        } else if (status == pair_wait_dot) {
            skip_space(view, " \t", false);
            if (view.empty()) {
                ;
            } else if (starts_with(view, "=")) {
                status = pair_wait_value;
                view.remove_prefix(1);
            } else {
                ;
            }
        } else if (status == pair_wait_value) {
            skip_space(view, " \t", false);
            item_t item = parse_item(view);
            insert_table(root, item, brackets, keys);
            status = pair_wait_newline;
        } else if (status == pair_wait_newline) {
            if (wait_newline(view)) {
                status = start;
            } else {
                break;
            }
        } else {
            if (view.empty()) {
                break;
            }
        }
    }
}

}  // namespace tomload
