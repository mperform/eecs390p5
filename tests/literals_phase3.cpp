// WARNING: This is a test file, NOT the expected output of the
// compiler. Rather, this file #includes the generated literals.cpp
// file and directly tests its contents using C++ code. See the
// project spec for what the compiler should generate in each phase.

#include <cassert>
#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  #include "literals.cpp"

  void test_default() {
  }

  void test_non_default_with_defaults() {
  }

  void test_non_default_with_non_defaults() {
  }

}

int main() {
  uc::test_default();
  uc::test_non_default_with_defaults();
  uc::test_non_default_with_non_defaults();
  return 0;
}
