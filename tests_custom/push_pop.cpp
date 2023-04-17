#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  // Forward type declarations

  struct UC_TYPEDEF(foo);
  struct UC_TYPEDEF(bar);
  struct UC_TYPEDEF(baz);
  // Forward function declarations

UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
UC_PRIMITIVE(void)
  UC_FUNCTION(test)();
  // Full type definitions

struct UC_TYPEDEF(foo) {
  // member variable declaratons
  UC_PRIMITIVE(int) UC_VAR(x);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(x) == rhs.UC_VAR(x);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(x) != rhs.UC_VAR(x);
}
//default constructor
UC_TYPEDEF(foo)() : 

  UC_VAR(x)()
{}
//non default constructor
UC_TYPEDEF(foo)(UC_PRIMITIVE(int) UC_VAR(x)) : UC_VAR(x){UC_VAR(x)}{}
};
struct UC_TYPEDEF(bar) {
  // member variable declaratons
  UC_REFERENCE(foo) UC_VAR(f);
  UC_PRIMITIVE(int) UC_VAR(x);
  UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(a);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(bar) &rhs) const {
  return UC_VAR(f) == rhs.UC_VAR(f) && UC_VAR(x) == rhs.UC_VAR(x) && UC_VAR(a) == rhs.UC_VAR(a);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(bar) &rhs) const {
  return UC_VAR(f) != rhs.UC_VAR(f) || UC_VAR(x) != rhs.UC_VAR(x) || UC_VAR(a) != rhs.UC_VAR(a);
}
//default constructor
UC_TYPEDEF(bar)() : 

  UC_VAR(f)(), UC_VAR(x)(), UC_VAR(a)()
{}
//non default constructor
UC_TYPEDEF(bar)(UC_REFERENCE(foo) UC_VAR(f), UC_PRIMITIVE(int) UC_VAR(x), UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(a)) : UC_VAR(f){UC_VAR(f)}, UC_VAR(x){UC_VAR(x)}, UC_VAR(a){UC_VAR(a)}{}
};
struct UC_TYPEDEF(baz) {
  // member variable declaratons
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(baz) &rhs) const {
  return true;
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(baz) &rhs) const {
  return false;
}
};
  // Full function definitions

UC_PRIMITIVE(void) UC_FUNCTION(main) (UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(args)){
  // decl local uC vars
  UC_REFERENCE(foo) UC_VAR(f);
  UC_REFERENCE(bar) UC_VAR(b);
  UC_REFERENCE(baz) UC_VAR(z);
  // Block Body
(UC_VAR(f) = uc_construct<UC_REFERENCE(foo)>()
); //Statement
(UC_VAR(b) = uc_construct<UC_REFERENCE(bar)>()
); //Statement
(UC_VAR(z) = uc_construct<UC_REFERENCE(baz)>()
); //Statement
UC_FUNCTION(println)(UC_FUNCTION(int_to_string)(UC_VAR(f)->UC_VAR(x))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((UC_VAR(b)->UC_VAR(f) == nullptr))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((UC_VAR(b)->UC_VAR(a) == nullptr))); //Statement
UC_FUNCTION(test)(); //Statement
}
UC_PRIMITIVE(void) UC_FUNCTION(test) (){
  // decl local uC vars
  UC_PRIMITIVE(int) UC_VAR(start);
  UC_PRIMITIVE(int) UC_VAR(num);
  UC_ARRAY(UC_PRIMITIVE(int)) UC_VAR(arr);
  // Block Body
(UC_VAR(start) = 0); //Statement
(UC_VAR(num) = 0); //Statement
(UC_VAR(arr) = uc_construct<UC_ARRAY(UC_PRIMITIVE(int))>()
); //Statement
  // Start of While Block
while ((UC_VAR(start) < 10)) {
  // Block Body
uc_array_push(UC_VAR(arr), UC_VAR(start)); //Statement
++UC_VAR(start); //Statement
  }
; //Statement
UC_FUNCTION(println)(UC_FUNCTION(int_to_string)(uc_array_index(UC_VAR(arr), 5))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(int_to_string)(uc_array_index(UC_VAR(arr), UC_VAR(num)))); //Statement
(UC_VAR(start) = 0); //Statement
  // Start of While Block
while ((UC_VAR(start) < 10)) {
  // Block Body
uc_array_pop(UC_VAR(arr), UC_VAR(num)); //Statement
++UC_VAR(start); //Statement
  }
; //Statement
(UC_VAR(start) = 0); //Statement
(UC_VAR(num) = 0); //Statement
  // Start of While Block
while ((UC_VAR(start) < 10)) {
  // Block Body
uc_array_push(UC_VAR(arr), 1); //Statement
++UC_VAR(start); //Statement
  }
; //Statement
UC_FUNCTION(println)(UC_FUNCTION(int_to_string)(uc_array_index(UC_VAR(arr), 5))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(int_to_string)(uc_array_index(UC_VAR(arr), UC_VAR(num)))); //Statement
(UC_VAR(start) = 0); //Statement
  // Start of While Block
while ((UC_VAR(start) < 10)) {
  // Block Body
uc_array_pop(UC_VAR(arr), UC_VAR(num)); //Statement
++UC_VAR(start); //Statement
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
