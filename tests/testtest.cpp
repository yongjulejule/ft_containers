#include <iostream>
#include <string>

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

unsigned test() { return 3489589589132ULL; }

int main() {
  Parent p;
  Child c;

  // Child *cc = new Parent;
  unsigned a = test();
  std::cout << a << "\n";
  std::cout << typeid(unsigned).name() << "," << typeid(unsigned int).name()
            << "\n";

  p.printA();
  c.printA();
}
