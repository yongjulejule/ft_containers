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

#include <sys/time.h>

#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

#include "iterator.hpp"

template <typename T>
void print_vector(T it, T ite) {
  while (it != ite) {
    std::cout << *it << ", ";
    ++it;
    if (it == ite) std::cout << "\n";
  }
}

template <typename vec>
void print_vector(vec v) {
  std::cout << "vector info (size, capacity) : (" << v.size() << ", "
            << v.capacity() << ")\n";
}

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

void stl_method_test() {
  typedef std::vector<int>::iterator iterator;

  {
    std::cout << "swap()\n";
    std::vector<int> x(10, 10);
    std::vector<int>().swap(x);  // ??????????? 이런걸 왜하지?
    std::cout << "x capacity and size : " << x.capacity() << "," << x.size()
              << "\n";
  }

  {
    std::cout << "insert()\n";
    std::vector<int> a(10, 10);
    iterator it = a.begin() + 1;
    iterator it_insert = a.insert(it + 5, 42);
    std::cout << "insert ret location is: "
              << std::distance(a.begin(), it_insert) << "\n";
    iterator itb = a.begin();
    for (; itb != a.end(); itb++) std::cout << *itb << ",";
    std::cout << "\n";
    int arr[] = {4242, 4241, 4240, 420, 424242};
    a.insert(a.end(), arr, arr + 5);
    itb = a.begin();
    for (; itb != a.end(); itb++) std::cout << *itb << ",";
    std::cout << "\n";
    iterator it_erased = a.erase(a.end() - 4, a.end() - 1);
    std::cout << "*it_erased : " << *it_erased
              << "\n";  // end()의 위치이면, sanitize=address 걸면 터짐!
    std::cout << "distance(a.begin(), it_erased): "
              << std::distance(a.begin(), it_erased) << "\n";
    itb = a.begin();
    for (; itb != a.end(); itb++) std::cout << *itb << ",";
    std::cout << "\n";
  }
  {
    std::cout << "front and back test when empty\n";
    std::vector<int> a;
    std::cout << "vecot default capacity : " << a.capacity() << "\n";
    try {
      std::cout << a.at(0) << "\n";
    } catch (std::exception &e) {
      std::cout << "vector at :" << e.what() << "\n";
      std::cout << typeid(e).name() << "\n";
    }
    std::cout << "is empty? : " << a.empty() << "\n";
    // std::cout << "a (front, back) : (" << a.front() << ", " << a.back()
    //           << ")\n";
  }
}

void my_vec_method_test() {
  // typedef ft::vector<int>::iterator iterator;
  {
    std::cout << "push_back()\n";
    int arr[] = {4, 2, 42, 424, 242, 4242, 2424, 424242, 242424};
    ft::vector<int> my_v(arr, arr + (sizeof(arr) / sizeof(int)));
    print_vector(my_v.begin(), my_v.end());
    for (int i = 0; i < 42; i++) my_v.push_back(-4242);
    print_vector(my_v.begin(), my_v.end());
    print_vector(my_v);
  }
}

void std_vec_method_test() {
  // typedef ft::vector<int>::iterator iterator;
  {
    std::cout << "push_back()\n";
    int arr[] = {4, 2, 42, 424, 242, 4242, 2424, 424242, 242424};
    std::vector<int> my_v(arr, arr + (sizeof(arr) / sizeof(int)));
    print_vector(my_v.begin(), my_v.end());
    for (int i = 0; i < 42; i++) my_v.push_back(-4242);
    print_vector(my_v.begin(), my_v.end());
    print_vector(my_v);
  }
}

int main(void) {
  std::cout << std::boolalpha;
  std::cout << "===== stl_vec_test() =====\n";
  stl_vec_test();
  std::cout << "===== my_vec_test() =====\n";
  my_vec_test();
  std::cout << "===== stl_method_test() =====\n";
  stl_method_test();
  struct timeval tv;
  std::cout << "===== my_vec_method_test() =====\n";
  gettimeofday(&tv, NULL);
  suseconds_t beg = tv.tv_usec;
  my_vec_method_test();
  gettimeofday(&tv, NULL);
  suseconds_t taken = tv.tv_usec - beg;
  std::cout << "===== std_vec_method_test() =====\n";
  gettimeofday(&tv, NULL);
  suseconds_t beg2 = tv.tv_usec;
  std_vec_method_test();
  gettimeofday(&tv, NULL);
  suseconds_t taken2 = tv.tv_usec - beg2;

  std::cout << "ft::vector : <" << taken << "> std::vector : <" << taken2
            << ">\n";
  std::cout << (taken < taken2);

  // system("leaks mine.out");
  // ft::vector<int, std::allocator<int> > h;
}