#include <sys/time.h>

#include <iostream>
int f2(int n);

int f1(int n) {
  if (n == 42424) return n;
  return (f2(++n));
}

int f2(int n) {
  f1(++n);
  return n;
}

int f3() throw() { return (f1(0)); }

void throw_test() {
  try {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    suseconds_t begin = tp.tv_usec;
    std::cout << tp.tv_sec << ":" << tp.tv_usec << "\n";
    int n = f3();
    gettimeofday(&tp, NULL);
    suseconds_t end = tp.tv_usec;
    std::cout << tp.tv_sec << ":" << tp.tv_usec << "\n";
    std::cout << n;
    std::cout << "\nresult : " << end - begin << "\n";
  } catch (...) {
    std::cout << "don't print\n";
  }
}

int main() { throw_test(); }