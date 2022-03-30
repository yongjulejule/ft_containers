/**
 * @file type_traits.hpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief enable_if and is_integral
 * @version 0.1
 * @date 2022-03-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TYPE_TRAITS
#define TYPE_TRAITS

namespace ft {
template <bool b, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

template <typename T>
struct remove_cv {
  typedef T type
};

template <typename T>
struct remove_cv<const T> {
  typedef T type
};

template <typename T>
struct remove_cv<volatile T> {
  typedef T type
};

template <typename T>
struct remove_cv<const volatile T> {
  typedef T type
};

template <typename T>
typedef typename remove_cv<T>::type remove_cv_t<T>;
}  // namespace ft

#endif  // ENABLE_IF