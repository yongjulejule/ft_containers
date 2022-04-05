/**
 * @file vector_main.cpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief How vector works?
 * @version 0.1
 * @date 2022-03-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "vector.hpp"

#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

#include "iterator.hpp"

void stl_vec_test() {
  // std::vector<int> thw(10, ULLONG_MAX);
  // ft::vector<int> ft_thw(10, ULLONG_MAX);
  int arr[] = {1, 2, 3, 4, 5};
  std::vector<int> a(arr, arr + 5);
  std::vector<bool> c;

  c.push_back(false);
  c.push_back(true);
  c.push_back(false);
  c.push_back(true);
  c.push_back(false);
  c.push_back(true);
  std::vector<bool>::iterator it = c.begin();
  std::vector<bool>::iterator ite = c.end();
  std::vector<int>::iterator it2 = a.begin();
  std::vector<int>::iterator ite2 = a.end();
  for (; it != ite; ++it) std::cout << *it << ",";
  std::cout << "\n";
  for (; it2 != ite2; it2++) std::cout << *it2 << ",";
  std::cout << "\n";
  std::cout << sizeof(c) << "\n";
  std::cout << sizeof(a) << "\n";
  std::cout << c.size() << "\n";
  std::cout << a.size() << "\n";
}

void my_vec_test() {
  ft::__vector_iterator<ft::iterator<ft::input_iterator_tag, int> > ok;

  std::cout << typeid(ok).name();
  ft::vector<int> dd;
  std::cout << typeid(dd.get_allocator()).name() << "\n";
  ft::vector<int> v(10);
  std::cout << "size is:" << v.size() << "\n";
  {
    ft::vector<int> my_v(10, 10);
    ft::vector<int>::iterator it = my_v.begin();
    ft::vector<int>::iterator ite = my_v.end();
    std::cout << "vector constructed by vector(size, value)\n";
    for (; it != ite; it++) {
      std::cout << *it << ", ";
    }
    std::cout << "\n";
  }
  // ft::vector<int> c_it(it, ite);
  {
    int arr[] = {1, 2, 3, 4, 5};
    ft::vector<int> my_v(arr, arr + 5);
    std::cout << "vector made by array iterator\n";
    std::cout << my_v.size() << "\n";
    ft::vector<int>::iterator it = my_v.begin();
    ft::vector<int>::iterator ite = my_v.end();
    for (; it != ite; it++) {
      std::cout << *it << ", ";
    }
    std::cout << "\n";
  }
}

int main(void) {
  std::cout << "===== stl_vec_test() =====\n";
  stl_vec_test();
  std::cout << "===== my_vec_test() =====\n";
  my_vec_test();
  std::vector<int> x(10, 10);
  std::vector<int>().swap(x);  // ??????????? 이런걸 왜하지?
  std::cout << "x capacity and size : " << x.capacity() << "," << x.size()
            << "\n";
  system("leaks mine.out");
  // ft::vector<int, std::allocator<int> > h;
}