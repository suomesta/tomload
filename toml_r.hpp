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
    enum type_t {
        TYPE_VOID = 0,
        TYPE_BOOL,
        TYPE_UINT,
        TYPE_FLOAT,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_TABLE,
    } type = TYPE_VOID;

    bool b;
    u64 u;
    double d;
    std::string s;
    std::unique_ptr<std::vector<item_t>> v;
    std::unique_ptr<std::map<std::string, item_t>> m;
};

item_t parse_array(view_t& view);
item_t parse_item(view_t& view);

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
view_t::size_type get_radix_length(view_t view, view_t allowed) {
    view_t::size_type pos = view.find_first_not_of(allowed, 2);
    if (pos == view_t::npos) {
        pos = view.size();
    }
    return pos;
}

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
u64 parse_radix_value(view_t view, view_t::size_type length, int base) {
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

    u64 ret = 0;
    try {
        ret = std::stoull(str, nullptr, base);
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
view_t::size_type get_bare_length(view_t view) {
    view_t::size_type pos = view.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-", 2);
    if (pos == view_t::npos) {
        pos = view.size();
    }
    return pos;
}

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
std::string parse_bare_value(view_t view, view_t::size_type length) {
    return {view.data(), length};
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

item_t parse_array(view_t& view) {
    view_t backup(view);

    view.remove_prefix(1);

    item_t tmp_vector = {item_t::TYPE_ARRAY};
    tmp_vector.v = std::make_unique<std::vector<item_t>>();

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
    item_t ret = {item_t::TYPE_VOID};

    skip_space(view, " \t\r\n", false);

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
    } else if (starts_with(view, "[")) {
        ret = parse_array(view);
    } else {
        throw parse_error("not hit item");
    }

    return ret;
}

void insert_table(item_t& root, item_t& item, const std::vector<std::string>& brackets, const std::vector<std::string>& keys) {
    std::map<std::string, item_t>* mptr = root.m.get();
    for (const std::string& key : brackets) {
        mptr->insert({key, item_t{}});
        mptr->find(key)->second.type = item_t::TYPE_TABLE;
        mptr->find(key)->second.m = std::make_unique<std::map<std::string, item_t>>();
        mptr = mptr->find(key)->second.m.get();
    }
    for (const std::string& key : keys) {
        if (&key != &keys.back()) {
            mptr->insert({key, item_t{}});
            mptr->find(key)->second.type = item_t::TYPE_TABLE;
            mptr->find(key)->second.m = std::make_unique<std::map<std::string, item_t>>();
            mptr = mptr->find(key)->second.m.get();
        } else {
            mptr->insert({key, item_t{}});
            mptr->find(key)->second = std::move(item);
        }
        
    }
}

item_t parse(view_t& view) {
    item_t ret = {};
    ret.type = item_t::TYPE_TABLE;
    ret.m = std::make_unique<std::map<std::string, item_t>>();

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
std::cout << int(item.type) << std::endl;
std::cout << int(item.b) << std::endl;
            insert_table(ret, item, brackets, keys);
std::cout << int(ret.type) << std::endl;
std::cout << int((*ret.m)["aa"].type) << std::endl;
std::cout << int((*(*ret.m)["aa"].m)["bb"].type) << std::endl;
std::cout << int((*(*ret.m)["aa"].m)["bb"].b) << std::endl;
return ret;
/*
            std::unique_ptr<std::map<std::string, item_t>>* last = &ret.m;
            for (const std::string& k : bracket) {
                (*last)->insert({k, item_t{}});
                (*(*last))[k].type = item_t::TYPE_TABLE;
                (*(*last))[k].m = std::make_unique<std::map<std::string, item_t>>();
//                ret.m = std::make_unique<std::map<std::string, item_t>>(k, item_t{});
                last = &(*last)[k].m;
            }
            for (const std::string& k : key) {
                (*last)->insert({k, item_t{}});
                (*(*last))[k].type = item_t::TYPE_TABLE;
                (*(*last))[k].m = std::make_unique<std::map<std::string, item_t>>();
//                ret.m = std::make_unique<std::map<std::string, item_t>>(k, item_t{});
                last = &(*last)[k].m;
            }
            last
*/
        } else {
            if (view.empty()) {
                break;
            }
        }
    }

    return ret;
}

#endif  // TOML_R_HPP
