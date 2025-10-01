/*
 * @file tomload/parser.h
 * @note target version of C++ is C++14. 
 */

#ifndef TOMLOAD_PARSER_H
#define TOMLOAD_PARSER_H

#include "tomload/tomload.h"
#include "tomload/view_t.h"

namespace tomload {

/**
 * @brief Checks for a newline at the beginning of the input view.
 *
 * This function skips leading whitespace characters (`' '`, `'\t'`, `'\r'`) and comments in the input view.
 *
 * @param view[in,out]: A reference to the input view to be examined and potentially modified.
 * @return true if a newline was found and handled; false otherwise.
 */
bool wait_newline(view_t& view);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief Skips leading whitespace and optionally comments in the input view.
 *
 * This function removes leading characters from the input view that match any character
 * in the `spaces` set. If `skip_comment` is true and the view starts with a comment
 * character (`'#'`), it removes all characters up to and including the next newline.
 * The function may call itself recursively if a comment is removed and further whitespace
 * or comments may follow.
 *
 * @param view[in,out]: A reference to the input view to be modified.
 * @param spaces[in]: A set of characters considered as whitespace (e.g., " \t\r").
 * @param skip_comment[in]: If true, lines starting with '#' are treated as comments and skipped.
 */
void skip_space(view_t& view, view_t spaces, bool skip_comment);
/////////////////////////////////////////////////////////////////////////////

item_t parse_array(view_t& view);
/////////////////////////////////////////////////////////////////////////////

void insert_key_value(std::map<key_t, item_t>* p, std::vector<key_t> keys, item_t value);
/////////////////////////////////////////////////////////////////////////////

item_t parse_inline_table(view_t& view);
/////////////////////////////////////////////////////////////////////////////

item_t parse_item(view_t& view);
/////////////////////////////////////////////////////////////////////////////

std::vector<key_t> parse_keys(view_t& view);
/////////////////////////////////////////////////////////////////////////////

void check_duplex_keys(const std::vector<key_t>& keys, const std::vector<std::vector<key_t>>& brackets_set);
/////////////////////////////////////////////////////////////////////////////

}  // namespace tomload

#endif  // TOMLOAD_PARSER_H
