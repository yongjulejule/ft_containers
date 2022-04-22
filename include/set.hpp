/**
 * @file set.hpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief stl set
 * @version 0.1
 * @date 2022-04-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SET_HPP
#define SET_HPP

#include "__tree.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"

namespace ft {
template <typename _T, typename _Compare = std::less<_T>,
          typename _Alloc = std::allocator<_T> >
class set {
  // SECTION: type define
 public:
  typedef _T key_type;
  typedef _T value_type;
  typedef _Compare key_compare;
  typedef _Compare value_compare;
  typedef _Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

 private:
  typedef __tree<_T, _T, ft::identity<_T>, key_compare, allocator_type> __base;

 public:
  typedef typename __base::const_iterator iterator;
  typedef typename __base::const_iterator const_iterator;
  typedef typename __base::const_reverse_iterator reverse_iterator;
  typedef typename __base::const_reverse_iterator const_reverse_iterator;
  typedef typename __base::difference_type difference_type;
  typedef typename __base::size_type size_type;

 private:
  // SECTION: base of set
  __base __tree_;

  // SECTION: public member function
 public:
  // constructor
  explicit set(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : __tree_(comp, alloc) {}

  template <typename _InputIterator>
  set(_InputIterator first, _InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : __tree_(comp, alloc) {
    __tree_.insert_range(first, last);
  }

  set(const set& other) : __tree_(other.__tree_) {}

  set& operator=(const set& other) {
    if (this != &other) {
      __tree_ = other.__tree_;
    }
    return *this;
  }

  ~set() {}

  // iterators
  iterator begin() FT_NOEXCEPT { return iterator(__tree_.begin()); }
  const_iterator begin() const FT_NOEXCEPT {
    return const_iterator(__tree_.begin());
  }
  iterator end() FT_NOEXCEPT { return iterator(__tree_.end()); }
  const_iterator end() const FT_NOEXCEPT {
    return const_iterator(__tree_.end());
  }
  reverse_iterator rbegin() FT_NOEXCEPT { return __tree_.rbegin(); }
  const_reverse_iterator rbegin() const FT_NOEXCEPT { return __tree_.rbegin(); }
  reverse_iterator rend() FT_NOEXCEPT { return __tree_.rend(); }
  const_reverse_iterator rend() const FT_NOEXCEPT { return __tree_.rend(); }

  // capacity
  bool empty() const FT_NOEXCEPT { return __tree_.empty(); }
  size_type size() const FT_NOEXCEPT { return __tree_.size(); }
  size_type max_size() const FT_NOEXCEPT { return __tree_.max_size(); }

  // modifiers
  pair<iterator, bool> insert(const value_type& val) {
    return __tree_.insert_unique(val);
  }
  iterator insert(iterator position, const value_type& val) {
    return __tree_.insert_unique_with_hint(position, val);
  }
  template <typename _InputIterator>
  void insert(_InputIterator first, _InputIterator last) {
    __tree_.insert_range(first, last);
  }

  void erase(iterator position) { __tree_.erase(position); }
  size_type erase(const key_type& k) { return __tree_.erase(k); }
  void erase(iterator first, iterator last) { __tree_.erase(first, last); }

  void swap(set& other) { __tree_.swap(other.__tree_); }

  void clear() { __tree_.clear(); }

  // observers
  key_compare key_comp() const { return __tree_.key_comp(); }
  value_compare value_comp() const { return value_compare(__tree_.key_comp()); }

  // operations
  iterator find(const value_type& k) const {
    return __tree_.find(k).__remove_const();
  }
  size_type count(const value_type& k) const { return __tree_.count(k); }
  iterator lower_bound(const value_type& k) { return __tree_.lower_bound(k); }
  const_iterator lower_bound(const value_type& k) const {
    return __tree_.lower_bound(k);
  }
  iterator upper_bound(const value_type& k) { return __tree_.upper_bound(k); }
  const_iterator upper_bound(const value_type& k) const {
    return __tree_.upper_bound(k);
  }
  pair<iterator, iterator> equal_range(const value_type& k) {
    return __tree_.equal_range(k);
  }
  pair<const_iterator, const_iterator> equal_range(const value_type& k) const {
    return __tree_.equal_range(k);
  }
  allocator_type get_allocator() const {
    return allocator_type(__tree_.get_allocator());
  }
  template <typename _T1, typename _C1, typename _A1>
  friend bool operator==(const set& lhs, const set& rhs);
  template <typename _T1, typename _C1, typename _A1>
  friend bool operator<(const set& lhs, const set& rhs);
};

template <typename _T, typename _Compare, typename _Alloc>
bool operator==(const ft::set<_T, _Compare, _Alloc>& lhs,
                const ft::set<_T, _Compare, _Alloc>& rhs) {
  return (lhs.size() == rhs.size() &&
          ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename _T, typename _Compare, typename _Alloc>
bool operator!=(const ft::set<_T, _Compare, _Alloc>& lhs,
                const ft::set<_T, _Compare, _Alloc>& rhs) {
  return !(lhs == rhs);
}

template <typename _T, typename _Compare, typename _Alloc>
bool operator<(const ft::set<_T, _Compare, _Alloc>& lhs,
               const ft::set<_T, _Compare, _Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <typename _T, typename _Compare, typename _Alloc>
bool operator>(const ft::set<_T, _Compare, _Alloc>& lhs,
               const ft::set<_T, _Compare, _Alloc>& rhs) {
  return rhs < lhs;
}

template <typename _T, typename _Compare, typename _Alloc>
bool operator<=(const ft::set<_T, _Compare, _Alloc>& lhs,
                const ft::set<_T, _Compare, _Alloc>& rhs) {
  return !(rhs < lhs);
}

template <typename _T, typename _Compare, typename _Alloc>
bool operator>=(const ft::set<_T, _Compare, _Alloc>& lhs,
                const ft::set<_T, _Compare, _Alloc>& rhs) {
  return !(lhs < rhs);
}

template <typename _T, typename _Compare, typename _Alloc>
void swap(ft::set<_T, _Compare, _Alloc>& lhs,
          ft::set<_T, _Compare, _Alloc>& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft

#endif  // SET_HPP