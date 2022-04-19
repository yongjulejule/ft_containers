/**
 * @file utility.hpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief utility (pair, make_pair)
 * @version 0.1
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <functional>

namespace ft {

template <typename _T1, typename _T2>
struct pair {
  // typedef
  typedef _T1 first_type;
  typedef _T2 second_type;

  // member variable
  _T1 first;
  _T2 second;

  // constructor
  pair() : first(), second() {}
  template <typename _U1, typename _U2>
  pair(const pair<_U1, _U2> &other)
      : first(other.first), second(other.second) {}
  pair(const _T1 &t1, const _T2 &t2) : first(t1), second(t2) {}

  // assign operator
  pair &operator=(pair const &other) {
    first = other.first;
    second = other.second;
    return *this;
  }
};

template <class _T1, class _T2>
bool operator==(const pair<_T1, _T2> &lhs, const pair<_T1, _T2> &rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class _T1, class _T2>
bool operator!=(const pair<_T1, _T2> &lhs, const pair<_T1, _T2> &rhs) {
  return !(lhs == rhs);
}

template <class _T1, class _T2>
bool operator<(const pair<_T1, _T2> &lhs, const pair<_T1, _T2> &rhs) {
  return lhs.first < rhs.first ||
         (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class _T1, class _T2>
bool operator>(const pair<_T1, _T2> &lhs, const pair<_T1, _T2> &rhs) {
  return rhs < lhs;
}

template <class _T1, class _T2>
bool operator>=(const pair<_T1, _T2> &lhs, const pair<_T1, _T2> &rhs) {
  return !(lhs < rhs);
}

template <class _T1, class _T2>
bool operator<=(const pair<_T1, _T2> &lhs, const pair<_T1, _T2> &rhs) {
  return !(rhs < lhs);
}

template <typename _T1, typename _T2>
inline pair<_T1, _T2> make_pair(_T1 x, _T2 y) {
  return pair<_T1, _T2>(x, y);
}

template <typename T>
void swap(T &x, T &y) {
  T tmp(x);
  x = y;
  y = tmp;
}

template <typename pair>
struct select_first {
  typename pair::first_type &operator()(pair &__x) const { return __x.first; }
  const typename pair::first_type &operator()(const pair &__x) const {
    return __x.first;
  }
};

template <typename T>
struct identity {
  T &operator()(T &__x) const { return __x; }
  const T &operator()(const T &__x) const { return __x; }
};

}  // namespace ft

#endif  // UTILITY_HPP