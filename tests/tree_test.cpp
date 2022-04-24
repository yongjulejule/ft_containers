
#include "__tree.hpp"
#include "test.hpp"

#define R "\033[31m";
#define B "\033[32m";
#define RESET "\033[0m"

typedef ft::__tree<
    int, ft::pair<int, std::string>,
    ft::select_first<ft::pair<int, std::string> >, std::less<int>,
    std::allocator<ft::pair<int, std::string> > >::iterator iterator;
typedef ft::__tree<int, ft::pair<int, std::string>,
                   ft::select_first<ft::pair<int, std::string> >,
                   std::less<int>, std::allocator<ft::pair<int, std::string> > >
    my_tree;
typedef ft::__tree<int, int, ft::identity<int>, std::less<int>,
                   std::allocator<int> >
    int_tree;

int_tree tree_int;

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void ft::__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::print_tree() {
  print_tree("", __begin(), false);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void ft::__tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::print_tree(
    const std::string &prefix, _Link_type x, bool isLeft) {
  if (x != NULL) {
    std::cout << prefix;
    std::cout << (isLeft ? "L├──" : "R└──");
    if (x->__color_ == RED) {
      std::cout << R std::cout << __S_key(x) << RESET << "\n";
    } else {
      std::cout << B std::cout << __S_key(x) << RESET << "\n";
    }
    print_tree(prefix + (isLeft ? " │   " : "     "),
               static_cast<_Link_type>(x->__left_), true);
    print_tree(prefix + (isLeft ? " │   " : "     "),
               static_cast<_Link_type>(x->__right_), false);
  }
}

int generateRandomNumber(std::pair<int, int> range) {
  static bool first = true;
  if (first) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    srand(tp.tv_usec);
    rand();
    first = false;
  }
  return ((static_cast<float>(rand())) / RAND_MAX) *
             (static_cast<long long>(range.second) - range.first + 1) +
         range.first;
}
int generateRandomNumber(int beg, int end) {
  static bool first = true;
  if (first) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    srand(tp.tv_usec);
    rand();
    first = false;
  }
  return ((static_cast<float>(rand())) / RAND_MAX) *
             (static_cast<long long>(end) - beg + 1) +
         first;
}

void tree_test(int argc, char **argv) {
  argc *= 10;
  typedef ft::pair<int, std::string> _Val;
  ft::pair<int, std::string> test[argc];
  for (int i = 0; i < argc; ++i) {
    test[i] = ft::make_pair(i, std::string(argv[0]));
    if (i == 10) test[i] = ft::make_pair(i, std::string("HI Im Val"));
  }
  {
    my_tree tree;
    tree.insert_range(test, test + argc);
    my_tree cptree(tree);
    my_tree atr;
    atr = tree;
    iterator it_test = tree.begin();
    iterator ite_test = tree.end();
    for (; it_test != ite_test; ++it_test) {
      std::cout << (*it_test).first << ", " << (*it_test).second << "\n";
    }
    std::cout << "\n";

    tree.print_tree();
    std::cout << "tree size is: " << tree.size() << "\n";
    std::cout << "delete random [" << argc / 3 << "] numbers of node\n";

    for (int i = 1; i < (argc / 2); i++) {
      int num = generateRandomNumber(std::make_pair(0, argc));
      std::cout << "Key to delete: " << num << "\n";
      tree.erase(num);
      tree.print_tree();
    }
    tree.print_tree();
    cptree.print_tree();
    atr.print_tree();
    for (int i = 0; i < argc; ++i) {
      test[i] =
          ft::make_pair(generateRandomNumber(std::make_pair(-10000, 10000)),
                        std::string(argv[0]));
      if (i == 10) test[i] = ft::make_pair(i, std::string("HI Im Val"));
    }
    tree.insert_range(test, test + argc);
    tree.print_tree();
    std::cout << "tree size is: " << tree.size() << "\n";
    iterator it = tree.find(10);
    if (it != tree.end()) std::cout << (*it).first << ":" << it->second << "\n";
    it = tree.find(9);
    if (it != tree.end()) std::cout << (*it).first << ":" << it->second << "\n";
  }
  {
    ft::__tree_node_base *basis = new ft::__tree_node_base[10];
    for (int i = 0; i < 10; i++) {
      if (i & 1)
        basis[i].__color_ = ft::BLACK;
      else
        basis[i].__color_ = ft::RED;
      // std::cout << basis[i].__color_ << "\n";
    }
    delete[] basis;
  }
  {
    ft::__tree_node<int> *test = new ft::__tree_node<int>();
    int *val_ptr = test->__valptr();
    *val_ptr = 42;
    // std::cout << &test.__value_field << "\n";
    // std::cout << test->__valptr() << "\n";
    // std::cout << test->__value_field << "\n";
    delete test;
  }

  {
    // typedef std::allocator<_Val>::rebind<ft::__tree_node<_Val> >::other
    //     _Node_alloc;
    // ft::__tree_node<_Val> *p = _Node_alloc().allocate(10);
    // std::uninitialized_fill(p, p + 10, 0);
    // _Node_alloc().destroy(p);
    // _Node_alloc().deallocate(p, 10);
  }

  // tree.insert_range(test, test + argc);
}

class why {
 private:
  int w;
  int h;
  int y;

 public:
  why() : w('w'), h('h'), y('y') {}
};

template <typename _T, typename _Val, typename _Alloc = std::allocator<_T> >
class AllocRebind {
  typedef typename _Alloc::template rebind<_Val>::other Node_Alloc;

  struct impl : public Node_Alloc, public why {
    impl() : Node_Alloc() {}
  };

 public:
  impl _impl;
  AllocRebind() : _impl() {}
  Node_Alloc &get_node_alloc() { return this->_impl; }
};

void alloc_test() {
  typedef ft::pair<int, std::string> value;
  AllocRebind<int, value> a;
  std::allocator<value> no = a.get_node_alloc();
  value *pr = no.allocate(1);
  no.construct(pr, value(42, "42"));
  // std::cout << typeid(no).name() << "\n";
  no.deallocate(pr, 1);
}

class static_test {
 public:
  static int S_increment() {
    int a = 0;
    for (int i = 0; i < 100000; i++) {
      if (i & 1)
        a++;
      else
        a -= 2;
    }
    return a;
  }
  int increment() {
    int a = 0;
    for (int i = 0; i < 100000; i++) {
      if (i & 1)
        a++;
      else
        a -= 2;
    }
    return a;
  }
};

void benchmark_static() {
  timeval tp;
  suseconds_t tm1, tm2, gap1, gap2;

  gettimeofday(&tp, NULL);
  tm1 = tp.tv_usec;
  int b = static_test::S_increment();
  // int c = static_test().increment();
  gettimeofday(&tp, NULL);
  gap1 = tp.tv_usec - tm1;

  gettimeofday(&tp, NULL);
  tm2 = tp.tv_usec;
  int c = static_test().increment();
  gettimeofday(&tp, NULL);
  gap2 = tp.tv_usec - tm2;

  std::cout << "static gap: " << gap1 << "\n"
            << "non-static gap: " << gap2 << "\n";
}

#define GEN_NUM 100
int main(int argc, char **argv) {
  // tree_test(argc, argv);
  // alloc_test();
  // benchmark_static();
  ft::vector<int> numbers;
  for (int i = 0; i < GEN_NUM; ++i)
    numbers.push_back(generateRandomNumber(std::make_pair(0, GEN_NUM * 3)));
  // int_tree tree_int;
  tree_int.insert_range(numbers.begin(), numbers.end());
  tree_int.print_tree();
  for (int j = 0; j < 5; ++j) {
    int i = generateRandomNumber(0, GEN_NUM - 1);
    std::cout << "to erase: " << numbers[i] << "\n";
    tree_int.erase(numbers[i]);
    tree_int.print_tree();
  }
  // tree_int.print_tree();
  // tree_int.print_tree();

  // int b = static_test::S_increment();
  // int c = static_test().increment();
  //
  // std::string leak = std::string("leaks ") + std::string(argv[0]);
  // system("leaks mine.out 1>/dev/null");
}
