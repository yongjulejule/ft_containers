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

#define FT_NOEXCPT throw()

namespace ft {

enum __tree_node_color { red = false, black = true };

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

void __tree_balance_after_insert(const bool __insert_left,
                                 __tree_node_base *__x, __tree_node_base *__p,
                                 __tree_node_base &__header) FT_NOEXCPT;

__tree_node_base *__tree_rebalance_for_erase(
    __tree_node_base *const __z, __tree_node_base &__header) FT_NOEXCPT;

unsigned int __tree_black_count(const __tree_node_base *__node,
                                const __tree_node_base *__root) FT_NOEXCPT;

struct __tree_nil {
  __tree_node_color __color = black;
};

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

struct __tree_header {
  __tree_node_base __header_;
  std::size_t __node_count_;

  __tree_header() {
    __header_.__color_ = black;
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

}  // namespace ft

#endif  // __TREE
