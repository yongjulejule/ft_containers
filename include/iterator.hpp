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
#include <iterator>

#include "type_traits.hpp"

namespace ft {

// tags for iterator_traits
#if defined(_LIBCPP_ITERATOR) || defined(_STL_ITERATOR_H)

typedef std::input_iterator_tag input_iterator_tag;
typedef std::output_iterator_tag output_iterator_tag;
typedef std::forward_iterator_tag forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

#else  // !defined(_LIBCPP_ITERATOR) && !defined(_STL_ITERATOR_H)

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

#endif  // defined(_LIBCPP_ITERATOR) || defined(_STL_ITERATOR_H)

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

template <typename _T>
struct __has_iterator_typedefs {
 private:
  struct __two {
    char __x;
    char __y;
  };
  template <typename _U>
  static __two __test(...){};
  template <typename _U>
  static char __test(
      typename ft::void_t<typename _U::iterator_category>::type * = 0,
      typename ft::void_t<typename _U::difference_type>::type * = 0,
      typename ft::void_t<typename _U::value_type>::type * = 0,
      typename ft::void_t<typename _U::reference>::type * = 0,
      typename ft::void_t<typename _U::pointer>::type * = 0){};

 public:
  static const bool value = sizeof(__test<_T>(0, 0, 0, 0, 0)) == 1;
};

template <typename _Iter, bool>
struct __iterator_traits_typedefs {};

template <typename _Iter>
struct __iterator_traits_typedefs<_Iter, true> {
  typedef typename _Iter::iterator_category iterator_category;
  typedef typename _Iter::value_type value_type;
  typedef typename _Iter::difference_type difference_type;
  typedef typename _Iter::pointer pointer;
  typedef typename _Iter::reference reference;
};

template <typename _Iter, bool>
struct __iterator_traits {};

template <typename _Iter>
struct __iterator_traits<_Iter, true>
    : __iterator_traits_typedefs<
          _Iter, is_same<typename _Iter::iterator_category,
                         input_iterator_tag>::value ||
                     is_same<typename _Iter::iterator_category,
                             output_iterator_tag>::value ||
                     is_same<typename _Iter::iterator_category,
                             forward_iterator_tag>::value ||
                     is_same<typename _Iter::iterator_category,
                             bidirectional_iterator_tag>::value ||
                     is_same<typename _Iter::iterator_category,
                             random_access_iterator_tag>::value> {};

template <typename _Iter>
struct iterator_traits
    : __iterator_traits<_Iter, __has_iterator_typedefs<_Iter>::value> {};

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

template <typename _Iter,
          bool = __has_iterator_typedefs<iterator_traits<_Iter> >::value>
struct __is_iterator : public false_type {
  typedef void category;
};

template <typename _Iter>
struct __is_iterator<_Iter, true> : public true_type {
  typedef typename _Iter::iterator_category category;
};

template <typename _T>
struct __is_iterator<_T *, true> : public true_type {
  typedef typename iterator_traits<_T *>::iterator_category category;
};

template <typename _Iter>
struct __is_input_iterator
    : public integral_constant<bool,
                               (is_same<typename __is_iterator<_Iter>::category,
                                        input_iterator_tag>::value ||
                                is_same<typename __is_iterator<_Iter>::category,
                                        forward_iterator_tag>::value ||
                                is_same<typename __is_iterator<_Iter>::category,
                                        bidirectional_iterator_tag>::value ||
                                is_same<typename __is_iterator<_Iter>::category,
                                        random_access_iterator_tag>::value)> {};

template <typename _Iter>
struct __is_output_iterator
    : public integral_constant<bool,
                               is_same<typename __is_iterator<_Iter>::category,
                                       output_iterator_tag>::value> {};

template <typename _Iter>
struct __is_forward_iterator
    : public integral_constant<
          bool, is_same<typename __is_iterator<_Iter>::category,
                        forward_iterator_tag>::value ||
                    is_same<typename __is_iterator<_Iter>::category,
                            bidirectional_iterator_tag>::value ||
                    is_same<typename __is_iterator<_Iter>::category,
                            random_access_iterator_tag>::value> {};

template <typename _Iter>
struct __is_bidirectional_iterator
    : public integral_constant<
          bool, is_same<typename __is_iterator<_Iter>::category,
                        bidirectional_iterator_tag>::value ||
                    is_same<typename __is_iterator<_Iter>::category,
                            random_access_iterator_tag>::value> {};

template <typename _Iter>
struct __is_random_access_iterator
    : public integral_constant<bool,
                               is_same<typename __is_iterator<_Iter>::category,
                                       random_access_iterator_tag>::value> {};

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
  typedef typename iterator_traits<_Iter>::value_type value_type;
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

template <typename _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type __distance(
    _InputIterator __first, _InputIterator __last, ft::input_iterator_tag) {
  typename iterator_traits<_InputIterator>::difference_type d(0);
  for (; __first != __last; ++__first) ++d;
  return d;
}

template <typename _RandIterator>
inline typename iterator_traits<_RandIterator>::difference_type __distance(
    _RandIterator __first, _RandIterator __last,
    ft::random_access_iterator_tag) {
  return __last - __first;
}

template <typename _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type distance(
    _InputIterator first, _InputIterator last) {
  return ft::__distance(
      first, last,
      typename iterator_traits<_InputIterator>::iterator_category());
}

}  // namespace ft

#endif  // ITERATOR
