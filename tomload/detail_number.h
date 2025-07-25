#ifndef DETAIL_NUMBER_H
#define DETAIL_NUMBER_H

#include "tomload/tomload.h"
#include "tomload/view_t.hpp"

namespace tomload {

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
view_t::size_type get_radix_length(view_t view, view_t allowed);

/*
 * @pre `view` must start with "0x", "0o", or "0b"
 */
integer_t parse_radix_value(view_t view, view_t::size_type length, int base);

}  // namespace tomload

#endif  // DETAIL_NUMBER_H
