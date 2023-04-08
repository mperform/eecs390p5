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

  void test_default() {
    UC_REFERENCE(bar) var0 = uc_construct<UC_REFERENCE(bar)>();
    UC_REFERENCE(bar) var0b = uc_construct<UC_REFERENCE(bar)>();
    assert(var0 == var0b);
    assert(!(var0 != var0b));
    UC_REFERENCE(foo) var1 = uc_construct<UC_REFERENCE(foo)>();
    UC_REFERENCE(foo) var1b = uc_construct<UC_REFERENCE(foo)>();
    assert(var1 == var1b);
    assert(!(var1 != var1b));
    assert(var1->UC_VAR(x) == UC_PRIMITIVE(int){});
  }

  void test_non_default_with_defaults() {
    UC_REFERENCE(bar) var0 = uc_construct<UC_REFERENCE(bar)>();
    UC_REFERENCE(foo) var1 = uc_construct<UC_REFERENCE(foo)>(UC_PRIMITIVE(int){});
    assert(var1->UC_VAR(x) == UC_PRIMITIVE(int){});
  }

  void test_non_default_with_non_defaults() {
    UC_REFERENCE(bar) var0 = uc_construct<UC_REFERENCE(bar)>();
    UC_REFERENCE(bar) var0b = uc_construct<UC_REFERENCE(bar)>();
    UC_REFERENCE(bar) var0c = uc_construct<UC_REFERENCE(bar)>();
    assert(var0 == var0b);
    assert(!(var0 != var0b));
    UC_PRIMITIVE(int) arg1_0 = 1;
    UC_PRIMITIVE(int) arg1_0c = 2;
    UC_REFERENCE(foo) var1 = uc_construct<UC_REFERENCE(foo)>(arg1_0);
    UC_REFERENCE(foo) var1b = uc_construct<UC_REFERENCE(foo)>(arg1_0);
    UC_REFERENCE(foo) var1c = uc_construct<UC_REFERENCE(foo)>(arg1_0c);
    assert(var1 == var1b);
    assert(!(var1 != var1b));
    assert(var1 != var1c);
    assert(!(var1 == var1c));
    assert(var1->UC_VAR(x) == arg1_0);
  }

}

int main() {
  uc::test_default();
  uc::test_non_default_with_defaults();
  uc::test_non_default_with_non_defaults();
  return 0;
}
