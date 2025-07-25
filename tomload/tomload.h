
#ifndef TOMLOAD_TOMLOAD_H
#define TOMLOAD_TOMLOAD_H

#include <algorithm>
#include <cstdint>
#include <exception>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "tomload/view_t.hpp"

namespace tomload {

class parse_error : public std::runtime_error {
 public:
    parse_error(const char* msg) :
        runtime_error(msg) {
    }
};

template <typename I>
class range_t {
 public:
    range_t(I begin, I end) :
        begin_(begin),
        end_(end) {
    }

    I begin(void) const noexcept { return begin_; }
    I end(void) const noexcept { return end_; }

 private:
    I begin_, end_;
};

using boolean_t = bool;
using integer_t = int64_t;
using float_t = double;
using string_t = std::string;
using key_t = std::string;
struct item_t;
using array_iterator = std::vector<item_t>::const_iterator;
using table_iterator = std::map<key_t, item_t>::const_iterator;
using array_range_t = range_t<array_iterator>;
using table_range_t = range_t<table_iterator>;
static_assert(sizeof(long long) == sizeof(integer_t), "sizeof(long long) must be 8");
struct make_array_t { explicit make_array_t() = default; };
static constexpr make_array_t make_array{};
struct make_table_t { explicit make_table_t() = default; };
static constexpr make_table_t make_table{};

struct item_t {
    enum type_t : int {
        TYPE_BOOLEAN = 0,
        TYPE_INTEGER,
        TYPE_FLOAT,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_TABLE,
        TYPE_NONE,
    } type = TYPE_NONE;

    boolean_t b;
    integer_t i;
    float_t d;
    string_t s;
    std::shared_ptr<std::vector<item_t>> v;
    std::shared_ptr<std::map<key_t, item_t>> m;

    item_t(void) = default;
    item_t(view_t view);
    item_t(boolean_t val) noexcept;
    item_t(integer_t val) noexcept;
    item_t(float_t val) noexcept;
    item_t(const string_t& val) noexcept;
    item_t(string_t&& val) noexcept;
    item_t(std::shared_ptr<std::vector<item_t>> val) noexcept;
    item_t(make_array_t);
    item_t(std::shared_ptr<std::map<key_t, item_t>> val) noexcept;
    item_t(make_table_t);

    bool is_boolean(void) const noexcept;
    bool is_integer(void) const noexcept;
    bool is_float(void) const noexcept;
    bool is_string(void) const noexcept;
    bool is_array(void) const noexcept;
    bool is_table(void) const noexcept;

    boolean_t get_bool(void) const;
    integer_t get_integer(void) const;
    float_t get_float(void) const;
    string_t get_string(void) const;

    template <class PARAM>
    bool get(PARAM& val) const noexcept {
        if (std::is_same<PARAM, boolean_t>() && type == TYPE_BOOLEAN) {
            val = b;
        } else if (std::is_same<PARAM, integer_t>() && type == TYPE_INTEGER) {
            val = i;
        } else if (std::is_same<PARAM, float_t>() && type == TYPE_FLOAT) {
            val = d;
        } else if (std::is_same<PARAM, string_t>() && type == TYPE_STRING) {
            val = s;
        } else if (std::is_integral<PARAM>() && not std::is_same<PARAM, boolean_t>() && type == TYPE_INTEGER) {
            val = static_cast<PARAM>(i);
        } else if (std::is_integral<PARAM>() && not std::is_same<PARAM, boolean_t>() && type == TYPE_FLOAT) {
            val = static_cast<PARAM>(d);
        } else if (std::is_floating_point<PARAM>() && type == TYPE_INTEGER) {
            val = static_cast<PARAM>(i);
        } else if (std::is_floating_point<PARAM>() && type == TYPE_FLOAT) {
            val = static_cast<PARAM>(d);
        } else {
            return false;
        }

        return true;
    }

    size_t size(void) const;
    item_t& operator[](size_t index);
    item_t& operator[](const key_t& key);
    const item_t& operator[](size_t index) const;
    const item_t& operator[](const key_t& key) const;
    array_iterator array_begin(void) const;
    array_iterator array_end(void) const;
    table_iterator table_begin(void) const;
    table_iterator table_end(void) const;
    const array_range_t array_range(void) const noexcept;
    const table_range_t table_range(void) const noexcept;
    bool contains(const key_t& key) const;
    void push(const item_t& item) {
        if (type != TYPE_ARRAY) {
            throw parse_error("not array");
        }
        v->push_back(item);
    }
    void push(const key_t& key, const item_t& item) {
        if (type != TYPE_TABLE) {
            throw parse_error("not table");
        }
        m->insert({key, item});
    }

 private:
    void insert_new_table(item_t& item, const std::vector<key_t>& brackets, std::vector<key_t> keys);
    void parse_main(view_t& view);

};

}  // namespace tomload

#endif  // TOMLOAD_TOMLOAD_H
