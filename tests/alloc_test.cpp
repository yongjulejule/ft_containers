/**
 * @file alloc_test.cpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief allocator test
 * @version 0.1
 * @date 2022-03-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <memory>
#include <vector>
void allocTest(std::allocator<int> myAlloc, int **arr) {
  myAlloc.construct(*arr, 1);
  myAlloc.construct(*arr + 1, 1);
  myAlloc.construct(*arr + 2, 1);
  // for (int i = 0; i < 2; i++) std::cout << sizeof(*arr[i]) << ",";
  // for (int i = 0; i < 2; i++) std::cout << *arr[i] << ",";
}

namespace my {
template <class _ForwardIterator, class _Tp>
void uninitialized_fill(_ForwardIterator __f, _ForwardIterator __l,
                        const _Tp &__x) {
  typedef
      typename std::iterator_traits<_ForwardIterator>::value_type value_type;
#ifndef _LIBCPP_NO_EXCEPTIONS
  _ForwardIterator __s = __f;
  try {
#endif
    for (; __f != __l; ++__f)
      ::new (static_cast<void *>(_VSTD::addressof(*__f))) value_type(__x);
#ifndef _LIBCPP_NO_EXCEPTIONS
  } catch (...) {
    for (; __s != __f; ++__s) __s->~value_type();
    throw;
  }
#endif
}
}  // namespace my

void test_init_is_heap() {
  // int *val = NULL;
  // my::uninitialized_fill(val, val + 7, 42);
  // return val;
  int b = 42;
  int c = b;
  int *val = ::new (static_cast<void *>(&c)) int(b);
  std::cout << *val;
}

int main() {
  std::allocator<int> myAlloc;
  int *arr = myAlloc.allocate(14);
  allocTest(myAlloc, &arr);
  // std::vector<int> a(42, 10, myAlloc);
  // std::cout << sizeof(a);
  myAlloc.deallocate(arr, 1);
  std::cout << "\n";

  // int *aa;
  // new (static_cast<void *>(aa)) int;

  // std::cout << *aa;
  // delete aa;
  {
    int arr[10];
    std::uninitialized_fill(&arr[0], &arr[10], 42);
    std::cout << *arr << "\n";
  }

  { test_init_is_heap(); }
  // int *val = test_init_is_heap();
  // for (int *tmp = val; tmp < val + 10; tmp++) {
  //   std::cout << *tmp << ",";
  // }
  // myAlloc.deallocate(val, 1);
  system("leaks mine.out");
}