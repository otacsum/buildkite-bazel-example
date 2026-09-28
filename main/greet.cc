#include "main/greet.h"

std::string get_greet(const std::string& who) {
  return "Hello dynamic Bazel pipelines " + who;
}
