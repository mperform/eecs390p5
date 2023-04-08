// WARNING: This is a test file, NOT the expected output of the
// compiler. Rather, this file #includes the generated default.cpp
// file and directly tests its contents using C++ code. See the
// project spec for what the compiler should generate in each phase.

#include <cassert>
#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  #include "default.cpp"

  void test_default() {
    UC_REFERENCE(bar) var0 = uc_construct<UC_REFERENCE(bar)>();
    UC_REFERENCE(bar) var0b = uc_construct<UC_REFERENCE(bar)>();
    assert(var0 == var0b);
    assert(!(var0 != var0b));
    assert(var0->UC_VAR(f) == UC_REFERENCE(foo){});
    assert(var0->UC_VAR(x) == UC_PRIMITIVE(int){});
    assert(var0->UC_VAR(a) == UC_ARRAY(UC_PRIMITIVE(string)){});
    UC_REFERENCE(baz) var1 = uc_construct<UC_REFERENCE(baz)>();
    UC_REFERENCE(baz) var1b = uc_construct<UC_REFERENCE(baz)>();
    assert(var1 == var1b);
    assert(!(var1 != var1b));
    UC_REFERENCE(foo) var2 = uc_construct<UC_REFERENCE(foo)>();
    UC_REFERENCE(foo) var2b = uc_construct<UC_REFERENCE(foo)>();
    assert(var2 == var2b);
    assert(!(var2 != var2b));
    assert(var2->UC_VAR(x) == UC_PRIMITIVE(int){});
  }

  void test_non_default_with_defaults() {
    UC_REFERENCE(bar) var0 = uc_construct<UC_REFERENCE(bar)>(UC_REFERENCE(foo){},
                                                             UC_PRIMITIVE(int){},
                                                             UC_ARRAY(UC_PRIMITIVE(string)){});
    assert(var0->UC_VAR(f) == UC_REFERENCE(foo){});
    assert(var0->UC_VAR(x) == UC_PRIMITIVE(int){});
    assert(var0->UC_VAR(a) == UC_ARRAY(UC_PRIMITIVE(string)){});
    UC_REFERENCE(baz) var1 = uc_construct<UC_REFERENCE(baz)>();
    UC_REFERENCE(foo) var2 = uc_construct<UC_REFERENCE(foo)>(UC_PRIMITIVE(int){});
    assert(var2->UC_VAR(x) == UC_PRIMITIVE(int){});
  }

  void test_non_default_with_non_defaults() {
    UC_REFERENCE(foo) arg0_0 = uc_construct<UC_REFERENCE(foo)>();
    UC_REFERENCE(foo) arg0_0c = uc_construct<UC_REFERENCE(foo)>();
    UC_PRIMITIVE(int) arg0_1 = 1;
    UC_PRIMITIVE(int) arg0_1c = 2;
    UC_ARRAY(UC_PRIMITIVE(string)) arg0_2 = uc_construct<UC_ARRAY(UC_PRIMITIVE(string))>();
    UC_ARRAY(UC_PRIMITIVE(string)) arg0_2c = uc_construct<UC_ARRAY(UC_PRIMITIVE(string))>();
    UC_REFERENCE(bar) var0 = uc_construct<UC_REFERENCE(bar)>(arg0_0,
                                                             arg0_1,
                                                             arg0_2);
    UC_REFERENCE(bar) var0b = uc_construct<UC_REFERENCE(bar)>(arg0_0,
                                                              arg0_1,
                                                              arg0_2);
    UC_REFERENCE(bar) var0c = uc_construct<UC_REFERENCE(bar)>(arg0_0c,
                                                              arg0_1c,
                                                              arg0_2c);
    assert(var0 == var0b);
    assert(!(var0 != var0b));
    assert(var0 != var0c);
    assert(!(var0 == var0c));
    assert(var0->UC_VAR(f) == arg0_0);
    assert(var0->UC_VAR(x) == arg0_1);
    assert(var0->UC_VAR(a) == arg0_2);
    UC_REFERENCE(baz) var1 = uc_construct<UC_REFERENCE(baz)>();
    UC_REFERENCE(baz) var1b = uc_construct<UC_REFERENCE(baz)>();
    UC_REFERENCE(baz) var1c = uc_construct<UC_REFERENCE(baz)>();
    assert(var1 == var1b);
    assert(!(var1 != var1b));
    UC_PRIMITIVE(int) arg2_0 = 3;
    UC_PRIMITIVE(int) arg2_0c = 4;
    UC_REFERENCE(foo) var2 = uc_construct<UC_REFERENCE(foo)>(arg2_0);
    UC_REFERENCE(foo) var2b = uc_construct<UC_REFERENCE(foo)>(arg2_0);
    UC_REFERENCE(foo) var2c = uc_construct<UC_REFERENCE(foo)>(arg2_0c);
    assert(var2 == var2b);
    assert(!(var2 != var2b));
    assert(var2 != var2c);
    assert(!(var2 == var2c));
    assert(var2->UC_VAR(x) == arg2_0);
  }

}

int main() {
  uc::test_default();
  uc::test_non_default_with_defaults();
  uc::test_non_default_with_non_defaults();
  return 0;
}
