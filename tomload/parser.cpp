// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

/*
 * @file tomload/parser.cpp
 * @note target version of C++ is C++14. 
 */

#include "tomload/parser.h"
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include "tomload/detail_number.h"
#include "tomload/detail_string.h"

namespace tomload {

/**
 * @brief Checks a string for disallowed control characters and single carriage returns.
 *
 * @param view The input string to be checked.
 * @throw parse_error If any of the following characters or sequences are detected:
 *        - Control characters in the range 0x00 to 0x08 (including NULL and BS, excluding HT).
 *        - Control characters 0x0B (VT) and 0x0C (FF).
 *        - Control characters in the range 0x0E to 0x1F (including SO and US, excluding LF and CR).
 *        - The DEL character (0x7F).
 *        - A solitary Carriage Return (CR, \r) that is not immediately followed by a Line Feed (\n).
 * * @note This check specifically permits only the Horizontal Tab (HT: 0x09) and 
 *         Line Feed (LF: 0x0A) as control characters, and allows CR (0x0D) only 
 *         as part of the standard CR+LF (\r\n) sequence.
 */
void check_control_character(view_t view) {
    for (char c : view) {
        if (('\x00' <= c && c <= '\x08') ||
            ('\x0b' <= c && c <= '\x0c') ||
            ('\x0e' <= c && c <= '\x1f') ||
            (c == '\x7f')) {
                throw parse_error("detect disallowed character");
        }
    }

    for (view_t::size_type i = 0; i < view.size(); ++i) {
        if ((view[i] == '\r') &&
            ((i + 1 == view.size()) || (view[i + 1] != '\n'))) {
            throw parse_error("detect single CR");
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks for a newline at the beginning of the input view.
 *
 * This function skips leading whitespace characters (`' '`, `'\t'`, `'\r'`) and comments in the input view.
 *
 * @param view[in,out]: A reference to the input view to be examined and potentially modified.
 * @return true if a newline was found and handled; false otherwise.
 */
bool wait_newline(view_t& view) {
    skip_space(view, " \t\r", false);
    if (view.empty()) {
        return true;
    } else if (starts_with(view, "\n")) {
        view.remove_prefix(1);
        return true;
    } else if (starts_with(view, "#")) {
        view_t::size_type lf_pos = view.find('\n');
        view.remove_prefix((lf_pos != view_t::npos) ? lf_pos : view.size());
        return true;
    } else {
        return false;
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief Skips leading whitespace and optionally comments in the input view.
 *
 * This function removes leading characters from the input view that match any character
 * in the `spaces` set. If `skip_comment` is true and the view starts with a comment
 * character (`'#'`), it removes all characters up to and including the next newline.
 * The function may call itself recursively if a comment is removed and further whitespace
 * or comments may follow.
 *
 * @param view[in,out]: A reference to the input view to be modified.
 * @param spaces[in]: A set of characters considered as whitespace (e.g., " \t\r").
 * @param skip_comment[in]: If true, lines starting with '#' are treated as comments and skipped.
 */
void skip_space(view_t& view, view_t spaces, bool skip_comment) {
    view_t::size_type pos = view.find_first_not_of(spaces);
    view.remove_prefix((pos != view_t::npos) ? pos : view.size());

    if (skip_comment && starts_with(view, "#")) {
        view_t::size_type lf_pos = view.find('\n');
        view.remove_prefix((lf_pos != view_t::npos) ? lf_pos : view.size());

        // go to recurrsive call, because current `view` may start with `spaces`
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
        skip_space(view, " \t\r\n", true);

        if (view.empty()) {
            throw parse_error("missing \"]\" in array");
        } else if (starts_with(view, "]")) {
            view.remove_prefix(1);
            status = closed;
        } else if (status == wait_item) {
            v->push_back(parse_item(view));
            status = wait_comma;
        } else if (status == wait_comma) {
            skip_space(view, " \t\r\n", true);
            if (view.empty()) {
                throw parse_error("missing \",\" or \"]\" in array");
            } else if (starts_with(view, ",")) {
                view.remove_prefix(1);
                status = wait_item;
            } else {
                throw parse_error("missing \",\" or \"]\" in array");
            }
        } else {
            throw parse_error("unknown error");
        }
    }

    return item_t{single_construct, v};
}
/////////////////////////////////////////////////////////////////////////////

item_t parse_inline_table(view_t& view) {
    item_t ret{single_construct, std::make_shared<std::map<key_t, item_t>>()};

    view.remove_prefix(1);

    std::vector<key_t> keys;
    std::vector<std::pair<std::vector<key_t>, item_t>> key_vals;

    enum {
        wait_key,
        wait_equal,
        wait_value,
        wait_comma,
        closed,
    } status = wait_key;

    while (status != closed) {
        skip_space(view, " \t", false);

        if (view.empty()) {
            throw parse_error("imcomplete inline table");
        } else if (starts_with(view, "}")) {
            if (((status == wait_key) && key_vals.empty()) ||
                (status == wait_comma)) {
                view.remove_prefix(1);
                status = closed;
            } else {
                throw parse_error("imcomplete inline table");
            }
        } else if (status == wait_key) {
            keys = parse_keys(view);
            status = wait_equal;
        } else if (status == wait_equal) {
            if (starts_with(view, "=")) {
                view.remove_prefix(1);
                status = wait_value;
            } else {
                throw parse_error("missing \"=\" in inline table");
            }
        } else if (status == wait_value) {
            key_vals.emplace_back(std::move(keys), parse_item(view));
            status = wait_comma;
        } else if (status == wait_comma) {
            if (starts_with(view, ",")) {
                view.remove_prefix(1);
                status = wait_key;
            } else {
                throw parse_error("missing \",\" or \"}\" in array");
            }
        } else {
            throw parse_error("unknown error");
        }
    }

    ret.set_inline_table_keys_value(std::move(key_vals));

    return ret;
}
/////////////////////////////////////////////////////////////////////////////

item_t parse_item(view_t& view) {
    const std::pair<view_t, item_t> fixed_values[8] = {
        {"true", item_t{single_construct, true}},
        {"false", item_t{single_construct, false}},
        {"inf", item_t{single_construct, std::numeric_limits<double>::infinity()}},
        {"+inf", item_t{single_construct, std::numeric_limits<double>::infinity()}},
        {"-inf", item_t{single_construct, -std::numeric_limits<double>::infinity()}},
        {"nan", item_t{single_construct, std::numeric_limits<double>::quiet_NaN()}},
        {"+nan", item_t{single_construct, std::numeric_limits<double>::quiet_NaN()}},
        {"-nan", item_t{single_construct, std::numeric_limits<double>::quiet_NaN()}},
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
        return item_t{single_construct, i};
    } else if (starts_with(view, {"+", "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})) {
        view_t::size_type integer_length = get_integer_length(view);
        view_t::size_type float_length = get_float_length(view);
        if (float_length > integer_length) {
            float_t d = parse_float(view, float_length);

            view.remove_prefix(float_length);
            return item_t{single_construct, d};
        } else {
            integer_t i = parse_integer(view, integer_length);

            view.remove_prefix(integer_length);
            return item_t{single_construct, i};
        }
    } else if (starts_with(view, "'''")) {
        view_t::size_type length = get_multi_literal_string_length(view);
        string_t str = parse_multi_literal_string(view, length);

        view.remove_prefix(length);
        return item_t{single_construct, std::move(str)};
    } else if (starts_with(view, "'")) {
        view_t::size_type length = get_literal_string_length(view);
        string_t str = parse_literal_string(view, length);

        view.remove_prefix(length);
        return item_t{single_construct, std::move(str)};
    } else if (starts_with(view, "\"\"\"")) {
        view_t::size_type length = get_multi_string_length(view);
        string_t str = parse_multi_string(view, length);

        view.remove_prefix(length);
        return item_t{single_construct, std::move(str)};
    } else if (starts_with(view, "\"")) {
        view_t::size_type length = get_string_length(view);
        string_t str = parse_string(view, length);

        view.remove_prefix(length);
        return item_t{single_construct, std::move(str)};
    } else if (starts_with(view, "[")) {
        return parse_array(view);
    } else if (starts_with(view, "{")) {
        return parse_inline_table(view);
    } else {
        throw parse_error("not hit item");
    }
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

void check_duplex_keys(const std::vector<key_t>& keys, const std::vector<std::vector<key_t>>& brackets_set) {
// # See: https://github.com/toml-lang/toml/issues/846
// #      https://github.com/toml-lang/toml/pull/859
    if (not brackets_set.empty()) {
        std::vector<std::vector<key_t>>::const_iterator begin = brackets_set.cbegin();
        std::vector<std::vector<key_t>>::const_iterator end = brackets_set.cend() - 1;
        const std::vector<key_t>& lastst = brackets_set.back();

        for (decltype(begin) it = begin; it != end; ++it) {
            if ((lastst.size() < it->size()) &&
                std::equal(lastst.cbegin(), lastst.cend(), it->cbegin()) &&
                (it->size() < (lastst.size() + keys.size())) &&
                std::equal(it->cbegin() + lastst.size(), it->cend(), keys.cbegin())) {
                throw parse_error("found duplex key");
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload
