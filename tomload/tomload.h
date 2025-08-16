/*
 * @file tomload.h
 * @brief Header file for tomload library.
 * @details This file defines the item_t class and its methods for parsing and handling TOML-like data.
 */

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

/*
 * @class parse_error
 * @brief Exception class for parsing errors.
 * @details This class is derived from std::runtime_error and is used to indicate errors during parsing.
 */
class parse_error : public std::runtime_error {
 public:
    parse_error(const char* msg) :
        runtime_error(msg) {
    }
};
/////////////////////////////////////////////////////////////////////////////

/*
 * @class type_error
 * @brief Exception class for type errors.
 * @details This class is derived from std::runtime_error and is used to indicate type mismatches.
 */
class type_error : public std::runtime_error {
 public:
    type_error(const char* msg) :
        runtime_error(msg) {
    }
};
/////////////////////////////////////////////////////////////////////////////

/*
 * @class range_t
 * @brief A template class for creating a range of iterators.
 * @details This class is used to represent a range defined by two iterators,
 *          and intented to be used at ranged-based for loops.
 * @tparam I The type of the iterator.
 */
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
/////////////////////////////////////////////////////////////////////////////

struct item_t;
using boolean_t = bool;
using integer_t = int64_t;
using float_t = double;
using string_t = std::string;
using key_t = std::string;
using array_iterator = std::vector<item_t>::const_iterator;
using table_iterator = std::map<key_t, item_t>::const_iterator;
using array_range_t = range_t<array_iterator>;
using table_range_t = range_t<table_iterator>;
static_assert(sizeof(long long) == sizeof(integer_t), "sizeof(long long) must be 8");

class item_t {
 public:
    item_t(void) = delete;  // Default constructor is deleted.

    /*
     * @brief Constructor that initializes item_t from raw TOML string.
     * @param view[in]: The view_t object containing raw TOML string.
     *                  TOML string must contain at least one key-value pair or
     *                  completely empty (not allowed single value, like
     *                  "true" or "123").
     * @throws parse_error: if the view cannot be parsed correctly.
     * @note Most users must use only this constructor to parse TOML string.
     */
    item_t(view_t view);
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Constructors for each types (boolean, integer, float, string, array, and table).
     * @note Main purpose of these constructors are testing. Most users does not need use these.
     */
    item_t(boolean_t val) noexcept;
    item_t(integer_t val) noexcept;
    item_t(float_t val) noexcept;
    item_t(string_t&& val) noexcept;
    item_t(std::shared_ptr<std::vector<item_t>> val) noexcept;
    item_t(std::shared_ptr<std::map<key_t, item_t>> val) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Type checker for each types (boolean, integer, float, string, array, and table).
     */
    bool is_boolean(void) const noexcept;
    bool is_integer(void) const noexcept;
    bool is_float(void) const noexcept;
    bool is_string(void) const noexcept;
    bool is_array(void) const noexcept;
    bool is_table(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Getter of single value (boolean, integer, float, and string).
     * @throw type_error: if type of item_t does not match with the type specified by getter.
     * @pre To prevent throwing exceptions, call `is_boolean()`, `is_integer()`, `is_float()`, or `is_string()` and confirm the return value.
     */
    boolean_t get_boolean(void) const;
    integer_t get_integer(void) const;
    float_t get_float(void) const;
    string_t get_string(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Getter of param[out] version. supported types are boolean, integer, float, and string.
     * @param val[out]: gotten value to be loaded.
     * @return true/false: success/fail to get.
     * @tparam PARAM: should one of boolean_t, integer_t, float_t, string_t or other integer or float types.
     */
    template <class PARAM>
    bool get(PARAM& val) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief get size of array or table.
     * @return size_t: size of array or table.
     * @throw type_error: if the type is neither array nor table.
     * @pre To prevent throwing exceptions, call `is_array()`, or `is_table()` and confirm the return value.
     */
    size_t size(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief operator[] of array.
     * @param index[in]: appointed index of array.
     * @throw type_error: if the type is not array.
     * @throw std::out_of_range: if `index` is out of range of array.
     * @pre To prevent throwing exceptions, call `is_array()` and confirm the return value.
     */
    const item_t& operator[](size_t index) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief operator[] of table.
     * @param key[in]: appointed key of table.
     * @throw type_error: if the type is not table.
     * @throw std::out_of_range: if `key` is not found in the table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
     */
    const item_t& operator[](const key_t& key) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Check if the table contains the specified key, like std::map::contains() in C++20.
     * @param key[in]: The key to check for existence in the table.
     * @return true if the key exists in the table, false otherwise.
     * @throw type_error: if the type is not table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
     */
    bool contains(const key_t& key) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get an iterator to the beginning of the array.
     * @return array_iterator: an iterator pointing to the first element of the array.
     * @throw type_error: if the type is not array.
     * @pre To prevent throwing exceptions, call `is_array()` and confirm the return value.
     */
    array_iterator array_begin(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get an iterator to the end of the array.
     * @return array_iterator: an iterator pointing to the end of the array.
     * @throw type_error: if the type is not array.
     * @pre To prevent throwing exceptions, call `is_array()` and confirm the return value.
     */
    array_iterator array_end(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get an iterator to the beginning of the table.
     * @return table_iterator: an iterator pointing to the first element of the table.
     * @throw type_error: if the type is not table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
     */
    table_iterator table_begin(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get an iterator to the end of the table.
     * @return table_iterator: an iterator pointing to the end of the table.
     * @throw type_error: if the type is not table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
     */
    table_iterator table_end(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get a range of the array.
     * @return array_range_t: a range object containing iterators to the beginning and end of the array.
     * @throw type_error: if the type is not array.
     * @pre To prevent throwing exceptions, call `is_array()` and confirm the return value.
     */
    const array_range_t array_range(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get a range of the table.
     * @return table_range_t: a range object containing iterators to the beginning and end of the table.
     * @throw type_error: if the type is not table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm the return value.
     */
    const table_range_t table_range(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Insert a value at the [keys] spot.
     * @param keys[in]: appointed spot to be inserted.
     * @param val[in]: A value to be inserted.
     * @throw parse_error: [keys] spot is inappropreate.
     * @note this method is intended to be used in parsing process.
     */
    void merge(std::vector<key_t> keys, item_t val);
    /////////////////////////////////////////////////////////////////////////////

 private:
    item_t* push(const key_t& key, const item_t& val);
    void insert_empty_table(const std::vector<key_t>& brackets);
    void insert_new_table(const std::vector<key_t>& brackets, std::vector<key_t> keys, item_t val);
    void parse_main(view_t& view);
    /////////////////////////////////////////////////////////////////////////////

 private:
    enum type_t : int {
        TYPE_BOOLEAN = 0,
        TYPE_INTEGER,
        TYPE_FLOAT,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_TABLE,
    } type;

    union {
        boolean_t b;
        integer_t i;
        float_t d;
    } u = {false};
    // to keep source code clean, string, array and table are not in union.
    // if you want to use union, you can use std::variant instead, but it requires C++17.
    string_t s;
    std::shared_ptr<std::vector<item_t>> v;
    std::shared_ptr<std::map<key_t, item_t>> m;
    /////////////////////////////////////////////////////////////////////////////
};
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief This is the template specialization when PARAM is string_t.
 */
template <>
bool item_t::get<string_t>(string_t& val) const noexcept;
/////////////////////////////////////////////////////////////////////////////

/*
 * @brief Getter of param[out] version. supported types are boolean, integer, float, and string.
 * @param val[out]: gotten value to be loaded.
 * @return true/false: success/fail to get.
 * @tparam PARAM: should one of boolean_t, integer_t, float_t, string_t or other integer or float types.
 * @note When PARAM is string_t, then get<string_t>() is called instead.
 */
template <class PARAM>
bool item_t::get(PARAM& val) const noexcept {
    if (std::is_same<PARAM, boolean_t>() && type == TYPE_BOOLEAN) {
        val = u.b;
    } else if (std::is_same<PARAM, integer_t>() && type == TYPE_INTEGER) {
        val = u.i;
    } else if (std::is_same<PARAM, float_t>() && type == TYPE_FLOAT) {
        val = u.d;
    } else if (std::is_integral<PARAM>() && not std::is_same<PARAM, boolean_t>() && type == TYPE_INTEGER) {
        val = static_cast<PARAM>(u.i);
    } else if (std::is_integral<PARAM>() && not std::is_same<PARAM, boolean_t>() && type == TYPE_FLOAT) {
        val = static_cast<PARAM>(u.d);
    } else if (std::is_floating_point<PARAM>() && type == TYPE_INTEGER) {
        val = static_cast<PARAM>(u.i);
    } else if (std::is_floating_point<PARAM>() && type == TYPE_FLOAT) {
        val = static_cast<PARAM>(u.d);
    } else {
        return false;
    }

    return true;
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload

#endif  // TOMLOAD_TOMLOAD_H
