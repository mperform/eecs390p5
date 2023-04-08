// WARNING: This is a test file, NOT the expected output of the
// compiler. Rather, this file #includes the generated particle.cpp
// file and directly tests its contents using C++ code. See the
// project spec for what the compiler should generate in each phase.

#include <cassert>
#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  #include "particle.cpp"

  void test_default() {
    UC_REFERENCE(particle) var0 = uc_construct<UC_REFERENCE(particle)>();
    UC_REFERENCE(particle) var0b = uc_construct<UC_REFERENCE(particle)>();
    assert(var0 == var0b);
    assert(!(var0 != var0b));
    assert(var0->UC_VAR(x) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(y) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(x_vel) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(y_vel) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(x_acc) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(y_acc) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(id) == UC_PRIMITIVE(int){});
  }

  void test_non_default_with_defaults() {
    UC_REFERENCE(particle) var0 = uc_construct<UC_REFERENCE(particle)>(UC_PRIMITIVE(float){},
                                                                       UC_PRIMITIVE(float){},
                                                                       UC_PRIMITIVE(float){},
                                                                       UC_PRIMITIVE(float){},
                                                                       UC_PRIMITIVE(float){},
                                                                       UC_PRIMITIVE(float){},
                                                                       UC_PRIMITIVE(int){});
    assert(var0->UC_VAR(x) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(y) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(x_vel) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(y_vel) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(x_acc) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(y_acc) == UC_PRIMITIVE(float){});
    assert(var0->UC_VAR(id) == UC_PRIMITIVE(int){});
  }

  void test_non_default_with_non_defaults() {
    UC_PRIMITIVE(float) arg0_0 = 1.1;
    UC_PRIMITIVE(float) arg0_0c = 2.1;
    UC_PRIMITIVE(float) arg0_1 = 3.1;
    UC_PRIMITIVE(float) arg0_1c = 4.1;
    UC_PRIMITIVE(float) arg0_2 = 5.1;
    UC_PRIMITIVE(float) arg0_2c = 6.1;
    UC_PRIMITIVE(float) arg0_3 = 7.1;
    UC_PRIMITIVE(float) arg0_3c = 8.1;
    UC_PRIMITIVE(float) arg0_4 = 9.1;
    UC_PRIMITIVE(float) arg0_4c = 10.1;
    UC_PRIMITIVE(float) arg0_5 = 11.1;
    UC_PRIMITIVE(float) arg0_5c = 12.1;
    UC_PRIMITIVE(int) arg0_6 = 13;
    UC_PRIMITIVE(int) arg0_6c = 14;
    UC_REFERENCE(particle) var0 = uc_construct<UC_REFERENCE(particle)>(arg0_0,
                                                                       arg0_1,
                                                                       arg0_2,
                                                                       arg0_3,
                                                                       arg0_4,
                                                                       arg0_5,
                                                                       arg0_6);
    UC_REFERENCE(particle) var0b = uc_construct<UC_REFERENCE(particle)>(arg0_0,
                                                                        arg0_1,
                                                                        arg0_2,
                                                                        arg0_3,
                                                                        arg0_4,
                                                                        arg0_5,
                                                                        arg0_6);
    UC_REFERENCE(particle) var0c = uc_construct<UC_REFERENCE(particle)>(arg0_0c,
                                                                        arg0_1c,
                                                                        arg0_2c,
                                                                        arg0_3c,
                                                                        arg0_4c,
                                                                        arg0_5c,
                                                                        arg0_6c);
    assert(var0 == var0b);
    assert(!(var0 != var0b));
    assert(var0 != var0c);
    assert(!(var0 == var0c));
    assert(var0->UC_VAR(x) == arg0_0);
    assert(var0->UC_VAR(y) == arg0_1);
    assert(var0->UC_VAR(x_vel) == arg0_2);
    assert(var0->UC_VAR(y_vel) == arg0_3);
    assert(var0->UC_VAR(x_acc) == arg0_4);
    assert(var0->UC_VAR(y_acc) == arg0_5);
    assert(var0->UC_VAR(id) == arg0_6);
  }

}

int main() {
  uc::test_default();
  uc::test_non_default_with_defaults();
  uc::test_non_default_with_non_defaults();
  return 0;
}
