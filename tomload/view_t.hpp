/*
 * @file view_t.hpp
 * @brief Header file for view_t class.
 * @details This file defines the view_t class, which is a wrapper around std::string_view or string_view14,
 *          providing utility functions for string manipulation.
 */

#ifndef TOMLOAD_VIEW_T_HPP
#define TOMLOAD_VIEW_T_HPP

#include <initializer_list>

#if __cpp_lib_string_view
#include <string_view>
#else
#include "include/string_view14.hpp"
#endif

namespace tomload {

#if __cpp_lib_string_view
using view_t = std::string_view;
#else
using view_t = string_view14;
#endif

/* 
 * @brief Same as std::string_view::starts_with() in C++ 20.
 */
inline bool starts_with(view_t view, view_t x) {
    return view.substr(0, x.size()) == x;
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Same as std::string_view::ends_with() in C++ 20.
 */
inline bool ends_with(view_t view, view_t x) {
    return view.size() >= x.size() && view.compare(view.size() - x.size(), view_t::npos, x) == 0;
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Same as std::string_view::contains() in C++ 23.
 */
inline bool contains(view_t view, view_t x) {
    return view.find(x) != view_t::npos;
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function like Python str.startswith([list]).
 */
inline bool starts_with(view_t view, std::initializer_list<const char*> list) {
    for (const char* str : list) {
        if (starts_with(view, str)) {
            return true;
        }
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function like Python str.endswith([list]).
 */
inline bool ends_with(view_t view, std::initializer_list<const char*> list) {
    for (const char* str : list) {
        if (ends_with(view, str)) {
            return true;
        }
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function, expand list.
 */
inline bool contains(view_t view, std::initializer_list<const char*> list) {
    for (const char* str : list) {
        if (contains(view, str)) {
            return true;
        }
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload

#endif  // TOMLOAD_VIEW_T_HPP
