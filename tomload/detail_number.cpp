// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

/*
 * @file tomload/detail_number.cpp
 * @note target version of C++ is C++14. 
 */

#include "tomload/detail_number.h"
#include <algorithm>
#include <string>

namespace tomload {

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
view_t::size_type get_radix_length(view_t view) {
    view_t allowed = starts_with(view, "0x") ? "0123456789ABCDEFabcdef_" :
                          starts_with(view, "0o") ? "01234567_" :
                          starts_with(view, "0b") ? "01_" : "";

    view_t::size_type pos = view.find_first_not_of(allowed, 2);
    return (pos != view_t::npos) ? pos : view.size();
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
integer_t parse_radix_value(view_t view, view_t::size_type length) {
    int base = starts_with(view, "0x") ? 16 :
                          starts_with(view, "0o") ? 8 :
                          starts_with(view, "0b") ? 2 : 10;

    view_t sub(view.data() + 2, length - 2);
    if (starts_with(sub, "_") ||
        ends_with(sub, "_") ||
        contains(sub, "__")) {
        throw parse_error("invalid `_`");
    }

    std::string str;
    std::copy_if(sub.begin(), sub.end(), std::back_inserter(str),
                 [](char c) { return c != '_'; });

    try {
        return std::stoll(str, nullptr, base);
    } catch (std::out_of_range& err) {
        throw parse_error("out_of_range");
    } catch (std::invalid_argument& err) {
        throw parse_error("invalid_argument");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
view_t::size_type get_integer_length(view_t view) {
    view_t::size_type pos = view.find_first_not_of("0123456789_", 1);
    return (pos != view_t::npos) ? pos : view.size();
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
integer_t parse_integer(view_t view, view_t::size_type length) {
    view_t sub(view.data(), length);
    if (starts_with(sub, {"_", "+_", "-_"}) ||
        ends_with(sub, "_") ||
        contains(sub, "__")) {
        throw parse_error("invalid `_`");
    }

    std::string str;
    std::copy_if(sub.begin(), sub.end(), std::back_inserter(str),
                 [](char c) { return c != '_'; });

    view_t ref{str.c_str()};
    if (starts_with(ref, {"+", "-"})) {
        ref.remove_prefix(1);
    }
    if (starts_with(ref, "0") && (ref.size() > 1)) {
        throw parse_error("starts with 0");
    }

    try {
        return std::stoll(str, nullptr, 10);
    } catch (std::out_of_range& err) {
        throw parse_error("out_of_range");
    } catch (std::invalid_argument& err) {
        throw parse_error("invalid_argument");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
view_t::size_type get_float_length(view_t view) {
    view_t::size_type pos = get_integer_length(view);

    if (pos < view.size() && view[pos] == '.') {
        pos++;

        view_t::size_type decimal_pos = view.find_first_not_of("0123456789_", pos);
        if (decimal_pos == pos) {
            throw parse_error("must digit after '.'");
        }
        pos = (decimal_pos != view_t::npos) ? decimal_pos : view.size();
    }

    if (pos < view.size() && (view[pos] == 'e' || view[pos] == 'E')) {
        pos++;

        if (pos < view.size() && (view[pos] == '+' || view[pos] == '-')) {
            pos++;
        }
        view_t::size_type expo_pos = view.find_first_not_of("0123456789_", pos);
        if (expo_pos == pos) {
            throw parse_error("must digit after 'e' or 'E'");
        }
        pos = (expo_pos != view_t::npos) ? expo_pos : view.size();
    }

    return pos;
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
float_t parse_float(view_t view, view_t::size_type length) {
    view_t sub(view.data(), length);
    if (starts_with(sub, "_") ||
        ends_with(sub, "_") ||
        contains(sub, {"__", "+_", "_+", "-_", "_-", "._", "_.", "e_", "_e", "E_", "_E"})) {
        throw parse_error("invalid `_`");
    }

    std::string str;
    std::copy_if(sub.begin(), sub.end(), std::back_inserter(str),
                 [](char c) { return c != '_'; });

    view_t ref{str.c_str()};
    if (starts_with(ref, {"+", "-"})) {
        ref.remove_prefix(1);
    }
    if (starts_with(ref, "0") && not starts_with(ref, {"0.", "0e", "0E"})) {
        throw parse_error("starts with 0");
    }
    if (starts_with(ref, {".", "e", "E"})) {
        throw parse_error("missing integer digits");
    }

    try {
        return std::stod(str, nullptr);
    } catch (std::out_of_range& err) {
        throw parse_error("out_of_range");
    } catch (std::invalid_argument& err) {
        throw parse_error("invalid_argument");
    }
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload
