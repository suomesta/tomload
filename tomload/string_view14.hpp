// Copyright (c) 2025 suomesta
// Distributed under the MIT Software License

/**
 * @file    tomload/string_view14.hpp
 * @brief   define string_view14 class.
 *          string_view14 is string_view class for C++14 compiler.
 * @remark  the target is C++14 or more.
 */

#ifndef TOMLOAD_STRING_VIEW14_HPP_
#define TOMLOAD_STRING_VIEW14_HPP_

#include <algorithm>
#include <cstddef>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>

/**
 * @class   string_view14.
 * @brief   string_view14 has almost same interfaces and behaviors with std::string_view in C++17.
 *          string_view14 can be compiled on C++14.
 *
 *          string_view14 just refers char string. never allocates heap memory.
 *          Most functions in string_view14 are constexpr.
 *
 *          Some minor differences with std::string_view in C++17 are:
 *            - only char is supported as element type.
 *            - is independent from std::char_traits.
 *            - const_reverse_iterator is not 100% complied with standard requirements (but no actual disadvantages in normal use).
 *            - literal definition is not ""sv but ""_sv, because user literal definition should starts with "_".
 *            - no functions for std::hash.
 *            - bonus. starts_with()/ends_with() in C++20 and contains() in C++23 are supported.
 *
 *          The usage is completely identical with std::string_view.
 *              string_view14 sv{"ABCDE"};
 *              std::cout << sv;  // => "ABCDE"
 *              sv.remove_prefix(2);
 *              std::cout << sv;  // => "CDE"
 */
class string_view14 {
 public:
    // Types
    using value_type = char;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using const_iterator = const value_type*;
    using iterator = const_iterator;
    /**
     * @class   const_reverse_iterator.
     * @brief   C++14 std::reverse_iterator<> does not allow to construct as constexpr variable.
     *          This const_reverse_iterator class' constructors are constexpr. string_view14 can
     *          support constexpr rbegin()/rend() to make use of this const_reverse_iterator class.
     */
    class const_reverse_iterator {
     public:
        // Constructors and assignment
        constexpr const_reverse_iterator() = default;
        constexpr const_reverse_iterator(const const_reverse_iterator&) = default;
        constexpr explicit const_reverse_iterator(const char* p) noexcept;
        constexpr const_reverse_iterator& operator=(const const_reverse_iterator&) = default;
        /////////////////////////////////////////////////////////////////////////////

        // Operators
        constexpr const char& operator*() const;
        constexpr const char* operator->() const;
        constexpr const_reverse_iterator& operator++();
        constexpr const_reverse_iterator operator++(int);
        constexpr const_reverse_iterator& operator--();
        constexpr const_reverse_iterator operator--(int);
        constexpr const_reverse_iterator operator+(int off) const;
        constexpr const_reverse_iterator& operator+=(int off);
        constexpr int operator-(const_reverse_iterator rhs) const;
        constexpr const_reverse_iterator operator-(int off) const;
        constexpr const_reverse_iterator& operator-=(int off);
        /////////////////////////////////////////////////////////////////////////////

     private:
         const char* ptr_ = nullptr;
    };
    using reverse_iterator = const_reverse_iterator;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    /////////////////////////////////////////////////////////////////////////////

    // Constant
    static constexpr size_type npos{static_cast<size_type>(-1)};
    /////////////////////////////////////////////////////////////////////////////

 public:
    // Constructors and assignment
    constexpr string_view14() noexcept = default;
    constexpr string_view14(const string_view14&) noexcept = default;
    constexpr string_view14(const char* str);
    constexpr string_view14(const char* str, size_type len);
    string_view14& operator=(const string_view14&) = default;
    /////////////////////////////////////////////////////////////////////////////

    // Iterator support
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator end() const noexcept;
    constexpr const_iterator cbegin() const noexcept;
    constexpr const_iterator cend() const noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr const_reverse_iterator rend() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    // Element access
    constexpr const char& operator[](size_type pos) const;
    constexpr const char& at(size_type pos) const;
    constexpr const char& front() const;
    constexpr const char& back() const;
    constexpr const char* data() const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    // Capacity
    constexpr size_type size() const noexcept;
    constexpr size_type length() const noexcept;
    constexpr size_type max_size() const noexcept;
    constexpr bool empty() const noexcept;
    /////////////////////////////////////////////////////////////////////////////

    // Modifiers
    constexpr void remove_prefix(size_type n);
    constexpr void remove_suffix(size_type n);
    constexpr void swap(string_view14& s) noexcept;
    /////////////////////////////////////////////////////////////////////////////

    // String operations
    size_type copy(char* s, size_type n, size_type pos = 0) const;
    constexpr string_view14 substr(size_type pos = 0, size_type n = npos) const;
    constexpr int compare(string_view14 sv) const noexcept;
    constexpr int compare(size_type pos1, size_type n1, string_view14 sv) const;
    constexpr int compare(size_type pos1, size_type n1, string_view14 sv, size_type pos2, size_type n2) const;
    constexpr int compare(const char* s) const;
    constexpr int compare(size_type pos1, size_type n1, const char* s) const;
    constexpr int compare(size_type pos1, size_type n1, const char* s, size_type n2) const;
    /////////////////////////////////////////////////////////////////////////////

    // Searching
    constexpr bool starts_with(string_view14 x) const noexcept;
    constexpr bool starts_with(char x) const noexcept;
    constexpr bool starts_with(const char* x) const;
    constexpr bool ends_with(string_view14 x) const noexcept;
    constexpr bool ends_with(char x) const noexcept;
    constexpr bool ends_with(const char* x) const;
    constexpr bool contains(string_view14 x) const noexcept;
    constexpr bool contains(char x) const noexcept;
    constexpr bool contains(const char* x) const;
    constexpr size_type find(string_view14 sv, size_type pos = 0) const noexcept;
    constexpr size_type find(char c, size_type pos = 0) const noexcept;
    constexpr size_type find(const char* s, size_type pos, size_type n) const;
    constexpr size_type find(const char* s, size_type pos = 0) const;
    constexpr size_type rfind(string_view14 sv, size_type pos = npos) const noexcept;
    constexpr size_type rfind(char c, size_type pos = npos) const noexcept;
    constexpr size_type rfind(const char* s, size_type pos, size_type n) const;
    constexpr size_type rfind(const char* s, size_type pos = npos) const;
    constexpr size_type find_first_of(string_view14 sv, size_type pos = 0) const noexcept;
    constexpr size_type find_first_of(char c, size_type pos = 0) const noexcept;
    constexpr size_type find_first_of(const char* s, size_type pos, size_type n) const;
    constexpr size_type find_first_of(const char* s, size_type pos = 0) const;
    constexpr size_type find_last_of(string_view14 sv, size_type pos = npos) const noexcept;
    constexpr size_type find_last_of(char c, size_type pos = npos) const noexcept;
    constexpr size_type find_last_of(const char* s, size_type pos, size_type n) const;
    constexpr size_type find_last_of(const char* s, size_type pos = npos) const;
    constexpr size_type find_first_not_of(string_view14 sv, size_type pos = 0) const noexcept;
    constexpr size_type find_first_not_of(char c, size_type pos = 0) const noexcept;
    constexpr size_type find_first_not_of(const char* s, size_type pos, size_type n) const;
    constexpr size_type find_first_not_of(const char* s, size_type pos = 0) const;
    constexpr size_type find_last_not_of(string_view14 sv, size_type pos = npos) const noexcept;
    constexpr size_type find_last_not_of(char c, size_type pos = npos) const noexcept;
    constexpr size_type find_last_not_of(const char* s, size_type pos, size_type n) const;
    constexpr size_type find_last_not_of(const char* s, size_type pos = npos) const;
    /////////////////////////////////////////////////////////////////////////////

 private:
    const char* data_ = nullptr;
    size_type size_ = 0;
};
/////////////////////////////////////////////////////////////////////////////

// Non-member comparison functions
constexpr bool operator==(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept;
constexpr bool operator!=(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept;
constexpr bool operator<(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept;
constexpr bool operator<=(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept;
constexpr bool operator>(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept;
constexpr bool operator>=(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept;
/////////////////////////////////////////////////////////////////////////////

// Non-member comparison functions
constexpr bool operator==(string_view14 lhs, string_view14 rhs) noexcept;
constexpr bool operator!=(string_view14 lhs, string_view14 rhs) noexcept;
constexpr bool operator<(string_view14 lhs, string_view14 rhs) noexcept;
constexpr bool operator<=(string_view14 lhs, string_view14 rhs) noexcept;
constexpr bool operator>(string_view14 lhs, string_view14 rhs) noexcept;
constexpr bool operator>=(string_view14 lhs, string_view14 rhs) noexcept;
/////////////////////////////////////////////////////////////////////////////

// Output
inline std::ostream& operator<<(std::ostream& os, string_view14 sv);
/////////////////////////////////////////////////////////////////////////////

// Literal
inline namespace literals {
inline namespace string_view14_literals {
constexpr string_view14 operator""_sv(const char* str, std::size_t length);
}  // string_view14_literals
}  // literals
/////////////////////////////////////////////////////////////////////////////

namespace string_view14_helper {

constexpr string_view14::size_type constexpr_strlen(const char* str) {
    string_view14::size_type len = 0;
    while (*str++) {
        len++;
    }
    return len;
}
/////////////////////////////////////////////////////////////////////////////

template <class T>
constexpr void constexpr_swap(T& t1, T& t2) {
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}
/////////////////////////////////////////////////////////////////////////////

}  // namespace string_view14_helper

constexpr string_view14::const_reverse_iterator::const_reverse_iterator(const char* p) noexcept :
    ptr_(p)
{}
/////////////////////////////////////////////////////////////////////////////

constexpr const char& string_view14::const_reverse_iterator::operator*() const {
    const char* tmp = ptr_;
    return *--tmp;
}
/////////////////////////////////////////////////////////////////////////////

constexpr const char* string_view14::const_reverse_iterator::operator->() const {
    const char* tmp = ptr_;
    return --tmp;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator& string_view14::const_reverse_iterator::operator++() {
    --ptr_;
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator string_view14::const_reverse_iterator::operator++(int) {
    const_reverse_iterator tmp = *this;
    --ptr_;
    return tmp;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator& string_view14::const_reverse_iterator::operator--() {
    ++ptr_;
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator string_view14::const_reverse_iterator::operator--(int) {
    const_reverse_iterator tmp = *this;
    ++ptr_;
    return tmp;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator string_view14::const_reverse_iterator::operator+(int off) const {
    return const_reverse_iterator(ptr_ - off);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator& string_view14::const_reverse_iterator::operator+=(int off) {
    ptr_ -= off;
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

constexpr int string_view14::const_reverse_iterator::operator-(const_reverse_iterator rhs) const {
    return rhs.ptr_ - ptr_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator string_view14::const_reverse_iterator::operator-(int off) const {
    return const_reverse_iterator(ptr_ + off);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator& string_view14::const_reverse_iterator::operator-=(int off) {
    ptr_ += off;
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::string_view14(const char* str) :
    data_(str),
    size_(string_view14_helper::constexpr_strlen(str))
{}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::string_view14(const char* str, size_type len) :
    data_(str),
    size_(len)
{}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_iterator string_view14::begin() const noexcept {
    return data_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_iterator string_view14::end() const noexcept {
    return data_ + size_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_iterator string_view14::cbegin() const noexcept {
    return data_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_iterator string_view14::cend() const noexcept {
    return data_ + size_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator string_view14::rbegin() const noexcept {
    return const_reverse_iterator{data_ + size_};
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator string_view14::rend() const noexcept {
    return const_reverse_iterator{data_};
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator string_view14::crbegin() const noexcept {
    return const_reverse_iterator{data_ + size_};
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::const_reverse_iterator string_view14::crend() const noexcept {
    return const_reverse_iterator{data_};
}
/////////////////////////////////////////////////////////////////////////////

constexpr const char& string_view14::operator[](size_type pos) const {
    return *(data_ + pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr const char& string_view14::at(size_type pos) const {
    if (pos >= size_) {
        throw std::out_of_range("string_view14::at()");
    }
    return *(data_ + pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr const char& string_view14::front() const {
    return *data_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr const char& string_view14::back() const {
    return *(data_ + size_ - 1);
}
/////////////////////////////////////////////////////////////////////////////

constexpr const char* string_view14::data() const noexcept {
    return data_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::size() const noexcept {
    return size_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::length() const noexcept {
    return size_;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::empty() const noexcept {
    return size_ == 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr void string_view14::remove_prefix(size_type n) {
    data_ += n;
    size_ -= n;
}
/////////////////////////////////////////////////////////////////////////////

constexpr void string_view14::remove_suffix(size_type n) {
    size_ -= n;
}
/////////////////////////////////////////////////////////////////////////////

constexpr void string_view14::swap(string_view14& s) noexcept {
    string_view14_helper::constexpr_swap(data_, s.data_);
    string_view14_helper::constexpr_swap(size_, s.size_);
}
/////////////////////////////////////////////////////////////////////////////

inline size_t string_view14::copy(char* s, size_type n, size_type pos/* = 0*/) const {
    if (pos < size_) {
        size_type len = (std::min)(size_ - pos, n);
        for (size_type i = 0; i < len; i++) {
            s[i] = data_[pos + i];
        }
        return len;
    } else {
        return 0;
    }
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14 string_view14::substr(size_type pos/* = 0*/, size_type n/* = npos*/) const {
    if (pos > size_) {
        throw std::out_of_range("string_view14::substr()");
    }
    size_type len = (std::min)(size_ - pos, n);
    return string_view14(data_ + pos, len);
}
/////////////////////////////////////////////////////////////////////////////

constexpr int string_view14::compare(string_view14 sv) const noexcept {
    size_type len = (std::min)(size_, sv.size());
    for (size_type i = 0; i < len; i++) {
        if (data_[i] < sv[i]) {
            return -1;
        } else if (data_[i] > sv[i]) {
            return 1;
        }
    }
    if (size_ < sv.size()) {
        return -1;
    } else if (size_ > sv.size()) {
        return 1;
    } else {
        return 0;
    }
}
/////////////////////////////////////////////////////////////////////////////

constexpr int string_view14::compare(size_type pos1, size_type n1, string_view14 sv) const {
    return substr(pos1, n1).compare(sv);
}
/////////////////////////////////////////////////////////////////////////////

constexpr int string_view14::compare(size_type pos1, size_type n1, string_view14 sv, size_type pos2, size_type n2) const {
    return substr(pos1, n1).compare(sv.substr(pos2, n2));
}
/////////////////////////////////////////////////////////////////////////////

constexpr int string_view14::compare(const char* s) const {
    return compare(string_view14(s));
}
/////////////////////////////////////////////////////////////////////////////

constexpr int string_view14::compare(size_type pos1, size_type n1, const char* s) const {
    return substr(pos1, n1).compare(string_view14(s));
}
/////////////////////////////////////////////////////////////////////////////

constexpr int string_view14::compare(size_type pos1, size_type n1, const char* s, size_type n2) const {
    return substr(pos1, n1).compare(string_view14(s, n2));
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::starts_with(string_view14 x) const noexcept {
    return substr(0, x.size()) == x;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::starts_with(char x) const noexcept {
    return starts_with(string_view14(&x, 1));
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::starts_with(const char* x) const {
    return starts_with(string_view14(x));
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::ends_with(string_view14 x) const noexcept {
    return size_ >= x.size() && compare(size_ - x.size(), npos, x) == 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::ends_with(char x) const noexcept {
    return ends_with(string_view14(&x, 1));
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::ends_with(const char* x) const {
    return ends_with(string_view14(x));
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::contains(string_view14 x) const noexcept {
    return find(x) != npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::contains(char x) const noexcept {
    return find(x) != npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool string_view14::contains(const char* x) const {
    return find(x) != npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find(string_view14 sv, size_type pos/* = 0*/) const noexcept {
    if (pos > size_) {
        return npos;
    }

    for (size_type i = pos; i < size_; i++) {
        string_view14 sub = substr(i, sv.size());
        if (sub == sv) {
            return i;
        }
    }
    return sv.empty() ? pos : npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find(char c, size_type pos/* = 0*/) const noexcept {
    return find(string_view14(&c, 1), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find(const char* s, size_type pos, size_type n) const {
    return find(string_view14(s, n), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find(const char* s, size_type pos/* = 0*/) const {
    return find(string_view14(s), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::rfind(string_view14 sv, size_type pos/* = npos*/) const noexcept {
    size_type target_size = std::min(size_, pos);

    for (size_type i = 0; i <= target_size; i++) {
        size_type idx = target_size - i;
        if (substr(idx, sv.size()) == sv) {
            return idx;
        }
    }
    return npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::rfind(char c, size_type pos/* = npos*/) const noexcept {
    return rfind(string_view14(&c, 1), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::rfind(const char* s, size_type pos, size_type n) const {
    return rfind(string_view14(s, n), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::rfind(const char* s, size_type pos/* = npos*/) const {
    return rfind(string_view14(s), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_first_of(string_view14 sv, size_type pos/* = 0*/) const noexcept {
    for (size_type i = pos; i < size_; i++) {
        if (sv.find(data_[i]) != npos) {
            return i;
        }
    }
    return npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_first_of(char c, size_type pos/* = 0*/) const noexcept {
    return find_first_of(string_view14(&c, 1), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_first_of(const char* s, size_type pos, size_type n) const {
    return find_first_of(string_view14(s, n), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_first_of(const char* s, size_type pos/* = 0*/) const {
    return find_first_of(string_view14(s), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_last_of(string_view14 sv, size_type pos/* = npos*/) const noexcept {
    size_type target_size = std::min(size_, std::max(pos, pos + 1));
    for (size_type i = target_size; i > 0; i--) {
        if (sv.find(data_[i - 1]) != npos) {
            return i - 1;
        }
    }
    return npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_last_of(char c, size_type pos/* = npos*/) const noexcept {
    return find_last_of(string_view14(&c, 1), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_last_of(const char* s, size_type pos, size_type n) const {
    return find_last_of(string_view14(s, n), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_last_of(const char* s, size_type pos/* = npos*/) const {
    return find_last_of(string_view14(s), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_first_not_of(string_view14 sv, size_type pos/* = 0*/) const noexcept {
    for (size_type i = pos; i < size_; i++) {
        if (sv.find(data_[i]) == npos) {
            return i;
        }
    }
    return npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_first_not_of(char c, size_type pos/* = 0*/) const noexcept {
    return find_first_not_of(string_view14(&c, 1), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_first_not_of(const char* s, size_type pos, size_type n) const {
    return find_first_not_of(string_view14(s, n), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_first_not_of(const char* s, size_type pos/* = 0*/) const {
    return find_first_not_of(string_view14(s), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_last_not_of(string_view14 sv, size_type pos/* = npos*/) const noexcept {
    size_type target_size = std::min(size_, std::max(pos, pos + 1));
    for (size_type i = target_size; i > 0; i--) {
        if (sv.find(data_[i - 1]) == npos) {
            return i - 1;
        }
    }
    return npos;
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_last_not_of(char c, size_type pos/* = npos*/) const noexcept {
    return find_last_not_of(string_view14(&c, 1), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_last_not_of(const char* s, size_type pos, size_type n) const {
    return find_last_not_of(string_view14(s, n), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr string_view14::size_type string_view14::find_last_not_of(const char* s, size_type pos/* = npos*/) const {
    return find_last_not_of(string_view14(s), pos);
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator==(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept {
    return (lhs - rhs) == 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator!=(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept {
    return (lhs - rhs) != 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator<(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept {
    return (lhs - rhs) < 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator<=(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept {
    return (lhs - rhs) <= 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator>(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept {
    return (lhs - rhs) > 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator>=(string_view14::const_reverse_iterator lhs, string_view14::const_reverse_iterator rhs) noexcept {
    return (lhs - rhs) >= 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator==(string_view14 lhs, string_view14 rhs) noexcept {
    return lhs.compare(rhs) == 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator!=(string_view14 lhs, string_view14 rhs) noexcept {
    return lhs.compare(rhs) != 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator<(string_view14 lhs, string_view14 rhs) noexcept {
    return lhs.compare(rhs) < 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator<=(string_view14 lhs, string_view14 rhs) noexcept {
    return lhs.compare(rhs) <= 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator>(string_view14 lhs, string_view14 rhs) noexcept {
    return lhs.compare(rhs) > 0;
}
/////////////////////////////////////////////////////////////////////////////

constexpr bool operator>=(string_view14 lhs, string_view14 rhs) noexcept {
    return lhs.compare(rhs) >= 0;
}
/////////////////////////////////////////////////////////////////////////////

inline std::ostream& operator<<(std::ostream& os, string_view14 sv) {
    for (char i : sv) {
        os << i;
    }
    return os;
}
/////////////////////////////////////////////////////////////////////////////

inline namespace literals {
inline namespace string_view14_literals {
constexpr string_view14 operator""_sv(const char* str, std::size_t length) {
    return string_view14(str, length);
}
}  // string_view14_literals
}  // literals
/////////////////////////////////////////////////////////////////////////////

#endif  // TOMLOAD_STRING_VIEW14_HPP_
