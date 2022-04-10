#include "test.hpp"

int main(int argc, char **argv) {
  std::cout << std::boolalpha;
  ft::pair<int, std::string> pr[argc];
  for (int i = 0; i < argc; i++)
    pr[i] = ft::make_pair<int, std::string>(i, argv[i]);
  for (int i = 0; i < argc; i++) {
    PRINT("pair[", i, "] : (", pr[i].first, ", ", pr[i].second, ")");
  }
  ft::pair<int, std::string> a(pr[0]);
  ft::pair<int, std::string> b(pr[0]);
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  b = pr[1];
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
}