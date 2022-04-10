/**
 * @file stack.hpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief stack container
 * @version 0.1
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#define FT_NOEXCEPT throw()

namespace ft {

template <typename _T, typename _Container = vector<_T> >
class stack {
 public:
  typedef _Container container_type;
  typedef typename container_type::value_type value_type;
  typedef typename container_type::size_type size_type;

 protected:
  container_type c;

 public:
  // constructor
  explicit stack(const container_type& __c = container_type()) : c(__c) {}

  // member function
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  value_type& top() { return c.back(); }
  const value_type& top() const { return c.back(); }
  void push(const value_type& val) { return c.push_back(val); }
  void pop() { c.pop_back(); }

  // relational operator
  // Use friend to compare protected member variable
  template <typename T, typename C>
  friend bool operator==(const stack<T, C>& lhs, const stack<T, C>& rhs);
  template <typename T, typename C>
  friend bool operator<(const stack<T, C>& lhs, const stack<T, C>& rhs);
};

template <typename T, typename C>
inline bool operator==(const stack<T, C>& lhs, const stack<T, C>& rhs) {
  return lhs.c == rhs.c;
}

template <typename T, typename C>
inline bool operator!=(const stack<T, C>& lhs, const stack<T, C>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename C>
inline bool operator<(const stack<T, C>& lhs, const stack<T, C>& rhs) {
  return lhs.c < rhs.c;
}

template <typename T, typename C>
inline bool operator<=(const stack<T, C>& lhs, const stack<T, C>& rhs) {
  return !(rhs < lhs);
}

template <typename T, typename C>
inline bool operator>(const stack<T, C>& lhs, const stack<T, C>& rhs) {
  return rhs < lhs;
}

template <typename T, typename C>
inline bool operator>=(const stack<T, C>& lhs, const stack<T, C>& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif  // STACK_HPP