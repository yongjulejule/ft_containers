#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "test.hpp"

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

  bool test = ft::__is_input_iterator<
      ft::iterator<std::input_iterator_tag, int> >::value;
  // ft::__is_iterator<
  //     ft::iterator<std::input_iterator_tag, int> >::iterator_category a;

  // std::iterator_traits<int> aa;
  ft::iterator_traits<int *> bb;

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

void simple_test() {
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
  // ft::reverse_iterator<my_it> rit;
}

template <typename U>
static int __test(...) {
  std::cout << "!Q!! ... !!!\n";
  return 2;
}

template <typename U>
static char __test(
    typename ft::void_t<typename U::iterator_category>::type * = 0,
    typename ft::void_t<typename U::difference_type>::type * = 0,
    typename ft::void_t<typename U::value_type>::type * = 0,
    typename ft::void_t<typename U::pointer>::type * = 0,
    typename ft::void_t<typename U::reference>::type * = 0) {
  std::cout << "types!!!!!\n";
  return 1;
};

void iterable_test() {
  std::iterator<std::random_access_iterator_tag, float> f_it;
  // std::__has_iterator_category<
  //     ft::iterator<ft::input_iterator_tag, float> >::value;
  ft::iterator<std::input_iterator_tag, float> ft_f_it;
  std::cout << ft::__has_iterator_typedefs<
                   ft::iterator<std::input_iterator_tag, float> >::value
            << "\n";
  // std::__has_iterator_typedefs<
  //     ft::iterator<ft::input_iterator_tag, float> >::value;

  __test<ft::iterator<ft::input_iterator_tag, float> >(0, 0, 0, 0, 0);
  __test<int>(0, 0, 0, 0, 0);
  std::cout << sizeof(__test<ft::iterator<ft::input_iterator_tag, float> >(
                   0, 0, 0, 0, 0))
            << " <- test size\n";
  // ft::enable_if<f_it::iterator_catrgory>::type
  // ft::__iterator_traits<
  //     ft::iterator<std::input_iterator_tag, float>, >::difference_type a = 1;
}

int main() {
  std::cout << "==== simple_test =====\n";
  simple_test();
  std::cout << "==== iterable_test =====\n";
  iterable_test();
  std::cout << "==== check_iterator_category =====\n";
  check_iterator_category();

  {
    // ft::iterator_traits<ft::__tree_const_iterator<int> >::value_type a;
    // ft::__tree_const_iterator<int>::value_type a;
    // ft::__tree_const_iterator<int>::difference_type b;
    // ft::__tree_const_iterator<int>::iterator_catergory c;
    // ft::__tree_const_iterator<int>::pointer d;
    // ft::__tree_const_iterator<int>::reference f = 10;
    // std::cout << typeid(a).name() << ", " << typeid(b).name() << ", "
    //           << typeid(c).name() << ", " << typeid(d).name() << ", "
    //           << typeid(f).name() << ", \n";
  }
  __test<ft::vector<int>::iterator>(0, 0, 0, 0, 0);
  __test<ft::__tree_const_iterator<int> >(0, 0, 0, 0, 0);
  __test<ft::iterator_traits<ft::__tree_const_iterator<int> > >(0, 0, 0, 0, 0);
  int arr[5] = {1, 2, 5, 4, 3};
  ft::pair<int, int> b[5];
  std::pair<int, int> c[5];
  for (int i = 0; i < 5; i++) {
    b[i] = ft::make_pair(arr[i], arr[i]);
    c[i] = std::make_pair(arr[i], arr[i]);
  }
  ft::map<int, int> mp(b, b + 5);
  std::map<int, int> smp(c, c + 5);
  ft::map<int, int>::iterator it = mp.begin();
  std::map<int, int>::iterator sit = smp.begin();
  // ft::map<int, int>::const_iterator cit = mp.begin();
  // std::map<int, int>::const_iterator scit = smp.begin();
  // *sit = std::make_pair(42, 42);
  // *it = ft::make_pair(42, 42);
  __test<ft::map<int, int>::const_iterator>(0, 0, 0, 0, 0);
  __test<ft::map<int, int>::const_reverse_iterator>(0, 0, 0, 0, 0);
  __test<ft::map<int, int>::reverse_iterator>(0, 0, 0, 0, 0);
  ft::map<int, int>::reverse_iterator rit(it);
  ft::map<int, int>::const_reverse_iterator crit(rit);
  // ft::map<int, int>::const_reverse_iterator crit_2(cit);
  // ft::iterator_traits<ft::__tree_const_iterator<int> >::value_type val;

  // std::cout << rit[5];
}