#include <sys/errno.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

class thrw {
 protected:
  int *x;

 public:
  thrw() { std::cout << "constructor\n"; }
  void allocate_memory() {
    x = new int[42];
    throw std::bad_alloc();
  }
  int get_x() { return *x; }
  ~thrw() {
    delete x;
    std::cout << "destructor\n";
  }
};

class thrw_child : public thrw {
 public:
  thrw_child() : thrw() {
    allocate_memory();
    std::cout << "thrw_child\n";
  }
  ~thrw_child() { std::cout << "thrw_child destructor\n"; }
};

void raii_test() {
  try {
    thrw a;
    std::cout << "a constructed...\n";
    a.allocate_memory();
    std::cout << a.get_x() << "\n";
  } catch (std::exception &e) {
    std::cout << e.what() << "\ncatch! in raii_test\n";
  }
}

void f1() {
  thrw_child a;
  std::cout << a.get_x() << "\n";
}

void raii_child_test() {
  try {
    f1();
  } catch (...) {
    std::cout << "catch f1\n";
  }
}

int main() {
  try {
    raii_test();
  } catch (std::exception &e) {
    std::cout << e.what() << "in Main RAII TEST CATCH\n";
  }
  try {
    raii_child_test();
  } catch (std::exception &e) {
    std::cout << e.what() << "in Main F1 TEST CATCH\n";
  }
  std::vector<int> alloc;
  size_t size = alloc.get_allocator().max_size();
  std::cout << size << "<- size\n";
  std::vector<int> v(size / 10, 42);
  v.push_back(10);
  std::cout << *(v.end() - 1);
  system("leaks mine.out");
}