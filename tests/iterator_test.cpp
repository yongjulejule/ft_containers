#include "iterator.hpp"

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

template <typename tag>
struct my {
  static const bool input = ft::__is_input_iterator<tag>::value;
  static const bool output = ft::__is_output_iterator<tag>::value;
  static const bool fwd = ft::__is_forward_iterator<tag>::value;
  static const bool bidi = ft::__is_bidirectional_iterator<tag>::value;
  static const bool rd = ft::__is_random_access_iterator<tag>::value;
};

template <typename tag>
std::ostream &operator<<(std::ostream &os, my<tag> in) {
  os << "input:" << in.input << ", output :" << in.output
     << ", forward :" << in.fwd << ", bidirectional :" << in.bidi
     << ", random access :" << in.rd;
  return os;
}

template <typename tag>
struct lib {
  static const bool input = std::__is_cpp17_input_iterator<tag>::value;
  static const bool fwd = std::__is_cpp17_forward_iterator<tag>::value;
  static const bool bidi = std::__is_cpp17_bidirectional_iterator<tag>::value;
  static const bool rd = std::__is_cpp17_random_access_iterator<tag>::value;
};

template <typename tag>
std::ostream &operator<<(std::ostream &os, lib<tag> in) {
  os << "input:" << in.input << ", output :"
     << "N / A"
     << ", forward :" << in.fwd << ", bidirectional :" << in.bidi
     << ", random access :" << in.rd;
  return os;
}

void check_iterator_category() {
  my<ft::iterator<ft::input_iterator_tag, int> > my_in_tag;
  lib<std::iterator<std::input_iterator_tag, int> > lib_in_tag;
  my<ft::iterator<ft::output_iterator_tag, int> > my_out_tag;
  lib<std::iterator<std::output_iterator_tag, int> > lib_out_tag;
  my<ft::iterator<ft::forward_iterator_tag, int> > my_fwd_tag;
  lib<std::iterator<std::forward_iterator_tag, int> > lib_fwd_tag;
  my<ft::iterator<ft::bidirectional_iterator_tag, int> > my_bidi_tag;
  lib<std::iterator<std::bidirectional_iterator_tag, int> > lib_bidi_tag;
  my<ft::iterator<ft::random_access_iterator_tag, int> > my_rd_tag;
  lib<std::iterator<std::random_access_iterator_tag, int> > lib_rd_tag;

  std::cout << "====== input =====\n";
  std::cout << "My  ret -> " << my_in_tag << "\n";
  std::cout << "lib ret -> " << lib_in_tag << "\n";

  std::cout << "====== output =====\n";
  std::cout << "My  ret -> " << my_out_tag << "\n";
  std::cout << "lib ret -> " << lib_out_tag << "\n";

  std::cout << "====== forward =====\n";
  std::cout << "My  ret -> " << my_fwd_tag << "\n";
  std::cout << "lib ret -> " << lib_fwd_tag << "\n";

  std::cout << "====== bidirectional =====\n";
  std::cout << "My  ret -> " << my_bidi_tag << "\n";
  std::cout << "lib ret -> " << lib_bidi_tag << "\n";

  std::cout << "====== random_access =====\n";
  std::cout << "My  ret -> " << my_rd_tag << "\n";
  std::cout << "lib ret -> " << lib_rd_tag << "\n";
}

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
  typedef ft::iterator<ft::input_iterator_tag, int> my_it;
  ft::reverse_iterator<my_it> rit;
  check_iterator_category();
  // std::cout << rit[5];
}