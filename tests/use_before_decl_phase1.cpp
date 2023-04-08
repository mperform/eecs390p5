// WARNING: This is a test file, NOT the expected output of the
// compiler. Rather, this file #includes the generated use_before_decl.cpp
// file and directly tests its contents using C++ code. See the
// project spec for what the compiler should generate in each phase.

#include <cassert>
#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  #include "use_before_decl.cpp"

  void UC_CONCAT(UC_TYPEDEF(baz), _test)(UC_REFERENCE(baz));
  void UC_CONCAT(UC_TYPEDEF(foo), _test)(UC_REFERENCE(foo));

}

int main() {
  return 0;
}
