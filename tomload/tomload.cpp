#include "tomload/tomload.h"
#include "tomload/parser.h"

namespace tomload {

item_t::item_t(view_t view) :
    type(TYPE_TABLE),
    m(std::make_shared<std::map<key_t, item_t>>()) {
    parse_main(view);
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(boolean_t val) noexcept :
    type(TYPE_BOOLEAN),
    b(val) {
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(integer_t val) noexcept :
    type(TYPE_INTEGER),
    i(val) {
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(float_t val) noexcept :
    type(TYPE_FLOAT),
    d(val) {
}
/////////////////////////////////////////////////////////////////////////////

item_t::item_t(const string_t& val) noexcept :
    type(TYPE_STRING),
    s(val) {
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

boolean_t item_t::get_bool(void) const {
    if (type != TYPE_BOOLEAN) {
        throw parse_error("type mismatch");
    }
    return b;
}
/////////////////////////////////////////////////////////////////////////////

integer_t item_t::get_integer(void) const {
    if (type != TYPE_INTEGER) {
        throw parse_error("type mismatch");
    }
    return i;
}
/////////////////////////////////////////////////////////////////////////////

float_t item_t::get_float(void) const {
    if (type != TYPE_FLOAT) {
        throw parse_error("type mismatch");
    }
    return d;
}
/////////////////////////////////////////////////////////////////////////////

string_t item_t::get_string(void) const {
    if (type != TYPE_STRING) {
        throw parse_error("type mismatch");
    }
    return s;
}
/////////////////////////////////////////////////////////////////////////////

size_t item_t::size(void) const {
    if (type == TYPE_ARRAY) {
        return v->size();
    } else if (type == TYPE_TABLE) {
        return m->size();
    } else {
        throw parse_error("neither array nor table");
    }
}
/////////////////////////////////////////////////////////////////////////////

const item_t& item_t::operator[](size_t index) const {
    if (type == TYPE_ARRAY) {
        return v->at(index);
    } else {
        throw parse_error("not array");
    }
}
/////////////////////////////////////////////////////////////////////////////

const item_t& item_t::operator[](const key_t& key) const {
    if (type == TYPE_TABLE) {
        return m->at(key);
    } else {
        throw parse_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

bool item_t::contains(const key_t& key) const {
    if (type == TYPE_TABLE) {
        return m->find(key) != m->cend();
    } else {
        throw parse_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

array_iterator item_t::array_begin(void) const {
    if (type == TYPE_ARRAY) {
        return v->begin();
    } else {
        throw parse_error("not array");
    }
}
/////////////////////////////////////////////////////////////////////////////

array_iterator item_t::array_end(void) const {
    if (type == TYPE_ARRAY) {
        return v->end();
    } else {
        throw parse_error("not array");
    }
}
/////////////////////////////////////////////////////////////////////////////

table_iterator item_t::table_begin(void) const {
    if (type == TYPE_TABLE) {
        return m->begin();
    } else {
        throw parse_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

table_iterator item_t::table_end(void) const {
    if (type == TYPE_TABLE) {
        return m->end();
    } else {
        throw parse_error("not table");
    }
}
/////////////////////////////////////////////////////////////////////////////

const array_range_t item_t::array_range(void) const noexcept {
    if (type == TYPE_ARRAY) {
        return array_range_t(v->begin(), v->end());
    } else {
        return array_range_t(array_iterator{}, array_iterator{});
    }
}
/////////////////////////////////////////////////////////////////////////////

const table_range_t item_t::table_range(void) const noexcept {
    if (type == TYPE_TABLE) {
        return table_range_t(m->begin(), m->end());
    } else {
        return table_range_t(table_iterator{}, table_iterator{});
    }
}
/////////////////////////////////////////////////////////////////////////////

tomload::item_t* item_t::push(const key_t& key, const item_t& item) {
    if (type != TYPE_TABLE) {
        throw parse_error("not table");
    }
    auto ret = m->insert({key, item});
    return &ret.first->second;
}
/////////////////////////////////////////////////////////////////////////////

void item_t::insert_new_table(item_t& item, const std::vector<key_t>& brackets, std::vector<key_t> keys) {
    item_t* p_item = this;
    for (const key_t& key : brackets) {
        auto next_table = item_t{std::make_shared<std::map<key_t, item_t>>()};
        p_item = p_item->push(key, next_table);
        if (not p_item->is_table()) {
            throw parse_error("expected table");
        }
    }
    for (const key_t& key : keys) {
        if (&key != &keys.back()) {
            auto next_table = item_t{std::make_shared<std::map<key_t, item_t>>()};
            p_item = p_item->push(key, next_table);
            if (not p_item->is_table()) {
                throw parse_error("expected table");
            }
        } else {
            if (not p_item->contains(key)) {
                p_item->push(key, item);
            } else {
                throw parse_error("already reginstered");
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

void item_t::parse_main(view_t& view) {
    std::vector<key_t> brackets;

    bool ini_state = true;

    for (;;) {
        if (ini_state) {
            skip_space(view, " \t\r\n", true);
            if (view.empty()) {
                break;
            } else if (starts_with(view, "[")) {
                view.remove_prefix(1);
                brackets = parse_keys(view);

                skip_space(view, " \t", false);
                if (starts_with(view, "]")) {
                    view.remove_prefix(1);
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
                item_t item = parse_item(view);
                insert_new_table(item, brackets, std::move(keys));
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

}  // namespace tomload
