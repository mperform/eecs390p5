// WARNING: This is a test file, NOT the expected output of the
// compiler. Rather, this file #includes the generated equality.cpp
// file and directly tests its contents using C++ code. See the
// project spec for what the compiler should generate in each phase.

#include <cassert>
#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  #include "equality.cpp"

  void UC_CONCAT(UC_TYPEDEF(bar), _test)(UC_REFERENCE(bar));
  void UC_CONCAT(UC_TYPEDEF(foo), _test)(UC_REFERENCE(foo));

}

int main() {
  return 0;
}
