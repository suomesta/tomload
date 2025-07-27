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
    if ((starts_with(sub, "_")) ||
        (ends_with(sub, "_")) ||
        (sub.find("__") != view_t::npos)) {
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
    if ((ends_with(sub, "_")) ||
        (sub.find("__") != view_t::npos)) {
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
    return get_integer_length(view);
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
float_t parse_float(view_t view, view_t::size_type length) {
    return parse_integer(view, length);
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload
