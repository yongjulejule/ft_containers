#include "iterator.hpp"

#include <iostream>
#include <iterator>
#include <map>
#include <vector>
int main() {
  std::iterator<int, int, int, int *, int *> a;
  std::cout << typeid(a).name() << "\n";
  ft::iterator<int, int, int, int *, int *> b;
  std::cout << typeid(b).name() << "\n";
  std::vector<int> vtest(10, 10);
  std::vector<int>::iterator it = vtest.begin();
  std::cout << std::boolalpha
            << ft::is_same<std::vector<int>::pointer,
                           std::vector<int>::iterator>::value;
  std::vector<int>::pointer t1;
  std::vector<int>::iterator t2;
  std::cout << typeid(t1).name() << "\n" << typeid(t2).name() << "\n";
  typedef std::iterator<std::forward_iterator_tag, int> my_it;
  std::reverse_iterator<my_it> rit;
  // std::cout << rit[5];
}