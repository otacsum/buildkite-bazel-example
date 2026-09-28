#include "main/greet.h"

#include <iostream>

int main() {
  if (!(get_greet("world") == "Hello dynamic Bazel pipelines world")) {
    std::cerr << "FAIL: get_greet(\"world\") != \"Hello world\"" << std::endl;
    return 1;
  }
  if (!(get_greet("") == "Hello dynamic Bazel pipelines ")) {
    std::cerr << "FAIL: get_greet(\"\") != \"Hello \"" << std::endl;
    return 1;
  }
  return 0;
}
