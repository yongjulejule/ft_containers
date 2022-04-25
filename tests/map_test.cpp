#include "test.hpp"

struct print {
  template <typename T>
  void operator()(T val) {
    std::cout << "key: " << val.first << ", value: " << val.second << "\n";
  }
};

void max_size_test() {
  ft::map<int, ft::vector<int> > my_map;
  size_t map_max = my_map.max_size();
  std::cout << "ft max_size: " << map_max << "\n";
  try {
    // for (size_t i = 0; i < map_max; ++i) {
    //   my_map.insert(ft::make_pair(i, i));
    // }
    my_map.get_allocator().allocate(map_max - 1);
  } catch (std::exception &e) {
    std::cout << "exception occur" << e.what() << "\n";
  }

  std::map<int, ft::vector<int> > std_map;
  size_t std_map_max = std_map.max_size();
  std::cout << "STD max_size: " << std_map_max << "\n";
  try {
    std_map.get_allocator().allocate(std_map_max / 2);
  } catch (std::exception &e) {
    std::cout << "exception occur" << e.what() << "\n";
  }
  std::cout << ft::set<int>().max_size() << "\n";
  std::cout << std::set<int>().max_size() << "\n";
}

void map_test(int argc, char **argv) {
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
  std::cout << sizeof(my_map) << "," << sizeof(std_map) << "\n";
  std::cout << sizeof(ft::__tree<int, int, ft::select_first<int> >) << "\n";
  std::cout << sizeof(std::__tree<int, std::less<int>, std::allocator<int> >)
            << "\n";
  ft::__tree_key_compare<std::less<int> > key_cmp;
  std::cout << "key comp : " << sizeof(key_cmp.__key_comp) << "\n";
}

template <typename T>
void print_iter(T it, T ite) {
  for (; it != ite; ++it) print()(*it);
}

void compare_test(int argc, char **argv) {
  std::cout << std::boolalpha;
  ft::map<int, std::string> a;
  ft::map<int, std::string> b;
  ft::pair<int, std::string> pr;
  for (int i = 0; i < argc; ++i) {
    pr = ft::make_pair(i, argv[i]);
    if (i != argc - 1) {
      b.insert(pr);
    }
    a.insert(pr);
  }
  PRINT("map a");
  print_iter(a.begin(), a.end());
  PRINT("map b");
  print_iter(b.begin(), b.end());
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  b.insert(pr);
  PRINT("map a");
  print_iter(a.begin(), a.end());
  PRINT("map b");
  print_iter(b.begin(), b.end());
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  b.erase(pr.first);
  PRINT("map a");
  print_iter(a.begin(), a.end());
  PRINT("map b");
  print_iter(b.begin(), b.end());
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  ++pr.first;
  b.insert(pr);
  PRINT("map a");
  print_iter(a.begin(), a.end());
  PRINT("map b");
  print_iter(b.begin(), b.end());
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
}

int main(int argc, char **argv) {
  max_size_test();
  map_test(argc, argv);
  compare_test(argc, argv);
  sizeof(ft::__tree_node_base);
  system("leaks mine.out");
}