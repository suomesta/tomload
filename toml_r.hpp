#include <iostream>

#ifndef TOML_R_HPP
#define TOML_R_HPP

#include <exception>
#include <limits>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "integers.hpp"
#include "view_t.hpp"

class parse_error : public std::runtime_error {
 public:
    parse_error(const char* msg) :
        runtime_error(msg) {
    }
};

struct item_t {
    enum type_t : int {
        TYPE_VOID = 0,
        TYPE_BOOL,
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_TABLE,
    } type = TYPE_VOID;

    bool b;
    i64 i;
    double d;
    std::string s;
    std::shared_ptr<std::vector<item_t>> v;
    std::shared_ptr<std::map<std::string, item_t>> m;

    type_t get_type(void) const noexcept { return type; }
    bool is_bool(void) const noexcept { return type == TYPE_BOOL; }
    bool is_int(void) const noexcept { return type == TYPE_INT; }
    bool is_float(void) const noexcept { return type == TYPE_FLOAT; }
    bool is_string(void) const noexcept { return type == TYPE_STRING; }
    bool is_array(void) const noexcept { return type == TYPE_ARRAY; }
    bool is_table(void) const noexcept { return type == TYPE_TABLE; }
    template <class PARAM>
    bool get(PARAM& val) {
        if (std::is_same<PARAM, bool>() && type == TYPE_BOOL) {
            val = b;
        } else if (std::is_same<PARAM, i64>() && type == TYPE_INT) {
            val = i;
        } else if (std::is_same<PARAM, double>() && type == TYPE_FLOAT) {
            val = d;
        } else if (std::is_same<PARAM, std::string>() && type == TYPE_STRING) {
            val = s;
        } else if (std::is_integral<PARAM>() && not std::is_same<PARAM, bool>() && type == TYPE_INT) {
            val = static_cast<PARAM>(i);
        } else if (std::is_integral<PARAM>() && not std::is_same<PARAM, bool>() && type == TYPE_FLOAT) {
            val = static_cast<PARAM>(d);
        } else if (std::is_floating_point<PARAM>() && type == TYPE_INT) {
            val = static_cast<PARAM>(i);
        } else if (std::is_floating_point<PARAM>() && type == TYPE_FLOAT) {
            val = static_cast<PARAM>(d);
        } else {
            return false;
        }

        return true;
    }
    bool get_bool(void) const {
        if (type != TYPE_BOOL) {
            throw parse_error("type mismatch");
        }
        return b;
    }
    i64 get_int(void) const {
        if (type != TYPE_INT) {
            throw parse_error("type mismatch");
        }
        return i;
    }
    double get_float(void) const {
        if (type != TYPE_FLOAT) {
            throw parse_error("type mismatch");
        }
        return d;
    }
    std::string get_string(void) const {
        if (type != TYPE_STRING) {
            throw parse_error("type mismatch");
        }
        return s;
    }

    size_t size(void) const {
        if (type == TYPE_ARRAY) {
            return v->size();
        } else if (type == TYPE_TABLE) {
            return m->size();
        } else {
            throw parse_error("neither array nor table");
        }
    }

    const item_t& operator[](size_t index) const {
        if (type == TYPE_ARRAY) {
            return v->at(index);
        } else {
            throw parse_error("not array");
        }
    }

    const item_t& operator[](const std::string& key) const {
        if (type == TYPE_TABLE) {
            return m->at(key);
        } else {
            throw parse_error("not table");
        }
    }

    bool contains(const std::string& key) const {
        if (type == TYPE_TABLE) {
            return m->find(key) != m->cend();
        } else {
            return false;
        }
    }

    using array_iterator = std::vector<item_t>::const_iterator;
    using table_iterator = std::map<std::string, item_t>::const_iterator;

    array_iterator array_begin(void) const {
        if (type == TYPE_ARRAY) {
            return v->begin();
        } else {
            throw parse_error("not array");
        }
    }

    array_iterator array_end(void) const {
        if (type == TYPE_ARRAY) {
            return v->end();
        } else {
            throw parse_error("not array");
        }
    }

    table_iterator table_begin(void) const {
        if (type == TYPE_TABLE) {
            return m->begin();
        } else {
            throw parse_error("not table");
        }
    }

    table_iterator table_end(void) const {
        if (type == TYPE_TABLE) {
            return m->end();
        } else {
            throw parse_error("not table");
        }
    }

    template <typename I>
    class range_t {
     public:
        range_t(I begin, I end) :
            begin_(begin),
            end_(end) {
        }
        I begin(void) const noexcept {
            return begin_;
        }
        I end(void) const noexcept {
            return end_;
        }
     private:
        I begin_;
        I end_;
    };
    using array_range_t = range_t<array_iterator>;
    using table_range_t = range_t<table_iterator>;

    const array_range_t array_range(void) const noexcept {
        if (type == TYPE_ARRAY) {
            return array_range_t(v->begin(), v->end());
        } else {
            return array_range_t(array_iterator{}, array_iterator{});
        }
    }

    const table_range_t table_range(void) const noexcept {
        if (type == TYPE_TABLE) {
            return table_range_t(m->begin(), m->end());
        } else {
            return table_range_t(table_iterator{}, table_iterator{});
        }
    }
};

item_t parse_array(view_t& view);
item_t parse_item(view_t& view);

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
inline view_t::size_type get_radix_length(view_t view, view_t allowed) {
    view_t::size_type pos = view.find_first_not_of(allowed, 2);
    if (pos == view_t::npos) {
        pos = view.size();
    }
    return pos;
}

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
inline i64 parse_radix_value(view_t view, view_t::size_type length, int base) {
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

    i64 ret = 0;
    try {
        ret = std::stoll(str, nullptr, base);
    } catch (std::out_of_range& err) {
        throw parse_error("out_of_range");
    } catch (std::invalid_argument& err) {
        throw parse_error("invalid_argument");
    }
    return ret;
}

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
inline view_t::size_type get_bare_length(view_t view) {
    view_t::size_type pos = view.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-", 2);
    if (pos == view_t::npos) {
        pos = view.size();
    }
    return pos;
}

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
inline std::string parse_bare_value(view_t view, view_t::size_type length) {
    return {view.data(), length};
}

inline void skip_space(view_t& view, view_t spaces, bool skip_comment) {
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

inline bool wait_newline(view_t& view) {
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

/*
 * @pre `view` must start with "'''"
 */
inline view_t::size_type get_multi_literal_string_length(view_t view) {
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

inline std::string parse_multi_literal_string(view_t& view, view_t::size_type length) {
    if (starts_with(view, "'''\r\n")) {
        return std::string(view.data() + 5, length - 8);
    } else if (starts_with(view, "'''\n")) {
        return std::string(view.data() + 4, length - 7);
    } else {
        return std::string(view.data() + 3, length - 6);
    }
}

/*
 * @pre `view` must start with "'"
 */
inline view_t::size_type get_literal_string_length(view_t view) {
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

inline std::string parse_literal_string(view_t& view, view_t::size_type length) {
    return std::string(view.data() + 1, length - 2);
}

inline item_t parse_array(view_t& view) {
    view_t backup(view);

    view.remove_prefix(1);

    item_t tmp_vector = {item_t::TYPE_ARRAY};
    tmp_vector.v = std::make_shared<std::vector<item_t>>();

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

inline item_t parse_item(view_t& view) {
    item_t ret = {item_t::TYPE_VOID};

    if (starts_with(view, "true")) {
        ret.type = item_t::TYPE_BOOL;
        ret.b = true;
        view.remove_prefix(4);
    } else if (starts_with(view, "false")) {
        ret.type = item_t::TYPE_BOOL;
        ret.b = false;
        view.remove_prefix(5);
    } else if (starts_with(view, "inf")) {
        ret.type = item_t::TYPE_FLOAT;
        ret.d = std::numeric_limits<double>::infinity();
        view.remove_prefix(3);
    } else if (starts_with(view, "+inf")) {
        ret.type = item_t::TYPE_FLOAT;
        ret.d = std::numeric_limits<double>::infinity();
        view.remove_prefix(4);
    } else if (starts_with(view, "-inf")) {
        ret.type = item_t::TYPE_FLOAT;
        ret.d = -std::numeric_limits<double>::infinity();
        view.remove_prefix(4);
    } else if (starts_with(view, "nan")) {
        ret.type = item_t::TYPE_FLOAT;
        ret.d = std::numeric_limits<double>::quiet_NaN();
        view.remove_prefix(3);
    } else if (starts_with(view, "+nan")) {
        ret.type = item_t::TYPE_FLOAT;
        ret.d = std::numeric_limits<double>::quiet_NaN();
        view.remove_prefix(4);
    } else if (starts_with(view, "-nan")) {
        ret.type = item_t::TYPE_FLOAT;
        ret.d = -std::numeric_limits<double>::quiet_NaN();
        view.remove_prefix(4);
    } else if (starts_with(view, "0x")) {
        view_t::size_type length = get_radix_length(view, "0123456789ABCDEFabcdef_");
        i64 i = parse_radix_value(view, length, 16);

        ret.type = item_t::TYPE_INT;
        ret.i = i;
        view.remove_prefix(length);
    } else if (starts_with(view, "0o")) {
        view_t::size_type length = get_radix_length(view, "01234567_");
        i64 i = parse_radix_value(view, length, 8);

        ret.type = item_t::TYPE_INT;
        ret.i = i;
        view.remove_prefix(length);
    } else if (starts_with(view, "0b")) {
        view_t::size_type length = get_radix_length(view, "01_");
        i64 i = parse_radix_value(view, length, 2);

        ret.type = item_t::TYPE_INT;
        ret.i = i;
        view.remove_prefix(length);
    } else if (starts_with(view, "'''")) {
        view_t::size_type length = get_multi_literal_string_length(view);
        std::string str = parse_multi_literal_string(view, length);

        ret.type = item_t::TYPE_STRING;
        ret.s = std::move(str);
        view.remove_prefix(length);
    } else if (starts_with(view, "'")) {
        view_t::size_type length = get_literal_string_length(view);
        std::string str = parse_literal_string(view, length);

        ret.type = item_t::TYPE_STRING;
        ret.s = std::move(str);
        view.remove_prefix(length);
    } else if (starts_with(view, "[")) {
        ret = parse_array(view);
    } else {
        throw parse_error("not hit item");
    }

    return ret;
}

inline void insert_table(item_t& root, item_t& item, const std::vector<std::string>& brackets, const std::vector<std::string>& keys) {
    std::map<std::string, item_t>* mptr = root.m.get();
    for (const std::string& key : brackets) {
        mptr->insert({key, item_t{}});
        mptr->find(key)->second.type = item_t::TYPE_TABLE;
        mptr->find(key)->second.m = std::make_shared<std::map<std::string, item_t>>();
        mptr = mptr->find(key)->second.m.get();
    }
    for (const std::string& key : keys) {
        if (&key != &keys.back()) {
            mptr->insert({key, item_t{}});
            mptr->find(key)->second.type = item_t::TYPE_TABLE;
            mptr->find(key)->second.m = std::make_shared<std::map<std::string, item_t>>();
            mptr = mptr->find(key)->second.m.get();
        } else {
            mptr->insert({key, item_t{}});
            mptr->find(key)->second = std::move(item);
        }
        
    }
}

inline item_t parse(view_t& view) {
    item_t ret = {};
    ret.type = item_t::TYPE_TABLE;
    ret.m = std::make_shared<std::map<std::string, item_t>>();

    std::vector<std::string> brackets;
    std::vector<std::string> keys;

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
                std::string s = parse_bare_value(view, length);

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
                std::string s = parse_bare_value(view, length);

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
            insert_table(ret, item, brackets, keys);
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

    return ret;
}

#endif  // TOML_R_HPP
