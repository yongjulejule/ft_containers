#include "type_traits.hpp"

#include <deque>
#include <iostream>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <vector>

// 1번 후보
template <typename Iter>
typename Iter::value_type mean(Iter first, Iter last) {
  std::cout << "first candidate\n";
  return *first;
}

// 2번 후보
template <typename T>
T mean(T* first, T* last) {
  std::cout << "second candidate\n";
  return *first;
}

double mean(float a, char* b) { return 1.0; }

void f(std::vector<int>& v, int* p, int n) {
  int x = mean(v.begin(), v.end());  // OK
  std::cout << x << "\n";
  int a = mean(p, p + n);  // error -> int*::value_type 꼴이 되어서 에러 ->
                           // SFINAE에 의해 후보 2번을 찾아감
  std::cout << a << "\n";
}

template <typename T>
T* allocate(size_t size) throw(int) {
  throw 1;
  return new T[size];
}

void sifae_test() {
  std::vector<int> v(10, 10);
  v.push_back(1);
  int* p = new int[10];
  std::uninitialized_fill(p, p + 10, 42);
  int n = 5;
  f(v, p, n);
  try {
    int* throwing = allocate<int>(ULLONG_MAX);
  } catch (int n) {
    std::cout << n << "\n";
  } catch (...) {
    std::cout << "thrown\n";
  }
}

void integral_constant_test() {
  /**
   * @details This block does not work because variable a evaluate in run-time
   * int a = 10;
   * typedef std::integral_constant<int, a> std_two_t;
   * typedef ft::integral_constant<int, a> ft_two_t;
   **/
  const size_t a = -1;
  typedef std::integral_constant<size_t, a> std_two_t;
  typedef ft::integral_constant<size_t, a> ft_two_t;
  if (ft_two_t::value == std_two_t::value)
    std::cout << "ft_two :" << ft_two_t() << "\n";
  else {
    std::cout << "ft_two :" << ft_two_t() << "\n";
    std::cout << "std_two :" << std_two_t() << "\n";
  }
  std::cout << std::boolalpha << ft::true_type() << "\n";
  std::cout << std::boolalpha << std::true_type() << "\n";
}
template <int N>
struct Factorial {
  static const int result = N * Factorial<N - 1>::result;
};

template <>
struct Factorial<1> {
  static const int result = 1;
};

void calculate_based_type_eg() {
  typedef Factorial<10> ten;
  std::cout << "Factorial :" << ten::result << "\n";
};

template <typename T>
void print_integral_test(T v) {
  std::cout << "current type is :" << typeid(v).name() << "\n";
  std::cout << "std::is_integral :" << std::is_integral<T>() << "\n";
  std::cout << "ft::is_integral :" << ft::is_integral<T>() << "\n";
}

void is_integral_test() {
  print_integral_test(true);
  {
    signed char a = 'a';
    print_integral_test(a);
  }
  {
    char a = 'a';
    print_integral_test(a);
  }
  {
    unsigned char a = 'a';
    print_integral_test(a);
  }
  {
    short a = 'a';
    print_integral_test(a);
  }
  {
    unsigned short a = 'a';
    print_integral_test(a);
  }
  {
    int a = 'a';
    print_integral_test(a);
  }
  {
    unsigned int a = 'a';
    print_integral_test(a);
  }
  {
    long a = 'a';
    print_integral_test(a);
  }
  {
    unsigned long a = 'a';
    print_integral_test(a);
  }
  {
    long long a = 'a';
    print_integral_test(a);
  }
  {
    unsigned long long a = 'a';
    print_integral_test(a);
  }
  {
    std::string a = "abc";
    print_integral_test(a);
  }
  print_integral_test(1.0f);
  print_integral_test(1.0);
  std::vector<int> test(10, 10);
  print_integral_test(test);
}

void is_same_test() {
  std::cout << ft::is_same<int, double>::value << ", "
            << std::is_same<int, double>::value << "\n";
  std::cout << ft::is_same<unsigned int, u_int32_t>::value << ", "
            << std::is_same<unsigned int, u_int32_t>::value << "\n";
  std::cout << ft::is_same<std::vector<int>, std::vector<int> >::value << ", "
            << std::is_same<std::vector<int>, std::vector<int> >::value << "\n";
  std::cout << ft::is_same<std::vector<int>, std::deque<int> >::value << ", "
            << std::is_same<std::vector<int>, std::deque<int> >::value << "\n";
  std::cout << ft::is_same<std::vector<double>, std::vector<int> >::value
            << ", "
            << std::is_same<std::vector<double>, std::vector<int> >::value
            << "\n";
}

int main() {
  std::cout << "===== SIFAE_TEST ===== \n";
  sifae_test();
  std::cout << "===== calculate_based_type_example ===== \n";
  calculate_based_type_eg();
  std::cout << "===== integral_constant_test ===== \n";
  integral_constant_test();
  std::cout << "===== is_integral_test ===== \n";
  is_integral_test();
  std::cout << "===== is_same_test ===== \n";
  is_same_test();
}