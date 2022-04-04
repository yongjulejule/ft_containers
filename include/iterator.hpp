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

template <typename _Iter>
class reverse_iterator
    : public iterator<typename iterator_traits<_Iter>::iterator_category,
                      typename iterator_traits<_Iter>::value_type,
                      typename iterator_traits<_Iter>::difference_type,
                      typename iterator_traits<_Iter>::pointer,
                      typename iterator_traits<_Iter>::reference> {
 protected:
  _Iter current;

 public:
  // typedef
  typedef _Iter iterator_type;
  typedef typename iterator_traits<_Iter>::difference_type difference_type;
  typedef typename iterator_traits<_Iter>::reference reference;
  typedef typename iterator_traits<_Iter>::pointer pointer;

  // constructor
  reverse_iterator() : current() {}
  reverse_iterator(_Iter __it) : current(__it) {}
  template <typename _U>
  reverse_iterator(const reverse_iterator<_U> &__u) : current(__u.base()) {}
  template <typename _U>
  reverse_iterator &operator=(const reverse_iterator<_U> &__u) {
    current = __u.base();
    return *this;
  }

  _Iter base() const { return current; }

  // operator
  reference operator*() const {
    _Iter __tmp = current;
    return *--__tmp;
  }
  pointer operator->() const { return &(operator*()); }
  reverse_iterator &operator++() {
    --current;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator __tmp(*this);
    --current;
    return __tmp;
  }
  reverse_iterator &operator--() {
    ++current;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator __tmp(*this);
    ++current;
    return __tmp;
  }
  reverse_iterator operator+(difference_type __n) const {
    return reverse_iterator(current - __n);
  }
  reverse_iterator operator-(difference_type __n) const {
    return reverse_iterator(current + __n);
  }
  reverse_iterator &operator+=(difference_type __n) {
    current -= __n;
    return *this;
  }
  reverse_iterator &operator-=(difference_type __n) {
    current += __n;
    return *this;
  }
  reference operator[](difference_type __n) const { return *(*this + __n); }
};

// non-member function overloads

template <typename _Iter1, typename _Iter2>
bool operator==(const reverse_iterator<_Iter1> &__lhs,
                const reverse_iterator<_Iter2> &__rhs) {
  return __lhs.base() == __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator!=(const reverse_iterator<_Iter1> &__lhs,
                const reverse_iterator<_Iter2> &__rhs) {
  return __lhs.base() != __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator<(const reverse_iterator<_Iter1> &__lhs,
               const reverse_iterator<_Iter2> &__rhs) {
  return __lhs.base() > __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator>(const reverse_iterator<_Iter1> &__lhs,
               const reverse_iterator<_Iter2> &__rhs) {
  return __lhs.base() < __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator>=(const reverse_iterator<_Iter1> &__lhs,
                const reverse_iterator<_Iter2> &__rhs) {
  return __lhs.base() <= __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator<=(const reverse_iterator<_Iter1> &__lhs,
                const reverse_iterator<_Iter2> &__rhs) {
  return __lhs.base() >= __rhs.base();
}

template <typename _Iter1, typename _Iter2>
typename reverse_iterator<_Iter1>::difference_type operator-(
    const reverse_iterator<_Iter1> &__lhs,
    const reverse_iterator<_Iter2> &__rhs) {
  return __rhs.base() - __lhs.base();
}

template <typename _Iter>
reverse_iterator<_Iter> operator+(
    typename reverse_iterator<_Iter>::difference_type __n,
    const reverse_iterator<_Iter> &__it) {
  return reverse_iterator<_Iter>(__it.base() - __n);
}

template <class, class Enable = void>
struct is_iterator : false_type {};

template <typename T>
struct is_iterator<T, typename enable_if<T::iterator_category>::type>
    : public true_type {};

// template <typename _T>
// struct __is_input_iterator<
//     _T,
//     typename enable_if<(is_same<typename
//     iterator_traits<_T>::iterator_category,
//                                 input_iterator_tag>::value ||
//                         is_same<typename
//                         iterator_traits<_T>::iterator_category,
//                                 forward_iterator_tag>::value ||
//                         is_same<typename
//                         iterator_traits<_T>::iterator_category,
//                                 bidirectional_iterator_tag>::value ||
//                         is_same<typename
//                         iterator_traits<_T>::iterator_category,
//                                 random_access_iterator_tag>::value)>::type>
//     : public true_type {};
template <typename _T>
struct __is_input_iterator
    : public integral_constant<
          bool, (is_same<typename iterator_traits<_T>::iterator_category,
                         input_iterator_tag>::value ||
                 is_same<typename iterator_traits<_T>::iterator_category,
                         forward_iterator_tag>::value ||
                 is_same<typename iterator_traits<_T>::iterator_category,
                         bidirectional_iterator_tag>::value ||
                 is_same<typename iterator_traits<_T>::iterator_category,
                         random_access_iterator_tag>::value)> {};

template <typename _T>
struct __is_output_iterator
    : public integral_constant<
          bool, is_same<typename iterator_traits<_T>::iterator_category,
                        output_iterator_tag>::value> {};

template <typename _T>
struct __is_forward_iterator
    : public integral_constant<
          bool, is_same<typename iterator_traits<_T>::iterator_category,
                        forward_iterator_tag>::value ||
                    is_same<typename iterator_traits<_T>::iterator_category,
                            bidirectional_iterator_tag>::value ||
                    is_same<typename iterator_traits<_T>::iterator_category,
                            random_access_iterator_tag>::value> {};

template <typename _T>
struct __is_bidirectional_iterator
    : public integral_constant<
          bool, is_same<typename iterator_traits<_T>::iterator_category,
                        bidirectional_iterator_tag>::value ||
                    is_same<typename iterator_traits<_T>::iterator_category,
                            random_access_iterator_tag>::value> {};

template <typename _T>
struct __is_random_access_iterator
    : public integral_constant<
          bool, is_same<typename iterator_traits<_T>::iterator_category,
                        random_access_iterator_tag>::value> {};

}  // namespace ft

#endif  // ITERATOR