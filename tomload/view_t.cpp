/*
 * @file tomload/view_t.cpp
 * @brief implement some functions regarding view_t.
 * @note target version of C++ is C++14. 
 */

#include "tomload/view_t.h"

namespace tomload {

/* 
 * @brief Same as std::string_view::starts_with() in C++ 20.
 */
bool starts_with(view_t view, view_t x) {
    return view.substr(0, x.size()) == x;
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Same as std::string_view::ends_with() in C++ 20.
 */
bool ends_with(view_t view, view_t x) {
    return view.size() >= x.size() && view.compare(view.size() - x.size(), view_t::npos, x) == 0;
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Same as std::string_view::contains() in C++ 23.
 */
bool contains(view_t view, view_t x) {
    return view.find(x) != view_t::npos;
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function like Python str.startswith([list]).
 */
bool starts_with(view_t view, std::initializer_list<const char*> list) {
    return std::any_of(list.begin(), list.end(), [view](const char* str) -> bool {
        return starts_with(view, str);
    });
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function like Python str.endswith([list]).
 */
bool ends_with(view_t view, std::initializer_list<const char*> list) {
    return std::any_of(list.begin(), list.end(), [view](const char* str) -> bool {
        return ends_with(view, str);
    });
}
/////////////////////////////////////////////////////////////////////////////

/* 
 * @brief Util function, expand list.
 */
bool contains(view_t view, std::initializer_list<const char*> list) {
    return std::any_of(list.begin(), list.end(), [view](const char* str) -> bool {
        return contains(view, str);
    });
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload
