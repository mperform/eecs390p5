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

  void test() {
    UC_FUNCTION(apply_force)(UC_REFERENCE(particle){},
                             UC_REFERENCE(particle){});
    UC_PRIMITIVE(float) var1 = UC_FUNCTION(box_size)();
    UC_PRIMITIVE(float) var2 = UC_FUNCTION(cutoff_radius)();
    UC_PRIMITIVE(float) var3 = UC_FUNCTION(density)();
    UC_ARRAY(UC_PRIMITIVE(float)) var4 = UC_FUNCTION(initial_x_positions)();
    UC_ARRAY(UC_PRIMITIVE(float)) var5 = UC_FUNCTION(initial_x_velocities)();
    UC_ARRAY(UC_PRIMITIVE(float)) var6 = UC_FUNCTION(initial_y_positions)();
    UC_ARRAY(UC_PRIMITIVE(float)) var7 = UC_FUNCTION(initial_y_velocities)();
    UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)){});
    UC_ARRAY(UC_REFERENCE(particle)) var9 = UC_FUNCTION(make_particles)(UC_PRIMITIVE(int){});
    UC_PRIMITIVE(float) var10 = UC_FUNCTION(mass)();
    UC_PRIMITIVE(float) var11 = UC_FUNCTION(max)(UC_PRIMITIVE(float){},
                                                 UC_PRIMITIVE(float){});
    UC_PRIMITIVE(float) var12 = UC_FUNCTION(min_radius_squared)();
    UC_FUNCTION(move_particle)(UC_REFERENCE(particle){});
    UC_PRIMITIVE(int) var14 = UC_FUNCTION(num_particles)();
    UC_PRIMITIVE(int) var15 = UC_FUNCTION(num_steps)();
    UC_FUNCTION(print_particle_positions)(UC_ARRAY(UC_REFERENCE(particle)){});
    UC_FUNCTION(simulate)(UC_PRIMITIVE(int){});
    UC_PRIMITIVE(float) var18 = UC_FUNCTION(time_interval)();
  }

}

int main() {
  uc::test();
  return 0;
}
