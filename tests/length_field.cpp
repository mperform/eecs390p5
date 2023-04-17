#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  // Forward type declarations

  struct UC_TYPEDEF(foo);
  // Forward function declarations

UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
UC_PRIMITIVE(void)
  UC_FUNCTION(bar)(UC_REFERENCE(foo));
  // Full type definitions

struct UC_TYPEDEF(foo) {
  // member variable declaratons
  UC_PRIMITIVE(int) UC_VAR(x);
  UC_PRIMITIVE(string) UC_VAR(length);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(x) == rhs.UC_VAR(x) && UC_VAR(length) == rhs.UC_VAR(length);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(x) != rhs.UC_VAR(x) || UC_VAR(length) != rhs.UC_VAR(length);
}
//default constructor
UC_TYPEDEF(foo)() : 

  UC_VAR(x)(), UC_VAR(length)()
{}
//non default constructor
UC_TYPEDEF(foo)(UC_PRIMITIVE(int) UC_VAR(x), UC_PRIMITIVE(string) UC_VAR(length)) : UC_VAR(x){UC_VAR(x)}, UC_VAR(length){UC_VAR(length)}{}
};
  // Full function definitions

UC_PRIMITIVE(void) UC_FUNCTION(main) (UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(args)){
  // decl local uC vars
  UC_REFERENCE(foo) UC_VAR(f);
  // Block Body
UC_FUNCTION(println)((""s +   uc_length_field(UC_VAR(args)))); //Statement
(UC_VAR(f) = uc_construct<UC_REFERENCE(foo)>(3, "hello"s)
); //Statement
UC_FUNCTION(println)(  uc_length_field(UC_VAR(f))); //Statement
(  uc_length_field(UC_VAR(f)) = "world"s); //Statement
UC_FUNCTION(println)(  uc_length_field(UC_VAR(f))); //Statement
}
UC_PRIMITIVE(void) UC_FUNCTION(bar) (UC_REFERENCE(foo) UC_VAR(f)){
  // decl local uC vars
  // Block Body
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
