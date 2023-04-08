// WARNING: This is a test file, NOT the expected output of the
// compiler. Rather, this file #includes the generated length_field.cpp
// file and directly tests its contents using C++ code. See the
// project spec for what the compiler should generate in each phase.

#include <cassert>
#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  #include "length_field.cpp"

  void test() {
    UC_FUNCTION(bar)(UC_REFERENCE(foo){});
    UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)){});
  }

}

int main() {
  uc::test();
  return 0;
}
