/*
 * @file tomload/detail_number.h
 * @note target version of C++ is C++14. 
 */

#ifndef TOMLOAD_DETAIL_NUMBER_H_
#define TOMLOAD_DETAIL_NUMBER_H_

#include "tomload/tomload.h"
#include "tomload/view_t.h"

namespace tomload {

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
view_t::size_type get_radix_length(view_t view);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
integer_t parse_radix_value(view_t view, view_t::size_type length);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
view_t::size_type get_integer_length(view_t view);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
integer_t parse_integer(view_t view, view_t::size_type length);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
view_t::size_type get_float_length(view_t view);
/////////////////////////////////////////////////////////////////////////////

/*
 * @pre `view` must start with one of "+-0123456789"
 */
float_t parse_float(view_t view, view_t::size_type length);
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload

#endif  // TOMLOAD_DETAIL_NUMBER_H_
