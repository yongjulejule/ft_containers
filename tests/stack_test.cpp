#include "test.hpp"

void method_test(int argc, char **argv) {
  ft::stack<std::string> stk;
  std::cout << std::boolalpha;
  PRINT("stk.empty :", stk.empty());
  for (int i = 0; i < argc; i++) {
    PRINT("stk.push(", argv[i], ")");
    stk.push(argv[i]);
    PRINT("stk.size() :", stk.size());
  }
  PRINT("stk.empty :", stk.empty());
  for (int i = 0; i < argc; i++) {
    PRINT("stk.top() : ", stk.top());
    stk.pop();
  }
  PRINT("stk.empty :", stk.empty());
}

template <typename stack>
void print_stack(stack &stk) {
  PRINT("stack (size, empty, top) (", stk.size(), ", ", stk.empty(), ", ",
        stk.top(), ")");
}

void operator_test() {
  ft::stack<double> a;
  ft::stack<double> b;
  PRINT("push to stack a , b");
  for (int i = 0; i < 10; i++) {
    a.push(4.2 + i);
    b.push(4.2 + i);
    std::cout << "[" << 4.2 + i << "] ";
  }
  std::cout << "\n";
  PRINT("stack a");
  print_stack(a);
  PRINT("stack b");
  print_stack(b);
  PRINT("b.pop()");
  b.pop();
  PRINT("stack b");
  print_stack(b);
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  PRINT("b.push(13.2)");
  b.push(13.2);
  PRINT("stack a");
  print_stack(a);
  PRINT("stack b");
  print_stack(b);
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  PRINT("b.pop()");
  b.pop();
  PRINT("stack a");
  print_stack(a);
  PRINT("stack b");
  print_stack(b);
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
  PRINT("b.push(13.2)");
  b.push(13.2);
  PRINT("stack a");
  print_stack(a);
  PRINT("stack b");
  print_stack(b);
  PRINT("a == b, a != b, a < b, a <= b, a > b, a >= b");
  PRINT(a == b, ", ", a != b, ", ", a<b, ", ", a <= b, ", ", a> b, ", ",
        a >= b);
}

int main(int argc, char **argv) {
  method_test(argc, argv);
  operator_test();
}