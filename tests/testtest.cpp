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

int main() {
  Parent p;
  Child c;

  Child *cc = new Parent;

  p.printA();
  c.printA();
}
