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
void allocTest(std::allocator<int> myAlloc, int **arr) {
  myAlloc.construct(*arr, 1);
  myAlloc.construct(*arr + 1, 1);
  myAlloc.construct(*arr + 2, 1);
  // for (int i = 0; i < 2; i++) std::cout << sizeof(*arr[i]) << ",";
  // for (int i = 0; i < 2; i++) std::cout << *arr[i] << ",";
  *arr = NULL;
}

int main() {
  std::allocator<int> myAlloc;
  int *arr = myAlloc.allocate(14);
  allocTest(myAlloc, &arr);
  myAlloc.deallocate(arr, 243256);
}