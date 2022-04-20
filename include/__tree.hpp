/**
 * @file tree.hpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief Red Black Tree which is base of set and map
 * @version 0.1
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __TREE_HPP
#define __TREE_HPP

#define R "\033[31m";
#define B "\033[32m";
#define RESET "\033[0m"

#include <iostream>
#include <memory>

#include "iterator.hpp"
#include "utility.hpp"

#define FT_NOEXCEPT throw()

namespace ft {
/*************************************************************************************
 * @brief Tree Nodes member function
 *************************************************************************************/

enum __tree_node_color { RED = false, BLACK = true };

struct __tree_node_base;

__tree_node_base *__tree_increment(__tree_node_base *__x) FT_NOEXCEPT;
const __tree_node_base *__tree_increment(const __tree_node_base *__x)
    FT_NOEXCEPT;

__tree_node_base *__tree_decrement(__tree_node_base *__x) FT_NOEXCEPT;
const __tree_node_base *__tree_decrement(const __tree_node_base *__x)
    FT_NOEXCEPT;

void __tree_rotate_left(__tree_node_base *const __x, __tree_node_base *&__root);
void __tree_rotate_right(__tree_node_base *const __x,
                         __tree_node_base *&__root);

void __tree_insert_and_fixup(const bool __insert_left, __tree_node_base *__x,
                             __tree_node_base *__p,
                             __tree_node_base &__header) FT_NOEXCEPT;

__tree_node_base *__tree_erase_and_fixup(
    __tree_node_base *const __z, __tree_node_base &__header) FT_NOEXCEPT;

/*************************************************************************************
 * @brief Tree Nodes
 *************************************************************************************/

// base of node structure for rb-tree
struct __tree_node_base {
  typedef __tree_node_base *_Base_ptr;
  typedef const __tree_node_base *_Const_base_ptr;

  __tree_node_color __color_;
  _Base_ptr __parent_;
  _Base_ptr __left_;
  _Base_ptr __right_;

  static _Base_ptr __S_minimum(_Base_ptr __x) FT_NOEXCEPT {
    while (__x->__left_ != NULL) __x = __x->__left_;
    return __x;
  }

  static _Const_base_ptr __S_minimum(_Const_base_ptr __x) FT_NOEXCEPT {
    while (__x->__left_ != NULL) __x = __x->__left_;
    return __x;
  }

  static _Base_ptr __S_maximum(_Base_ptr __x) FT_NOEXCEPT {
    while (__x->__right_ != NULL) __x = __x->__right_;
    return __x;
  }

  static _Const_base_ptr __S_maximum(_Const_base_ptr __x) FT_NOEXCEPT {
    while (__x->__right_ != NULL) __x = __x->__right_;
    return __x;
  }
};

// tree header
// parent: root of tree
// left: left-most element
// right: right-most element
struct __tree_header {
  __tree_node_base __header_;
  std::size_t __node_count_;

  __tree_header() {
    __header_.__color_ = RED;
    __tree_reset();
  }

  void __tree_reset() {
    __header_.__parent_ = NULL;
    __header_.__left_ = &__header_;
    __header_.__right_ = &__header_;
    __node_count_ = 0;
  }

  void __tree_move_data(__tree_header &__from) {
    __header_.__color_ = __from.__header_.__color_;
    __header_.__parent_ = __from.__header_.__parent_;
    __header_.__left_ = __from.__header_.__left_;
    __header_.__right_ = __from.__header_.__right_;
    __header_.__parent_->__parent_ = &__header_;
    __node_count_ = __from.__node_count_;

    __from.__tree_reset();
  }
};

// FIXME: 굳이...?
template <typename _Key_compare>
struct __tree_key_compare {
  _Key_compare __key_comp;

  __tree_key_compare() : __key_comp() {}
  __tree_key_compare(const _Key_compare &other) : __key_comp(other) {}
};

// Node for rb-tree
template <typename _Val>
struct __tree_node : public __tree_node_base {
  typedef __tree_node<_Val> *_Link_type;

  _Val __value_field;

  _Val *__valptr() { return &__value_field; }
  const _Val *__valptr() const { return &__value_field; }
};

/*************************************************************************************
 * @brief Tree Nodes Iterator
 *************************************************************************************/

template <typename _T>
struct __tree_iterator : public iterator<bidirectional_iterator_tag, _T> {
  typedef _T value_type;
  typedef _T &reference;
  typedef _T *pointer;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef __tree_iterator<_T> iterator_type;
  typedef __tree_node_base::_Base_ptr _Base_ptr;
  typedef __tree_node<_T> *_Link_type;

  _Base_ptr __node_;

  __tree_iterator() : __node_() {}

  __tree_iterator(const __tree_iterator &other) : __node_(other.__node_) {}

  explicit __tree_iterator(_Base_ptr __x) : __node_(__x) {}

  reference operator*() const FT_NOEXCEPT {
    return *static_cast<_Link_type>(__node_)->__valptr();
  }

  pointer operator->() const FT_NOEXCEPT {
    return static_cast<_Link_type>(__node_)->__valptr();
  }

  iterator_type &operator++() FT_NOEXCEPT {
    __node_ = __tree_increment(__node_);
    return *this;
  }

  iterator_type operator++(int) FT_NOEXCEPT {
    iterator_type __tmp(*this);
    ++(*this);
    return __tmp;
  }

  iterator_type &operator--() FT_NOEXCEPT {
    __node_ = __tree_decrement(__node_);
    return *this;
  }

  iterator_type operator--(int) FT_NOEXCEPT {
    iterator_type __tmp(*this);
    --(*this);
    return __tmp;
  }

  friend bool operator==(const iterator_type &lhs,
                         const iterator_type &rhs) FT_NOEXCEPT {
    return lhs.__node_ == rhs.__node_;
  }
  friend bool operator!=(const iterator_type &lhs,
                         const iterator_type &rhs) FT_NOEXCEPT {
    return lhs.__node_ != rhs.__node_;
  }
};

template <typename _T>
struct __tree_const_iterator : public iterator<bidirectional_iterator_tag, _T> {
  typedef _T value_type;
  typedef const _T *pointer;
  typedef const _T &reference;
  typedef bidirectional_iterator_tag iterator_catergory;
  typedef ptrdiff_t difference_type;

  typedef __tree_iterator<_T> iterator;
  typedef __tree_const_iterator<_T> const_iterator_type;
  typedef __tree_node_base::_Const_base_ptr _Base_ptr;
  typedef const __tree_node<_T> *_Link_type;

  _Base_ptr __node_;

  __tree_const_iterator() FT_NOEXCEPT : __node_() {}
  explicit __tree_const_iterator(_Base_ptr __x) FT_NOEXCEPT : __node_(__x) {}
  __tree_const_iterator(const __tree_const_iterator &other)
      : __node_(other.__node_) {}
  __tree_const_iterator(iterator __it) : __node_(__it.__node_) {}

  iterator __remove_const() const FT_NOEXCEPT {
    return iterator(const_cast<typename iterator::_Base_ptr>(__node_));
  }

  reference operator*() const FT_NOEXCEPT {
    return *static_cast<_Link_type>(__node_)->__valptr();
  }

  pointer operator->() const FT_NOEXCEPT {
    return static_cast<_Link_type>(__node_)->__valptr();
  }

  const_iterator_type &operator++() FT_NOEXCEPT {
    __node_ = __tree_increment(__node_);
    return *this;
  }

  const_iterator_type operator++(int) FT_NOEXCEPT {
    const_iterator_type __tmp(*this);
    ++(*this);
    return __tmp;
  }

  const_iterator_type &operator--() FT_NOEXCEPT {
    __node_ = __tree_decrement(__node_);
    return *this;
  }

  const_iterator_type operator--(int) FT_NOEXCEPT {
    const_iterator_type __tmp(*this);
    --(*this);
    return __tmp;
  }

  friend bool operator==(const const_iterator_type &lhs,
                         const const_iterator_type &rhs) FT_NOEXCEPT {
    return lhs.__node_ == rhs.__node_;
  }
  friend bool operator!=(const const_iterator_type &lhs,
                         const const_iterator_type &rhs) FT_NOEXCEPT {
    return lhs.__node_ != rhs.__node_;
  }
};

template <typename _Key, typename _Val, typename _KeyOfVal, typename _Compare,
          typename _Alloc>
class __tree;

// template <typename _Key, typename _Val, typename _KeyOfVal, typename
// _Compare,
//           typename _Alloc>
// struct __alloc_node {
//   typedef __tree_node<_Val> *_Link_type;
//   __alloc_node(__tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc> &__t)
//       : __t_(__t) {}

//   template <typename _Arg>
//   _Link_type operator()(const _Arg &__arg) const {
//     return __t_.__create_node(__arg);
//   }

//  private:
//   __tree<_Key, _Val, _KeyOfVal, _Compare, _Alloc> &__t_;
// };
/*************************************************************************************
 * @brief Tree
 *************************************************************************************/

/**
 * @brief RB-tree class
 *
 * @tparam _Key: key of each node
 * @tparam _Val: value of each node
 * @tparam _KeyOfValue: get key of value functor
 * @tparam _Compare: Comparing functor
 * @tparam _Alloc: allocator (default: std::allocator<_Val>)
 */
template <typename _Key, typename _Val, typename _KeyOfValue,
          typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<_Val> >
class __tree {
 public:
  typedef typename _Alloc::template rebind<__tree_node<_Val> >::other
      _Node_allocator;

 protected:
  typedef __tree_node_base *_Base_ptr;
  typedef const __tree_node_base *_Const_base_ptr;
  typedef __tree_node<_Val> *_Link_type;
  typedef const __tree_node<_Val> *_Const_link_type;

 public:
  typedef _Key key_type;
  typedef _Val value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef _Alloc allocator_type;

  typedef __tree_iterator<value_type> iterator;
  typedef __tree_const_iterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  // typedef __alloc_node<_Key, _Val, _KeyOfValue, _Compare, _Alloc>
  // __alloc_node;

 private:
  // functor allocate node
  struct __alloc_node {
    __alloc_node(__tree &__t) : __t_(__t) {}

    template <typename _Arg>
    _Link_type operator()(const _Arg &__arg) const {
      return __t_.__create_node(__arg);
    }

   private:
    __tree &__t_;
  };

  // _Node_allocator: rebind of allocator
  // __tree_key_compare: key compare functor
  // __tree_header: head of tree
  template <typename _Key_compare>
  struct __tree_impl : public _Node_allocator,  // FIXME: 굳이 상속 왜받음??????
                       public __tree_key_compare<_Key_compare>,
                       public __tree_header {
    typedef __tree_key_compare<_Key_compare> _Base_key_compare;

    __tree_impl() : _Node_allocator() {}
    __tree_impl(const __tree_impl &other)
        : _Node_allocator(other),
          _Base_key_compare(other.__key_comp),
          __tree_header() {}
    __tree_impl(const _Key_compare &__comp, const _Node_allocator &__a)
        : _Node_allocator(__a), _Base_key_compare(__comp) {}
  };

  __tree_impl<_Compare> __impl_;

 public:
  // FIXME: Does this have to be public?
  _Node_allocator &__get_Node_allocator() { return this->__impl_; }
  const _Node_allocator &__get_Node_allocator() const { return this->__impl_; }

  // TODO: move to public member function
  allocator_type get_allocator() const {
    return allocator_type(__get_Node_allocator());
  }

 protected:
  // SECTION: generate/delete node
  _Link_type __allocate_node() { return __get_Node_allocator().allocate(1); }

  // FIXME: does not compile
  void __deallocate_node(_Link_type __p) {
    __get_Node_allocator().deallocate(__p, 1);
  }

  void __construct_node(_Link_type __node, const value_type &__x) {
    get_allocator().construct(__node->__valptr(), __x);
  }

 public:
  _Link_type __create_node(const value_type &__x) {
    _Link_type __tmp = __allocate_node();
    __construct_node(__tmp, __x);
    return __tmp;
  }

 protected:
  void __destroy_node(_Link_type __p) {
    get_allocator().destroy(__p->__valptr());
  }

  // Return: new node which clone of __x's value and color
  template <typename _NodeGenerator>
  _Link_type __clone_node(_Link_type __x, _NodeGenerator &__node_gen) {
    _Link_type __tmp = __node_gen(*__x->__valptr());
    __tmp->__color_ = __x->__color_;
    __tmp->__left_ = NULL;
    __tmp->__right_ = NULL;
    return __tmp;
  }

  // SECTION: get specific node
  _Base_ptr &__root() { return this->__impl_.__header_.__parent_; }
  _Const_base_ptr __root() const { return this->__impl_.__header_.__parent_; }

  _Base_ptr &__leftmost() { return this->__impl_.__header_.__left_; }
  _Const_base_ptr &__leftmost() const {
    return this->__impl_.__header_.__left_;
  }

  _Base_ptr &__rightmost() { return this->__impl_.__header_.__right_; }
  _Const_base_ptr &__rightmost() const {
    return this->__impl_.__header_.__right_;
  }

  _Link_type __begin() {
    return static_cast<_Link_type>(this->__impl_.__header_.__parent_);
  }
  _Const_link_type __begin() const {
    return static_cast<_Link_type>(this->__impl_.__header_.__parent_);
  }

  _Base_ptr __end() { return &this->__impl_.__header_; }
  _Const_base_ptr __end() const { return &this->__impl_.__header_; }

  // SECTION: static member function
  static const _Key &__S_key(_Const_link_type __x) {
    return _KeyOfValue()(*__x->__valptr());
  }

  static const _Key &__S_key(_Const_base_ptr __x) {
    return __S_key(static_cast<_Const_link_type>(__x));
  }

  static _Link_type __S_left(_Base_ptr __x) {
    return static_cast<_Link_type>(__x->__left_);
  }
  static _Const_link_type __S_left(_Const_base_ptr __x) {
    return static_cast<_Link_type>(__x->__left_);
  }

  static _Link_type __S_right(_Base_ptr __x) {
    return static_cast<_Link_type>(__x->__right_);
  }
  static _Const_link_type __S_right(_Const_base_ptr __x) {
    return static_cast<_Link_type>(__x->__right_);
  }

  static _Base_ptr __S_minimum(_Base_ptr __x) {
    return __tree_node_base::__S_minimum(__x);
  }
  static _Const_base_ptr __S_minimum(_Const_base_ptr __x) {
    return __tree_node_base::__S_minimum(__x);
  }

  static _Base_ptr __S_maximum(_Base_ptr __x) {
    return __tree_node_base::__S_maximum(__x);
  }
  static _Const_base_ptr __S_maximum(_Const_base_ptr __x) {
    return __tree_node_base::__S_maximum(__x);
  }

  // SECTION: helper for public member function

  // get position to insert
  ft::pair<_Base_ptr, _Base_ptr> __get_insert_unique_pos(const key_type &__k);
  // get hint and get position
  ft::pair<_Base_ptr, _Base_ptr> __get_insert_hint_unique_pos(
      const_iterator __pos, const key_type &__k);

  template <typename _NodeGenerator>
  _Link_type __copy_tree(_Link_type __x, _Base_ptr __p,
                         _NodeGenerator &__node_gen);
  template <typename _NodeGenerator>
  _Link_type __copy_tree(const __tree &__t, _NodeGenerator &__node_gen) {
    // copy whole tree
    _Link_type __root =
        __copy_tree(const_cast<_Link_type>(__t.__begin()), __end(), __node_gen);

    // update header
    __leftmost() = __S_minimum(__root);
    __rightmost() = __S_maximum(__root);
    __impl_.__node_count_ = __t.__impl_.__node_count_;
    return __root;
  }

  _Link_type __copy_tree(const __tree &__x) {
    __alloc_node __node_gen(*this);
    return __copy_tree(__x, __node_gen);
  }

  void __delete_node(_Link_type __p) {
    __destroy_node(__p);
    __deallocate_node(__p);
  }

  void __erase_without_balance(_Link_type __x);
  void __erase_helper(const_iterator __position);
  void __erase_helper(const_iterator __first, const_iterator __last);

  iterator __lower_bound_helper(_Link_type __x, _Base_ptr __y,
                                const key_type &__k);
  const_iterator __lower_bound_helper(_Const_link_type __x, _Const_base_ptr __y,
                                      const key_type &__k) const;

  iterator __upper_bound_helper(_Link_type __x, _Base_ptr __y,
                                const key_type &__k);
  const_iterator __upper_bound_helper(_Const_link_type __x, _Const_base_ptr __y,
                                      const key_type &__k) const;

 public:
  // SECTION: constructor/destructor
  __tree() {}
  __tree(const _Compare &_comp, const allocator_type &__a = allocator_type())
      : __impl_(_comp, _Node_allocator(__a)) {}
  __tree(const __tree &other) : __impl_(other.__impl_) {
    if (other.__root() != NULL) __root() = __copy_tree(other);
  }
  ~__tree() { __erase_without_balance(__begin()); }
  __tree &operator=(const __tree &other) {
    if (this != &other) {
      __alloc_node __node(*this);
      this->clear();
      // __impl_.__tree_reset();
      __impl_.__key_comp = other.__impl_.__key_comp;
      if (other.__root() != NULL) __root() = __copy_tree(other, __node);
    }
    return *this;
  }

  // SECTION: public member function

  // access to data

  _Compare key_comp() const { return __impl_.__key_comp; }

  iterator begin() { return iterator(__impl_.__header_.__left_); }
  const_iterator begin() const {
    return const_iterator(__impl_.__header_.__left_);
  }
  iterator end() { return iterator(&__impl_.__header_); }
  const_iterator end() const { return const_iterator(&__impl_.__header_); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  const_iterator cbegin() const { return const_iterator(begin()); }
  const_iterator cend() const { return const_iterator(end()); }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(begin());
  }

  // capacity
  bool empty() const { return __impl_.__node_count_ == 0; }
  size_type max_size() const {
    return std::min<size_type>(__get_Node_allocator().max_size(),
                               std::numeric_limits<difference_type>::max());
  }
  size_type size() const { return __impl_.__node_count_; }

  // modifiers

  void erase(iterator position) { __erase_helper(position); }
  void erase(const_iterator position) { __erase_helper(position); }

  size_type erase(const key_type &__v);

  void erase(iterator first, iterator last) { __erase_helper(first, last); }
  void erase(const_iterator first, const_iterator last) {
    __erase_helper(first, last);
  }

  void clear() {
    __erase_without_balance(__begin());
    __impl_.__tree_reset();
  }

  void swap(__tree &__t);

  template <typename _NodeGenerator>
  iterator __insert(_Base_ptr __x, _Base_ptr __p, const value_type &__v,
                    _NodeGenerator &__node_gen);
  ft::pair<iterator, bool> __insert_unique(const value_type &__v);

  template <typename _NodeGenerator>
  iterator __insert_unique_with_hint(const_iterator __position,
                                     const value_type &__v,
                                     _NodeGenerator &__node_gen);

  iterator __insert_unique_with_hint(const_iterator __pos,
                                     const value_type &__x) {
    __alloc_node __node(*this);
    return __insert_unique_with_hint(__pos, __x, __node);
  }

  template <typename _InputIterator>
  void __insert_range(_InputIterator __first, _InputIterator __last) {
    __alloc_node __node(*this);
    for (; __first != __last; ++__first) {
      __insert_unique_with_hint(cend(), *__first, __node);
    }
  }

  // operations
  iterator find(const key_type &__k) {
    iterator __found = __lower_bound_helper(__begin(), __end(), __k);
    if (__impl_.__key_comp(__k, __S_key(__found.__node_)) || __found == end())
      return end();
    return __found;
  }
  const_iterator find(const key_type &__k) const {
    const_iterator __found = __lower_bound_helper(__begin(), __end(), __k);
    if (__impl_.__key_comp(__k, __S_key(__found.__node_)) || __found == cend())
      return cend();
    return __found;
  }

  size_type count(const key_type &__k) const {
    const_iterator __found = find(__k);
    return __found == end() ? 0 : 1;
  }

  iterator lower_bound(const key_type &__k) {
    return __lower_bound_helper(__begin(), __end(), __k);
  }
  const_iterator lower_bound(const key_type &__k) const {
    return __lower_bound_helper(__begin(), __end(), __k);
  }

  iterator upper_bound(const key_type &__k) {
    return __upper_bound_helper(__begin(), __end(), __k);
  }
  const_iterator upper_bound(const key_type &__k) const {
    return __upper_bound_helper(__begin(), __end(), __k);
  }

  pair<iterator, iterator> equal_range(const key_type &__k);
  pair<const_iterator, const_iterator> equal_range(const key_type &__k) const;

  // NOTE: print tree
  void print_tree();
  void print_tree(const std::string &prefix, _Link_type x, bool isLeft);
};

/**
 * @brief get unique position to insert
 *
 * @param __k: key to get position
 * @return ft::pair<_Base_ptr, _Base_ptr> (ret_pair)
 *         ret_pair.first: if not NULL, insert left else insert right
 *         ret_pair.second: if not NULL, parent of node to insert
 *                          if NULL, regard it as false which the node will not
 *                          insert
 */
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
ft::pair<typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr,
         typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr>
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__get_insert_unique_pos(
    const key_type &__k) {
  typedef ft::pair<_Base_ptr, _Base_ptr> ret_pair;

  _Link_type __x = __begin();  // __root
  _Base_ptr __y = __end();     // __header
  bool __comp = true;

  // check left or right until meet leaf. __y gonna leaf
  while (__x != NULL) {
    __y = __x;
    __comp = __impl_.__key_comp(__k, __S_key(__x));
    __x = __comp ? __S_left(__x) : __S_right(__x);
  }

  iterator __j = iterator(__y);
  if (__comp) {
    if (__j == begin())           // leftmost
      return ret_pair(__x, __y);  // (NULL, leaf)
    else
      --__j;  // decrement node
  }

  if (__impl_.__key_comp(__S_key(__j.__node_),
                         __k))         // compare before leaf and __k
    return ret_pair(__x, __y);         // return (NULL, leaf)
  return ret_pair(__j.__node_, NULL);  // return (decremented leaf, NULL(false))
}

/**
 * @brief get unique position when hint is given
 *
 * @param __position: hint where __k should be inserted
 * @param __k: key to get position
 * @return ft::pair<_Base_ptr, _Base_ptr> (ret_pair)
 *         ret_pair.first: if not NULL, insert left else insert right
 *         ret_pair.second: if not NULL, parent of node to insert
 *                          if NULL, regard it as false which the node will not
 *                          insert
 */
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
ft::pair<typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr,
         typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr>
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__get_insert_hint_unique_pos(
    const_iterator __position, const key_type &__k) {
  iterator __pos = __position.__remove_const();
  typedef ft::pair<_Base_ptr, _Base_ptr> ret_pair;

  if (__pos.__node_ == __end()) {  // header
    if (size() > 0 && __impl_.__key_comp(__S_key(__rightmost()), __k))
      return ret_pair(NULL, __rightmost());
    else
      return __get_insert_unique_pos(__k);
  } else if (__impl_.__key_comp(__k,
                                __S_key(__pos.__node_))) {  // less than pos
    iterator __before = __pos;

    if (__pos.__node_ == __leftmost()) {
      return ret_pair(__leftmost(), __leftmost());
    } else if (__impl_.__key_comp(__S_key((--__before).__node_), __k)) {
      if (__S_right(__before.__node_) == NULL)
        return ret_pair(NULL, __before.__node_);
      else
        return ret_pair(__pos.__node_, __pos.__node_);
    } else {
      return __get_insert_unique_pos(__k);
    }
  } else if (__impl_.__key_comp(__S_key(__pos.__node_),
                                __k)) {  // more than pos
    iterator __after = __pos;

    if (__pos.__node_ == __rightmost()) {
      return ret_pair(NULL, __rightmost());
    } else if (__impl_.__key_comp(__k, __S_key((++__after).__node_))) {
      if (__S_right(__pos.__node_) == NULL)
        return ret_pair(NULL, __pos.__node_);
      else
        return ret_pair(__after.__node_, __after.__node_);
    } else {
      return __get_insert_unique_pos(__k);
    }
  } else  // equal to pos. the key cannot be same.
    return ret_pair(__pos.__node_, NULL);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
template <typename _NodeGenerator>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__insert(
    _Base_ptr __x, _Base_ptr __p, const value_type &__v,
    _NodeGenerator &__node_gen) {
  bool __insert_left = (__x != 0 || __p == __end() ||
                        __impl_.__key_comp(_KeyOfValue()(__v), __S_key(__p)));
  _Link_type __z = __node_gen(__v);
  __tree_insert_and_fixup(__insert_left, __z, __p, this->__impl_.__header_);
  ++__impl_.__node_count_;
  return iterator(__z);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
ft::pair<typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator,
         bool>
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__insert_unique(
    const value_type &__v) {
  typedef ft::pair<iterator, bool> ret_pair;
  ft::pair<_Base_ptr, _Base_ptr> __ret = __get_insert_unique_pos(
      _KeyOfValue()(__v));  // get position based key of __v

  if (__ret.second) {
    __alloc_node __node(*this);
    return ret_pair(__insert(__ret.first, __ret.second, __v, __node), true);
  }
  return ret_pair(iterator(__ret.first), false);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
template <typename _NodeGenerator>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__insert_unique_with_hint(
    const_iterator __position, const value_type &__v,
    _NodeGenerator &__node_gen) {
  ft::pair<_Base_ptr, _Base_ptr> __ret =
      __get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));
  if (__ret.second) {
    return __insert(__ret.first, __ret.second, __v, __node_gen);
  }
  return iterator(__ret.first);
}

// TODO: test and add comment
/**
 * @brief copy tree include header of tree
 *
 * @param __x: root of new tree
 * @param __p: first, header of *this and than parent of __x
 * @param __node_gen: __alloc_node functor
 * @return __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Link_type
 */
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
template <typename _NodeGenerator>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Link_type
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__copy_tree(
    _Link_type __x, _Base_ptr __p, _NodeGenerator &__node_gen) {
  _Link_type __top =
      __clone_node(__x, __node_gen);  // clone data of current node
  __top->__parent_ = __p;             // link parent

  if (__x->__right_) {
    __top->__right_ = __copy_tree(__S_right(__x), __top, __node_gen);
  }
  __p = __top;
  __x = __S_left(__x);

  while (__x != NULL) {
    _Link_type __y = __clone_node(__x, __node_gen);
    __p->__left_ = __y;
    __y->__parent_ = __p;
    if (__x->__right_) {
      __y->__right_ = __copy_tree(__S_right(__x), __y, __node_gen);
    }
    __p = __y;
    __x = __S_left(__x);
  }
  return __top;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__erase_without_balance(
    _Link_type __x) {
  while (__x != NULL) {
    __erase_without_balance(__S_right(__x));
    _Link_type __y = __S_left(__x);
    __delete_node(__x);
    __x = __y;
  }
}

/**
 * @brief helper function to erase specific node and rebalance
 *
 * @param __position
 */
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__erase_helper(
    const_iterator __position) {
  _Link_type __y = static_cast<_Link_type>(__tree_erase_and_fixup(
      const_cast<_Base_ptr>(__position.__node_), __impl_.__header_));
  __delete_node(__y);
  --__impl_.__node_count_;
}

/**
 * @brief helper function to erase nodes in range and rebalance
 *
 * @param __first
 * @param __last
 */
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__erase_helper(
    const_iterator __first, const_iterator __last) {
  if (__first == begin() && __last == end())
    clear();
  else
    while (__first != __last) __erase_helper(__first++);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(const key_type &__v) {
  ft::pair<const_iterator, const_iterator> __p = equal_range(__v);
  const size_type __prev_size = size();
  __erase_helper(__p.first, __p.second);
  return __prev_size - size();
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::swap(__tree &__t) {
  if (__root() == NULL) {
    if (__t.__root() != NULL) __impl_.__tree_move_data(__t.__impl_);
  } else if (__t.__root() == NULL)
    __t.__impl_.__tree_move_data(__impl_);
  else {
    ft::swap(__root(), __t.__root());
    ft::swap(__leftmost(), __t.__leftmost());
    ft::swap(__rightmost(), __t.__rightmost());

    __root()->__parent_ = __end();
    __t.__root()->__parent_ = __t.__end();
    ft::swap(__impl_.__node_count_, __t.__impl_.__node_count_);
  }
  ft::swap(__impl_.__key_comp, __t.__impl_.__key_comp);
  ft::swap(__get_Node_allocator(), __t.__get_Node_allocator());
}

/**
 * @brief key보다 같거나 큰 element를 리턴
 *
 * @param __x: starting node
 * @param __y: backup node
 * @param __k: key to compare
 * @return __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
 */
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__lower_bound_helper(
    _Link_type __x, _Base_ptr __y, const key_type &__k) {
  while (__x != NULL) {
    if (!__impl_.__key_comp(__S_key(__x), __k)) {
      __y = __x;
      __x = __S_left(__x);
    } else {
      __x = __S_right(__x);
    }
  }
  return iterator(__y);
}
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__lower_bound_helper(
    _Const_link_type __x, _Const_base_ptr __y, const key_type &__k) const {
  while (__x != NULL) {
    if (!__impl_.__key_comp(__S_key(__x), __k)) {
      __y = __x;
      __x = __S_left(__x);
    } else {
      __x = __S_right(__x);
    }
  }
  return const_iterator(__y);
}

/**
 * @brief key보다 큰 element를 리턴
 *
 * @param __x: starting node
 * @param __y: backup node
 * @param __k: key to compare
 * @return __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
 */
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__upper_bound_helper(
    _Link_type __x, _Base_ptr __y, const key_type &__k) {
  while (__x != NULL) {
    if (__impl_.__key_comp(__k, __S_key(__x))) {
      __y = __x;
      __x = __S_left(__x);
    } else {
      __x = __S_right(__x);
    }
  }
  return iterator(__y);
}
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__upper_bound_helper(
    _Const_link_type __x, _Const_base_ptr __y, const key_type &__k) const {
  while (__x != NULL) {
    if (__impl_.__key_comp(__k, __S_key(__x))) {
      __y = __x;
      __x = __S_left(__x);
    } else {
      __x = __S_right(__x);
    }
  }
  return const_iterator(__y);
}

/**
 * @brief 컨테이너 안의 주어진 키를 포함하는 범위를 리턴.
 *        first: >= key, second: > key.
 *
 * @param __k
 * @return ft::pair<iterator, iterator>
 */
template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
ft::pair<typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator,
         typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator>
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::equal_range(
    const key_type &__k) {
  _Link_type __x = __begin();
  _Base_ptr __y = __end();
  while (__x != NULL) {
    if (__impl_.__key_comp(__S_key(__x), __k))
      __x = __S_right(__x);
    else if (__impl_.__key_comp(__k, __S_key(__x))) {
      __y = __x;
      __x = __S_left(__x);
    } else {  // key of __x == __k
      _Link_type __x_up(__x);
      _Base_ptr __y_up(__y);
      __y = __x;
      __x = __S_left(__x);
      __x_up = __S_right(__x_up);
      return ft::pair<iterator, iterator>(
          __lower_bound_helper(__x, __y, __k),
          __upper_bound_helper(__x_up, __y_up, __k));
    }
  }
  return ft::pair<iterator, iterator>(iterator(__y), iterator(__y));
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
ft::pair<
    typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator,
    typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator>
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::equal_range(
    const key_type &__k) const {
  _Const_link_type __x = __begin();
  _Const_base_ptr __y = __end();
  while (__x != NULL) {
    if (__impl_.__key_comp(__S_key(__x), __k))
      __x = __S_right(__x);
    else if (__impl_.__key_comp(__k, __S_key(__x))) {
      __y = __x;
      __x = __S_left(__x);
    } else {  // key of __x == __k
      _Const_link_type __x_up(__x);
      _Const_base_ptr __y_up(__y);
      __y = __x;
      __x = __S_left(__x);
      __x_up = __S_right(__x_up);
      return ft::pair<const_iterator, const_iterator>(
          __lower_bound_helper(__x, __y, __k),
          __upper_bound_helper(__x_up, __y_up, __k));
    }
  }
  return ft::pair<const_iterator, const_iterator>(const_iterator(__y),
                                                  const_iterator(__y));
}

static __tree_node_base *local_tree_increment(__tree_node_base *__x)
    FT_NOEXCEPT {
  if (__x->__right_ != NULL) {
    __x = __x->__right_;
    while (__x->__left_ != NULL) __x = __x->__left_;
  } else {
    __tree_node_base *__y = __x->__parent_;
    while (__x == __y->__right_) {
      __x = __y;
      __y = __y->__parent_;
    }
    if (__x->__right_ != __y) {
      __x = __y;
    }
  }
  return __x;
}

__tree_node_base *__tree_increment(__tree_node_base *__x) FT_NOEXCEPT {
  return local_tree_increment(__x);
}

const __tree_node_base *__tree_increment(const __tree_node_base *__x)
    FT_NOEXCEPT {
  return local_tree_increment(const_cast<__tree_node_base *>(__x));
}

// Return: prev node by in-order traverse
static __tree_node_base *local_tree_decrement(__tree_node_base *__x) {
  // if __x is head of RB-tree
  if (__x->__color_ == RED && __x->__parent_->__parent_ == __x) {
    __x = __x->__right_;
    // left가 존재하면, left노드의 right-most
  } else if (__x->__left_ != NULL) {
    __tree_node_base *__y = __x->__left_;
    while (__y->__right_ != 0) __y = __y->__right_;
    __x = __y;
    // left가 존재하지 않으면, 부모 노드가 조부모 노드의 left여야함.
  } else {
    __tree_node_base *__y = __x->__parent_;
    while (__x == __y->__left_) {
      __x = __y;
      __y = __y->__parent_;
    }
    __x = __y;
  }
  return __x;
}

__tree_node_base *__tree_decrement(__tree_node_base *__x) FT_NOEXCEPT {
  return local_tree_decrement(__x);
}
const __tree_node_base *__tree_decrement(const __tree_node_base *__x)
    FT_NOEXCEPT {
  return local_tree_decrement(const_cast<__tree_node_base *>(__x));
}

/**
 * @brief Tree rotate left
 *
 * @param __x: node to rotate
 * @param __root: root of tree
 */
void __tree_rotate_left(__tree_node_base *const __x,
                        __tree_node_base *&__root) {
  __tree_node_base *const __y = __x->__right_;

  __x->__right_ = __y->__left_;
  if (__y->__left_ != NULL) __y->__left_->__parent_ = __x;
  __y->__parent_ = __x->__parent_;

  if (__x == __root) {
    __root = __y;
  } else if (__x == __x->__parent_->__left_) {
    __x->__parent_->__left_ = __y;
  } else {
    __x->__parent_->__right_ = __y;
  }
  __y->__left_ = __x;
  __x->__parent_ = __y;
}

/**
 * @brief Tree rotate right
 *
 * @param __x: node to rotate
 * @param __root: root of tree
 */
void __tree_rotate_right(__tree_node_base *const __x,
                         __tree_node_base *&__root) {
  __tree_node_base *const __y = __x->__left_;

  __x->__left_ = __y->__right_;
  if (__y->__right_ != NULL) __y->__right_->__parent_ = __x;
  __y->__parent_ = __x->__parent_;

  if (__x == __root) {
    __root = __y;
  } else if (__x == __x->__parent_->__right_) {
    __x->__parent_->__right_ = __y;
  } else {
    __x->__parent_->__left_ = __y;
  }
  __y->__right_ = __x;
  __x->__parent_ = __y;
}

static void local_init_new_node(const bool __insert_left,
                                __tree_node_base *&__x, __tree_node_base *&__p,
                                __tree_node_base &__header) FT_NOEXCEPT {
  // initiate new node
  __x->__parent_ = __p;
  __x->__right_ = NULL;
  __x->__left_ = NULL;
  __x->__color_ = RED;

  // __p의 left에 __x를 삽입
  if (__insert_left) {
    __p->__left_ = __x;  // __p가 __header여도 leftmost = __x 유지

    // 트리에 노드가 하나도 없는 경우
    if (__p == &__header) {
      __header.__parent_ = __x;
      __header.__right_ = __x;
    } else if (__p == __header.__left_) {
      __header.__left_ = __x;  // __p가 leftmost인 경우 __x가 leftmost
    }
  } else {  // __p의 right에 __x 삽입
    __p->__right_ = __x;
    if (__p == __header.__right_)
      __header.__right_ = __x;  // __p가 rightmost인 경우 __x가 rightmost
  }
}

/**
 * @brief Insert new node in tree and rebalance.
 *        __x와 __p가 들어갈 위치는 찾아서 들어온다고 가정.
 *        __x가 처음 insert 된다면, left에 insert (__p가 header이므로)
 *        header의 root, leftmost, rightmost를 잘 저장
 *
 * @param __insert_left : insert left or not
 * @param __x : Node to insert
 * @param __p : Parent Node
 * @param __header : head of rb-tree
 */
void __tree_insert_and_fixup(const bool __insert_left, __tree_node_base *__x,
                             __tree_node_base *__p,
                             __tree_node_base &__header) FT_NOEXCEPT {
  __tree_node_base *&__root = __header.__parent_;

  local_init_new_node(__insert_left, __x, __p, __header);

  // rebalance
  // __x가 root까지 올라오거나,
  // 부모가 red가 아닐때까지 (자식을 red로 넣었으므로!)
  while (__x != __root && __x->__parent_->__color_ == RED) {
    __tree_node_base *const __xpp = __x->__parent_->__parent_;

    if (__x->__parent_ == __xpp->__left_) {
      __tree_node_base *const __y = __xpp->__right_;

      if (__y && __y->__color_ == RED) {  // __x의 uncle 노드가 RED
        __x->__parent_->__color_ = BLACK;
        __y->__color_ = BLACK;
        __xpp->__color_ = RED;
        __x = __xpp;
      } else {  // __x의 uncle 노드가 black
        if (__x == __x->__parent_->__right_) {
          __x = __x->__parent_;
          __tree_rotate_left(__x, __root);
        }
        __x->__parent_->__color_ = BLACK;
        __xpp->__color_ = RED;
        __tree_rotate_right(__xpp, __root);
      }
    } else {
      __tree_node_base *const __y = __xpp->__left_;

      if (__y && __y->__color_ == RED) {
        __x->__parent_->__color_ = BLACK;
        __y->__color_ = BLACK;
        __xpp->__color_ = RED;
        __x = __xpp;
      } else {
        if (__x == __x->__parent_->__left_) {
          __x = __x->__parent_;
          __tree_rotate_right(__x, __root);
        }
        __x->__parent_->__color_ = BLACK;
        __xpp->__color_ = RED;
        __tree_rotate_left(__xpp, __root);
      }
    }
  }
  __root->__color_ = BLACK;
}

// TODO: explain logic
__tree_node_base *__tree_erase_and_fixup(
    __tree_node_base *const __z, __tree_node_base &__header) FT_NOEXCEPT {
  __tree_node_base *&__root = __header.__parent_;
  __tree_node_base *&__leftmost = __header.__left_;
  __tree_node_base *&__rightmost = __header.__right_;
  __tree_node_base *__y = __z;
  __tree_node_base *__x = NULL;
  __tree_node_base *__x_p = NULL;

  if (__y->__left_ == NULL)
    __x = __y->__right_;
  else if (__y->__right_ == NULL)
    __x = __y->__left_;
  else {
    __y = __y->__right_;
    // __tree_node_base::__S_minimum(__y->__right_);  // __y: successor of __Z
    while (__y->__left_ != NULL) __y = __y->__left_;
    __x = __y->__right_;
  }

  if (__y != __z) {
    __z->__left_->__parent_ = __y;
    __y->__left_ = __z->__left_;
    if (__y != __z->__right_) {
      __x_p = __y->__parent_;
      if (__x) __x->__parent_ = __y->__parent_;
      __y->__parent_->__left_ = __x;
      __y->__right_ = __z->__right_;
      __z->__right_->__parent_ = __y;
    } else
      __x_p = __y;
    if (__root == __z)
      __root = __y;
    else if (__z->__parent_->__left_ == __z)
      __z->__parent_->__left_ = __y;
    else
      __z->__parent_->__right_ = __y;
    __y->__parent_ = __z->__parent_;
    ft::swap(__y->__color_, __z->__color_);
    __y = __z;  // __y points to node actually deleted
  } else {
    __x_p = __y->__parent_;
    if (__x) __x->__parent_ = __y->__parent_;
    if (__root == __z)
      __root = __x;
    else if (__z->__parent_->__left_ == __z)
      __z->__parent_->__left_ = __x;
    else
      __z->__parent_->__right_ = __x;
    if (__leftmost == __z) {
      if (__z->__right_ == NULL)
        __leftmost = __z->__parent_;
      else
        __leftmost = __tree_node_base::__S_minimum(__x);
    }
    if (__rightmost == __z) {
      if (__z->__left_ == NULL)
        __rightmost = __z->__parent_;
      else
        __rightmost = __tree_node_base::__S_maximum(__x);
    }
  }

  if (__y->__color_ != RED) {
    while (__x != __root && (__x == NULL || __x->__color_ == BLACK)) {
      if (__x == __x_p->__left_) {
        __tree_node_base *__w = __x_p->__right_;
        if (__w->__color_ == RED) {
          __w->__color_ = BLACK;
          __x_p->__color_ = RED;
          __tree_rotate_left(__x_p, __root);
          __w = __x_p->__right_;
        }
        if ((__w->__left_ == NULL || __w->__left_->__color_ == BLACK) &&
            (__w->__right_ == NULL || __w->__right_->__color_ == BLACK)) {
          __w->__color_ = RED;
          __x = __x_p;
          __x_p = __x_p->__parent_;
        } else {
          if (__w->__right_ == NULL || __w->__right_->__color_ == BLACK) {
            __w->__left_->__color_ = BLACK;
            __w->__color_ = RED;
            __tree_rotate_right(__w, __root);
            __w = __x_p->__right_;
          }
          __w->__color_ = __x_p->__color_;
          __x_p->__color_ = BLACK;
          if (__w->__right_) __w->__right_->__color_ = BLACK;
          __tree_rotate_left(__x_p, __root);
          break;
        }
      } else {
        __tree_node_base *__w = __x_p->__left_;
        if (__w->__color_ == RED) {
          __w->__color_ = BLACK;
          __x_p->__color_ = RED;
          __tree_rotate_right(__x_p, __root);
          __w = __x_p->__left_;
        }
        if ((__w->__right_ == NULL || __w->__right_->__color_ == BLACK) &&
            (__w->__left_ == NULL || __w->__left_->__color_ == BLACK)) {
          __w->__color_ = RED;
          __x = __x_p;
          __x_p = __x_p->__parent_;
        } else {
          if (__w->__left_ == NULL || __w->__left_->__color_ == BLACK) {
            __w->__right_->__color_ = BLACK;
            __w->__color_ = RED;
            __tree_rotate_left(__w, __root);
            __w = __x_p->__left_;
          }
          __w->__color_ = __x_p->__color_;
          __x_p->__color_ = BLACK;
          if (__w->__left_) __w->__left_->__color_ = BLACK;
          __tree_rotate_right(__x_p, __root);
          break;
        }
      }
    }
    if (__x) __x->__color_ = BLACK;
  }
  // if (__y) {
  //   __y->__left_ = __y->__right_ = __y->__parent_ = NULL;
  // }
  return __y;
}

}  // namespace ft

#endif  // __TREE
