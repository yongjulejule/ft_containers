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
#include <vector>

#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft {
template <typename _T, typename _Allocator>
class vector {
 private:
 protected:
  typedef _T value_type;
  typedef _Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef pointer iterator;
  typedef const pointer const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

 public:
  // default constructor
  explicit vector(const allocator_type& _Allocator = allocator_type());

  // fill constructor
  explicit vector(size_type n, const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type());

  // range constructor
  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type());

  // copy constructor
  vector(const vector& x);
};

}  // namespace ft

#endif  // VECTOR_HPP