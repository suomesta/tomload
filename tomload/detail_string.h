#ifndef DETAIL_STRING_H
#define DETAIL_STRING_H

#include <cstdint>
#include <string>
#include "tomload/tomload.h"
#include "tomload/view_t.hpp"

namespace tomload {

std::string utf8_encode(uint32_t codepoint);

/*
 * @pre `view` must start with "'''"
 */
view_t::size_type get_multi_literal_string_length(view_t view);

string_t parse_multi_literal_string(view_t& view, view_t::size_type length);

/*
 * @pre `view` must start with "'"
 */
view_t::size_type get_literal_string_length(view_t view);

string_t parse_literal_string(view_t& view, view_t::size_type length);

std::string parse_unicode_escape(const view_t& view, int size);
/*
 * @pre `view` must start with '"'
 */
view_t::size_type get_string_length(view_t view);

string_t parse_string(view_t view, view_t::size_type length);

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
view_t::size_type get_bare_length(view_t view);

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
string_t parse_bare_value(view_t view, view_t::size_type length);

}  // namespace tomload

#endif  // DETAIL_STRING_H