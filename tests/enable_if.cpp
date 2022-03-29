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

int main() {
  std::vector<int> v(10, 10);
  v.push_back(1);
  int* p = new int[10];
  std::uninitialized_fill(p, p + 10, 42);
  int n = 5;
  f(v, p, n);
}