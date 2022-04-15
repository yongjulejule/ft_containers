#include <algorithm>
#include <iostream>
#include <vector>

struct Add {
  Add(int toAdd) : _toAdd(toAdd) {}
  int operator()(int x) { return x + _toAdd; }

 private:
  int _toAdd;
};

template <typename pair>
struct select_first {
  typename pair::first_type& operator()(pair& __x) const { return __x.first; }
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

  std::pair<int, std::string> pr(1, "abc");
  std::cout << "[" << pr.first << "] [" << pr.second << "]\n";
  std::cout << select_first<std::pair<int, std::string> >()(pr) << "\n";
  // std::cout << select_first<int>()(pr) << "\n";
}