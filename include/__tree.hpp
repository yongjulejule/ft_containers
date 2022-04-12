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

struct __tree_nil {
  __tree_node_color __color = BLACK;
};

// base of node structure for rb-tree
struct __tree_node_base {
  typedef __tree_node_base *__base_ptr;
  typedef const __tree_node_base *__const_base_ptr;

  __tree_node_color __color_;
  __base_ptr __parent_;
  __base_ptr __left_;
  __base_ptr __right_;

  static __base_ptr __tree_min(__base_ptr __x) FT_NOEXCPT {
    while (__x->__left_ != 0) __x = __x->__left_;
    return __x;
  }

  static __const_base_ptr __tree_min(__const_base_ptr __x) FT_NOEXCPT {
    while (__x->__left_ != 0) __x = __x->__left_;
    return __x;
  }

  static __base_ptr __tree_max(__base_ptr __x) FT_NOEXCPT {
    while (__x->__right_ != NULL) __x = __x->__right_;
    return __x;
  }

  static __const_base_ptr __tree_max(__const_base_ptr __x) FT_NOEXCPT {
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
template <typename _val>
struct __tree_node : public __tree_node_base {
  typedef __tree_node<_val> *__link_type;

  _val __value_field;

  _val *__valptr() { return &__value_field; }
  const _val *__valptr() const { return &__value_field; }
};

template <typename _T>
struct __tree_iterator {
  typedef _T value_type;
  typedef _T &reference;
  typedef _T *pointer;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef __tree_iterator<_T> iterator_type;
  typedef __tree_node_base::__base_ptr __base_ptr;
  typedef __tree_node<_T> *__link_type;

  __base_ptr __node;

  __tree_iterator() : __node() {}

  explicit __tree_iterator(__base_ptr __x) : __node(__x) {}

  reference operator*() const FT_NOEXCPT {
    return *static_cast<__link_type>(__node)->__valptr();
  }

  pointer operator->() const FT_NOEXCPT {
    return static_cast<__link_type>(__node)->__valptr();
  }

  iterator_type &operator++() FT_NOEXCPT {
    __node = __tree_increment(__node);
    return *this;
  }

  iterator_type operator++(int) FT_NOEXCPT {
    iterator_type __tmp(*this);
    ++(*this);
    return __tmp;
  }

  iterator_type &operator--() FT_NOEXCPT {
    __node = __tree_decrement(__node);
    return *this;
  }

  iterator_type operator--(int) FT_NOEXCPT {
    iterator_type __tmp(*this);
    --(*this);
    return __tmp;
  }

  friend bool operator==(const iterator_type &lhs,
                         const iterator_type &rhs) FT_NOEXCPT {
    return lhs.__node == rhs.__node;
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
  typedef __tree_node_base::__base_ptr __base_ptr;
  typedef const __tree_node<_T> *__link_type;

  __base_ptr __node;

  __tree_const_iterator() FT_NOEXCPT : __node() {}
  explicit __tree_const_iterator(__base_ptr __x) FT_NOEXCPT : __node(__x) {}

  iterator __remove_const() const FT_NOEXCPT {
    return iterator(const_cast<typename iterator::__base_ptr>(__node));
  }

  reference operator*() const FT_NOEXCPT {
    return *static_cast<__link_type>(__node)->__valptr();
  }

  pointer operator->() const FT_NOEXCPT {
    return static_cast<__link_type>(__node)->__valptr();
  }

  const_iterator_type &operator++() FT_NOEXCPT {
    __node = __tree_increment(__node);
    return *this;
  }

  const_iterator_type operator++(int) FT_NOEXCPT {
    const_iterator_type __tmp(*this);
    ++(*this);
    return __tmp;
  }

  const_iterator_type &operator--() FT_NOEXCPT {
    __node = __tree_decrement(__node);
    return *this;
  }

  const_iterator_type operator--(int) FT_NOEXCPT {
    const_iterator_type __tmp(*this);
    --(*this);
    return __tmp;
  }

  friend bool operator==(const const_iterator_type &lhs,
                         const const_iterator_type &rhs) FT_NOEXCPT {
    return lhs.__node == rhs.__node;
  }
};

template <typename _T>
bool operator!=(const __tree_const_iterator<_T> &lhs,
                const __tree_const_iterator<_T> &rhs) FT_NOEXCPT {
  return !(lhs == rhs);
}

}  // namespace ft

#endif  // __TREE
