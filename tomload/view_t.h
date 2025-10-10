// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

/*
 * @file tomload/view_t.h
 * @brief Header file for view_t class.
 * @details This file defines the view_t class, which is a wrapper around std::string_view or string_view14,
 *          providing utility functions for string manipulation.
 * @note target version of C++ is C++14. 
 */

#ifndef TOMLOAD_VIEW_T_H_
#define TOMLOAD_VIEW_T_H_

#include <algorithm>
#include <string_view14.hpp>

namespace tomload {

using view_t = string_view14;
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Same as std::string_view::starts_with() in C++ 20.
 */
bool starts_with(view_t view, view_t x);
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Same as std::string_view::ends_with() in C++ 20.
 */
bool ends_with(view_t view, view_t x);
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Same as std::string_view::contains() in C++ 23.
 */
bool contains(view_t view, view_t x);
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function like Python str.startswith([list]).
 */
bool starts_with(view_t view, std::initializer_list<const char*> list);
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function like Python str.endswith([list]).
 */
bool ends_with(view_t view, std::initializer_list<const char*> list);
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function, expand list.
 */
bool contains(view_t view, std::initializer_list<const char*> list);
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload

#endif  // TOMLOAD_VIEW_T_H_
