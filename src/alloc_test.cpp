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

int main() {
  std::allocator<int> myAlloc;
  int *arr = myAlloc.allocate(14);
  allocTest(myAlloc, &arr);
  std::vector<int> a(42, 10, myAlloc);
  std::cout << sizeof(a);
  myAlloc.deallocate(&arr[1], 1);
  std::cout << *arr;
  arr = NULL;
  std::cout << "\n";

  int *val = myAlloc.allocate(10);
  std::uninitialized_fill(val, val + 7, 42);
  for (int *tmp = val; tmp < val + 10; tmp++) {
    std::cout << *tmp << ",";
  }
  myAlloc.deallocate(val, 1);
  system("leaks a.out");
}