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

namespace ft {
template <typename _T, typename _Allocator>
class __vector_base {
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
  // TODO: convert to ft::iterator_traits
  typedef pointer iterator;
  typedef const pointer const_iterator;
  // TODO: convert to ft::reverse_iterator
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  pointer __begin_;
  pointer __end_;
  pointer __end_cap_;
  allocator_type __a_;

  allocator_type& __alloc() { return __a_; }
  const allocator_type& __alloc() const { return __a_; }

  pointer& __end_cap() { return __end_cap_; }
  const pointer& __end_cap() const { return __end_cap_; }

  __vector_base();
  __vector_base(const allocator_type& __a);
  ~__vector_base();

  void clear() { __destruct_at_end(__begin_); }
  size_type capacity() const {
    return static_case<size_type>(__end_cap_ - __begin_);
  }
};

template <typename _T, typename _Allocator>
class vector : private __vector_base<_T, _Allocator> {
 private:
  typedef __vector_base<_T, _Allocator> __base;

 public:
  // constructor
  explicit vector(const allocator_type& _Allocator = allocator_type());
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
  iterator insert(interator position, const value_type& val);
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