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

#include <memory>

#include "iterator.hpp"
#include "utility.hpp"

#define FT_NOEXCPT throw()

namespace ft {

/*************************************************
 NOTE: LLVM
 *************************************************/

// template <typename _NodePtr>
// inline bool __tree_is_left_child(_NodePtr __x) FT_NOEXCPT {
//   return __x == __x->__parent_->__left_;
// }

// // __x로 만들어지는 subtree가 적절한 rb-tree인지 판별.
// // 적절하지 못하면 0, 적절하면 black-height 리턴
// template <typename _NodePtr>
// unsigned int __tree_sub_invariant(_NodePtr __x) {
//   // 적절한 트리
//   if (__x == NULL) return 1;

//   // 잘못된 트리
//   if (__x->__left_ != NULL && __x->__left_->__parent_ != __x) return 0;
//   if (__x->__right_ != NULL && __x->__left_ != NULL) return 0;

//   // red의 자식들은 black 이여야 함
//   if (!__x->__is_black_) {
//     if (__x->__left_ && !__x->__left_->__is_black_) return 0;
//     if (__x->__right_ && !__x->__right_->__is_black_) return 0;
//   }
//   unsigned int __h = __tree_sub_invariant(__x->__left_);

//   // invalid
//   if (__h == 0) return 0;

//   // subtree가 rb-tree의 조건을 충족하지 못함
//   if (__h != __tree_sub_invariant(__x->__right_)) return 0;

//   // black-height 리턴
//   return __h + __x->__is_black;
// }

// template <typename _NodePtr>
// inline _NodePtr __tree_min(_NodePtr __x) FT_NOEXCPT {
//   while (__x->__left_ != NULL) __x = __x->__left_;
//   return __x;
// }

// template <typename _NodePtr>
// inline _NodePtr __tree_max(_NodePtr __x) FT_NOEXCPT {
//   while (__x->__right_ != NULL) __x = __x->__right_;
//   return __x;
// }

// // Return: next node by in-order traverse
// template <typename _NodePtr>
// _NodePtr __tree_next(_NodePtr __x) FT_NOEXCPT {
//   if (__x->__right_ != NULL) return __tree_min(__x->__right_);
//   while (!__tree_is_left_child(__x)) __x = __x->__parent_unsafe();
//   return __x->__parent_unsafe();
// }

// // Return: next node by in-order traverse as EndNodePtr
// template <typename _EndNodePtr, typename _NodePtr>
// _EndNodePtr __tree_next_iter(_NodePtr __x) FT_NOEXCPT {
//   if (__x->__right_ != NULL)
//     return static_cast<_EndNodePtr>(__tree_min(__x->__right_));
//   while (!__tree_is_left_child(__x)) __x = __x->__parent_unsafe();
//   return static_cast<_EndNodePtr>(__x->__parent_unsafe());
// }

// // add prev, insert_rebalance, remove_rebalance

// template <typename _Key, typename _Value>
// struct __value_type;

// template <typename _T>
// struct __tree_key_value_types {
//   typedef _T key_type;
//   typedef _T __node_value_type;
//   typedef _T __container_value_type;
//   static const bool __is_map = false;

//   static key_type const &__get_key(_T const &__v) { return __v; }
//   static __container_value_type const &__get_value(
//       __node_value_type const &__v) {
//     return __v;
//   }
//   static __container_value_type *__get_ptr(__node_value_type &__v) {
//     return &(__n);
//   }
// };

// // value_type is defined in map.hpp
// template <typename _Key, typename _T>
// struct __tree_key_value_types<__value_type<_Key, _T> > {
//   typedef _Key key_type;
//   typedef _T mapped_type;
//   typedef __value_type<_Key, _T> __node_value_type;
//   typedef ft::pair<const _Key, _T> __container_value_type;
//   typedef __container_value_type __map_value_type;
//   static const bool __is_map = true;

//   // NOTE: remove_cv and get key or value is needed?
//   static key_type const &__get_key(__node_value_type const &__t) {
//     return __t.__get_value().first;
//   }

//   static __container_value_type const &__get_value(
//       __node_value_type const &__t) {
//     return __t.__get_value();
//   }

//   static __container_value_type *__get_ptr(__node_value_type &__n) {
//     return &(__n.__get_value());
//   }
// };

// struct __tree_node_base;
// struct __tree_end_node;

// struct __tree_node_base_types {
//   typedef __tree_node_base __node_base_type;
//   typedef __node_base_type *__node_base_pointer;
//   typedef __tree_end_node __end_node_type;
//   typedef __end_node_type *__end_node_pointer;
//   typedef __end_node_pointer;
// };

// template <typename _T, typename _KVtypes = __tree_key_value_types<_T>,
//           bool = _KVtypes::__is_map>
// struct __tree_map_pointer_types {};

// template <typename _T, typename _KVtypes>
// struct __tree_map_pointer_types<_T, _KVtypes, true> {
//   typedef typename _KVtypes::__map_value_type __map_value_type;
//   typedef __map_value_type *__map_value_type_pointer;
// };

// template <typename _T, typename _disable = void>
// struct __tree_node_types;

// template <typename _T>
// struct __tree_node;

// template <typename _T>
// struct __tree_node_types<_T *, __tree_node<_T> >
//     : public __tree_node_base_types,
//       __tree_key_value_types<_T>,
//       __tree_map_pointer_types<_T> {
//   typedef __tree_node_base_types __base;
//   typedef __tree_key_value_types<_T> __key_base;
//   typedef __tree_map_pointer_types<_T> __map_pointer_base;

//  public:
//   typedef _T __node_type;
//   typedef __node_type *_node_pointer;
// };

/*************************************************
 NOTE: GCC
 *************************************************/

/*************************************************************************************
 * @brief Tree Nodes Methods
 *************************************************************************************/

enum __tree_node_color { RED = false, BLACK = true };

struct __tree_node_base;

__tree_node_base *__tree_increment(__tree_node_base *__x) FT_NOEXCPT;
const __tree_node_base *__tree_increment(const __tree_node_base *__x)
    FT_NOEXCPT;

__tree_node_base *__tree_decrement(__tree_node_base *__x) FT_NOEXCPT;
const __tree_node_base *__tree_decrement(const __tree_node_base *__x)
    FT_NOEXCPT;

void __tree_rotate_left(__tree_node_base *const __x, __tree_node_base *&__root);
void __tree_rotate_right(__tree_node_base *const __x,
                         __tree_node_base *&__root);

void __tree_insert_and_fixup(const bool __insert_left, __tree_node_base *__x,
                             __tree_node_base *__p,
                             __tree_node_base &__header) FT_NOEXCPT;

__tree_node_base *__tree_erase_and_fixup(__tree_node_base *const __z,
                                         __tree_node_base &__header) FT_NOEXCPT;

unsigned int __tree_black_count(const __tree_node_base *__node,
                                const __tree_node_base *__root) FT_NOEXCPT;

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

  static _Base_ptr __S_minimum(_Base_ptr __x) FT_NOEXCPT {
    while (__x->__left_ != 0) __x = __x->__left_;
    return __x;
  }

  static _Const_base_ptr __S_minimum(_Const_base_ptr __x) FT_NOEXCPT {
    while (__x->__left_ != 0) __x = __x->__left_;
    return __x;
  }

  static _Base_ptr __S_maximum(_Base_ptr __x) FT_NOEXCPT {
    while (__x->__right_ != NULL) __x = __x->__right_;
    return __x;
  }

  static _Const_base_ptr __S_maximum(_Const_base_ptr __x) FT_NOEXCPT {
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
template <typename _key_compare>
struct __tree_key_compare {
  _key_compare __key_comp;

  __tree_key_compare() : __key_comp() {}
  __tree_key_compare(const _key_compare &other) : __key_comp(other) {}
};

// Node for rb-tree
template <typename _Val>
struct __tree_node : public __tree_node_base {
  typedef __tree_node<_Val> *__link_type;

  _Val __value_field;

  _Val *__valptr() { return &__value_field; }
  const _Val *__valptr() const { return &__value_field; }
};

/*************************************************************************************
 * @brief Tree Nodes Iterator
 *************************************************************************************/

template <typename _T>
struct __tree_iterator {
  typedef _T value_type;
  typedef _T &reference;
  typedef _T *pointer;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef __tree_iterator<_T> iterator_type;
  typedef __tree_node_base::_Base_ptr _Base_ptr;
  typedef __tree_node<_T> *__link_type;

  _Base_ptr __node_;

  __tree_iterator() : __node_() {}

  explicit __tree_iterator(_Base_ptr __x) : __node_(__x) {}

  reference operator*() const FT_NOEXCPT {
    return *static_cast<__link_type>(__node_)->__valptr();
  }

  pointer operator->() const FT_NOEXCPT {
    return static_cast<__link_type>(__node_)->__valptr();
  }

  iterator_type &operator++() FT_NOEXCPT {
    __node_ = __tree_increment(__node_);
    return *this;
  }

  iterator_type operator++(int) FT_NOEXCPT {
    iterator_type __tmp(*this);
    ++(*this);
    return __tmp;
  }

  iterator_type &operator--() FT_NOEXCPT {
    __node_ = __tree_decrement(__node_);
    return *this;
  }

  iterator_type operator--(int) FT_NOEXCPT {
    iterator_type __tmp(*this);
    --(*this);
    return __tmp;
  }

  friend bool operator==(const iterator_type &lhs,
                         const iterator_type &rhs) FT_NOEXCPT {
    return lhs.__node_ == rhs.__node_;
  }
};

template <typename _T>
bool operator!=(const __tree_iterator<_T> &lhs,
                const __tree_iterator<_T> &rhs) FT_NOEXCPT {
  return !(lhs == rhs);
}

template <typename _T>
struct __tree_const_iterator {
  typedef _T value_type;
  typedef const _T *pointer;
  typedef const _T &reference;
  typedef bidirectional_iterator_tag iterator_catrgory;
  typedef ptrdiff_t difference_type;

  typedef __tree_iterator<_T> iterator;
  typedef __tree_const_iterator<_T> const_iterator_type;
  typedef __tree_node_base::_Base_ptr _Base_ptr;
  typedef const __tree_node<_T> *__link_type;

  _Base_ptr __node_;

  __tree_const_iterator() FT_NOEXCPT : __node_() {}
  explicit __tree_const_iterator(_Base_ptr __x) FT_NOEXCPT : __node_(__x) {}

  iterator __remove_const() const FT_NOEXCPT {
    return iterator(const_cast<typename iterator::_Base_ptr>(__node_));
  }

  reference operator*() const FT_NOEXCPT {
    return *static_cast<__link_type>(__node_)->__valptr();
  }

  pointer operator->() const FT_NOEXCPT {
    return static_cast<__link_type>(__node_)->__valptr();
  }

  const_iterator_type &operator++() FT_NOEXCPT {
    __node_ = __tree_increment(__node_);
    return *this;
  }

  const_iterator_type operator++(int) FT_NOEXCPT {
    const_iterator_type __tmp(*this);
    ++(*this);
    return __tmp;
  }

  const_iterator_type &operator--() FT_NOEXCPT {
    __node_ = __tree_decrement(__node_);
    return *this;
  }

  const_iterator_type operator--(int) FT_NOEXCPT {
    const_iterator_type __tmp(*this);
    --(*this);
    return __tmp;
  }

  friend bool operator==(const const_iterator_type &lhs,
                         const const_iterator_type &rhs) FT_NOEXCPT {
    return lhs.__node_ == rhs.__node_;
  }
};

template <typename _T>
bool operator!=(const __tree_const_iterator<_T> &lhs,
                const __tree_const_iterator<_T> &rhs) FT_NOEXCPT {
  return !(lhs == rhs);
}

/*************************************************************************************
 * @brief Tree
 *************************************************************************************/

/**
 * @brief RB-tree class
 *
 * @tparam _Key: key of each node
 * @tparam _Val: value of each node
 * @tparam _KeyofValue: get key of value functor
 * @tparam _Compare: Comparing functor
 * @tparam _Alloc: allocator (default: std::allocator<_Val>)
 */
template <typename _Key, typename _Val, typename _KeyofValue, typename _Compare,
          typename _Alloc = std::allocator<_Val> >
class __tree {
 public:
  typedef typename _Alloc::rebind<__tree_node<_Val> >::other _Node_allocator;

 protected:
  typedef __tree_node_base *_Base_ptr;
  typedef const __tree_node_base *_Const_base_ptr;
  typedef __tree_node<_Val> *_Link_type;
  typedef const __tree_node<_Val> *_Const_link_type;

 public:
  typedef _Key key_type;
  typedef _Val value_type;
  typedef value_type *pointer;
  typedef const value_type *cosnt_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef _Alloc allocator_type;

  typedef __tree_iterator<value_type> iterator;
  typedef __tree_const_iterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> cosnt_rerverse_iterator;

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
  }

  // _Node_allocator: rebind of allocator
  // __tree_key_compare: key compare functor
  // __tree_header: head of tree
  template <typename _Key_compare>
  struct __tree_impl : public _Node_allocator,  // FIXME: 굳이 상속 왜받음??????
                       public __tree_key_compare,
                       public __tree_header {
    typedef __tree_key_compare<_Key_compare> _Base_key_compare;

    __tree_impl() : _Node_allocator() {}
    __tree_impl(const __tree_impl &other)
        : _Node_allocator(other),
          _Base_key_compare(other._Base_key_compare),
          __tree_header() {}
    __tree_impl(const _Key_compare &__comp, const _Node_allocator &__a)
        : _Node_allocator(__a), _Base_key_compare(__comp) {}
  };

  __tree_impl<_Compare> __impl_;

 public:
  // FIXME: Does this have to be public?
  _Node_allocator &__get_Node_allocator() { return this->__impl_; }
  const _Node_allocator &__get_Node_allocator() const { return this->__impl_; }

  // TODO: move to public methods
  allocator_type get_allocator() const {
    return allocator_type(__get_Node_allocator());
  }

 protected:
  // SECTION: generate/delete node
  _Link_type __allocate_node() { return get_allocator().construct(1); }

  void __deallocate_node(_Link_type __p) { get_allocator().deallocate(__p, 1); }

  void __construct_node(_Link_type __node, const value_type &__x) {
    get_allocator().construct(__node->__valptr(), __x);
  }

  _Link_type __create_node(const value_type &__x) {
    _Link_type __tmp = __alloc_node();
    __construct_node(__tmp, __x);
    return __tmp;
  }

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

  // SECTION: static methods
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

  // get position to insert
  ft::pair<_Base_ptr, _Base_ptr> __get_insert_unique_pos(const key_type &__k);
  // get hint and get position
  ft::pair<_Base_ptr, _Base_ptr> __get_insert_hint_unique_pos(
      const_iterator __pos, const key_type &__k);

  // insert
  template <typename _NodeGenerator>
  _Link_type __copy_tree(_Link_type __x, _Base_ptr __p,
                         _NodeGenerator &__node_gen);
  template <typename _NodeGenerator>
  _Link_type __copy_tree(const __tree &__t, _NodeGenerator &__node_gen) {
    // copy whole tree
    _Link_type __root = __copy(__t.__begin(), __end(), __node_gen);

    // update header
    __leftmost() = __S_minimum(__root);
    __rightmost() = __S_maximum(__root);
    __impl_.__node_count_ = __x.__impl_.__node_count_;
    return __root;
  }

  _Link_type __copy_tree(const __tree &__x) {
    __alloc_node __node_gen(*this);
    return __copy_tree(__x, __node_gen);
  }

  void __erase_without_balance(_Link_type __x);

 public:
  // SECTION: constructor/destructor
  __tree() {}
  __tree(const _Compare &_comp, const allocator_type &__a = allocator_type())
      : __impl_(_comp, _Node_allocator(__a)) {}
  __tree(const __tree &other) : __impl_(other.__impl_) {
    if (__other.__root() != NULL) __root() = __copy_data(other);
  }
  ~__tree() { __erase_without_balance(__begin()); }
  __tree &operator=(const __tree &other);

  // SECTION: public methods

  // access to data

  _Compare key_comp() const { return __impl_.__key_compare; }

  iterator begin() { return iterator(__impl_.__header_.__left_); }
  const_iterator begin() const {
    return const_iterator(__impl_.__header_.__left_);
  }

  iterator end() { return iterator(__impl_.__header_); }
  const_iterator end() const { return const_iterator(__impl_.__header_); }

  reverse_iterator rbegin() {
    return reverse_iterator(__impl_.__header_.__left_);
  }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(__impl_.__header_.__left_);
  }

  reverse_iterator rend() { return reverse_iterator(__impl_.__header_); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(__impl_.__header_);
  }

  // capacity
  bool empty() const { return __impl_.__node_count_ == 0; }
  size_type max_size() const { return __get_Node_allocator().max_size(); }
  size_type size() const { return __impl_.__node_count_; }
  void swap(__tree &__t);

  // modifiers

  void erase(iterator position);
  size_type erase(cosnt key_type &__v);
  void erase(iterator first, iterator last);

  template <typename _NodeGenerator>
  iterator __insert(_Base_ptr __x, _Base_ptr __p, const value_type &__v,
                    _NodeGenerator &__node_gen);
  ft::pair<_Base_ptr, bool> __insert_unique(const value_type &__v);
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
  void __insert_range(_InputIterator __first, __InputIterator __last) {
    __alloc_node __node(*this);
    for (; __first != __last; ++first) {
      __insert_unique_with_hint(end(), *__first, __node);
    }
  }

  // operations
  iterator find(const key_type &__k);
  cosnt_iterator find(const key_type &__k) const;

  size_type count(const key_type &__k) const;

  iterator lower_bound(const key_type &__k);
  const_iterator lower_bound(const key_type &__k) const;

  iterator upper_bound(const key_type &__k);
  const_iterator upper_bound(const key_type &__k) const;

  pair<iterator, iterator> equal_range(const key_value &__k);
  pair<const_iterator, const_iterator> equal_range(const key_value &__k) const;
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
    __comp = __impl_.__key_compare(__k, __S_key(__x));
    __x = __comp ? __S_left(__x) : __S_right(__x);
  }

  iterator __j = iterator(__y);
  if (__comp) {
    if (__j == begin())           // leftmost
      return ret_pair(__x, __y);  // (NULL, leaf)
    else
      --__j;  // decrement node
  }

  if (__impl_.__key_compare(__S_key(__j.__node_),
                            __k))      // compare before leaf and __k
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
  iterator __pos = const_cast<iterator>(__position);
  typedef ft::pair<_Base_ptr, _Base_ptr> ret_pair;

  if (__pos.__node_ == __end()) {  // header
    if (size() > 0 && __impl_.__key_compare(__S_key(__rightmost()), __k))
      return res_pair(NULL, __rightmost());
    else
      return __get_insert_unique_pos(__k);
  } else if (__impl_.__key_compare(__k,
                                   __S_key(__pos.__node_))) {  // less than pos
    iterator __before = __pos;

    if (__pos.__node_ == __leftmost()) {
      return ret_pair(__leftmost(), __leftmost());
    } else if (__impl_.__key_compare(__S_key((--__before).__node_), __k)) {
      if (__S_right(__before.__node_) == NULL)
        return ret_pair(NULL, __before.__node_);
      else
        return ret_pair(__pos.__node_, __pos.__node_);
    } else {
      return __get_insert_unique_pos(__k);
    }
  } else if (__impl_.__key_compare(__S_key(__pos.__node_),
                                   __k)) {  // more than pos
    iterator __after = _pos;

    if (__pos.__node_ == __rightmost()) {
      return ret_pair(NULL, __rightmost());
    } else if (__impl_.__key_compare(__k, __S_key((++__after).__node_))) {
      if (__S_right(__pos.__node_) == NULL)
        return ret_pair(NULL, __pos.__node_);
      else
        return ret_pair(__after.__node_, __after.__node_);
    } else {
      return __get_insert_unique_pos(__k);
    }
  } else  // equal to pos. the key cannot be same.
    return ret_pair(__pos.__node, NULL);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
template <typename _NodeGenerator>
typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__insert(
    _Base_ptr __x, _Base_ptr __p, const value_type &__v,
    _NodeGenerator &__node_gen) {
  bool __insert_left = (__x != 0 || __p == __end() ||
                        __impl.__key_compare(_KeyOfValue()(__v), __S_key(__p)));
  _Link_type __z = __node_gen(__v);
  __tree_insert_and_fixup(__insert_left, __z, __p, this->__impl_.__header_);
  ++__impl_.__node_count_;
  return iterator(__z);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
ft::pair<typename __tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr,
         bool>
__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__insert_unique(
    const value_type &__v) {
  typedef ft::pair<iterator, _Base_ptr> ret_pair;
  ft::pair<_Base_ptr, _Base_ptr> __ret = __get_insert_unique_pos(
      _KeyofValue()(__v));  // get position based key of __v

  if (__res.second) {
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
      __get_insert_hint_unique_pos(__position, _KeyofValue()(__v));
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
    if (__x->__parent_) {
      __y->__right_ = __copy_tree(__S_right(__x), __y, __node_gen);
    }
    __p = __y;
    __x = __S_left(__x);
  }
  return __top;
}
}  // namespace ft

#endif  // __TREE
