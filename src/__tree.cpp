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

namespace ft {

__tree_node_base *__tree_increment(__tree_node_base *__x) FT_NOEXCPT {}
const __tree_node_base *__tree_increment(const __tree_node_base *__x)
    FT_NOEXCPT {}

__tree_node_base *__tree_decrement(__tree_node_base *__x) FT_NOEXCPT;
const __tree_node_base *__tree_decrement(const __tree_node_base *__x)
    FT_NOEXCPT {}

void __tree_rotate_left(__tree_node_base *const __x, __tree_node_base *&__root);
void __tree_rotate_right(__tree_node_base *const __x,
                         __tree_node_base *&__root) {}

void __tree_balance_after_insert(const bool __insert_left,
                                 __tree_node_base *__x, __tree_node_base *__p,
                                 __tree_node_base &__header) FT_NOEXCPT {}

__tree_node_base *__tree_rebalance_for_erase(
    __tree_node_base *const __z, __tree_node_base &__header) FT_NOEXCPT {}

unsigned int __tree_black_count(const __tree_node_base *__node,
                                const __tree_node_base *__root) FT_NOEXCPT {}

}  // namespace ft