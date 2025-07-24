#include "detail_string.h"
#include "parser.h"

namespace tomload {

std::string utf8_encode(uint32_t codepoint) {
    if (codepoint <= 0x7F) {  // 1-byte UTF-8
        return {static_cast<char>(codepoint)};
    } else if (codepoint <= 0x7FF) {  // 2-byte UTF-8
        return {static_cast<char>(0xC0 | (codepoint >> 6)),
                static_cast<char>(0x80 | (codepoint & 0x3F))};
    } else if (codepoint <= 0xFFFF) {  // 3-byte UTF-8
        return {static_cast<char>(0xE0 | (codepoint >> 12)),
                static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)),
                static_cast<char>(0x80 | (codepoint & 0x3F))};
    } else if (codepoint <= 0x10FFFF) {  // 4-byte UTF-8
        return {static_cast<char>(0xF0 | (codepoint >> 18)),
                static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F)),
                static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)),
                static_cast<char>(0x80 | (codepoint & 0x3F))};  
    } else {
        return {};  // Invalid code point
    }
}

/*
 * @pre `view` must start with "'''"
 */
view_t::size_type get_multi_literal_string_length(view_t view) {
    view_t::size_type pos = view.find("'''", 3);

    if (pos == view_t::npos) {
        throw parse_error("not closed by '''");
    }

    view_t::size_type pos5 = view.find("'''''", 3);
    view_t::size_type pos4 = view.find("''''", 3);
    if (pos == pos5) {
        pos += 2;
    } else if (pos == pos4) {
        pos += 1;
    }

    return pos + 3;
}

string_t parse_multi_literal_string(view_t& view, view_t::size_type length) {
    if (starts_with(view, "'''\r\n")) {
        return string_t(view.data() + 5, length - 8);
    } else if (starts_with(view, "'''\n")) {
        return string_t(view.data() + 4, length - 7);
    } else {
        return string_t(view.data() + 3, length - 6);
    }
}

/*
 * @pre `view` must start with "'"
 */
view_t::size_type get_literal_string_length(view_t view) {
    view_t::size_type pos = view.find("'", 1);

    if (pos == view_t::npos) {
        throw parse_error("not closed by '");
    }

    view_t::size_type pos_r = view.find("\r", 1);
    view_t::size_type pos_n = view.find("\n", 1);
    if ((pos_r != view_t::npos) && (pos_r < pos)) {
        throw parse_error("detect newline in literal string");
    } else if ((pos_n != view_t::npos) && (pos_n < pos)) {
        throw parse_error("detect newline in literal string");
    }

    return pos + 1;
}

string_t parse_literal_string(view_t& view, view_t::size_type length) {
    return string_t(view.data() + 1, length - 2);
}

std::string parse_unicode_escape(const view_t& view, int size) {
    auto is_hex = [](char c) {  // avoid to use std::isxdigit() because it depends on the locale
        return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
    };

    if (size > view.size()) {
        throw parse_error("invalid unicode escape sequence");
    }
    if (not std::all_of(view.data(), view.data() + size, is_hex)) {
        throw parse_error("invalid unicode escape sequence");
    }
    uint32_t code_point = static_cast<uint32_t>(std::stoul(std::string(view.data(), size), nullptr, 16));
    if (((0x00 <= code_point) && (code_point <= 0x08)) ||
        ((0x0A <= code_point) && (code_point <= 0x1F)) ||
        (code_point == 0x7F)) {  // U+0000 ～ U+0008、U+000A ～ U+001F、U+007F
        throw parse_error("invalid unicode escape sequence");
    }
    std::string chars = utf8_encode(code_point);
    if (chars.empty()) {
        throw parse_error("invalid unicode escape sequence");
    }
    return chars;
}

/*
 * @pre `view` must start with '"'
 */
view_t::size_type get_string_length(view_t view) {
    bool detected_backslash = false;
    for (view_t::size_type i = 1; i < view.size(); i++) {
        if (not detected_backslash) {
            if (view[i] == '"') {
                return i + 1;
            } else if (view[i] == '\\') {
                detected_backslash = true;
            } else if (view[i] == '\n' || view[i] == '\r') {
                throw parse_error("detect newline in string");
            }
        } else {
            if ((view[i] == 'n') || (view[i] == 'r') || (view[i] == 't') || (view[i] == 'b') ||
                (view[i] == 'f') || (view[i] == '\\') || (view[i] == '"')) {
            } else if (view[i] == 'u') {
                if (i + 4 > view.size()) {
                    throw parse_error("invalid unicode escape sequence");
                }
                i += 4;
            } else if (view[i] == 'U') {
                if (i + 8 > view.size()) {
                    throw parse_error("invalid unicode escape sequence");
                }
                i += 8;
            } else {
                throw parse_error("invalid escape sequence");
            }
            detected_backslash = false;
        }
    }
    throw parse_error("not closed by \"");
}

string_t parse_string(view_t view, view_t::size_type length) {
    std::string ret;

    view_t sub(view.data() + 1, length - 2);
    for (view_t::size_type i = 0; i < sub.size(); i++) {
        if (sub[i] == '\\') {
            i++;

            if (sub[i] == 'n') {
                ret.push_back('\n');
            } else if (sub[i] == 'r') {
                ret.push_back('\r');
            } else if (sub[i] == 't') {
                ret.push_back('\t');
            } else if (sub[i] == 'b') {
                ret.push_back('\b');
            } else if (sub[i] == 'f') {
                ret.push_back('\f');
            } else if (sub[i] == '\\') {
                ret.push_back('\\');
            } else if (sub[i] == '"') {
                ret.push_back('"');
            } else if (sub[i] == 'u') {
                ret += parse_unicode_escape(sub.substr(i + 1), 4);
                i += 4;
            } else if (sub[i] == 'U') {
                ret += parse_unicode_escape(sub.substr(i + 1), 8);
                i += 8;
            }
        } else {
            ret.push_back(sub[i]);
        }
    }
    return ret;
}

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
view_t::size_type get_bare_length(view_t view) {
    view_t::size_type pos = view.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-", 1);
    if (pos == view_t::npos) {
        pos = view.size();
    }
    return pos;
}

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
string_t parse_bare_value(view_t view, view_t::size_type length) {
    return {view.data(), length};
}

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
                ;
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

}  // namespace tomload
