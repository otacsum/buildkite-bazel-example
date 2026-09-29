#include "main/greet.h"

#include <iostream>

int main() {
  if (!(get_greet("world") == "Hello dynamic Bazel pipelines 2 world")) {
    std::cerr << "FAIL: get_greet(\"world\") != \"Hello world\"" << std::endl;
    return 1;
  }
  if (!(get_greet("") == "Hello dynamic Bazel pipelines 2 ")) {
    std::cerr << "FAIL: get_greet(\"\") != \"Hello \"" << std::endl;
    return 1;
  }
  return 0;
}
