/**
 * @file vector_main.cpp
 * @author yongjule (lyjshow200@gmail.com)
 * @brief How vector works?
 * @version 0.1
 * @date 2022-03-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <memory>
#include <vector>

int main(void) {
  std::vector<int> a;
  std::vector<int> b(a);
  a.push_back(10);
  a.push_back(10);
  a.push_back(10);
  a.push_back(10);
}