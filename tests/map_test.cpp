#include "test.hpp"

struct print {
  template <typename T>
  void operator()(T val) {
    std::cout << "key: " << val.first << ", value: " << val.second << "\n";
  }
};

int main(int argc, char **argv) {
  ft::map<char, int> my_map;
  std::map<char, int> std_map;
  for (int i = 0; argv[0][i]; ++i) {
    my_map.insert(ft::make_pair(argv[0][i], i));
    std_map.insert(std::make_pair(argv[0][i], i));
  }
  std::cout << (my_map.find('/'))->second << "\n";
  ft::map<char, int>::iterator it = my_map.begin();
  ft::map<char, int>::iterator ite = my_map.end();
  std::for_each(it, ite, print());
  std::for_each(std_map.begin(), std_map.end(), print());
  std::cout << my_map.size() << ", " << my_map.max_size() << "\n";
  std::cout << my_map.max_size() << ", " << std_map.max_size() << "\n";
}