#include "tomload/tomload.h"
#include <set>
#include "tomload/parser.h"

namespace tomload {

/*
 * @brief Constructor that initializes item_t from a view_t which holds TOML raw string.
 * @param view[in]: The view_t object containing raw TOML string.
 *                  TOML string must contain at least one key-value pair or
 *                  completely empty (not allowed single value, like
 *                  "true" or "123").
 * @throws parse_error: if the view cannot be parsed correctly.
 * @note Most users must use only this constructor to parse TOML string.
 */
item_t::item_t(view_t view) :
    type(TYPE_TABLE),
    m(std::make_shared<std::map<key_t, item_t>>()) {
    parse_main(view);
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(boolean_t val) noexcept :
    type(TYPE_BOOLEAN) {
    u.b = val;
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(integer_t val) noexcept :
    type(TYPE_INTEGER) {
    u.i = val;
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(float_t val) noexcept :
    type(TYPE_FLOAT) {
    u.d = val;
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(string_t&& val) noexcept :
    type(TYPE_STRING),
    s(std::move(val)) {
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(std::shared_ptr<std::vector<item_t>> val) noexcept :
    type(TYPE_ARRAY),
    v(val) {
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(std::shared_ptr<std::map<key_t, item_t>> val) noexcept:
    type(TYPE_TABLE),
    m(val) {
    u.is_inline_table = false;  // default false
}
/////////////////////////////////////////////////////////////////////////////

bool item_t::is_boolean(void) const noexcept {
    return type == TYPE_BOOLEAN;
}
/////////////////////////////////////////////////////////////////////////////

bool item_t::is_integer(void) const noexcept {
    return type == TYPE_INTEGER;
}
/////////////////////////////////////////////////////////////////////////////

bool item_t::is_float(void) const noexcept {
    return type == TYPE_FLOAT;
}
/////////////////////////////////////////////////////////////////////////////

bool item_t::is_string(void) const noexcept {
    return type == TYPE_STRING;
}
/////////////////////////////////////////////////////////////////////////////

bool item_t::is_array(void) const noexcept {
    return type == TYPE_ARRAY;
}
/////////////////////////////////////////////////////////////////////////////

bool item_t::is_table(void) const noexcept {
    return type == TYPE_TABLE;
}
/////////////////////////////////////////////////////////////////////////////

boolean_t item_t::get_boolean(void) const {
    if (type != TYPE_BOOLEAN) {
        throw type_error("type mismatch");
    }
    return u.b;
}
/////////////////////////////////////////////////////////////////////////////

integer_t item_t::get_integer(void) const {
    if (type != TYPE_INTEGER) {
        throw type_error("type mismatch");
    }
    return u.i;
}
/////////////////////////////////////////////////////////////////////////////

float_t item_t::get_float(void) const {
    if (type != TYPE_FLOAT) {
        throw type_error("type mismatch");
    }
    return u.d;
}
/////////////////////////////////////////////////////////////////////////////

string_t item_t::get_string(void) const {
    if (type != TYPE_STRING) {
        throw type_error("type mismatch");
    }
    return s;
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief get size of array or table.
 * @return size_t: size of array or table.
 * @throw type_error: if the type is neither array nor table.
 * @pre To prevent throwing exceptions, call `is_array()`, or `is_table()` and confirm the return value.
 */
size_t item_t::size(void) const {
    if (type == TYPE_ARRAY) {
        return v->size();
    } else if (type == TYPE_TABLE) {
        return m->size();
    } else {
        throw type_error("neither array nor table");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief check the array or table is empty or not.
 * @return bool: array or table is empty.
 * @throw type_error: if the type is neither array nor table.
 * @pre To prevent throwing exceptions, call `is_array()`, or `is_table()` and confirm the return value.
 */
bool item_t::empty(void) const {
    if (type == TYPE_ARRAY) {
        return v->empty();
    } else if (type == TYPE_TABLE) {
        return m->empty();
    } else {
        throw type_error("neither array nor table");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief operator[] of array.
 * @param index[in]: appointed index of array.
 * @throw type_error: if the type is not array.
 * @throw std::out_of_range: if `index` is out of range of array.
 * @pre To prevent throwing exceptions, call `is_array()` and confirm the return value.
 */
const item_t& item_t::operator[](size_t index) const {
    if (type == TYPE_ARRAY) {
        return v->at(index);
    } else {
        throw type_error("not array");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief operator[] of table.
 * @param key[in]: appointed key of table.
 * @throw type_error: if the type is not table.
 * @throw std::out_of_range: if `key` is not found in the table.
 * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
 */
const item_t& item_t::operator[](const key_t& key) const {
    if (type == TYPE_TABLE) {
        return m->at(key);
    } else {
        throw type_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Check if the table contains the specified key, like std::map::contains() in C++20.
 * @param key[in]: The key to check for existence in the table.
 * @return true if the key exists in the table, false otherwise.
 * @throw type_error: if the type is not table.
 * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
 */
bool item_t::contains(const key_t& key) const {
    if (type == TYPE_TABLE) {
        return m->find(key) != m->cend();
    } else {
        throw type_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Get an iterator to the beginning of the array.
 * @return array_iterator: an iterator pointing to the first element of the array.
 * @throw type_error: if the type is not array.
 * @pre To prevent throwing exceptions, call `is_array()` and confirm the return value.
 */
array_iterator item_t::array_begin(void) const {
    if (type == TYPE_ARRAY) {
        return v->begin();
    } else {
        throw type_error("not array");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Get an iterator to the end of the array.
 * @return array_iterator: an iterator pointing to the end of the array.
 * @throw type_error: if the type is not array.
 * @pre To prevent throwing exceptions, call `is_array()` and confirm the return value.
 */
array_iterator item_t::array_end(void) const {
    if (type == TYPE_ARRAY) {
        return v->end();
    } else {
        throw type_error("not array");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Get an iterator to the beginning of the table.
 * @return table_iterator: an iterator pointing to the first element of the table.
 * @throw type_error: if the type is not table.
 * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
 */
table_iterator item_t::table_begin(void) const {
    if (type == TYPE_TABLE) {
        return m->begin();
    } else {
        throw type_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Get an iterator to the end of the table.
 * @return table_iterator: an iterator pointing to the end of the table.
 * @throw type_error: if the type is not table.
 * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
 */
table_iterator item_t::table_end(void) const {
    if (type == TYPE_TABLE) {
        return m->end();
    } else {
        throw type_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Get a range of the array.
 * @return array_range_t: a range object containing iterators to the beginning and end of the array.
 * @throw type_error: if the type is not array.
 * @pre To prevent throwing exceptions, call `is_array()` and confirm the return value.
 */
const array_range_t item_t::array_range(void) const {
    if (type == TYPE_ARRAY) {
        return array_range_t(v->begin(), v->end());
    } else {
        throw type_error("not array");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Get a range of the table.
 * @return table_range_t: a range object containing iterators to the beginning and end of the table.
 * @throw type_error: if the type is not table.
 * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
 */
const table_range_t item_t::table_range(void) const {
    if (type == TYPE_TABLE) {
        return table_range_t(m->begin(), m->end());
    } else {
        throw type_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Construct inline table from multiple keys-value pairs.
 * @param key_vals[in]: keys-value pairs..
 * @throw parse_error: type is not table, or [keys] spot is inappropreate.
 * @note this method is intended to be used in parsing process.
 */
void item_t::set_inline_table_keys_value(std::vector<std::pair<std::vector<key_t>, item_t>> key_vals) {
    if (type != TYPE_TABLE) {
        throw parse_error("not table");
    }

    for (std::pair<std::vector<key_t>, item_t>& key_val : key_vals) {
        if (key_val.first.empty()) {
            throw parse_error("no keys");
        }

        insert_keys_table(this, std::move(key_val.first), key_val.second);
    }

    u.is_inline_table = true;
}
/////////////////////////////////////////////////////////////////////////////

item_t* item_t::push(const key_t& key, item_t val) {
    if (type != TYPE_TABLE) {
        throw parse_error("not table");
    }
    auto ret = m->insert({key, val});
    return &ret.first->second;
}
/////////////////////////////////////////////////////////////////////////////

item_t* item_t::insert_brackets_table(const std::vector<key_t>& brackets) {
    item_t* p_item = this;
    for (const key_t& key : brackets) {
        if (p_item->u.is_inline_table) {
            throw parse_error("inline table error");
        }

        auto next_table = item_t{std::make_shared<std::map<key_t, item_t>>()};
        p_item = p_item->push(key, next_table);
        if (not p_item->is_table()) {
            throw parse_error("expected table");
        }
    }
    return p_item;
}
/////////////////////////////////////////////////////////////////////////////

void item_t::insert_keys_table(item_t* p_begin, std::vector<key_t> keys, item_t val) {
    if (p_begin == nullptr) {
        throw parse_error("unknown error");
    }

    item_t* p_item = p_begin;
    for (const key_t& key : keys) {
        if (p_item->u.is_inline_table) {
            throw parse_error("inline table error");
        }

        if (&key != &keys.back()) {
            auto next_table = item_t{std::make_shared<std::map<key_t, item_t>>()};
            p_item = p_item->push(key, next_table);
            if (not p_item->is_table()) {
                throw parse_error("expected table");
            }
        } else {
            if (not p_item->contains(key)) {
                p_item = p_item->push(key, val);
            } else {
                throw parse_error("already reginstered");
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

void item_t::parse_main(view_t& view) {
    std::set<std::vector<key_t>> brackets_set;
    item_t* p_brackets_end = this;
    bool ini_state = true;

    for (;;) {
        if (ini_state) {
            skip_space(view, " \t\r\n", true);
            if (view.empty()) {
                break;
            } else if (starts_with(view, "[")) {
                view.remove_prefix(1);
                std::vector<key_t> brackets = parse_keys(view);

                skip_space(view, " \t", false);
                if (starts_with(view, "]")) {
                    view.remove_prefix(1);
                    if (brackets_set.insert(brackets).second) {
                        // OK. now registered
                    } else {
                        throw parse_error("duplicate table");
                    }
                    p_brackets_end = insert_brackets_table(std::move(brackets));
                    ini_state = false;
                } else {
                    throw parse_error("expected ']'");
                }
            } else {
                std::vector<key_t> keys = parse_keys(view);

                skip_space(view, " \t", false);
                if (starts_with(view, "=")) {
                    view.remove_prefix(1);
                } else {
                    throw parse_error("expected '='");
                }

                skip_space(view, " \t", false);
                insert_keys_table(p_brackets_end, std::move(keys), parse_item(view));
                ini_state = false;
            }
        } else {
            if (wait_newline(view)) {
                ini_state = true;
            } else {
                throw parse_error("expected newline");
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

template <>
bool item_t::get<string_t>(string_t& val) const {
    if (type == TYPE_STRING) {
        val = s;
    } else {
        return false;
    }

    return true;
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload
