#ifndef PARSER_H
#define PARSER_H

#include "tomload/tomload.h"
#include "tomload/view_t.hpp"

namespace tomload {

bool wait_newline(view_t& view);

void skip_space(view_t& view, view_t spaces, bool skip_comment);

item_t parse_array(view_t& view);

item_t parse_item(view_t& view);

std::vector<key_t> parse_keys(view_t& view);

}  // namespace tomload

#endif  // PARSER_H
