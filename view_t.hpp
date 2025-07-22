
#ifndef VIEW_T_HPP
#define VIEW_T_HPP

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

inline bool starts_with(view_t view, view_t x) {
    return view.substr(0, x.size()) == x;
}

inline bool ends_with(view_t view, view_t x) {
    return view.size() >= x.size() && view.compare(view.size() - x.size(), view_t::npos, x) == 0;
}

}  // namespace tomload

#endif  // VIEW_T_HPP
