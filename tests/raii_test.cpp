#include <sys/errno.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

class thrw {
 protected:
  int *x;
  size_t size;
  std::allocator<int> a;

 public:
  thrw() : x(NULL), size(424242), a(std::allocator<int>()) {
    std::cout << "thrw constructor\n";
    // leaks here !
    // allocate_memory();
  }
  void allocate_memory() {
    std::cout << "allocate_memory\n";
    for (;;) {
      x = a.allocate(size);
      if (size > (a.max_size() >> 32)) throw std::bad_alloc();
      a.deallocate(x, size);
      size *= 2;
    }
  }
  ~thrw() {
    std::cout << "thrw destructor\n";
    a.deallocate(x, size);
  }
};

class thrw_child : public thrw {
 public:
  thrw_child() : thrw() {
    std::cout << "thrw_child constructor\n";
    allocate_memory();
  }
  ~thrw_child() { std::cout << "thrw_child destructor\n"; }
};

void raii_test() {
  thrw a;
  std::cout << "a constructed...\n";
  a.allocate_memory();
}

void raii_child_test() { thrw_child a; }

int main() {
  try {
    raii_test();
  } catch (std::exception &e) {
    std::cout << e.what() << " in Main raii_test CATCH\n";
  }
  try {
    raii_child_test();
  } catch (std::exception &e) {
    std::cout << e.what() << " in Main raii_child_test CATCH\n";
  }
  system("leaks mine.out | grep leaked");
}