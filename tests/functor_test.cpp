#include <algorithm>
#include <iostream>
#include <vector>

struct Add {
  Add(int toAdd) : _toAdd(toAdd) {}
  int operator()(int x) { return x + _toAdd; }

 private:
  int _toAdd;
};

int main() {
  Add add_42(42);
  Add add_13(13);
  int result_42 = add_42(2);
  int result_13 = add_13(2);
  std::vector<int> v(10, 10);
  std::transform(v.begin(), v.end(), v.begin(), add_42);
  std::vector<int>::iterator it = v.begin();
  std::vector<int>::iterator ite = v.end();
  for (; it != ite; ++it) std::cout << "[" << *it << "]";
  std::cout << "\n";
}