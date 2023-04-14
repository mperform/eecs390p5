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
