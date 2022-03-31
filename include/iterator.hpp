/**
 * @file iterator.hpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief iterator_traits and reverse_iterator
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ITERATOR
#define ITERATOR

#include <cstddef>

#include "type_traits.hpp"

namespace ft {

// tags for iterator_traits
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

/**
 * @brief base of iterator. common to %iterator classes.
 *
 * @tparam _Category
 * @tparam _T
 * @tparam _Distance
 * @tparam _pointer
 * @tparam _reference
 */
template <typename _Category, typename _T, typename _Distance = ptrdiff_t,
          typename _pointer = _T *, typename _reference = _T &>
struct iterator {
  typedef _T value_type;
  typedef _Distance difference_type;
  typedef _pointer pointer;
  typedef _reference reference;
  typedef _Category iterator_category;
};

// iterator_traits
template <typename _Iter>
struct iterator_traits {
  typedef typename _Iter::iterator_category iterator_category;
  typedef typename _Iter::value_type value_type;
  typedef typename _Iter::difference_type difference_type;
  typedef typename _Iter::pointer pointer;
  typedef typename _Iter::reference reference;
};

// iterator_traits specialization for pointer type
template <typename _T>
struct iterator_traits<_T *> {
  typedef random_access_iterator_tag iterator_category;
  typedef _T value_type;
  typedef ptrdiff_t difference_type;
  typedef _T *pointer;
  typedef _T &reference;
};

// iterator_traits specialization for const pointer type
template <typename _T>
struct iterator_traits<const _T *> {
  typedef random_access_iterator_tag iterator_category;
  typedef typename remove_cv<_T>::type value_type;
  typedef ptrdiff_t difference_type;
  typedef const _T *pointer;
  typedef const _T &reference;
};

/**
 * @brief iterator wrapper for container (not only STL)
 *
 * @tparam _Iter: iterator
 * @tparam _Container: container
 */
template <typename _Iter, typename _Container>
class __wrap_iter {
 public:
  // type define
  typedef _Iter iterator_type;
  typedef typename iterator_traits<iterator_type>::iterator_category
      iterator_catrgory;
  typedef typename iterator_traits<iterator_type>::value_type value_type;
  typedef
      typename iterator_traits<iterator_type>::difference_type difference_type;
  typedef typename iterator_traits<iterator_type>::pointer pointer;
  typedef typename iterator_traits<iterator_type>::reference reference;

 private:
  iterator_type __it;

 public:
  __wrap_iter() FT_NOEXCEPT {}
  __wrap_iter(const _Iter &__other) FT_NOEXCEPT : __it(__other) {}
  __wrap_iter(
      const __wrap_iter<
          _Iter, typename ft::enable_if<
                     (ft::is_same<_Iter, typename _Container::iterator>::value),
                     _Container>::type> &__other)
      : __it(__other.base()) {}

  const _Iter &base() const FT_NOEXCEPT { return __it; }

 private:
  __wrap_iter &operator=(const __wrap_iter){};

 public:
};

}  // namespace ft

#endif  // ITERATOR