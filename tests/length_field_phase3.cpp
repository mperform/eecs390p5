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

  void test_default() {
    UC_REFERENCE(foo) var0 = uc_construct<UC_REFERENCE(foo)>();
    UC_REFERENCE(foo) var0b = uc_construct<UC_REFERENCE(foo)>();
    assert(var0 == var0b);
    assert(!(var0 != var0b));
    assert(var0->UC_VAR(x) == UC_PRIMITIVE(int){});
    assert(var0->UC_VAR(length) == UC_PRIMITIVE(string){});
  }

  void test_non_default_with_defaults() {
    UC_REFERENCE(foo) var0 = uc_construct<UC_REFERENCE(foo)>(UC_PRIMITIVE(int){},
                                                             UC_PRIMITIVE(string){});
    assert(var0->UC_VAR(x) == UC_PRIMITIVE(int){});
    assert(var0->UC_VAR(length) == UC_PRIMITIVE(string){});
  }

  void test_non_default_with_non_defaults() {
    UC_PRIMITIVE(int) arg0_0 = 1;
    UC_PRIMITIVE(int) arg0_0c = 2;
    UC_PRIMITIVE(string) arg0_1 = "foo3";
    UC_PRIMITIVE(string) arg0_1c = "foo4";
    UC_REFERENCE(foo) var0 = uc_construct<UC_REFERENCE(foo)>(arg0_0,
                                                             arg0_1);
    UC_REFERENCE(foo) var0b = uc_construct<UC_REFERENCE(foo)>(arg0_0,
                                                              arg0_1);
    UC_REFERENCE(foo) var0c = uc_construct<UC_REFERENCE(foo)>(arg0_0c,
                                                              arg0_1c);
    assert(var0 == var0b);
    assert(!(var0 != var0b));
    assert(var0 != var0c);
    assert(!(var0 == var0c));
    assert(var0->UC_VAR(x) == arg0_0);
    assert(var0->UC_VAR(length) == arg0_1);
  }

}

int main() {
  uc::test_default();
  uc::test_non_default_with_defaults();
  uc::test_non_default_with_non_defaults();
  return 0;
}
