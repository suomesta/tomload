#ifndef PARSER_H
#define PARSER_H

#include "tomload.h"
#include "view_t.hpp"

namespace tomload {

bool wait_newline(view_t& view);

void skip_space(view_t& view, view_t spaces, bool skip_comment);

item_t parse_array(view_t& view);

item_t parse_item(view_t& view);

void insert_table(item_t& root, item_t& item, const std::vector<key_t>& brackets, const std::vector<key_t>& keys);

void parse_main(item_t& root, view_t& view);

}  // namespace tomload

#endif  // PARSER_H
