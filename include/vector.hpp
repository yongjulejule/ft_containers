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
template <typename _T, typename _Allocator>
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

  allocator_type& __alloc() FT_NOEXCEPT { return __a_; }
  const allocator_type& __alloc() const FT_NOEXCEPT { return __a_; }

  pointer& __end_cap() FT_NOEXCEPT { return __end_cap_; }
  const pointer& __end_cap() const FT_NOEXCEPT { return __end_cap_; }

  __vector_base() FT_NOEXCEPT;
  __vector_base(const allocator_type& a) FT_NOEXCEPT;
  __vector_base(size_type __n_);
  __vector_base(size_type __n_, const allocator_type& alloc = allocator_type());
  ~__vector_base() FT_NOEXCEPT { __a_.deallocate(__begin_, capacity()); }

  void clear() FT_NOEXCEPT {
    if (__begin_) __destruct_storage();
  }
  size_type capacity() const FT_NOEXCEPT {
    return static_cast<size_type>(__end_cap_ - __begin_);
  }

  void __destruct_storage() FT_NOEXCEPT;
  pointer __construct_storage(size_type __n_) {
    return __n_ == 0 ? pointer() : __alloc().allocate(__n_);
  };
  void __copy_data(__vector_base const& __src_) FT_NOEXCEPT;
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
void __vector_base<_T, _Allocator>::__swap_data(__vector_base& __src_)
    FT_NOEXCEPT {
  __vector_base<_T, _Allocator> tmp;
  tmp.__copy_data(__src_);
  __src_.copy_data(*this);
  __copy_data(tmp);
};

template <typename _T, typename _Allocator>
void __vector_base<_T, _Allocator>::__destruct_storage() FT_NOEXCEPT {
  __alloc().deallocate(__begin_, capacity());
  __end_ = __begin_ = __end_cap_ = NULL;
}

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

  // TODO: convert to ft::iterator_traits
  typedef pointer iterator;
  typedef const pointer const_iterator;
  // TODO: convert to ft::reverse_iterator
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // constructor
  explicit vector(const allocator_type& _Alloc = allocator_type());
  explicit vector(size_type n, const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type());
  template <typename InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type());
  vector(const vector& x);

  // assign operator
  vector& operator=(const vector& rhs);

  // iterators
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;
  reverse_iterator rend();
  const_reverse_iterator rend() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;

  // capacity
  size_type size() const;
  size_type max_size() const;
  void resize(size_type n, value_type val = value_type());
  size_type capacity() const;
  bool empty() const;
  void reserve(size_type n);

  // element access
  reference operator[](size_type n);
  const_reference operator[](size_type n) const;
  reference at(size_type n);
  const_reference at(size_type n) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  // modifiers
  template <typename InputIterator>
  void assign(InputIterator first, InputIterator last);
  void assign(size_type n, const value_type& val);
  void push_back(const value_type& val);
  void pop_back();
  iterator insert(iterator position, const value_type& val);
  void insert(iterator position, size_type n, const value_type& val);
  template <typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last);
  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);
  void swap(vector& x);
  void clear();

  // Allocator
  allocator_type get_allocator() const;

  // destructor
  ~vector();
};

// comparision operators
template <typename _T, typename _Allocator>
bool operator==(const vector<_T, _Allocator>& lhs,
                const vector<_T, _Allocator>& rhs);
template <typename _T, typename _Allocator>
bool operator!=(const vector<_T, _Allocator>& lhs,
                const vector<_T, _Allocator>& rhs);
template <typename _T, typename _Allocator>
bool operator<(const vector<_T, _Allocator>& lhs,
               const vector<_T, _Allocator>& rhs);
template <typename _T, typename _Allocator>
bool operator<=(const vector<_T, _Allocator>& lhs,
                const vector<_T, _Allocator>& rhs);
template <typename _T, typename _Allocator>
bool operator>(const vector<_T, _Allocator>& lhs,
               const vector<_T, _Allocator>& rhs);
template <typename _T, typename _Allocator>
bool operator>=(const vector<_T, _Allocator>& lhs,
                const vector<_T, _Allocator>& rhs);

// TODO: swap needed

}  // namespace ft

#endif  // VECTOR_HPP