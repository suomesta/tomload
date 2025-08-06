#include "tomload/detail_number.h"

namespace tomload {

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
view_t::size_type get_radix_length(view_t view) {
    view_t allowed = starts_with(view, "0x") ? "0123456789ABCDEFabcdef_" :
                          starts_with(view, "0o") ? "01234567_" :
                          starts_with(view, "0b") ? "01_" : "";

    view_t::size_type pos = view.find_first_not_of(allowed, 2);
    if (pos == view_t::npos) {
        pos = view.size();
    }
    return pos;
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
    for (char c : sub) {
        if (c != '_') {
            str.push_back(c);
        }
    }

    integer_t ret = 0;
    try {
        ret = std::stoll(str, nullptr, base);
    } catch (std::out_of_range& err) {
        throw parse_error("out_of_range");
    } catch (std::invalid_argument& err) {
        throw parse_error("invalid_argument");
    }
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
view_t::size_type get_integer_length(view_t view) {
    view_t::size_type pos = view.find_first_not_of("0123456789_", 1);
    if (pos == view_t::npos) {
        pos = view.size();
    }
    return pos;
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
    for (char c : sub) {
        if (c != '_') {
            str.push_back(c);
        }
    }

    view_t ref{str.c_str()};
    if ((starts_with(ref, "0") && (ref.size() > 1)) ||
        (starts_with(ref, {"+0", "-0"}) && (ref.size() > 2))) {
        throw parse_error("starts with 0");
    }

    integer_t ret = 0;
    try {
        ret = std::stoll(str, nullptr, 10);
    } catch (std::out_of_range& err) {
        throw parse_error("out_of_range");
    } catch (std::invalid_argument& err) {
        throw parse_error("invalid_argument");
    }
    return ret;
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
        if (decimal_pos == view_t::npos) {
            decimal_pos = view.size();
        }
        pos = decimal_pos;
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
        if (expo_pos == view_t::npos) {
            expo_pos = view.size();
        }
        pos = expo_pos;
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
        contains(sub, {"__", "+_", "_+", "-_", "_-", "e_", "_e", "E_", "_E"})) {
        throw parse_error("invalid `_`");
    }

    std::string str;
    for (char c : sub) {
        if (c != '_') {
            str.push_back(c);
        }
    }

    view_t ref{str.c_str()};
    if ((starts_with(ref, "0") && not starts_with(ref, "0.")) ||
        (starts_with(ref, {"+0", "-0"}) && not starts_with(ref, {"+0.", "-0."}))) {
        throw parse_error("starts with 0");
    }

    float_t ret = 0;
    try {
        ret = std::stod(str, nullptr);
    } catch (std::out_of_range& err) {
        throw parse_error("out_of_range");
    } catch (std::invalid_argument& err) {
        throw parse_error("invalid_argument");
    }
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload
