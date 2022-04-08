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
    ft::vector<int> my_cp_v(my_v);
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
    for (int i = 0; i < 420; i++) my_v.push_back(-4242);
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
    for (int i = 0; i < 420; i++) my_v.push_back(-4242);
    print_vector(my_v.begin(), my_v.end());
    print_vector(my_v);
  }
}

void perfomance_test() {
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
  std::cout << "ft is faster than std? :" << (taken < taken2) << "\n";
}

class alloc_ed {
 private:
  int *a;

 public:
  alloc_ed() : a(new int[24]()) {
    std::cout << "constructer called\n";
    for (int i = 0; i < 24; i++) a[i] = i * 2;
  }
  ~alloc_ed() {
    std::cout << "destructor called\n";
    delete[] a;
  }
};

void erase_test() {
  {
    std::cout << "std vector erase test\n";
    std::vector<int> v(10, 10);
    v[5] = 421;
    v.push_back(42);
    std::cout << "erase from end -> seg fault\n";
    std::vector<int>::iterator it = v.begin();
    std::cout << "befre erase: capacity :" << v.capacity() << "\n";
    v.erase(v.begin() + 5);
    std::cout << "after erase: capacity :" << v.capacity() << "\n";
    std::cout << "erased\n";
    print_vector(v.begin(), v.end());
  }

  {
    std::cout << "ft vector erase test\n";
    ft::vector<int> v(10, 10);
    v[5] = 421;
    v.push_back(42);
    std::cout << "erase from end -> seg fault\n";
    ft::vector<int>::iterator it = v.begin();
    std::cout << "befre erase: capacity :" << v.capacity() << "\n";
    v.erase(v.begin() + 5);
    std::cout << "after erase: capacity :" << v.capacity() << "\n";
    std::cout << "erased\n";
    print_vector(v.begin(), v.end());
  }

  {
    std::cout
        << "std vector alloc_ed class test\n";  // ????????? vector 가 터지네?
    std::vector<int> a;
    a.push_back(421);
    a.push_back(422);
    a.push_back(423);
    // a.pop_back();
    a.erase(a.begin() + 1);
    print_vector(a.begin(), a.end());
    // std::cout << "erase begin() + 5\n";
  }

  {
    std::cout << "ft vector alloc_ed class test\n";
    ft::vector<int> a;
    std::cout << "push_back\n";
    a.push_back(421);
    a.push_back(422);
    a.push_back(423);
    // a.pop_back();
    std::cout << "erase\n";
    a.erase(a.begin() + 1);
    print_vector(a.begin(), a.end());
  }
  {
    std::cout << "std vector range erase test\n";
    std::string a[10] = {"a", "b", "c", "d", "e", "f"};
    std::vector<std::string> v(a, a + 5);
    print_vector(v.begin(), v.end());
    print_vector(v);
    v.erase(v.begin() + 1, v.end() - 2);
    print_vector(v.begin(), v.end());
    print_vector(v);
  }
  {
    std::cout << "std vector range erase test\n";
    std::string a[10] = {"a", "b", "c", "d", "e", "f"};
    ft::vector<std::string> v(a, a + 5);
    print_vector(v.begin(), v.end());
    print_vector(v);
    v.erase(v.begin() + 1, v.end());
    print_vector(v.begin(), v.end());
    print_vector(v);
  }
}

void insert_test() {
  {
    typedef std::vector<int>::iterator iterator;
    std::cout << "std vector insert()\n";
    std::vector<int> a(10, 10);
    iterator it = a.begin() + 1;
    iterator it_insert = a.insert(it + 5, 42);
    std::cout << "insert ret location is: "
              << std::distance(a.begin(), it_insert) << "\n";
    print_vector(a.begin(), a.end());
    int arr[] = {4242, 4241, 4240, 420, 424242};
    a.insert(a.end(), arr, arr + 5);
    print_vector(a.begin(), a.end());
  }

  {
    typedef ft::vector<int>::iterator iterator;
    std::cout << "ft vector insert()\n";
    ft::vector<int> a(10, 10);
    iterator it = a.begin() + 1;
    iterator it_insert = a.insert(it + 5, 42);
    std::cout << "insert ret location is: "
              << std::distance(a.begin(), it_insert) << "\n";
    print_vector(a.begin(), a.end());
    int arr[] = {4242, 4241, 4240, 420, 424242};
    a.insert(a.end(), arr, arr + 5);
    print_vector(a.begin(), a.end());
  }
}

void inputiterator_test() {
  std::iterator<std::input_iterator_tag, int> a;
  std::vector<int> b(10, 10);
  ft::vector<int> c(b.begin(), b.end());
}

int main(int argc, char **argv) {
  std::cout << std::boolalpha;
  std::cout << "===== stl_vec_test() =====\n";
  stl_vec_test();
  std::cout << "===== my_vec_test() =====\n";
  my_vec_test();
  std::cout << "===== stl_method_test() =====\n";
  stl_method_test();
  perfomance_test();
  erase_test();
  insert_test();
  inputiterator_test();

  (void)argc;
  std::string leak = std::string("leaks ") + &argv[0][2];
  system(leak.c_str());
  // int empty = a.front(); -> SEG_FAULT
  // ft::vector<int, std::allocator<int> > h;
}
