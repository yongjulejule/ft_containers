#include <sys/errno.h>

#include <cstdlib>
#include <iostream>

class thrw {
 private:
  int *x;

 public:
  thrw() {
    std::cout << "constructor\n";
    x = new int(42);
    throw std::bad_alloc();
  }
  int get_x() { return *x; }
  ~thrw() {
    delete x;
    std::cout << "distructor\n";
  }
};

void raii_test() {
  try {
    thrw a;
    std::cout << a.get_x() << "\n";
  } catch (std::exception &e) {
    std::cout << e.what() << "\ncatch!\n";
  }
}

int main() {
  raii_test();
  system("leaks a.out");
}