/**
 * @file vector.hpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief vector container declaration
 * @version 0.1
 * @date 2022-03-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iterator>
#include <memory>
#include <vector>

#include "iterator.hpp"

#ifndef VECTOR_HPP
#define VECTOR_HPP

#define FT_NOEXCEPT throw()

namespace ft {

/**
 * @brief base of Vector to RAII.
 *
 * @tparam _T: Type of Vector
 * @tparam _Allocator: Allocator of Vector
 *
 * @details 벡터의 데이터가 실제로 저장되는 base. 벡터의 Exception-safety를
 * 보장하기 위해 RAII 구조로 작성. 외부에서 객체로 만들 수 없으며 vector
 * 클래스에선 이곳에 정의된 메소드들로 데이터에 접근한다.
 */
template <typename _T, typename _Allocator = std::allocator<_T>()>
struct __vector_base {
 public:
  typedef _Allocator allocator_type;

 protected:
  typedef _T value_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  pointer __begin_;
  pointer __end_;
  pointer __end_cap_;
  allocator_type __a_;

  allocator_type& __get_allocator() FT_NOEXCEPT { return __a_; }
  const allocator_type& __get_allocator() const FT_NOEXCEPT { return __a_; }

  pointer& __end_cap() FT_NOEXCEPT { return __end_cap_; }
  const pointer& __end_cap() const FT_NOEXCEPT { return __end_cap_; }

  __vector_base() FT_NOEXCEPT;
  __vector_base(const allocator_type& a) FT_NOEXCEPT;
  __vector_base(size_type __n_);
  __vector_base(size_type __n_, const allocator_type& alloc);
  ~__vector_base() FT_NOEXCEPT {
    if (__begin_) __a_.deallocate(__begin_, __capacity());
  }

  // FIXME: not destruct. destory
  void clear() FT_NOEXCEPT {
    if (__begin_) __destruct_storage();
  }

  size_type __capacity() const FT_NOEXCEPT {
    return static_cast<size_type>(__end_cap_ - __begin_);
  }

  // TODO: throw suitable error when __n_ > max_size()
  size_type __check_size(size_type __n_) {
    // if (__n_ > __a_.max_size())
    // 	throw_blah
    return __n_;
  }

  void __destruct_storage() FT_NOEXCEPT;
  pointer __construct_storage(size_type __n_) {
    return __n_ == 0 ? pointer() : __get_allocator().allocate(__n_);
  };

  void __copy_data(__vector_base const& __src_) FT_NOEXCEPT;
  void __copy_data(pointer const& __new_begin_, pointer const& __new_end_,
                   pointer const& __new_end_cap_) FT_NOEXCEPT;
  void __swap_data(__vector_base& __src_) FT_NOEXCEPT;

 private:
  __vector_base(const __vector_base& other) { (void)other; };
  __vector_base& operator=(const __vector_base& other) { (void)other; };
};

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base() FT_NOEXCEPT
    : __begin_(NULL),
      __end_(NULL),
      __end_cap_(NULL),
      __a_(std::allocator<_T>()) {}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(const allocator_type& a)
    FT_NOEXCEPT : __begin_(NULL),
                  __end_(NULL),
                  __end_cap_(NULL),
                  __a_(a) {}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(size_type __n_)
    : __a_(std::allocator<_T>()) {
  __begin_ = __construct_storage(__n_);
  __end_ = __begin_;
  __end_cap_ = __begin_ + __n_;
}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(size_type __n_,
                                             const allocator_type& a)
    : __a_(a) {
  __begin_ = __construct_storage(__n_);
  __end_ = __begin_;
  __end_cap_ = __begin_ + __n_;
}

template <typename _T, typename _Allocator>
void __vector_base<_T, _Allocator>::__copy_data(__vector_base const& __src_)
    FT_NOEXCEPT {
  __begin_ = __src_.__begin_;
  __end_ = __src_.__end_;
  __end_cap_ = __src_.__end_cap_;
};

template <typename _T, typename _Allocator>
void __vector_base<_T, _Allocator>::__copy_data(
    pointer const& __new_begin_, pointer const& __new_end_,
    pointer const& __new_end_cap_) FT_NOEXCEPT {
  __begin_ = __new_begin_;
  __end_ = __new_end_;
  __end_cap_ = __new_end_cap_;
};

template <typename _T, typename _Allocator>
void __vector_base<_T, _Allocator>::__swap_data(__vector_base& __src_)
    FT_NOEXCEPT {
  __vector_base<_T, _Allocator> tmp;
  tmp.__copy_data(__src_);
  __src_.copy_data(*this);
  __copy_data(tmp);
};

template <typename _T, typename _Allocator>
void __vector_base<_T, _Allocator>::__destruct_storage() FT_NOEXCEPT {
  __get_allocator().deallocate(__begin_, __capacity());
  __end_ = __begin_ = __end_cap_ = NULL;
}

/**
 * @brief Iterator for vector.
 *
 * @tparam _Iter: type of iterator
 */
template <typename _Iter>
class __vector_iterator {
 public:
  typedef _Iter iterator_type;
  typedef typename ft::random_access_iterator_tag iterator_category;
  typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
  typedef typename ft::iterator_traits<iterator_type>::difference_type
      difference_type;
  typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
  typedef typename ft::iterator_traits<iterator_type>::reference reference;

 private:
  iterator_type __it;

 public:
  __vector_iterator() FT_NOEXCEPT {}
  template <typename _U>
  __vector_iterator(
      const __vector_iterator<_U>& __u,
      typename enable_if<__is_random_access_iterator<_U>::value>::type* =
          0)  // can copy when the category is random_access
      FT_NOEXCEPT : __it(__u.base()) {}

  __vector_iterator(iterator_type __x) FT_NOEXCEPT : __it(__x) {}

  const iterator_type& base() const { return __it; }

  // operator
  reference operator*() const FT_NOEXCEPT { return *__it; }
  pointer operator->() const FT_NOEXCEPT { return __it; }
  __vector_iterator& operator++() FT_NOEXCEPT {
    ++__it;
    return *this;
  }
  __vector_iterator operator++(int) FT_NOEXCEPT {
    __vector_iterator __tmp(*this);
    ++(*this);
    return __tmp;
  }
  __vector_iterator& operator--() FT_NOEXCEPT {
    --__it;
    return *this;
  }
  __vector_iterator operator--(int) FT_NOEXCEPT {
    __vector_iterator __tmp(*this);
    --(*this);
    return __tmp;
  }
  __vector_iterator& operator+=(difference_type __n) {
    __it += __n;
    return *this;
  }
  __vector_iterator operator+(difference_type __n) {
    __vector_iterator __w(*this);
    __w += __n;
    return __w;
  }
  __vector_iterator& operator-=(difference_type __n) {
    __it -= __n;
    return *this;
  }
  __vector_iterator operator-(difference_type __n) {
    __vector_iterator __w(*this);
    __w -= __n;
    return __w;
  }
  reference operator[](difference_type __n) { return __it[__n]; }
};

template <typename _Iter1, typename _Iter2>
bool operator==(const __vector_iterator<_Iter1>& __lhs,
                const __vector_iterator<_Iter2>& __rhs) {
  return __lhs.base() == __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator!=(const __vector_iterator<_Iter1>& __lhs,
                const __vector_iterator<_Iter2>& __rhs) {
  return __lhs.base() != __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator<(const __vector_iterator<_Iter1>& __lhs,
               const __vector_iterator<_Iter2>& __rhs) {
  return __lhs.base() < __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator>(const __vector_iterator<_Iter1>& __lhs,
               const __vector_iterator<_Iter2>& __rhs) {
  return __lhs.base() > __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator>=(const __vector_iterator<_Iter1>& __lhs,
                const __vector_iterator<_Iter2>& __rhs) {
  return __lhs.base() >= __rhs.base();
}

template <typename _Iter1, typename _Iter2>
bool operator<=(const __vector_iterator<_Iter1>& __lhs,
                const __vector_iterator<_Iter2>& __rhs) {
  return __lhs.base() <= __rhs.base();
}

template <typename _Iter1, typename _Iter2>
typename __vector_iterator<_Iter1>::difference_type operator-(
    const __vector_iterator<_Iter1>& __lhs,
    const __vector_iterator<_Iter2>& __rhs) {
  return __lhs.base() - __rhs.base();
}

template <typename _Iter>
__vector_iterator<_Iter> operator+(
    typename __vector_iterator<_Iter>::difference_type __n,
    const __vector_iterator<_Iter>& __it) {
  return __vector_iterator<_Iter>(__it.base() + __n);
}

/**
 * @brief vector container class.
 *
 * @tparam _T: each element type in vector
 * @tparam _Allocator: Allocator of vector
 */
template <typename _T, typename _Allocator = std::allocator<_T> >
class vector : private __vector_base<_T, _Allocator> {
 private:
  typedef __vector_base<_T, _Allocator> __base;

 public:
  typedef _T value_type;
  typedef _Allocator allocator_type;
  typedef typename __base::reference reference;
  typedef typename __base::const_reference const_reference;
  typedef typename __base::size_type size_type;
  typedef typename __base::difference_type difference_type;
  typedef typename __base::pointer pointer;
  typedef typename __base::const_pointer const_pointer;

  typedef __vector_iterator<pointer> iterator;
  typedef __vector_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // constructor
  explicit vector(const allocator_type& _Alloc = allocator_type());

  explicit vector(size_type n);
  explicit vector(size_type n, const value_type& val);
  vector(size_type n, const value_type& val, const allocator_type& _Alloc);

  template <typename _InputIterator>
  vector(_InputIterator first,
         typename enable_if<__is_input_iterator<_InputIterator>::value &&
                                !__is_forward_iterator<_InputIterator>::value,
                            _InputIterator>::type last,
         const allocator_type& _Alloc = allocator_type());

  template <typename _ForwardIterator>
  vector(_ForwardIterator first,
         typename enable_if<__is_forward_iterator<_ForwardIterator>::value,
                            _ForwardIterator>::type last,
         const allocator_type& _Alloc = allocator_type());

  vector(const vector<_T, _Allocator>& other);

  // assign operator
  vector& operator=(const vector& rhs);

  // iterators
  iterator begin() FT_NOEXCEPT { return this->__begin_; }
  const_iterator begin() const { return this->__begin_; }
  iterator end() { return this->__end_; }
  const_iterator end() const { return this->__end_; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  const_iterator cbegin() const { return const_iterator(begin()); }
  const_iterator cend() const { return const_iterator(begin()); }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(begin());
  }

  // capacity
  size_type size() const {
    return std::distance(this->__begin_, this->__end_cap_);
  }
  size_type max_size() const { return this->__a_.max_size(); }
  void resize(size_type n, value_type val = value_type());
  size_type capacity() const { return this->__capacity(); }
  bool empty() const { return this->__begin_ == this->__end_; }
  void reserve(size_type n);

  // element access
  reference operator[](size_type n) { return this->__begin_ + n; }
  const_reference operator[](size_type n) const { return this->__begin_ + n; }
  reference at(size_type n);
  const_reference at(size_type n) const;

  // FIXME: what if vector is empty?
  reference front() { return *this->__begin_; }
  const_reference front() const { return *this->__begin_; }
  reference back() { return *(this->__end_ - 1); }
  const_reference back() const { return *(this->__end_ - 1); }

  // modifiers
  template <typename _InputIterator>
  void assign(_InputIterator first, _InputIterator last);
  void assign(size_type n, const value_type& val);
  void push_back(const value_type& val);
  void pop_back();
  iterator insert(iterator position, const value_type& val);
  void insert(iterator position, size_type n, const value_type& val);
  template <typename _InputIterator>
  void insert(iterator position, _InputIterator first, _InputIterator last);
  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);
  void swap(vector& x);
  void clear();

  // Allocator
  allocator_type get_allocator() const FT_NOEXCEPT { return this->__a_; }

  // TODO: Impl destructor
  ~vector() {}

 private:
  void __construct_one(const value_type& val);
  void __reconstruct(size_type __new_n_);
};

template <typename _T, typename _Allocator>
vector<_T, _Allocator>::vector(const allocator_type& _Alloc)
    : __vector_base<_T, _Allocator>(size_type(), _Alloc) {}

template <typename _T, typename _Allocator>
vector<_T, _Allocator>::vector(size_type n)
    : __vector_base<_T, _Allocator>(n, allocator_type()) {
  std::uninitialized_fill(this->__begin_, this->__begin_ + n, value_type());
  this->__end_ += n;
}

template <typename _T, typename _Allocator>
vector<_T, _Allocator>::vector(size_type n, const value_type& val)
    : __vector_base<_T, _Allocator>(n, allocator_type()) {
  std::uninitialized_fill(this->__begin_, this->__begin_ + n, val);
  this->__end_ += n;
}

template <typename _T, typename _Allocator>
vector<_T, _Allocator>::vector(size_type n, const value_type& val,
                               const allocator_type& _Alloc)
    : __vector_base<_T, _Allocator>(n, _Alloc) {
  std::uninitialized_fill(this->__begin_, this->__begin_ + n, val);
  this->__end_ += n;
}

template <typename _T, typename _Allocator>
template <typename _InputIterator>
vector<_T, _Allocator>::vector(
    _InputIterator first,
    typename enable_if<__is_input_iterator<_InputIterator>::value &&
                           !__is_forward_iterator<_InputIterator>::value,
                       _InputIterator>::type last,
    const allocator_type& _Alloc)
    : __vector_base<_T, _Allocator>(size_type(), _Alloc) {
  for (; first == last; ++first) {
    // push_back(*first);
  }
}

template <typename _T, typename _Allocator>
template <typename _ForwardIterator>
vector<_T, _Allocator>::vector(
    _ForwardIterator first,
    typename enable_if<__is_forward_iterator<_ForwardIterator>::value,
                       _ForwardIterator>::type last,
    const allocator_type& _Alloc)
    : __vector_base<_T, _Allocator>(
          static_cast<size_type>(std::distance(first, last)), _Alloc) {
  std::uninitialized_copy(first, last, this->__begin_);
  this->__end_ = this->__end_cap_;
}

template <typename _T, typename _Allocator>
vector<_T, _Allocator>::vector(const vector<_T, _Allocator>& other)
    : __vector_base<_T, _Allocator>(other.capacity()) {
  this->__end_ =
      std::uninitialized_copy(other.__begin_, other.__end_, this->__begin_);
}

template <typename _T, typename _Allocator>
void vector<_T, _Allocator>::__reconstruct(size_type __new_n_) {
  pointer __new_begin_, __new_end_, __new_cap_;
  __new_begin_ = this->__reconstruct_storage(__new_n_);
  __new_end_ =
      std::uninitialized_copy(this->__begin_, this->__end_, __new_begin_);
  __new_cap_ = __new_n_;
}

template <typename _T, typename _Allocator>
void vector<_T, _Allocator>::__construct_one(const value_type& val) {
  if (this->__end_ == this->__end_cap_) __reconstruct(this->__capacity() * 2);
  *this->end++ = val
}

template <typename _T, typename _Allocator>
void vector<_T, _Allocator>::push_back(const value_type& val) {
  if (this->__end_ != this->__end_cap_) {
    // __construct_one();
    return;
  }
  // __reconstruct_storage();
  // __construct_one();
}

// comparision operators
template <typename _T, typename _Allocator>
bool operator==(const vector<_T, _Allocator>& __lhs,
                const vector<_T, _Allocator>& __rhs);
template <typename _T, typename _Allocator>
bool operator!=(const vector<_T, _Allocator>& __lhs,
                const vector<_T, _Allocator>& __rhs);
template <typename _T, typename _Allocator>
bool operator<(const vector<_T, _Allocator>& __lhs,
               const vector<_T, _Allocator>& __rhs);
template <typename _T, typename _Allocator>
bool operator<=(const vector<_T, _Allocator>& __lhs,
                const vector<_T, _Allocator>& __rhs);
template <typename _T, typename _Allocator>
bool operator>(const vector<_T, _Allocator>& __lhs,
               const vector<_T, _Allocator>& __rhs);
template <typename _T, typename _Allocator>
bool operator>=(const vector<_T, _Allocator>& __lhs,
                const vector<_T, _Allocator>& __rhs);

// TODO: swap needed

}  // namespace ft

#endif  // VECTOR_HPP
