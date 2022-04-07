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
  myAlloc.construct(*arr, 42412);
  myAlloc.construct(*arr + 1, 1);
  myAlloc.construct(*arr + 2, 1);
  myAlloc.destroy(*arr);
  // for (int i = 0; i < 2; i++) std::cout << sizeof(*arr[i]) << ",";
  // for (int i = 0; i < 2; i++) std::cout << *arr[i] << ",";
}

void test_init_is_heap() {
  // int *val = NULL;
  // my::uninitialized_fill(val, val + 7, 42);
  // return val;
  int b = 42;
  int c = b;
  int *val = ::new (static_cast<void *>(&c)) int(b);
  std::cout << *val;
}

template <typename T>
void my_destroy(T t) {
  ~T(t);
}

int main() {
  std::allocator<int> myAlloc;
  int *arr = myAlloc.allocate(14);
  myAlloc.construct(arr, 424242);
  my_destroy(*arr);
  std::cout << *arr << "\n";
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
  {
    try {
      std::vector<int> a(SIZE_MAX, 42);
      a.push_back(1002);
    } catch (...) {
      std::cout << "alloc error?\n";
    }
  }

  // int *val = test_init_is_heap();
  // for (int *tmp = val; tmp < val + 10; tmp++) {
  //   std::cout << *tmp << ",";
  // }
  // myAlloc.deallocate(val, 1);
  system("leaks mine.out");
}