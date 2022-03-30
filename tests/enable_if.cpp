#include <iostream>
#include <memory>
#include <vector>

template <typename Iter>
typename Iter::value_type mean(Iter first, Iter last) {
  return *first;
}

template <typename T>
T mean(T* first, T* last) {
  return *first;
}

void f(std::vector<int>& v, int* p, int n) {
  auto x = mean(v.begin(), v.end());  // OK
  std::cout << x << "\n";
  auto y = mean(p, p + n);  // error -> int*::value_type 꼴이 되어서 에러
  std::cout << y << "\n";
}

template <typename T>
T* allocate(size_t size) throw(int) {
  throw 1;
  return new T[size];
}
int f2(int n);

int f1(int n) {
  if (n == 42424) return n;
  return (f2(++n));
}

int f2(int n) {
  f1(++n);
  return n;
}

int f3() throw() { return (f1(0)); }

#include <sys/time.h>
void throw_test() {
  try {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    suseconds_t begin = tp.tv_usec;
    std::cout << tp.tv_sec << ":" << tp.tv_usec << "\n";
    n = f3();
    gettimeofday(&tp, NULL);
    suseconds_t end = tp.tv_usec;
    std::cout << tp.tv_sec << ":" << tp.tv_usec << "\n";
    std::cout << n;
    std::cout << "\nresult : " << end - begin << "\n";
  } catch (...) {
    std::cout << "don't print\n";
  }
}

int main() {
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
  throw_test()
}