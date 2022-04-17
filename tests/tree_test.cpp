#include "__tree.hpp"
#include "test.hpp"

int main(int argc, char **argv) {
  typedef ft::pair<int, std::string> _Val;
  ft::pair<int, std::string> test[argc];
  for (int i = 0; i < argc; ++i) {
    test[i] = ft::make_pair(i, std::string(argv[i]));
  }
  {
    // ft::__tree<int, ft::pair<int, std::string>,
    //            ft::select_first<ft::pair<int, std::string> >, std::less<int>,
    //            std::allocator<ft::pair<const int, std::string> > >
    //     tree;
  }
  ft::__tree_iterator<ft::pair<int, std::string> > a;
  *a = 4242;
  std::cout << *a << "\n";
  // std::cout << typeid(*a).name();
  {
    ft::__tree_node_base *basis = new ft::__tree_node_base[10];
    for (int i = 0; i < 10; i++) {
      if (i & 1)
        basis[i].__color_ = ft::BLACK;
      else
        basis[i].__color_ = ft::RED;
      std::cout << basis[i].__color_ << "\n";
    }
  }
  {
    ft::__tree_node<int> *test = new ft::__tree_node<int>();
    int *val_ptr = test->__valptr();
    *val_ptr = 42;
    // std::cout << &test.__value_field << "\n";
    std::cout << test->__valptr() << "\n";
    std::cout << test->__value_field << "\n";
  }

  {
    // typedef std::allocator<_Val>::rebind<ft::__tree_node<_Val> >::other
    //     _Node_alloc;
    // ft::__tree_node<_Val> *p = _Node_alloc().allocate(10);
    // std::uninitialized_fill(p, p + 10, 0);
    // _Node_alloc().destroy(p);
    // _Node_alloc().deallocate(p, 10);
  }

  // tree.__insert_range(test, test + argc);
}
