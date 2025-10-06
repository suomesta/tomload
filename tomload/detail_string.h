/*
 * @file tomload/detail_string.h
 * @note target version of C++ is C++14. 
 */

#ifndef TOMLOAD_DETAIL_STRING_H_
#define TOMLOAD_DETAIL_STRING_H_

#include <cstdint>
#include <string>
#include "tomload/tomload.h"
#include "tomload/view_t.h"

namespace tomload {

/**
 * @brief Encodes a Unicode code point into its UTF-8 string representation.
 *
 * This function takes a 32-bit Unicode code point and converts it into a UTF-8 encoded string.
 * UTF-8 encoding uses 1 to 4 bytes depending on the value of the code point:
 * - 1 byte for code points in [U+0000, U+007F]
 * - 2 bytes for code points in [U+0080, U+07FF]
 * - 3 bytes for code points in [U+0800, U+FFFF]
 * - 4 bytes for code points in [U+10000, U+10FFFF]
 *
 * If the code point is outside the valid Unicode range (greater than U+10FFFF).
 *
 * @param codepoint The Unicode code point to encode.
 * @return A UTF-8 encoded string representing the input code point.
 * @throw parse_error: when detect invalid unicode escape or surrogate pair in 2 bytes.
 */
std::string utf8_encode(uint32_t codepoint);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with "'''"
 */
view_t::size_type get_multi_literal_string_length(view_t view);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with "'''"
 */
string_t parse_multi_literal_string(view_t& view, view_t::size_type length);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with "'"
 */
view_t::size_type get_literal_string_length(view_t view);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with "'"
 */
string_t parse_literal_string(view_t& view, view_t::size_type length);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must starts with 4 or 8 digits hex
 */
std::string parse_unicode_escape(const view_t& view, int size);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with '"""'
 */
view_t::size_type get_multi_string_length(view_t view);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with '"""'
 */
string_t parse_multi_string(view_t view, view_t::size_type length);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with '"'
 */
view_t::size_type get_string_length(view_t view);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with '"'
 */
string_t parse_string(view_t view, view_t::size_type length);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
view_t::size_type get_bare_length(view_t view);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with A-Za-z0-9_-
 */
string_t parse_bare_value(view_t view, view_t::size_type length);
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload

#endif  // TOMLOAD_DETAIL_STRING_H_
