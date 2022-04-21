#include "test.hpp"
struct print {
  template <typename T>
  void operator()(T val) {
    std::cout << "key: " << val << "\n";
  }
};

void max_size_test() {
  ft::set<ft::vector<int> > my_set;
  size_t set_max = my_set.max_size();
  std::cout << "ft max_size: " << set_max << "\n";
  try {
    // for (size_t i = 0; i < set_max; ++i) {
    //   my_set.insert(ft::make_pair(i, i));
    // }
    my_set.get_allocator().allocate(set_max);
  } catch (std::exception &e) {
    std::cout << "exception occur" << e.what() << "\n";
  }

  std::set<ft::vector<int> > std_set;
  size_t std_set_max = std_set.max_size();
  std::cout << "STD max_size: " << std_set_max << "\n";
  try {
    std_set.get_allocator().allocate(std_set_max >> 32);
  } catch (std::exception &e) {
    std::cout << "exception occur" << e.what() << "\n";
  }
  {
    ft::set<int> my_int_set;
    std::set<int> std_int_set;
    for (int i = 0; i < 10000; i++) {
      my_int_set.insert(i);
      std_int_set.insert(i);
    }
    std::cout << my_int_set.max_size() << "\n";
    std::cout << std_int_set.max_size() << "\n";
    std::cout << ft::set<float>().max_size() << "\n";
    std::cout << std::set<float>().max_size() << "\n";
  }
}

void set_test(int argc, char **argv) {
  ft::set<std::string> my_set;
  std::set<std::string> std_set;
  for (int i = 0; i < argc; ++i) {
    my_set.insert(std::string(argv[i]));
    std_set.insert(std::string(argv[i]));
  }
  std::cout << *(my_set.find(argv[2])) << "\n";
  ft::set<std::string>::iterator it = my_set.begin();
  ft::set<std::string>::iterator ite = my_set.end();
  std::for_each(it, ite, print());
  std::for_each(std_set.begin(), std_set.end(), print());
  std::cout << my_set.size() << ", " << my_set.max_size() << "\n";
  std::cout << my_set.max_size() << ", " << std_set.max_size() << "\n";
  std::cout << sizeof(my_set) << "," << sizeof(std_set) << "\n";
  std::cout << sizeof(ft::__tree<int, int, ft::select_first<int> >) << "\n";
  std::cout << sizeof(std::__tree<int, std::less<int>, std::allocator<int> >)
            << "\n";
  ft::__tree_key_compare<std::less<int> > key_cmp;
  std::cout << "key comp : " << sizeof(key_cmp.__key_comp) << "\n";
}

int main(int argc, char **argv) {
  max_size_test();
  set_test(argc, argv);
  std::cout << std::numeric_limits<ptrdiff_t>().max() << "\n";
  std::cout << std::numeric_limits<size_t>().max() << "\n";
  std::cout << sizeof(std::__compressed_pair<size_t, std::allocator<int> >)
            << "\n";
  std::cout << sizeof(ft::pair<size_t, std::allocator<int> >) << "\n";
  std::cout << sizeof(std::pair<size_t, std::allocator<int> >) << "\n";
  std::cout << sizeof(std::__compressed_pair<int, double>) << "\n";
  std::cout << sizeof(ft::pair<int, double>) << "\n";
  std::cout << sizeof(std::pair<int, double>) << "\n";
  system("leaks mine.out");
}