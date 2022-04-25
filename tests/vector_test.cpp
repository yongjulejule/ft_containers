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

#include <fstream>

#include "test.hpp"

template <typename T>
void print_vector(T it, T ite) {
  while (it != ite) {
    std::cout << *it << ", ";
    ++it;
    if (it == ite) std::cout << "\n";
  }
}

template <typename vec>
void print_vector(vec &v) {
  PRINT("vector info (size, capacity) : (", v.size(), ", ", v.capacity(), ")");
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

void performance_test() {
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
    std::cout << "before erase: capacity :" << v.capacity() << "\n";
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
    std::cout << "before erase: capacity :" << v.capacity() << "\n";
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
    std::cout << "ft vector range erase test\n";
    std::string a[10] = {"a", "b", "c", "d", "e", "f", "g"};
    ft::vector<std::string> v(a, a + 7);
    print_vector(v.begin(), v.end());
    print_vector(v);
    v.erase(v.begin(), v.begin() + 3);
    print_vector(v.begin(), v.end());
    print_vector(v);
  }
}

void insert_test() {
  {
    typedef std::vector<int>::iterator iterator;
    PRINT("std vector insert()");
    std::vector<int> a(10, 10);
    iterator it = a.begin() + 1;
    iterator it_insert = a.insert(it + 5, 10, 42);
    std::cout << "insert ret location is: "
              << std::distance(a.begin(), it_insert) << "\n";
    print_vector(a.begin(), a.end());
    print_vector(a);
    int arr[] = {4242, 4241, 4240, 420, 424242};
    a.insert(a.end(), arr, arr + 5);
    print_vector(a.begin(), a.end());
    print_vector(a);
  }

  {
    typedef ft::vector<int>::iterator iterator;
    PRINT("ft vector insert()");
    ft::vector<int> a(10, 10);
    // a.insert(a.begin() + 2, a.begin(), a.end());
    print_vector(a.begin(), a.end());
    a.insert(a.end(), 424242);
    print_vector(a.begin(), a.end());
    print_vector(a);
    a.insert(a.begin(), 42424211);
    print_vector(a.begin(), a.end());
    print_vector(a);
    a.insert(a.begin() + 2, 424211);
    print_vector(a.begin(), a.end());
    print_vector(a);
    a.insert(a.begin(), 2, 212121);
    print_vector(a.begin(), a.end());
    print_vector(a);
    a.insert(a.end() - 2, 4242);
    print_vector(a.begin(), a.end());
    print_vector(a);
    a.insert(a.end(), 2, 8484);
    print_vector(a.begin(), a.end());
    print_vector(a);

    a.insert(a.begin() + 2, a.begin(), a.end());
    print_vector(a.begin(), a.end());
    print_vector(a);
    int arr[] = {4242, 4241, 4240, 420, 424242};
    a.insert(a.end(), arr, arr + 5);
    print_vector(a.begin(), a.end());
    print_vector(a);

    ft::vector<int> v2(5, 42);
    a.insert(a.begin() + 2, v2.begin(), v2.end());
    print_vector(a.begin(), a.end());
  }
}

void vector_construct_test() {
  {
    PRINT("ft::vector<int> v(3);");
    ft::vector<int> v(3);
    print_vector(v.begin(), v.end());
    print_vector(v);
  }

  {
    PRINT("ft::vector<int> v(3, 42);");
    ft::vector<int> v(3, 42);
    print_vector(v.begin(), v.end());
    print_vector(v);
  }

  {
    int arr[] = {42, 43, 44, 45};
    PRINT("ft::vector<int> v(arr, arr + 4);");
    ft::vector<int> v(arr, arr + 4);
    print_vector(v.begin(), v.end());
    print_vector(v);

    PRINT("ft::vector<int> v_cp(v);");
    ft::vector<int> v_cp(v);
    print_vector(v_cp.begin(), v_cp.end());
    print_vector(v_cp);
    PRINT("copied memory :", &(*v_cp.begin()), "\n",
          "origin memory :", &(*v.begin()));
  }

  {
    PRINT(
        "ft::vector<char> v((std::istreambuf_iterator<char>(source)), "
        "std::istreambuf_iterator<char>()) ");
    std::ifstream source("Makefile", std::ios::binary);
    ft::vector<char> v((std::istreambuf_iterator<char>(source)),
                       std::istreambuf_iterator<char>());
    print_vector(v.begin(), v.end());
    print_vector(v);
  }

  {
    ft::vector<char> v;
    std::ifstream source("Makefile", std::ios::binary);
    // v.assign(std::istreambuf_iterator<char>(source),
    //          std::istreambuf_iterator<char>());
    // print_vector(v.begin(), v.end());
    // print_vector(v);
  }
}

void swap_test() {
  ft::vector<std::string> x;
  x.push_back("this");
  x.push_back("is");
  x.push_back("x");
  PRINT("x");
  PRINT(&(*x.begin()), "\n", &(*x.end()), "\n");
  print_vector(x.begin(), x.end());
  print_vector(x);
  ft::vector<std::string> y;
  y.push_back("this");
  y.push_back("is");
  y.push_back("y");
  y.push_back("hahaha");
  PRINT("Y");
  PRINT(&(*y.begin()), "\n", &(*y.end()), "\n");
  print_vector(y.begin(), y.end());
  print_vector(y);
  x.swap(y);
  PRINT("x");
  PRINT(&(*x.begin()), "\n", &(*x.end()), "\n");
  print_vector(x.begin(), x.end());
  print_vector(x);
  PRINT("Y");
  PRINT(&(*y.begin()), "\n", &(*y.end()), "\n");
  print_vector(y.begin(), y.end());
  print_vector(y);
  ft::swap(x, y);
  PRINT("x");
  PRINT(&(*x.begin()), "\n", &(*x.end()), "\n");
  print_vector(x.begin(), x.end());
  print_vector(x);
  PRINT("Y");
  PRINT(&(*y.begin()), "\n", &(*y.end()), "\n");
  print_vector(y.begin(), y.end());
  print_vector(y);
  PRINT("assign operator test");
  x = y;
  PRINT("x");
  PRINT(&(*x.begin()), "\n", &(*x.end()), "\n");
  print_vector(x.begin(), x.end());
  print_vector(x);
  PRINT("Y");
  PRINT(&(*y.begin()), "\n", &(*y.end()), "\n");
  print_vector(y.begin(), y.end());
  print_vector(y);
}

void compare_test() {
  ft::vector<double> a(10, 4.2);
  ft::vector<double> b(9, 4.2);
  PRINT("vector a");
  print_vector(a.begin(), a.end());
  PRINT("vector b");
  print_vector(b.begin(), b.end());
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  b.push_back(4.2);
  PRINT("vector a");
  print_vector(a.begin(), a.end());
  PRINT("vector b");
  print_vector(b.begin(), b.end());
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  b.pop_back();
  PRINT("vector a");
  print_vector(a.begin(), a.end());
  PRINT("vector b");
  print_vector(b.begin(), b.end());
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  b.push_back(4.3);
  PRINT("vector a");
  print_vector(a.begin(), a.end());
  PRINT("vector b");
  print_vector(b.begin(), b.end());
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
}

int main(int argc, char **argv) {
  std::cout << std::boolalpha;
  PRINT("constructor test");
  vector_construct_test();
  std::cout << "===== stl_method_test() =====\n";
  stl_method_test();
  performance_test();
  erase_test();
  insert_test();
  swap_test();
  compare_test();

  // std::cout << std::distance(v.begin(), v.end()) << "\n";
  (void)argc;
  std::string leak = std::string("leaks ") + &argv[0][2];
  system(leak.c_str());
}
