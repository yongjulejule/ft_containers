/**
 * @file __tree.cpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief RB-tree algorithms implementation
 * @version 0.1
 * @date 2022-04-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "__tree.hpp"

#include "utility.hpp"

namespace ft {

__tree_node_base *__minimum(__tree_node_base *__x) FT_NOEXCEPT {
  while (__x->__left_ != NULL) __x = __x->__left_;
  return __x;
}

const __tree_node_base *__minimum(const __tree_node_base *__x) FT_NOEXCEPT {
  while (__x->__left_ != NULL) __x = __x->__left_;
  return __x;
}

__tree_node_base *__maximum(__tree_node_base *__x) FT_NOEXCEPT {
  while (__x->__right_ != NULL) __x = __x->__right_;
  return __x;
}

const __tree_node_base *__maximum(const __tree_node_base *__x) FT_NOEXCEPT {
  while (__x->__right_ != NULL) __x = __x->__right_;
  return __x;
}

// Return: next node by in-order traverse
static __tree_node_base *local_tree_increment(__tree_node_base *__x)
    FT_NOEXCEPT {
  if (__x->__right_ != NULL) {
    return __minimum(__x->__right_);
  }
  __tree_node_base *__y = __x->__parent_;
  while (__x == __y->__right_) {
    __x = __y;
    __y = __y->__parent_;
  }
  if (__x->__right_ != __y) {
    __x = __y;
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
  if (__x->__color_ == RED && __x->__parent_->__parent_ == __x) {
    return __x->__right_;
  }
  if (__x->__left_ != NULL) {
    return __maximum(__x->__left_);
  }
  __tree_node_base *__y = __x->__parent_;
  while (__x == __y->__left_) {
    __x = __y;
    __y = __y->__parent_;
  }
  return __y;
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

static void local_insert_new_node(const bool __insert_left,
                                  __tree_node_base *&__x,
                                  __tree_node_base *&__p,
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

static void local_insert_fixup(__tree_node_base *&__x,
                               __tree_node_base *&__root) {
  while (__x != __root && __x->__parent_->__color_ == RED) {
    __tree_node_base *const __xpp = __x->__parent_->__parent_;

    if (__x->__parent_ == __xpp->__left_) {
      __tree_node_base *const __y = __xpp->__right_;

      if (__y && __y->__color_ == RED) {  // __x의 uncle 노드가 RED(case 1)
        __x->__parent_->__color_ = BLACK;
        __y->__color_ = BLACK;
        __xpp->__color_ = RED;
        __x = __xpp;
      } else {  // __x의 uncle 노드가 black (case 2)
        if (__x == __x->__parent_->__right_) {
          __x = __x->__parent_;
          __tree_rotate_left(__x, __root);
        }
        __x->__parent_->__color_ = BLACK;  // case 3
        __xpp->__color_ = RED;
        __tree_rotate_right(__xpp, __root);
      }
    } else {
      __tree_node_base *const __y = __xpp->__left_;

      if (__y && __y->__color_ == RED) {  // sym case 1
        __x->__parent_->__color_ = BLACK;
        __y->__color_ = BLACK;
        __xpp->__color_ = RED;
        __x = __xpp;
      } else {
        if (__x == __x->__parent_->__left_) {  // sym case 2
          __x = __x->__parent_;
          __tree_rotate_right(__x, __root);
        }
        __x->__parent_->__color_ = BLACK;  // sym case 3
        __xpp->__color_ = RED;
        __tree_rotate_left(__xpp, __root);
      }
    }
  }
  __root->__color_ = BLACK;
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
  local_insert_new_node(__insert_left, __x, __p, __header);
  local_insert_fixup(__x, __root);
}

static void local_erase_node(__tree_node_base *const &__z,
                             __tree_node_base *&__y, __tree_node_base *&__x,
                             __tree_node_base *&__x_p,
                             __tree_node_base &__header) {
  __tree_node_base *&__root = __header.__parent_;
  __tree_node_base *&__leftmost = __header.__left_;
  __tree_node_base *&__rightmost = __header.__right_;

  if (__y->__left_ != NULL && __y->__right_ != NULL) {
    __y = __minimum(__y->__right_);  // __y: successor of __Z
    __x = __y->__right_;

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
    return;
  }

  __x = (__z->__left_ == NULL) ? __z->__right_ : __z->__left_;
  __x_p = __z->__parent_;
  if (__x) __x->__parent_ = __z->__parent_;
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
      __leftmost = __minimum(__x);
  }
  if (__rightmost == __z) {
    if (__z->__left_ == NULL)
      __rightmost = __z->__parent_;
    else
      __rightmost = __maximum(__x);
  }
}

inline static bool local_erase_fixup_left(__tree_node_base *&__x,
                                          __tree_node_base *&__x_p,
                                          __tree_node_base *&__root) {
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
    return true;
  }
  return false;
}

inline static bool local_erase_fixup_right(__tree_node_base *&__x,
                                           __tree_node_base *&__x_p,
                                           __tree_node_base *&__root) {
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
    return true;
  }
  return false;
}

static void local_erase_fixup(__tree_node_base *&__x, __tree_node_base *&__x_p,
                              __tree_node_base *&__root) {
  bool __is_end = false;
  while (__x != __root && (__x == NULL || __x->__color_ == BLACK) &&
         !__is_end) {
    if (__x == __x_p->__left_) {
      __is_end = local_erase_fixup_left(__x, __x_p, __root);
    } else {
      __is_end = local_erase_fixup_right(__x, __x_p, __root);
    }
  }
  if (__x) __x->__color_ = BLACK;
}

/**
 * @brief Delete Node in tree and rebalance and return deleted node
 *        __y : Node to replace __z
 *        __x : child node of __y
 *        __x_p : parent of __x
 *
 * @param __z : node to delete
 * @param __header : head of rb-tree
 * @return __tree_node_base*
 */
__tree_node_base *__tree_erase_and_fixup(
    __tree_node_base *const __z, __tree_node_base &__header) FT_NOEXCEPT {
  __tree_node_base *&__root = __header.__parent_;
  __tree_node_base *__y = __z;
  __tree_node_base *__x = NULL;
  __tree_node_base *__x_p = NULL;

  local_erase_node(__z, __y, __x, __x_p, __header);
  if (__y->__color_ != RED) local_erase_fixup(__x, __x_p, __root);
  return __y;
}

void __tree_header::__tree_reset() {
  __header_.__parent_ = NULL;
  __header_.__left_ = &__header_;
  __header_.__right_ = &__header_;
  __node_count_ = 0;
}

void __tree_header::__tree_move_data(__tree_header &other) {
  __header_.__color_ = other.__header_.__color_;
  __header_.__parent_ = other.__header_.__parent_;
  __header_.__left_ = other.__header_.__left_;
  __header_.__right_ = other.__header_.__right_;
  __header_.__parent_->__parent_ = &__header_;
  __node_count_ = other.__node_count_;

  other.__tree_reset();
}

}  // namespace ft