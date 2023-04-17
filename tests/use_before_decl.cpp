#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  // Forward type declarations

  struct UC_TYPEDEF(foo);
  struct UC_TYPEDEF(baz);
  // Forward function declarations

UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
UC_PRIMITIVE(void)
  UC_FUNCTION(bar)(UC_REFERENCE(foo));
  // Full type definitions

struct UC_TYPEDEF(foo) {
  // member variable declaratons
  UC_REFERENCE(baz) UC_VAR(b);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(b) == rhs.UC_VAR(b);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(b) != rhs.UC_VAR(b);
}
//default constructor
UC_TYPEDEF(foo)() : 

  UC_VAR(b)()
{}
//non default constructor
UC_TYPEDEF(foo)(UC_REFERENCE(baz) UC_VAR(b)) : UC_VAR(b){UC_VAR(b)}{}
};
struct UC_TYPEDEF(baz) {
  // member variable declaratons
  UC_PRIMITIVE(string) UC_VAR(s);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(baz) &rhs) const {
  return UC_VAR(s) == rhs.UC_VAR(s);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(baz) &rhs) const {
  return UC_VAR(s) != rhs.UC_VAR(s);
}
//default constructor
UC_TYPEDEF(baz)() : 

  UC_VAR(s)()
{}
//non default constructor
UC_TYPEDEF(baz)(UC_PRIMITIVE(string) UC_VAR(s)) : UC_VAR(s){UC_VAR(s)}{}
};
  // Full function definitions

UC_PRIMITIVE(void) UC_FUNCTION(main) (UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(args)){
  // decl local uC vars
  UC_REFERENCE(foo) UC_VAR(f);
  // Block Body
(UC_VAR(f) = uc_construct<UC_REFERENCE(foo)>(uc_construct<UC_REFERENCE(baz)>(uc_array_index(UC_VAR(args), 0))
)
); //Statement
UC_FUNCTION(bar)(UC_VAR(f)); //Statement
}
UC_PRIMITIVE(void) UC_FUNCTION(bar) (UC_REFERENCE(foo) UC_VAR(f)){
  // decl local uC vars
  // Block Body
UC_FUNCTION(println)(UC_VAR(f)->UC_VAR(b)->UC_VAR(s)); //Statement
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
