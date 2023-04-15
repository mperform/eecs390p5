  // Forward type declarations

  struct UC_TYPEDEF(particle);
  // Forward function declarations

UC_PRIMITIVE(int)
  UC_FUNCTION(num_particles)();
UC_PRIMITIVE(int)
  UC_FUNCTION(num_steps)();
UC_PRIMITIVE(float)
  UC_FUNCTION(box_size)();
UC_ARRAY(UC_PRIMITIVE(float))
  UC_FUNCTION(initial_x_positions)();
UC_ARRAY(UC_PRIMITIVE(float))
  UC_FUNCTION(initial_y_positions)();
UC_ARRAY(UC_PRIMITIVE(float))
  UC_FUNCTION(initial_x_velocities)();
UC_ARRAY(UC_PRIMITIVE(float))
  UC_FUNCTION(initial_y_velocities)();
UC_PRIMITIVE(float)
  UC_FUNCTION(density)();
UC_PRIMITIVE(float)
  UC_FUNCTION(mass)();
UC_PRIMITIVE(float)
  UC_FUNCTION(cutoff_radius)();
UC_PRIMITIVE(float)
  UC_FUNCTION(min_radius_squared)();
UC_PRIMITIVE(float)
  UC_FUNCTION(time_interval)();
UC_PRIMITIVE(float)
  UC_FUNCTION(max)(UC_PRIMITIVE(float), UC_PRIMITIVE(float));
UC_PRIMITIVE(void)
  UC_FUNCTION(apply_force)(UC_REFERENCE(particle), UC_REFERENCE(particle));
UC_PRIMITIVE(void)
  UC_FUNCTION(move_particle)(UC_REFERENCE(particle));
UC_PRIMITIVE(void)
  UC_FUNCTION(print_particle_positions)(UC_ARRAY(UC_REFERENCE(particle)));
UC_ARRAY(UC_REFERENCE(particle))
  UC_FUNCTION(make_particles)(UC_PRIMITIVE(int));
UC_PRIMITIVE(void)
  UC_FUNCTION(simulate)(UC_PRIMITIVE(int));
UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
  // Full type definitions

struct UC_TYPEDEF(particle) {
  // member variable declaratons
  UC_PRIMITIVE(float) UC_VAR(x);
  UC_PRIMITIVE(float) UC_VAR(y);
  UC_PRIMITIVE(float) UC_VAR(x_vel);
  UC_PRIMITIVE(float) UC_VAR(y_vel);
  UC_PRIMITIVE(float) UC_VAR(x_acc);
  UC_PRIMITIVE(float) UC_VAR(y_acc);
  UC_PRIMITIVE(int) UC_VAR(id);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(particle) &rhs) const {
  return UC_VAR(x) == rhs.UC_VAR(x) && UC_VAR(y) == rhs.UC_VAR(y) && UC_VAR(x_vel) == rhs.UC_VAR(x_vel) && UC_VAR(y_vel) == rhs.UC_VAR(y_vel) && UC_VAR(x_acc) == rhs.UC_VAR(x_acc) && UC_VAR(y_acc) == rhs.UC_VAR(y_acc) && UC_VAR(id) == rhs.UC_VAR(id);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(particle) &rhs) const {
  return UC_VAR(x) != rhs.UC_VAR(x) || UC_VAR(y) != rhs.UC_VAR(y) || UC_VAR(x_vel) != rhs.UC_VAR(x_vel) || UC_VAR(y_vel) != rhs.UC_VAR(y_vel) || UC_VAR(x_acc) != rhs.UC_VAR(x_acc) || UC_VAR(y_acc) != rhs.UC_VAR(y_acc) || UC_VAR(id) != rhs.UC_VAR(id);
}
//default constructor
UC_TYPEDEF(particle)() : 

  UC_VAR(x)(), UC_VAR(y)(), UC_VAR(x_vel)(), UC_VAR(y_vel)(), UC_VAR(x_acc)(), UC_VAR(y_acc)(), UC_VAR(id)()
{}
//non default constructor
UC_TYPEDEF(particle)(UC_PRIMITIVE(float) UC_VAR(x), UC_PRIMITIVE(float) UC_VAR(y), UC_PRIMITIVE(float) UC_VAR(x_vel), UC_PRIMITIVE(float) UC_VAR(y_vel), UC_PRIMITIVE(float) UC_VAR(x_acc), UC_PRIMITIVE(float) UC_VAR(y_acc), UC_PRIMITIVE(int) UC_VAR(id)) : UC_VAR(x){UC_VAR(x)}, UC_VAR(y){UC_VAR(y)}, UC_VAR(x_vel){UC_VAR(x_vel)}, UC_VAR(y_vel){UC_VAR(y_vel)}, UC_VAR(x_acc){UC_VAR(x_acc)}, UC_VAR(y_acc){UC_VAR(y_acc)}, UC_VAR(id){UC_VAR(id)}{}
};
