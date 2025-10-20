// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

/*
 * @file tomload/tomload.h
 * @brief Header file for tomload library.
 * @details This file defines the item_t class and its methods for parsing and handling TOML data.
 *          `tomload::item_t` is main class of this library.
 *          typical usage is shown in example.
 *
 *          `tomload::item_t` lacks the following three capabilities:
 *            (1) the ability to output TOML strings,
 *            (2) the ability to read Date and Time data, and
 *            (3) the ability to read Array of Tables.
 * @note target version of C++ is C++14. 
 * @example
 *      tomload::item_t item("[root]\r\narray = [1, 2, 3]\r\n");
 *      for (auto i : item) {
 *          std::cout << i.first;  // => "root"
 *          for (auto j : i.second) {
 *              std::cout << j.first;  // => "array"
 *              for (auto k : j.second) {
 *                  std::cout << k.get_integer();  // => 1, 2, 3 
 *              }
 *          }
 *      }
 */

#ifndef TOMLOAD_TOMLOAD_H_
#define TOMLOAD_TOMLOAD_H_

#include <algorithm>
#include <cstdint>
#include <exception>
#include <map>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "tomload/view_t.h"

namespace tomload {

/*
 * @class parse_error
 * @brief Exception class for parsing errors.
 * @details This class is derived from std::runtime_error and is used to indicate errors during parsing.
 */
class parse_error : public std::runtime_error {
 public:
    explicit parse_error(const std::string& what_arg) :
        runtime_error(what_arg) {
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
    explicit type_error(const std::string& what_arg) :
        runtime_error(what_arg) {
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

class item_t;
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
struct single_construct_t { explicit single_construct_t() = default; };
constexpr single_construct_t single_construct;

/**
 * @class item_t
 * @brief A versatile container class for representing and manipulating parsed TOML data.
 *
 * The `item_t` class serves as a unified data structure for holding values parsed from TOML (Tom's Obvious, Minimal Language) documents.
 * It supports all TOML data types, including booleans, integers, floats, strings, arrays, and tables.
 *
 * This class provides type-safe access to values, type inspection utilities, and structured traversal of arrays and tables.
 * It is designed to preserve the hierarchical and strongly typed nature of TOML, making it ideal for configuration parsing and structured data handling.
 */
class item_t {
 public:
    item_t(void) = delete;  // Default constructor is deleted.
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Constructor that initializes item_t from raw TOML string.
     * @param view[in]: The view_t object containing raw TOML string.
     *                  TOML string must contain at least one key-value pair or
     *                  completely empty (not allowed single value, like
     *                  "true" or "123").
     * @throws parse_error: if the view cannot be parsed correctly.
     * @note Most users must use only this constructor to parse TOML string.
     */
    explicit item_t(view_t view);
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @defgroup SingleConstruct Constructors with Single Element
     * @brief A set of constructors used to create item_t with single element.
     *
     * Main purpose of these constructors are testing. Most users does not need use these.
     */

    /*
     * @ingroup SingleConstruct
     * @brief Constructor with boolean.
     * @param single_construct_t[in]: placeholder.
     * @param val[in]: pointer of input boolean.
     */
    item_t(single_construct_t, boolean_t val) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup SingleConstruct
     * @brief Constructor with integer.
     * @param single_construct_t[in]: placeholder.
     * @param val[in]: pointer of input integer.
     */
    item_t(single_construct_t, integer_t val) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup SingleConstruct
     * @brief Constructor with float.
     * @param single_construct_t[in]: placeholder.
     * @param val[in]: pointer of input float.
     */
    item_t(single_construct_t, float_t val) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup SingleConstruct
     * @brief Constructor with array.
     * @param single_construct_t[in]: placeholder.
     * @param val[in]: pointer of input array.
     */
    item_t(single_construct_t, string_t&& val) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup SingleConstruct
     * @brief Constructor with table.
     * @param single_construct_t[in]: placeholder.
     * @param val[in]: pointer of input table.
     */
    item_t(single_construct_t, std::shared_ptr<std::vector<item_t>> val) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup SingleConstruct
     * @brief Constructor with table.
     * @param single_construct_t[in]: placeholder.
     * @param val[in]: pointer of input table.
     */
    item_t(single_construct_t, std::shared_ptr<std::map<key_t, item_t>> val) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @defgroup TypeCheckers Type Checking Functions
     * @brief A set of functions used to determine the type of an item.
     *
     * These functions allow you to check whether an item is of a specific type,
     * such as boolean, integer, float, string, array, or table.
     */

    /*
     * @ingroup TypeCheckers
     * @brief Type checker for boolean.
     */
    bool is_boolean(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup TypeCheckers
     * @brief Type checker for integer.
     */
    bool is_integer(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup TypeCheckers
     * @brief Type checker for float.
     */
    bool is_float(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup TypeCheckers
     * @brief Type checker for string.
     */
    bool is_string(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup TypeCheckers
     * @brief Type checker for array.
     */
    bool is_array(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup TypeCheckers
     * @brief Type checker for table.
     */
    bool is_table(void) const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @defgroup Getters Get the Value
     * @brief A set of functions used to get the specified typed value.
     *
     * These functions allow you to get value an item is of a specific type,
     * such as boolean, integer, float, string.
     *
     * A tomload::type_error is raised when the type is mismatched.
     */

    /*
     * @ingroup Getters
     * @brief Getter of boolean value.
     * @return boolean value.
     * @throw tomload::type_error: when type is mismatched.
     * @pre in order to prevent throw, call is_boolean() and confirm its return value.
     */
    boolean_t get_boolean(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup Getters
     * @brief Getter of integer value.
     * @return integer value.
     * @throw tomload::type_error: when type is mismatched.
     * @pre in order to prevent throw, call is_integer() and confirm its return value.
     */
    integer_t get_integer(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup Getters
     * @brief Getter of float value.
     * @return float value.
     * @throw tomload::type_error: when type is mismatched.
     * @pre in order to prevent throw, call is_float() and confirm its return value.
     */
    float_t get_float(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup Getters
     * @brief Getter of string value.
     * @return string value.
     * @throw tomload::type_error: when type is mismatched.
     * @pre in order to prevent throw, call is_string() and confirm its return value.
     */
    string_t get_string(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @ingroup Getters
     * @brief Getter of param[out] version. supported types are boolean, integer, float, and string.
     * @param val[out]: gotten value to be loaded.
     * @return true/false: success/fail to get.
     * @tparam PARAM: should one of boolean_t, integer_t, float_t, string_t or other integer or float types.
     */
    template <class PARAM>
    bool get(PARAM& val) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief get size of array or table.
     * @return size_t: size of array or table.
     * @throw type_error: if the type is neither array nor table.
     * @pre To prevent throwing exceptions, call `is_array()`, or `is_table()` and confirm its return value.
     */
    size_t size(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief check the array or table is empty or not.
     * @return bool: array or table is empty.
     * @throw type_error: if the type is neither array nor table.
     * @pre To prevent throwing exceptions, call `is_array()`, or `is_table()` and confirm its return value.
     */
    bool empty(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief operator[] of array.
     * @param index[in]: appointed index of array.
     * @throw type_error: if the type is not array.
     * @throw std::out_of_range: if `index` is out of range of array.
     * @pre To prevent throwing exceptions, call `is_array()` and confirm its return value.
     */
    const item_t& operator[](size_t index) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief operator[] of table.
     * @param key[in]: appointed key of table.
     * @throw type_error: if the type is not table.
     * @throw std::out_of_range: if `key` is not found in the table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm its return value.
     */
    const item_t& operator[](const key_t& key) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Check if the table contains the specified key, like std::map::contains() in C++20.
     * @param key[in]: The key to check for existence in the table.
     * @return true if the key exists in the table, false otherwise.
     * @throw type_error: if the type is not table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm its return value.
     */
    bool contains(const key_t& key) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get an iterator to the beginning of the array.
     * @return array_iterator: an iterator pointing to the first element of the array.
     * @throw type_error: if the type is not array.
     * @pre To prevent throwing exceptions, call `is_array()` and confirm its return value.
     */
    array_iterator array_begin(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get an iterator to the end of the array.
     * @return array_iterator: an iterator pointing to the end of the array.
     * @throw type_error: if the type is not array.
     * @pre To prevent throwing exceptions, call `is_array()` and confirm its return value.
     */
    array_iterator array_end(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get an iterator to the beginning of the table.
     * @return table_iterator: an iterator pointing to the first element of the table.
     * @throw type_error: if the type is not table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm its return value.
     */
    table_iterator table_begin(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get an iterator to the end of the table.
     * @return table_iterator: an iterator pointing to the end of the table.
     * @throw type_error: if the type is not table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm its return value.
     */
    table_iterator table_end(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get a range of the array.
     * @return array_range_t: a range object containing iterators to the beginning and end of the array.
     * @throw type_error: if the type is not array.
     * @pre To prevent throwing exceptions, call `is_array()` and confirm its return value.
     */
    const array_range_t array_range(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Get a range of the table.
     * @return table_range_t: a range object containing iterators to the beginning and end of the table.
     * @throw type_error: if the type is not table.
     * @pre To prevent throwing exceptions, call `is_table()` and confirm its return value.
     */
    const table_range_t table_range(void) const;
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @brief Construct inline table from multiple keys-value pairs.
     * @param key_vals[in]: keys-value pairs.
     * @throw parse_error: type is not table, or [keys] spot is inappropreate.
     * @note this method is intended to be used in parsing process.
     */
    void set_inline_table_keys_value(std::vector<std::pair<std::vector<key_t>, item_t>> key_vals);
    /////////////////////////////////////////////////////////////////////////////

 private:
    /*
     * @throw parse_error: thrown if the this->type is not TYPE_TABLE.
     * @return A pointer to the inserted `val`. If the `key` is already registered, `val` will not be inserted;
     *         instead, a pointer to the already registered `item_t` is returned.
     */
    item_t* push(const key_t& key, item_t val);
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @pre brackets_set.empty() == false.
     */
    item_t* insert_brackets_table(const std::vector<std::vector<key_t>>& brackets_set);
    /////////////////////////////////////////////////////////////////////////////

    /*
    * @pre p_item != nullptr.
    */
    void insert_keys_val(item_t* p_item, std::vector<key_t> keys, item_t val);
    /////////////////////////////////////////////////////////////////////////////

    /*
     * @param view[in,out]: toml string.
     */
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
        TYPE_INLINE_TABLE,
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
 * @brief JSON format out-stream.
 * @param os[in,out]: out-stream.
 * @param item[in]: TOML data.
 * @note supported escape characters are only '\"', '\t', '\n', '\r', and '\\'.
 * @return `os`
 */
std::ostream& operator<<(std::ostream& os, const item_t& item);
/////////////////////////////////////////////////////////////////////////////

/*
 * @ingroup Getters
 * @brief This is the template specialization when PARAM is string_t.
 */
template <>
bool item_t::get<string_t>(string_t& val) const;
/////////////////////////////////////////////////////////////////////////////

/*
 * @ingroup Getters
 * @brief Getter of param[out] version. supported types are boolean, integer, float, and string.
 * @param val[out]: gotten value to be loaded.
 * @return true/false: success/fail to get.
 * @tparam PARAM: should one of boolean_t, integer_t, float_t, string_t or other integer or float types.
 * @note When PARAM is string_t, then get<string_t>() is called instead.
 */
template <class PARAM>
bool item_t::get(PARAM& val) const {
    if (std::is_same<PARAM, boolean_t>() && is_boolean()) {
        val = u.b;
    } else if (std::is_same<PARAM, integer_t>() && is_integer()) {
        val = u.i;
    } else if (std::is_same<PARAM, float_t>() && is_float()) {
        val = u.d;
    } else if (std::is_integral<PARAM>() && not std::is_same<PARAM, boolean_t>() && is_integer()) {
        val = static_cast<PARAM>(u.i);
    } else if (std::is_integral<PARAM>() && not std::is_same<PARAM, boolean_t>() && is_float()) {
        val = static_cast<PARAM>(u.d);
    } else if (std::is_floating_point<PARAM>() && is_integer()) {
        val = static_cast<PARAM>(u.i);
    } else if (std::is_floating_point<PARAM>() && is_float()) {
        val = static_cast<PARAM>(u.d);
    } else {
        return false;
    }

    return true;
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload

#endif  // TOMLOAD_TOMLOAD_H_
