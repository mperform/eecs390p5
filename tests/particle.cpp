#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

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
  // Full function definitions

UC_PRIMITIVE(int) UC_FUNCTION(num_particles) (){
  // decl local uC vars
  // Block Body
return 20;//return node; //Statement
}
UC_PRIMITIVE(int) UC_FUNCTION(num_steps) (){
  // decl local uC vars
  // Block Body
return 10;//return node; //Statement
}
UC_PRIMITIVE(float) UC_FUNCTION(box_size) (){
  // decl local uC vars
  // Block Body
return 0.1;//return node; //Statement
}
UC_ARRAY(UC_PRIMITIVE(float)) UC_FUNCTION(initial_x_positions) (){
  // decl local uC vars
  // Block Body
return uc_construct<UC_ARRAY(UC_PRIMITIVE(float))>(0.0167, 0.033, 0.05, 0.0667, 0.0833, 0.0167, 0.033, 0.05, 0.0667, 0.0833, 0.0167, 0.033, 0.05, 0.0667, 0.0833, 0.0167, 0.033, 0.05, 0.0667, 0.0833)
;//return node; //Statement
}
UC_ARRAY(UC_PRIMITIVE(float)) UC_FUNCTION(initial_y_positions) (){
  // decl local uC vars
  // Block Body
return uc_construct<UC_ARRAY(UC_PRIMITIVE(float))>(0.02, 0.02, 0.02, 0.02, 0.02, 0.04, 0.04, 0.04, 0.04, 0.04, 0.06, 0.06, 0.06, 0.06, 0.06, 0.08, 0.08, 0.08, 0.08, 0.08)
;//return node; //Statement
}
UC_ARRAY(UC_PRIMITIVE(float)) UC_FUNCTION(initial_x_velocities) (){
  // decl local uC vars
  // Block Body
return uc_construct<UC_ARRAY(UC_PRIMITIVE(float))>(-0.482, 0.430, -0.338, -0.556, -0.332, 0.880, -0.730, 0.458, 0.576, 0.792, -0.810, -0.836, 0.572, -0.038, -0.960, 0.872, 0.704, -0.35, -0.374, -0.348)
;//return node; //Statement
}
UC_ARRAY(UC_PRIMITIVE(float)) UC_FUNCTION(initial_y_velocities) (){
  // decl local uC vars
  // Block Body
return uc_construct<UC_ARRAY(UC_PRIMITIVE(float))>(-0.330, -0.622, 0.088, -0.058, 0.328, 0.292, 0.792, 0.648, 0.812, -0.460, -0.382, -0.624, 0.262, -0.662, -0.212, 0.914, -0.898, -0.026, -0.062, 0.008)
;//return node; //Statement
}
UC_PRIMITIVE(float) UC_FUNCTION(density) (){
  // decl local uC vars
  // Block Body
return 0.0005;//return node; //Statement
}
UC_PRIMITIVE(float) UC_FUNCTION(mass) (){
  // decl local uC vars
  // Block Body
return 0.01;//return node; //Statement
}
UC_PRIMITIVE(float) UC_FUNCTION(cutoff_radius) (){
  // decl local uC vars
  // Block Body
return 0.01;//return node; //Statement
}
UC_PRIMITIVE(float) UC_FUNCTION(min_radius_squared) (){
  // decl local uC vars
  // Block Body
return UC_FUNCTION(pow)((UC_FUNCTION(cutoff_radius)() / 100), 2);//return node; //Statement
}
UC_PRIMITIVE(float) UC_FUNCTION(time_interval) (){
  // decl local uC vars
  // Block Body
return 0.0005;//return node; //Statement
}
UC_PRIMITIVE(float) UC_FUNCTION(max) (UC_PRIMITIVE(float) UC_VAR(a), UC_PRIMITIVE(float) UC_VAR(b)){
  // decl local uC vars
  // Block Body
  
  // Start of If Block
  if ((UC_VAR(a) > UC_VAR(b))){
  // Block Body
return UC_VAR(a);//return node; //Statement
  }
; //Statement
return UC_VAR(b);//return node; //Statement
}
UC_PRIMITIVE(void) UC_FUNCTION(apply_force) (UC_REFERENCE(particle) UC_VAR(p), UC_REFERENCE(particle) UC_VAR(other)){
  // decl local uC vars
  UC_PRIMITIVE(float) UC_VAR(dx);
  UC_PRIMITIVE(float) UC_VAR(dy);
  UC_PRIMITIVE(float) UC_VAR(radius2);
  UC_PRIMITIVE(float) UC_VAR(radius);
  UC_PRIMITIVE(float) UC_VAR(coefficient);
  // Block Body
(UC_VAR(dx) = (UC_VAR(other)->UC_VAR(x) - UC_VAR(p)->UC_VAR(x))); //Statement
(UC_VAR(dy) = (UC_VAR(other)->UC_VAR(y) - UC_VAR(p)->UC_VAR(y))); //Statement
  
  // Start of If Block
  if (((UC_VAR(dx) == 0) && (UC_VAR(dy) == 0))){
  // Block Body
return;//return node; //Statement
  }
; //Statement
(UC_VAR(radius2) = UC_FUNCTION(max)((uc_add((UC_VAR(dx) * UC_VAR(dx)), (UC_VAR(dy) * UC_VAR(dy)))), UC_FUNCTION(min_radius_squared)())); //Statement
  
  // Start of If Block
  if ((UC_VAR(radius2) > (UC_FUNCTION(cutoff_radius)() * UC_FUNCTION(cutoff_radius)()))){
  // Block Body
return;//return node; //Statement
  }
; //Statement
(UC_VAR(radius) = UC_FUNCTION(sqrt)(UC_VAR(radius2))); //Statement
(UC_VAR(coefficient) = (((1 - (UC_FUNCTION(cutoff_radius)() / UC_VAR(radius))) / UC_VAR(radius2)) / UC_FUNCTION(mass)())); //Statement
(UC_VAR(p)->UC_VAR(x_acc) = (uc_add(UC_VAR(p)->UC_VAR(x_acc), (UC_VAR(coefficient) * UC_VAR(dx))))); //Statement
(UC_VAR(p)->UC_VAR(y_acc) = (uc_add(UC_VAR(p)->UC_VAR(y_acc), (UC_VAR(coefficient) * UC_VAR(dy))))); //Statement
}
UC_PRIMITIVE(void) UC_FUNCTION(move_particle) (UC_REFERENCE(particle) UC_VAR(p)){
  // decl local uC vars
  // Block Body
(UC_VAR(p)->UC_VAR(x_vel) = (uc_add(UC_VAR(p)->UC_VAR(x_vel), (UC_VAR(p)->UC_VAR(x_acc) * UC_FUNCTION(time_interval)())))); //Statement
(UC_VAR(p)->UC_VAR(y_vel) = (uc_add(UC_VAR(p)->UC_VAR(y_vel), (UC_VAR(p)->UC_VAR(y_acc) * UC_FUNCTION(time_interval)())))); //Statement
(UC_VAR(p)->UC_VAR(x) = (uc_add(UC_VAR(p)->UC_VAR(x), (UC_VAR(p)->UC_VAR(x_vel) * UC_FUNCTION(time_interval)())))); //Statement
(UC_VAR(p)->UC_VAR(y) = (uc_add(UC_VAR(p)->UC_VAR(y), (UC_VAR(p)->UC_VAR(y_vel) * UC_FUNCTION(time_interval)())))); //Statement
  // Start of While Block
while (((UC_VAR(p)->UC_VAR(x) < 0) || (UC_VAR(p)->UC_VAR(x) > UC_FUNCTION(box_size)()))) {
  // Block Body
  
  // Start of If Block
  if ((UC_VAR(p)->UC_VAR(x) < 0)){
  // Block Body
(UC_VAR(p)->UC_VAR(x) = -UC_VAR(p)->UC_VAR(x)); //Statement
  } else {
  // Block Body
(UC_VAR(p)->UC_VAR(x) = ((2 * UC_FUNCTION(box_size)()) - UC_VAR(p)->UC_VAR(x))); //Statement
  }
; //Statement
(UC_VAR(p)->UC_VAR(x_vel) = -UC_VAR(p)->UC_VAR(x_vel)); //Statement
  }
; //Statement
  // Start of While Block
while (((UC_VAR(p)->UC_VAR(y) < 0) || (UC_VAR(p)->UC_VAR(y) > UC_FUNCTION(box_size)()))) {
  // Block Body
  
  // Start of If Block
  if ((UC_VAR(p)->UC_VAR(y) < 0)){
  // Block Body
(UC_VAR(p)->UC_VAR(y) = -UC_VAR(p)->UC_VAR(y)); //Statement
  } else {
  // Block Body
(UC_VAR(p)->UC_VAR(y) = ((2 * UC_FUNCTION(box_size)()) - UC_VAR(p)->UC_VAR(y))); //Statement
  }
; //Statement
(UC_VAR(p)->UC_VAR(y_vel) = -UC_VAR(p)->UC_VAR(y_vel)); //Statement
  }
; //Statement
}
UC_PRIMITIVE(void) UC_FUNCTION(print_particle_positions) (UC_ARRAY(UC_REFERENCE(particle)) UC_VAR(ps)){
  // decl local uC vars
  UC_PRIMITIVE(int) UC_VAR(i);
  // Block Body
  // Start of For Block
  for ((UC_VAR(i) = 0); (UC_VAR(i) <   uc_length_field(UC_VAR(ps))); ++UC_VAR(i)) {
  // Block Body
UC_FUNCTION(println)((uc_add((uc_add((uc_add((uc_add(uc_array_index(UC_VAR(ps), UC_VAR(i))->UC_VAR(id), ": "s)), uc_array_index(UC_VAR(ps), UC_VAR(i))->UC_VAR(x))), ", "s)), uc_array_index(UC_VAR(ps), UC_VAR(i))->UC_VAR(y)))); //Statement
  }
; //Statement
UC_FUNCTION(println)(""s); //Statement
}
UC_ARRAY(UC_REFERENCE(particle)) UC_FUNCTION(make_particles) (UC_PRIMITIVE(int) UC_VAR(num_particles)){
  // decl local uC vars
  UC_ARRAY(UC_REFERENCE(particle)) UC_VAR(particles);
  UC_ARRAY(UC_PRIMITIVE(float)) UC_VAR(xs);
  UC_ARRAY(UC_PRIMITIVE(float)) UC_VAR(ys);
  UC_ARRAY(UC_PRIMITIVE(float)) UC_VAR(xvs);
  UC_ARRAY(UC_PRIMITIVE(float)) UC_VAR(yvs);
  UC_PRIMITIVE(int) UC_VAR(i);
  // Block Body
(UC_VAR(particles) = uc_construct<UC_ARRAY(UC_REFERENCE(particle))>()
); //Statement
(UC_VAR(xs) = UC_FUNCTION(initial_x_positions)()); //Statement
(UC_VAR(ys) = UC_FUNCTION(initial_y_positions)()); //Statement
(UC_VAR(xvs) = UC_FUNCTION(initial_x_velocities)()); //Statement
(UC_VAR(yvs) = UC_FUNCTION(initial_y_velocities)()); //Statement
  // Start of For Block
  for ((UC_VAR(i) = 0); (UC_VAR(i) < UC_VAR(num_particles)); ++UC_VAR(i)) {
  // Block Body
uc_array_push(UC_VAR(particles), uc_construct<UC_REFERENCE(particle)>(uc_array_index(UC_VAR(xs), UC_VAR(i)), uc_array_index(UC_VAR(ys), UC_VAR(i)), uc_array_index(UC_VAR(xvs), UC_VAR(i)), uc_array_index(UC_VAR(yvs), UC_VAR(i)), 0, 0, UC_VAR(i))
); //Statement
  }
; //Statement
return UC_VAR(particles);//return node; //Statement
}
UC_PRIMITIVE(void) UC_FUNCTION(simulate) (UC_PRIMITIVE(int) UC_VAR(num_steps)){
  // decl local uC vars
  UC_ARRAY(UC_REFERENCE(particle)) UC_VAR(particles);
  UC_PRIMITIVE(int) UC_VAR(step);
  UC_PRIMITIVE(int) UC_VAR(i);
  UC_PRIMITIVE(int) UC_VAR(j);
  // Block Body
(UC_VAR(particles) = UC_FUNCTION(make_particles)(UC_FUNCTION(num_particles)())); //Statement
UC_FUNCTION(println)("Initial"s); //Statement
UC_FUNCTION(print_particle_positions)(UC_VAR(particles)); //Statement
  // Start of For Block
  for ((UC_VAR(step) = 0); (UC_VAR(step) < UC_VAR(num_steps)); ++UC_VAR(step)) {
  // Block Body
UC_FUNCTION(println)((uc_add("Step "s, (uc_add(UC_VAR(step), 1))))); //Statement
  // Start of For Block
  for ((UC_VAR(i) = 0); (UC_VAR(i) < UC_FUNCTION(num_particles)()); ++UC_VAR(i)) {
  // Block Body
(uc_array_index(UC_VAR(particles), UC_VAR(i))->UC_VAR(x_acc) = 0); //Statement
(uc_array_index(UC_VAR(particles), UC_VAR(i))->UC_VAR(y_acc) = 0); //Statement
(UC_VAR(j) = 0); //Statement
  // Start of For Block
  for ((UC_VAR(j) = 0); (UC_VAR(j) < UC_FUNCTION(num_particles)()); ++UC_VAR(j)) {
  // Block Body
UC_FUNCTION(apply_force)(uc_array_index(UC_VAR(particles), UC_VAR(i)), uc_array_index(UC_VAR(particles), UC_VAR(j))); //Statement
  }
; //Statement
  }
; //Statement
  // Start of For Block
  for ((UC_VAR(i) = 0); (UC_VAR(i) < UC_FUNCTION(num_particles)()); ++UC_VAR(i)) {
  // Block Body
UC_FUNCTION(move_particle)(uc_array_index(UC_VAR(particles), UC_VAR(i))); //Statement
  }
; //Statement
UC_FUNCTION(print_particle_positions)(UC_VAR(particles)); //Statement
  }
; //Statement
}
UC_PRIMITIVE(void) UC_FUNCTION(main) (UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(args)){
  // decl local uC vars
  // Block Body
  
  // Start of If Block
  if ((  uc_length_field(UC_VAR(args)) > 0)){
  // Block Body
UC_FUNCTION(simulate)(UC_FUNCTION(string_to_int)(uc_array_index(UC_VAR(args), 0))); //Statement
  } else {
  // Block Body
UC_FUNCTION(simulate)(UC_FUNCTION(num_steps)()); //Statement
  }
; //Statement
}
} // namespace uc

int main(int argc, char **argv) {
  uc::UC_ARRAY(uc::UC_PRIMITIVE(string)) args = uc::uc_make_array_of<uc::UC_PRIMITIVE(string)>();
  for (int i = 1; i < argc; i++) {
    uc::uc_array_push(args, uc::UC_PRIMITIVE(string)(argv[i]));
  }
  uc::UC_FUNCTION(main)(args);
  return 0;
}
