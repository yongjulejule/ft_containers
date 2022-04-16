#include <iostream>
#include <string>

#include "utility.hpp"

class Parent {
 public:
  std::string a;
  Parent() { a = "a"; }
  void printA() { std::cout << a << "\n"; }
};
class Child : public Parent {
 public:
  Child() { a = "b"; }
};

class SwapTest {
 private:
  std::string str;

 public:
  SwapTest() : str("NULL") { std::cout << str << "SwapTest\n"; }
  SwapTest(std::string string) : str(string) {
    std::cout << str << "SwapTest\n";
  }
  SwapTest(const SwapTest& oth) : str(oth.str) {
    std::cout << str << "SwapTest copy constructor\n";
  }
  const SwapTest& operator=(const SwapTest& oth) {
    this->str = oth.str;
    std::cout << str << "Swap assign operator\n";
    return *this;
  }
  std::string& get() { return str; }
  ~SwapTest() { std::cout << str << "SwapTest Destroyed\n"; }
};

unsigned test() { return 3489589589132ULL; }

// const method test.
// call non-const to const function: ok
// call const to non-const function: no!!
template <typename T>
class ConstTest {
 private:
  int a;

 public:
  typedef T my;
  typedef const T cmy;
  ConstTest() : a(0) {}
  my& print(my& val) const {
    std::cout << "print with my :" << val << "\n";
    return val;
  }
  cmy& print(cmy& val) const {
    std::cout << "print with cmy :" << val << "\n";
    return val;
  }
};
int main() {
  Parent p;
  Child c;

  // Child *cc = new Parent;
  unsigned a = test();
  std::cout << a << "\n";
  std::cout << typeid(unsigned).name() << "," << typeid(unsigned int).name()
            << "\n";
  {
    const int a = 42;
    int b = 4242;
    ConstTest<int> test;
    test.print(a);
    test.print(b);
    int c = 55;
    std::swap(c, b);
  }
  {
    SwapTest a("hi im a");
    SwapTest b("hi im b");
    std::cout << "before swap:\naddress of a: " << &a
              << "\naddress of b: " << &b << "\n";
    ft::swap(a, b);
    std::cout << "after swap:\naddress of a: " << &a << "\naddress of b: " << &b
              << "\n";
    // std::swap(a, b);
    std::cout << "a: " << a.get() << "\nb: " << b.get() << "\n";
    std::cout << "===end swap ===\n";
  }

  p.printA();
  c.printA();
}
