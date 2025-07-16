
#ifndef VIEW_T_HPP
#define VIEW_T_HPP

#include <string_view>

using view_t = std::string_view;

inline bool starts_with(view_t view, view_t x) {
    return view.substr(0, x.size()) == x;
}

inline bool ends_with(view_t view, view_t x) {
    return view.size() >= x.size() && view.compare(view.size() - x.size(), view_t::npos, x) == 0;
}

#endif  // VIEW_T_HPP
