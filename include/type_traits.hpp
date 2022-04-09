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
#define FT_NOEXCEPT throw()

namespace ft {

template <typename T, T v>
struct integral_constant {
  typedef integral_constant<T, v> type;
  typedef T value_type;
  static const T value = v;
  operator value_type() const FT_NOEXCEPT { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

template <typename T>
struct _remove_cv {
  typedef T type;
};

template <typename T>
struct _remove_cv<const T> {
  typedef T type;
};

template <typename T>
struct _remove_cv<volatile T> {
  typedef T type;
};

template <typename T>
struct _remove_cv<const volatile T> {
  typedef T type;
};

template <typename T>
struct remove_cv {
  typedef typename _remove_cv<T>::type type;
};

template <typename T>
struct _is_integral : public false_type {};
template <>
struct _is_integral<bool> : public true_type {};
template <>
struct _is_integral<char> : public true_type {};
template <>
struct _is_integral<unsigned char> : public true_type {};
template <>
struct _is_integral<signed char> : public true_type {};
template <>
struct _is_integral<wchar_t> : public true_type {};
template <>
struct _is_integral<short> : public true_type {};
template <>
struct _is_integral<unsigned short> : public true_type {};
template <>
struct _is_integral<int> : public true_type {};
template <>
struct _is_integral<unsigned int> : public true_type {};
template <>
struct _is_integral<long> : public true_type {};
template <>
struct _is_integral<unsigned long> : public true_type {};
template <>
struct _is_integral<long long> : public true_type {};
template <>
struct _is_integral<unsigned long long> : public true_type {};

template <typename T>
struct is_integral : public _is_integral<typename remove_cv<T>::type> {};

template <typename T, typename U>
struct is_same : public false_type {};

template <typename T>
struct is_same<T, T> : public true_type {};

template <typename>
struct void_t {
  typedef void type;
};

}  // namespace ft

#endif  // TYPE_TRAITS
